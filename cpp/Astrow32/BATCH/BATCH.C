#include <stdio.h>
#include <string.h>
#include <search.h>
#include <stdlib.h>
#include <dos.h>
#include <share.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <cscape.h>
#include <kbrecord.h>
#include <scancode.h>
#include <oakpriv.h>
#include <winpriv.h>
#include "astro.fns"
#include "setup.h"
#include "screens.fns"
#include "batch.fns"
#include "fileques.fns"
#include "errors.fns"
#include "output.fns"
#include "charcons.h"
#include "basedcs.h"
#include <ctype.h>

typedef struct CMD {
	char name[20];
	int (*exec)();
	int (*proc)( FILE *stream, struct CMD *cm );
	} CMD;

char *bptrs[7];

int blnicmp( const void *p1, const void *p2 );

#define MAX_LABEL 20

long labels[20];
long returns[20];
long repeat_target[4] = { -1L,-1L,-1L,-1L };
int repeat_count[4] = { 0,0,0,0 };
int go_no = 0, rep_no = 0;

#define NCMD 63

CMD _far cmds[NCMD] = { /*
		   ########################################
		   Sorted for bsearch(). Make changes Below
		   ######################################## */
		   "CO",              do_comp, menu_cmd,
		   "COMPILE",         do_comp, menu_cmd,
		   "CONVERT",         do_conv_text,  do_output_cmd,
		   "CT",              do_conv_text,  do_output_cmd,
		   "DOS",             dos,   dos_f_cmd,
		   "EED",             do_get_data, menu_cmd,
		   "END_REPEAT",      NULL,        end_repeat_cmd,
		   "ENTER_EDIT",      do_get_data, menu_cmd,
		   "ER",              NULL,        end_repeat_cmd,
		   "GC",              do_graph_ptr,  do_graph_cmd,
		   "GOSUB",           NULL,          gosub_cmd,
		   "GP",              do_graph_ptr,  do_graph_cmd,
		   "GRAPH_C_PRINT",   do_graph_ptr,  do_graph_cmd,
		   "GRAPH_PRINT",     do_graph_ptr,  do_graph_cmd,
		   "GRAPH_VIEW",      do_graph_ptr,  do_graph_cmd,
		   "GS",              NULL,          gosub_cmd,
		   "GV",              do_graph_ptr,  do_graph_cmd,
		   "IF",              import_file,   prgf_cmd,
		   "IMPORT_FILE",     import_file,   prgf_cmd,
		   "IMPORT_RECORD",   NULL,          do_import_cmd,
		   "IR",              NULL,          do_import_cmd,
		   "KI",              do_kill_file,  do_kill_cmd,
		   "KILL",            do_kill_file,  do_kill_cmd,
		   "LA",              NULL,          label_cmd,
		   "LABEL",           NULL,          label_cmd,
		   "LBD",             read_birth_data, birthf_cmd,
		   "LM",              load_macros,   prgf_cmd,
		   "LOAD_BIRTH_DAT",  read_birth_data, birthf_cmd,
		   "LOAD_MACROS",     load_macros,   prgf_cmd,
		   "OP",              do_op, menu_cmd,
		   "OPTIONS",         do_op, menu_cmd,
		   "PO",              NULL,  progr_ofs,
		   "PR",              do_print_file, do_output_cmd,
		   "PRINT",           do_print_file, do_output_cmd,
		   "PROGR_OFS",       NULL,  progr_ofs,
		   "QT",              NULL, menu_cmd,
		   "QUIT",            NULL, menu_cmd,
		   "RB",              do_batch,    prgf_cmd,
		   "REP",             NULL, repeat_cmd,
		   "REPEAT",          NULL, repeat_cmd,
		   "RETURN",          NULL, return_cmd,
		   "RK",              NULL,        run_keys_cmd,
		   "RT",              NULL, return_cmd,
		   "RUN_BATCH",       do_batch,    prgf_cmd,
		   "RUN_KEYS",        NULL,        run_keys_cmd,
		   "SAVE_BIRTH_DAT",  write_birth_data, birthf_cmd,
		   "SBD",             write_birth_data, birthf_cmd,
		   "SH",              shell, NULL,
		   "SHELL",           shell, NULL,
		   "TC",              NULL,  trans_count,
		   "TD",              NULL,  trans_date,
		   "TO",              NULL,  trans_ofs,
		   "TRANS_COUNT",     NULL,  trans_count,
		   "TRANS_DATE",      NULL,  trans_date,
		   "TRANS_OFS",       NULL,  trans_ofs,
		   "TRANS_TODAY",     NULL,  trans_today,
		   "TT",              NULL,  trans_today,
		   "UT",              do_ut, menu_cmd,
		   "UTILITIES",       do_ut, menu_cmd,
		   "VI",              do_view,       do_output_cmd,
		   "VIEW",            do_view,       do_output_cmd,
		   "VIEW_PRINT",      do_view_print, menu_cmd,
		   "VP",              do_view_print, menu_cmd
		   /* ##############################################
		   unsorted for bsearch() make changes here,
		   save this section to a file sort and replace top
		   #################################################
		   "RUN_KEYS",        NULL,        run_keys_cmd,
		   "RK",              NULL,        run_keys_cmd,
		   "LM",              load_macros,   prgf_cmd,
		   "LOAD_MACROS",     load_macros,   prgf_cmd,
		   "RB",              do_batch,    prgf_cmd,
		   "RUN_BATCH",       do_batch,    prgf_cmd,
		   "GOSUB",           NULL,          go_cmd,
		   "GS",              NULL,          go_cmd,
		   "END_REPEAT",      NULL,        end_repeat_cmd,
		   "ER",              NULL,        end_repeat_cmd,
		   "LA",              NULL,          label_cmd,
		   "LABEL",           NULL,          label_cmd,
		   "REP",             NULL, repeat_cmd,
		   "REPEAT",          NULL, repeat_cmd,
		   "RETURN",          NULL, return_cmd,
		   "RT",              NULL, return_cmd,
		   "EED",             do_get_data, menu_cmd,
		   "CO",              do_comp, menu_cmd,
		   "VP",              do_view_print, menu_cmd,
		   "UT",              do_ut, menu_cmd,
		   "OP",              do_op, menu_cmd,
		   "QT",              NULL, menu_cmd,
		   "LBD",             read_birth_data, birthf_cmd,
		   "SBD",             write_birth_data, birthf_cmd,
		   "SH",              shell, NULL,
		   "TD",              NULL,  trans_date,
		   "TT",              NULL,  trans_today,
		   "TO",              NULL,  trans_ofs,
		   "TC",              NULL,  trans_count,
		   "PO",              NULL,  progr_ofs,
		   "VI",              do_view,       do_output_cmd,
		   "CT",              do_conv_text,  do_output_cmd,
		   "PR",              do_print_file, do_output_cmd,
		   "GV",              do_graph_ptr,  do_graph_cmd,
		   "GP",              do_graph_ptr,  do_graph_cmd,
		   "GC",              do_graph_ptr,  do_graph_cmd,
		   "KI",              do_kill_file,  do_kill_cmd,
		   "IF",              import_file,   birthf_cmd,
		   "IR",              NULL,          do_import_cmd,
		   "ENTER_EDIT",      do_get_data, menu_cmd,
		   "COMPILE",         do_comp, menu_cmd,
		   "VIEW_PRINT",      do_view_print, menu_cmd,
		   "UTILITIES",       do_ut, menu_cmd,
		   "OPTIONS",         do_op, menu_cmd,
		   "QUIT",            NULL, menu_cmd,
		   "LOAD_BIRTH_DAT",  read_birth_data, birthf_cmd,
		   "SAVE_BIRTH_DAT",  write_birth_data, birthf_cmd,
		   "SHELL",           shell, NULL,
		   "DOS",             dos,   dos_f_cmd,
		   "TRANS_DATE",      NULL,  trans_date,
		   "TRANS_TODAY",     NULL,  trans_today,
		   "TRANS_OFS",       NULL,  trans_ofs,
		   "TRANS_COUNT",     NULL,  trans_count,
		   "PROGR_OFS",       NULL,  progr_ofs,
		   "VIEW",            do_view,       do_output_cmd,
		   "CONVERT",         do_conv_text,  do_output_cmd,
		   "PRINT",           do_print_file, do_output_cmd,
		   "GRAPH_VIEW",      do_graph_ptr,  do_graph_cmd,
		   "GRAPH_PRINT",     do_graph_ptr,  do_graph_cmd,
		   "GRAPH_C_PRINT",   do_graph_ptr,  do_graph_cmd,
		   "IMPORT_FILE",     import_file,   birthf_cmd,
		   "IMPORT_RECORD",   NULL,          do_import_cmd,
		   "KILL",            do_kill_file,  do_kill_cmd,
		   */
		   };


