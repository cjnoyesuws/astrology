#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "chartinf.h"
#include "numbr.h"
#include "name.h"
#include "namegraf.h"
#include "errors.fns"


extern void calc_numbers( NUMBERS *n, DATES *d );
extern void do_all_name_numbers( CHART_INFO *cip, NAME_NUMB_GROUP *n );
extern void print_name_grafs_num( FILE *stream, CHART_INFO *cip, NAMEGRF_GRP *g, short head, short start, short end);
extern void print_name_grafs( FILE *stream, CHART_INFO *cip, NAMEGRF_GRP *g, short head, short start, short end);
extern int fdata_write( FILE *stream, unsigned short type );
extern short full_personality_report_print( FILE *stream, CHART_INFO *cip,
		    NUMBERS *np, NAME_NUMB_GROUP *nngp, short head );
extern short num_report_print( FILE *stream, CHART_INFO *cip,
		    NUMBERS *np, NAME_NUMB_GROUP *nngp, short head );
extern short do_all_names(NAMEGRF_GRP *n, CHART_INFO *c, NUMBERS *bn, NAME_NUMB_GROUP *nn );


extern void file_info_write( FILE *p );

int demo_mode;

int do_demo_mode( FILE *stream )
{ 
 if ( !demo_mode ) 
    return 0;
 fprintf( stream, "{WARNING! This file was produced by a Shareware Trial Version "
                  "of NUMERO UNO For Windows! This copy of NUMERO UNO "
                  "For Windows is is for Trial Use Only. Please Register it!}\n\n" );
 return( 1 );
}




NAMEGRF_GRP name_graphs;
NAME_NUMB_GROUP name_numbers;
NUMBERS date_numbers;
CHART_INFO chart_info_data;
short start, end;

void SetGroupStartEnd( short st, short ed )
{
 	
 start = st;
 end = ed;
}


void SetChartInfoData( CHART_INFO *h )
{
 chart_info_data = *h;
}

void compile_numbers()
{
 calc_numbers( &date_numbers, &chart_info_data.birth_date );
 do_all_name_numbers( &chart_info_data, &name_numbers );
 do_all_names(&name_graphs, &chart_info_data, &date_numbers, &name_numbers );
}

FILE *open_file( char *file )
{
 FILE *stream;

 if ( ( stream = fopen(file, "wb") ) == NULL ) {
    do_error( file );
    return( NULL );
    }
 assert( stream != NULL );
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 assert( stream != NULL );
 file_info_write( stream );
 return( stream );
}

/* Function to test the value of errno, Basically as a function to
   reduce redundant code */

int test_errno(void)
{
 if ( errno ) {
    return( 1 );
    }
 else
    return( 0 );
}

int CompileReport( int rep, char *n1_file )
{
 FILE *stream = NULL;
 time_t t;
 struct tm date;
 if (rep > 100) {
    demo_mode = 1;
    rep -= 100;
    }
 else
    demo_mode = 0; 
 switch( rep ) {
       case PERSON_FILE :
       case NUMERIC_FILE :
	    compile_numbers();
	    if ( ( stream = open_file( n1_file ) ) == NULL )
	      break;
	    fdata_write( stream, rep );
	    if ( rep == PERSON_FILE )
	       full_personality_report_print( stream, &chart_info_data,
		    &date_numbers, &name_numbers, 1 );
	    else
	       num_report_print( stream, &chart_info_data,
		    &date_numbers, &name_numbers, 1 );
	    	break;
       case NAMEGRAPH_FILE :
       case NUMGRAPH_FILE :
	    compile_numbers();
	    if ( ( stream = open_file( n1_file ) ) == NULL )
	       break;
	    fdata_write( stream, rep );
	    time(&t);
		date = *gmtime(&t);
	    if ( start < chart_info_data.birth_date.year ) {
               start = date.tm_year;
   	       end = start+10;
               }
	    if ( end > chart_info_data.birth_date.year+120 ||
		    start < chart_info_data.birth_date.year ) {
	       start = chart_info_data.birth_date.year;
	       end = start+10;
	       }
	    if ( rep == NAMEGRAPH_FILE )
	       print_name_grafs( stream, &chart_info_data, &name_graphs, 1, start, end);
	    else
	       print_name_grafs_num( stream, &chart_info_data, &name_graphs, 1, start, end);
	    break;
       default:
	    break;

       }
 file_info_write( stream );
 if ( errno ) {
    if ( stream != NULL ) {
       if ( ferror( stream ) ) {
	  do_error( n1_file );
	  }
       fclose( stream );
       }
    }
 else if ( !errno && stream != NULL )
    fclose( stream );
 errno = 0;
 return( 1 );
}
