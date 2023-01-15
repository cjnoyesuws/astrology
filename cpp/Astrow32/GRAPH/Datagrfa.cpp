#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "asgflags.h"
#include "datagrfa.hpp"
#include "polar.hpp"
  
inline int checkMin( int min )
{
 if ( min > (360 * 60) )
    min -=  (360 * 60);
 else if (min < 0 )
    min +=  (360 * 60);
 return( min );
}


int adj_degrees( int minutes, int asc_min )
{
 int degrees, m;

 minutes = abs(minutes); 
 m = ( asc_min - minutes );
 if ( m < 0 )
    m += (360 * 60);
 m += 30; /* round up */
 degrees = m / 60;
 return( degrees );
}

void PlanGrfa::doGrfdArray(int offset)
{
 Grfa *g = gr;
 short *a = array, i, m;
 for ( i = 0; i <= count; g++, a++, i++ ) {
     if ( *a != -1 ) {
 	   m = *a;
	   g->format( m, mode );
       }
    }
}



void PlanGrfa::doAdjs(int offset)
{
 int i, m;
 short *plp = array;

 for ( i = 0; i <= count; i++, plp++ )
     if ( *plp != -1 ) {
	if ( offset )
           m = checkMin(*plp+offset);
	else
           m = *plp;
	getAdj(i) = adj_degrees( m, asc_min );
        }
     else
	getAdj(i) = -1;
}

void PlanGrfa::doOffset()
{
 gr[0].offsetMin(array[0],house_offset, asc_min, mode);
 gr[MED_COELI].offsetMin(array[MED_COELI],house_offset, asc_min, mode);
 gr[IM_COELI].offsetMin(array[IM_COELI],house_offset, asc_min, mode);
}


int HouseGrfa::houseMidpoint( int h1, int h2 )
{
 unsigned int t;
 int temp;

 if ( h2 > h1 ) {
    temp = h1;
    h1 = h2;
    h2 = temp;
    }
 h1 -= h2;
 if ( h1 > (280 * 60) ) {
    h1 /= 2;
    t = h1 + h2;
    t += 10800;
    return( (int) (t % 21600) );
    }
 h1 /= 2;
 return( (h2 + h1) % 21600 );
}

void HouseGrfa::getMhps()
{
 int h;

 for ( h = 0; h < 12; h++ ) {
     if ( h == 11 )
	getMhp(11) = adj_degrees( houseMidpoint( array[11]
	  + house_offset, array[0] + house_offset ),
	  asc_min + house_offset );
     else
	getMhp(h) = adj_degrees( houseMidpoint( array[h]
	  + house_offset, array[h+1] + house_offset ),
	  asc_min + house_offset );
     }
}


void Grfa::format( int min, int mode )
{
 int d, m, s, r;
 static char signs[12][4] = { "ARI", "TAU", "GEM", "CAN", "LEO", "VIR",
			      "LIB", "SCO", "SAG", "CAP", "AQU", "PIS" };
  
  if ( min < 0 ) {
     min = abs(min);
     r = 1;
     }
  else
    r = 0;
    m = min % 60;
    d = (min / 60) % 30;
    s = min / 1800;
/* _asm {
    mov ax, min
    cwd
    mov cx, 60
    idiv cx
    mov m, dx
    cwd
    mov cx, 30
    idiv cx
    mov d, dx
    mov s, ax
    } */

 if ( mode & USE_GLYPH )
    sprintf( buf, "%-2.2d%c%-2.2d%c", d, 'w' + s, m, (r?'R':'\0') );
 else
    sprintf( buf, "%-2.2d%3s%-2.2d%c", d, signs[s], m, (r?'R':'\0') );
}


void Grfa::offsetMin( int min, int offset, int asc, int mode )
{
 format(min, mode );
 min = checkMin(min+offset);
 min = adj_degrees(min, asc);
 adj = min;
}

int PlanGrfa::doGrf( short *ar, int mo, int points, int force )
{
 if ( force || array != ar || mode != mo ) {
    setCount(points);
    setArray(ar);
    setMode(mo);
    doAdjs(house_offset);
    doGrfdArray(house_offset);
    }
 return( 0 );
}

int HouseGrfa::doGrf( short *ar, int mo, int force )
{
 if ( ar[0] == -1 ) {
    setCount(0);
    setArray(ar);
    setMode(mo);
    return( 0 );
    }
 if ( force || ar != array || mo != mode ) {
    PlanGrfa::doGrf( ar, mo, 12, force );
    getMhps();
    }
 return( 0 );
}


