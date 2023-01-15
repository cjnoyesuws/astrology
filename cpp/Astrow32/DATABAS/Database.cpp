/* database functions used for locbase and for astro for
   location and birthbas handling procedures */
#include "stdafx.h"
#include <io.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>
#include <string.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dbstruct.h"
#include "freesp.hpp"
#include "paths.hpp"
#include "database.hpp"
#include "uicvt.fns"
#include "errors.fns"
#include <assert.h>
#include <errno.h>

extern char *strclip( char * );

Database::Database(char *dname, char *iname)
{
 strcpy( dataName, set_path( dname, DATABASE_F ) );
 strcpy( indexName, set_path( iname, DATABASE_F ) );
 fail_rec = 0L;
 fail_len = 0L;
 index = NULL;
}

/*
Database::Database( Database *dp )
{
 strcpy( dataName, dp->dataName );
 strcpy( indexName, dp->indexName );
 fail_rec = dp->fail_rec;
 fail_len = dp->fail_len;
 index = dp->index;
}
*/

void Database::key_error( char *key, char *msg )
{
 char *kp;

 char *keyb = new char[250];
 strcpy( keyb, key );
 kp = keyb;
 do {
    kp = strchr( kp, '\1' );
    if ( kp != NULL )
       *kp = ';';           /* replace field separators with ; */
    } while ( kp != NULL );
 alert_box_ext("DATABASE ERROR!!", MB_OK|MB_ICONSTOP,
	  "\"%s\" : %s", keyb, msg );
 delete keyb;
}

/* function to write a record from database. Filename is name of
   file, size is record size (width of *data). and offset offset
   of record in file in bytes, data is pointer to data record
   returns offset of file for success -1 otherwise. If offset is
   -1 data is written to end of file otherwise data is written to
   offset position */



long Database::write_rec( short size, long offset, void *data )
{
 short ret, handle;
 long pos;

 if ( ( handle = open( dataName, O_BINARY|O_CREAT|O_WRONLY, S_IWRITE ) ) == -1 ) {
    do_error( dataName );
    return( -1L );
    }
 if ( offset == -1L ) {
    if ( lseek( handle, 0L, SEEK_END ) == -1L ) {
       do_error( dataName );
       close( handle );
       return( -1L );
       }
    else
       pos = tell( handle );
    }
 else {
    if ( lseek( handle, offset, SEEK_SET ) == -1L ) {
       do_error( dataName );
       close( handle );
       return( -1L );
       }
    else
       pos = offset;
    }
 if ( ( ret = write( handle, data, size ) ) != size )
    do_error( dataName );
 close( handle );
 if ( ret == size )
    return( pos );
 else
    return( -1L );
}


/* function to read a record from database. Filename is name of
   file, size is record size (width of *data). and offset offset
   of record in file in bytes, data is pointer to data record
   returns 0 for success non -1 otherwise */

short Database::read_rec( short size, long offset, void *data )
{
 short ret, handle;

 if ( ( handle = open( dataName, O_BINARY|O_RDONLY ) ) == -1 ) {
    do_error( dataName );
    return( -1 );
    }
 if ( lseek( handle, offset, SEEK_SET ) == -1L ) {
    do_error( dataName );
    close( handle );
    return( -1 );
    }
 if ( ( ret = read( handle, data, size )) != size )
    do_error( dataName );
 close( handle );
 if ( ret == size )
    return( 0 );
 else
    return( -1 );
}

short Database::startup()
{
 FILE *stream;
 short result;

 if ( index == NULL ) {
    index = new IX_DESC;
    if ( index == NULL ) {
       do_mem_error( 0 );
       return( IX_ERROR );
       }
    }
 memset( index, 0, sizeof( IX_DESC ) );
 if ( ( stream = fopen( indexName, "rb" ) ) == NULL ) {
    if ( ( result = make_index( indexName, index, NO_DUPS ) ) != IX_OK ) {
       delete index ;
       index = NULL;
       return( IX_ERROR );
       }
    }
    else {
	fclose( stream );
	if ( ( result = open_index( indexName, index, NO_DUPS ) ) != IX_OK ) {
	   delete index ;
	   index = NULL;
	   return( IX_ERROR );
	   }
	}
 return( frees.read( dataName ) );
}


