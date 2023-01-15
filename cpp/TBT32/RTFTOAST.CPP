#include <stdafx.h>
#include "Strbuff.h"
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <ctype.h>
#include "rtf.h"

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static int get_code_word( Strbuff &stream, CODE_WORD *cwp );
static int set_win( Strbuff &in, Strbuff &OUT, CODE_WORD *cwp, TCHAR *s );
static int rtf_read( Strbuff &stream, CODE_WORD *cwp );
static int skip_dest( Strbuff &in, Strbuff &OUT, CODE_WORD *cwp, TCHAR *s );
static int set_caps( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int set_inv( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int output_bold( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int output_head( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int output_us( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int plain( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int font( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int output( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
static int do_code( CODE_WORD *cwp, Strbuff &in, Strbuff &out );
static int pard( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );

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
static STATE curr_state = { 0, 0, 0, 0, 0, 0, 24 };


static CWDO cwd_array[] = { _T("par"), _T("\r\n"), output, _T("b"), _T(""), output_bold,
   _T("i"), _T(""), output_us, _T("ul"), _T(""), output_us, _T("ulw"), _T(""), output_us,
   _T("uld"), _T(""), output_us, _T("uldb"), _T(""), output_us, _T("plain"), _T(""), plain,
   _T("plain"), _T(""), plain, _T("lquote"), _T("\'"), output, _T("rquote"), _T("\'"), output,
   _T("ldblquote"), _T("\""), output, _T("rdblquote"), _T("\""), output,
   _T("endash"), _T(" - "), output, _T("emdash"), _T("--"), output, _T("bullet"), _T("*"), output,
   _T("footnote"), _T(""), skip_dest, _T("footer"), _T(""), skip_dest, _T("header"), _T(""), skip_dest,
   _T("pic"), _T(""), skip_dest, _T("fonttbl"), _T(""), skip_dest, _T("stylesheet"), _T(""), skip_dest,
   _T("info"), _T(""), skip_dest, _T("colortbl"), _T(""), skip_dest, _T("atnid"), _T(""), skip_dest,
   _T("annotation"), _T(""), skip_dest, _T("field"), _T(""), skip_dest, _T("fldinst"), _T(""), skip_dest,
   _T("footerl"), _T(""), skip_dest, _T("headerl"), _T(""), skip_dest, _T("pard"), _T(""), pard,
   _T("footerr"), _T(""), skip_dest, _T("headerr"), _T(""), skip_dest, _T("footerf"), _T(""), skip_dest, _T("headerf"), _T(""), skip_dest,
   _T("txe"), _T(""), skip_dest, _T("ixe"), _T(""), skip_dest, _T("bxe"), _T(""), skip_dest, _T("rxe"), _T(""), skip_dest,
   _T("bkmkstart"), _T(""), skip_dest, _T("bkmkend"), _T(""), skip_dest, _T("nextfile"), _T(""), skip_dest,
   _T("template"), _T(""), skip_dest, _T("ansi"), _T(""), set_win, _T("pc"), _T(""), set_win,
   _T("tab"), _T("|"), output, _T("caps"), _T(""), set_caps, _T("v"), _T(""), set_inv, _T("fs"), _T(""), output_head,
   _T("qc"), _T(""), output_head, _T("ql"), _T(""), output_head, _T("qj"), _T(""), output_head,
   _T("froman"), _T(""), font, _T("fswiss"), _T(""), font, _T("fnil"), _T(""), font, _T("fsymbol"), _T(""), font,
   _T("fdecor"), _T(""), font, _T("red"), _T(""), font, _T("blue"), _T(""), font, _T("green"), _T(""), font, _T("tab"), _T("     "), output };


static unsigned char winc[128] = {
'?','?','?','?','?','?','?','?',   '?','?','?','?','?','?','?','?',
'?','\'','\'','?','?','?','?','?', '?','?','?','?','?','?','?','?',
' ','­','›','œ','¯','','|','\x15',   '"','C','¦','®','ª','-','R','Ä',
'\x16','ñ','ý','*','\'','æ','\x14','ù', ',', '\'','§','¯','¬','«','?','¨',
'A','A','A','A','Ž','','’','€',  'E', 'E', 'E','','','¡','Œ','‹',
'D','¥', 'O', 'O', 'O', 'O', '™', 'x', '', 'U', 'U', 'U', 'š', 'Y', 'ž', 'á',
'…', ' ', 'ƒ', 'a', '„', '†', '‘', '‡', 'Š', '‚', 'ˆ', '‰', '', '¡', 'Œ', '‹',
'd', '¤', '•', '¢', '“', 'o', '”', 'ö', '›', '—', '£', '–', '', 'y', 'ž', '˜'
};


static int pop_state( Strbuff &out )
{
 STATE tos;

 if ( state_sp > 0 ) {
    tos = state_stack[state_sp--];
    if ( curr_state.map_inv ) {
       curr_state = tos;
       return( 1 );
       }
    if ( curr_state.bold && !tos.bold )
       out.put( _T('}')) ;
    else if ( !curr_state.bold && tos.bold )
       out.put( _T('{')) ;
    if ( curr_state.underscore && !tos.underscore )
       out.put( _T('>')) ;
    else if ( !curr_state.underscore && tos.underscore )
       out.put( _T('<')) ;
    if ( curr_state.head && !tos.head )
       out.put( _T(']')  );
    else if ( !curr_state.head && tos.head )
       out.put( _T('[')  );
    curr_state = tos;
    return( 1 );
    }
 else
    return( 0 );
}


int hval( TCHAR c )
{
 if ( _istdigit(c) )
    return( c - _T('0')  );
 else if ( _istxdigit(c) && _istupper(c) )
    return( c - _T('A')+10 );   
 else
    return( c - _T('a')+10 );   
}


int read_hex2( Strbuff &stream )
{
 int i;
 TCHAR buf[10];

 buf[0] = stream.get();
 if ( !_istxdigit(buf[0]) ) {
    stream.putback( buf[0] );
    return( 0 );
    }
 buf[1] = stream.get();
 if ( !_istxdigit(buf[1]) ) {
    stream.putback( buf[1] );
    buf[1] = _T('\0');
    }
 buf[2] = _T('\0');
 return( (hval(buf[0])*16) + hval(buf[1]) );
}

int read_int( Strbuff &stream )
{
 int i = 0;
 TCHAR buf[15];

 do {
    buf[i] = stream.get();
    if ( !_istdigit(buf[i]) ) {
       stream.putback( buf[i] );
       buf[i] = _T('\0');
       break;
       }
    i++;
    } while ( _istdigit(buf[i-1]) && !stream.eof() );
 buf[i] = _T('\0');
 return( _tstoi(buf) );
}


int read_name( Strbuff &stream, TCHAR *str )
{
 int i = 0;
 TCHAR buf[35];

 do {
    buf[i] = stream.get();
    if ( !_istalpha(buf[i]) ) {
       stream.putback( buf[i]);
       buf[i] = _T('\0');
       break;
       }
    i++;
    } while ( _istalpha(buf[i-1]) && !stream.eof() );
 buf[i] = _T('\0');
 _tcscpy( str, buf );
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


static int pard( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
    if ( curr_state.head )
       out.puts( _T("]\r\n")  );
    else if ( curr_state.bold )
       out.put( _T('}')  );
    if ( curr_state.underscore )
       out.put( _T('>')  );
    return( 1 );
 
}


static int get_code_word( Strbuff &stream, CODE_WORD *cwp )
{
 TCHAR buf[35];
 int v, c;

 c = stream.get();
 switch( c ) {
       case _T('\\')  :
       case _T('}')   :
       case _T('{')   :
	    return( c );
	    break;
       case _T('*')   :
	    stream.get();
	    break;
#ifndef _UNICODE
       case _T('~')   :
	    return( _T(' ')  );
	    break;
#else
	   case _T('u')  :
	    v = read_int(stream);
		return( v );
	   break;
#endif
       case _T('\xa')  :
       case _T('\xd')  :
	    return( REOL );
	    break;
       case _T('_')  :
	    return( _T('-')  );
	    break;
       case _T('\'')  :
	    v = read_hex2( stream );
	    return( v );
	    break;
       case _T('|')  :
	    break;
       default :
	    stream.putback( c );
	    read_name( stream, buf );
	    cwp->val = 1;
	    _tcscpy( cwp->name, buf );
	    c = stream.get();
	    if ( _tcschr( _T(" -1234567890"), c ) == NULL )
	       stream.putback( c );
	    else if ( c != _T(' ') ) {
	       stream.putback( c );
	       if ( c != _T(' ') )
		  cwp->val = read_int( stream );
	       c = stream.get();
	       if ( c != _T(' ') )
		  stream.putback( c );
	       }
	    return( RCODE );
	    break;
       }
 return( 0 );
}

static int set_win( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( !_tcsicmp( cwp->name, _T("pc" ) ) )
    map_win = 0;
 else if ( !_tcsicmp( cwp->name, _T("ansi" ) ) )
    map_win = 1;
 return( 0 );
}

static int rtf_read( Strbuff &stream, CODE_WORD *cwp )
{
 _TUCHAR ch;

 stream._get( ch );
 if (stream.eof() )
    ch=_T('\0');
 switch( ch ) {
	   case _T('\0'):
	    return( REOF );
	    break;
       case _T('\\')  :
	    return( get_code_word( stream, cwp ) );
	    break;
       case _T('{')  :
	    ++brace_state;
	    return( ROBRA );
	    break;
       case _T('}')  :
	    --brace_state;
	    return( RCBRA );
	    break;
       default :
	    return( (int)ch );
	    break;
       }
}


static int skip_dest( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
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

static int set_caps( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( cwp->val ) {
    curr_state.map_caps = 1;
    }
 else {
    curr_state.map_caps = 0;
    }
 return( 0 );
}

static int set_inv( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( cwp->val ) {
    curr_state.map_inv = 1;
    }
 else {
    curr_state.map_inv = 0;
    }
 return( 0 );
}


static int output_bold( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( cwp->val ) {
    if ( !curr_state.bold && !curr_state.head ) {
       out.put( _T('{')) ;
       curr_state.bold = 1;
       }
    }
 else {
    if ( curr_state.bold && !curr_state.head) {
       out.put( _T('}')) ;
       curr_state.bold = 0;
       }
    }
 return( 0 );
}


static int output_head( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( !_tcsicmp( cwp->name, _T("qc") ) ) {
    if ( !curr_state.head ) {
       out.put( _T('[')) ;
       curr_state.head = 1;
       curr_state.size=14;
       }
    }
 else if ( !_tcsicmp( cwp->name, _T("qj") ) || !_tcsicmp( cwp->name, _T("ql") ) ) {
    if ( curr_state.head ) {
       out.put(_T(']')) ;
       curr_state.head = 0;
       curr_state.size = 12;
       }
    }
 if ( !_tcsicmp( cwp->name, _T("fs") ) ) {
	if ( curr_state.head && cwp->val == 24 ) {
	   out.put(_T(']')) ;
       curr_state.head = 0;
       curr_state.size = 12;
       }
	else if ( !curr_state.head && cwp->val == 28 ) {
       out.put( _T('[')) ;
       curr_state.head = 1;
       curr_state.size=14;
       }
    }
 
 return( 0 );
}


static int output_us( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( !_tcsicmp( cwp->name, _T("ulnone") ) && curr_state.underscore ) {
    out.put( _T('>')) ;
    curr_state.underscore = 0;
    return( 0 );
    }
 if ( cwp->val ) {
    if ( !curr_state.underscore ) {
       out.put( _T('<')) ;
       curr_state.underscore = 1;
       }
    }
 else {
    if ( curr_state.underscore ) {
       out.put( _T('>')) ;
       curr_state.underscore = 0;
       }
    }
 return( 0 );
}

static int plain( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( curr_state.bold ) {
    out.put( _T('}')) ;
    curr_state.bold = 0;
    }
 if ( curr_state.underscore ) {
    out.put( _T('>')  );
    curr_state.underscore = 0;
    }
 if ( curr_state.head ) {
    out.put( _T(']')  );
    curr_state.head = 0;
    curr_state.size = 12;
    }

 return( 1 );
}

static int font( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 while (in.get() != _T(';')) ;
 return( 1 );
}


static int output( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s )
{
 if ( !(!_tcsicmp(cwp->name,_T("par")) && curr_state.head==1) )
	out.puts( s );
 else if (_tcsicmp(cwp->name,_T("par")))
    out.puts(s);
 return( 1 );
}

typedef int ( *matchfunc)(const void *,const void *); 

static int do_code( CODE_WORD *cwp, Strbuff &in, Strbuff &out )
{
 CWDO *cwd;

 cwd = (CWDO *)lfind( cwp->name, cwd_array, (unsigned int *)&cwd_count, sizeof( CWDO ), (matchfunc)strcmpi );
 if ( cwd == NULL )
    return( 0 );
 return( cwd->df( in, out, cwp, cwd->out ) );
}


CString RTFToAst( CString &str )
{
 CODE_WORD cw;
 int c;
 Strbuff outstream = Strbuff();
 Strbuff instream = Strbuff(str);

 while ( ( c = rtf_read( instream, &cw ) ) != REOF ) {
       switch( c ) {
		 case _T('<'):
		 case _T('>'):
	     case _T('['):
		 case _T(']'):
             outstream.put(_T('~')) ;
			 outstream.put(c);
			 break;
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
		  outstream.put( _T('\n')) ;
		  break;
	     case 9 :
		  outstream.put( _T('|')  );
		  break;
	     case 0x0a :
	     case 0x0d :
		  break;
#ifdef _UNICODE
	     case _T('^')  :
		  outstream.put( _T('^')) ;
		  break;
#endif
	     default :
		  if ( !curr_state.map_inv ) {
		     if ( c == _T(' ')  && curr_state.hi_char ) {
			curr_state.hi_char = 0;
			outstream.puts( _T("~ ") );
			}
		     else if ( curr_state.map_caps && _istascii( c ) && !_istlower( c ) )
			outstream.put( _totupper( c ) );
		     else if ( _istascii( c ) )
			outstream.put( c);
		     else {
#ifndef _UNICODE 
			outstream.put( _T('~')) ;
			outstream.put( c);
			curr_state.hi_char = 1;
#else
		    outstream.put( c); 
#endif
			 }
		     }
		     break;
	     }
       }
 return( outstream.getstr() );
}


