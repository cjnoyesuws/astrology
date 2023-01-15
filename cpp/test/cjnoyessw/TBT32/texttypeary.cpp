#include "stdafx.h"
#include <stdlib.h>
#include <search.h>
#include "TEXTTYPEARY.hpp"
#include "errors.fns"



int CATextType::Read( FILE *stream )
{
TCHAR dummy;

 return( fscanf( stream, "%d %s %s %d %74[^\n]%c", &_type, _dest, _symtypes, &_hasarray, _descrip, &dummy ) );
}

int __cdecl CATextTypeCmp( void const * p1, void const * p2 )
{
 CATextType *a1, *a2;

 a1 = (CATextType *)p1;
 a2 = (CATextType *)p2;
 int ret = stricmp( a1->dest(), a2->dest() );
 if ( ret != 0 )
	 return ( ret );
 if ( a1->type() == a2->type() )
	 return( 0 );
 else if ( a1->type()<a2->type() )
	 return( -1 );
 else
     return( 1 );
}


int CATextTypeAry::Load( char *name )
{
 char buf[120];
 CATextType *afp;
 FILE *stream;
 int i;

 if ( ( stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 for ( afp = _array, i = 0; i < _nAlloc && !feof( stream ); i++, afp++ ) {
	 if ( afp->Read( stream ) < 5 && ferror( stream ) && !feof(stream ) ) {
	do_error( name );
	break;
	}
     }
 if ( !strlen(afp->dest() ) )
    i--;
 _nElements = i;
 fclose( stream );
 qsort( _array, i, sizeof( CATextType ), CATextTypeCmp );
 return( 1 );
}

int CATextTypeAry::toListBox( CListBox *lb, int which, int ary )
{
 CATextType *pTT;
 int i, max;
 char buf[100];
 int ret, flag = 0;

 max = nElements();
 lb->ResetContent();
 for ( i = 0; i < max; i++ ) {
     pTT = &array()[i];
	 if ( (pTT->type() == which || which == -1) && (!ary || (ary && ary==pTT->hasArray()))  ) {
	sprintf( buf, "%s--%s ", pTT->dest(), pTT->descrip() );
	lb->AddString( CString(buf) );
	}
     }
 return( ret );
}

CATextType *CATextTypeAry::Find( CString &name, int tp, int lin )
{
 CATextType file;
 CATextType *pFile;

#ifdef _UNICODE
 memset(file.dest(),0,25);
 wcstombs(file.dest(), name, name.GetLength());
#else
 strcpy( file.dest(), name );
#endif
 file.type() = tp;
 if ( lin )
    pFile = (CATextType *) lfind( (void *)&file, array(), &_nElements,
	    sizeof(CATextType), CATextTypeCmp );
 else
    pFile = (CATextType *) bsearch( (void *)&file, array(), _nElements,
	    sizeof(CATextType), CATextTypeCmp );
 return( pFile );
}


int CATextTypeAry::toTextTypeCombo( CComboBox *pBox, int tp, int ary )
{
    pBox->ResetContent();
	char buf[100];
	for ( int i=0; i < _nElements; i++ ) {
      if ( _array[i].type() != tp || (ary && ary !=_array[i].hasArray()))
		  continue;
	  char *p=_array[i].dest();
      strcpy( buf, p );
	  strcat( buf, "-" );
	  strcat( buf, _array[i].descrip() );
	  pBox->AddString(CString(buf));
      }
   return( 0 );
}

char *CATextTypeAry::toTextType( CString &sel )
{
 char *p;
 static char buf[150];
#ifdef _UNICODE
 memset(buf,0,150);
 wcstombs(buf,sel,sel.GetLength());
#else
 strcpy( buf, sel );
#endif
 p = strchr(buf, '-' );
 if ( p != NULL )
    *p = '\0';
 return buf;
}