void eat_line( FILE *stream )
{
 while ( fgetc( stream ) != '\n' );
 return;
}


int repeat_cmd( FILE *stream, CMD *cm )
{
 static char BCS msg[] = {"Either Too Many Nested Repeats or No Repeat Count!!" };
 int arg;

 fscanf( stream, "%d", &arg );
 eat_line( stream );
 if ( arg > 0 && rep_no < 4 ) {
    repeat_target[rep_no] = ftell( stream );
    repeat_count[rep_no] = arg-1;
    rep_no++;
    return( 0 );
    }
 else {
    alert_box( ERROR2, (char _far *)msg );
    return( 1 );
    }
}


int find_return( FILE *stream )
{
 char buf[25];
 do {
   fscanf( stream, "%s", buf );
   eat_line( stream );
 } while ( blnicmp( buf, "RETURN" ) && blnicmp( buf, "RT" ) );
 return( 0 );
}


int label_cmd( FILE *stream, CMD *cm )
{
 static char BCS msg[] = {"ILLEGAL LABEL!" };
 int arg;

 fscanf( stream, "%d", &arg );
 eat_line( stream );
 if ( arg > 0 && arg < MAX_LABEL ) {
    labels[arg-1] = ftell( stream );
    find_return( stream );
    return( 0 );
    }
 else {
    alert_box( ERROR2, (char _far *)msg );
    find_return( stream );
    return( 1 );
    }
}

