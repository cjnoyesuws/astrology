#include "stdafx.h"
#include "astrow.h"
#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "output.fns"
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
#include "inifile.hpp"
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "procmsg.h"
#include "compile.hpp"
#include "orbs.h"
#include "graphdat.hpp"
#include "graphwrt.hpp"
#include "chartoptions.h"
#include "customize.h"
#include "textptr.h"
#include "grids.fns"
#include <afxcoll.h>

#define debugLogOut(p) 

extern void mem_reclaim( AS_INF *aptr, AS_INF *alt_ptr, TRANS_DATA *td, BITS mode );

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
 if ( openFile( grid_file,0) == NULL )
    return( 0 );
 num_print_grid( stream, birth_inf, &birth_rec,
      birth_ext, op.getFlags(), op.getHouseMode()&0xf, &dp,
	  comment_buf, ftype );
 return( 1 );
}


int ChartCompiler::writeGraph()
{
 debugLogOut("writeGraph1");
 GraphWriter *gw = new GraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr);
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 debugLogOut("writeGraph2");
 return( 1 );
}


NatalChartCompiler::doSetup()
{
 debugLogOut("doSetup1"); 
    
 switch( chartType ) {
    case DefaultChart :
	 op = setup_dat.getBirthOpt();
    case BirthSgnOnly :
	 if ( chartType == BirthSgnOnly ) {
	    op = setup_dat.getBirthOpt();
		op.getFlags() = fixupbits(op.getFlags(),HOUSES|ASPECTS|BASE_MID|HALF_MID|FULL_MID,0);
	    }
    case BirthSgnHse :
	 if ( chartType == BirthSgnHse ) {
	    op = setup_dat.getBirthOpt();
		op.getFlags() = fixupbits(op.getFlags(),ASPECTS|BASE_MID|HALF_MID|FULL_MID,HOUSES);
	    //op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST);
	    //op.getFlags() |= HOUSES;
	    }
    case SgnHseAsp :
	 if ( chartType == SgnHseAsp ) {
	    op = setup_dat.getBirthOpt();
	    op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST |
		 EXT_ASPECTS | MISCELL);
	    op.getFlags() |= (HOUSES | ASPECTS);		
		op.getFlags() = fixupbits(op.getFlags(),BASE_MID|HALF_MID|FULL_MID,HOUSES|ASPECTS);
	    
	   }
    case Complete :
	 if ( chartType == Complete ) {
	    op = setup_dat.getBirthOpt();
	    op.getFlags() |= (HOUSES | ASPECTS|EXT_ASPECTS|MISCELL);
		op.getFlags() = fixupbits(op.getFlags(),BASE_MID|HALF_MID|FULL_MID,HOUSES|ASPECTS);
		
	 }
#ifdef DELUXE
    case CompleteBMid :
	 if ( chartType == CompleteBMid ) {
	    op = setup_dat.getBirthOpt();
	    //op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST | EXT_ASPECTS
		//| EXT_CALCS | BASE_MID | FULL_MID | MID_ASPECT | HALF_MID);
	    //op.getFlags() |= (HOUSES | ASPECTS | MISCELL | BASE_MID);
		op.getFlags() = fixupbits(op.getFlags(),0,BASE_MID | MID_ASPECT);
	    }
    case CompleteFMid :
	 if ( chartType == CompleteFMid ) {
	    op = setup_dat.getBirthOpt();
	    //op.getFlags() &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST |
		//   EXT_ASPECTS | MID_ASPECT);
	     //op.getFlags() |= (HOUSES | ASPECTS | MISCELL | FULL_MID | HALF_MID);
	     op.getFlags() = fixupbits(op.getFlags(),0,BASE_MID|FULL_MID|HALF_MID | MID_ASPECT);   
	 }
#endif
    case Numeric :
	 {
	 if ( chartType == Numeric )
	    op = setup_dat.getNumerOpt();
	 unsigned short alt = op.getFlags();
     if ( alt & VERT_EAST )
	    alt ^= VERT_EAST;
	 dp = birth_dp;
	 if (birth_rec.birth_data.latitude.degrees <= 30 )
		 op.getFlags() = alt;
	 if ( chartType != BirthSgnHse && chartType != BirthSgnOnly ) {
	     if ( !customizeScreen( "Natal Chart Options:" ) )
	       return( 0 );
	    }
	  }
	 break;
 #ifdef DELUXE
    case Reloc :

	  if ( chartType == Reloc )
	    op = setup_dat.getRelocOpt();
	 dp = reloc_dp;
	 if ( !customizeScreen( "Relocated Chart Options:" ) )
	    return( 0 );
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
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
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
 if ( with_rec != NULL )
	 pb = with_rec;
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
#ifdef PRO
 BIRTH_DB *pb=&birth_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 if ( op.getCharts() & DATAF && op.getDatafile() == DATABIN ) {
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
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATAC1F ) {
    if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE ||
				     ftype == NUMERIC_FILE )
       write_csvx_natal( pb, birth_inf, op.getFlags(),
				      op.getHouseMode()&0xf, &dp, 18 );
	}
 else if ( op.getCharts() & DATAF && op.getDatafile() == DATATAB ) {
    if ( ftype == NATAL_FILE || ftype == RELOCATION_FILE ||
				     ftype == NUMERIC_FILE )
       write_tab_natal( pb, birth_inf, op.getFlags(),
				      op.getHouseMode()&0xf, &dp, 18 );
	}
