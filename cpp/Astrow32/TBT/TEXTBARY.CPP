#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include <search.h>
#include "symbol.hpp"
#include "textbloc.hpp"
#include "errors.fns"

void zYield(int i = 1);
extern void setupBuf(int);

int CTextBlockCmp( const void * p1, const void * p2 )
{
 CTextBlock **t1, **t2;

 t1 =(CTextBlock **) p1;
 t2 =(CTextBlock **) p2;
 return( strcmp( (*t1)->IDstring(), (*t2)->IDstring() ) );
}



CTextBlock *CTextBlockAry::Find( CTextBlock *b )
{
 CTextBlock **ptb;
                        
 ptb = (CTextBlock **) lfind( &b, _array, (unsigned _far *)&_nElements,
	    sizeof(CTextBlock *), CTextBlockCmp );
 if ( ptb == NULL )
    return( NULL );
 else
    return( *ptb );
}
                       

CTextBlock *CTextBlockAry::Find( char *id, int n )
{
 CTextBlock tb;

 tb.SetID( id, n );
 return( Find( &tb ) );
}

CTextBlock *CTextBlockAry::Find( char *id1, char *id2 )
{
 CTextBlock tb;

 tb.SetID( id1, id2 );
 return( Find( &tb ) );
}

CTextBlock *CTextBlockAry::Find( char *id1, char *id2, char *id3 )
{
 CTextBlock tb;

 tb.SetID( id1, id2, id3 );
 return( Find( &tb ) );
}


int CTextBlockAry::Save( char *name )
{
 int i;
 FILE *stream;
 CTextBlock **p;
 char *dot;
 char buf[100];

 if ( ( stream = fopen( name, "wt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 setupBuf(1);
 for ( i = 0, p = _array; i < _nElements; i++, p++ ) {
     zYield();
     if ( _type == 1 )
	(*p)->WriteHeaderR( stream );
     else
	(*p)->WriteHeader( stream );
     (*p)->WriteText( stream );
     }
 fclose( stream );
 setupBuf(0);
 return( 1 );
}

int CTextBlockAry::Add( CTextBlock *b )
{
 CTextBlock **ptb;

 if ( _nElements >= _nAlloc-1 )
    return( 0 );
 ptb = _array;
 _bDirty = 1;
 ptb[_nElements++] = b;
 return( 1 );
}


int CTextBlockAry::Load( char *name, int start_size, int tp )
{
 CTextBlock *pblk, **par, **t;
 FILE *stream;
 int i, prev, e;
 char prid[60];

 _type = tp;
 _array = new CTextBlock *[start_size];
 if ( _array == NULL ) {
    do_mem_error( 0 );
    return( 0 );
    }
 memset( _array, 0, start_size * sizeof( CTextBlock *) );
 _nAlloc = start_size;
 if ( ( stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 setupBuf(1);
 for ( par = _array, i = 0; !feof( stream ); i++, par++ ) {
     if ( i >= _nAlloc-2 ) {
	_nAlloc += 100;
	t = new CTextBlock *[_nAlloc];
	if ( t == NULL ) {
	   do_mem_error( 0 );
	   setupBuf(0);
	   return( 0 );
	   }
	memset( t, 0, sizeof(CTextBlock *) *_nAlloc);
	memcpy( t, _array, sizeof(CTextBlock *) *i);
	delete _array;
	_array = t;
	}
     zYield();
     pblk = new CTextBlock;
     if ( pblk == NULL ) {
	do_mem_error( 0 );
	fclose( stream );
	setupBuf(0);
	return( 0 );
	}
     memset( pblk, 0, sizeof( CTextBlock ) );
     switch ( tp ) {
	case 1 :
	     if ( pblk->ReadHeader( stream, &prev, prid ) ) {
		do_error( name );
		break;
		}
	     break;
	case 2 :
	     if ( pblk->ReadHeader2( stream ) ) {
		do_error( name );
		break;
		}
	     break;
	case 3 :
	     if ( pblk->ReadHeader3( stream ) ) {
		do_error( name );
		break;
		}
	     break;
	default :
	     break;
	}
     if ( feof( stream ) )
	break;
     if ( pblk->ReadText( stream ) ) {
	do_error( name );
	break;
	}
     *par = pblk;
     if ( feof( stream ) )
	break;
     }
 _bDirty = 0;
 _nElements = i+1;
 fclose( stream );
 setupBuf(0);
 return( 1 );
}
