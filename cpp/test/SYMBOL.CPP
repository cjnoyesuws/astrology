#include "stdafx.h"
#include <stdlib.h>
#include <search.h>
#include <ctype.h>
#include "symbol.hpp"
#include "errors.fns"

int CSymbol::Read( FILE *stream )
{
 char buf[50];
 int dummy;
 memset(buf,0,50);
 fscanf( stream, "%s %d %d %s %59[^\n]%c",
      buf, &_value, &_position, _symtype, _descrip, &dummy );
 if ( _position == 4 )
    _position = 2;
 _limit = 1;
 _referenced = 0;
 strcpy(_name,_strupr(buf));
 return( ferror( stream ) );
}


int CRSymbol::Read( FILE *stream )
{
 int val;
 char dummy, buf[50];
 memset(buf,0,50);
 fscanf( stream, "%s %d %d %s %59[^\n]%c", buf, &_value, &_limit,
      _symtype, _descrip, &dummy );
 _position = 1;
 _referenced = 0;
 strcpy(_name,_strupr(buf));
 return( ferror( stream ) );
}


int CSymbolCmp( const void * p1, const void *p2 )
{
 int v;
 CSymbol *s1, *s2;

 s1 = (CSymbol *)p1;
 s2 = (CSymbol *)p2;
 v = stricmp( s1->name(), s2->name() );
 return(v);
}

int CSymbolCmpX( const void * p1, const void *p2 )
{
 int v;
 CSymbol *s1, *s2;

 s1 = (CSymbol *)p1;
 s2 = (CSymbol *)p2;
 v = stricmp( s1->name(), s2->name() );
 if ( !v )
    v = s1->position() - s2->position();
 return(v);
}

CSymbol *CSymbolAry::Find( const wchar_t*str, int pos, int lin  )
{
 char buf[50];
 wcstombs(buf,str,wcslen(str));
 buf[wcslen(str)] = '\0';
 return( Find(buf,pos,lin));
}


CSymbol *CSymbolAry::Find( const char *str, int pos, int lin  )
{
 CSymbol sym;
 CSymbol *psym;

 strcpy( sym.name(), str );
 if ( pos == -1 ) {
    if ( lin )
       psym = (CSymbol *) lfind( &sym, _array, (unsigned *)&_nElements,
	       sizeof(CSymbol), CSymbolCmp );
    else
       psym = (CSymbol *) bsearch( &sym, _array, _nElements,
	       sizeof(CSymbol), CSymbolCmp );
    }
 else {
    sym.position() = pos;
    if ( lin )
       psym = (CSymbol *) lfind( &sym, _array, (unsigned *)&_nElements,
	       sizeof(CSymbol), CSymbolCmpX );
    else
       psym = (CSymbol *) bsearch( &sym, _array, _nElements,
	       sizeof(CSymbol), CSymbolCmpX );}
 return( psym );
}



int CSymbolAry::Load( char *name)
{
 char buf[100];
 CSymbol *psym;
 FILE *stream;
 int t = 1, ch;
 int i;
 
 if ( ( stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 for ( psym = _array, i = 0; i < _nAlloc && !feof( stream ); i++, psym++ ) {
     do {
	ch = fgetc( stream );
	ungetc( ch, stream );
	if ( ch == '#' || isspace(ch) || iscntrl(ch) ) {
	   fgets( buf, 99, stream );
	   }
	} while ( ch =='#' || ch == '\n' || ch == ' ' );
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



int CSymbolAry::toCombo( CComboBox *pbx, int pos, char *typ, int pos2 )
{
 char buf[150];
 CSymbol *psym; 
 int i, max;

 pbx->ResetContent();
 for ( i=0, psym=_array; i < _nElements; i++, psym++ ) {
    if ( (psym->position()==pos||(pos2!=-1 && psym->position()==pos2) ) && ( typ==NULL || strstr(typ,psym->symtype())!=NULL ) ) {
       sprintf(buf,"%s--%s", psym->name(),psym->descrip());
       pbx->AddString(CString(buf));
       }
    }
 
 return( 1 );
}


int CSymbolAry::toArrayCombo( CComboBox *pbx, CString &symtyp )
{
 char buf[150];
 CSymbol *psym; 
 int i, max;
 char stbuf[30];

#ifdef _UNICODE
 memset(stbuf,0,30);
 wcstombs(stbuf,symtyp,symtyp.GetLength());
#else
 strcpy(stbuf,symtyp);
#endif

 pbx->ResetContent();
 for ( i=0, psym=_array; i < _nElements; i++, psym++ ) {
	 if ( (psym->position()==1) &&  psym->limit()>1 && strstr(stbuf,psym->symtype()) != NULL) {
       sprintf(buf,"%s--%s", psym->name(),psym->descrip());
       pbx->AddString(CString(buf));
       }
    }
 
 return( 1 );
}


char *CSymbolAry::toSymName( CString &sel )
{
 char *p;
 static char buf[150];
#ifdef _UNICODE
 memset(buf,0,150);
 wcstombs(buf,(LPCTSTR)sel,sel.GetLength());
#else
 strcpy( buf, sel );
#endif 
 p = strchr(buf, '-' );
 if ( p != NULL )
    *p = '\0';
 return buf;
}
