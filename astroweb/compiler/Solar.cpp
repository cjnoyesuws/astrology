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



int SolarChartCompiler::doSetup()
{
 dp = solar_dp;
 op = options;
 dp.chart_code = op.getChartCode();
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = SOLARARC_FILE;
 load_orbs(SOLAR_ORB);
 return( ChartCompiler::doSetup() );
}

int SolarChartCompiler::compile()
{
 do_full_direc( &birth_rec.birth_data, birth_inf, alt_inf,
    op.getFlags(), op.getHouseMode(), &dp );
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int SolarChartCompiler::writeData()
{
/*#ifdef PRO
 if ( op.getCharts() & DATAF && op.getDatafile()==DATABIN ) {
    bin_write_solar_chart( birth_inf, alt_inf, &birth_rec, op.getFlags(), &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATACMF ) {
    write_csv_solar( &birth_rec, birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile()==DATAC1F ) {
    write_csvx_solar( &birth_rec, birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }

 else if ( op.getCharts() & DATAF && op.getDatafile()==DATATAB ) {
    write_tab_Solar( &birth_rec, birth_inf, alt_inf, op.getFlags(), op.getHouseMode()&0xf, &dp );
    }


#endif*/
 return( 1 );
}

int SolarChartCompiler::doReport()
{
 /*if ( openFile( ast_file ) == NULL )
    return( 0 );
 solar_print_results( stream, birth_inf, &birth_rec, op.getFlags(), alt_inf,
    op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );*/
 return( 1 );
}

int SolarChartCompiler::writeGrid()
{
  return 0;
}


int SolarChartCompiler::writeGraph()
{
  return 0;
}
