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


int TransChartCompiler::doSetup()
{
 dp = trans_dp;
 op = options;
 dp.chart_code = op.getChartCode()|TRANS_CH;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = TRANSITS_FILE;
 if ( !transit_data.num_transits )
    transit_data.num_transits = 1;
 load_orbs(TRANS_ORB);
 return( ChartCompiler::doSetup() );
}

int TransChartCompiler::compile()
{
 BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 manage_transits( birth_inf, alt_inf, &birth_rec.birth_data,
	   &pb->birth_data, op.getFlags(), op.getFlags(), op.getHouseMode(), &dp);
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int TransChartCompiler::writeData()
{
stream = getOutputFile(getBasename(),getFormat());
  if (strcmp(getFormat(),"ini")==0) {
     IniChartWriter *wrt = new IniChartWriter(stream);
     wrt->writeTrans(maxpt);
     delete wrt;
  }


/*BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
#ifdef PRO
	if ( op.getCharts() & DATAF && op.getDatafile() == DATABIN ) {
    bin_write_trans_chart( birth_inf, &birth_rec, pb,
				       op.getFlags(), &dp );
    }
	else if ( op.getCharts() & DATAF && op.getDatafile()==DATACMF ) {
    write_csv_trans( &birth_rec, birth_inf, op.getFlags(),
			   pb, op.getHouseMode()&0xf, &dp );
    }
	else if ( op.getCharts() & DATAF && op.getDatafile()==DATAC1F ) {
    write_csvx_trans( &birth_rec, birth_inf, op.getFlags(),
			   pb, op.getHouseMode()&0xf, &dp );
    }

	else if ( op.getCharts() & DATAF && op.getDatafile()==DATATAB ) {
    write_tab_trans( &birth_rec, birth_inf, op.getFlags(),
			   pb, op.getHouseMode()&0xf, &dp );
    }


#endif*/
 return( 1 );
}

int TransChartCompiler::doReport()
{
 /*BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 trans_print_results( stream, birth_inf, &birth_rec, op.getFlags(),
       alt_inf, pb, op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP );*/

 return( 1 );
}

int TransChartCompiler::writeGrid()
{
/*BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
if ( openFile( grid_file,0 ) == NULL )
    return( 0 );
 trans_print_grid( stream, birth_inf, &birth_rec, op.getFlags(),
       alt_inf, ftype, pb, op.getHouseMode()&0xf, &dp, comment_buf );*/
 return( 1 );
}


int TransChartCompiler::writeGraph()
{
 /*extern AS_INF **trans_ptr;
 extern DATES *date_ptr;
 BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 TransGraphWriter *gw = new TransGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
     pb, &transit_data, trans_ptr, date_ptr );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;*/
 return( 1 );
}
