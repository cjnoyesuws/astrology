#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "report_def.h"
#include "outfunc.fns"
#include "output.fns"
#include "errors.fns"
#include "textptr.h"

/* 09/15/92  Modified for C++ Windows */

int global_table = -1;
#define GLOBAL_NAME "GLOBAL"
extern int report_table;
extern int output_solar_header( FILE *stream, char *s1, DATA_PACKET *dpk, char *rpt );



int output_sex_codes( FILE *stream, int sex, int sexno, int table )
{
 fprintf( stream, "^%d", sexno );
 if ( sex )
    sex = CHH_FEMALE;
 else
    sex = CHH_MALE;

 return ( tb_write_text(table, sex, 0, stream ) );

 return( 1 );
}


int close_tables( int table, int global )
{
 tb_close_table( table );
 tb_close_table( global );
 global_table = -1;
 report_table = -1;
 return( 0 );
}


int get_tables( char *table_name, int *global )
{
 int table = -1;

 *global = tb_open_file( GLOBAL_NAME );
 if ( *global == -1 )
    return( -1 );
 global_table = *global;
 table = tb_open_file( table_name );
 if ( table == -1 ) {
    if ( global_table != -1 )
       tb_close_table( global_table );
    return( -1 );
    }
 return( table );
}


const char *get_report( int table, int gtable, int key )
{
 static char erf[] = { "Error in Report--Key %d Not Found see REPORT.SYM" };
 static char missing[] = {""};

 const char *report;

 report = tb_get_text( table, key, 0 );
 if ( report == NULL )
    report = tb_get_text( gtable, key, 0 );
 else
    return( report );
 if ( report == NULL ) {
    return( missing );
    }
 else
    return( report );
}

int output_birth_head_group( FILE *stream, BITS mode, BIRTH_DB *data,

   int table, int house_mode, char *cmt, DATA_PACKET *dpk, int gtable )
{
 const char *report;

 report = tb_get_text( table, CHH_MALE, 0 );
 if ( report == NULL )
    output_sex_codes( stream, data->sex, 1, gtable );
 else
    output_sex_codes( stream, data->sex, 1, table );
 if ( dpk->chart_code & TRANS_CH ) {
    report = get_report( table, gtable, CHT_TRANS_YB );
    if ( report == NULL )
       return( -1 );
    output_title( stream, data->name, data->name, cmt, (char *)report );
    }
 report = get_report( table, gtable, CHH_BIRTH);
 if ( report == NULL )
    return( -1 );
 output_birth_header( stream, mode, data,
	      data->name, house_mode, dpk, (char *)report  );

 if ( mode & NOBIRTHTIM ) {
    report = get_report( table, gtable, CHH_RECT );
    if ( report == NULL )
       return( -1 );
    output_rect_header( stream, dpk->rdp, data->name, (char *)report );
    }
 if ( house_mode != -1 ) {
    report = get_report( table, gtable, CHH_TS_HOUSE );
    if ( report == NULL )
       return( -1 );
    output_ts_house_mode( stream, data->name, mode, house_mode, (char *)report );
    }
#ifdef DELUXE
 if ( dpk->chart_code & RELOC_CH ) {
    report = get_report( table, gtable, CHH_RELOC_DAT );
    if ( report == NULL )
       return( -1 );
    output_reloc_header( stream, data->name, dpk, (char *)report );
    }

 if ( dpk->chart_code & PROGR_CH ) {
    if ( ( report = get_report( table, gtable, CHH_PROG ) ) == NULL )
       return( -1 );
    output_prog_header( stream, data->name, dpk, (char *)report );
    }
 if ( dpk->chart_code & SOLAR_CH ) {
    if ( ( report = get_report( table, gtable, CHSO_DATA ) ) == NULL )
       return( -1 );
    fprintf(stream, "\x80\x80");
	output_solar_header( stream, data->name, dpk, (char *)report );
    }
#endif
 return( 0 );
}



