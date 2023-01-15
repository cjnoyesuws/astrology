#include "stdafx.h"
#include <stdlib.h>
#include <search.h>
#include "FILEARY.hpp"
#include "errors.fns"
#include <afxcoll.h>


int CAsFile::Read( FILE *stream )
{
 char dummy;

 return( fscanf( stream, "%s %d %s %s %74[^\n]%c", _name, &_type, _symbols, _dest, _descrip, &dummy ) );
}

int __cdecl CAsFileCmp( void const * p1, void const * p2 )
{
 CAsFile *a1, *a2;

 a1 = (CAsFile *)p1;
 a2 = (CAsFile *)p2;
 return( strcmpi( a1->name(), a2->name() ) );
}


int CAsFileAry::Load( char *name )
{
 char buf[120];
 CAsFile *afp;
 FILE *stream;
 int i;

 if ( ( stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 for ( afp = _array, i = 0; i < _nAlloc && !feof( stream ); i++, afp++ ) {
     if ( afp->Read( stream ) < 4 && ferror( stream ) && !feof(stream ) ) {
	do_error( name );
	break;
	}
     }
 if ( !strlen(afp->name() ) )
    i--;
 _nElements = i+1;
 fclose( stream );
 qsort( _array, i+1, sizeof( CAsFile ), CAsFileCmp );
 return( 1 );
}

int CAsFileAry::toListBox( CListBox *lb, int which )
{
 CAsFile *pFile;
 int i, max;
 char buf[100];
 int ret=0, flag = 0;

 max = nElements();
 lb->ResetContent();
 for ( i = 0; i < max; i++ ) {
     pFile = &array()[i];
     if ( pFile->type() == which || which == -1 ) {
	sprintf( buf, "%s--%s ", pFile->name(), pFile->descrip() );
	lb->AddString( CString( buf) );
	}
     }
 return( ret );
}

CAsFile *CAsFileAry::Find( const char *name, int lin )
{
 CAsFile file;
 CAsFile *pFile;
                                 
 strcpy( file.name(), name );
 if ( lin )
    pFile = (CAsFile *) lfind( (void *)&file, array(), &nElements(),
	    sizeof(CAsFile), CAsFileCmp );
 else
    pFile = (CAsFile *) bsearch( (void *)&file, array(), nElements(),
	    sizeof(CAsFile), CAsFileCmp );
 return( pFile );
}


TCHAR *CAsFileAry::toFileName( const TCHAR *sel )
{
 TCHAR *p;
 static TCHAR buf[150];

 _tcscpy( buf, sel );
 p = _tcschr(buf, _T('-') );
 if ( p != NULL )
    *p = _T('\0');
 return buf;
}

#ifdef _UNICODE
char *CAsFileAry::toFileName( CString &sel )
{
 wchar_t *p = toFileName((LPCTSTR)sel);
 static char buf[150];

 wcstombs( buf, p, wcslen(p) );
 buf[wcslen(p)] = '\0';
 return buf;
}
#endif

int CAsFileAry::toTextTypeCombo( CComboBox *pBox )
{
   for ( int i=0; i < _nElements; i++ ) {
      char *p=_array[i].dest();
      if ( pBox->FindString(0,CString(p))==CB_ERR )
         pBox->AddString(CString(p));
      }
   return( 0 );
}

int CAsFileAry::toStringArray( CString &dir, CStringArray &ar, int which )
{
 int cnt = 0, max;
 CString str= dir;
 if ( str.Right(1) != "\\")
	 str += "\\";

 max = nElements();
 for ( int i = 0; i < max; i++ ) {
     CAsFile *pFile = &array()[i];
     if ( pFile->type() == which || which == -1 ) {
	 	CString file = str + pFile->name();
		if ( !_waccess(file,0) ) {
			ar.Add(pFile->name());
			cnt++;
		  }
	    }
     }
 return( cnt ); 
}

int CAsFileAry::getCount(int t)
{
 int cnt=0;
 for ( int i=0; i < _nElements; i++ ) {
     if (_array[i].type()==t )
		 cnt++;
      }
   return( cnt );
}