#include <stdafx.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include "array.hpp"
#include <iostream.h>
#include <fstream.h>

#define BUF_SIZE 32000
#define COMP_SIZE 20000

// 7/8/94 CJN complete Conversion


#define END_OF_ARRAY 39
#define MAX_DEPTH 12

LST symbols[350];
dataArray3d *index3;
int num_cols, num_rows, num_depth, num_symbols;
unsigned bytes_saved = 0;
char *buffer;
char *inbuf;
char * comp_buf;
extern int compress_string( char *, char  *);

/* function to read text symbols from file text.sym into symbols
   listing. If symbols can't be read then program errors out.
   If successful, sets num_symbols to the number of items read */

static void read_symbols( char *file )
{
 FILE *stream;
#ifndef BSR
 int x = 0, test;
 char buf2[250], *p;
 char buf[100];

 if ( ( stream = fopen( "TEXT.SYM", "rt" ) ) == NULL ) {
    alert_box( "3DBLDTXT", "Can't Open \"TEXT.SYM\" File for Reading!\n" );
    Throw( j,  1 );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
       setvbuf( stream, NULL, _IOFBF, 256 );
    }
 do {
    if (( test = fgetc( stream ) ) == EOF ) {
       fclose( stream );
       num_symbols = x;
       }
    else if ( test == '#' ) {
       fgets( buf, 99, stream );
       continue;
       }
    else
       ungetc( test, stream );
    p = fgets( buf2, 149, stream );
    test = sscanf( buf2, "%17s %d %d ", symbols[x].symbol,
	  &symbols[x].value, &symbols[x].col_used );
    if ( test != 3 && p == NULL ) {
       alert_box( "3DBLDTXT", "Error Reading Text Symbols!" );
       fclose( stream );
       Throw( j,  2 );
       }
    else
       ++x;
 } while ( !stream.bad() && !stream.eof() );
 fclose( stream );
 num_symbols = x;
 qsort( symbols, num_symbols, sizeof( LST ), strcmpi );
#else
 if ( ( stream = fopen( file, "rb" ) ) == NULL ) {
    alert_box( "3DBLDTXT","Can't Open \"%s\" For Reading!", file );
    Throw( j,  1 );
    }
 if ( fread( &num_symbols, 2, 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Reading \"%s\"!", file );
    Throw( j,  2 );
    }
 if ( fread( symbols, sizeof( LST ), num_symbols, stream ) != num_symbols ) {
    alert_box( "3DBLDTXT","Error Reading \"%s\"!", file );
    Throw( j,  3 );
    }
 fclose( stream );
#endif

}

/* function to read an array into memory. first it reads num_rows, and
   then num_cols, and them reads the array itself into memory. If file
   can't be opened then it is assumed it doesn't exist then it is created
   otherwise it is read. If it cannot be read correctly then the program
   errors out */

