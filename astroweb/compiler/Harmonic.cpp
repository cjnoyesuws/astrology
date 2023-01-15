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


HarmonicChartCompiler::doSetup()
{
 dp = harmonic_dp;
 op = setup_dat.getHarmonicOpt();
 dp.chart_code = op.getChartCode();
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = HARMONIC_FILE;
 load_orbs(HARMONIC_ORB);
 return( ChartCompiler::doSetup() );
}

int HarmonicChartCompiler::compile()
{
	harmonic_calc_chart( birth_inf, alt_inf, &birth_rec.birth_data,
    op.getFlags(), op.getHouseMode(), &dp );
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int HarmonicChartCompiler::writeData()
{
#ifdef PRO
 if ( op.getCharts() & DATAF && op.getDatafile()==DATABIN ) {
    bin_write_harmonic_chart( birth_inf, alt_inf, &birth_rec, op.getFlags(), &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATACMF ) {
    write_csv_harmonic( &birth_rec, birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATAC1F ) {
    write_csvx_harmonic( &birth_rec, birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }

 else if ( op.getCharts() & DATAF && op.getDatafile()==DATATAB ) {
    write_tab_Harmonic( &birth_rec, birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }
#endif
 return( 1 );
}

int HarmonicChartCompiler::doReport()
{
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 harmonic_print_results( stream, birth_inf, &birth_rec, op.getFlags(), alt_inf,
    op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );
 return( 1 );
}

int HarmonicChartCompiler::writeGrid()
{
 if ( openFile( grid_file,0 ) == NULL )
    return( 0 );
 harmonic_print_grid( stream, birth_inf, &birth_rec, op.getFlags(), alt_inf, ftype,
    op.getHouseMode()&0xf, &dp, comment_buf  );
 return( 1 );
}


int HarmonicChartCompiler::writeGraph()
{
 HarmonicGraphWriter *gw = new HarmonicGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
	 *dp.harmonic, alt_inf );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 return( 1 );
}
