#include <stdio.H>
#include <stdio.H>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "astsed.h"
#include "astro.h"
#include "setup.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "output.fns"
#include "screens.fns"
#include "compute.fns"
#include "misc.fns"
#include "errors.fns"
#include "fileques.fns"
#include "charcons.h"
#include "fptr.h"
#include <math.h>
#include "tickle.h"
#include "utlduad.h"
#include "astro.fns"
#include "fixstar.h"
#include "arabpt.h"
#include "basedcs.h"
#include "oututil.h"

char _far ast_file[AS_MAX_PATH], _far graph_file[AS_MAX_PATH];
FILE_DB *out_file_ptr = NULL, *graph_ptr = NULL;
char comment_buf[80];

static int has_graph_file( int type )
{
 static char hgf[] = { 1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0 };

 return( (int)hgf[type-1] );
}


int check_ok( int ok, char *errmsg )
{
 static char fmt[] = "Your %s Screen is Not Complete--Use F10 To Complete Screen!!";
 char buf[130];
 if ( ok )
    return( 0 );
 alert_box( ERROR2, (char _far *)fmt, errmsg );
 do_msg( NULL );
 return( 1 );
}

/* Function to open a file and reallocate a file buffer to it. Created
   as a function to reduce redundant code */

FILE *dc_open_file( char *file )
{
 FILE *stream;

 if ( ( stream = fwrite_fptr( file, (NFDB *)out_file_ptr, 1) ) == NULL ) {
    do_msg( NULL );
    do_error( file );
    rem_file( file );
    return( NULL );
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 return( stream );
}

/* Function to test the value of errno, Basically as a function to
   reduce redundant code */

int dc_test_errno(void)
{
 if ( errno ) {
    rem_file(ast_file);
    if ( strcmp( graph_file, "" ) )
       rem_file( graph_file );
    return( 1 );
    }
 else
    return( 0 );
}

int dc_make_file( int type, int grsave, char *name )
{
 char ast[14], graph[14];
 status_bar( screen_st );
 memset( graph, 0, 14 );
 memset( ast, 0, 14 );
 if ( !has_graph_file(type) && grsave )
    grsave = 0;
 if ( do_add_file( type, grsave, name, ast, graph, &graph_ptr, &out_file_ptr ) ) {
    status_bar( break_st );
    do_msg( NULL );
    return( 1 );
    }
 strcpy( comment_buf, out_file_ptr->comment );
 assert( strlen( ast ) < sizeof( ast ) );
 if ( grsave )
    assert( strlen( graph) < sizeof( graph ) );
 status_bar( break_st );
 strcpy( ast_file, set_path( ast, TEMP_F ) );
 assert( strlen( ast_file ) < sizeof( ast_file ) );
 if ( grsave )
   strcpy( graph_file, set_path( graph, TEMP_F ) );
 else
   strcpy( graph_file, "" );
 assert( strlen( graph_file ) < sizeof( graph_file ) );
 que_keep = 0;
 return( 0 );
}

FILE *do_natal( OPTIONS *opp, int chart_type, DATA_PACKET *dpk, int file_type )
{
 DATA_PACKET dp = *dpk;
 FILE *stream;
 OPTIONS op = *opp;

 if ( !dp.rdp->birth_time_known )
    op.flags |= NOBIRTHTIM;
 dp.chart_code = op.chart_code|chart_type;
 if ( dc_make_file( file_type, op.charts & GRAPH, birth_rec.name ) )
    return( NULL );
 if ( x_kb_Check() )
    return( NULL );
 do_calc( birth_inf, &birth_rec.birth_data, op.flags, op.house_mode, &dp );
 if ( dc_test_errno() )
     return( NULL );
 if ( x_kb_Check() )
    return( NULL );
 if ( op.charts & GRAPH && has_graph_file(file_type) )
    save_graph_data( graph_file, file_type + LAST_NON_GRAPH, &birth_rec,
	  NULL, birth_inf, NULL, op.flags, op.flags, graph_ptr );
 if ( op.charts & TEXTF ) {
    if ( ( stream = dc_open_file( ast_file ) ) == NULL )
       return( NULL );
    fdata_write( stream, dp.chart_code );
    switch( file_type ) {
	  case NATAL_FILE :
	  case RELOCATION_FILE :
	       print_results( stream, birth_inf, &birth_rec, birth_ext,
		   op.flags, op.house_mode, &dp, comment_buf  );
	       break;
	  case NUMERIC_FILE :
	       num_print_results( stream, birth_inf, &birth_rec, birth_ext,
		   op.flags, op.house_mode, &dp, comment_buf );
	       break;
#ifdef PRO
	  case FIXED_FILE :
	       do_fixed_stars( op.flags, birth_rec.birth_data.birth_date.year );
	       if ( errno == ENOMEM )
		  return( stream );
	       nx_print_results( stream, fixed_stars, &birth_rec, op.flags,
		    op.house_mode, FIXED_DI, fixed_star_count, &fixed_dp, "FIXEDST",
			  comment_buf  );
	       break;
	  case ARABIC_FILE :
	       do_arabic_parts( op.flags, birth_rec.birth_data.birth_date.year );
	       if ( errno == ENOMEM )
		  return( stream );
	       nx_print_results( stream, arabic_parts, &birth_rec, op.flags,
		    op.house_mode, ARABP_DI, arabic_count, &arabp_dp, "ARABIC",
			 comment_buf  );
	       break;
	  case PROBLEM_FILE :
	       problem_solving_report( stream, birth_inf, &birth_rec,
		   op.flags, op.house_mode, &dp, comment_buf );
	       break;
#endif
	  default :
	       break;
	  }
    }
 else
    stream = NULL;

 if ( op.charts & DATAB ) {
    switch( file_type ) {
	  case NATAL_FILE :
	  case RELOCATION_FILE :
	  case NUMERIC_FILE :
	       bin_write_natal_chart( birth_inf, &birth_rec,
						     op.flags, &dp );
	       break;
#ifdef PRO
	  case FIXED_FILE :
	       bin_write_fixed_chart( birth_inf, &birth_rec,
						     op.flags, &dp );
	       break;
	  case ARABIC_FILE :
	       bin_write_arabic_chart( birth_inf, &birth_rec,
						     op.flags, &dp );
	       break;
#endif
	  default :
	       break;
	  }
    }
 else if ( op.charts & DATAC ) {
    switch( file_type ) {
	  case NATAL_FILE :
	  case RELOCATION_FILE :
	  case NUMERIC_FILE :
	       write_csv_natal( &birth_rec, birth_inf, op.flags,
		   op.house_mode, &dp, 18 );
	       break;
#ifdef PRO
	  case FIXED_FILE :
	       if ( fixed_stars != NULL )
		  write_csv_natal( &birth_rec, fixed_stars, op.flags,
		      op.house_mode, &dp, fixed_star_count );
	       break;
	  case ARABIC_FILE :
	       if ( arabic_parts != NULL )
		  write_csv_natal( &birth_rec, arabic_parts, op.flags,
		     op.house_mode, &dp, arabic_count );
	       break;
#endif
	  default :
	       break;
	  }
    }
 return( stream );
}




FILE *do_compat( OPTIONS *opp, int chart_type, DATA_PACKET *dpk, int file_type )
{
 char buffer[80];
 DATA_PACKET dp = *dpk;
 FILE *stream;
 OPTIONS op = *opp;
 static char BCS msg1[] = "Partner's Birth Information";
 static char BCS msg2[] = "Partner's Birth Rectification";

 dp.chart_code = op.chart_code|chart_type;

 if ( !dp.rdp->birth_time_known )
    op.flags |= NOBIRTHTIM;
 if ( check_ok( comp_ok, (char _far *) msg1 ) ||
      check_ok( comp_rect_ok,(char _far *) msg2 ) )
    return( NULL );
 strcpy( buffer, birth_rec.name );
 strcat( buffer, " & " );
 strcat( buffer, comp_rec.name );
 buffer[NAME_WIDTH] = '\0';
 if ( file_type != COMPOTRAN_FILE ) {
    if ( dc_make_file( file_type, op.charts & GRAPH,
	  buffer ) )
       return( NULL );
    }
 if ( x_kb_Check() )
    return( NULL );
 if ( file_type == COMPATIBILITY_FILE )
    do_comp_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	  alt_inf, op.flags, op.flags, op.house_mode, &dp );
 else
    do_composite_calc( &birth_rec.birth_data, birth_inf, &comp_rec.birth_data,
	  alt_inf, op.flags, op.flags, op.house_mode, &dp );
 if ( dc_test_errno() )
    return( NULL );
 if ( x_kb_Check() )
    return( NULL );
 if ( file_type == COMPOTRAN_FILE )
    return( NULL );
 if ( op.charts & GRAPH && has_graph_file(file_type) )
    save_graph_data( graph_file, file_type + LAST_NON_GRAPH, &birth_rec,
       &comp_rec, birth_inf, alt_inf, op.flags, op.flags, graph_ptr );
 if ( op.charts & TEXTF ) {
    if ( ( stream = dc_open_file( ast_file ) ) == NULL )
       return( NULL );
    fdata_write( stream, dp.chart_code );
    if ( file_type == COMPATIBILITY_FILE )
       comp_print_results( stream, birth_inf, &birth_rec,
	  op.flags, alt_inf, &comp_rec, op.house_mode, &dp, comment_buf );
    else
       compos_print_results( stream, birth_inf, birth_ext, alt_inf, alt_ext,&birth_rec,
	op.flags, &comp_rec, op.house_mode, &dp, comment_buf );
    }
 else
    stream = NULL;
 if ( file_type == COMPATIBILITY_FILE ) {
    if ( op.charts & DATAB )
       bin_write_compat_chart( birth_inf, alt_inf,
		&birth_rec, &comp_rec, op.flags, &dp );
    else if ( op.charts & DATAC )
       write_csv_compat( &birth_rec, &comp_rec,
	  birth_inf, alt_inf, op.flags, op.house_mode, &dp );
       }
 else {
    if ( op.charts & DATAB )
       bin_write_compos_chart( birth_inf, &birth_rec,
		      &comp_rec, op.flags, &compos_dp );
    else if ( op.charts & DATAC )
       write_csv_compos( &birth_rec, &comp_rec, birth_inf,
	    op.flags, op.house_mode, &dp );
    }
 return( stream );
}

