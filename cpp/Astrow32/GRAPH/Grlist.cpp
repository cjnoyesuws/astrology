#include "stdafx.h"
#include <stdlib.h>
#include "grlist.hpp"
#include "polar.hpp"
#include "asgflags.h"
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

int PlanetList::check(int degs, int var, int var2, int &rad)
{
 int i, f=0;

 for ( i = 0; i < count; i++ ) {
     if ( array[i].compare(degs,var, var2) ) {
	rad = array[i].getRad();
        f = 1;
	}
     }
 return(f);
}

int PlanetList::add(int degs, int rads )
{
 array[count].setDegs(degs);
 array[count].setRad(rads);
 count++;
 return( 1 );
}

int PlanetList::compWidth(int deg)
{
 int h, wd;

 wd = abs(icos(deg,width,0)) +1;
 h = abs(isin(deg,height,0)) +1;
 if ( wd > h )
    return( wd );
 else
    return( h );
}

int PlanetList::getVar(int degs, int &v2)
{
 short q, s, iv;

 q=degs/90;
 s=degs%90;
 s/=10;
 /* _asm {
    mov ax, degs
    cwd
    mov cx, 90
    idiv cx
    mov q, ax
    xchg ax, dx
    cwd
    mov cx, 10
    idiv cx
    mov s, ax
    }*/

 if ( q == 1 || q == 3 )
    s = 9 - s;
 iv = var[s];
 v2 = 360 - iv;
 return( iv );
}


int PlanetListClassical::checknAdd(int &degs)
{
 int i, nd, r, d, msh = 360 - shift;

 if ( !check(degs,shift,msh,r) ) {
    add(degs, init );
    return( init );
    }
 else if (r == init) {
    add(degs, r-width );
    return( r-width );
    }
 else {
    if ( degs < 8 || degs > 352 ) {
	for ( i = 2; i < 10; i+= 2 ) {
	    d = checkDeg(degs+i);
	    nd = checkDeg(degs-i);
	    if ( !check(d,shift,msh,r) ) {
	       add(d, init );
	       degs = d;
	       return( init );
	       }
	    else if ( !check(nd,shift,msh,r) ) {
	       add(nd, init );
	       degs = nd;
	       return( init );
	       }
	    }
       return( init-width );
       }
    else {
	for ( i = 2; i < 8; i+=2 ) {
	    if ( !check(degs+i,shift,msh,r) ) {
	       add(degs+i, init );
	       degs += i;
	       return( init );
	       }
	    else if ( !check(degs-i,shift,msh,r) ) {
	       add(degs-i, init );
	       degs -= i;
	       return( init );
	       }
	    }
	return( init - width );
	}
    }
}


int PlanetList::checknAdd(int &degs)
{
 int r, rm2 = -1, rp2 = -1, v, v2;
 int p2, m2;

 v = getVar(degs, v2);
 if ( !check(degs,v,v2,r) ) {
    add(degs, init-compWidth(degs) );
    return( init );
    }
 else {
    if ( r-width > min ) {
       add(degs, r-compWidth(degs) );
       return( r );
       }
    else {
       m2 = checkDeg(degs-2);
       check(m2, v, v2, rm2);
       p2 = checkDeg(degs+2);
       check(p2, v, v2, rp2);
       if (rm2 != -1 && rm2 < r && rm2 < rp2 ) {
	  add(m2, rm2-compWidth(degs) );
	  degs = m2;
	  return( rm2 );
	  }
       else if (rp2 != -1 && rp2 < r && rp2 < rm2 ) {
	  add(p2, rp2-compWidth(degs) );
	  degs = p2;
	  return( rp2 );
	  }
       else if (!failOverlap) {
	 add(degs, r- compWidth(degs));
	 return( r );
	 }
       else
	  return( -1 );
       }
    }
}