void GraphicDataGroup::doAspects( GR_ASPT *as, int n )
{
 GR_ASPT *a;
 int i;

 if ( pAspect != NULL )
    delete pAspect;
 pAspect = new GR_ASPT[n+1];
 memcpy( pAspect, as, n * sizeof( GR_ASPT ) );
 if ( pAspect == NULL ) {
    asp_cnt = 0;
    return;
    }
 asp_cnt = n;
 for ( i = 0, a = pAspect; i < n; i++, a++ ) {
     a->first = (short)adj_degrees( a->first, asc_min );
     a->second = (short)adj_degrees( a->second, asc_min );
     }
}

void GraphicDataGroup::doGrfs( short *pla, int pt, short *hsa, int mode, int am )
{
 int f;

 am = checkMin(offset+am);
 asc_min = am;
 if ( am != amin )
    f = 1;
 else
    f = 0;
 pl.setOffset(0);
 pl.setAscMin(asc_min);
 pl.doGrf( pla, mode, pt, f );
 pl.setOffset(offset);
 if ( offset )
    pl.doOffset();
 hs.setOffset(offset);
 hs.setAscMin(asc_min);
 hs.doGrf( hsa, mode, f );
 amin = am;
 }

int HouseGrfa::getHouse( int d, int &s )
{
 int h;

 if ( !getCount() )
    return( -1 );
 if ( !d ) {
    s = (array[0]/60)/30;
    return( 1 );
    }
 for ( h = 0; h < 12; h++ ) {
     if ( h != 11 && h != 0 && d <= getAdj(h) && d > getAdj(h+1) ) {
	    s = (array[h]/60)/30;
	    return h+1;
	    }
     else if ( h == 11 && d <= getAdj(h) ) {
	    s = (array[h]/60)/30;
	    return h+1;
	    }
	 else if ( h==0 && d >= getAdj(h+1) ) {
	    s = (array[h]/60)/30;
	    return h+1;
	    }
     }
 return( 1 );
}

int PtOpLess( CPoint &p1, CPoint &p2 )
{
 if ( p1.x < p2.x && p1.y < p2.y ) 
	return ( 1 );
 else
	return( 0 );

}

int PlanGrfa::find(int d, int r, int width, int height, int &ps, int &min)
{
 static int dgv[15] = {30,27,25,22,20,17,14,13,11,10,9,8,7,6,5};
 PolarCoord pc;
 CPoint at[5],cmp[5], pa;
 int fnd[5], cnt = 0, dd, hm = height/9;
 int i, rd, dg;

 ps = -1;
 min = -1;
 if ( mode & PLOT_CLASSIC ) {
    dd = 4;
    }
 else {
    dd = (r / width);
    if ( dd > 14 )
       dd = 14;
    dd = dgv[dd];
    }
 pa = pc.xy(d,r);
 for ( i = 0; i <= count; i++ ) {
     dg = getAdj(i);
     if ( abs(dg - d) <= dd || abs(dg - d) > 360-dd  ) {
	  rd = getRad(i);
	  CPoint p = pc.xy(dg,rd);
	  if ( mode & PLOT_CLASSIC ) {
         if ( !(dg <= 90 || dg >= 270) ) {
		    ps = abs(array[i]/(60*30));
		    min = array[i];
		if ( r >= rd && r <= rd+width )
		   return( i );
		}
	     else {
		ps = abs(array[i]/(60*30));
		min = array[i];
		if ( rd-width <= r && r <= rd )
		   return( i );
		}							   
	     }
	  else if ( !(mode & SHOW_PDEGS) ) {
	     CRect rx(p.x-(width/2)-1,p.y-(height+hm),
		p.x+(width/2),p.y-hm);
	if ( rx.PtInRect(pa) ) {  
	       at[cnt] = p;
	       fnd[cnt] = i;
	       cnt++;
	       }
	    }
	  else {
	    CRect rxa(p.x-(width/2)-1,p.y-((height/2)+hm),
		p.x+(width/2),p.y+(height/2)-hm);
	if ( rxa.PtInRect(pa) ) {
	       at[cnt] = p;
	       fnd[cnt] = i;
	       cnt++;
	       }
	    }
       }
      }
 ps = -1;
 min = -1;
 if ( !cnt )
    return( -1 );
 else if ( cnt == 1 ) {
    ps = abs(array[fnd[0]]/(60*30));
    min = array[fnd[0]];
    return( fnd[0] );
    }
 for ( i = 0; i < cnt; i++ )
     cmp[i] = CPoint(abs(at[i].x-pa.x),abs(at[i].y-pa.y));
 CPoint x(100,100);
 int j = -1;
 for ( i = 0;  i < cnt; i++ ) {
     if ( PtOpLess( cmp[i], x  ) ) {  
	j = i;
	x = cmp[i];
	}
     }
 if ( j == -1 )
    return( -1 );
 else {
    ps = abs(array[fnd[j]]/(60*30));
    min = array[fnd[j]];
    return( fnd[j] );
    }
 return( 0 );
}