#endif
 debugLogOut("writedata2");
 return( 1 );
}

int NatalChartCompiler::writeGraph()
{
 BIRTH_DB *pb=&birth_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 debugLogOut("writeGraph3");
 GraphWriter *gw = new GraphWriter( pb, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr);
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 debugLogOut("writeGraph4");
 return( 1 );
}

int NatalChartCompiler::doReport()
{
 BIRTH_DB *pb=&birth_rec;
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
 debugLogOut("writerep2");
 return( 1 );
}

CompChartCompiler::doSetup()
{
  char buffer[120];
  debugLogOut("doSetup1");
  switch( chartType ) {
    case Compatibility :
	 dp = comp_dp;
	 op = setup_dat.getCompatOpt();
	 dp.chart_code = op.getChartCode()|COMPA_CH;
	 ftype = COMPATIBILITY_FILE;
	 if ( !customizeScreen( "Compatability Chart Options:" ) )
	       return( 0 );
	 load_orbs(COMPA_ORB);
	 break;
#ifdef DELUXE
    case Compos :
	 dp = comp_dp;
	 op = setup_dat.getComposOpt();
	 dp.chart_code = op.getChartCode()|COMPO_CH|RELOC_CH;
	 ftype = COMPOSITE_FILE;
	 if ( !customizeScreen("Composite Chart Options:") )
	    return( 0 );
	 load_orbs(COMPO_ORB);
	 break;
#endif
    default:
	 break;
  }
  BITS alt = op.getFlags();
  if ( alt & VERT_EAST )
	  alt ^= VERT_EAST;
 if ( !dp.rdp->birth_time_known )
    op.getFlags() |= NOBIRTHTIM;
 if ( birth_rec.birth_data.latitude.degrees<30 || 
	    comp_rec.birth_data.latitude.degrees<30)
	op.getFlags() = alt;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 if ( dp.crdp->rect_system == -1 )
	 dp.crdp->rect_system = op.getDefRectMethod();
 strcpy( buffer, birth_rec.name );
 strcat( buffer, " & " );
 strcat( buffer, comp_rec.name );
 buffer[NAME_WIDTH] = '\0';
 buffer[NAME_WIDTH+1] = '\0';
 if ( makeFile( ftype, op.getCharts() & GRAPH, buffer, types[ftype] ) )
    return( 0 );
 debugLogOut("dosetup2");
 return( 1 );
}

int CompChartCompiler::compile()
{
 debugLogOut("compile3");
 if ( chartType == Compatibility  )
    do_comp_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	  alt_inf, op.getFlags(), op.getFlags(), op.getHouseMode(), &dp );