output_comp_head_group( FILE *stream, BITS mode, BIRTH_DB *data,
    BIRTH_DB *padata, int table, int house_mode, char *cmt,
					   DATA_PACKET *dpk, int gtable )
{
 const char *report;

 report = tb_get_text( table, CHH_MALE, 0 );
 if ( report == NULL )
    output_sex_codes( stream, data->sex, 1, gtable );
 else
    output_sex_codes( stream, data->sex, 1, table );
 if ( report == NULL )
    output_sex_codes( stream, padata->sex, 2, gtable );
 else
    output_sex_codes( stream, padata->sex, 2, table );

 if ( ( report = get_report( table, gtable, CHH_COMPAT_YB ) ) == NULL )
    return( -1 );
 output_title( stream, data->name, padata->name, cmt, (char *)report );

 if ( ( report = get_report( table, gtable, CHH_BIRTH ) ) == NULL )
    return( -1 );
 output_birth_header( stream, mode, data,
	      data->name, house_mode, dpk, (char *)report  );

 if ( mode & NOBIRTHTIM ) {
    if ( ( report = get_report( table, gtable, CHH_RECT ) ) == NULL )
       return( -1 );
    output_rect_header( stream, dpk->rdp, data->name, (char *)report );
    }

 if ( ( report = get_report( table, gtable, CHH_COMPAT_YB ) ) == NULL )
    return( -1 );
 output_title( stream, padata->name, data->name, cmt, (char *)report );

 if ( ( report = get_report( table, gtable, CHH_BIRTH ) ) == NULL )
    return( -1 );
 output_birth_header( stream, mode, padata,
	      padata->name, house_mode, dpk, (char *)report  );

 if ( mode & NOBIRTHTIM ) {
    if ( ( report = get_report( table, gtable, CHH_RECT ) ) == NULL )
       return( -1 );
    output_rect_header( stream, dpk->crdp, padata->name, (char *)report );
    }

 report = tb_get_text( table, CHH_TS_HOUSE, 0 );
 if ( ( report = get_report( table, gtable, CHH_TS_HOUSE ) ) == NULL )
    return( -1 );
 output_ts_house_mode( stream, data->name, mode, house_mode, (char *)report );

#ifdef DELUXE
 if ( dpk->chart_code & RELOC_CH ) {
    if ( ( report = get_report( table, gtable, CHH_RELOC_DAT ) ) == NULL )
       return( -1 );
    output_reloc_header( stream, data->name, dpk, (char *)report );
    }

 if ( dpk->chart_code & PROGR_CH ) {
    if ( ( report = get_report( table, gtable, CHH_PROG ) ) == NULL )
       return( -1 );
    output_prog_header( stream, data->name, dpk, (char *)report );
    }
#endif
 return( 0 );
}


int output_trans_head_group( FILE *stream, BITS mode, BIRTH_DB *data, char *cmt,
   int table, int house_mode, char *name, DATA_PACKET *dpk, int gtable )
{
 const char *report;

 if ( table == -1 || gtable == -1 )
    return( -1 );
 if ( ( report = get_report( table, gtable, CHT_TRANS_TD ) ) == NULL )
    return( -1 );
 output_title( stream, name, data->name, cmt, (char *)report );

 if ( ( report = get_report( table, gtable, CHH_BIRTH ) ) == NULL )
    return( -1 );
 output_birth_header( stream, mode, data,
	      data->name, house_mode, dpk, (char *)report  );
 if ( mode & NOBIRTHTIM ) {
    if ( ( report = get_report( table, gtable, CHH_RECT ) ) == NULL )
       return( -1 );
    output_rect_header( stream, dpk->rdp, data->name, (char *)report );
    }
 if ( house_mode != -1 ) {
    if ( ( report = get_report( table, gtable, CHH_TS_HOUSE ) ) == NULL )
       return( -1 );
    output_ts_house_mode( stream, data->name, mode, house_mode, (char *)report );
    }
#ifdef DELUXE
 if ( dpk->chart_code & RELOC_CH ) {
    if ( ( report = get_report( table, gtable, CHH_RELOC_DAT ) ) == NULL )
       return( -1 );
    output_reloc_header( stream, data->name, dpk, (char *)report );
    }
 if ( dpk->chart_code & PROGR_CH ) {
    if ( ( report = get_report( table, gtable, CHH_PROG ) ) == NULL )
       return( -1 );
    output_prog_header( stream, data->name, dpk, (char *)report );
    }
#endif
 if ( ( report = get_report( table, gtable, CHT_TRANS_PARAM ) ) == NULL )
    return( -1 );
 output_trans_header( stream, name, dpk, (char *)report );
 return( 0 );
}
