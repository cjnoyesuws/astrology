#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <iostream.h>
#include <fstream.h>

#undef  END_OF_ARRAY
#define END_OF_ARRAY 255

int *rindex;
int start, end, comp_mode = 1, nl_mode = 1;

static void write_array( char *name );

/* function to read text symbols from file text.sym into symbols
   listing. If symbols can't be read then program errors out.
   If successful, sets num_symbols to the number of items read */

static void read_symbols( char *name )
{
 FILE *stream;
#ifndef BSR
 int x = 0, test;
 char buf2[250], *p;
 char buf[100];

 if ( ( stream = fopen( "REPORT.SYM", "rt" ) ) == NULL ) {
    alert_box( "BUILDRPT", "Can't Open \"REPORT.SYM\" for Reading!\n" );
    Throw( j, 1 );
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
    test = sscanf( buf2, "%s %d ", rsymbols[x].symbol,
	  &rsymbols[x].value );
    if ( test != 2 && p == NULL ) {
       alert_box( "BUILDRPT", "Error Reading Report Symbols\n" );
       fclose( stream );
       Throw( j, 2 );
       }
    else
       ++x;
 } while ( !ferror( stream ) && !feof( stream ) );
 fclose( stream );
 num_symbols = x;
 qsort( rsymbols, num_symbols, sizeof( RLST ), strcmpi );
#else
 if ( ( stream = fopen( "REPORT.BSM", "rb" ) ) == NULL ) {
    alert_box( "BUILDRPT", "Can't Open \"REPORT.BSM\" For Reading!" );
    Throw( j, 1 );
    }
 if ( fread( &num_symbols, 2, 1, stream ) != 1 ) {
    alert_box( "BUILDRPT", "Error reading \"REPORT.BSM\"!" );
    Throw( j, 2 );
    }
 if ( fread( rsymbols, sizeof( RLST ), num_symbols, stream ) != num_symbols ) {
    alert_box( "BUILDRPT", "Error Reading \"REPORT.BSM\"!" );
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

 if (( stream = fopen( name, "rb" ) ) == NULL ) {
    LogPrintf( "NEW FILE %s\n", name );
    return;
    }
 if ( fread( &start, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDRPT", "Error Reading START!" );
    fclose( stream );
    Throw( j, 3 );
    }
 if ( fread( &end, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDRPT", "Error Reading END!" );
    fclose( stream );
    Throw( j, 4 );
    }
 if ( fread( &rindex[start], sizeof( unsigned ),
			     end - start + 1, stream ) != end - start +1 ) {
    alert_box( "BUILDRPT", "Error Reading Index!" );
    fclose( stream );
    Throw( j, 5 );
    }
 fclose( stream );
}

static void write_array( char *file )
{
 int flag;
 int x;
 FILE *stream;

 if ( ( stream = fopen( file, "r+b" ) ) == NULL  ) {
    if ( ( stream = fopen( file, "wb" ) ) == NULL ) {
       alert_box( "BUILDRPT", "Error Opening Array and Text!" );
       Throw( j, 6 );
       }
    flag = 1;
    end = 258;
    }
 else
    flag = 0;
 if ( fwrite( &start, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDRPT", "Error Writing START!" );
    fclose( stream );
    Throw( j, 7 );
    }
 if ( fwrite( &end, sizeof( int ), 1, stream ) != 1 ) {
    alert_box( "BUILDRPT", "Error Writing END!" );
    fclose( stream );
    Throw( j, 8 );
    }
 if ( fwrite( &rindex[start], sizeof( unsigned ),
		       end - start + 1, stream ) != end - start + 1 ) {
    alert_box( "BUILDRPT", "Error Wriiting Index!" );
    fclose( stream );
    Throw( j, 9 );
    }
 if ( flag )
    end = 0;
 fclose( stream );
}

/* function that adjusts val and ajusts start and end. If Illegal returns
   END_OF_ARRAY */

static int adjust_num( int val )
{
 int i;

 if ( val < 0 || val >= END_OF_ARRAY )
    return( END_OF_ARRAY );
 if ( val < start ) {
    for ( i = val+1; i < start; ++i )
	rindex[i] = -1;
    start = val;
    }
 else if ( !start )
    start = val;
 if ( val > end ) {
    for ( i = end+1; i < val; ++i )
	rindex[i] = -1;
    end = val;
    }
 return( val );
}

typedef int (__far __cdecl *matchfunc)(const void __far *,const void __far *);

/* function to find a symbol in table and return the integer
   value defined for it. If the symbol is in the wrong column,
   then an error is reported, and END_OF_SYMBOL is returned, same
   is true if symbol is not found. First if symbol converts to an
   int that is returned. If symbol is found and the num_rows or
   num_cols is less than this variable then the appropriate
   number of rows or cols is increased */

static int find_symbol( char *symbol, int count, int *item )
{
 int val;
 RLST *ptr;

 val = atoi( symbol );
 if ( val != 0 || *symbol == '0' ) {
    val = adjust_num( val );
    return( val );
    }
 if ( *symbol == '+' ) {
    (*item)++;
    val = adjust_num( *item );
    return( val );
    }
 if ( ( ptr = ( struct RLST *) bsearch( symbol, rsymbols, num_symbols,
      sizeof( RLST ), (matchfunc)strcmpi ) ) == NULL ) {
    alert_box( "BUILDRPT", "Symbol %s Not Found! Text Chunk # = %d\n", symbol, count );
    return( END_OF_ARRAY );
    }
 *item = ptr->value;
 val = adjust_num( ptr->value );
 return( val );
}
/* function to read the control string if found in the read function.
   Returns col & row via pointers. Returns 1 for success, 0 for
   failure to read data properly */

static int read_ctl_string( ifstream &stream, int *item, int count )
{
 char buf[100];
 char symbol1[25];

 stream >> symbol1;
 stream.getline( inbuf, IN_BUF_SIZE-1 );
 strcat( inbuf, "\n" );
 if ( stream.bad() || stream.fail() || stream.eof() ) {
    alert_box( "BUILDRPT", "Error Reading Index String! Text Chunk # = %d\n", count );
    *item = END_OF_ARRAY;
    return( FAIL );
    }
 *item = find_symbol( symbol1, count, item );
 if ( *item == END_OF_ARRAY )
    return( FAIL );
 return ( SUCCEED );
 }

/* function to read a record. A record consists of a ctl_string and
   the text that follows. Text has been previously concatenated by
   textcomp.exe (textcomp.c) so that each paragraph or line (where
   indicated for line-for-line) is one line. function reads and
   concatenates all text up to #mark indicating next record. Assumes
   that we are at start of record and the # mark has been read.
   returns via pointers row and col. Returns 1 for success, 0
   for failure */

static int read_record( ifstream &stream, int *item, int count )
{
 int read_c;

 dllYield();
 if ( read_ctl_string( stream, item, count ) == FAIL )
    return( FAIL );
 stream.getline( inbuf, IN_BUF_SIZE-1 );
 strcat( inbuf, "\n" );
 if ( stream.bad() || stream.fail() ) {
    alert_box( "BUILDRPT", "Error Reading: Text Chunk # = %d\n", count );
    return( FAIL );
    }
 inbuf[IN_BUF_SIZE-1] = '\0';
 strcpy( buffer, inbuf );
 do {
    read_c = stream.get();
    if ( stream.bad() || stream.fail() || stream.eof() ) {
       if ( stream.eof() )
          return( SUCCEED );
       else 
	      alert_box( "BUILDRPT", "Error Reading: Text Chunk # = %d\n", count );
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
    stream.getline(inbuf, IN_BUF_SIZE-1);
    strcat( inbuf, "\n" );
    if ( stream.bad() || stream.fail() ) {
       if ( stream.bad() || stream.fail() ) {
	      alert_box( "BUILDRPT", "Error Reading: Text Chunk # = %d\n", count );
	      return( FAIL );
	      }
       }
    inbuf[IN_BUF_SIZE-2] = '\0';
    strcat( buffer, inbuf );
    } while( !stream.eof() );
 return( SUCCEED );
}

/* function to put text in buffer out to text output file. Also sets up
   info in index with offset and length. returns 0 for error 1 for SUCCEED
   NOTE: output file should be opened in "r+b" mode. A fseek( stream,
   0, SEEK_END ) should be called at start of program
   */

static int put_text( FILE *stream, int item, int count )
{
 long offset;
 int length;

 offset = ftell( stream );
 if ( offset == -1L ) {
    alert_box( "BUILDRPT", "Error Getting Offset in Text File To Output!" );
    return( FAIL );
    }
 doConvertText( buffer, _CVT_T_, _DST_T_ );
 if ( comp_mode )
    bytes_saved += compress_string( buffer, comp_buf );
 else
    strcpy( comp_buf, buffer );
 length = strlen( comp_buf );
 if ( !nl_mode ) {
    comp_buf[length-1] = '\0';
    length--;
    }
 if ( fwrite( comp_buf, 1, length+1, stream ) != length+1 ) {
    alert_box( "BUILDRPT", "Error Writing To Output File!" );
    return( FAIL );
    }
 fflush( stream );
 rindex[item] = (unsigned) offset-520L;
 return( SUCCEED );
}

extern "C" {

int __far __pascal __export _BUILDRPT( int argc, char *argv[] )
{
 char outfile[85], syscmd[125], sysprog[12], infile[85];
 FILE *outstream;
 int test, last, item, noer, count, i, val;

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
    if ( rindex != NULL ) {
       delete rindex;
       rindex = NULL;
       }
    return( val );
    }
 if ( argc < 3 ) {
    alert_box( "BUILDRPT", "Syntax: BUILDRPT infile.ext outfile.ext C|X FMT T|X N|X SYMBOL.BSM \n"
       "Where C (indicates Compress) or X (Don't Compress),\n"
       "FMT is one of WS, WP4, WP5, RTF, AST, or ASC,\n"
       "T (indicates Translate) or X (Don't Translate), and\n"
       "N (indicates New Line at end of entry ) or X (No New Lines)\n"
       "are indicated,\n"
       "The Last Argument is the BSM file generated by MKBSM, default is TEXT.BSM." );
    return( -1 );
    }
 strcpy( outfile, argv[2] );
 strcpy( infile, argv[1] );
 if ( argc > 7 ) {
    read_symbols(argv[7]);
    }
 else
    read_symbols("REPORT.BSM");
 rindex = new int[260];
 read_array( outfile );
 if ( argc > 3 ) {
    if ( !strcmpi( argv[3], "C" ) )
       comp_mode = 1;
    else
       comp_mode = 0;
    }
 if ( argc > 4 ) {
    strcpy( sysprog, argv[4] );
    strcat( sysprog, "TOAST" );
    if ( strcmpi( argv[4], "AST" ) && strcmpi( argv[4], "DOC" )  ) {
       execFunction( sysprog, sysprog, argv[1], "BLDTX$$$.TMP" );
       if ( getFunctionRet() ) {
	      alert_box( "BUILDRPT", "Error Processing With %s!", sysprog );
	      return( 10 );
	      }
       strcpy( infile, "BLDTX$$$.TMP" );
       }
    else
       strcpy( infile, argv[1] );
    }
 else
    strcpy( infile, argv[1] );
 if ( argc > 5 ) {
    if ( !strcmpi( argv[5], "T" ) ) {
       strcpy( sysprog, "STRTABLE" );
       execFunction( sysprog, sysprog, infile, "BLDT$$$$.TMP" );
       if ( getFunctionRet() ) {
	  alert_box( "BUILDRPT", "Error Processing With %s!", sysprog );
	  delete rindex;
	  return( 10 );
	  }
       unlink( "BLDTX$$$.TMP" );
       if ( rename( "BLDT$$$$.TMP", "BLDTX$$$.TMP" ) ) {
	  alert_box( "BUILDRPT", "Can't Rename Translated Input file to Input Temporary File" );
	  delete rindex;
	  return( 11 );
	  }
      strcpy( infile, "BLDTX$$$.TMP" );
      }
    }
 if ( argc > 6 ) {
    if ( !strcmpi( argv[6], "N" ) )
       nl_mode = 1;
    else
       nl_mode = 0;
    }
 ifstream instream( infile, ios::in|ios::nocreate );
 if ( instream.bad()||instream.fail() ) {
    alert_box( "BUILDRPT", "Can't Open Input Temporary File %s!", infile );
    delete rindex;
    return( 11 );
    }
 if ( !access( outfile, 0 ) ) {
    if ( ( outstream = fopen( outfile, "ab" ) ) == NULL ) {
       alert_box( "BUILDRPT", "Can't Open Output Text File %s to Write!", outfile );
       instream.close();
       delete rindex;
       return( 12 );
       }
    fputc( 0, outstream );
    }
 else {
    write_array( outfile );
    if ( ( outstream = fopen( outfile, "ab" ) ) == NULL ) {
       alert_box( "BUILDRPT", "Can't Open Output Text File %s to Write!", outfile );
       instream.close();
       delete rindex;
       return( 12 );
       }
    fputc( 0, outstream );
    }
 buffer = new char[20000];
 inbuf = new char[6000];
 comp_buf = new char[12000];
 last = test = '\n';
 while ( !((test = instream.get() ) == '#' && last == '\n') &&
          !instream.eof() && !instream.fail() )
       last = test;
 noer = 1; count = 0;
 while ( !instream.eof() && !instream.fail() && noer ) {
       noer = read_record( instream, &item, count );
       dllYield();
       if ( noer )
	  noer = put_text( outstream, item, count );
       ++count;
       }
 instream.close();
 fclose( outstream );
 LogPrintf( "Total Bytes Saved by compression = %u\n", bytes_saved );
 unlink( "BLDTX$$$.TMP" );
 if ( noer ) {
    write_array( outfile );
    delete rindex;
    rindex = NULL;
    delete buffer;
    buffer = NULL;
    delete inbuf;
    inbuf = NULL;
    delete comp_buf;
    comp_buf = NULL;
    return( 0 );
    }
 delete buffer;
 buffer = NULL;
 delete inbuf;
 inbuf = NULL;
 delete comp_buf;
 comp_buf = NULL;
 delete rindex;
 rindex = NULL;
 return( 14 );
}

}
