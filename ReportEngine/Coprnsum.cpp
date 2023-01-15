#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "flags.h"
#include "misccalc.h"
#include "aspect.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "report.h"
#include "oututil.h"
#include "outfunc.fns"

/* 09/15/92  Modified for C++ Windows */

extern char *strclip( char *s );

#define SENSE  2

/* function that tests value and determines which is larger. yval = -1
   indicates initialize function when adding data, pointers are set to
   NULL. To evaluate data set index == -1 and pointers to ints. Returns
   appropriate index ( y or p ) associated with val ( y or p ) using
   ret and ret2 ( y or p ), ret being first choice. If ret2 is -1 then
   it should not be used
*/

void cotestval( int yval, int yindex, int pval, int pindex,
                 int *yret, int *yret2, int *pret, int *pret2 )
{
 static int yvals[13], yindexes[13], yentries;
 static int pvals[13], pindexes[13], pentries;
 int i, j, yd, pd, temp, p, y;

 if ( yval == -1 ) {
    yentries = 0;
    pentries = 0;
    return;
    }
 else if ( yindex != -1 ) {
   yvals[yentries] = yval;
   yindexes[yentries] = yindex;
   ++yentries;
   pvals[pentries] = pval;
   pindexes[pentries] = pindex;
   ++pentries;
   return;
   }
 if ( yentries != pentries )
    return;
 if ( pentries > 2 ) {
    for ( i = 0; i < yentries -1; ++i ) {      /* sort -y- list */
	for ( j = i+1; j < yentries; ++j ) {
            if ( yvals[j] > yvals[i] ) {
               temp = yvals[i];
               yvals[i] = yvals[j];
               yvals[j] = temp;
               temp = yindexes[i];
               yindexes[i] = yindexes[j];
               yindexes[j] = temp;
               }
            }
        }
    for ( i = 0; i < pentries -1; ++i ) {      /* sort -p- list */
	for ( j = i+1; j < pentries; ++j ) {
            if ( pvals[j] > pvals[i] ) {
               temp = pvals[i];
               pvals[i] = pvals[j];
               pvals[j] = temp;
               temp = pindexes[i];
               pindexes[i] = pindexes[j];
               pindexes[j] = temp;
               }
            }
        }
    }
 else {
    p = abs( pvals[0] - yvals[0] );
    y = abs( pvals[1] - yvals[1] );
    pd = pvals[0] - pvals[1];
    yd = yvals[0] - yvals[1];
    if ( abs( p - y ) <= SENSE && abs( pd - yd ) <= SENSE ) {
       *pret = 0;
       *yret = 7;
       }
    else if ( p <= SENSE ) {
       *pret = 1;
       *yret = 7;
       }
    else {
       *pret = 2;
       *yret = 7;
       }
    return;
    }
 p = pvals[1] - pvals[2];
 y = yvals[1] - yvals[2];
 pd = pvals[0] - pvals[1];
 yd = yvals[0] - yvals[1];


 if ( pd >= SENSE && yd >= SENSE ) {
    *pret = pindexes[0];
    *yret = yindexes[0];
    *pret2 = -1;
    *yret2 = -1;
    }
 else if ( pd >= SENSE ) {
    *pret = pindexes[0];
    *pret2 = pindexes[0];
    *yret = yindexes[0];
    *yret2 = yindexes[1];
    }
 else if ( yd >= SENSE ) {
    *yret = yindexes[0];
    *yret2 = yindexes[0];
    *pret = pindexes[0];
    *pret2 = pindexes[1];
    }
 else if ( p >= SENSE || y >= SENSE ) {
    *pret = pindexes[0];
    *yret = yindexes[0];
    *pret2 = pindexes[1];
    *yret2 = yindexes[1];
    }
 else  if ( ( p >= 1 && pd >= 1 ) || ( yd >= 1 && y >= 1 ) ) {
    *pret = pindexes[0];
    *yret = yindexes[0];
    *pret2 = -1;
    *yret2 = -1;
    }
 else {
    *pret = -1;
    *yret = -1;
    *pret2 = -1;
    *yret2 = -1;
    }
}