#ifdef DELUXE
 else
    do_composite_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	  alt_inf, op.getFlags(), op.getFlags(), op.getHouseMode(), &dp );
#endif
 debugLogOut("compile4");
 if ( testErrno() )
    return( 0 );
 else
    return( 1 );
}

int CompChartCompiler::writeData()
{
debugLogOut("writedata3");
#ifdef PRO
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
#endif
 return( 1 );
}

int CompChartCompiler::writeGraph()
{
 debugLogOut("writegraph3");
 CompGraphWriter *gw = new CompGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
     alt_inf, &comp_rec, op.getFlags() );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 debugLogOut("writegraph4");
 delete gw;
 return( 1 );
}

int CompChartCompiler::doReport()
{
 debugLogOut("dorep3");
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
 debugLogOut("dorep4");
 return( 1 );
}

int CompChartCompiler::writeGrid()
{
	if ( openFile( grid_file,0 ) == NULL )
       return( 0 );
	if ( chartType == Compatibility ) {
	  comp_print_grid( stream, birth_inf, &birth_rec,
      op.getFlags(), alt_inf, &comp_rec, op.getHouseMode()&0xf, &dp, comment_buf, ftype );
	}
#ifdef DELUXE
	else if ( chartType == Compos ) {
	  setup_composg( &comp_rec );
	  compos_print_grid( stream, birth_inf, birth_ext,
	 &birth_rec, op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf, ftype );

	}
#endif
return ( 1 );

}

#ifdef DELUXE
ProgChartCompiler::doSetup()
{
 dp = progr_dp;
 op = setup_dat.getProgrOpt();
 dp.chart_code = op.getChartCode()|PROGR_CH;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = PROGRESSED_FILE;
 if ( !customizeScreen( "Progressed Chart Options:") )
    return( 0 );
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
#ifdef PRO
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


#endif
 return( 1 );
}

int ProgChartCompiler::doReport()
{
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 prog_print_results( stream, alt_inf, &birth_rec, op.getFlags(),
    op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );
 return( 1 );
}

int ProgChartCompiler::writeGrid()
{
 if ( openFile( grid_file,0 ) == NULL )
    return( 0 );
 prog_print_grid( stream, alt_inf, &birth_rec, op.getFlags(),
    op.getHouseMode()&0xf, &dp, comment_buf, ftype  );
 return 1;
}

int ProgChartCompiler::writeGraph()
{
 extern AS_INF *prog;

 ProgGraphWriter *gw = new ProgGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
     &progress_data, alt_inf, prog );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 return( 1 );
}

SolarChartCompiler::doSetup()
{
 dp = solar_dp;
 op = setup_dat.getSolarOpt();
 dp.chart_code = op.getChartCode();
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = SOLARARC_FILE;
 if ( !customizeScreen( "Solar Chart Options:") )
    return( 0 );
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
#ifdef PRO
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


#endif
 return( 1 );
}

int SolarChartCompiler::doReport()
{
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 solar_print_results( stream, birth_inf, &birth_rec, op.getFlags(), alt_inf,
    op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );
 return( 1 );
}

int SolarChartCompiler::writeGrid()
{
 if ( openFile( grid_file,0 ) == NULL )
    return( 0 );
 solar_print_grid( stream, birth_inf, &birth_rec, op.getFlags(), alt_inf, ftype,
    op.getHouseMode()&0xf, &dp, comment_buf  );
 return( 1 );
}


int SolarChartCompiler::writeGraph()
{
 SolarGraphWriter *gw = new SolarGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
     &solar_data, alt_inf );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 return( 1 );
}

