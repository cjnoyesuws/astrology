#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include <search.h>
#include <ctype.h>
#include "symbol.hpp"
#include "errors.fns"

int CSymbol::Read( FILE *stream )
{
 int dummy;

 fscanf( stream, "%s %d %d %59[^\n]%c",
      _name, &_value, &_position, _descrip, &dummy );
 if ( _position == 4 )
    _position = 2;
 _limit = 1;
 _referenced = 0;
 return( ferror( stream ) );
}


int CRSymbol::Read( FILE *stream )
{
 int val;
 char dummy;

 fscanf( stream, "%s %d %d %59[^\n]%c", _name, &_value, &_limit,
      _descrip, &dummy );
 _position = 1;
 _referenced = 0;
 return( ferror( stream ) );
}

int CSymbol::Write( FILE *stream )
{
 int dummy;

 fprintf( stream, "%40s %2d %2d %s\n",
      _name, _value, _position, _descrip );
 return( 1 );
}

int CRSymbol::Write( FILE *stream )
{
 int val;
 char dummy;

 fprintf( stream, "%40s %2d %2d %s\n", _name, _value, _limit,
      _descrip );
 return( 1 );
}


int CSymbolCmp( const void * p1, const void *p2 )
{
 int v;
 CSymbol *s1, *s2;

 s1 = (CSymbol *)p1;
 s2 = (CSymbol *)p2;
 v = strcmp( s1->name(), s2->name() );
 return(v);
}

int CSymbolCmpX( const void * p1, const void *p2 )
{
 int v;
 CSymbol *s1, *s2;

 s1 = (CSymbol *)p1;
 s2 = (CSymbol *)p2;
 v = strcmp( s1->name(), s2->name() );
 if ( !v )
    v = s1->position() - s2->position();
 return(v);
}


CSymbol *CSymbolAry::Find( char *str, int pos, int lin  )
{
 CSymbol sym;
 CSymbol *psym;

 strcpy( sym.name(), str );
 if ( pos == -1 ) {
    if ( lin )
       psym = (CSymbol *) lfind( &sym, _array, (unsigned _far *)&_nElements,
	       sizeof(CSymbol), CSymbolCmp );
    else
       psym = (CSymbol *) bsearch( &sym, _array, _nElements,
	       sizeof(CSymbol), CSymbolCmp );
    }
 else {
    sym.position() = pos;
    if ( lin )
       psym = (CSymbol *) lfind( &sym, _array, (unsigned _far *)&_nElements,
	       sizeof(CSymbol), CSymbolCmpX );
    else
       psym = (CSymbol *) bsearch( &sym, _array, _nElements,
	       sizeof(CSymbol), CSymbolCmpX );}
 return( psym );
}



int CSymbolAry::Load( char *name, int start_size )
{
 char buf[100];
 CSymbol *psym;
 FILE *stream;
 int t = 1, ch;
 int i;
 
 if ( strstr( name, "REPORT" ) != NULL )
    t = 0;
 type = t;
 if ( !t )
    _array = new CRSymbol[start_size];
 else
    _array = new CSymbol[start_size];
 if ( _array == NULL ) {
    do_mem_error( 0 );
    return( 0 );
    }
 _nAlloc = start_size;
 if ( ( stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    delete []_array;
    _array = NULL;
    return( 0 );
    }
 for ( psym = _array, i = 0; i < start_size && !feof( stream ); i++, psym++ ) {
     do {
	ch = fgetc( stream );
	ungetc( ch, stream );
	if ( ch == '#' || isspace(ch) || iscntrl(ch) ) {
	   fgets( buf, 99, stream );
	   }
	} while ( ch == '#' || ch == '\n' || ch == ' ' );
	if ( psym->Read( stream ) ) {
	   do_error( name );
	   break;
	   }
     }
 _nElements = i;
 fclose( stream );
 qsort( _array, i, sizeof( CSymbol ), CSymbolCmpX );
 return( 1 );
}

int CSymbolAry::Save( char *name )
{
 char buf[100];
 CSymbol *psym;
 FILE *stream;
 int t = 1, ch;
 int i;

 if ( ( stream = fopen( name, "wt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 for ( psym = _array, i = 0; i < _nElements; i++, psym++ ) {
     if ( type )
	psym->Write( stream );
     else
	(CRSymbol*)psym->Write( stream );
     }
 _nElements = i;
 fclose( stream );
 qsort( _array, i, sizeof( CSymbol ), CSymbolCmp );
 return( 1 );
}



int CSymbolAry::toCombo( zComboBoxBase *bs, int which, int incl )
{
 char buf[150];
 CSymbol *psym; 
 int i, max;
 char **b, **p, *pt;
 int x, y, e, ret, flag = 0;

 if ( _array == NULL || !max )
    return( 0 );
 max = _nElements;
 b = new char *[max+2];
 if ( b == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 if ( incl > 0 ) {
    for ( i = 0, p = b; i < max; i++ ) {
	psym = &_array[i];
	if ( psym->position() == which ) {
	   sprintf( buf, "%c%s--%s", (psym->referenced()?' ':'*'),
	      psym->name(), psym->descrip() );
	   pt = new char[strlen(buf)+1];
	   strcpy( pt, buf );
	   *p++ = pt;
	   }
	}                                      
    }
 else if ( !incl ) {
    for ( i = 0, p = b; i < max; i++ ) {
	psym = &_array[i];
	if ( psym->position() == which && psym->referenced() ) {
	   sprintf( buf, "%s--%s", psym->name(), psym->descrip() );
	   pt = new char[strlen(buf)+1];
	   strcpy( pt, buf );
	   *p++ = pt;
	   }
	}
    }
 else if ( incl < 0 ) {
    for ( i = 0, p = b; i < max; i++ ) {
	psym = &_array[i];
	sprintf( buf, "%s--%s", psym->name(), psym->descrip() );
	   pt = new char[strlen(buf)+1];
	   strcpy( pt, buf );
	   *p++ = pt;
	   }
	}
 *p++ = NULL;
 bs->reset();
 bs->addCharStrings( b );
 for ( p = b; *p; p++ )
     delete *p;
 delete b;
 return( 1 );
}


char *toSymName( char *sel )
{
 char *p;
 static char buf[150];

 if ( *sel == ' ' || *sel == '*' )
    sel++;
 strcpy( buf, sel );
 p = strchr(buf, '-' );
 if ( p != NULL )
    *p = '\0';
 return buf;
}
