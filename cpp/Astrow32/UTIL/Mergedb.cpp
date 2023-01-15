/* routines for databases to merge one database into another  */
#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "useri.h"         
#include "dbstruct.h"
#include "database.hpp"
#include "errors.fns"
#include "charcons.h"
#include "astrow.h"
#include "procmsg.h"

short Database::mergeIndex(char *prompt, char *ftype, short dlen)
{
 FILE *stream, *src_stream;
 long offset;
 void *data;
 int x = 0, len, e;
 char src_file[250];
 int _break = 0;
 static char ftypes[] = { "Data Files (*.dat)|*.dat|All Files (*.*)|*.*||" };

 CFileDialog cfd(TRUE, ".dat", src_file, OFN_FILEMUSTEXIST, ftypes );
 cfd.m_ofn.lpstrTitle = prompt;
 if ( cfd.DoModal()==IDOK ) 
    strcpy( src_file, cfd.GetPathName() );
 else 
    return( IX_OK );
 data = new char[dlen];
 if ( data == NULL )
    do_mem_error(0);
 if ( !startup() )
    return( IX_OK );
 if ( ( stream = fopen( dataName, "ab" ) ) == NULL ) {
    do_error( dataName );
    delete data;
    return( IX_FAIL );
    }
 if ( ( src_stream = fopen( src_file, "rb" ) ) == NULL ) {
    do_error( src_file );
    quit:
    delete data;
    fclose( stream );
    shutdown();
    return( IX_FAIL );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( src_stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( src_stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( src_stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( src_stream, NULL, _IOFBF, 256 );
       }
    }
 fseek( src_stream, sizeof(short)+(20 * sizeof( FREE_SP )), SEEK_SET );
 fseek( stream, 0L, SEEK_END );
 offset = ftell( stream );
 ProcMsg pm(prompt, &_break);
 for ( ; !feof( src_stream ) && !ferror( src_stream ); offset += len, ++x ) {
     if ( (fread( &len, 2, 1, src_stream ) != 1) && !feof( src_stream )) {
	    do_error( src_file );
	    fclose( src_stream );
	    goto quit;
	    }
     if ( _break ) {
	    fclose( src_stream );
		goto quit;
	    }
	 if ( len < sizeof(D_LOC_DB)-L_WIDTH || len > dlen ) {
	    alert_box( ERROR2, "Possible Corrupted Data File len = %d, offset = %lx ", len, offset );
	    goto quit;
	    }
     if ( (fread( ((char *)data)+2, len-2, 1, src_stream ) != 1)
				    && !feof( src_stream ) ) {
	    do_error( src_file );
	    fclose( src_stream );
	    goto quit;
	    }
     ((CAstrowApp *)AfxGetApp())->_Yield();
	 *((short *)data) = len;
     if ( ((D_LOC_DB *)data)->freer == 1 )
	    continue;
     id.recptr = offset;
     id.data_len = len;
     if ( !feof( src_stream ) ) {
	    buildDataKey( data );
	    e = add_key( &id, index );
	    }
     if ( _break ) {
	    fclose( src_stream );
	    goto quit;
	    }
     if ( e == IX_OK ) {
	    if ( fwrite( data, len, 1, stream ) != 1 ) {
	       do_error( dataName );
	       fclose( src_stream );
	       goto quit;
	       }
	    }
     }
 delete data;
 fclose( src_stream );
 fclose( stream );
 shutdown();
 return( IX_OK );
}

short LocDatabase::mergeIndex(char *prompt, char *ftype, short dlen)
{
 FILE *stream, *src_stream;
 long offset;
 void *data;
 int x = 0, len, e;
 char src_file[250];
 int _break = 0;
 static char ftypes[] = { "Data Files (*.dat)|*.dat|All Files (*.*)|*.*||" };

 CFileDialog cfd(TRUE, ".dat", src_file, OFN_FILEMUSTEXIST, ftypes );
 cfd.m_ofn.lpstrTitle = prompt;
 if ( cfd.DoModal()==IDOK ) 
    strcpy( src_file, cfd.GetPathName() );
 else 
    return( IX_OK );
 data = new char[dlen];
 if ( data == NULL )
    do_mem_error(0);
 if ( !startup() )
    return( IX_OK );
 if ( ( stream = fopen( dataName, "ab" ) ) == NULL ) {
    do_error( dataName );
    delete data;
    return( IX_FAIL );
    }
 if ( ( src_stream = fopen( src_file, "rb" ) ) == NULL ) {
    do_error( src_file );
    quit:
    delete data;
    fclose( stream );
    shutdown();
    return( IX_FAIL );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( src_stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( src_stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( src_stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( src_stream, NULL, _IOFBF, 256 );
       }
    }
 fseek( src_stream, sizeof(short)+(20 * sizeof( FREE_SP )), SEEK_SET );
 fseek( stream, 0L, SEEK_END );
 offset = ftell( stream );
 ProcMsg pm(prompt, &_break);
 for ( ; !feof( src_stream ) && !ferror( src_stream ); offset += len, ++x ) {
     if ( (fread( &len, 2, 1, src_stream ) != 1) && !feof( src_stream )) {
	    do_error( src_file );
	    fclose( src_stream );
	    goto quit;
	    }
     if ( _break ) {
	    fclose( src_stream );
		goto quit;
	    }
	 if ( len < sizeof(D_LOC_DB) || len > dlen ) {
	    alert_box( ERROR2, "Possible Corrupted Data File len = %d, offset = %lx ", len, offset );
	    goto quit;
	    }
     if ( (fread( ((char *)data)+2, len-2, 1, src_stream ) != 1)
				    && !feof( src_stream ) ) {
	    do_error( src_file );
	    fclose( src_stream );
	    goto quit;
	    }
     ((CAstrowApp *)AfxGetApp())->_Yield();
	 *((short *)data) = len;
     if ( ((D_LOC_DB *)data)->freer == 1 )
	    continue;
     id.recptr = offset;
     id.data_len = len;
     if ( !feof( src_stream ) ) {
	    buildDataKey( data );
	    e = add_key( &id, index );
		strcpy( id.key, country_key );
		add_key( &id, country_index );
		strcpy( id.key, state_key );
		add_key( &id, state_index );
	    }
     if ( _break ) {
	    fclose( src_stream );
	    goto quit;
	    }
     if ( e == IX_OK ) {
	    if ( fwrite( data, len, 1, stream ) != 1 ) {
	       do_error( dataName );
	       fclose( src_stream );
	       goto quit;
	       }
	    }
     }
 delete data;
 fclose( src_stream );
 fclose( stream );
 shutdown();
 return( IX_OK );
}

void merge_index_db( char *which )
{
 if ( !strcmpi( which, "LOC" ) || !strcmpi( which, "ALL" ) ) {
    LocDatabase *pld = new LocDatabase();
    pld->mergeIndex("...MERGING LOCATION DATABASE...","Location Database File To Merge");
    delete pld;
    }
 if ( !strcmpi( which, "BIRTH" ) || !strcmpi( which, "ALL" ) ) {
    BirthDatabase *pbd = new BirthDatabase();
    pbd->mergeIndex("...MERGING BIRTH DATABASE...","Birth Database File To Merge");
    delete pbd;
    }
 return;
}
