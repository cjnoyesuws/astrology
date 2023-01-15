// Strbuff.cpp: implementation of the Strbuff class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TBT32.h"
#include "Strbuff.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void Strbuff::put( TCHAR c )
{
 if ( len > 148 )
	 flush();
 buf[len++] = c;
 buf[len]=_T('\0');
}

_TUCHAR Strbuff::get()
{
  if ( index < len )
	  return( str[index++] );
  else
	  return( _T('\0'));
}


_TUCHAR Strbuff::_get( _TUCHAR &c )
{
 _TUCHAR ch;
 if ( index < len )
	 ch = str[index++];
 else
	 ch = _T('\0');
 c = ch;
 return c;
}

Strbuff & __cdecl operator >> ( TCHAR const *p, Strbuff &s ) 
{ 
 if (s.len) { 
	s.str+=s.buf; 
	s.len=0; 
	} 
  s.str += p; 
  return s; 
}
