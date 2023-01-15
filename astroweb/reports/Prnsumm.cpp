#include "stdafx.h"
#include "astro.h"
#include "misccalc.h"
#include "aspect.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"

/* 09/15/92  Modified for C++ Windows */

/* functions to print out summary */
#define SENSE  2
#define THRESH 11

/* function that tests value and determines which is larger. The function
   is initialized with tval == -1. When setting data pointers are set to
   NULL. Use index == -1 to evaluate data. ret & ret2 return index
   associated with tval. If ret2 == -1 then it should be ignored. ret == 0
   indicates a balanced state
*/

void testval( int tval, int index, int *ret, int *ret2 )
{
 static vals[14], indexes[14], entries;
 int i, j, temp;

 if ( tval == -1 ) {
    entries = 0;
    return;
    }
 else if ( index != -1 ) {
   vals[entries] = tval;
   indexes[entries] = index;
   ++entries;
   return;
   }
 for ( i = 0; i < entries -1; ++i ) {      /* sort list */
     for ( j = i+1; j < entries; ++j ) {
	 if ( vals[j] > vals[i] ) {
	    temp = vals[i];
	    vals[i] = vals[j];
	    vals[j] = temp;
	    temp = indexes[i];
	    indexes[i] = indexes[j];
	    indexes[j] = temp;
	    }
	 }
     }
 if ( entries == 2 ) {
    if ( vals[0] - SENSE > vals[1]  ) {
       *ret = indexes[0];
       *ret2 = -1;
       return;
       }
    else {
       *ret = 0;
       *ret2 = -1;
       }
    }
 else if ( vals[0] - SENSE > vals[1] || vals[1] - SENSE > vals[2] ) {
    *ret = indexes[0];
    if ( vals[1] - SENSE > vals[2] ) {
       *ret2 = indexes[1];
       return;
       }
    else
       *ret2 = -1;
    }
 else {
    *ret = 0;
    *ret2 = -1;
    }
 if ( *ret == 0 && vals[0] >= THRESH )
    *ret = indexes[0];
 else if ( *ret2 == -1 && vals[1] >= THRESH )
    *ret = indexes[1];
}

/* macros to make calling testval() easier */

#define inittv() testval( -1, 0, NULL, NULL )
#define addtv(a,b) testval( a, b, NULL, NULL )
#define gettv() testval( 0, -1, &index, &index2 )


