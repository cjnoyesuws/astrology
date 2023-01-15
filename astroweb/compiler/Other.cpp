#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "compute.fns"
#include "errors.fns"
#include "charcons.h"
#include "fptr.h"
#include <math.h>
#include "utlduad.h"
#ifdef PRO
#include "fixstar.h"
#include "arabpt.h"
#endif
#include "oututil.h"
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "Compile.hpp"
#include "orbs.h"
#include <cstring>
#include "output.fns"
#define debugLogOut(p)
#include "IniChartWriter.h"

int OtherChartCompiler::doSetup()
{
 int ormsk;
 char *prompt;

 switch( chartType ) {
       case Helio :
	    ormsk = 0;
	    op = options;
	    dp = birth_dp;
	    op.getCharts() &= TEXTF|GRIDF;
	    dp.chart_code = op.getChartCode();
	    ftype = HELIO_FILE;
	    break;
       case Arabic :
	    ormsk = ARABP_CH;
	    op = options;
	    op.getCharts() &= TEXTF|DATAF|GRIDF;
	    dp = arabp_dp;
	    ftype = ARABIC_FILE;
	    load_orbs(ARABIC_ORB);
	    break;
       case Fixed :
	    ormsk = FIXED_CH;
	    op = options;
	    op.getCharts() &= TEXTF|DATAF|GRIDF;
	    dp = fixed_dp;
	    ftype = FIXED_FILE;
	    load_orbs(FIXED_ORB);
	    break;
       case Problem :
	    ormsk = NATAL_CH;
	    op = options;
	    dp = birth_dp;
	    op.getCharts() &= TEXTF;
	    ftype = PROBLEM_FILE;
	    load_orbs(NATAL_ORB);
	    break;
       default :
	    break;
       }
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 dp.chart_code = op.getChartCode()| ormsk;
 return( ChartCompiler::doSetup() );
}

int OtherChartCompiler::compile()
{
/* if ( chartType != Helio )
    do_calc( birth_inf, &birth_rec.birth_data,
				 op.getFlags(), op.getHouseMode(), &dp );
 switch( chartType ) {
       case Helio :
	     helio_do_calc( birth_inf, &birth_rec.birth_data, op.getFlags(), &birth_dp );
	    break;
       case Arabic :

	     do_arabic_parts( op.getFlags(), birth_rec.birth_data.birth_date.year );
	    break;
       case Fixed :
		 do_fixed_stars( op.getFlags(), birth_rec.birth_data.birth_date.year, 0, birth_rec.birth_data.birth_date);
	    break;
       default :
	    break;
       }
 if ( testErrno() )
    return( 0 );
 else*/
    return( 1 );
}

int OtherChartCompiler::writeData()
{
/*
 if ( op.getCharts() & DATAF && op.getDatafile() == DATABIN ) {
    switch( chartType ) {
	  case Arabic :
	       bin_write_arabic_chart( birth_inf, &birth_rec, op.getFlags(), &dp );
	       break;
	  case Fixed :
	       bin_write_fixed_chart( birth_inf, &birth_rec, op.getFlags(), &dp );
	       break;
	  default :
	       break;
	  }
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATACMF ) {
    switch( chartType ) {
	  case Arabic :
	       if ( arabic_parts != NULL )
		  write_csv_natal( &birth_rec, getArabicParts(), op.getFlags(),
		     op.getHouseMode()&0xf, &dp, getArabicCount() );
	       break;
	  case Fixed :
	       if ( fixed_stars != NULL )
		  write_csv_natal( &birth_rec, getFixedStars(), op.getFlags(),
		      op.getHouseMode()&0xf, &dp, getFixedStarCount() );
	       break;
	  default :
	       break;
	  }
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATAC1F ) {
    switch( chartType ) {
	  case Arabic :
	       if ( arabic_parts != NULL )
		  write_csvx_natal( &birth_rec, getArabicParts(), op.getFlags(),
		     op.getHouseMode()&0xf, &dp, getArabicCount() );
	       break;
	  case Fixed :
	       if ( fixed_stars != NULL )
		  write_csvx_natal( &birth_rec, getFixedStars(), op.getFlags(),
		      op.getHouseMode()&0xf, &dp, getFixedStarCount() );
	       break;
	  default :
	       break;
	  }
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATATAB ) {
    switch( chartType ) {
	  case Arabic :
	       if ( arabic_parts != NULL )
		  write_tab_natal( &birth_rec, getArabicParts(), op.getFlags(),
		     op.getHouseMode()&0xf, &dp, getArabicCount() );
	       break;
	  case Fixed :
	       if ( fixed_stars != NULL )
		  write_tab_natal( &birth_rec, getFixedStars(), op.getFlags(),
		      op.getHouseMode()&0xf, &dp, getFixedStarCount() );
	       break;
	  default :
	       break;
	  }
    }
*/
 return( 1 );
}

int OtherChartCompiler::doReport()
{
/*char *arabtxt[3] = {ARABIC_SIGN, ARABIC_HOUSE, ARABIC_ASPECTS };
char *fixedtxt[3] = {FIXEDST_SIGN, FIXEDST_HOUSE, FIXEDST_ASPECTS };

if ( openFile( ast_file ) == NULL )
    return( 0 );
 switch( chartType ) {
       case Helio :
	    nh_print_results( stream, birth_inf, &birth_rec,
		 op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf );
	    break;
       case Arabic :
	    nx_print_results( stream, getArabicParts(), &birth_rec, op.getFlags(),
		  op.getHouseMode()&0xf, ARABP_DI, getArabicCount(), &dp,
		  (op.getCharts()&INTRP?"ARABICTXT":"ARABIC"), comment_buf, arabtxt  );
	    break;
       case Fixed :
	    nx_print_results( stream, getFixedStars(), &birth_rec, op.getFlags(),
		 op.getHouseMode(), FIXED_DI, getFixedStarCount(), &fixed_dp,
		 (op.getCharts()&INTRP?"FIXEDSTTXT":"FIXEDST"), comment_buf, fixedtxt  );
	    break;
       case Problem :
	    problem_solving_report( stream, birth_inf, &birth_rec,
			    op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf );
	    break;
       default :
	    break;
       }*/
 return( 1 );
}

int OtherChartCompiler::writeGrid()
{
  return 0;
}



int OtherChartCompiler::cleanUp( int ok )
{
 /*switch( chartType ) {
       case Arabic :
	    close_arabic_pts();
	    break;
       case Fixed :
	    close_fixed_stars();
	    break;
       default :
	    break;
       }*/
 return( ChartCompiler::cleanUp( ok ) );
}
