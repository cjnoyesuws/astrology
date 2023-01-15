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
#define debugLogOut(p)
#include "BaseChartWriter.h"
#include "IniChartWriter.h"



int ProgChartCompiler::doSetup()
{
 dp = progr_dp;
 op = options;
 dp.chart_code = op.getChartCode()|PROGR_CH;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = PROGRESSED_FILE;
 load_orbs(PROGR_ORB);
 return( ChartCompiler::doSetup() );
}

int ProgChartCompiler::compile()
{
 do_full_progr( &birth_rec.birth_data, birth_inf, alt_inf,
    op.getFlags(), op.getFlags(), op.getHouseMode(), &dp );
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int ProgChartCompiler::writeData()
{
stream = getOutputFile(getBasename(),getFormat());
  if (strcmp(getFormat(),"ini")==0) {
     IniChartWriter *wrt = new IniChartWriter(stream);
     wrt->writeProgr(maxpt);
     delete wrt;
  }

/*#ifdef PRO
 if ( op.getCharts() & DATAF && op.getDatafile()==DATABIN ) {
    bin_write_prog_chart( birth_inf, &birth_rec, op.getFlags(), &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATACMF ) {
    write_csv_prog( &birth_rec, birth_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATAC1F ) {
    write_csvx_prog( &birth_rec, birth_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }

 else if ( op.getCharts() & DATAF && op.getDatafile()==DATATAB ) {
    write_tab_prog( &birth_rec, birth_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }


#endif*/
 return( 1 );
}

int ProgChartCompiler::doReport()
{
 /*if ( openFile( ast_file ) == NULL )
    return( 0 );
 prog_print_results( stream, alt_inf, &birth_rec, op.getFlags(),
    op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );*/
 return( 1 );
}

int ProgChartCompiler::writeGrid()
{
 return 1;
}

int ProgChartCompiler::writeGraph()
{
 return( 1 );
}