HarmonicChartCompiler::doSetup()
{
 dp = harmonic_dp;
 op = setup_dat.getHarmonicOpt();
 dp.chart_code = op.getChartCode();
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = HARMONIC_FILE;
 if ( !customizeScreen( "Harmonic Chart Options:") )
    return( 0 );
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


#endif

TransChartCompiler::doSetup()
{
 dp = trans_dp;
 op = setup_dat.getTransOpt();
 dp.chart_code = op.getChartCode()|TRANS_CH;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 ftype = TRANSITS_FILE;
 if ( !transit_data.num_transits )
    transit_data.num_transits = 1;
 if ( !customizeScreen( "Transits Chart Options:" ) )
    return( 0 );
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
BIRTH_DB *pb=&trans_rec;
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


#endif
 return( 1 );
}

int TransChartCompiler::doReport()
{
 BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 trans_print_results( stream, birth_inf, &birth_rec, op.getFlags(),
       alt_inf, pb, op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP );
 return( 1 );
}

int TransChartCompiler::writeGrid()
{
BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
if ( openFile( grid_file,0 ) == NULL )
    return( 0 );
 trans_print_grid( stream, birth_inf, &birth_rec, op.getFlags(),
       alt_inf, ftype, pb, op.getHouseMode()&0xf, &dp, comment_buf );
 return( 1 );
}


int TransChartCompiler::writeGraph()
{
 extern AS_INF **trans_ptr;
 extern DATES *date_ptr;
 BIRTH_DB *pb=&trans_rec;
 if ( with_rec != NULL )
	 pb = with_rec;
 TransGraphWriter *gw = new TransGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
     pb, &transit_data, trans_ptr, date_ptr );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 return( 1 );
}

#ifdef PRO
OtherChartCompiler::doSetup()
{
 int ormsk;
 char *prompt;

 switch( chartType ) {
       case Helio :
	    ormsk = 0;
	    op = setup_dat.getBirthOpt();
	    dp = birth_dp;
	    op.getCharts() &= TEXTF|GRIDF;
	    dp.chart_code = op.getChartCode();
	    prompt = "Heliocentric Chart Options:";
	    ftype = HELIO_FILE;
	    break;
       case Arabic :
	    ormsk = ARABP_CH;
	    op = setup_dat.getArabptOpt();
	    op.getCharts() &= TEXTF|DATAF|GRIDF;
	    dp = arabp_dp;
	    ftype = ARABIC_FILE;
	    prompt = "Arabic Points Chart Options:";
	    load_orbs(ARABIC_ORB);
	    break;
       case Fixed :
	    ormsk = FIXED_CH;
	    op = setup_dat.getFixstarOpt();
	    op.getCharts() &= TEXTF|DATAF|GRIDF;
	    prompt = "Fixed Star Chart Options:";
	    dp = fixed_dp;
	    ftype = FIXED_FILE;
	    load_orbs(FIXED_ORB);
	    break;
       case Problem :
	    ormsk = NATAL_CH;
	    op = setup_dat.getBirthOpt();
	    dp = birth_dp;
	    op.getCharts() &= TEXTF;
	    prompt = "Problem Report Options:";
	    ftype = PROBLEM_FILE;
	    load_orbs(NATAL_ORB);
	    break;
       default :
	    break;
       }
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 if ( !customizeScreen( prompt ) )
    return( 0 );
 dp.chart_code = op.getChartCode()| ormsk;
 return( ChartCompiler::doSetup() );
}

int OtherChartCompiler::compile()
{
 if ( chartType != Helio )
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
 else
    return( 1 );
}

int OtherChartCompiler::writeData()
{

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

 return( 1 );
}

int OtherChartCompiler::doReport()
{
char *arabtxt[3] = {ARABIC_SIGN, ARABIC_HOUSE, ARABIC_ASPECTS };
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
       }
 return( 1 );
}

int OtherChartCompiler::writeGrid()
{
 if ( chartType != Problem ) {
   if ( openFile( grid_file,0 ) == NULL )
       return( 0 );
   }
 else
    return ( 0 );
 switch( chartType ) {
       case Helio :
	    nh_print_grid( stream, birth_inf, &birth_rec,
		 op.getFlags(), op.getHouseMode()&0xf, &dp, comment_buf );
	    break;
       case Arabic :
	    nx_print_grid( stream, getArabicParts(), &birth_rec, op.getFlags(),
		  op.getHouseMode()&0xf, ARABP_DI, getArabicCount(), &dp,
		      "ARABICGRID", comment_buf  );
	    break;
       case Fixed :
	    nx_print_grid( stream, getFixedStars(), &birth_rec, op.getFlags(),
		 op.getHouseMode(), FIXED_DI, getFixedStarCount(), &fixed_dp,
		     "FIXEDSTGRID", comment_buf  );
	    break;
        default :
	    break;
       }
 return( 1 );
}



