#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "errors.fns"
#include "graphdat.hpp"
#include "paths.hpp"
#include "aspect.h"


short GR_ASPT::isHard()
{
 static short ih[] = { 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 };

 if ( aspect == -1 )
    return( 1 );
 return( ih[aspect] );
}

short GR_CHART::read(FILE *stream)
{
 fread( &date, sizeof(GR_CHART)-4,1,stream );
 if ( aspect_count == -1 )
    aspect_count = 0;
 if ( aspect_count > 0 ) {
    pAspects = new GR_ASPT[aspect_count];
    if ( pAspects != NULL )
       fread( pAspects, sizeof(GR_ASPT),aspect_count,stream );
    else
       aspect_count = 0;
    }
 return( 1 );
}

short GR_CHART::write(FILE *stream)
{
 fwrite( &date, sizeof(GR_CHART)-4,1,stream );
 if ( aspect_count > 0 ) {
    if ( pAspects != NULL )
       fwrite( pAspects, sizeof(GR_ASPT),aspect_count,stream );
    }
 return( 1 );
}


unsigned short GraphData::getVersion( FILE *stream, char *name )
{
 unsigned short i;
 fread( &i, 2, 1, stream );
 if ( (int)(i & 0xff) == 65 ) {
    reread(name,stream,&nfp);
    fread( &i, 2, 1, stream );
	}
 fseek( stream, -2L, SEEK_CUR );
 return( i );
}

short GraphData::cvtTo( O_GR_DAT *pOld )
{
 data->maxpt=pOld->maxpt;
 memcpy( &data->type, &pOld->type, pOld->natal_minutes-&pOld->type );
 memcpy( data->natal_minutes, pOld->natal_minutes, (data->maxpt+1) * 2 );
 memcpy( data->other_minutes, pOld->other_minutes, (data->maxpt+1) * 2 );
 memcpy( data->natal_house_cusps, pOld->natal_house_cusps, 24 );
 memcpy( data->other_house_cusps, pOld->other_house_cusps, 24 );
 data->num_aspects = pOld->num_aspects;
 data->num_charts = pOld->num_charts;
 data->num_text = 0;
 data->num_data = 0;
 data->num_other = 0;
 data->num_grid_aspects = 0;
 data->num_other_grid_aspects = 0;
 strcpy( data->trop_side, "" );
 strcpy( data->house_proc, "" );
 OemToAnsi(pOld->name1, data->name1 );
 OemToAnsi(pOld->date1, data->date1 );
 OemToAnsi(pOld->time1, data->time1 );
 OemToAnsi(pOld->name2, data->name2 );
 OemToAnsi(pOld->date2, data->date2 );
 OemToAnsi(pOld->time2, data->time2 );
 data->birth_time_known_1 = pOld->birth_time_known_1;
 data->birth_time_known_2 = pOld->birth_time_known_2;
 return( 1 );
}

short GraphData::readOld2( O_GR_DAT *pOld, FILE *stream )
{
 fudge = NEW_GRA_DIFF;
 if ( fread( pOld, sizeof( O_GR_DAT), 1, stream ) )
    cvtTo(pOld);
 else {
    return( 0 );
    }
 return( 1 );
}

#define GRW (sizeof(O_GR_DAT)-(data->date1-((char*)data))-2)

short GraphData::readOld1( O_GR_DAT *pOld, FILE *stream )
{
 fudge = NEW_GRA_DIFF;
 if ( fread( (char *) pOld, sizeof( short ), 3, stream ) != 3 )
    return( 0 );
 pOld->type += 3;
 if ( fread( pOld->name1, 1, O_NAME_WIDTH+1, stream ) != O_NAME_WIDTH+1 )
    return( 0 );
 if ( fread( pOld->name2, 1, O_NAME_WIDTH+1, stream ) != O_NAME_WIDTH+1 )
    return( 0 );
 if ( fread( pOld->date1, 1, GRW, stream ) != GRW )
    return( 0 );
 pOld->num_charts = 0;
 cvtTo(pOld);
 return( 1 );
}

