#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include "tdirec.hpp"
#include <stdlib.h>
#include <search.h>
#include <malloc.h>
#include "FILEARY.hpp"
#include "errors.fns"

CAsFileAry tbt_edit_files;

int CAsFile::Read( FILE *stream )
{
 char dummy;

 return( fscanf( stream, "%s %d %s %74[^\n]%c", _name, &_type, _symbols, _descrip, &dummy ) );
}

int _cdecl CAsFileCmp( void const * p1, void const * p2 )
{
 CAsFile *a1, *a2;

 a1 = (CAsFile *)p1;
 a2 = (CAsFile *)p2;
 return( strcmp( a1->name(), a2->name() ) );
}


int CAsFileAry::Load( char *name, int start_size )
{
 char buf[120];
 CAsFile *afp;
 FILE *stream;
 int i;

 _array = new CAsFile[start_size];
 if ( _array == NULL ) {
    do_mem_error( 0 );
    return( 0 );
    }
 _nAlloc = start_size;
 strcpy( buf, (char * ) theTbtDirectories.getMain() );
 if ( buf[strlen(buf)-1] != '\\' );
    strcat( buf, "\\" );
 strcat( buf, name );
 if ( ( stream = fopen( buf, "rt" ) ) == NULL ) {
    do_error( buf );
    return( 0 );
    }
 for ( afp = _array, i = 0; i < start_size && !feof( stream ); i++, afp++ ) {
     if ( afp->Read( stream ) < 4 && ferror( stream ) && !feof(stream ) ) {
	do_error( buf );
	break;
	}
     }
 if ( !strlen(afp->name() ) )
    i--;
 _nElements = i;
 fclose( stream );
 qsort( _array, i, sizeof( CAsFile ), CAsFileCmp );
 return( 1 );
}

int CAsFileAry::toListBox( zListBoxBase *lb, int which )
{
 CAsFile *pFile;
 int i, max;
 char buf[100];
 int ret, flag = 0;

 max = nElements();
 lb->clear();
 for ( i = 0; i < max; i++ ) {
     pFile = &array()[i];
     if ( pFile->type() == which || which == -1 ) {
	sprintf( buf, "%-8.8s  \t  %s ", pFile->name(), pFile->descrip() );
	lb->add( buf );
	}
     }
 return( ret );
}

CAsFile *CAsFileAry::Find( char *name, int lin )
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