int analyze_genders( int fem, int masc, int pfem, int pmasc )
{
 int dfem, dmasc;

 dfem = abs(fem - pfem);
 dmasc = abs(masc - pmasc);
 if (dfem < 2 && dmasc < 2) {
    return( 1 );
    }
 else if (dfem < 4 && dmasc < 4) {
    return( 0 );
    }
 else
    return( 2 );
}


/* macro for using cotestval() easier. */

#define initct() cotestval( -1, 0, 0, 0, NULL, NULL, NULL, NULL )
#define addct(a,pi,b,yi) cotestval(a,pi,b,yi,NULL,NULL,NULL,NULL)
#define getct() cotestval( 0, -1, 0, 0, &yindex, &yindex2, &pindex, &pindex2 )

/* function to print out summary for compatibility. Mode refers to items
   that are either printed out or skipped.  */

void comp_print_summary( FILE *stream, BITS mode, int table, int global,
       char *name, char *name2, char *comment )
{
 int file = -1, yindex, yindex2, pindex, pindex2;
 const char *report;

 if ( mode & TEXT ) {
    if ( ( file = open_files( COMPAT_SUMMARY ) ) == -1 )
       mode &= ( 0xffff ^ TEXT );
    }
 if ( ( report = get_report( table, global, CHS_SUMARY_TITLE ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
       output_title( stream, name, name2, comment, (char *)report );
 if ( ( report = get_report( table, global, CHS_SIGN_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_sign_count(stream, name, name2, (char *)report );
/*
 if ( mode & TEXT ) {
    initct();
    addct( sign_count[ARIES], ARIES+1, comp_sign_count[ARIES], ARIES+1 );
    addct( sign_count[TAURUS], TAURUS+1, comp_sign_count[TAURUS], TAURUS+1 );
    addct( sign_count[GEMINI], GEMINI+1, comp_sign_count[GEMINI], GEMINI+1 );
    addct( sign_count[CANCER], CANCER+1, comp_sign_count[CANCER], CANCER+1 );
    addct( sign_count[LEO], LEO+1, comp_sign_count[LEO], LEO+1 );
    addct( sign_count[VIRGO], VIRGO+1, comp_sign_count[VIRGO], VIRGO+1 );
    addct( sign_count[LIBRA], LIBRA+1, comp_sign_count[LIBRA], LIBRA+1 );
    addct( sign_count[SCORPIO], SCORPIO+1, comp_sign_count[SCORPIO], SCORPIO+1 );
    addct( sign_count[SAGITARIUS], SAGITARIUS+1, comp_sign_count[SAGITARIUS], SAGITARIUS+1 );
    addct( sign_count[CAPRICORN], CAPRICORN+1, comp_sign_count[CAPRICORN], CAPRICORN+1 );
    addct( sign_count[AQUARIUS], AQUARIUS+1, comp_sign_count[AQUARIUS], AQUARIUS+1 ) ;
    addct( sign_count[PISCES], PISCES+1, comp_sign_count[PISCES], PISCES+1 );
    getct();
    if ( yindex != -1 )
       get_transfer_text( yindex, pindex, file, stream );
    if ( yindex2 != -1 )
       get_transfer_text( yindex2, pindex2, file, stream );
    }
    */
 if ( ( report = get_report( table, global, CHS_GENDER_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_genders(stream, name, name2, (char *)report );
 if ( mode & TEXT ) {
    get_transfer_text( 7, analyze_genders(genders.masculine, genders.feminine,
	 comp_genders.masculine, comp_genders.feminine), file, stream );
    }
 if ( ( report = get_report( table, global, CHS_ELEMENT_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_elements(stream, name, name2, (char *)report );
 if ( mode & TEXT ) {
    initct();
    addct( elements.fire, 0, comp_elements.fire, 1 );
    addct( elements.water, 3, comp_elements.water, 4 );
    addct( elements.earth, 1, comp_elements.earth, 2 );
    addct( elements.air, 2, comp_elements.air, 3 );
    getct();
    if ( yindex != -1 )
       get_transfer_text( yindex, pindex, file, stream );
    if ( yindex2 != -1 )
       get_transfer_text( yindex2, pindex2, file, stream );
    }
 if ( ( report = get_report( table, global, CHS_QUALITIES_COUNT ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_qualities(stream, name, name2, (char *)report );
 if ( mode & TEXT ) {
    initct();
    addct( qualities.cardinal, 4, comp_qualities.cardinal, 1 );
    addct( qualities.fixed, 5, comp_qualities.fixed, 2 );
    addct( qualities._mutable, 6, comp_qualities._mutable, 3 );
    getct();
    if ( yindex != -1 )
       get_transfer_text( yindex, pindex, file, stream );
    if ( yindex2 != -1 )
       get_transfer_text( yindex2, pindex2, file, stream );
    }
 if ( mode & HOUSES ) {
    if ( ( report = get_report( table, global, CHS_HOUSE_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_house_count(stream, name, name2, (char *)report );
/*
    if ( mode & TEXT ) {
       initct();
       addct( house_count[1], 1, comp_house_count[1], 1 );
       addct( house_count[2], 2, comp_house_count[2], 2 );
       addct( house_count[3], 3, comp_house_count[3], 3 );
       addct( house_count[4], 4, comp_house_count[4], 4 );
       addct( house_count[5], 5, comp_house_count[5], 5 );
       addct( house_count[6], 6, comp_house_count[6], 6 );
       addct( house_count[7], 7, comp_house_count[7], 7 );
       addct( house_count[8], 8, comp_house_count[8], 8 );
       addct( house_count[9], 9, comp_house_count[9], 9 );
       addct( house_count[10], 10, comp_house_count[10], 10 );
       addct( house_count[11], 11, comp_house_count[11], 11 );
       addct( house_count[12], 12, comp_house_count[12], 12 );
       getct();
       if ( yindex != -1 )
	  get_transfer_text( yindex, pindex, file, stream );
       if ( yindex2 != -1 )
	  get_transfer_text( yindex2, pindex2, file, stream );
       }
*/
    if ( ( report = get_report( table, global, CHS_HEMISPHERES_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_hemispheres(stream, name, name2, (char *)report );
    if ( mode & TEXT ) {
       initct();
       addct( hemispheres.north, 10, comp_hemispheres.north, 3 );
       addct( hemispheres.south, 11, comp_hemispheres.south, 4 );
       addct( hemispheres.east, 8, comp_hemispheres.east, 1 );
       addct( hemispheres.west, 9, comp_hemispheres.west, 2 );
       getct();
       if ( yindex != -1 )
	  get_transfer_text( yindex, pindex, file, stream );
       if ( yindex2 != -1 )
	  get_transfer_text( yindex2, pindex2, file, stream );
       }
    if ( ( report = get_report( table, global, CHS_FUNCTIONAL_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_functionals(stream, name, name2, (char *)report );
    if ( mode & TEXT ) {
       initct();
       addct( functionals.individual, 12, comp_functionals.individual, 1 );
       addct( functionals.temporal, 13, comp_functionals.temporal, 2 );
       addct( functionals.relative, 14, comp_functionals.relative, 3 );
       addct( functionals.terminal, 15, comp_functionals.terminal, 4 );
       getct();
       if ( yindex != -1 )
	  get_transfer_text( yindex, pindex, file, stream );
       if ( yindex2 != -1 )
	  get_transfer_text( yindex2, pindex2, file, stream );
       }
    if ( ( report = get_report( table, global, CHS_MODAL_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_modals(stream, name, name2, (char *)report );
    if ( mode & TEXT ) {
       initct();
       addct( modals.angular, 16, comp_modals.angular, 1 );
       addct( modals.cadent, 18, comp_modals.cadent, 3 );
       addct( modals.succedent, 17, comp_modals.succedent, 2 );
       getct();
       if ( yindex != -1 )
	  get_transfer_text( yindex, pindex, file, stream );
       if ( yindex2 != -1 )
	  get_transfer_text( yindex2, pindex2, file, stream );
       }
    }
 if ( mode & ASPECTS ) {
    if ( ( report = get_report( table, global, CHS_ASPECT_COUNT ) ) == NULL ) {
       close_tables( table, global );
       return;
       }
    else
       output_aspect_count(stream, name, name2, (char *)report );
    }
 if ( mode & TEXT )
    close_files( file );
 fputs("\n\n",stream);
}
