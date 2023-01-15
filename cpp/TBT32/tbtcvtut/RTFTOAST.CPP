#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include <ctype.h>
#include "rtf.h"

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static int get_code_word( FILE *stream, CODE_WORD *cwp );
static int to_win( int c );
static int set_win( FILE *in, FILE *OUT, CODE_WORD *cwp, char *s );
static int rtf_read( FILE *stream, CODE_WORD *cwp );
static int skip_dest( FILE *in, FILE *OUT, CODE_WORD *cwp, char *s );
static int set_caps( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int set_inv( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int output_bold( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int output_head( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int output_us( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int plain( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int font( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int output( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
static int do_code( CODE_WORD *cwp, FILE *in, FILE *out );

static int brace_state;
static int map_caps;
static int map_win;
static int map_inv;
static int hi_char;
static int bold;
static int underscore;
static int cwd_count = 59;
static int to_winf;

#define STATE_CNT 25

static STATE state_stack[STATE_CNT];
static int state_sp = -1;
static STATE curr_state = { 0, 0, 0, 0, 0, 0, 20 };

static CWDO cwd_array[] = { "par", "\n", output, "b", "", output_bold,
   "i", "", output_us, "ul", "", output_us, "ulw", "", output_us,
   "uld", "", output_us, "uldb", "", output_us, "plain", "", plain,
   "plain", "", plain, "lquote", "\'", output, "rquote", "\'", output,
   "ldblquote", "\"", output, "rdblquote", "\"", output,
   "endash", " - ", output, "emdash", "--", output, "bullet", "*", output,
   "footnote", "", skip_dest, "footer", "", skip_dest, "header", "", skip_dest,
   "pic", "", skip_dest, "fonttbl", "", skip_dest, "stylesheet", "", skip_dest,
   "info", "", skip_dest, "colortbl", "", skip_dest, "atnid", "", skip_dest,
   "annotation", "", skip_dest, "field", "", skip_dest, "fldinst", "", skip_dest,
   "footerl", "", skip_dest, "headerl", "", skip_dest,
   "footerr", "", skip_dest, "headerr", "", skip_dest, "footerf", "", skip_dest, "headerf", "", skip_dest,
   "txe", "", skip_dest,  "ixe", "", skip_dest,  "bxe", "", skip_dest,  "rxe", "", skip_dest,
   "bkmkstart", "", skip_dest, "bkmkend", "", skip_dest, "nextfile", "", skip_dest,
   "template", "", skip_dest, "ansi", "", set_win, "pc", "", set_win,
   "tab", "|", output, "caps", "", set_caps, "v", "", set_inv, "fs", "", output_head,
   "qc", "", output_head,  "ql", "", output_head, "qj", "", output_head,
   "froman", "", font, "fswiss", "", font, "fnil", "", font, "fsymbol", "", font,
   "fdecor", "", font, "red", "", font, "blue", "", font, "green", "", font,
   };

static unsigned char winc[128] = {
'?','?','?','?','?','?','?','?',   '?','?','?','?','?','?','?','?',
'?','\'','\'','?','?','?','?','?', '?','?','?','?','?','?','?','?',
' ','≠','õ','ú','Ø','ù','|','\x15',   '"','C','¶','Æ','™','-','R','ƒ',
'\x16','Ò','˝','*','\'','Ê','\x14','˘', ',', '\'','ß','Ø','¨','´','?','®',
'A','A','A','A','é','è','í','Ä',  'E', 'E', 'E','ê','ç','°','å','ã',
'D','•', 'O', 'O', 'O', 'O', 'ô', 'x', 'ù', 'U', 'U', 'U', 'ö', 'Y', 'û', '·',
'Ö', '†', 'É', 'a', 'Ñ', 'Ü', 'ë', 'á', 'ä', 'Ç', 'à', 'â', 'ç', '°', 'å', 'ã',
'd', '§', 'ï', '¢', 'ì', 'o', 'î', 'ˆ', 'õ', 'ó', '£', 'ñ', 'Å', 'y', 'û', 'ò'
};


int hval( char c )
{
 if ( isdigit(c) )
    return( c - '0' );
 else if ( isxdigit(c) && isupper(c) )
    return( c - 'A'+10 );   
 else
    return( c - 'a'+10 );   
}

int read_hex2( FILE *stream )
{
 int i;
 char buf[10];

 buf[0] = fgetc(stream);
 if ( !isxdigit(buf[0]) ) {
    ungetc( buf[0], stream );
    return( 0 );
    }
 buf[1] = fgetc(stream);
 if ( !isxdigit(buf[1]) ) {
    ungetc( buf[1], stream );
    buf[1] = '\0';
    }
 buf[2] = '\0';
 return( (hval(buf[0])*16) + hval(buf[1]) );
}

int read_int( FILE *stream )
{
 int i = 0;
 char buf[15];

 do {
    buf[i] = fgetc(stream);
    if ( !isdigit(buf[i]) ) {
       ungetc( buf[i], stream );
       buf[i] = '\0';
       break;
       }
    i++;
    } while ( isdigit(buf[i-1]) && !feof( stream ) );
 buf[i] = '\0';
 return( atoi(buf) );
}


int read_name( FILE *stream, char *str )
{
 int i = 0;
 char buf[35];

 do {
    buf[i] = fgetc(stream);
    if ( !isalpha(buf[i]) ) {
       ungetc( buf[i], stream );
       buf[i] = '\0';
       break;
       }
    i++;
    } while ( isalpha(buf[i-1]) && !feof( stream ) );
 buf[i] = '\0';
 strcpy( str, buf );
 return( i );
}



static int push_state()
{
 if ( state_sp < STATE_CNT-1 ) {
    state_stack[++state_sp] = curr_state;
    return( 1 );
    }
 else
    return( 0 );
}

static int pop_state( FILE *out )
{
 STATE tos;

 if ( state_sp > 0 ) {
    tos = state_stack[state_sp--];
    if ( curr_state.map_inv ) {
       curr_state = tos;
       return( 1 );
       }
    if ( curr_state.bold && !tos.bold )
       fputc( '}', out );
    else if ( !curr_state.bold && tos.bold )
       fputc( '{', out );
    if ( curr_state.underscore && !tos.underscore )
       fputc( '>', out );
    else if ( !curr_state.underscore && tos.underscore )
       fputc( '<', out );
    if ( curr_state.head && !tos.head )
       fputc( ']', out );
    else if ( !curr_state.head && tos.head )
       fputc( '[', out );
    curr_state = tos;
    return( 1 );
    }
 else
    return( 0 );
}


static int get_code_word( FILE *stream, CODE_WORD *cwp )
{
 char buf[35];
 int v, c;

 c = fgetc( stream );
 switch( c ) {
       case '\\' :
       case '}'  :
       case '{'  :
	    return( c );
	    break;
       case '*'  :
	    fgetc( stream );
	    break;
       case '~'  :
	    return( ' ' );
	    break;
       case '\xa' :
       case '\xd' :
	    return( REOL );
	    break;
       case '_' :
	    return( '-' );
	    break;
       case '\'' :
	    v = read_hex2( stream );
	    return( v );
	    break;
       case '|' :
	    break;
       default :
	    ungetc( c, stream );
	    read_name( stream, buf );
	    cwp->val = 1;
	    strcpy( cwp->name, buf );
	    c = fgetc( stream );
	    if ( strchr( " -1234567890", c ) == NULL )
	       ungetc( c, stream );
	    else if ( c != ' ' ) {
	       ungetc( c, stream );
	       if ( c != ' ' )
		  cwp->val = read_int( stream );
	       c = fgetc( stream );
	       if ( c != ' ' )
		  ungetc( c, stream );
	       }
	    return( RCODE );
	    break;
       }
 return( 0 );
}


static int to_win( int c )
{
 char b[5];

 b[0] = (char)c;
 b[1] = 0;
 AnsiToOem(b, b);
 return( b[0] );
}

static int to_dos( int c )
{
 char b[5];

 b[0] = (char)c;
 b[1] = 0;
 OemToAnsi(b, b);
 return( b[0] );
}


static int set_win( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( !strcmpi( cwp->name, "pc" ) )
    map_win = 0;
 else if ( !strcmpi( cwp->name, "ansi" ) )
    map_win = 1;
 return( 0 );
}

static int rtf_read( FILE *stream, CODE_WORD *cwp )
{
 int c;

 c = fgetc( stream );
 switch( c ) {
       case EOF :
	    return( REOF );
	    break;
       case '\\' :
	    return( get_code_word( stream, cwp ) );
	    break;
       case '{' :
	    ++brace_state;
	    return( ROBRA );
	    break;
       case '}' :
	    --brace_state;
	    return( RCBRA );
	    break;
       default :
	    return( c );
	    break;
       }
}


static int skip_dest( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 int level = brace_state, c;
 CODE_WORD cw;

 curr_state.map_inv = 1;
 do {
    c = rtf_read( in, &cw );
    switch( c ) {
	  case RCBRA :
	       break;
	  case ROBRA :
	  case RCODE :
	  default :
	     continue;
	  }
    } while ( brace_state > level-1 );
 pop_state( out );
 curr_state.map_inv = 0;
 return( 1 );
}

static int set_caps( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( cwp->val ) {
    curr_state.map_caps = 1;
    }
 else {
    curr_state.map_caps = 0;
    }
 return( 0 );
}

static int set_inv( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( cwp->val ) {
    curr_state.map_inv = 1;
    }
 else {
    curr_state.map_inv = 0;
    }
 return( 0 );
}


static int output_bold( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( cwp->val ) {
    if ( !curr_state.bold ) {
       fputc( '{', out );
       curr_state.bold = 1;
       }
    }
 else {
    if ( curr_state.bold ) {
       fputc( '}', out );
       curr_state.bold = 0;
       }
    }
 return( 0 );
}


static int output_head( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( !strcmpi( cwp->name, "qc" ) ) {
    if ( !curr_state.head ) {
       fputc( '[', out );
       curr_state.head = 1;
       }
    }
 else if ( !strcmpi( cwp->name, "qj" ) || !strcmpi( cwp->name, "ql" ) ) {
    if ( curr_state.head ) {
       fputc( ']', out );
       curr_state.head = 0;
       }
    }
 return( 0 );
}


static int output_us( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( !strcmpi( cwp->name, "ulnone" ) && curr_state.underscore ) {
    fputc( '>', out );
    curr_state.underscore = 0;
    return( 0 );
    }
 if ( cwp->val ) {
    if ( !curr_state.underscore ) {
       fputc( '<', out );
       curr_state.underscore = 1;
       }
    }
 else {
    if ( curr_state.underscore ) {
       fputc( '>', out );
       curr_state.underscore = 0;
       }
    }
 return( 0 );
}

static int plain( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 if ( curr_state.bold ) {
    fputc( '}', out );
    curr_state.bold = 0;
    }
 if ( curr_state.underscore ) {
    fputc( '>', out );
    curr_state.underscore = 0;
    }
 if ( curr_state.head ) {
    fputc( ']', out );
    curr_state.head = 0;
    curr_state.size = 20;
    }

 return( 1 );
}

static int font( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 while (fgetc(in) != ';');
 return( 1 );
}


static int output( FILE *in, FILE *out, CODE_WORD *cwp, char *s )
{
 return( fputs( s, out ) );
}

typedef int ( *matchfunc)(const void *,const void *); 

static int do_code( CODE_WORD *cwp, FILE *in, FILE *out )
{
 CWDO *cwd;

 cwd = (CWDO *)lfind( cwp->name, cwd_array, (unsigned int *)&cwd_count, sizeof( CWDO ), (matchfunc)strcmpi );
 if ( cwd == NULL )
    return( 0 );
 return( cwd->df( in, out, cwp, cwd->out ) );
}

extern "C" {

int __declspec(dllexport) WINAPI _RTFTOAST( int argc, char *argv[] )
{
 FILE *instream, *outstream;
 CODE_WORD cw;
 int c, d, e, s;

 getConvertTextSettings(s,e,d,c);
 to_winf = c;
 if ( argc < 2 ) {
    alert_box( "RTFTOAST", "USAGE: RTFTOAST INFILE.EXT OUTFILE.EXT\n" );
    return( 1 );
    }
 if ( ( instream = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "RTFTOAST", "Can't Open %s For Reading!\n", argv[1] );
    return( 2 );
    }
 if ( ( outstream = fopen( argv[2], "wt" ) ) == NULL ) {
    alert_box( "RTFTOAST", "Can't Open %s For Writing!\n", argv[2] );
    fclose(instream);
    return( 3 );
    }
 if ( setvbuf( instream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( instream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( instream, NULL, _IOFBF, 1024 ) )
	  setvbuf( instream, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( outstream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( outstream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( outstream, NULL, _IOFBF, 1024 ) )
	  setvbuf( outstream, NULL, _IOFBF, 256 );
       }
    }
 dllYield();
 while ( ( c = rtf_read( instream, &cw ) ) != REOF ) {
       switch( c ) {
	     case ROBRA :
		  push_state();
		  break;
	     case RCBRA :
		  pop_state( outstream );
		  break;
	     case RCODE :
		  do_code( &cw, instream, outstream );
		  break;
	     case REOL :
		  fputc( '\n', outstream );
		  dllYield();
		  break;
	     case 9 :
		  fputc( '|', outstream );
		  break;
	     case 0x0a :
	     case 0x0d :
		  break;
	     case '^' :
		  fputs( "^", outstream );
		  break;
	     default :
		  if ( !curr_state.map_inv ) {
		     if ( c == ' ' && curr_state.hi_char ) {
			curr_state.hi_char = 0;
			fputs( "~ ", outstream );
			}
		     else if ( curr_state.map_caps && isascii( c ) && !islower( c ) )
			fputc( toupper( c ), outstream );
		     else if ( isascii( c ) )
			fputc( c, outstream );
		     else {
			if ( map_win && !to_winf  )
			   c = to_win( c );
			else if ( !map_win && to_winf )
			   c = to_dos( c );
			fputc( '~', outstream );
			fputc( c, outstream );
			curr_state.hi_char = 1;
			}
		     }
		     break;
	     }
       }
 fclose(instream);
 fclose(outstream);
 return( 0 );
}

}