short GraphData::read( char *name, short dir )
{
 char buf[200];
 GR_TEXT **ptx, **pt;
 O_GR_DAT *pOld;
 O_GR_ASPT oas;
 GR_ASPT *pAsp;
 FILE *stream;
 unsigned short v;
 short i;
 
 fudge = NEW_GRA_DIFF;
 strcpy( buf, set_path(name, dir) );
 if ( ( stream = freadx_fptr( buf, &nfp, 1 ) ) == NULL ) {
    do_error( buf );
    return( 0 );
    }
 if ( feof(stream) || ferror(stream) ) {
	 alert_box("Error", "No File to Read");
	 return ( 0 );
 }
 if ( isafptr2_file( &nfp ) || isafptr_file( &nfp ) )  {
    pOld = new O_GR_DAT;
    if ( pOld == NULL ) {
       do_mem_error( 0 );
       fclose( stream );
       return( 0 );
       }
    if ( isafptr_file( &nfp ) ) {
       if ( !readOld1( pOld, stream ) ) {
	  do_error( buf );
	  fclose( stream );
	  delete pOld;
	  return( 0 );
	  }
       fclose( stream );
       delete pOld;
       return( 1 );
       }
    else if ( isafptr2_file( &nfp ) ) {
       if ( !readOld2( pOld, stream ) ) {
	  do_error( buf );
	  fclose( stream );
	  delete pOld;
	  return( 0 );
	  }
       delete pOld;
       }
    }
 else {
    v = getVersion(stream,buf);
    if ( v == WIN_GRAPH ) {
       if ( !fread( data, sizeof( GR_DAT)-4, 1, stream ) ) {
	  do_error( buf );
	  fclose( stream );
	  return( 0 );
	  }
       data->num_grid_aspects = 0;
       data->num_other_grid_aspects = 0;
       }
    else if ( v == NEW_WIN_GRAPH ||  v == XP_WIN_GRAPH ) {
       if ( !fread( data, sizeof( GR_DAT), 1, stream ) ) {
	  do_error( buf );
	  fclose( stream );
	  return( 0 );
	  }
       }
    }
 if ( data->num_aspects ) {
    pAspect = new GR_ASPT[data->num_aspects];
    aspect_count = data->num_aspects;
    if ( pAspect == NULL ) {
       do_mem_error(0);
       fclose( stream );
       return( 0 );
       }
    if (isafptr2_file(&nfp)) {
       has_aspect_glyphs = 0;
       short j;
       for ( j = 0, pAsp=pAspect; j < aspect_count; j++, pAsp++ ) {
	       fread( &oas, 4, 1, stream );
	       if ( oas.first < 0 )
	          pAsp->set(-oas.first, oas.second, -1);
	       else
		  pAsp->set(oas.first, oas.second, 1);
	       }
       }
    else {
       has_aspect_glyphs = 1;
       fread( pAspect, sizeof(GR_ASPT), aspect_count, stream );
       }
    }
 if (isafptr2_file(&nfp)) {
    if ( data->num_charts ) {
       pChart = new GR_CHART[data->num_charts];
       chart_count = data->num_charts;
       cur_chart = 0;
       if ( pChart == NULL ) {
	  do_mem_error(0);
	  fclose( stream );
	  return( 0 );
	  }
       for ( short k = 0; k < data->num_charts; k++ ) {
	   fread( pChart[k].date, DATE_WIDTH+2, 1, stream );
	   fread( pChart[k].chart_minutes, 2, 18, stream );
	   memset( &pChart[k].chart_minutes[18], 0xff, 24 );
	   }
       }
    }
 else {
    if ( data->num_charts ) {
       pChart = new GR_CHART[data->num_charts];
       chart_count = data->num_charts;
       cur_chart = 0;
       if ( pChart == NULL ) {
	  do_mem_error(0);
	  fclose( stream );
	  return( 0 );
	  }
       for ( i = 0; i < chart_count; i++ )
	   pChart[i].read(stream);
	   }
    }
 if ( data->num_data ) {
    pDataLst = new GR_DATALST[data->num_data];
    data_count = data->num_data;
    if ( pDataLst == NULL ) {
       do_mem_error(0);
       fclose( stream );
       return( 0 );
       }
    fread( pDataLst, sizeof(GR_DATALST), data_count, stream );
    }
 if ( data->num_other ) {
    pOtherLst = new GR_DATALST[data->num_other];
    other_data_count = data->num_other;
    if ( pOtherLst == NULL ) {
       do_mem_error(0);
       fclose( stream );
       return( 0 );
       }
    fread( pOtherLst, sizeof(GR_DATALST), other_data_count, stream );
    }
 if ( data->num_text ) {
    pText = new GR_TEXT *[data->num_text];
    text_count = data->num_text;
    text_alloc = data->num_text;
    if ( pText == NULL ) {
       do_mem_error(0);
       fclose( stream );
       return( 0 );
       }
    ptx = pText;
    for ( pt = ptx, i = 0; i < text_count; i++, pt++ ) {
	if ( !readTextItem( pt, stream ) ) {
	   do_error( buf );
	   fclose( stream );
	   }
	}
    }
 if ( data->num_grid_aspects ) {
    pGridAspect = new GR_ASPT[data->num_grid_aspects];
    grid_aspect_count = data->num_grid_aspects;
    if ( pGridAspect == NULL ) {
       do_mem_error(0);
       fclose( stream );
       return( 0 );
       }
    fread( pGridAspect, sizeof(GR_ASPT), grid_aspect_count, stream );
    }
 if ( data->num_other_grid_aspects ) {
    pOtherGridAspect = new GR_ASPT[data->num_other_grid_aspects];
    other_grid_aspect_count = data->num_other_grid_aspects;
    if ( pOtherGridAspect == NULL ) {
       do_mem_error(0);
       fclose( stream );
       return( 0 );
       }
    fread( pOtherGridAspect, sizeof(GR_ASPT), other_grid_aspect_count, stream );
    }
 fclose( stream );
 return( 1 );
}