int run_key_string( char *string, int key, char *name )
{
 char buf[150];
 strcpy( buf, name );
 strcat( buf, ":" );
 strcat( buf, string );
 key_SetMacroStr(buf);
 wmgr_SetReplyStash(MOU_IGNORE);
 kb_Stuff( key );
}

int run_keys_cmd( FILE *stream, CMD *cm )
{
 static char BCS kn[] = {"{ALT_FN10}"};
 static char BCS fmt[] = {"%137[^\n]"};
 char buf[150];

 fscanf( stream, (char _far *)fmt, buf );
 run_key_string( buf, ALT_FN10, kn );
 eat_line(stream);
 return( 0 );
}


int gosub_cmd( FILE *stream, CMD *cm )
{
 static char BCS msg[] = {"Too Many Nested GOSUBs!!" };
 static char BCS msg2[] = { "ILLEGAL LABEL!" };
 int arg;

 fscanf( stream, "%d", &arg );
 eat_line( stream );
 if ( arg > 0 && arg < MAX_LABEL && labels[arg-1] != -1L ) {
    if ( go_no < MAX_LABEL )
       returns[go_no++] = ftell( stream );
    else
       alert_box( ERROR2, (char _far *)msg );
    fseek( stream, labels[arg-1], SEEK_SET );
    return( 0 );
    }
 else {
    alert_box( ERROR2, (char _far *)msg2 );
    return( 1 );
    }
}


int return_cmd( FILE *stream, CMD *cm )
{
 static char BCS msg[] = { "RETURN Without GOSUB!!" };

 eat_line( stream );
 if ( go_no > 0 && returns[go_no-1] != -1L ) {
    fseek( stream, returns[--go_no], SEEK_SET );
    return( 0 );
    }
 else {
    alert_box( ERROR2, (char _far *)msg );
    return( 1 );
    }
}

int end_repeat_cmd( FILE *stream, CMD *cm )
{
 static char BCS msg[] = {"Missing REPEAT for END_REPEAT!!" };

 eat_line( stream );
 if ( rep_no && repeat_count[rep_no-1] && repeat_target[rep_no-1] != -1L ) {
    fseek( stream, repeat_target[rep_no-1], SEEK_SET );
    repeat_count[rep_no-1]--;
    return( 0 );
    }
 else if (rep_no && !repeat_count[rep_no-1] ) {
    rep_no--;
    return( 0 );
    }
 else if ( !rep_no && repeat_target[0] == -1L ) {
    alert_box( ERROR2, (char _far *)msg );
    return( 1 );
    }
 else
    return( 0 );
}



int menu_cmd( FILE *stream, CMD *cm )
{
 char buf[10];
 int arg = 0;

 fscanf( stream, "%s", buf );
 if ( isalpha(buf[0] ) )
    arg = toupper(buf[0]-'A'+10);
 else
    arg = atoi(buf);
 eat_line( stream );
 if ( cm->exec == NULL ) {
    fclose( stream );
    exit( arg );
    }
 return( !(cm->exec( "", arg ) == arg) );
}

int prgf_cmd( FILE *stream, CMD *cm )
{
 char fname[75];
 char file[75];

 fscanf( stream, "%s", fname );
 eat_line( stream );
 return( cm->exec( fname ) );
}