int do_comp( int val )
{
 char buffer[65];
 static char msg1[] = "  COMPILING YOUR CHART...  ";
 static char msg2[] = "Birth Information";
 static char msg3[] = "Birth Rectification";
 static char msg4[] = "Compatability Chart:";
 static char msg5[] = "Transits Chart:";
 static char msg6[] = "Transit Information";
 static char msg7[] = "Transit Data";
 static char msg8[] = "Progression Chart:";
 static char msg9[] = "Progression Data";
 static char *rts[] = { "SOLAR", "LUNAR" };
 FILE *stream = NULL;
 int mode;
 OPTIONS op;
 DATA_PACKET dp;

 errno = 0;
 ast_file[0] = '\0';
 graph_file[0] = '\0';
 do_msg( (char _far *) msg1 );
 if ( check_ok( birth_ok, (char _far *) msg2 ) )
    return( val );
 if ( check_ok( birth_rect_ok, (char _far *) msg3 ) )
    return( val );
 status_bar( break_st );
 switch( val ) {
   case 1 :
	op = setup_dat.birth;
   case 2 :
	if ( val == 2 ) {
	   op = setup_dat.birth;
	   op.flags &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST);
	   }
   case 3 :
	if ( val == 3 ) {
	   op = setup_dat.birth;
	   op.flags &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST);
	   op.flags |= HOUSES;
	   }
   case 4 :
	if ( val == 4 ) {
	   op = setup_dat.birth;
	   op.flags &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST |
		EXT_ASPECTS | MISCELL);
	   op.flags |= (HOUSES | ASPECTS);
	   }
   case 5 :
	if ( val == 5 ) {
	   op = setup_dat.birth;
	   op.flags &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST | EXT_ASPECTS
		| EXT_CALCS | BASE_MID | FULL_MID | MID_ASPECT | HALF_MID);
	   op.flags |= (HOUSES | ASPECTS | MISCELL);
	   }
   case 6 :
	if ( val == 6 ) {
	   op = setup_dat.birth;
	   op.flags &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST | EXT_ASPECTS
	       | EXT_CALCS | BASE_MID | FULL_MID | MID_ASPECT | HALF_MID);
	   op.flags |= (HOUSES | ASPECTS | MISCELL | BASE_MID);
	   }
   case 7 :
	if ( val == 7 ) {
	   op = setup_dat.birth;
	   op.flags &= (SIDEREAL | SUMMARY | TEXT | VERT_EAST |
		  EXT_ASPECTS | MID_ASPECT);
	   op.flags |= (HOUSES | ASPECTS | MISCELL | FULL_MID | HALF_MID);
	   }
	if ( val == 2 || val == 3 || custom_scr( "Natal Chart:", &op, -1 ) )
	   stream = do_natal( &op, NATAL_CH, &birth_dp, NATAL_FILE );
	break;
   case 8 :
	op = setup_dat.compat;
	if ( custom_scr( (char _far *) msg4, &op, -1 ) )
	   stream = do_compat( &op, COMPA_CH, &comp_dp, COMPATIBILITY_FILE );
	break;
   case 9 :
	op = setup_dat.trans;
	dp = birth_dp;
	if ( !custom_scr( (char _far *) msg5, &op, -1 ) )
	   break;
	mode = op.flags;
	if ( check_ok( trans_ok, (char _far *) msg6 ) ||
	      check_ok( trans_data_ok, (char _far *) msg7 ) ) {
	   status_bar( main_st );
	   return( val );
	   }
	if ( x_kb_Check() )
	   break;
	dp.chart_code = op.chart_code;
	manage_transits( birth_inf, alt_inf, &birth_rec.birth_data,
	     &trans_rec.birth_data, mode, mode, op.house_mode, &trans_dp);
	if ( x_kb_Check() )
	   break;
	if ( dc_test_errno() )
	   break;
	if ( dc_make_file( TRANSITS_FILE, op.charts & GRAPH, birth_rec.name ) )
	   break;
	if ( x_kb_Check() )
	   break;
	if ( op.charts & GRAPH )
	   save_graph_data( graph_file, TRANSITS_GRAPH_FILE, &birth_rec,
		&trans_rec, birth_inf, alt_inf, mode, mode, graph_ptr );
	if ( op.charts & TEXTF ) {
	   if ( ( stream = dc_open_file( ast_file ) ) == NULL )
	      break;
	   if ( x_kb_Check() )
	      break;
	   fdata_write( stream, dp.chart_code );
	   trans_print_results( stream, birth_inf, &birth_rec, mode,
	       alt_inf, &trans_rec, op.house_mode, &trans_dp, comment_buf  );
	   }
	else
	   stream = NULL;
	if ( op.charts & DATAB )
	   bin_write_trans_chart( birth_inf, &birth_rec, &trans_rec,
				       mode, &trans_dp );
	else if ( op.charts & DATAC )
	   write_csv_trans( &birth_rec, birth_inf, op.flags,
			   &trans_rec, op.house_mode, &trans_dp );
	break;
    case 10 :
	op = setup_dat.progr;
	dp = progr_dp;
	if ( !custom_scr( (char _far *) msg8, &op, -1 ) )
	   break;
	mode = op.flags;
	dp.chart_code = op.chart_code;
	if ( x_kb_Check() )
	   break;
	if ( check_ok( prog_ok, (char _far *) msg9 ) ) {
	   status_bar( main_st );
	   return( val );
	   }
	do_full_progr( &birth_rec.birth_data, birth_inf, alt_inf,
	     op.flags, op.flags, op.house_mode, &progr_dp );
	if ( dc_test_errno() )
	   break;
	if ( x_kb_Check() )
	   break;
	if ( dc_make_file( PROGRESSED_FILE, op.charts & GRAPH,
		 birth_rec.name ) )
	   break;
	if ( op.charts & GRAPH )
	   save_graph_data( graph_file, PROGRESS_GRAPH_FILE, &birth_rec,
		NULL, birth_inf, alt_inf, mode, mode, graph_ptr );
	if ( op.charts & TEXTF ) {
	   if ( ( stream = dc_open_file( ast_file ) ) == NULL )
	      break;
	   if ( x_kb_Check() )
	      break;
	   fdata_write( stream, dp.chart_code );
	   prog_print_results( stream, alt_inf, &birth_rec,
	      setup_dat.progr.flags, setup_dat.progr.house_mode, &progr_dp, comment_buf  );
	   }
	else
	   stream = NULL;
	if ( op.charts & DATAB )
	   bin_write_prog_chart( birth_inf, &birth_rec,
					 op.flags, &progr_dp );
	else if ( op.charts & DATAC )
	   write_csv_prog( &birth_rec, birth_inf, op.flags,
					 op.house_mode, &progr_dp );
	break;
   case 11 :
	op = setup_dat.numer;
	if ( custom_scr( "Natal Chart:", &op, -1 ) )
	   stream = do_natal( &op, NATAL_CH, &birth_dp, NUMERIC_FILE );
	break;
   case 12 :
	if ( dc_make_file( SOLAR_RETURN_FILE+return_data.planet,
		0, birth_rec.name ) )
	   break;
	if ( ( stream = dc_open_file( ast_file ) ) == NULL )
	   break;
	dp = return_dp;
	fdata_write( stream, dp.chart_code );
	return_chart( stream, return_data.planet, &birth_rec, op.flags,
	     op.house_mode, &dp, comment_buf );
	break;
   case 13 :
	op = setup_dat.reloc;
	if ( custom_scr( "Relocation Chart:", &op, -1 ) )
	   stream = do_natal( &op, RELOC_CH, &reloc_dp, RELOCATION_FILE );
	break;
   case 14 :
	op = setup_dat.compos;
	if ( custom_scr( "Composite Chart:", &op, -1 ) )
	   stream = do_compat( &op, COMPO_CH, &comp_dp, COMPOSITE_FILE );
	break;