void Database::shutdown()
{
  if ( index != NULL ) {
     close_index( index );
     delete index;
     index = NULL;
     }
  else
     return;
  frees.write( dataName );
}

/* function to add a new record to a database file. d_name is the datafile
   name, data is pointer to structure, key is pointer to key for file,
   i_file is pointer to index file structure, width is width of *data,
   fail_rec is a pointer to a record number. If fail_rec is not equal
   to zero, then the record number is retrieved from there. this varaiable
   is a pointer to the last deleted or failed database record. If this
   variable points to 0L then the next available record is used. If
   successful it returns IX_OK, otherwise prints error message and
   returns IX_FAIL */

short Database::add_write_rec( void *data, char *key, short width )
{
 long rec;
 STAT ret;
 short nwidth = width;

 if ( index == NULL )            
    return( IX_FAIL );
 strcpy( id.key, key );
 id.data_len = nwidth;
 assert( data != NULL && index != NULL );
 if ( find_key( &id, index ) == IX_OK ) {
    key_error( id.key, "KEY ALREADY IN INDEX ERROR!!" );
    return( IX_FAIL );
    }
 rec = frees.do_free( nwidth, &nwidth, &fail_len, &fail_rec );
 *((short *)data) = nwidth;
 rec = write_rec( nwidth, rec, data );
 if ( rec == -1L ) {
    return( IX_ERROR );
    }
 id.recptr = rec;
 id.data_len = nwidth;
 if ( ( ret = add_key( &id, index ) ) != IX_OK ) {
    if ( ret == IX_ERROR ) {
       del_rec(id.recptr, id.data_len );
       return( ret );
       }
    else if ( ret == IX_FAIL ) {
       del_rec( id.recptr, id.data_len);
       key_error( key, "COULD NOT ADD KEY ERROR!!" );
       return( ret );
       }
    }
 return( ret );
}

/* Function to replace a record in a database. This should only be used
   if the record is already on the db. d_name is the datafile name.
   data is a pointer to the structer to write. key is a pointer to the
   key for the replacement data, old_key is a pointer to the key for
   the previous data. If the keys are the same then the keys are not
   replaced in the index. If the keys are not the same, then the
   old_key is removed from the index and key is added. i_file is a
   pointer to the index file structure for the file. width is the
   width of *data. fail_rec is a pointer to a record pointer. If the
   write should fail, the db will save the record address in that
   variable so it won't be wasted. If this function is successful, it
   returns IX_OK, otherwise an error message is printed and the function
   returns IX_FAIL */

short Database::replace_rec( void *data, char *key, char *old_key, short width )
{
 ENTRY old_id;
 long rec;
 STAT ret;

 if ( index == NULL )
    return( IX_FAIL );
 assert( data != NULL && index != NULL );
 strcpy( id.key, key );
 strcpy( old_id.key, old_key );
 if ( find_key( &old_id, index ) != IX_OK ) {
    key_error( old_key,  "OLD KEY NOT FOUND TO REPLACE ERROR, ADDING!!" );
    return( add_write_rec( data, key, width ) );
    }
 if ( ( ret = strcmpi( key, old_key ) ) != 0 || width != old_id.data_len ) {
    if ( delete_rec( old_key ) != IX_OK )
       return( IX_FAIL );
    rec = frees.do_free( width, &width, &fail_len, &fail_rec );
    *((short *)data) = width;
    if ( ( rec = write_rec( width, rec, data ) ) == -1L ) {
       key_error( dataName, "ERROR WRITING DATA" );
       return( IX_ERROR );
       }
    }
 else {
    if ( ( rec = write_rec( width, old_id.recptr, data ) ) == -1L ) {
       key_error( dataName, "ERROR WRITING DATA" );
       return( IX_ERROR );
       }
    }
 strcpy( id.key, key );
 id.data_len = width;
 id.recptr = rec;
 if ( ret ) {
    if ( ( ret = add_key( &id, index ) ) != IX_OK ) {
       key_error( key, "COULD NOT ADD NEW KEY ERROR!!" );
       del_rec(id.recptr, id.data_len);
       return( ret );
       }
    }
 return( ret );
}

/* Function to get a record from a database. d_name is a pointer to the
   datafile name. data is a pointer to the structure used to hold the
   data when read into memory. key is a pointer to the key to be used
   to find the record. i_file is a pointer to the index file structure
   for the index. width is the width of *data. If successful, this
   function returns IX_OK, otherwise prints an error message and returns
   IX_FAIL. */

