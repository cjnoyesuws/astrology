// StrTransform.cpp: implementation of the CStrTransform class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef TBT32
#include "tbt32.h"
#else
#include "astrow.h"
#endif
#include "StrTransform.h"
#include "errors.fns"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CString &CStrTransform::ToReplacements(CString &str)
{
   for ( int i = 0; i < count; i++ ) {
      CString sym=Symbols.GetAt(i);
      CString rep=Replacements.GetAt(i);
      str.Replace((LPCTSTR)sym,(LPCTSTR)rep);
      }
   return(str);
}

CString &CStrTransform::ToSymbols(CString &str)
{
   for ( int i = 0; i < count; i++ ) {
      CString sym=Symbols.GetAt(i);
      CString rep=Replacements.GetAt(i);
      str.Replace((LPCTSTR)rep,(LPCTSTR)sym);
      }
   return(str);
}   
   
int CStrTransform::Load( TCHAR *name)
{
 TCHAR str[25], rep[25];
 int num, dummy;
 FILE *stream;

 stream=_tfopen(name,_T("rt"));
 if ( stream == NULL ) {
    do_error( name );
    return( -1 );
    }
 do {
#ifdef _UNICODE
	_ftscanf(stream,_T("%d|%l[^\n]%c"), &num, str, &dummy );
    _ftscanf(stream,_T("%l[^\n]%c"),rep, &dummy );
#else
	 _ftscanf(stream,_T("%d|%[^\n]%c"), &num, str, &dummy );
    _ftscanf(stream,_T("%[^\n]%c"),rep, &dummy );
#endif
    Symbols.SetAtGrow(num-1,str);
    Replacements.SetAtGrow(num-1,rep);
    } while ( !feof( stream ) );
 count=num;
 fclose(stream);
 return( 0 );
}