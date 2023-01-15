/* routines for databases to re-index the databases
   location handling */
#include "stdafx.h"
#include <stdlib.h>
#include <share.h>
#include "astro.h"
#include "useri.h"
#include "dbstruct.h"
#include "freesp.hpp"
#include "database.hpp"
#include "errors.fns"
#include "uicvt.fns"
#include <io.h>
#include "charcons.h"
#include "astrow.h"
#include "procmsg.h"


/* Function to reindex a datafile. This function takes index which is a
   pointer to the name of the index file. It also takes  i_file which is
   a pointer to the index file structure. d_file is a pointer to the data
   file name. width is the width of the data record. If type is 0 then
   we are dealing with a location type record and the first three
   fields in the data record are used, otherwise we are reindexing a
   name type record and using only the first item. Note this function
   destroys the original index and creates a new index from the datafile
   including old deleted records. If successful, this function returns
   IX_OK, otherwise it prints an error message and returns IX_FAIL.
   Note, this function assumes this index file is closed, so functions
   which call re_index_file should close index if neccessary first */


short Database::reIndex( char *prompt, short size )
{
 FILE *stream;
 long offset;
 LOC_DB loc;
 short len;
 int x = 0, res;
 int _break = 0;
 void *data;

 data = new char[size];
 if ( data == NULL ) {
    do_mem_error(0);
    return( IX_FAIL );
    }
 memset( id.key, 0, sizeof(id.key) );
 memset( data, 0, size );
 memset( &loc, 0, sizeof(LOC_DB) );
 unlink( indexName );
 if ( !startup() ) {
    delete data;
    return( IX_FAIL );
    }
 if ( ( stream = _fsopen( dataName, "rb", SH_DENYWR ) ) == NULL ) {
    do_error( dataName );
    quit:
    delete data;
    shutdown();
    return( IX_FAIL );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	      setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 fseek( stream,  sizeof(short) + (20 * sizeof( FREE_SP )), SEEK_SET );
 ProcMsg pm( prompt, &_break );
 for ( offset = sizeof(short) + (20 * sizeof( FREE_SP ));
	   !feof( stream ) && !ferror( stream );
	                         offset += len, ++x ) {
     if (( fread( &len, 2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( dataName );
	    fclose( stream );
	    goto quit;
	    }
     if ( len < sizeof(D_LOC_DB)-L_WIDTH || len > size ) {
	    alert_box( ERROR2, "Possible Corrupted Data File len = %d, offset = %lx", len, offset );
	    goto quit;
	    }
     if (( fread( ((char *)data)+2, len-2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( dataName );
	    fclose( stream );
	    goto quit;
	    }
     *((short *) data) = len;
     if ( ((D_LOC_DB *)data)->freer == 1 )
	    continue;
     if ( !feof( stream ) ) {
	    buildDataKey(data);
	    id.data_len = len;
	    id.recptr = offset;
	((CAstrowApp *)AfxGetApp())->_Yield(); 
	if ( _break )
	   goto quit2;
	 if ( ( res = add_key( &id, index ) ) == IX_ERROR ) {
	   key_error( id.key, "ERROR ADDING KEY TO INDEX" );
	   fclose( stream );
	   goto quit2;
	   }
	if ( res == IX_FAIL )
	   key_error( id.key, "ERROR ADDING KEY TO INDEX MAY BE DUP!");
	}
     }
 quit2:
 fclose( stream );
 shutdown();
 delete data;
 return( IX_OK );
}

short LocDatabase::reIndex( char *prompt, short size )
{
 FILE *stream;
 long offset;
 LOC_DB loc;
 short len;
 int x = 0, res;
 int _break = 0;
 void *data;

 data = new char[size];
 if ( data == NULL ) {
    do_mem_error(0);
    return( IX_FAIL );
    }
 memset( id.key, 0, sizeof(id.key) );
 memset( data, 0, size );
 memset( &loc, 0, sizeof(LOC_DB) );
 unlink( indexName );
 unlink( countryindexname );
 unlink( stateindexname );
 if ( !startup() ) {
    delete data;
    return( IX_FAIL );
    }
 if ( ( stream = _fsopen( dataName, "rb", SH_DENYWR ) ) == NULL ) {
    do_error( dataName );
    quit:
    delete data;
    shutdown();
    return( IX_FAIL );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	      setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 fseek( stream,  sizeof(short) + (20 * sizeof( FREE_SP )), SEEK_SET );
 ProcMsg pm( prompt, &_break );
 for ( offset = sizeof(short) + (20 * sizeof( FREE_SP ));
	   !feof( stream ) && !ferror( stream );
	                         offset += len, ++x ) {
     if (( fread( &len, 2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( dataName );
	    fclose( stream );
	    goto quit;
	    }
     if ( len < sizeof(D_LOC_DB) || len > size ) {
	    alert_box( ERROR2, "Possible Corrupted Data File len = %d, offset = %lx", len, offset );
	    goto quit;
	    }
     if (( fread( ((char *)data)+2, len-2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( dataName );
	    fclose( stream );
	    goto quit;
	    }
     *((short *) data) = len;
     if ( ((D_LOC_DB *)data)->freer == 1 )
	    continue;
     if ( !feof( stream ) ) {
	    buildDataKey(data);
	    id.data_len = len;
	    id.recptr = offset;
	((CAstrowApp *)AfxGetApp())->_Yield(); 
	if ( _break )
	   goto quit2;
	 if ( ( res = add_key( &id, index ) ) == IX_ERROR ) {
	   key_error( id.key, "ERROR ADDING KEY TO INDEX" );
	   fclose( stream );
	   goto quit2;
	   }
	 strcpy( id.key, country_key );
     if ( ( res = add_key( &id, country_index ) ) == IX_ERROR ) {
	   key_error( id.key, "ERROR ADDING KEY TO INDEX" );
	   fclose( stream );
	   goto quit2;
	   }
	 strcpy( id.key, state_key );
	 if ( ( res = add_key( &id, state_index ) ) == IX_ERROR ) {
	   key_error( id.key, "ERROR ADDING KEY TO INDEX" );
	   fclose( stream );
	   goto quit2;
	   }
	}
     }
 quit2:
 fclose( stream );
 shutdown();
 delete data;
 return( IX_OK );
}

void LocDatabase::buildDataKey( void *buf )
{
 LOC_DB *lp, loc;

 memset( &loc, 0, sizeof( LOC_DB ) );
 lp = cvt_dsk_2_nlocdb( &loc, (struct D_LOC_DB *)buf );
 make_key( lp->country, lp->state, lp->location );
 strcpy( id.key, db_key );
}

void BirthDatabase::buildDataKey( void *buf )
{
 BIRTH_DB *bp, nb;

 memset( &nb, 0, sizeof( BIRTH_DB ) );
 bp = cvt_dsk_2_nbirthdb( &nb, (union DBR *)buf, NULL );
 strcpy( id.key, bp->name );
}


void index_db( char *which )
{
 if ( !strcmpi( which, "LOC" ) || !strcmpi( which, "ALL" ) ) {
    LocDatabase *pld = new LocDatabase();
    pld->reIndex("...RE-INDEXING LOCATION DATABASE...");
    delete pld;
    }
 if ( !strcmpi( which, "BIRTH" ) || !strcmpi( which, "ALL" ) ) {
    BirthDatabase *pbd = new BirthDatabase();
    pbd->reIndex("...RE-INDEXING BIRTH DATABASE...");
    delete pbd;
    }
 return;
}
