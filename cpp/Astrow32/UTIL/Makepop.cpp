#include "stdafx.h"
#include <stdlib.h>
#include <share.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "database.hpp"
#include "dbstruct.h"
#include "errors.fns"
#include <assert.h>
#include "basedcs.h"
#include "charcons.h"
#include "astrow.h"
#include "procmsg.h"


extern char *strclip( char *s );

#define ITEM_LEN (NAME_WIDTH+2)

#define LIST_LEN 3500

typedef char item[ITEM_LEN];

static char st[STATE_WIDTH+1];

/* Program to read indexes and create popup lists and store
   them in a file and create an index to them. */
 
class Itemlst {
      item *list;
      short  list_count;
      short  list_max;
      short  width;
      char *file;
      FILE *stream;
public:
      Itemlst( int max = LIST_LEN ) { list_max = max; list_count = 0; list = NULL; width = 0; }
      ~Itemlst();
      int alloc();
      void clear();
      void setFiles( char *f, FILE *s ) { file = f; stream = s; }
      long write();
      void add( char *item );
      void padd();
      int count() { return list_count; }
      };

class LocDatabMPU : public LocDatabase {  // class purely to make popups
private:
      Itemlst *pLst;
      ProcMsg *pm;
	  int _break;
	  char pmbuf[150];
      char statebuf[75];
      int doCountries();
      int doStates();
      int doCountryStates();
      int doLocations();
      int doStateLoc();
      char *mkTxt( char *pr, char *s ) { strcpy( pmbuf, pr );
					 strcat( pmbuf, s );
					 assert(strlen(pmbuf) < sizeof(pmbuf));
					 return pmbuf; }
public:
      LocDatabMPU() : LocDatabase() {_break = 0;}
      ~LocDatabMPU() { delete pLst; delete pm; }
      int makePopup();
      int makePopup( char *country, char *state );
      };

/* Function to close all index files and . Exits with variable
   state as return value */





/* function to empty list and set counter to 0 */

void Itemlst::clear()
{
 int x;

 for ( x = 0; x <= list_count; ++x )
     *((char *)list[x]) = '\0';
 list_count = 0;
 width = 0;
}

Itemlst::~Itemlst()
{
      delete [] list;
}

void Itemlst::padd()
{
 char *p;
 int x, l;

 for ( x = 0; x <= list_count; ++x ) {
     p = ((char *)list[x]);
     l = strlen( p );
     memset( p+l, ' ', width-l );
     p[width] = '\0';
     }
}

/* function to write list out to disk file. file is name. width is
   width of item to write. Function returns offset of that group 
   for indexing purposes. First writes list_count to file then
   each array of width from list up to list_count members, returns
   -1L for error */

long Itemlst::write()
{
 long fpt;
 int x;

 if ( fseek( stream, 0L, SEEK_END ) ) {
    do_error( file );
    return( -1L );
    }
 if ( ( fpt = ftell( stream ) ) == -1L ) {
    do_error( file );
    return( -1L );
    }
 if ( fwrite( &list_count, sizeof( short ), 1, stream ) != 1 ) {
    do_error( file );
    return( -1L );
    }
 x = width+1;
 if ( fwrite( &x, sizeof( short ), 1, stream ) != 1 ) {
    do_error( file );
    return( -1L );
    }
 padd();
 for ( x = 0; x < list_count; ++x ) {
     if ( fwrite( list[x], width+1, 1, stream ) != 1 ) {
        do_error( file );
	return( -1L );
        }
     }
 return( fpt );
}

/* function to add an item to the list. Copies the item to the
   list and increments the list_count */

void Itemlst::add( char *item)
{
 int l = strlen( item )+1;                                                   

 if ( l > width )                                                                      
    width = l;
 if ( list_count >= list_max) {
    alert_box( "WARNING!!", "Maximum Size of List Reached, No More Can Be Added!" );
    return;
    }
 strcpy( (char *)(&list[list_count]), item );
 ++list_count;
}