void print_summary( FILE *stream, BITS mode, int table, int global,
					   char *name, char *comment )
{
 const char *report;
 int file = -1, index, index2;

 if ( mode & TEXT ) {
    if ( ( file = open_files( SUMMARY_FILE ) ) == -1 )
       mode &= ( 0xffff ^ TEXT );
    }
 if ( mode & HOUSES ) {
    if ( ( report = get_report( table, global, CHS_SCOUT_PL ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_scout_planet( stream, name, comment, scout_planet, (char *)report );
    if ( mode & TEXT )
       get_transfer_text( 5, scout_planet, file, stream );
    }
    if ( ( report = get_report( table, global, CHS_SUMARY_TITLE ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
       output_title( stream, name, comment, "", (char *)report );
 if ( ( report = get_report( table, global, CHS_SIGN_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_sign_count(stream, name, comment, (char *)report );
/*
 if ( mode & TEXT ) {
    inittv();
    addtv( sign_count[ARIES], ARIES+1 );
    addtv( sign_count[TAURUS], TAURUS+1 );
    addtv( sign_count[GEMINI], GEMINI+1 );
    addtv( sign_count[CANCER], CANCER+1 );
    addtv( sign_count[LEO], LEO+1 );
    addtv( sign_count[VIRGO], VIRGO+1 );
    addtv( sign_count[LIBRA], LIBRA+1 );
    addtv( sign_count[SCORPIO], SCORPIO+1 );
    addtv( sign_count[SAGITARIUS], SAGITARIUS+1 );
    addtv( sign_count[CAPRICORN], CAPRICORN+1 );
    addtv( sign_count[AQUARIUS], AQUARIUS+1 );
    addtv( sign_count[PISCES], PISCES+1 );
    gettv();
    --index;
    if ( index != -1 )
       get_transfer_text( 0, index, file, stream );
    if ( index2 != -1 )
       get_transfer_text( 0, index2, file, stream );
    }
*/
 if ( ( report = get_report( table, global, CHS_GENDER_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_genders(stream, name, comment, (char *)report );
 if ( mode & TEXT ) {
    inittv();
    addtv( genders.feminine, 2 );
    addtv( genders.masculine, 1 );
    gettv();
    get_transfer_text( 2, index, file, stream );
    }

 if ( ( report = get_report( table, global, CHS_ELEMENT_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_elements(stream, name, comment, (char *)report );
 if ( mode & TEXT ) {
    inittv();
    addtv( elements.fire, 1 );
    addtv( elements.earth, 2 );
    addtv( elements.air, 3 );
    addtv( elements.water, 4 );
    gettv();
    get_transfer_text( 1, index, file, stream );
    if ( index2 != -1 )
        get_transfer_text( 1, index2, file, stream );
    }
 if ( ( report = get_report( table, global, CHS_QUALITIES_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_qualities(stream, name, comment, (char *)report );
 if ( mode & TEXT ) {
    inittv();
    addtv( qualities.cardinal, 1 );
    addtv( qualities.fixed, 2 );
    addtv( qualities._mutable, 3 );
    gettv();
    get_transfer_text( 3, index, file, stream );
    if ( index2 != -1 )
        get_transfer_text( 3, index2, file, stream );
    }

 if ( mode & HOUSES ) {
    if ( ( report = get_report( table, global, CHS_HOUSE_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_house_count(stream, name, comment, (char *)report );
/*
    if ( mode & TEXT ) {
       inittv();
       addtv( house_count[1], 1 );
       addtv( house_count[2], 2 );
       addtv( house_count[3], 3 );
       addtv( house_count[4], 4 );
       addtv( house_count[5], 5 );
       addtv( house_count[6], 6 );
       addtv( house_count[7], 7 );
       addtv( house_count[8], 8 );
       addtv( house_count[9], 9 );
       addtv( house_count[10], 10 );
       addtv( house_count[11], 11 );
       addtv( house_count[12], 12 );
       gettv();
       --index;
       if ( index != -1 )
	  get_transfer_text( 0, index, file, stream );
       if ( index2 != -1 )
	  get_transfer_text( 0, index2, file, stream );
       }
*/
    if ( ( report = get_report( table, global, CHS_HEMISPHERES_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_hemispheres(stream, name, comment, (char *)report );
    if ( mode & TEXT ) {
       inittv();
       addtv( hemispheres.east, 1 );
       addtv( hemispheres.west, 2 );
       addtv( hemispheres.north, 4 );
       addtv( hemispheres.south, 4 );
       gettv();
       get_transfer_text( 4, index, file, stream );
       if ( index2 != -1 )
          get_transfer_text( 4, index2, file, stream );
       }
    if ( ( report = get_report( table, global, CHS_FUNCTIONAL_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_functionals(stream, name, comment, (char *)report );
    if ( mode & TEXT ) {
       inittv();
       addtv( functionals.individual, 1 );
       addtv( functionals.relative, 2 );
       addtv( functionals.temporal, 3 );
       addtv( functionals.terminal, 4 );
       gettv();
       get_transfer_text( 1, index, file, stream );
       if ( index2 != -1 )
          get_transfer_text( 1, index2, file, stream );
       }
    if ( ( report = get_report( table, global, CHS_MODAL_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_modals(stream, name, comment, (char *)report );
    if ( mode & TEXT ) {
       inittv();
       addtv( modals.cadent, 1 );
       addtv( modals.angular, 2 );
       addtv( modals.succedent, 3 );
       gettv();
       get_transfer_text( 3, index, file, stream );
       if ( index2 != -1 )
          get_transfer_text( 3, index2, file, stream );
       }
    }
 if ( mode & ASPECTS ) {
    if ( ( report = get_report( table, global, CHS_ASPECT_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_aspect_count(stream, name, comment, (char *)report );
    if ( mode & TEXT ) {
       inittv();
       addtv( aspect_count[CONJUNCT], CONJUNCT+1 );
       addtv( aspect_count[TRINE], TRINE+1 );
       addtv( aspect_count[SEXTILE], SEXTILE+1 );
       addtv( aspect_count[SQUARED], SQUARED+1 );
       addtv( aspect_count[OPPOSITION], OPPOSITION+1 );
       gettv();
       --index;
       if ( index != -1 )
          get_transfer_text( 0, index, file, stream );
       if ( index2 != -1 )
          get_transfer_text( 0, index2, file, stream );
       }
    }
 if ( mode & TEXT )
    close_files( file );
}
