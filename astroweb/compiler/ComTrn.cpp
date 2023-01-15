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
#include "fixstar.h"
#include "arabpt.h"
#include "oututil.h"
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "Compile.hpp"
#include "orbs.h"
#include <cstring>


int ComTrnChartCompiler::doSetup()
{
 char buffer[120];
 op = options;
 dp = comptr_dp;
 ftype = COMPOTRAN_FILE;
 load_orbs(TRANS_ORB);
 dp.chart_code = op.getChartCode() | COMPO_CH|TRANS_CH|RELOC_CH;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 strcpy( buffer, birth_rec.name );
 strcat( buffer, " & " );
 strcat( buffer, comp_rec.name );
 buffer[NAME_WIDTH] = '\0';
 buffer[NAME_WIDTH+1] = '\0';
 if ( makeFile( ftype, op.getCharts() & GRAPH, buffer, (char *)types[ftype] ) )
    return( 0 );
 return( 1 );
}

int ComTrnChartCompiler::compile()
{
 do_composite_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	 alt_inf, op.getFlags(), op.getFlags(), op.getHouseMode(), &dp );
 if ( testErrno() )
    return( 0 );
 dp.chart_code = op.getChartCode();
 manage_transits( birth_inf, alt_inf, &birth_rec.birth_data,
	&trans_rec.birth_data, op.getFlags(), op.getFlags(), op.getHouseMode(), &comptr_dp);
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int ComTrnChartCompiler::writeData()
{
 /*if ( op.getCharts() & DATAF && op.getDatafile() == DATABIN ) {
    bin_write_cmtrans_chart( birth_inf, &birth_rec, &trans_rec,
					&comp_rec, op.getFlags(), &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATACMF ) {
    write_csv_cmtrans( &birth_rec, birth_inf, op.getFlags(),
	       &trans_rec, &comp_rec, op.getHouseMode()&0xf, &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATAC1F ) {
    write_csvx_cmtrans( &birth_rec, birth_inf, op.getFlags(),
	       &trans_rec, &comp_rec, op.getHouseMode()&0xf, &dp );
    }
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATATAB ) {
    write_tab_cmtrans( &birth_rec, birth_inf, op.getFlags(),
	       &trans_rec, &comp_rec, op.getHouseMode()&0xf, &dp );
    }*/
 return( 1 );
}

int ComTrnChartCompiler::doReport()
{/*
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 cmtrans_print_results( stream, birth_inf, &birth_rec, &comp_rec,
	 op.getFlags(), alt_inf, &trans_rec, op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );*/
 return( 1 );
}

int ComTrnChartCompiler::writeGrid()
{
 return( 1 );
}

int ComTrnChartCompiler::writeGraph()
{
 return( 1 );
}
