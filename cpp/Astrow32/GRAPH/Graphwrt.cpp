#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "output.fns"
#include "fptr.h"
#include <math.h>
#include "utlduad.h"
#include "aspect.h"
#include "graphdat.hpp"
#include "graphwrt.hpp"
#include "charcons.h"

#ifdef DELUXE
GR_DATALST *GraphWriter::setupDataList(AS_INF *inf, int cnt, int mode, int &n)
{
 int i;
 AS_INF *ptr;
 GR_DATALST *pd, *p;

 pd = new GR_DATALST[cnt+1];
 if ( pd == NULL ) {
    n = 0;
    return NULL;
    }
 for ( i = 0, p = pd, ptr = inf; i < cnt; ++ptr, ++i, p++ ) {
     p->min = ptr->minutes_total;
     if ( ( mode & HOUSES ) )
	p->house = ptr->house;
     else
	p->house = -1;
     if ( ( mode & MISCELL ) )
	p->decan = ptr->misc_code & 3;
     else
	p->decan = -1;
     }
 n = cnt;
 return( pd );
}
#endif

void GraphWriter::planets( AS_INF *inf, int c, int w, short *array, int start )
{
 AS_INF *ptr;
 short *p,i;

 if ( array )
    p = array;
 else {
    if ( w )
       p = data->natal_minutes;
    else
       p = data->other_minutes;
    }
 for ( i = 0; i < start; i++ )
     *p++ = -1;
 for ( ptr = inf; i <= c; ++i, ++ptr ) {
     if ( ptr->retrograde && ptr->minutes_total != 1 )
	*p++ = -ptr->minutes_total;
     else if  ( ptr->retrograde && ptr->minutes_total == 1 )
	*p++ = -2;
     else
	*p++ = ptr->minutes_total;
     }
 for ( ; i < data->maxpt; i++ )
     *p++ = -1;
}


int GraphWriter::countAspects(AS_INF *inf, int cnt)
{
 AS_INF *ptr;
 ASPEC *ap;
 int nas = 0, i, j;

 for ( i = 0, ptr = inf; i < cnt; ++ptr, ++i ) {
     ap = ptr->aspectr;
     for ( j = 0; j < ptr->no_aspects; ++j, ++ap ) {
	 if ( ap->aspect <= SQUARED || ap->aspect == QUINCUNX
	       || ap->aspect == SEMISQUARE )
	    ++nas;
	 }
     }
 return( nas );
}

#ifdef DELUXE
int GraphWriter::countGridAspects(AS_INF *inf, int cnt)
{
 AS_INF *ptr;
 ASPEC *ap;
 int nas = 0, i, j;

 for ( i = 0, ptr = inf; i < cnt; ++ptr, ++i ) {
     ap = ptr->aspectr;
     for ( j = 0; j < ptr->no_aspects; ++j, ++ap ) {
	 if ( ap->aspect >= 0 || ap->aspect <= QUINCUNX )
	    ++nas;
	 }
     }
 return( nas );
}
#endif

int GraphWriter::setupAspects(AS_INF *inf, int cnt)
{
 int n, i, j;
 AS_INF *ptr;
 ASPEC *ap;
 GR_ASPT *asp, *ax;

 n = countAspects(inf,cnt);
 asp = new GR_ASPT[n+1];
 if ( asp == NULL ) {
    n = 0;
    return( NULL );
    }
    for ( i = 0, ptr = inf, ax = asp; i < cnt; ++ptr, ++i ) {
	ap = ptr->aspectr;
	for ( j = 0; j < ptr->no_aspects; ++j, ++ap ) {
	    if ( ap->aspect <= SQUARED || ap->aspect == QUINCUNX ||
		 ap->aspect == SEMISQUARE ) {
	       if ( ap->aspect == SQUARED || ap->aspect == OPPOSITION ||
			 ap->aspect == SEMISQUARE ) {
		  ax->first = -ptr->minutes_total;
		  if ( !ax->first )
		     ax->first = -1;
		  }
	       else 
		  ax->first = ptr->minutes_total;
		  ax->second = (inf+ap->planet)->minutes_total;
		  ax->aspect = ap->aspect;
		  ++ax;
		  
	    }
	}
    }
 setAspects( n, asp );
 return( n );
}

#ifdef DELUXE
GR_ASPT *GraphWriter::setupGridAspects(AS_INF *inf, int cnt, int &n, int start)
{
 AS_INF *ptr;
 ASPEC *ap;
 GR_ASPT *asp, *ax;
 int i, j;

 n = countGridAspects(inf,cnt);
 asp = new GR_ASPT[n+1];
 for ( i = 0, ptr = inf, ax = asp; i < cnt; ++ptr, ++i ) {
	ap = ptr->aspectr;
	for ( j = 0; j < ptr->no_aspects; ++j, ++ap ) {
	    if ( ap->aspect >= 0 || ap->aspect <= QUINCUNX ) {
	       ax->first = i+start;
	       ax->second = ap->planet;
	       ax->aspect = ap->aspect;
	       ++ax;
	       }
	    }
	}
 return( asp );
}
#endif

