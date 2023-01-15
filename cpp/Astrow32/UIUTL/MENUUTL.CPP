#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "basedcs.h"
#include "menuutl.hpp"

int enableMenuItems( zMenu *pm, int idf, int idl )
{
 int i, e;

 if ( !idl )
    idl = idf;
 for ( i = idf; i <= idl; i++ ) {
     e = pm->grayItem(i,0);
     e = pm->enableItem(i,1);
     }
 return( e );
}

int disableMenuItems( zMenu *pm, int idf, int idl )
{
 int i, e;

 if ( !idl )
    idl = idf;
 for ( i = idf; i <= idl; i++ ) {
     e = pm->enableItem(i,0);
     e = pm->grayItem(i,1);
     }
 return( e );
}

int enableMenuItems( zMenu *pm, int *ids )
{
 int *ip, e;

 for ( ip = ids; *ip; ip++ ) {
     e = pm->grayItem(*ip,0);
     e = pm->enableItem(*ip,1);
     }
 return( e );
}

int disableMenuItems( zMenu *pm, int *ids )
{
 int *ip, e;

 for ( ip = ids; *ip; ip++ ) {
     e = pm->enableItem(*ip,0);
     e = pm->grayItem(*ip,1);
     }
 return( e );
}

int getMenuItemPos( zMenu *pm, unsigned id, HMENU &m, int topPos )
{
 int i, count;
 HMENU mn;

 mn = GetSubMenu(pm->Id(), topPos);
 if ( !mn )
    mn = pm->Id();
 count = GetMenuItemCount(mn);
 m = mn;
 for ( i = 0; i < count; i++ ) {
     if ( GetMenuItemID(mn, i) == id )
	return( i );
     }
 return( -1 );
}

