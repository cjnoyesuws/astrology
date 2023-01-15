#include "stdafx.h"
#include <stdlib.h>
#include <search.h>
#include "symbol.hpp"
#include "textbloc.hpp"
#include "errors.fns"

int charsize=1;


int _cdecl CTextBlockCmp( const void * p1, const void * p2 )
{
 CTextBlock **t1, **t2;

 t1 =(CTextBlock **) p1;
 t2 =(CTextBlock **) p2;
 return( strcmp( (*t1)->IDstring(), (*t2)->IDstring() ) );
}



CTextBlock *CTextBlockAry::Find( CTextBlock *b )
{
 CTextBlock **ptb;
                        
 ptb = (CTextBlock **) lfind( &b, _array, (unsigned *)&_nElements,
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
 CTextBlock *p;

 if ( ( stream = fopen( name, "wt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 setupBuf(1);
 for ( i = 0, p = _array; i < _nElements; i++, p++ ) {
     if ( _type == 1 )
	    p->WriteHeaderR( stream );
     else
	    p->WriteHeader( stream );
     p->WriteText( stream );
     }
 fclose( stream );
 setupBuf(0);
 return( 1 );
}



int CTextBlockAry::Load( char *name, int help )
{
 CTextBlock *pblk, *par, *t;
 FILE *stream;
 int i, prev, e;
 char prid[300], prch;
 TCHAR newname[100];

 if ( ( stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 setupBuf(1);
 e = fgetc(stream);
 if ( e != '#' && e != '@') {
	 while ( e != '#' && e != '@' ) {
		 e = fgetc(stream);
	     prch = e; 
	 }
	 e = fgetc(stream);
#ifdef _UNICODE
	 if ( e == 0 ) {
       ungetc(e,stream);
	   ungetc((int)prch,stream);
	   fclose(stream);
       mbstowcs(newname,name,strlen(name));
	   newname[strlen(name)]=_T('\0');
	   if ( ( stream = _tfopen( newname, _T("rb") ) ) == NULL ) {
          do_error( name );
          return( 0 );
          }
	   charsize = 2;
	   e = fgetc(stream);
      if ( e != '#' && e != '@' ) {
	     while ( e != '#' && e != '@' )
		     e = fgetc(stream);
		 ungetc(e,stream);
	    }
	 }
	 else
#endif
	    ungetc(e,stream);
 }
 else
    ungetc(e,stream);
 for ( par = _array, i = 0; !feof( stream ); i++, par++ ) {
     if ( i >= _nAlloc-2 ) {
	    _nAlloc += 100;
	    t = new CTextBlock [_nAlloc];
	    if ( t == NULL ) {
	       setupBuf(0);
	       return( 0 );
			}
	    memset( t, 0, sizeof(CTextBlock) * _nAlloc);
	    memcpy( t, _array, sizeof(CTextBlock) * i);
	    delete _array;
	    _array = t;
		}
	 if ( !help ) {
     switch ( _type ) {
		case 1 :
			 if ( par->ReadHeader( stream, &prev, prid ) ) {
				do_error( name );
				break;
				}
			break;
		case 2 :
			if ( par->ReadHeader2( stream ) ) {
				do_error( name );
				break;
				}
			break;
		case 3 :
			if ( par->ReadHeader3( stream ) ) {
				do_error( name );
				break;
				}
			break;
		default :
			break;
		}
	 }
     if ( feof( stream ) )
		break;
#ifndef _UNICODE 
     if ( par->ReadText( stream, help ) ) {
		do_error( name );
		break;
		}
#else
	 if ( charsize == 1 ) {
		if ( par->ReadTextMbs( stream, help ) ) {
		  do_error( name );
	 	  break;
		  }
	 }
	 else {
		if ( par->ReadText( stream, help ) ) {
		  do_error( name );
		  break;
		  }
	 }
#endif
     if ( feof( stream ) )
		break;
     }
 _bDirty = 0;
 _nElements = i+1;
 fclose( stream );
 setupBuf(0);
 return( 1 );
}
