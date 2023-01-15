#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <ctype.h>

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static int head;
static int hi_char, skip = 1;

static char *line;

char *check_cmd( char *cmd, char prv )
{
 if ( !strcmp( "<<", cmd ) )
    return( "~<" );
 else if ( !strcmp( "<;>", cmd ) )
    return( "~>" );
 else if ( !strcmp( "<+\">", cmd ) )
    return( "<" );
 else if ( !strcmp( "<-\">", cmd ) )
    return( ">" );
 else if ( !strcmp( "<+!>", cmd ) && !head )
    return( "{" );
 else if ( !strcmp( "<-!>", cmd ) && !head )
    return( "}" );
 else if ( !strcmp( "<+#>", cmd ) && !head )
    return( "<" );
 else if ( !strcmp( "<-#>", cmd ) && !head )
    return( ">" );
 else if ( !strncmp( "<:#", cmd, 3 ) && prv == '\n' )
    return( "\n" );
 else if ( !strcmp( "<:s>", cmd ) && prv == '\n' )
    return( "\n" );
 else if ( !strcmp( "<+C>", cmd ) && !skip )
    return( "\n" );
 else if ( !strcmp( "<+@>", cmd ) && !skip ) {
    if ( head ) {
       head = 0;
       return( "]" );
       }
    else
       return( "\n" );
    }
 else if ( !strcmp( "<+B>", cmd ) ) {
    head = 1;
    return( "[" );
    }
 return( NULL );
}

void skip_tag(FILE *stream)
{
 while ( fgetc(stream) != '@' );
}


void get_cmd(FILE *stream, char *buf )
{
 char c;

 *buf++ = '<';
 do {
    c = fgetc(stream);
    if ( c =='<' ) {
       *buf++ = '<';
       *buf++ = '\0';
       }
    else
       *buf++ = c;
    } while ( c != '>' );
 *buf++ = '\0';
}

extern "C" {

int __far __export __pascal _AMITOAST( int argc, char *argv[] )
{
 long ofs;
 char buf[100], *p;
 FILE *in, *out;
 int c, len, prv = '\n', nxt;

 if ( argc < 2 ) {
    alert_box( "AMITOAST", "AMITOAST INFILE OUTFILE\nConvert AMIPro Text to Text Source File Format" );
    return( -1 );
    }
 if ( argc < 3 ) {
    strcpy( buf, argv[1] );
    p = strchr( buf, '.' );
    if ( p == NULL )
       strcat( buf, ".AST" );
    else
       strcpy( p, ".AST" );
    }
 else
    strcpy( buf, argv[2] );
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "AMITOAST", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wt" ) ) == NULL ) {
    alert_box( "AMITOAST", "Can't Open %s for Writing!", buf );
    fclose( out );
    return( -1 );
    }
 line = new char[4000];
 if ( setvbuf( in, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( in, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( in, NULL, _IOFBF, 1024 ) )
	  setvbuf( in, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( out, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( out, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( out, NULL, _IOFBF, 1024 ) )
	  setvbuf( out, NULL, _IOFBF, 256 );
       }
    }
 fgets(line, 199, in );
 if ( strncmp( line, "[ver]", 5 ) ) {
    alert_box( "AMITOAST", "%s is not an AMIPRO file!\n", buf );
    fclose( in );
    fclose( out );
    delete line;
    return( -1 );
    }
 do {
    fgets(line, 199, in );
    } while ( strncmp( line, "[edoc]", 6 ) );
 
 while ( ( c = fgetc( in ) ) != EOF ) {
       switch ( c ) {
	      case '$' :
	       fputc( '$', out );
	       fputc( fgetc(in), out );
	       break;
	      case 9 :
		   fputc( '|', out );
		   break;
	      case '@' :
		   if ( prv == '\n' ) {
		      skip_tag(in);
		      fputs( "\n", out );
		      }
		   break;
	      case '\n' :
		   dllYield();
		   if ( head ) {
		      fputs( "]\n", out );
		      head = 0;
		      prv = 0;
		      }
		   nxt = fgetc(in);
		   if ( nxt == '>' ) {
		      fclose( in );
		      fclose( out );
		      delete line;
		      return(0);
		      }
		   else
		      ungetc( nxt, in );
		   break;
	      case '<' :
		   get_cmd(in,line);
		   p = check_cmd(line, prv);
		   if ( p != NULL )
		      fputs( p, out );
		   break;
	      case '{' :
	      case '}' :
		   fputc( '~', out );
		   fputc( c, out );
		   break;
	      case ' ' :
		   skip = 0;
		   if ( hi_char )
		      fputc( '~', out );
		   fputc( ' ', out );
		   hi_char = 0;
		   break;
	      default :
		   skip = 0;
		   if ( hi_char )
		      hi_char = 0;
		   if ( c > 0x7f ) {
		      fputc( '~', out );
		      hi_char = 1;
		      }
		   fputc( c, out );
		   break;
	     }
       prv = c;
       }
 fclose( in );
 fclose( out );
 delete line;
 return(0);
}
}