#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "acombbox.hpp"
#include "errors.fns"

/*
int zAstComboBoxStatic::addResStrings( int id )
{
 char *p;
 int e;
 ResStrBlock *px;

 px = new ResStrBlock(id);
 while ( ( p = px->get() ) != NULL )
       e = add( zString(p) );
 delete px;
 return( e );
}

int zAstComboBoxStatic::insertResStrings( int id, int nAt )
{
 ResStrBlock x(id);
 int e;
 char *p;

 while ( ( p = x.get() ) != NULL )
       e = insert( zString(p), (nAt != -1?nAt++:-1) );
 return( e );
}
*/
char *CAstComboBox::trim( char *buf )
{
 int l = strlen(buf);

 while ( l && buf[--l] == ' ' );
 buf[l+1]='\0';
 return( buf );
}


int CAstComboBox::loadList( IX_DESC *index, char *key )
{
 char buf[150];
 ENTRY id;
 short ret;
 char *ptr;
 
 ResetContent(); 
 if ( key == NULL ) {
	 first_key( index );
	 next_key(&id, index);
	}
 else {
	strcpy( id.key, key );
	locate_key(&id,index);
	}
 if ( key == NULL ) {
	 do {
		AddString( id.key );
		ret = next_key( &id, index );
	 } while ( ret == IX_OK );
	}
 else {
	 do {
       ptr = strrchr( id.key, '\1' );
	   if ( ptr == NULL )
		   break;
	   *ptr = '\0';
	   ptr++;
	   AddString( ptr );
	   ret = next_key(&id,index);
	 } while ( ret == IX_OK && !strcmpi(key,id.key) );
	}
 return( 1 );
}

/*
ResStrBlock::ResStrBlock(int id)
	: zUserResource(zResId(id),zString("ST_BLK"))
{
 char *p = (char *)(void *)*this;
 block = new char[strlen(p)+2];
 strcpy( block, p );
 ptrs[0] = block;
 char *pp = strchr( block, '\1' );
 int i = 1;
 while ( pp != NULL ) {
       *pp='\0';
       pp++;
       ptrs[i++] = pp;
       pp = strchr( pp, '\1' );
       }
 ptrs[i++] = pp;
 count = i-1;
 next = 0;
}


char *ResStrBlock::get()
{
 char *p;

 if ( next < count ) {
    p = ptrs[next];
    next++;
    }
 else p = NULL;
 return( p );
}

char *ResStrBlock::operator [] (int i)
{
 if ( i < count )
    return( ptrs[i] );
 else
    return( NULL );
}

*/