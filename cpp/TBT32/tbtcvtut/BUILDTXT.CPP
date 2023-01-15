#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include "array.hpp"
#include <assert.h>
#include <iostream.h>
#include <fstream.h>

#define BUF_SIZE 32000
#define COMP_SIZE 20000

dataArray *index;

/* function to read text symbols from file text.sym into symbols
   listing. If symbols can't be read then program errors out.
   If successful, sets num_symbols to the number of items read */

static void read_symbols( char *file )
{
 FILE *stream;
#ifndef BSR
 int x = 0, test;
 char buf[100];
 char buf2[250], *p;

 if ( ( stream = fopen( "TEXT.SYM", "rt" ) ) == NULL ) {
    alert_box( "BUILDTXT", "Can't Open \"TEXT.SYM\" For Reading!" );
    Throw( j, 1 );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
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
    p = fgets( buf2, 249, stream );
    test = sscanf( buf2, "%17s %d %d ", symbols[x].symbol,
          &symbols[x].value, &symbols[x].col_used );
    if ( test != 3 && p == NULL ) {
       alert_box( "BUILDTXT", "Error Reading Symbols!" );
       fclose( stream );
       Throw( j, 2 );
       }
    else
       ++x;
 } while ( !ferror( stream ) && !feof( stream ) );
 fclose( stream );
 num_symbols = x;
 qsort( symbols, num_symbols, sizeof( LST ), strcmpi );
#else
 if ( ( stream = fopen( file, "rb" ) ) == NULL ) {
    alert_box( "BUILDTXT", "Can't Open \"%s\" For Reading!", file );
    Throw( j, 1 );
    }
 if ( fread( &num_symbols, 2, 1, stream ) != 1 ) {
    alert_box( "BUILDTXT", "Error Reading \"%s\"!", file );
    Throw( j, 2 );
    }
 if ( fread( symbols, sizeof( LST ), num_symbols, stream ) != num_symbols ) {
    alert_box( "BUILDTXT", "Error Reading \"%s\"!", file );
    Throw( j, 3 );
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
 int x;
 FILE *stream;

 index = new dataArray( END_OF_ARRAY+1, END_OF_ARRAY+1);
 if (( stream = fopen( name, "rb" ) ) == NULL ) {
    num_rows = 0;
    num_cols = 0;
    return;
    }
 if ( fread( &num_rows, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDTXT", "Error Reading NUM_ROWS!" );
    fclose( stream );
    Throw( j, 3 );
    }
 if ( fread( &num_cols, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDTXT", "Error Reading NUM_COLS!" );
    fclose( stream );
    Throw( j, 4 );
    }
  for ( x = 0; x < num_cols; ++x ) {
      dllYield();
      if ( fread( index->getPtr(x,0), sizeof( TXTPT ),
               num_rows, stream ) != num_rows ) {
	alert_box( "BUILDTXT", "Error Reading INDEX[%d][]!", x );
        fclose( stream );
	Throw( j, 5 );
        }
      }
 fclose( stream );
}

static void write_array( char *file )
{
 int x;
 FILE *stream;

 if (( stream = fopen( file, "wb" ) ) == NULL ) {
    alert_box( "BUILDTXT", "Error Opening Array File \"%s\" to Write!", file );
    }
 if ( fwrite( &num_rows, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDTXT", "Error Writing NUM_ROWS!" );
    fclose( stream );
    Throw( j, 7 );
    }
 if ( fwrite( &num_cols, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDTXT", "Error Writing NUM_COLS!" );
    fclose( stream );
    Throw( j, 8 );
    }
 for ( x = 0; x < num_cols; ++x ) {
     dllYield();
     if ( fwrite( index->getPtr(x, 0), sizeof( TXTPT ),
               num_rows, stream ) != num_rows ) {
	alert_box( "BUILDTXT", "Error Writing INDEX[%d][]!", x );
        fclose( stream );
	Throw( j, 9 );
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
	 alert_box( "BUILDTXT", "Illegal Symbol Value = %d Text Chunk # = %d", val, count );
         return( END_OF_ARRAY );
         }
      return( val );
      break;
 case 2 :
      if ( val >= num_rows && val < END_OF_ARRAY )
         num_rows = val+1;
      else if ( val == END_OF_ARRAY ){
	 alert_box( "BUILDTXT", "Illegal Symbol Value = %d Text Chunk # = %d", val, count );
         return( END_OF_ARRAY );
         }
      return( val );
      break;
 case 3 :
 default :
      alert_box( "BUILDTXT", "Illegal Col. = %d Text Chunk # = %d", col, count );
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
 sym.col_used = pos;
 if ( ( ptr = ( struct LST *) bsearch( &sym, symbols, num_symbols,
      sizeof( LST ), matchsym ) ) == NULL ) {
    alert_box( "BUILDTXT", "Symbol %s Not Found! Text Chunk # = %d", symbol, count );
    return( END_OF_ARRAY );
    }
 if ( pos != ptr->col_used/* && pos != 1 && ptr->col_used != 4*/ ) {
    alert_box( "BUILDTXT", "Illegal Symbol Position %d: Text Chunk # = %d", pos, count );
    return( END_OF_ARRAY );
    }
 val = adjust_num( ptr->value, pos, count );
 return( val );
}
/* function to read the control string if found in the read function.
   Returns col & row via pointers. Returns 1 for success, 0 for
   failure to read data properly */

static int read_ctl_string( ifstream &stream, int *row, int *col, int count )
{
 char buf[100];
 char symbol1[25], symbol2[25];

 stream >> symbol1 >> symbol2;
 stream.getline( inbuf, IN_BUF_SIZE-1 );
 strcat( inbuf, "\n" );
 if ( stream.bad() || stream.fail() ) {
    alert_box( "BUILDTXT", "Error Reading Index String! Text Chunk # = %d", count );
    *row = END_OF_ARRAY;
    *col = END_OF_ARRAY;
    return( FAIL );
    }
 *col = find_symbol( symbol1, 1, count );
 *row = find_symbol( symbol2, 2, count );
 if ( *col == END_OF_ARRAY || *row == END_OF_ARRAY )
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

static int read_record( ifstream &stream, int *row, int *col, int count )
{
 int read_c;

 dllYield();
 if ( !read_ctl_string( stream, row, col, count ) )
    return( FAIL );
 stream.getline(inbuf, IN_BUF_SIZE-1 );
 strcat( inbuf, "\n" );
 if ( stream.bad() || stream.fail() || stream.eof() ) {
    if ( stream.bad() || stream.fail() )
       alert_box( "BUILDTXT", "Error Reading Text: Text Chunk # = %d", count );
    return( FAIL );
    }
 inbuf[IN_BUF_SIZE-1] = '\0';
 strcpy( buffer, inbuf );
 do {
    read_c = stream.get();
    if ( ( stream.bad() || stream.fail() || stream.eof() ) ) {
       if ( stream.eof() )
          return( SUCCEED );
       else if ( stream.bad() || stream.fail() )
	  alert_box( "BUILDTXT", "Error Reading Text: Text Chunk # = %d", count );
       return( FAIL );
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
       if ( stream.bad() || stream.fail() )
	  alert_box( "BUILDTXT", "Error Reading Text: Text Chunk # = %d", count );
       else if ( stream.eof() && strlen(inbuf)==1 )
          return( SUCCEED );
       return( FAIL );
       }
    inbuf[IN_BUF_SIZE-1] = '\0';
    strcat( buffer, inbuf );
    } while( !stream.eof() );
 return( SUCCEED );
}

/* function to put text in buffer out to text output file. Also sets up
   info in index with offset and length. returns 0 for error 1 for SUCCEED
   NOTE: output file should be opened in "r+b" mode. A fseek( stream,
   0, SEEK_END ) should be called at start of program
   */

static int put_text( FILE *stream, int row, int col, int count )
{
 long offset;
 int length;

 offset = ftell( stream );
 if ( offset == -1L ) {
    alert_box( "BUILDTXT", "Error Getting Offset to Text Output!" );
    return( FAIL );
    }
 doConvertText( buffer, _CVT_T_, _DST_T_ );
 bytes_saved += compress_string( buffer, comp_buf );
 length = strlen( comp_buf );
 if ( fputs( comp_buf, stream ) ) {
    alert_box( "BUILDTXT", "Error Writing To Output File!" );
    return( FAIL );
    }
 fflush( stream );
 TXTPT *t = (TXTPT *)index->getPtr(col, row);
 t->starts_at = offset;
 t->length = length;
 return( SUCCEED );
}


extern "C" {

int __declspec(dllexport) WINAPI _BUILDTXT( int argc, char *argv[] )
{
 char outtext[85], outindex[85], syscmd[125], sysprog[12];
 char infile[85], xbuf[50];
 FILE *outstream;
 int test, last, row, col, noer, count, val;

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
    if ( index != NULL ) {
       delete index;
       index = NULL;
       }
    return( val );
    }
 if ( argc < 3 ) {
    alert_box( "BUILDTXT", "Syntax: BUILDTXT infile.ext outfile FMT T|X SYMBOL.BSM\n"
       "Where FMT is WS, WP4, WP5, RTF, or ASC,\n"
       "and T (indicates Translate) or X (Don't Translate) are indicated\n"
       "The Last Argument is the BSM file generated by MKBSM, default is TEXT.BSM.");
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
    if ( strcmpi( argv[3], "AST" ) && strcmpi( argv[3], "DOC" ) ) {
       execFunction( sysprog, sysprog, argv[1], "BLDTX$$$.TMP" );
       if ( getFunctionRet() ) {
	  alert_box( "BUILDTXT", "Error Processing With %s", sysprog );
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
	  alert_box( "BUILDTXT", "Error Processing With %s", sysprog );
	  return( 10 );
	  }
       unlink( "BLDTX$$$.TMP" );
       strcpy( xbuf, "BLDTX$$$.TMP" );
       if ( rename( "BLDT$$$$.TMP", xbuf ) ) {
	  alert_box( "BUILDTXT", "Can't Rename Translated Input File to Input Temporary File!" );
	  return( 11 );
	  }
      strcpy( infile, "BLDTX$$$.TMP" );
      }
    
    }
 ifstream instream( infile, ios::in|ios::nocreate );
 if ( instream.bad()||instream.fail() ) {
    alert_box( "BUILDTXT", "Can't Open Input File %s!", infile );
    return( 11 );
    }
 if ( ( outstream = fopen( outtext, "ab" ) ) == NULL ) {
    alert_box( "BUILDTXT", "Can't Open Output Text File %s!", outtext );
    instream.close();
    return( 12 );
    }
 if ( setvbuf( outstream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( outstream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( outstream, NULL, _IOFBF, 1024 ) )
	  setvbuf( outstream, NULL, _IOFBF, 256 );
       }
    }
 if ( fseek( outstream, 0L, SEEK_END ) ) {
    alert_box( "BUILDTXT", "Error On Output File!" );
    instream.close();
    fclose( outstream );
    unlink( "BLDTX$$$.TMP" );
    return( 13 );
    }
 buffer = new char[BUF_SIZE];
 inbuf = new char[IN_BUF_SIZE];
 comp_buf = new char[20000];
 buffer[BUF_SIZE-1]='\0';
 inbuf[IN_BUF_SIZE-1]='\0';
 comp_buf[COMP_SIZE-1]='\0';
 last = test = '\n';
 while ( !((test = instream.get() ) == '#' && last == '\n') &&
	   !instream.eof() && !instream.bad() && !instream.fail()  )
       last = test;
 noer = 1; count = 0;
 while ( !instream.eof() && !instream.bad() && !instream.fail() && noer ) {
       assert( buffer[BUF_SIZE-1] == '\0' );
       assert( comp_buf[COMP_SIZE-1] == '\0' );
       assert( inbuf[IN_BUF_SIZE-1] == '\0' );
       noer = read_record( instream, &row, &col, count );
       dllYield();
       if ( noer )
          noer = put_text( outstream, row, col, count );
       ++count;
       }
 instream.close();
 fclose( outstream );
 LogPrintf( "Total Bytes Saved by compression = %u\n", bytes_saved );
 unlink( "BLDTX$$$.TMP" );
 if ( noer ) {
    write_array( outindex );
    delete buffer;
    buffer = NULL;
    delete inbuf;
    inbuf = NULL;
    delete comp_buf;
    comp_buf = NULL;
    delete index;
    index = NULL;
    return( 0 );
    }
 delete buffer;
 buffer = NULL;
 delete inbuf;
 inbuf = NULL;
 delete comp_buf;
 comp_buf = NULL;
 delete index;
 index = NULL;
 return( 14 );
}

}