short GraphData::readTextItem( GR_TEXT **pT, FILE *stream )
{
 GR_TEXT t;

 fread( &t, sizeof( GR_TEXT )-1, 1, stream );
 *pT = (GR_TEXT *)new char[sizeof(GR_TEXT)+t.len+1];
 if ( *pT == NULL ) {
    do_mem_error( 0 );
    return( 0 );
    }
 **pT = t;
 return( fread( (*pT)->buf, (*pT)->len+1, 1, stream ) );
}

short GraphData::writeTextItem( GR_TEXT **pT, FILE *stream )
{
 fwrite( *pT, sizeof( GR_TEXT )-1, 1, stream );
 return( fwrite( (*pT)->buf, (*pT)->len+1, 1, stream ) );
}

short GraphData::ncharts()
{
 static short ar[] = { 0, 1, 2, 2, 2, 1, 0, 0, 1, 1, 0, 0, 0, 0, 2 };

 return( ar[getData()->type - LAST_NON_GRAPH] );
}


short GraphData::save( char *name, short dir )
{
 char buf[200];
 GR_TEXT **ptx, **pt;
 FILE *stream;
 short i;
 NFDB n;

 n.n = nfp.n.fpt;
 strcpy( buf, set_path(name, dir) );
 if ( ( stream = fwrite_fptr( buf, &n, 7 ) ) == NULL ) {
    do_error( buf );
    return( 0 );
    }
 else {
    if ( !fwrite( data, sizeof( GR_DAT), 1, stream ) ) {
       do_error( buf );
       fclose( stream );
       return( 0 );
       }
    }
 if ( data->num_aspects ) {
    fwrite( pAspect, sizeof(GR_ASPT), aspect_count, stream );
    }
 if ( data->num_charts ) {
    for ( i = 0; i < data->num_charts; i++ ) {
	pChart[i].write(stream);
	}
    }
 if ( data->num_data ) {
    fwrite( pDataLst, sizeof(GR_DATALST), data_count, stream );
    }
 if ( data->num_other ) {
    fwrite( pOtherLst, sizeof(GR_DATALST), other_data_count, stream );
    }
 if ( data->num_text ) {
    ptx = pText;
    for ( pt = ptx, i = 0; i < text_count; i++, pt++ ) {
	if ( !writeTextItem( pt, stream ) ) {
	   do_error( buf );
	   fclose( stream );
	   }
	}
    }
 if ( data->num_grid_aspects ) {
    fwrite( pGridAspect, sizeof(GR_ASPT), grid_aspect_count, stream );
    }
 if ( data->num_other_grid_aspects ) {
    fwrite( pOtherGridAspect, sizeof(GR_ASPT), other_grid_aspect_count, stream );
    }
 fclose( stream );
 return( 1 );
}