GraphWriter::GraphWriter( BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr) 
{
 char buf[10], buf2[20];
 char lbuf[54];

 data->version = XP_WIN_GRAPH;
 nfp.x.fpt = *ptr;
 if ( mode & NOBIRTHTIM )
       data->birth_time_known_1 = 0;
    else
       data->birth_time_known_1 = 1;
 if ( mode & VERT_EAST && !(mode & NOBIRTHTIM) )
    data->maxpt = EAST_POINT;
 else if ( !(mode & NOBIRTHTIM) )
    data->maxpt = PART_FORTU;
 else
    data->maxpt = SOUTH_NODE;
 data->type = type;
 if ( mode & SIDEREAL )
    tropHouseProc( "Sidereal", housmod[house_proc] );
 else
    tropHouseProc( "Tropical", housmod[house_proc] );
 nameDateTime1( birth->name, make_date( &birth->birth_data.birth_date ),
    make_time( &birth->birth_data.birth_time, birth->am_pm ) );
 if ( mode & HOUSES  )
    houseCusps( &house_cusps[1], &alt_cusps[1] );
 else {
    data->natal_house_cusps[0] = -1;
    data->other_house_cusps[0] = -1;
    }
 planets( inf, data->maxpt );
 if ( type == NATAL_GRAPH_FILE || type == NUMERIC_GRAPH_FILE ) {
    sprintf( buf, "%3d%c%2d", birth->birth_data.longitude.degrees,
       birth->birth_data.longitude.dir, birth->birth_data.longitude.minutes );
    sprintf( buf2, "%2d%c%2d", birth->birth_data.latitude.degrees,
       birth->birth_data.latitude.dir, birth->birth_data.latitude.minutes );
    strcpy( lbuf, birth->location );
    strcat( lbuf, ", " );
    strncat( lbuf, birth->state, 49 );
    lbuf[50] = '\0';
    nameDateTime2(lbuf,buf,buf2);
    }
 if ( type == NATAL_GRAPH_FILE || type == NUMERIC_GRAPH_FILE ) {
    if ( mode & ASPECTS )
       setupAspects(inf, data->maxpt);
#ifdef DELUXE
    int cnt;
    GR_DATALST *pd = setupDataList(inf, data->maxpt, mode, cnt );
    setDataLst( cnt, pd );
#endif
    }
#ifdef DELUXE
 if ( mode & ASPECTS && type != PROGRESS_GRAPH_FILE ) {
    int cnt;
    GR_ASPT *pt =setupGridAspects(inf, data->maxpt, cnt );
    if ( pt != NULL )
       setGridAspects( cnt, pt );
    }
#endif
}

#ifndef _QDTRAN_
#ifdef DELUXE
ProgGraphWriter::ProgGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type,
      int mode, int house_proc, XPFILE_DB *ptr, PROGR_DATA *p,
	  AS_INF *alt, AS_INF *prg ) :
	   GraphWriter(birth, inf, type, mode, house_proc, ptr )
{
 int cnt;

 planets( alt, data->maxpt, 0 );
 if ( mode & ASPECTS ) {
    GR_ASPT *pt =setupGridAspects(alt, data->maxpt, cnt );
    if ( pt != NULL )
       setGridAspects( cnt, pt );
    pt =setupGridAspects(prg, data->maxpt, cnt );
    if ( pt != NULL )
       setOtherGridAspects( cnt, pt );
    }
 GR_DATALST *pd = setupDataList(alt, data->maxpt, mode, cnt );
 if ( pd != NULL )
    setOtherDataLst( cnt, pd );
 sprintf( data->date2, "%-2.2d/%-2.2d/%-2.2d", p->offset.year,
			   p->offset.month, p->offset.day );
}

SolarGraphWriter::SolarGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type,
      int mode, int house_proc, XPFILE_DB *ptr, DIREC_DATA *p,
	  AS_INF *alt ) :
	   GraphWriter(birth, inf, type, mode, house_proc, ptr )
{
 int cnt;

 planets( alt, data->maxpt, 0 );
 if ( mode & ASPECTS ) {
    GR_ASPT *pt =setupGridAspects(alt, data->maxpt, cnt );
    if ( pt != NULL )
       setGridAspects( cnt, pt );
    }
 GR_DATALST *pd = setupDataList(alt, data->maxpt, mode, cnt );
 if ( pd != NULL )
    setOtherDataLst( cnt, pd );
 sprintf( data->date2, "%-2.2d/%-2.2d/%-2.2d", p->direction.month,
			   p->direction.day, p->direction.year );
}