static void read_array( char *name )
{
 int x, y;
 FILE *stream;

 index3 = new dataArray3d( END_OF_ARRAY+1, END_OF_ARRAY+1,
       MAX_DEPTH, sizeof( TXTPT ) );
 if (( stream = fopen( name, "rb" ) ) == NULL ) {
    num_rows = 0;
    num_cols = 0;
    num_depth = 0;
    return;
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 if ( fread( &num_rows, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Reading NUM_ROWS!" );
    fclose( stream );
    Throw( j,  3 );
    }
 if ( fread( &num_cols, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Reading NUM_COLS!" );
    fclose( stream );
    Throw( j,  4 );
    }
 if ( fread( &num_depth, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Reading NUM_DEPTH!" );
    fclose( stream );
    Throw( j,  41 );
    }
 for ( x = 0; x < num_cols; ++x ) {
     for ( y = 0; y < num_rows; ++y ) {
	 dllYield();
	 if ( fread( index3->getPtr(x, y, 0), sizeof( TXTPT ),
	       num_depth, stream ) != num_depth ) {
	    alert_box( "3DBLDTXT","Error Reading INDEX[%d][%d][]!", x, y );
	    fclose( stream );
	    Throw( j,  5 );
	    }
	 }
     }
 fclose( stream );
}

static void write_array( char *file )
{
 int x, y;
 FILE *stream;

 if (( stream = fopen( file, "wb" ) ) == NULL ) {
    alert_box( "3DBLDTXT","Error Opening Array File \"%s\" to Write!", file );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 if ( fwrite( &num_rows, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Writing NUM_ROWS!" );
    fclose( stream );
    Throw( j,  7 );
    }
 if ( fwrite( &num_cols, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Writing NUM_COLS!" );
    fclose( stream );
    Throw( j,  8 );
    }
 if ( fwrite( &num_depth, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "3DBLDTXT","Error Writing NUM_DEPTH!" );
    fclose( stream );
    Throw( j,  41 );
    }

 for ( x = 0; x < num_cols; ++x ) {
     for ( y = 0; y < num_rows; ++y ) {
	 dllYield();
	 if ( fwrite( index3->getPtr(x, y, 0), sizeof( TXTPT ),
	       num_depth, stream ) != num_depth ) {
	    alert_box( "3DBLDTXT","Error Writing INDEX[%d][%d][]!", x, y );
	    fclose( stream );
	    Throw( j,  6 );
	    }
	 }
     }
 fclose( stream );
}

/* function that adjusts num_rows or num_cols. If Illegal returns
   END_OF_ARRAY */

static int adjust_num( int val, int col, int count )
{
 switch( col ) {
 case 1 :
      if ( val >= num_cols && val < END_OF_ARRAY )
	 num_cols = val+1;
      else if ( val == END_OF_ARRAY ) {
	 alert_box( "3DBLDTXT","Illegal Symbol Value = %d Text Chunk # = %d", val, count );
	 return( END_OF_ARRAY );
	 }
      return( val );
      break;
 case 2 :
 case 4 :
      if ( val >= num_rows && val < END_OF_ARRAY )
	 num_rows = val+1;
      else if ( val == END_OF_ARRAY ){
	 alert_box( "3DBLDTXT","Illegal Symbol Value = %d Text Chunk # = %d", val, count );
	 return( END_OF_ARRAY );
	 }
      return( val );
      break;
 case 3 :
      if ( val >= num_depth && val < MAX_DEPTH )
	 num_depth = val+1;
      else if ( val == END_OF_ARRAY ) {
	 alert_box( "3DBLDTXT","Illegal Symbol Value = %d Text Chunk # = %d", val, count );
	 return( MAX_DEPTH );
	 }
      return( val );
      break;
 default :
      alert_box( "3DBLDTXT","Illegal Symbol Position = %d Text Chunk # = %d", col, count );
      return( END_OF_ARRAY );
      break;
      }
}

static int _cdecl matchsym( const void *s1, const void *s2 )
{
 int r;
 LST *l1, *l2;

 l1 = (LST *)s1;
 l2 = (LST *)s2;
 if ( !( r = strcmpi( l1->symbol, l2->symbol )) )
    return( l1->col_used - l2->col_used );
 else
    return( r );
}

/* function to find a symbol in table and return the integer
   value defined for it. If the symbol is in the wrong column,
   then an error is reported, and END_OF_SYMBOL is returned, same
   is true if symbol is not found. First if symbol converts to an
   int that is returned. If symbol is found and the num_rows or
   num_cols is less than this variable then the appropriate
   number of rows or cols is increased */

static int find_symbol( char *symbol, int pos, int count )
{
 LST sym;
 int val;
 LST *ptr;

 val = atoi( symbol );
 if ( val != 0 || *symbol == '0' ) {
    val = adjust_num( val, pos, count );
    return( val );
    }
 strcpy( sym.symbol, symbol );
 if ( pos == 2 )
    sym.col_used = 4;
 else
    sym.col_used = pos;
 if ( ( ptr = ( struct LST *) bsearch( &sym, symbols, num_symbols,
      sizeof( LST ), matchsym ) ) == NULL ) {
    alert_box( "3DBLDTXT","Symbol %s Not Found! Text Chunk # = %d", symbol, count );
    return( END_OF_ARRAY );
    }
 if ( ptr->col_used != 4 && pos != ptr->col_used ) {
    alert_box( "3DBLDTXT","Illegal Symbol Position %d: Text Chunk # = %d", pos, count );
    return( END_OF_ARRAY );
    }
 val = adjust_num( ptr->value, pos, count );
 return( val );
}
/* function to read the control string if found in the read function.
   Returns col & row via pointers. Returns 1 for success, 0 for
   failure to read data properly */

static int read_ctl_string( ifstream &stream, int *row, int *col, int *deep, int count )
{
 char buf[250];
 char symbol1[25], symbol2[25], symbol3[25];

 stream >> symbol1 >> symbol2 >> symbol3;
 stream.getline( inbuf, IN_BUF_SIZE-1 );
 strcat(inbuf,"\n" );
 if ( stream.bad() || stream.eof() ) {
    alert_box( "3DBLDTXT","Error Reading Index String! Text Chunk # = %d", count );
    *row = END_OF_ARRAY;
    *col = END_OF_ARRAY;
    *deep = MAX_DEPTH;
    return( FAIL );
    }
 *col = find_symbol( symbol1, 1, count );
 *row = find_symbol( symbol2, 2, count );
 *deep = find_symbol( symbol3, 3, count );
 if ( *col == END_OF_ARRAY || *row == END_OF_ARRAY || *deep == END_OF_ARRAY )
    return( FAIL );
 return ( 1 );
 }

/* function to read a record. A record consists of a ctl_string and
   the text that follows. Text has been previously concatenated by
   textcomp.exe (textcomp.c) so that each paragraph or line (where
   indicated for line-for-line) is one line. function reads and
   concatenates all text up to #mark indicating next record. Assumes
   that we are at start of record and the # mark has been read.
   returns via pointers row and col. Returns 1 for success, 0
   for failure */

static int read_record( ifstream &stream, int *row, int *col, int *deep, int count )
{
 int read_c;

 dllYield();
 if ( !read_ctl_string( stream, row, col, deep, count ) )
    return( FAIL );
 stream.getline( inbuf, IN_BUF_SIZE-1 );
 strcat( inbuf, "\n" );
 if ( stream.fail() ) {
    alert_box( "3DBLDTXT","Error Reading: Text Chunk # = %d", count );
    return( FAIL );
    }
 inbuf[IN_BUF_SIZE-1] = '\0';
 strcpy( buffer, inbuf );
 do {
     read_c = stream.get();
     if ( stream.eof() || stream.bad() || stream.fail()  ) {
        if ( stream.eof() )
	       return( SUCCEED );
        else if ( stream.bad() || stream.fail() ) {
	       alert_box( "3DBLDTXT","Error Reading: Text Chunk # = %d", count );
           return( FAIL );
           }
        }   
    if ( read_c == '#' )
       return( SUCCEED );
    else if ( read_c == '@' ) {
       stream.getline( inbuf, IN_BUF_SIZE-1 );
       continue;
       }
    else
       stream.putback( read_c );
    stream.getline( inbuf, IN_BUF_SIZE-1 );
    strcat( inbuf, "\n" );
    if ( stream.bad() || stream.fail() ) {
	   alert_box( "3DBLDTXT","Error Reading: Text Chunk # = %d", count );
	   return( FAIL );
	   }
    inbuf[IN_BUF_SIZE-1] = '\0';
    strcat( buffer, inbuf );
    } while( !stream.eof() );
 return( SUCCEED );
}

/* function to put text in buffer out to text output file. Also sets up
   info in index3 with offset and length. returns 0 for error 1 for SUCCEED
   NOTE: output file should be opened in "r+b" mode. A fseek( stream,
   0, SEEK_END ) should be called at start of program
   */

static int put_text( FILE *stream, int row, int col, int deep, int count )
{
 long offset;
 int length;

 offset = ftell( stream );
 if ( offset == -1L ) {
    alert_box( "3DBLDTXT","Errpr Getting Offset to Text File!" );
    return( FAIL );
    }
 doConvertText( buffer, _CVT_T_, _DST_T_ );
 bytes_saved += compress_string( buffer, comp_buf );
 length = strlen( comp_buf );
 if ( fputs( comp_buf, stream ) ) {
    alert_box( "3DBLDTXT","Error Writing To Output File!" );
    return( FAIL );
    }
 fflush( stream );
 TXTPT *t = (TXTPT *)index3->getPtr(col, row, deep);
 t->starts_at = offset;
 t->length = length;
 return( SUCCEED );
}

extern "C" {

int __declspec(dllexport) WINAPI   _3DBLDTXT( int argc, char *argv[] )
{
 char outtext[65], outindex[65], syscmd[85], sysprog[12];
 char infile[65], xbuf[50];
 FILE *outstream;
 int test, last, row, col, deep, noer, count, val;

 bytes_saved = 0;
 if ( ( val = Catch( j ) ) ) {
    if ( buffer != NULL ) {
       delete buffer;
       buffer = NULL;
       }
    if ( comp_buf != NULL ) {
       delete comp_buf;
       comp_buf = NULL;
       }
    if ( inbuf != NULL ) {
       delete inbuf;
       inbuf = NULL;
       }
    if ( index3 != NULL ) {
       delete index3;
       index3 = NULL;
       }
    return( val );
    }
 if ( argc < 3 ) {
    alert_box( "3DBLDTXT","Syntax: BUILDTXT infile.ext outfile FMT T|X SYMBOL.BSM\n"
       "Where FMT is WS, WP4, WP5, RTF, or ASC,\n"
       "and T (indicates Translate) or X (Don't Translate) are indicated,\n"
       "The Last Argument is the BSM file generated by MKBSM, default is TEXT.BSM." );
    return( -1 );
    }
 strcpy( outtext, argv[2] );
 strcat( outtext, ".TXT" );
 strcpy( outindex, argv[2] );
 strcat( outindex, ".NDX" );
 if ( argc > 5 ) {
    read_symbols(argv[5]);
    }
 else
    read_symbols("TEXT.BSM");
 read_array( outindex );
 if ( argc > 3 ) {
    strcpy( sysprog, argv[3] );
    strcat( sysprog, "TOAST" );
    if ( strcmpi( argv[3], "AST" ) && strcmpi( argv[3], "DOC" )  ) {
       execFunction( sysprog, sysprog, argv[1], "BLDTX$$$.TMP" );
       if ( getFunctionRet() ) {
	  alert_box( "3DBLDTXT","Error Processing With %s", sysprog );
	  return( 10 );
	  }
       strcpy( infile, "BLDTX$$$.TMP" );
       }
    else
       strcpy( infile, argv[1] );
    }
 else
    strcpy( infile, argv[1] );
 if ( argc > 4 ) {
    if ( !strcmpi( argv[4], "T" ) ) {
       strcpy( sysprog, "STRTABLE" );
       execFunction( sysprog, sysprog, infile, "BLDT$$$$.TMP" );
       if ( getFunctionRet() ) {
	  alert_box( "3DBLDTXT","Error Processing With STRTABLE" );
	  return( 10 );
	  }
       unlink( "BLDTX$$$.TMP" );
       strcpy( xbuf, "BLDTX$$$.TMP" );
       if ( rename( "BLDT$$$$.TMP", xbuf ) ) {
	  alert_box( "3DBLDTXT", "Can't Reaname Translated File to Input Temporary File!" );
	  return( 11 );
	  }
       strcpy( infile, "BLDTX$$$.TMP" );
       }
     }
 ifstream instream( infile, ios::in|ios::nocreate );
 if ( instream.fail()||instream.bad() ) {
    alert_box( "3DBLDTXT","Can't Open Input File %s!", infile );
    return( 11 );
    }
 if ( ( outstream = fopen( outtext, "ab" ) ) == NULL ) {
    alert_box( "3DBLDTXT","Can't Open Output Text File \"%s\"!", outtext );
    instream.close();
    return( 12 );
    }
 if ( fseek( outstream, 0L, SEEK_END ) ) {
    alert_box( "3DBLDTXT","Trouble on Output File" );
    instream.close();
    fclose( outstream );
    return( 13 );
    }
 last = test = '\n';
 if ( setvbuf( outstream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( outstream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( outstream, NULL, _IOFBF, 1024 ) )
	  setvbuf( outstream, NULL, _IOFBF, 256 );
       }
    }
 buffer = new char[BUF_SIZE];
 inbuf = new char[IN_BUF_SIZE];
 comp_buf = new char[COMP_SIZE];
 buffer[BUF_SIZE-1]='\0';
 inbuf[IN_BUF_SIZE-1]='\0';
 comp_buf[COMP_SIZE-1]='\0';
 
 while ( !(test = ( instream.get() ) == '#' && last == '\n' ) &&
	       !instream.eof() && !instream.bad() )
       last = test;
 noer = 1; count = 0;
 while ( !instream.eof() && !instream.bad() && noer ) {
       noer = read_record( instream, &row, &col, &deep, count );
       dllYield();
       if ( noer )
	  noer = put_text( outstream, row, col, deep, count );
       ++count;
       }
 instream.close();
 fclose( outstream );
 unlink( "BLDTX$$$.TMP" );
 LogPrintf( "Bytes Saved by Compression = %u\n", bytes_saved );
 if ( noer ) {
    write_array( outindex );
    delete buffer;
    buffer = NULL;
    delete inbuf;
    inbuf = NULL;
    delete comp_buf;
    comp_buf = NULL;
    delete index3;
    index3 = NULL;
    return( 0 );
    }
 delete buffer;
 buffer = NULL;
 delete inbuf;
 inbuf = NULL;
 delete comp_buf;
 comp_buf = NULL;
 delete index3;
 index3 = NULL;
 return( 14 );
}
}
