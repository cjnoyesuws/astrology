#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_

#ifndef _DIREC____HPP_
#include "paths.hpp"
#endif

#ifndef IX_OK
#include "asbplus.h"
#endif

#ifndef _FREESP___HPP_
#include "freesp.hpp"
#endif

#ifndef _CHARCONS_H___
#include "charcons.h"
#endif

#define FAIL     -1
#define SUCCEED  0


#define COUNTRY_INDEX   (char *) set_path( LOCATION_INDEX_name, DATABASE_F )
#define STATE_INDEX   (char *) set_path( LOCATION_INDEX_name, DATABASE_F )
#define LOCATION_INDEX   (char *) set_path( LOCATION_INDEX_name, DATABASE_F )
#define LOCATION_DATA    (char *) set_path( LOCATION_DATA_name, DATABASE_F )
#define BIRTHBAS_INDEX   (char *) set_path( BIRTHBAS_INDEX_name, DATABASE_F )
#define BIRTHBAS_DATA    (char *) set_path( BIRTHBAS_DATA_name, DATABASE_F )
//#define LOCATION_POPUP   (char *) set_path( LOCATION_POPUP_name, DATABASE_F )
//#define BIRTHBAS_POPUP   (char *) set_path( BIRTHBAS_POPUP_name, DATABASE_F )
//#define LOC_POPUP_INDEX  (char *) set_path( LOC_POPUP_INDEX_name, DATABASE_F )

class Database {
protected:
      char dataName[150];
      char indexName[150];
      long fail_rec;
      short  fail_len;
      IX_DESC  *index;
      FreeBlock frees;
      short flags;
      ENTRY id;
public:
      Database(char  *dname, char  *iname);
      ~Database() {}
      void key_error( char *key, char *msg );
      // low level functions
      long write_rec( short size, long offset, void *data );
      short read_rec( short size, long offset, void *data );
      short del_rec( long o, short l );
      short startup();
      void shutdown();
      // high level access
      short add_write_rec( void *data, char *key, short width );
      short replace_rec( void *data, char *key, char *old_key, short width );
      short get_rec(void *data, char *key );
      short delete_rec( char *key );
      virtual void  buildDataKey( void *data ) {};
      virtual short reIndex( char *prompt="...REINDEXING DATABASE...",
		 short size=(sizeof(BIRTH_DB)+sizeof(RECT_DATA)+10) );
      virtual short mergeIndex(char *prompt="...MERGING DATABASE...",
	   char *ftype="Database File to Merge",
	   short dlen=(sizeof(BIRTH_DB)+sizeof(RECT_DATA)+10) );
      };

class LocDatabase : public Database {
protected:
      IX_DESC *country_index;
	  IX_DESC *state_index;
//      IX_DESC  *popup;
//      char popupName[150];
	  char *countryindexname;
	  char *stateindexname;
	  char country_key[COUNTRY_WIDTH+1];
	  char state_key[COUNTRY_WIDTH+STATE_WIDTH+1];
      char db_key[COUNTRY_WIDTH+STATE_WIDTH+LOCATION_WIDTH+1];
      char buf[sizeof(LOC_DB)+10];
public:
      LocDatabase(char  *dname  = LOCATION_DATA_name,
	  char  *iname = LOCATION_INDEX_name,
	  char  *ctname = COUNTRY_INDEX_name, char *stname = STATE_INDEX_name);
      ~LocDatabase() {}
      short startup();
      void shutdown();
      long find_loc( char *co, char *st, char *lo, char *which, short fShEr = 0 );
      char *make_key( char *co, char *st, char *lo );
      short write_loc( LOC_DB *data );
      short read_loc( char *country, char *state, char *location, LOC_DB *data );
      short delete_loc( char *country, char *state, char *location );
      short replace_loc( LOC_DB *data );
      virtual void  buildDataKey( void *data );
      virtual short reIndex( char *prompt="...REINDEXING DATABASE...",
		 short size=(sizeof(LOC_DB) );
      virtual short mergeIndex(char *prompt="...MERGING DATABASE...",
	   char *ftype="Database File to Merge",
	   short dlen=(sizeof(LOC_DB) ) );
	  short has_Loc() { return( flags == 1 ); }
      void has_Loc(short f) {  if ( f )
				  flags = 1;
			       else
				  flags = 0;
			       }
      };

class BirthDatabase : public Database {
      char db_key[NAME_WIDTH+1];
      char buf[sizeof(BIRTH_DB)+sizeof(RECT_DATA)+10];
public:
      BirthDatabase(char  *dname = BIRTHBAS_DATA_name,
	   char  *iname = BIRTHBAS_INDEX_name);
      ~BirthDatabase() {}
      short write_birth( BIRTH_DB *data, RECT_DATA *rd );
      short read_birth( char *name, BIRTH_DB *data, RECT_DATA *rd );
      short delete_birth( char *name );
      short replace_birth( BIRTH_DB *data, RECT_DATA *rd );
      virtual void  buildDataKey( void *data );
//      short makePopup();
      short has_Birth() { return( flags == 2 ); }
      void has_Birth(short f) {  if ( f )
				  flags = 2;
			       else
				  flags = 0;
			       }
      };


#endif /* _DATABASE_HPP_ */
