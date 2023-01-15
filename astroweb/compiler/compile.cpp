
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
#include <cstring>
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "Compile.hpp"
#include "orbs.h"
#include "output.fns"
#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>
#include <cstdio>
#include <stdio.h>
#include "BaseChartWriter.h"
#include "IniChartWriter.h"
#include "JsonChartWriter.h"

#define debugLogOut(p)

using namespace std;
using namespace rapidjson;

unsigned short fixupbits( unsigned short mode, unsigned short excl, unsigned short incl )
{
 unsigned short andmask;

 andmask = 0xffff ^ excl;
 mode &= andmask;
 mode |= incl;
 return( mode );
}


int ChartCompiler::writeGrid()
{
 return( 1 );
}


int ChartCompiler::writeGraph()
{
 return( 1 );
}


int NatalChartCompiler::doSetup()
{
 debugLogOut("doSetup1");
 if (getBasename()==NULL) {
    alert_box("Error","Output File Base is Required");
 }
 if (getFormat() == NULL) {
    alert_box( "Error", "Format is required");
 }
 dp=birth_dp;
    maxpt = PART_FORTU;
 switch( chartType ) {
    case DefaultChart :
	 op = options;
    case BirthSgnOnly :
	 if ( chartType == BirthSgnOnly ) {
		op.getFlags() = fixupbits(op.getFlags(),HOUSES|ASPECTS|BASE_MID|HALF_MID|FULL_MID,0);
	    }
    case BirthSgnHse :
	 if ( chartType == BirthSgnHse ) {
		op.getFlags() = fixupbits(op.getFlags(),ASPECTS|BASE_MID|HALF_MID|FULL_MID,HOUSES);
	    //op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST);
	    //op.getFlags() |= HOUSES;
	    }
    case SgnHseAsp :
	 if ( chartType == SgnHseAsp ) {
	    op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST |
		 EXT_ASPECTS | MISCELL);
	    op.getFlags() |= (HOUSES | ASPECTS);
		op.getFlags() = fixupbits(op.getFlags(),BASE_MID|HALF_MID|FULL_MID,HOUSES|ASPECTS);

	   }
    case Complete :
	 if ( chartType == Complete ) {
	    op.getFlags() |= (HOUSES | ASPECTS|EXT_ASPECTS|MISCELL);
		op.getFlags() = fixupbits(op.getFlags(),BASE_MID|HALF_MID|FULL_MID,HOUSES|ASPECTS);

	 }
#ifdef DELUXE
    case CompleteBMid :
	 if ( chartType == CompleteBMid ) {
	    //op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST | EXT_ASPECTS
		//| EXT_CALCS | BASE_MID | FULL_MID | MID_ASPECT | HALF_MID);
	    //op.getFlags() |= (HOUSES | ASPECTS | MISCELL | BASE_MID);
		op.getFlags() = fixupbits(op.getFlags(),0,BASE_MID | MID_ASPECT);
	    }
    case CompleteFMid :
	 if ( chartType == CompleteFMid ) {
	    //op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST |
		//   EXT_ASPECTS | MID_ASPECT);
	     //op.getFlags() |= (HOUSES | ASPECTS | MISCELL | FULL_MID | HALF_MID);
	     op.getFlags() = fixupbits(op.getFlags(),0,BASE_MID|FULL_MID|HALF_MID | MID_ASPECT);
	 }
#endif
    case Numeric :
	 {
	 if ( chartType == Numeric ) {
        unsigned short alt = op.getFlags();
        if ( alt & VERT_EAST ) {
            alt ^= VERT_EAST;
            }
        dp = birth_dp;
        if (birth_rec.birth_data.latitude.degrees <= 30 ) {
            op.getFlags() = alt;
            }
        }
     }
	 break;
 #ifdef DELUXE
    case Reloc :
	  if ( chartType == Reloc ) {
	    op = options;
	    }
	 dp = reloc_dp;
#endif
	 break;
    default:
	 break;
  }
 dp.chart_code = op.getChartCode()|NATAL_CH;
 switch ( chartType ) {
	case Numeric:
	     ftype = NUMERIC_FILE;
	     break;
#ifdef DELUXE
	case Reloc:
	     ftype = RELOCATION_FILE;
	     break;
#endif
	 default :
	     ftype = NATAL_FILE;
	     break;
	 }
 if ( dp.rdp->rect_system == -1 ) {
	 dp.rdp->rect_system = op.getDefRectMethod();
	 }
 int r = ChartCompiler::doSetup();
 mode = op.getFlags();
 load_orbs(NATAL_ORB);
 debugLogOut("doSetup2");
 return( r );
}

