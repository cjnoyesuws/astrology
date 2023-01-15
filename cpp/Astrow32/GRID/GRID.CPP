#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdio.h>
#include <string.h>
#include "charcons.h"
#include "astro.h"
#include "useri.h"
#include "grid.hpp"

GridArray::~GridArray()
{
 int i;

 if ( sortData != NULL );
    delete sortData;
 for ( i = 0; i < dcount; i++ )
     delete data[i];
}

int GridArray::allocate( int p, int c )
{
 if ( !c ) {
    alloc[p] = 0;
    count[p] = 0;
    data[p] = NULL;
    if ( dcount < p )
       dcount = p;
    return( -1 );
    }
 data[p] = new GRD_U[c];
 if ( data[p] == NULL )
    return( 0 );
 alloc[p] = c;
 count[p] = 0;
 if ( dcount < p )
    dcount = p;
 return( 1 );
}

int GridArray::add( int p, char f, char s, char a, char o )
{
 if ( count[p] < alloc[p] ) {
    data[count[p++]]->set( f, s, a, o );
    return( 1 );
    }
 return( 0 );
}

int GridArray::add(int p, char f, char s, char d, char i, char m )
{
 if ( count[p] < alloc[p] ) {
    data[count[p++]]->set( f, s, d, i, m );
    return( 1 );
    }
 return( 0 );
}


int GridArray::add(int p, MIDPT *m, int count)
{
 int i;
 MIDPT *mm;

 if ( !allocate( p, count ) )
    return( 0 );
 if ( !count )
    return( 1 );
 for ( i = 0, mm = m; i < count; i++, mm++ ) {
     add(p, i, p, mm->second_planet, mm->minor_degrees, mm->sign, mm->minor_minutes );
     }
 return( 1 );
}


int GridArray::add(int p, ASPEC *a, int count)
{
 int i;
 ASPEC *aa;

 if ( !allocate( p, count ) )
    return( 0 );
 if ( !count )
    return( 1 );
 for ( i = 0, aa = a; i < count; i++, aa++ ) {
     add(p, i, p, aa->aspect, aa->orb );
     }
 return( 1 );
}

void GridArray::setup()
{
 int i;

 for ( i = 0; i < dcount; i++ )
     desc.data_points += count[i];
 desc.rows = dcount;
 desc.srows = (scount / 4)+1;
}

int midCmp( void *p1, void *p2 )
{
 char d, i, m, f, s;
 GRD_MID *m1 = (GRD_MID *)p1, *m2 = (GRD_MID *)p2;
 int mi1, mi2;

 m1->get(f,s,d,i,m);
 mi1= ((i*30)+d*60)+m;
 m2->get(f,s,d,i,m);
 mi2= ((i*30)+d*60)+m;
 return( mi1-mi2 );
}

int GridArray::sort()
{
 int i;

 for ( i = 0; i < dcount; i++ ) {
     salloc += count[i];
     }
 sortData = new GRD_U[salloc];
 if ( sortData == NULL ) {
    salloc = 0;
    scount = 0;
    return( 0 );
    }
 for ( i = 0; i < dcount; i++ ) {
     memcpy(sortData+scount, data[i], count[i]*sizeof(GRD_U) );
     scount += count[i];
     }
 qsort(sortData,scount,sizeof(GRD_U), midCmp);
 type(type()|GRD_SQUARE);
 mode(mode()|GRD_SQUARE);
 return( 1 );
}


GRD_U *GridArray::get(int p, int i);
{
 assert( i >= 0 && p >= 0 );
 if ( p >= dcount || i >= count[p] )
    return( NULL );
 if ( data[p] == NULL )
    return( NULL );
 return( data[p]+i )
}



GRD_U *GridArray::getSorted(int i);
{
 assert( mode() & GRD_SQUARE );
 assert( i >= 0  );
 if ( i >= scount )
    return( NULL );
 if ( sortData == NULL )
    return( NULL );
 return( sortData+i );
}


int GridArray::save( char *name, int append )
{
 FILE *stream;
 int i;

 setup();
 if ( append )
    stream = fopen( name, "wb" );
 else
    stream = fopen( name, "ab" );
 if ( stream == NULL )
    return( 0 );
 fwrite( &desc, sizeof( GRID_STRUCT ), 1, stream );
 fwrite( &dcount, sizeof( int), 1, stream );
 fwrite( count, sizeof( int ), dcount, stream );
 fpr ( i = 0; i < dcount; i++ ) {
     if ( count[i] )
	fwrite( data[i], sizeof( GRD_U ), count[i], stream );
     }
 if ( mode() & GRD_SQUARE ) {
    fwrite( &scount, sizeof( int), 1, stream );
    fwrite( sortData, sizeof( GRD_U ), scount, stream );
    }
 i = ferror( stream );
 fclose( stream );
 return( i );
}

int GridArray::readHeader( FILE *stream )
{
 fread( &desc, sizeof( GRID_STRUCT ), 1, stream );
 fread( &dcount, sizeof( int), 1, stream );
 fread( count, sizeof( int ), dcount, stream );
}

int GridArray::seekEnd( FILE *stream )
{
 long l;

 l = fseek( stream, desc.data_points * sizeof( GRD_U ), SEEK_CUR );
 if ( mode() & GRD_SQUARE ) {
    fread( &scount, sizeof( int ), 1, stream );
    l = fseek( stream, scount * sizeof( GRD_U ), SEEK_CUR );
    }
 if ( l == -1L )
    return( 0 );
 return( 1 );
}


int GridArray::load( char *name, int which )
{
 FILE *stream;
 int i, e;

 if ( ( stream = fopen( name, "rb" ) ) == NULL )
    return( 0 );
 e = readHeader( stream );
 if ( e ) {
    fclose( stream );
    return( 0 );
    }
 for ( i = 0; i < which; i++ ) {
     e = seekEnd( stream );
     e = readHeader( stream );
     if ( e ) {
	fclose( stream );
	return( 0 );
	}
     }
 fpr ( i = 0; i < dcount; i++ ) {
     if ( count[i] ) {
	alloc[i] = count[i];
	data[i] = new GRD_U[count[i]];
	if ( data[i] == NULL ) {
	   fclose( stream );
	   return( 0 );
	   }
	fread( data[i], sizeof( GRD_U ), count[i], stream );
	}
     else {
	alloc[i] = 0;
	data[i] = NULL;
	}
     }
 if ( mode() & GRD_SQUARE ) {
    fread( &scount, sizeof( int), 1, stream );
    salloc = scount;
    sortData = new GRD_U[scount];
    if ( sortData == NULL ) {
       fclose( stream );
       return( 0 );
       }
    fread( sortData, sizeof( GRD_U ), scount, stream );
    }
 fclose( stream );
 return( 1 );
}

int GridArray::doAspects( AS_INF *inf, int count )
{
 AS_INF *ip;
 int i, e;

 for ( i = 0, ip = inf; i < count; i++, ip++ ) {
     if ( !add( i, ip->aspectr, ip->no_aspects ) )
	return( 0 );
     }
 return( 1 );
}


int GridArray::doMidpoints( AS_INF *inf, int count )
{
 AS_INF *ip;
 int i, e;

 for ( i = 0, ip = inf; i < count; i++, ip++ ) {
     if ( !add( i, ip->midptr, ip->no_midpt ) )
	return( 0 );
     }
 return( sort() );
}