int birthf_cmd( FILE *stream, CMD *cm )
{
 char fname[75];
 char file[75];

 fscanf( stream, "%s", file );
 eat_line( stream );
 if ( strchr( file, ':' ) != NULL || strchr( file, '\\' ) != NULL )
    strcpy( fname, file );
 else
    strcpy( fname, set_path( file, USER_F ) );
 return( cm->exec( fname ) );
}

int shell(void)
{
 shell_process( "COMMAND", NULL, NULL, NULL, NULL, NULL );
 return( 0 );
}

int dos_f_cmd( FILE *stream, CMD *cm )
{
 int i = 1, c;
 static char file[75];

 fscanf( stream, "%s", file );
 bptrs[0] = strdup( file );
 do {
    c = fgetc( stream );
    if ( c == '\n' )
       break;
    fscanf( stream, "%s", file );
    bptrs[i++] = strdup( file );
    } while ( i < 6 );
 if ( c != '\n' )
    eat_line( stream );
 return( cm->exec() );
}

int dos(void)
{
 int i;
 shell_process( bptrs[0], bptrs[1], bptrs[2], bptrs[3], bptrs[4], bptrs[5] );
 for ( i = 0; i < 7; ++i ) {
     if ( bptrs[i] != NULL )
	free( bptrs[i] );
     }
 return( 0 );
}

int trans_count( FILE *stream, CMD *cm )
{
 int i;

 fscanf( stream, "%d", &i );
 if ( i )
    transit_data.num_transits = i;
 eat_line( stream );
 return( 0 );
}

int trans_ofs( FILE *stream, CMD *cm )
{
 int i, j;

 fscanf( stream, "%d, %d", &i, &j );
 if ( j ) {
    transit_data.interval_date.month = i;
    transit_data.interval_date.day = j;
    }
 eat_line( stream );
 return( 0 );
}

int trans_date( FILE *stream, CMD *cm )
{
 int m, d, y;

 fscanf( stream, "%d/%d/%d", &m, &d, &y );
 trans_rec.birth_data.birth_date.month = m;
 trans_rec.birth_data.birth_date.day = d;
 trans_rec.birth_data.birth_date.year = y;
 eat_line( stream );
 return( 0 );
}

int progr_ofs( FILE *stream, CMD *cm )
{
 int m, d, y;

 fscanf( stream, "%d/%d/%d", &y, &m, &d );
 progress_data.offset.month = m;
 progress_data.offset.day = d;
 progress_data.offset.year = y;
 eat_line( stream );
 return( 0 );
}

int trans_today( FILE *stream, CMD *cm )
{
 struct dosdate_t d;

 _dos_getdate( &d );
 trans_rec.birth_data.birth_date.month = d.month;
 trans_rec.birth_data.birth_date.day = d.day;
 trans_rec.birth_data.birth_date.year = d.year;
 eat_line( stream );
 return( 0 );
}


int do_kill_cmd(FILE *stream, CMD *cm )
{
 char opr[25];
 FILE_DB *ptr;
 int i;

 fscanf( stream, "%s", opr );
 if ( opr[0] == 'M' || opr[0] == 'm' ) {
    eat_line( stream );
    cm->exec(NULL);
    return( 0 );
    }
 i = atoi(opr);
 if ( !i && strstr(opr,"0") == NULL ) {
    if ( !fscanf( stream, "%d", &i ) )
       i = 0;
    if ( opr[0] == 't' || opr[0] == 'T' )
       ptr = que_top_plus_ptr(i, ALL_F);
    else
       ptr = que_bottom_minus_ptr(i, ALL_F);
    eat_line( stream );
    cm->exec(ptr);
    return( 0 );
    }
 else
    ptr = que_top_plus_ptr( i, ALL_F);
 eat_line( stream );
 cm->exec(ptr);
 return( 0 );
}



int do_output_cmd(FILE *stream, CMD *cm )
{
 char opr[25];
 FILE_DB *ptr;
 int i;

 fscanf( stream, "%s", opr );
 if ( opr[0] == 'M' || opr[0] == 'm' ) {
    eat_line( stream );
    cm->exec(NULL);
    return( 0 );
    }
 i = atoi(opr);
 if ( !i && strstr(opr,"0") == NULL ) {
    if ( !fscanf( stream, "%d", &i ) )
       i = 0;
    if ( opr[0] == 't' || opr[0] == 'T' )
       ptr = que_top_plus_ptr(i, NON_GRA);
    else
       ptr = que_bottom_minus_ptr(i, NON_GRA);
    eat_line( stream );
    cm->exec(ptr);
    return( 0 );
    }
 else
    ptr = que_top_plus_ptr( i, NON_GRA );
 eat_line( stream );
 cm->exec(ptr);
 return( 0 );
}