int NatalChartCompiler::compile()
{
 debugLogOut("compile1");

 BIRTH_DB *pb=&birth_rec;
 if ( with_rec != NULL ) {
	 pb = with_rec;
	 }
 do_calc( birth_inf, &pb->birth_data,
	op.getFlags(), op.getHouseMode(), &dp );
 debugLogOut("compile2");
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int NatalChartCompiler::writeData()
{
debugLogOut("writedata1");
 BIRTH_DB *pb=&birth_rec;
 if ( with_rec != NULL )
	 pb = with_rec;

  stream = getOutputFile(getBasename(),getFormat());
  if (strcmp(getFormat(),"ini")==0) {
     IniChartWriter *wrt = new IniChartWriter(stream);
     wrt->writeNatal(maxpt);
     delete wrt;
  }
  else if (strcmp(getFormat(),"json")==0) {
     JsonChartWriter writer(stream);
     writer.writeNatal(maxpt);
  }
  /*else if (getFormat(),"csv"==0) {
      if ( op.getCharts() & DATAF && op.getDatafile() == DATACMF ) {
            if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE || ftype == NUMERIC_FILE )
                   write_csv_natal( pb, birth_inf, op.getFlags(), op.getHouseMode()&0xf, &dp, 18 );
	  }
      else if ( op.getCharts() & DATAF && op.getDatafile() == DATAC1F ) {
            if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE || ftype == NUMERIC_FILE )
                    write_csvx_natal( pb, birth_inf, op.getFlags(), op.getHouseMode()&0xf, &dp, 18 );

	  }
  }*/
 /*if ( op.getCharts() & DATAF && op.getDatafile() == DATABIN ) {
    if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE ||
				     ftype == NUMERIC_FILE )
       bin_write_natal_chart( birth_inf, pb, op.getFlags(), &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATACMF ) {
    if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE ||
				     ftype == NUMERIC_FILE )
       write_csv_natal( pb, birth_inf, op.getFlags(),
				      op.getHouseMode()&0xf, &dp, 18 );
	}
    else if ( op.getCharts() & DATAF && op.getDatafile() == DATATAB ) {
    if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE ||
				     ftype == NUMERIC_FILE )
       write_tab_natal( pb, birth_inf, op.getFlags(),
				      op.getHouseMode()&0xf, &dp, 18 );
	}*/
 debugLogOut("writedata2");
 return( 1 );
}

int NatalChartCompiler::writeGraph()
{
 return( 1 );
}

int NatalChartCompiler::doReport()
{
 /*BIRTH_DB *pb=&birth_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 debugLogOut("writerep1");
 if ( openFile( ast_file ) == NULL )
    return( 0 );
#ifndef PRO
 switch( chartType ) {
       case Numeric :
	    num_print_results( stream, birth_inf, pb, birth_ext,
	      op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf );
	    break;
       default :
	    print_results( stream, birth_inf, pb, birth_ext,
		op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf  );
	    break;
       }
#else
 if ( op.getCharts() & INTRP )
	 print_results( stream, birth_inf, pb, birth_ext,
		op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf  );
 else
	 num_print_results( stream, birth_inf, pb, birth_ext,
	      op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf );

#endif
 debugLogOut("writerep2");*/
 return( 1 );
}