short Database::get_rec(void *data, char *key )
{
 long rec;

 if ( index == NULL )
    return( IX_FAIL );
 assert( data != NULL && index != NULL );
 strcpy( id.key, key );
 if ( find_key( &id, index ) != IX_OK ) {
    key_error( key, "KEY NOT FOUND ERROR!!" );
    return( IX_FAIL );
    }
 rec = id.recptr;
 if ( read_rec( id.data_len, rec, data ) )
    return( IX_FAIL );
 else
    return( IX_OK );
}

/* Function to delete a record from a database if possible. The function
   first tests to see if this record is available, the deletes it.
   It is advised to check to see that this record is the one you wish to
   delete first as their is no un_delete, though a deleted record could
   probably be recovered unless it was reused immediately in which case
   it would not be recoverable. It is suggested that you add a new
   record to the database immediately after you delete one so the space
   is not wasted. Function takes char pointer to the key. i_file is a
   pointer to the index file structure for the file, and fail_rec is a
   long pointer to hold the deleted record. If successful, this function
   returns IX_OK, otherwise returns IX_FAIL and prints an error message. */

short Database::delete_rec( char *key )
{
 long rec;

 assert( index != NULL );
 strcpy( id.key, key );
 if ( find_key( &id, index ) != IX_OK ) {
    key_error( key,  "KEY NOT FOUND TO DELETE ERROR!!" );
    return( IX_FAIL );
    }
 rec = id.recptr;
 if ( delete_key( &id, index ) != IX_OK ) {
    key_error( key, "COULD NOT DELETE OLD FROM INDEX ERROR!!" );
    return( IX_FAIL );
    }
 return( del_rec(id.recptr, id.data_len ) );
}

short Database::del_rec( long o, short l )
{
 short x = 1;

 frees.add( l, o );
 return(( write_rec( 2, o+2, &x ) != -1L) );
}


LocDatabase::LocDatabase(char *dname, char *iname, char *ctname, char *stname) :
     Database(dname,iname)
{
  char buf[250];

  strcpy( buf, set_path( ctname, DATABASE_F ) );
  countryindexname = strdup(buf);
  strcpy( buf, set_path( iname, DATABASE_F ) );
  stateindexname = strdup(buf);
  memset( buf, 0, sizeof( buf ) );
  memset( db_key, 0, sizeof( db_key ) );
  memset( state_key, 0, sizeof( state_key ) );
  memset( country_key, 0, sizeof( country_key ));
}

/*
LocDatabase::LocDatabase( LocDatabase *lp ) :
     Database( (Database *)lp )
{
  popup = lp->popup;
  strcpy( popupName, lp->popupName );
}
*/

short LocDatabase::startup()
{
 FILE *stream;
 STAT result;

 if ( country_index == NULL ) {
    country_index = new IX_DESC;
    if ( country_index == NULL ) {
       do_mem_error( 0 );
       return( IX_ERROR );
       }
    }
 memset( country_index, 0, sizeof( IX_DESC ) );
 if ( state_index == NULL ) {
    state_index = new IX_DESC;
    if ( state_index == NULL ) {
       do_mem_error( 0 );
       return( IX_ERROR );
       }
    }
 memset( state_index, 0, sizeof( IX_DESC ) );


 if ( ( stream = fopen( stateindexname, "rb" ) ) == NULL ) {
    if ( ( result = make_index( stateindexname, popup, NO_DUPS ) ) != IX_OK ) {
       delete state_index ;
       state_index = NULL;
       return( IX_ERROR );
       }
    }
    else {
	fclose( stream );
	if ( ( result = open_index( stateindexname, state_index, NO_DUPS ) ) != IX_OK ) {
	   delete stae_index;
	   state_index = NULL;
	   return( IX_ERROR );
	   }
	}
 if ( ( stream = fopen( countryindexname, "rb" ) ) == NULL ) {
    if ( ( result = make_index( countryindexname, popup, NO_DUPS ) ) != IX_OK ) {
       delete countryindexname ;
       countryindexname = NULL;
       return( IX_ERROR );
       }
    }
    else {
	fclose( stream );
	if ( ( result = open_index( countryindexname, country_index, NO_DUPS ) ) != IX_OK ) {
	   delete country_index;
	   popup = NULL;
	   return( IX_ERROR );
	   }
	}
 return( Database::startup() );
}