int Itemlst::alloc()
{
 list = new item[list_max];
 if ( list == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 memset(list,0,ITEM_LEN*list_max);
 return( 1 );
}



/* function to process the birth database index and create popup.
   Returns the value 0 for success non-zero otherwise */

short BirthDatabase::makePopup()
{
 int ret, doshut;
 char *fname;
 FILE *stream;
 int _break = 0;
 static char msg1[] = "...MAKING BIRTH POPUP...";
 static char msg2[] = "Failed first key function";

 if ( index != NULL )
    doshut = 0;
 else
    doshut = 1;
 if ( index == NULL && !startup() )
    return( IX_ERROR );
 fname = BIRTHBAS_POPUP;
 Itemlst *pLst = new Itemlst(1000);
 
 if ( !pLst->alloc() ) {
    delete pLst;
    if ( doshut )
       shutdown();
    return( IX_ERROR );
    }
 if ( first_key( index ) != IX_OK ) {
    key_error( BIRTHBAS_INDEX, (char *)msg2 );
    if ( doshut )
       shutdown();
    delete pLst;
    return( IX_ERROR );
    }
 ProcMsg(msg1, &_break);
 ret = next_key( &id, index );
 while ( ret == IX_OK ) {
       pLst->add( id.key );
       ret = next_key( &id, index );
       ((CAstrowApp *)AfxGetApp())->_Yield();
       if (_break) {
	      if ( doshut )
             shutdown();
          delete pLst;
          return( IX_OK  );
	      }
       }  
 if ( pLst->count() ) {
    if ( ( stream = fopen( fname, "wb" ) ) == NULL ) {
       do_error( fname );
       delete pLst;
       if ( doshut )
	      shutdown();
       return( IX_ERROR );
       }
    pLst->setFiles( fname, stream );
    pLst->write();
    fclose( stream );
    }
 if ( doshut )
    shutdown();
 delete pLst;
 return( IX_OK  );
}

int LocDatabMPU::makePopup()
{
 int ret;
 char *fname;
 FILE *stream;
 static char msg1[] = "...MAKING LOCATION POPUPS...";
 static char msg2[] = "...COUNTRY POPUP COMPLETED...";
 static char msg3[] = "...STATES POPUPS COMPLETED...";
 static char msg4[] = "...LOCATIONS POPUPS COMPLETED...";
 _break = 0;
 unlink(popupName);  // the index
 if ( !startup() )
    return( IX_ERROR );
 fname = LOCATION_POPUP;
 if ( ( stream = fopen( fname, "wb" ) ) == NULL ) {
    do_error( fname );
    shutdown();
    free_index_mem();
    return( IX_ERROR );
    }
 pLst = new Itemlst();
 if ( !pLst->alloc() ) {
    fclose( stream );
    shutdown();
    free_index_mem();
    return( IX_ERROR );
    }
 ((CAstrowApp *)AfxGetApp)->_Yield();
 pLst->setFiles( fname, stream );
 pm = new ProcMsg(msg1,&_break);
 if ( _break )
	goto quit;
 if ( doCountries() != IX_OK )
    goto quit;
 ((CAstrowApp *)AfxGetApp)->_Yield();
 if ( _break )
	goto quit;
 pm->setText(msg2);
 pLst->clear();
 if ( doStates() != IX_OK )
    goto quit;
 ((CAstrowApp *)AfxGetApp)->_Yield();
 if ( _break )
   goto quit;
 pm->setText(msg3);
 pLst->clear();
 doLocations();
 pm->setText(msg4);
 quit:
 fclose( stream );
 shutdown();
 free_index_mem();
 return( IX_OK  );
}

/* function to write countries out to list. Goes through index looking
   for unique countries. Adds then to the list, padds them out to the
   proper width, and then writes them to disk. The countries are the
   first entry in the LOCATION.LST file so no index entry is needed. 
   Returns 0 for success, non-zero for error */

int LocDatabMPU::doCountries()
{
 char *fs;
 short ret;

 if ( first_key( index ) != IX_OK ) {
    key_error( LOCATION_INDEX, "Failed first key function" );
    return( IX_ERROR );
    }
 ret = next_key( &id, index );
 db_key[0] = '\0';
 while ( ret == IX_OK ) {
       ((CAstrowApp *)AfxGetApp)->_Yield();
	   fs = strchr( id.key, '\1' );
       if ( fs != NULL )
	      *fs = '\0';
       if ( strcmpi( id.key, db_key ) )  {
	      pLst->add( id.key );
          }
       strcpy( db_key, id.key );
       if ( fs != NULL )
	      *fs = '\1';
       ret = next_key( &id, index );
       }  
 if ( pLst->write() == -1L )
    return( IX_ERROR );
 else
    return( IX_OK  );
}

/* function to do all the states calling do_country_state().
   Returns 0 for success, -1 for failure */

int LocDatabMPU::doStates()
{
 short ret;
 static char msg1[] = "Failed first key function";

((CAstrowApp *)AfxGetApp)->_Yield();
 if ( first_key( index ) != IX_OK ) {
    key_error( LOCATION_INDEX, (char *)msg1 );
    return( IX_ERROR );
    }
 while( ( ret = doCountryStates() ) == IX_OK );
 if ( ret == IX_ERROR )
    return( IX_ERROR );
 else
    return( IX_OK  );
}

/* function to do a single group of states in one country. While
   within that country, continues to look for more states. If there
   are any states (there should be at least one "General", in each
   country), the function writes them out to disk and adds the 
   country name to the pop_list index. Returns 0 for success,
   -1 for error, and 1 for end of index reached */

int LocDatabMPU::doCountryStates()
{
 short ret;
 long fptr;
 char country[COUNTRY_WIDTH+5], *fs, *fs2;
 static char msg1[] = "DOING STATES FOR COUNTRY: ";

 ret = next_key( &id, index );
 db_key[0] = '\0';
 country[0] = '\0';
 pLst->clear();
 fs = strchr( id.key, '\1' );
 if ( fs != NULL )
    *fs = '\0';
 else
    return( IX_FAIL );
 strclip( id.key );
 strcpy( country, id.key );
 pm->setText(mkTxt(msg1,country));
 while ( ret == IX_OK && !strcmpi(country, id.key ) ) {
       ((CAstrowApp *)AfxGetApp)->_Yield();
       if ( fs != NULL ) {
	      *fs = '\1';
	      fs2 = strchr( fs+1, '\1' );
	      if ( fs2 != NULL ) {
	         *fs2 = '\0';
	         strclip( id.key );
	         }
	      if ( strcmpi( id.key, db_key ) )  {
	         pLst->add( fs+1 );
	         }
	      }
       strcpy( db_key, id.key );
       if ( fs2 != NULL )
	      *fs2 = '\1';
       ret = next_key( &id, index );
       if ( ret != IX_OK )
	      break;
       fs = strchr( id.key, '\1' );
       if ( fs != NULL ) {
	      *fs = '\0';
	      strclip( id.key );
	      }
       }
 prev_key( &id, index );
 if ( ( fptr = pLst->write() ) == -1L )
    return( IX_ERROR );
 strcpy( id.key, "1:" );
 strcat( id.key, country );
 strclip( id.key );
 id.recptr = fptr;
 id.data_len = -1;
 if ( add_key( &id, popup ) != IX_OK )
    return( IX_ERROR );
 else if ( ret == EOIX )
    return( IX_FAIL );
 else 
    return( IX_OK  );
}

/* function to do all the locations calling do_state_loc().
   Returns 0 for success, -1 for failure */

int LocDatabMPU::doLocations()
{
 static char msg1[] = "Failed first key function";
 short ret;

 strcpy( statebuf, "" );
 if ( first_key( index ) != IX_OK ) {
    key_error( LOCATION_INDEX, (char *)msg1 );
    return( IX_ERROR );
    }
 while( ( ret = doStateLoc() ) == IX_OK );
 if ( ret == IX_ERROR )
    return( IX_ERROR );
 else
    return( IX_OK  );
}

/* function to do a single group of locations in one state. While
   within that state, continues to look for more locations. If there
   are any locations (there should be at least one "General", in each
   state), the function writes them out to disk and adds the 
   country name to the pop_list index. Returns 0 for success,
   -1 for error, and 1 for end of index reached */

int LocDatabMPU::doStateLoc()
{
 ENTRY id;
 short ret;
 long fptr;
 char country_state[COUNTRY_WIDTH+STATE_WIDTH+5], *fs, *fs2;
 int width;
 static char msg1[] = "DOING LOCATIONS FOR STATE: ";

 ret = next_key( &id, index );
 if ( ret != IX_OK )
    return( ret );
 db_key[0] ='\0';
 pLst->clear();
 strclip( id.key );
 fs = strchr( id.key, '\1' );
 if ( fs == NULL )
    return( IX_FAIL );
 fs2 = strchr( fs+1, '\1' );
 if ( fs == NULL || fs2 == NULL )
    return( IX_FAIL );
 if ( fs2 != NULL ) {
    *fs2 = '\0';
    strclip( id.key );
    }
 strcpy( country_state, id.key );
 *fs = '\0';
 if ( strcmp( statebuf, fs+1 ) ) {
    pm->setText(mkTxt(msg1, fs+1 ));
	strcpy( statebuf, fs+1 );
    }
 *fs = '\1';
 while ( ret == IX_OK && !strcmpi(country_state, id.key ) ) {
       ((CAstrowApp *)AfxGetApp)->_Yield();
	   pLst->add( fs2+1 );
       *fs2 = '\1';
       ret = next_key( &id, index );
       if ( ret != IX_OK )
	      break;
       fs = strchr( id.key, '\1' );
       if ( fs == NULL )
	      break;
       fs2 = strchr( fs+1, '\1' );
       if ( fs2 != NULL ) {
	      strclip( id.key );
	      *fs2 = '\0';
	      }
       }
 prev_key( &id, index );
 if ( ( fptr = pLst->write() ) == -1L )
    return( IX_ERROR );
 strcpy( id.key, "2:" );
 strcat( id.key, country_state );
 strclip( id.key );
 id.recptr = fptr;
 id.data_len = -1;
 if ( add_key( &id, popup ) != IX_OK )
    return( IX_ERROR );
 else if ( ret == EOIX )
    return( IX_FAIL );
 else 
    return( IX_OK  );
}


void make_pop( char *which )
{
 if ( !strcmpi( which, "BIRTH" ) || !strcmpi( which, "ALL" ) )  {
    BirthDatabase *pbd = new BirthDatabase();
    pbd->makePopup();
    delete pbd;
    }
 if ( !strcmpi( which, "LOC" ) || !strcmpi( which, "ALL" ) )  {
    LocDatabMPU *pld = new LocDatabMPU();
    pld->makePopup();
    delete pld;
    }
}

/*
int LocDatabase::makePopup( char *country, char *state )
{
 ENTRY id;
 short ret;
 long fptr;
 char country_state[COUNTRY_WIDTH+STATE_WIDTH+5], *fs, *fs2;
 int width;
 static char BCS msg1[] = "DOING LOCATIONS FOR STATE: ";
 int ret;
 char *fname;
 FILE *stream;
 int _break = 0;
 static char BCS msg1[] = "...MAKING LOCATION POPUP...";
 static char BCS msg2[] = "Failed first key function";

 fname = LOCATION_POPUP;
 Itemlst *pLst = new Itemlst(500);
 if ( !pLst->alloc() ) {
    delete pLst;
    shutdown();
    return( IX_ERROR );
    }
 zYield();
 ProcMessage *pm = new ProcMessage((char _far *)msg1, &_break);
 if ( _break )
    goto quit;

 ret = next_key( &id, index );
 db_key[0] ='\0';
 pLst->clear();
 strclip( id.key );
 fs = strchr( id.key, '\1' );
 fs2 = strchr( fs+1, '\1' );
 if ( fs2 != NULL ) {
    *fs2 = '\0';
    strclip( id.key );
    }
 strcpy( country_state, id.key );
 *fs = '\0';
 if ( strcmp( statebuf, fs+1 ) ) {
    pm->setText( mkTxt( (char _far *)msg1, fs+1 ) );
    strcpy( statebuf, fs+1 );
    }
 *fs = '\1';
 while ( ret == IX_OK && !strcmpi(country_state, id.key ) ) {
       zYield();
       pLst->add( fs2+1 );
       *fs2 = '\1';
       ret = next_key( &id, index );
       fs = strchr( id.key, '\1' );
       fs2 = strchr( fs+1, '\1' );
       if ( fs2 != NULL ) {
	  strclip( id.key );
	  *fs2 = '\0';
	  }
       }
 prev_key( &id, index );
 if ( ( fptr = pLst->write() ) == -1L )
    return( IX_ERROR );
 strcpy( id.key, "2:" );
 strcat( id.key, country_state );
 strclip( id.key );
 id.recptr = fptr;
 id.data_len = -1;
 if ( add_key( &id, popup ) != IX_OK )
    return( IX_ERROR );
 else if ( ret == EOIX )
    return( IX_FAIL );
 else
    return( IX_OK  );

 if ( _break )
    goto quit;
 if ( pLst->count() ) {
    if ( ( stream = fopen( fname, "ab" ) ) == NULL ) {
       do_error( fname );
       delete pLst;
       shutdown();
       delete pm;
       return( IX_ERROR );
       }
    pLst->setFiles( fname, stream );
    pLst->write();
    fclose( stream );
    }
 strcpy( id.key, "2:" );
 strcat( id.key, country_state );
 strclip( id.key );
 id.recptr = fptr;
 id.data_len = -1;
 find_key( &id, popup );
 delete_key( &id, popup );
 if ( add_key( &id, popup ) != IX_OK )
    return( IX_ERROR );
 else if ( ret == EOIX )
    return( IX_FAIL );
 else
    return( IX_OK  );
 quit:
 delete pm;
 delete pLst;
 return( IX_OK  );
}

*/