int do_graph_cmd(FILE *stream, CMD *cm )
{
 char opr[25];
 FILE_DB *ptr = NULL;
 int i, dr;

 fscanf( stream, "%s", opr );
 if ( opr[0] == 'M' || opr[0] == 'm' ) {
    if ( strchr( cm->name, 'V' ) != NULL ||
		strchr( cm->name, 'v' ) != NULL )
       cm->exec(ptr, 0);
    else if ( strchr( cm->name, 'C' ) != NULL ||
		strchr( cm->name, 'c' ) != NULL ) {
       fscanf( stream, "%d", &dr );
       cm->exec(ptr, dr);
       }
    else
       cm->exec(ptr, -1);
    eat_line( stream );
    return( 0 );
    }
 i = atoi(opr);
 if ( !i && strstr(opr,"0") != NULL ) {
    if ( !fscanf( stream, "%d", &i ) )
       i = 0;
    if ( opr[0] == 't' || opr[0] == 'T' )
       ptr = que_top_plus_ptr(i, GRA_F);
    else
       ptr = que_bottom_minus_ptr(i, GRA_F);
    if ( strchr( cm->name, 'V' ) != NULL ||
		strchr( cm->name, 'v' ) != NULL)
       cm->exec(ptr, 0);
    else if ( strchr( cm->name, 'C' ) != NULL ||
		strchr( cm->name, 'c' ) != NULL ) {
       fscanf( stream, "%d", &dr );
       cm->exec(ptr, dr);
       }
    else
       cm->exec(ptr, -1);
    eat_line( stream );
    return( 0 );
    }
 else
    ptr = que_top_plus_ptr( i, GRA_F );
 if ( strchr( cm->name, 'V' ) != NULL ||
		strchr( cm->name, 'v' ) != NULL )
    cm->exec(ptr, 0);
 else if ( strchr( cm->name, 'C' ) != NULL ||
		strchr( cm->name, 'c' ) != NULL ) {
    fscanf( stream, "%d", &dr );
    cm->exec(ptr, dr);
    }
 else
    cm->exec(ptr, -1);
 eat_line( stream );
 return( 0 );
}

int do_import_cmd(FILE *stream, CMD *cm )
{
 int type;
 char code[5];

 fscanf( stream, "%s", code );
 type = import_record_code_type( code );
 import_data_record( type, stream );
 return( 0 );
}


int blnicmp( const void *p1, const void *p2 )
{
 int l1 = strlen(p1), l2 = strlen(p2), l;

 if ( l1 > l2 )
    l = l2;
 else
    l = l1;
 return( strnicmp( (char *)p1, (char *)p2, l ) );
}


int do_batch_line( FILE *stream )
{
 static char BCS msg[] = {"Illegal Command: %s!" };
 CMD *cmdf;
 int n;
 char buf[25], erbuf[50];

 fscanf( stream, "%s", buf );
 n = NCMD;
 cmdf =(struct CMD *) bsearch( buf, cmds, n, sizeof( struct CMD ), blnicmp );
 if ( cmdf == NULL ) {
    sprintf( erbuf, (char _far *)msg, buf );
    alert_box( ERROR2, erbuf );
    eat_line( stream );
    return( 1 );
    }
 else if ( cmdf->proc == NULL && cmdf->exec != NULL ) {
    eat_line( stream );
    return( cmdf->exec() );
    }
 else if ( cmdf->proc != NULL )
    return( cmdf->proc( stream, cmdf ) );
 else
    eat_line( stream );
 return( 0 );
}

int do_batch( char *batch_file )
{
 char buf[150];
 int c = 0, ret = 0;
 FILE *stream;

 if ( ( stream = _fsopen( batch_file, "rt", SH_DENYWR ) ) == NULL ) {
    do_error( batch_file );
    return( 1 );
    }
 do {
 c = fgetc( stream );
 switch( c ) {
       case '#' :  /* comment line */
	    fgets( buf, 149, stream );
	    break;
       case ' '  :
       case '\n' :
       case '\t' :
       case EOF  :
	    break;
       default :
	    ungetc( c, stream );
	    ret = do_batch_line( stream );
	    break;
       }
 } while ( !ret && c != EOF && !ferror( stream ) );
 if ( ferror( stream ) ) {
    do_error( batch_file );
    ret = 1;
    }
 else
    ret = 0;
 fclose( stream );
 que_keep = 0;
 return( ret );
}