void LocDatabase::shutdown()
{
  if ( state_index != NULL ) {
     close_index( state_index );
     delete state_index;
     state_index = NULL;
	 
     }
  if ( country_index != NULL ) {
     close_index( country_index );
     delete country_index;
     country_index = NULL;
	 
     }
  Database::shutdown();
}


/* function to find a popup index entry for a location 
   returns the offset in the popup file or -1L for not
   found. Key error is called only if fShEr is true */

long LocDatabase::find_loc( char *co, char *st, char *lo, char *which, short fShEr )
{
 memset( buf, 0, sizeof(buf) );
 make_key( co, st, lo );
 if ( index == NULL )
    return( -1L );
 assert( popup != NULL );
 strcpy( id.key, which );
 strcat( id.key, db_key );

 if ( find_key( &id, index ) != IX_OK ) {
    if ( fShEr )
       key_error( db_key, "KEY NOT FOUND ERROR!!" );
    return( -1L );
    }
return( id.recptr );
}

/* function to add a new location to the database using above procedures
   takes pointer to data record. Returns 0 for success, -1 for error */

short LocDatabase::write_loc( LOC_DB *data )
{
 short len;

 if ( index == NULL )
    return( -1 );
 make_key( data->country, data->state, data->location );
 memset( buf, 0, sizeof(buf) );
 len = cvt_nlocdb_2_dsk( data, (D_LOC_DB *)buf );
 if ( add_write_rec( buf, db_key, len ) == IX_OK ) {
    has_Loc( 1 );
    strcpy( id.key, country_key );
    id.data_len = strlen(country);
	id.recptr = 0;
    if ( find_key( &id, country_index ) != IX_OK ) {
       add_key( &id, country_index )
		}
    strcpy( id.key, state_key );
    id.data_len = strlen(state_key);
    if ( find_key( &id, state_index ) != IX_OK ) {
        id.recptr = 0;
        add_key( &id, state_index );                
		}
    return( 0 );
    }
  else
    return( -1 );
}

/* function to retrieve a location from the database using above procedures
   takes pointer to data record. Returns 0 for success, -1 for error */

short LocDatabase::read_loc( char *country, char *state, char *location, LOC_DB *data )
{
 if ( index == NULL )
    return( -1 );
 memset( buf, 0, sizeof(buf) );
 if ( !strlen(location) )
    return( -1 );
 make_key( country, state, location );
 if ( get_rec( buf, db_key ) == IX_OK ) {
    cvt_dsk_2_nlocdb( data, (D_LOC_DB *)buf );
    has_Loc( 1 );
    return( 0 );
    }
  else
    return( -1 );
}

/* function to delete a location from the database using above procedures
   takes pointer to data record. Returns 0 for success, -1 for error */

short LocDatabase::delete_loc( char *country, char *state, char *location )
{
 make_key( country, state, location );
 has_Loc( 0 );
 if ( index == NULL )
    return( -1 );
 if ( delete_rec( db_key ) == IX_OK )
    return( 0 );
 else
    return( -1 );
}

/* function to replace a location in the database with a new record.
   Takes data pointer to data to replace. User also provides old_key
   saved from db_key from the last read call. If old_key == NULL then
   old_key is assumed to be db_key. Note that if old_key is NULL, then
   an assumption is made that the location most recently read is the
   last key, and will be the one replaced. It is important to remember
   this. If user tries to add a record using replace, then the most
   recently made key from the last *_loc() function will be deleted
   takes pointer to new data record. Returns 0 for success, -1 for
   failure */

short LocDatabase::replace_loc( LOC_DB *data )
{
 short len;

 if ( index == NULL )
    return( -1 );
 char *key = new char[COUNTRY_WIDTH+STATE_WIDTH+LOCATION_WIDTH+1];
 if ( key == NULL ) {
    do_mem_error( 0 );
    return( -1 );
    }
 memset( buf, 0, sizeof(buf) );
 if ( !strcmpi( db_key, "" ) )
    make_key( data->country, data->state, data->location );
 strcpy( key, db_key );
 make_key( data->country, data->state, data->location );
 len = cvt_nlocdb_2_dsk( data, (D_LOC_DB *)buf );
 if ( replace_rec( buf, db_key, key, len ) == IX_OK ) {
    delete key;
    has_Loc( 1 );
    return( 0 );
    }
 else {
    delete key;
    has_Loc( 0 );
    return( -1 );
    }
}


