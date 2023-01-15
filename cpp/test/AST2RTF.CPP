#include <stdafx.h>
#include "strbuff.h"
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <ctype.h>


// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static TCHAR *rtf_soft_line = _T("\n");
static TCHAR *rtf_hard_line = _T("\\par\n");

static int rtf_foreign( Strbuff &stream, _TUCHAR c )
{
 TCHAR buf[10];
 TCHAR cbf[5];
#ifdef _UNICODE
 _stprintf( buf, _T("\\u%d "), c );
#else
 _stprintf( buf, _T("\\\'%2x"), c );
#endif
 (const TCHAR *) buf >> stream;
 return( 1 );
}

static int write_rtf_header(Strbuff &stream )
{
  _T("{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fswiss\\fprq2\\fTCHARset0 Arial;}") >> stream;
  _T("{\\f1\\froman\\fprq2\\fTCHARset0 Times New Roman;}}") >> stream;
  _T("{\\colortbl ;\\red0\\green0\\blue255;\\red255\\green0\\blue0;\\red0\\green255\\blue0;\\red255\\green0\\blue255;}") >> stream;
  _T("\\viewkind4\\uc1\\pard\\f1\\ql\\fs24") >> stream;
 return( 0 );
}



CString AstToRTF( CString &str )
{
 TCHAR buf[100], *p;
 int c, s, e, d;
 _TUCHAR ch;

 Strbuff out= Strbuff();
 Strbuff in= Strbuff(str);

 write_rtf_header( out );
 while ( !in.eof() ) {
       in._get(ch);
       switch( ch ) {
	     case _T('\\') :
		  _T("\\\\") >> out;
		  break;
         case _T('\r') :
          break;
		 case _T('\n') :
		  rtf_hard_line >> out;
		  //dllYield();
		  break;
	     case _T('<') :
		  _T("\\i1\\cf3") >> out;
		  break;
	     case _T('>') :
		  _T("\\i0\\cf0 ") >> out;
		  break;
	     case _T('{') :
		 _T("\\cf2\\b ") >> out;
		  break;
	     case _T('}') :
		 _T("\\b0\\cf0 ") >> out;
		  break;
        case _T('[') :
         _T("\\qc\\cf1\\b\\f0\\fs28") >> out;
        break;
        case _T(']') :
         _T("\\par\\ql\\f1\\cf0\\b0\\fs24") >> out;
        break;
	     case _T('~') :
		  in._get(ch);
		  if ( _istascii( ch ) && _tcschr( _T("\\{}"), ch ) != NULL ) {
		     out.put( _T('\\')) ;
		     out.put(ch);
		     }
		  else if ( _tcschr( _T("~^[]"), ch ) != NULL ) {
		     out.put(_T('~')) ;
		     out.put(ch);
		     }
		  else if ( isascii( ch ) )
		     out.put(ch);
		  else
		     rtf_foreign( out, ch );
		  break;
	     default :
		  out.put(ch);
		  break;
	     }
       }
  _T("\\par } }\n") >> out;
 return( out.getstr() );
}