GR_TEXT *GraphData::addTextItem( GR_TEXT *p )
{
#ifdef XXX
 GR_TEXT *pNew;
 GR_TEXT **pT;
 pNew = (GR_TEXT *)new char[sizeof(GR_TEXT)+p->len+1];
 if ( pNew == NULL ) {
    do_mem_error( 0 );
    return( NULL );
    }
 memcpy( pNew, p, sizeof(GR_TEXT)+p->len+1 );
 if ( text_alloc > text_count ) {
    *(pText+text_count) = pNew;
    text_count++;
    return( pNew );
    }
 else {
    pT = (GR_TEXT **)reallocx( pText, (text_alloc+5) * sizeof(GR_TEXT *) );
    if ( pT == NULL ) {
       do_mem_error( 0 );
       return( NULL );
       }
    pText = pT;
    text_alloc += 5;
    *(pText+text_count) = pNew;
    text_count++;
    return( pNew );
    }
#endif
return( NULL );
}

/* Make sure to pass this return a pointer that was given by
   addTextItem() and delete it after coming back from this operation,
   if this operation does not return NULL */

GR_TEXT *GraphData::replaceTextItem( GR_TEXT *p )
{
#ifdef XXX
 int i;
 GR_TEXT *pNew;
 GR_TEXT **pT;
 pNew = (GR_TEXT *)new char[sizeof(GR_TEXT)+p->len+1];
 if ( pNew == NULL ) {
    do_mem_error( 0 );
    return( NULL );
    }
 memcpy( pNew, p, sizeof(GR_TEXT)+p->len+1 );
 for ( i = 0, pT = pText; i < text_count; i++, pT++ ) {
     if ( *pT == p ) {
	    *pT = pNew;
	    return( pNew );
	    }
     }
#endif
 return( NULL );
}



GraphData::GraphData()
{
 
 data = new GR_DAT;
 memset( data, 0, sizeof (GR_DAT) );
 other_data_count = 0;
 pOtherLst = NULL;
 data_count = 0;
 pDataLst = NULL;
 aspect_count = 0;
 pAspect = NULL;
 chart_count = 0;
 pChart = NULL;
 text_count = 0;
 text_alloc = 0;
 pText = NULL;
 grid_aspect_count = 0;
 pGridAspect = NULL;
 other_grid_aspect_count = 0;
 pOtherGridAspect = NULL;
}

GraphData::~GraphData()
{
 int i;

 delete data;
 if ( other_data_count && pOtherLst )
    delete pOtherLst;
 if ( data_count && pDataLst )
    delete pDataLst;
 if ( aspect_count && pAspect )
    delete pAspect;
 if ( chart_count && pChart )
    delete pChart;
 if ( text_count && pText ) {
    for ( i = 0; i < text_count; i++ ) {
	delete pText[i];
	}
    delete pText;
    }
 if ( grid_aspect_count && pGridAspect )
    delete pGridAspect;
 if ( other_grid_aspect_count && pOtherGridAspect )
    delete pOtherGridAspect;
}