#ifdef PRO
   case 15 :
	op = setup_dat.comptr;
	if ( custom_scr( "Comp.Trans Chart:", &op, -1 ) ) {
	   if ( check_ok( trans_ok, "Transit Information" ) ||
		    check_ok( trans_data_ok, "Transit Data" ) ) {
	      status_bar( main_st );
	      return( val );
	      }
	   do_compat( &op, COMPO_CH|TRANS_CH, &comptr_dp, COMPOTRAN_FILE );
	   }
	else
	   break;
	mode = op.flags;
	if ( x_kb_Check() )
	   break;
	dp.chart_code = op.chart_code;
	manage_transits( birth_inf, alt_inf, &birth_rec.birth_data,
	     &trans_rec.birth_data, mode, mode, op.house_mode, &comptr_dp);
	if ( x_kb_Check() )
	   break;
	if ( dc_test_errno() )
	   break;
	strcpy( buffer, birth_rec.name );
	strcat( buffer, " & " );
	strcat( buffer, comp_rec.name );
	buffer[NAME_WIDTH] = '\0';
	if ( dc_make_file( COMPOTRAN_FILE, op.charts & GRAPH, buffer ) )
	   break;
	if ( x_kb_Check() )
	   break;
	if ( op.charts & GRAPH )
	   save_graph_data( graph_file, COMPTR_GRAPH_FILE, &birth_rec,
		&comp_rec, birth_inf, alt_inf, mode, mode, graph_ptr );
	if ( op.charts & TEXTF ) {
	   if ( ( stream = dc_open_file( ast_file ) ) == NULL )
	      break;
	   if ( x_kb_Check() )
	      break;
	   fdata_write( stream, dp.chart_code );
	   cmtrans_print_results( stream, birth_inf, &birth_rec, &comp_rec,
		mode, alt_inf, &trans_rec, op.house_mode, &trans_dp, comment_buf  );
	   }
	else
	   stream = NULL;
	if ( op.charts & DATAB )
	   bin_write_cmtrans_chart( birth_inf, &birth_rec, &trans_rec, &comp_rec,
				       mode, &comptr_dp );
	else if ( op.charts & DATAC )
	   write_csv_cmtrans( &birth_rec, birth_inf, op.flags,
		     &trans_rec, &comp_rec, op.house_mode, &trans_dp );
	break;
   case 16 :
	op = setup_dat.fixstar;
	op.charts &= TEXTF|DATAB|DATAC;
	if ( custom_scr( "Fixed Star Chart:", &op, -1 ) ) {
	   op.charts &= TEXTF|DATAB|DATAC;
	   stream = do_natal( &op, FIXED_CH, &fixed_dp, FIXED_FILE );
	   }
	 break;
   case 17 :
	op = setup_dat.arabpt;
	op.charts &= TEXTF|DATAB|DATAC;
	if ( custom_scr( "Arabic Points Chart:", &op, -1 ) ) {
	   op.charts &= TEXTF|DATAB|DATAC;
	   stream = do_natal( &op, ARABP_CH, &arabp_dp, ARABIC_FILE );
	   }
	 break;
   case 18 :
	op = setup_dat.birth;
	dp = birth_dp;
	op.charts &= TEXTF;
	if ( !custom_scr( "Heliocentric Chart:", &op, -1 ) )
	   break;
	op.charts &= TEXTF;
	mode = op.flags;
	if ( x_kb_Check() )
	   break;
	dp.chart_code = op.chart_code;
	if ( check_ok( birth_ok, "Birth Data" ) ) {
	   status_bar( main_st );
	   return( val );
	   }
	helio_do_calc( birth_inf, &birth_rec.birth_data, op.flags, &birth_dp );
	if ( dc_make_file( HELIO_FILE, op.charts & GRAPH,
		 birth_rec.name ) )
	   break;
	if ( op.charts & TEXTF ) {
	   if ( ( stream = dc_open_file( ast_file ) ) == NULL )
	      break;
	   if ( x_kb_Check() )
	      break;
	   fdata_write( stream, dp.chart_code );
	   nh_print_results( stream, birth_inf, &birth_rec,
	      op.flags, op.house_mode, &birth_dp, comment_buf );
	   }
	break;
   case 19 :
	op = setup_dat.birth;
	dp = birth_dp;
	op.charts &= TEXTF;
	if ( custom_scr( "Problem Report:", &op, -1 ) )
	   stream = do_natal( &op, NATAL_CH, &dp, PROBLEM_FILE );
	 break;
#endif
   default :
	break;
    }
 do_msg( NULL );
 if ( errno == ENOMEM )
    do_mem_error( 0 );
 if ( errno ) {
    if ( stream != NULL ) {
       if ( ferror( stream ) ) {
	  do_error( ast_file );
	  rem_file( ast_file );
	  }
       fclose( stream );
       }
 }
 else if ( !errno && stream != NULL )
    fclose( stream );
 errno = 0;
 tickle_do();
 mem_reclaim( birth_inf, alt_inf, &transit_data, mode );
 status_bar( main_st );
 return( val );
}