int OtherChartCompiler::cleanUp( int ok )
{
 switch( chartType ) {
       case Arabic :
	    close_arabic_pts();
	    break;
       case Fixed :
	    close_fixed_stars();
	    break;
       default :
	    break;
       }
 return( ChartCompiler::cleanUp( ok ) );
}
#endif
#ifdef DELUXE
ReturnChartCompiler::doSetup()
{
 op = setup_dat.getBirthOpt();
 op.getCharts() &= (GRIDF|TEXTF);
 ftype = SOLAR_RETURN_FILE+return_data.planet;
 dp = return_dp;
 if ( !customizeScreen( "Return Chart Options:" ) )
    return( 0 );
 return( ChartCompiler::doSetup() );
}


int ReturnChartCompiler::doReport()
{
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 return_chart( stream, return_data.planet, &birth_rec, setup_dat.getBirthOpt().getFlags(),
    setup_dat.getBirthOpt().getHouseMode()&0xf, &dp, comment_buf, 0, pDataArray, with_rec );
 return( 1 );
}

int ReturnChartCompiler::writeGrid()
{
 if ( openFile( grid_file, 0 ) == NULL )
    return( 0 );
 return_chart( stream, return_data.planet, &birth_rec, setup_dat.getBirthOpt().getFlags(),
    setup_dat.getBirthOpt().getHouseMode()&0xf, &dp, comment_buf, 1, NULL, NULL );
 return 1;
}

#endif
#ifdef PRO
ComTrnChartCompiler::doSetup()
{
 char buffer[120];
 op = setup_dat.getComptrOpt();
 dp = comptr_dp;
 ftype = COMPOTRAN_FILE;
 if ( !customizeScreen( "Composite Transits Chart Options:" ) )
    return( 0 );
 load_orbs(TRANS_ORB);
 dp.chart_code = op.getChartCode() | COMPO_CH|TRANS_CH|RELOC_CH;
 if ( dp.rdp->rect_system == -1 )
	 dp.rdp->rect_system = op.getDefRectMethod();
 strcpy( buffer, birth_rec.name );
 strcat( buffer, " & " );
 strcat( buffer, comp_rec.name );
 buffer[NAME_WIDTH] = '\0';
 buffer[NAME_WIDTH+1] = '\0';
 if ( makeFile( ftype, op.getCharts() & GRAPH, buffer, types[ftype] ) )
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
 if ( op.getCharts() & DATAF && op.getDatafile() == DATABIN ) {
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
    }
 return( 1 );
}

int ComTrnChartCompiler::doReport()
{
 if ( openFile( ast_file ) == NULL )
    return( 0 );
 cmtrans_print_results( stream, birth_inf, &birth_rec, &comp_rec,
	 op.getFlags(), alt_inf, &trans_rec, op.getHouseMode()&0xf, &dp, comment_buf, op.getCharts()&INTRP  );
 return( 1 );
}

int ComTrnChartCompiler::writeGrid()
{
 if ( openFile( grid_file,0 ) == NULL )
    return( 0 );
 cmtrans_print_grid( stream, birth_inf, ftype, &birth_rec, &comp_rec,
	op.getFlags(), alt_inf, &trans_rec, op.getHouseMode()&0xf, &dp, comment_buf  );
 return( 1 );
}

int ComTrnChartCompiler::writeGraph()
{
 extern AS_INF **trans_ptr;
 extern DATES *date_ptr;

 CompTransGraphWriter *gw = new CompTransGraphWriter( &birth_rec, birth_inf,
     ftype + LAST_NON_GRAPH, op.getFlags(), op.getHouseMode()&0xf, graph_ptr,
     &trans_rec, &transit_data, trans_ptr, date_ptr, &comp_rec );
 gw->save(graph_ptr->file_name, graph_ptr->folder);
 delete gw;
 return( 1 );
}
#endif

