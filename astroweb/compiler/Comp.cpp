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
#include "cstring"
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "Compile.hpp"
#include "orbs.h"
#include "output.fns"
#define debugLogOut(p)
#include "BaseChartWriter.h"
#include "IniChartWriter.h"


int CompChartCompiler::doSetup()
{
  char buffer[120];
  debugLogOut("doSetup1");
  switch( chartType ) {
    case Compatibility :
	 dp = comp_dp;
	 op = options;
	 dp.chart_code = op.getChartCode()|COMPA_CH;
	 ftype = COMPATIBILITY_FILE;
	 load_orbs(COMPA_ORB);
	 break;
#ifdef DELUXE
    case Compos :
	 dp = comp_dp;
	 op = options;
	 dp.chart_code = op.getChartCode()|COMPO_CH|RELOC_CH;
	 ftype = COMPOSITE_FILE;
	 load_orbs(COMPO_ORB);
	 break;
#endif
    default:
	 break;
  }
  BITS alt = op.getFlags();
  if ( alt & VERT_EAST )
	  alt ^= VERT_EAST;
 if ( !dp.rdp->birth_time_known ) {
    op.getFlags() |= NOBIRTHTIM;
    }
 if ( birth_rec.birth_data.latitude.degrees<30 ||
	    comp_rec.birth_data.latitude.degrees<30) {
	op.getFlags() = alt;
	}
 if ( dp.rdp->rect_system == -1 ) {
	 dp.rdp->rect_system = op.getDefRectMethod();
	 }
 if ( dp.crdp->rect_system == -1 ) {
	 dp.crdp->rect_system = op.getDefRectMethod();
	 }
 strcpy( buffer, birth_rec.name );
 strcat( buffer, " & " );
 strcat( buffer, comp_rec.name );
 buffer[NAME_WIDTH] = '\0';
 buffer[NAME_WIDTH+1] = '\0';
 if ( makeFile( ftype, op.getCharts() & GRAPH, buffer,(char *) types[ftype] ) )
    return( 0 );
 debugLogOut("dosetup2");
 return( 1 );
}

int CompChartCompiler::compile()
{
 debugLogOut("compile3");
 if ( chartType == Compatibility  ) {
    do_comp_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	  alt_inf, op.getFlags(), op.getFlags(), op.getHouseMode(), &dp );
	  }
#ifdef DELUXE
 else {
    do_composite_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	  alt_inf, op.getFlags(), op.getFlags(), op.getHouseMode(), &dp );
	  }
#endif
 debugLogOut("compile4");
 if ( testErrno() ) {
    return( 0 );
    }
 else {
    return( 1 );
    }
}

int CompChartCompiler::writeData()
{
stream = getOutputFile(getBasename(),getFormat());
  if (strcmp(getFormat(),"ini")==0) {
     IniChartWriter *wrt = new IniChartWriter(stream);
     wrt->writeCompat(maxpt);
     delete wrt;
  }
debugLogOut("writedata3");
/*#ifdef PRO
 if ( op.getCharts() & DATAF && op.getDatafile()==DATABIN ) {
    if ( chartType == Compatibility ) {
       bin_write_compat_chart( birth_inf, alt_inf,
		&birth_rec, &comp_rec, op.getFlags(), &dp );
       }
    else if (chartType == Compos) {
       bin_write_compos_chart( birth_inf, &birth_rec,
		      &comp_rec, op.getFlags(), &dp );
       }
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATACMF ) {
    if ( chartType == Compatibility ) {
       write_csv_compat( &birth_rec, &comp_rec,
	  birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
       }
    else if (chartType == Compos) {
       write_csv_compos( &birth_rec, &comp_rec, birth_inf,
	    op.getFlags(), op.getHouseMode()&0xf, &dp );
       }
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATAC1F ) {
    if ( chartType == Compatibility ) {
       write_csvx_compat( &birth_rec, &comp_rec,
	  birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
       }
    else if (chartType == Compos) {
       write_csvx_compos( &birth_rec, &comp_rec, birth_inf,
	    op.getFlags(), op.getHouseMode()&0xf, &dp );
       }
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATATAB ) {
    if ( chartType == Compatibility ) {
       write_tab_compat( &birth_rec, &comp_rec,
	  birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
       }
    else if (chartType == Compos) {
       write_tab_compos( &birth_rec, &comp_rec, birth_inf,
	    op.getFlags(), op.getHouseMode()&0xf, &dp );
       }
    }

 debugLogOut("writedata4");
#endif*/
 return( 1 );
}

int CompChartCompiler::writeGraph()
{
 return( 1 );
}

int CompChartCompiler::doReport()
{
 /*debugLogOut("dorep3");
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 if ( chartType == Compatibility ) {
    comp_print_results( stream, birth_inf, &birth_rec,
      op.getFlags(), alt_inf, &comp_rec, op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP );
    }
#ifdef DELUXE
 else if ( chartType == Compos ) {
    setup_compos( &comp_rec );
    compos_print_results( stream, birth_inf, birth_ext,
	 &birth_rec, op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf,op.getCharts()&INTRP );
    }
#endif
 debugLogOut("dorep4");*/
 return( 1 );
}

int CompChartCompiler::writeGrid()
{
return ( 1 );

}

