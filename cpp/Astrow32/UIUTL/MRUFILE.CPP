#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "inifile.hpp"
#include "mrufile.hpp"
#include "astromn.h"
#include "menuutl.hpp"

FileMRUList AstMruList;

FileMRUList::~FileMRUList()
{
 for ( int i = 0; i < count; i++ ) {
     delete mru[i].getName();
     mru[i].set(0,0,0);
     }
}

FileMRUList::FileMRUList()
{
 int i;

 for ( i = 0; i < _MRUCOUNT_; i++ )
     mru[i].getId() = IDM_F1+i;
 lastid = -1;
 }


void FileMRUList::check(char *name, char tp)
{
 int i;

 if ( !count && !startPos ) {
    startPos = getMenuItemPos(pMenu,IDM_FEXIT, sub, 0)+1;
    InsertMenu(sub, startPos++, MF_BYPOSITION|MF_SEPARATOR, 0, 0 );
    }
 for ( i = 0; i < count; i++ ) {
     if ( mru[i].isEqual(name) ) {
	mru[i].getRef() = GetTickCount();
	sort();
	return;
	}
     }
 if ( count < _MRUCOUNT_ ) {
    i = count;
    mru[i].set(new zString(name),GetTickCount(),tp);
    InsertMenu(sub, startPos++, MF_BYPOSITION|MF_ENABLED|MF_STRING,
	  mru[i].getId(), name );
    pMenu->setCommand(obj, proc, mru[i].getId());
    pMenu->update();
    count++;
    sort();
    return;
    }
 delete mru[_MRUCOUNT_-1].getName();
 mru[_MRUCOUNT_-1].set(new zString(name),GetTickCount(),tp);
 if ( mru[_MRUCOUNT_-1].getId() == lastid )
    lastid = -1;
 int pos = getMenuItemPos(pMenu, mru[_MRUCOUNT_-1].getId(), sub, 0 );
 pMenu->deleteItem( mru[_MRUCOUNT_-1].getId() );
 InsertMenu(sub, pos, MF_BYPOSITION|MF_ENABLED|MF_STRING,
	  mru[_MRUCOUNT_-1].getId(), name );
 pMenu->update();
 lastid = mru[_MRUCOUNT_-1].getId();
 sort();
}


char *FileMRUList::get( int id, char &tp )
{
 int i;

 for ( i = 0; i < count; i++ ) {
     if ( id == mru[i].getId() ) {
	tp = mru[i].getType();
	if ( lastid != -1 )
	   pMenu->checkItem(lastid, 0 );
	pMenu->checkItem(id, 1 );
	pMenu->update();
	lastid = id;
	return( *mru[i].getName() );
	}
     }
 return( "" );
}

void FileMRUList::sort()
{
 MRUstruct temp;

 int i, j;

 for ( i = 0; i < 4; i++ ) {
     for ( j = i+1; j < 4; j++ ) {
	 if ( mru[i].getRef() < mru[j].getRef() ) {
	    temp = mru[j];
	    mru[j] = mru[i];
	    mru[i] = temp;
	    }
	 }
     }
}


int FileMRUList::saveToIni()
{
 char buf[15], buf2[5];
 char *sec = "MRUList";

 itoa( count, buf, 10 );
 WritePrivateProfileString( sec, "Count", buf, APPNAME );
 for ( int i = 0; i < count; i++ ) {
     sprintf( buf, "File%d", i );
     WritePrivateProfileString( sec, buf, (char *)*mru[i].getName(), APPNAME );
     sprintf( buf, "Type%d", i );
     sprintf( buf2, "%d", mru[i].getType() );
     WritePrivateProfileString( sec, buf, buf2, APPNAME );
     }
 return( 1 );
}

int FileMRUList::getFromIni()
{
 int t, i;
 char buf[15];
 char buf2[150];
 char *sec = "MRUList";

 if ( !count && !startPos ) {
    startPos = getMenuItemPos(pMenu,IDM_FEXIT, sub, 0)+1;
    }
 itoa( count, buf, 10 );
 count = GetPrivateProfileInt( sec, "Count", 0, APPNAME );
 if ( count )
    InsertMenu(sub, ++startPos, MF_BYPOSITION|MF_SEPARATOR, 0, 0 );
 else
    return( 1 );
 for ( i = 0; i < count; i++ ) {
     sprintf( buf, "File%d", i );
     GetPrivateProfileString( sec, buf, "", buf2, 149, APPNAME );
     sprintf( buf, "Type%d", i );
     t = GetPrivateProfileInt( sec, buf, 0, APPNAME );
     mru[i].set(new zString(buf2), GetTickCount(), t );
     InsertMenu(sub, ++startPos, MF_BYPOSITION|MF_ENABLED|MF_STRING,
	  mru[i].getId(), buf2 );
     pMenu->setCommand(obj, proc, mru[i].getId() );
     }
 pMenu->update();
 return( 1 );
}

