#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "symbol.hpp"
#include "textbloc.hpp"

void CTextBlockAry::Xref( CSymbolAry *s )
{
 int i, val;
 char sym1[55], sym2[50], sym3[40], old[55], old2[50];
 CSymbol *psym;
 CTextBlock **p;

 strcpy( old, "" );
 strcpy( old2, "" );
 switch( _type ) {
       case 1 :
	    for ( i = 0, p = _array; i < _nElements; i++, p++ ) {
		(*p)->GetIDParts( sym1, &val );
		if ( strcmp( sym1, old ) ) {
		   psym = s->Find( sym1 );
		   strcpy( old, sym1 );
		   if ( psym != NULL )
		      psym->referenced() = 1;
		   }
		}
	    break;
       case 2 :
	    for ( i = 0, p = _array; i < _nElements; i++, p++ ) {
		(*p)->GetIDParts( sym1, sym2 );
		if ( strcmp( sym1, old ) ) {
		   psym = s->Find( sym1, 1 );
		   strcpy( old, sym1 );
		   if ( psym != NULL )
		      psym->referenced() = 1;
		   }
		psym = s->Find( sym2, 2 );
		if ( psym != NULL )
		   psym->referenced() = 1;

		}
	    break;
       case 3 :
	    for ( i = 0, p = _array; i < _nElements; i++, p++ ) {
		(*p)->GetIDParts( sym1, sym2, sym3 );
		if ( strcmp( sym1, old ) ) {
		   psym = s->Find( sym1, 1 );
		   strcpy( old, sym1 );
		   if ( psym != NULL )
		      psym->referenced() = 1;
		   }
		if ( strcmp( sym2, old2 ) ) {
		   psym = s->Find( sym2, 2 );
		   strcpy( old2, sym2 );
		   if ( psym != NULL )
		      psym->referenced() = 1;
		   }
		psym = s->Find( sym3, 3 );
		   if ( psym != NULL )
		      psym->referenced() = 1;
		}
	    break;
       default :
	    break;
      }

}
