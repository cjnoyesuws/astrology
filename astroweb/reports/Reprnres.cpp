#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include "output.fns"
#include "outfunc.fns"
#include "charcons.h"
#include "report_def.h"
#include "textptr.h"


int return_print_header( FILE *stream, char *chart, BIRTH_DB *data,
 RETURN_DATA *retd, DATA_PACKET *dpk, int house_mode, char *comment, int table )
{
 int er;
 char buf[50];
 const char *report = tb_get_text( table, CHR_RETURN_DATA, 0 );
 if ( report == NULL )
    return( -1 );
 er = output_return_head( stream, enquote_strclip((unsigned char *)data->name, (unsigned char *)buf), data,
      retd, dpk, house_mode, (char *)report );
 if ( !er ) {
    report = tb_get_text( table, CHR_RETURN_HD, 0 );
    if ( report == NULL )
       return( -1 );
    return ( output_return_title( stream, retd->planet, enquote_strclip((unsigned char *)data->name, (unsigned char *)buf),
	 comment, (char *)report ) );
    }
 else
   return( er );
}

int return_print_entry( FILE *stream, DATES *d, TIM *t, int ap, int table,
 char *name, int chart, int reno )
{
 int iret;
 static const char *report;
 if ( reno == 1 )
    report = tb_get_text( table, CHR_RETURN_ITM, 0 );
 if ( report == NULL )
    return( -1 );
 iret = output_return_entry( stream, chart, reno, d, t, ap, name, (char *)report );
 return( iret );
}