char *LocDatabase::make_key( char *country, char *state, char *location )
{
 short l;

 strclip(country);
 strcpy( db_key, country );
 strcpy( country_key, country );
 l = strlen( db_key );
 if ( state == NULL ) {
    return( db_key );
    }
 strcpy( &db_key[l], "\1" );
 l++;
 strclip(state);
 strcpy( &db_key[l], state );
 strcpy( state_key, db_key );
 l+= strlen( &db_key[l] );
 if ( location == NULL ) {
    return( db_key );
    }
 strcpy( &db_key[l], "\1" );
 l++;
 strclip(location);
 strcpy( &db_key[l], location );
 return( db_key );
}

BirthDatabase::BirthDatabase(char *dname, char *iname) : Database(dname,iname)
{
  memset( buf, 0, sizeof( buf ) );
  memset( db_key, 0, sizeof( db_key ) );
}



/* function to add a new birth to the database using above procedures
   takes pointer to data record. Returns 0 for success, -1 for error */

short BirthDatabase::write_birth( BIRTH_DB *data, RECT_DATA *rd )
{
 short len;

 if ( index == NULL )
    return( -1 );
 memset( buf, 0, sizeof(buf) );
 strcpy( db_key, data->name );
 len = cvt_nbirthdb_2_dsk( data, (DBR *)buf, rd );
 if ( add_write_rec( buf, data->name, len ) == IX_OK ) {
    strcpy( db_key, data->name );
    has_Birth( 1 );
    return( 0 );
    }
  else
    return( -1 );
}

/* function to retrieve a location from the database using above procedures
   takes pointer to data record. Returns 0 for success, -1 for error */

short BirthDatabase::read_birth( char *name, BIRTH_DB *data, RECT_DATA *rd )
{
 if ( !strlen(name) )
    return( -1 );
 if ( index == NULL )
    return( -1 );
 memset( buf, 0, sizeof(buf) );
 strcpy( db_key, name );
 if ( get_rec( buf, db_key ) == IX_OK ) {
    cvt_dsk_2_nbirthdb( data, (DBR *)buf, rd );
    has_Birth( 1 );
    return( 0 );
    }
  else
    return( -1 );
}

/* function to delete a location from the database using above procedures
   takes pointer to data record. Returns 0 for success, -1 for error */

short BirthDatabase::delete_birth( char *name )
{
 if ( index == NULL )
    return( -1 );
 if ( delete_rec( name ) == IX_OK ) {
    has_Birth( 0 );
    return( 0 );
    }
  else
    return( -1 );
}

/* function to replace a location in the database with a new record.
   Takes data pointer to data to replace. User also provides old_key
   saved from db_key from the last read call. If old_key == NULL then
   old_key is assumed to be db_key. Note that if old_key is NULL, then
   an assumption is made that the location most recently read is the
   last key, and will be the one replaced. It is important to remember
   this. If user tries to add a record using replace, then the most
   recently made key from the last *_loc() function will be deleted
   takes pointer to new data record. Returns 0 for success, -1 for
   failure */

short BirthDatabase::replace_birth( BIRTH_DB *data, RECT_DATA *rd )
{
 short len;
 char *old_key;

 if ( index == NULL )
    return( -1 );
 char *key = new char[NAME_WIDTH+1];
 if ( key == NULL ) {
    do_mem_error( 0 );
    return( -1 );
    }
 memset( buf, 0, sizeof(buf) );
 if ( !strcmpi( db_key, "" ) ) {
    strcpy( key, data->name );
    old_key = db_key;
    }
 old_key = db_key;
 strcpy( key, data->name );
 len = cvt_nbirthdb_2_dsk( data, (DBR *)buf, rd );
 if ( replace_rec( buf, key, old_key, len  ) == IX_OK ) {
    strcpy( db_key, key );
    delete key;
    has_Birth( 1 );
    return( 0 );
    }
 else {
    delete key;
    has_Birth( 0 );
    return( -1 );
    }
}