HarmonicGraphWriter::HarmonicGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type,
      int mode, int house_proc, XPFILE_DB *ptr, int harmonic,
	  AS_INF *alt ) :
	   GraphWriter(birth, inf, type, mode, house_proc, ptr )
{
 int cnt;

 planets( alt, data->maxpt, 0 );
 if ( mode & ASPECTS ) {
    GR_ASPT *pt =setupGridAspects(alt, data->maxpt, cnt );
    if ( pt != NULL )
       setGridAspects( cnt, pt );
    }
 GR_DATALST *pd = setupDataList(alt, data->maxpt, mode, cnt );
 if ( pd != NULL )
    setOtherDataLst( cnt, pd );
 sprintf( data->date2, "%d", harmonic );
}

#endif

CompGraphWriter::CompGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type,
      int mode, int house_proc, XPFILE_DB *ptr, AS_INF *alt, BIRTH_DB *other, int mode2) :
	   GraphWriter(birth, inf, type, mode, house_proc, ptr )
{
 if ( mode2 & NOBIRTHTIM )
    data->birth_time_known_1 = 0;
 else
    data->birth_time_known_1 = 1;
 nameDateTime2( other->name, make_date( &other->birth_data.birth_date ),
    make_time( &other->birth_data.birth_time, other->am_pm ) );
 if ( type != COMPOS_GRAPH_FILE ) {
    int cnt;
    planets( alt, data->maxpt, 0 );
#ifdef DELUXE
    if ( mode & ASPECTS ) {
       GR_ASPT *pt =setupGridAspects(alt, data->maxpt, cnt );
       if ( pt != NULL )
	  setOtherGridAspects( cnt, pt );
       }
    GR_DATALST *pd = setupDataList(alt, data->maxpt, mode, cnt );
    if ( pd != NULL )
       setOtherDataLst( cnt, pd );
#endif
    }
}
#endif

TransGraphWriter::TransGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type,
    int mode, int house_proc, XPFILE_DB *ptr, BIRTH_DB *trans, TRANS_DATA *tp,
	 AS_INF **alt, DATES *dates_ptr) : GraphWriter(birth, inf,
		 type, mode, house_proc, ptr )
{
 int i;
 GR_CHART *p;
 DATES *dp;
 AS_INF **ip;


 nameDateTime2( trans->name, make_date( &trans->birth_data.birth_date ),
    make_time( &trans->birth_data.birth_time, trans->am_pm ) );
 data->num_charts = tp->num_transits;
 GR_CHART *pc = new GR_CHART[tp->num_transits+1];
 this->setCharts(tp->num_transits, pc);
 strcpy( pc->date, make_date( dates_ptr++ ) );
 pc->maxpt = SOUTH_NODE;
 planets( *alt, SOUTH_NODE, 0, pc->chart_minutes, 1 );
#ifdef DELUXE
 if ( mode & ASPECTS ) {
    int cnt;
    GR_ASPT *pt =setupGridAspects(*alt, SOUTH_NODE, cnt, 1 );
    if ( pt != NULL )
       pc->setAspects( cnt, pt );
    }
#endif
 pc++;
 alt++;
 for ( i = 1, p = pc, dp = dates_ptr, ip = alt; i < tp->num_transits;
						i++, p++, dp++, ip++ ) {
     strcpy( p->date, make_date( dp ) );
     p->maxpt = tp->end_planet;
     planets( *ip, tp->end_planet, 0,
	   p->chart_minutes, tp->start_planet );
#ifdef DELUXE
     if ( mode & ASPECTS ) {
	int cnt;
	GR_ASPT *pt =setupGridAspects(*ip, tp->end_planet-tp->start_planet, cnt, tp->start_planet );
	if ( pt != NULL )
	   p->setAspects( cnt, pt );
	}
#endif
     }
}

#ifndef _QDTRAN_
#ifdef PRO
CompTransGraphWriter::CompTransGraphWriter(BIRTH_DB *birth, AS_INF *inf,
    int type, int mode, int house_proc, XPFILE_DB *ptr, BIRTH_DB *trans,
	 TRANS_DATA *tp, AS_INF **alt, DATES *dates_ptr, BIRTH_DB *other ) :
	     TransGraphWriter(birth, inf, type, mode, house_proc, ptr,
		  trans, tp, alt, dates_ptr)
{
 nameDateTime2( other->name, make_date( &other->birth_data.birth_date ),
    make_time( &other->birth_data.birth_time, other->am_pm) );
}
#endif
#endif
