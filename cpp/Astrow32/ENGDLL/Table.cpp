#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <share.h>
#include "tableptr.h"
#include <assert.h>
#include "errors.fns"
#include "output.fns"
#include "paths.hpp"
#error "Are you sure you need TABLE in the DLL?"

extern char *data_name( char * );

/* 09/10/92  Modified for C++ Windows */

#define NDIAG          1
#define NO_TBLFIL      17
#define SECTOR_SIZE 256
#define TWO_SECTORS 512
/* enough size for trailing '\n' plus '\0' + */
#define BUF_SIZE TWO_SECTORS+3

TBLFIL *table_ptr = NULL;
int no_table = 0;       /* number of positions used */
int tb_used = 0;


/* Kill memory associated to ems files */

/* close all the files associated with a specific text file.
   Marks the file closed. Also if there are no open files, it frees up
   the memory associated with them. Returns 0 for success, 1 for error */

int __export tb_close_table( int table_num )
{
 int er = 0;
 TBLFIL *pt;

 if ( table_num < 0  )
    return( 1 );
 assert( table_num < NO_TBLFIL && table_num >= 0 );
 pt = table_ptr + table_num;
 if ( pt->nd_open == MEM ) {
    delete( pt->index );
    pt->index = NULL;
    }
 if ( pt->tb_open == MEM ) {
    delete( pt->text );
    pt->text = NULL;
    }
 if ( pt->tb_open == MEM && pt->nd_open == MEM ) {
    --no_table;
    pt->name[0] = '\0';
    }
 if ( !no_table ) {
    delete table_ptr;
    table_ptr = (TBLFIL __far *)NULL;
    }
 return( 0 );
}

char *tb_get_ptr( TBLFIL *tb, int item )
{
 if ( item < tb->start || item > tb->end )
    return( NULL );
 item -= tb->start;
 if ( tb->index[item] == -1 )
    return( NULL );
 return( tb->text+tb->index[item] );
}


char * tb_get_text( int table_num, int item )
{
 int er = 0;
 TBLFIL *pt;

 if ( table_num < 0  )
    return( NULL );
 assert( table_num < NO_TBLFIL && table_num >= 0 );
 pt = table_ptr + table_num;
 if ( pt->nd_open == CLOSED || pt->tb_open == CLOSED )
    return( NULL );
 return( tb_get_ptr( pt, item ) );
}

int __export tb_write_text( FILE *stream, int table_num, int item )
{
 int er = 0;
 TBLFIL *pt;

 if ( table_num < 0  )
    return( -1 );
 assert( table_num < NO_TBLFIL && table_num >= 0 );
 pt = table_ptr + table_num;
 if ( pt->nd_open == CLOSED || pt->tb_open == CLOSED )
    return( -1 );
 return( fputs( tb_get_ptr( pt, item ), stream ) );
}

int __export tb_open_file( char *name )
{
 int table_num = 0, h1, l, flag, *ip, er;
 char *tx, file[150], base[15], *xp;
 TBLFIL *pt;
 long ll;

 if ( table_ptr == NULL ) {
    table_ptr = new TBLFIL[NO_TBLFIL];
    if ( table_ptr == NULL ) {
       do_mem_error( 0 );
       return( -1 );
       }
    no_table = 0;
    tb_used = 0;
    memset( table_ptr, 0, NO_TBLFIL * sizeof( TBLFIL ) );
    pt = table_ptr;
    }
 else {
    table_num = ++no_table;
    ++no_table;
    ++tb_used;
    pt = table_ptr + table_num;
    }
 assert( table_num < NO_TBLFIL );
 strcpy( base, name );
 strcpy( pt->name, name );
 strcat( base, ".TBL" );
 strcpy( file, data_name( base ) );
 assert( strlen( file ) < sizeof(file) );
 if ( ( h1 = sopen( file, O_BINARY|O_RDONLY, SH_DENYWR ) ) == -1 ) {
    do_error( file );
    return( -1 );
    }
 if ( read( h1, (char *)&pt->start, 2 ) != 2 ) {
    do_error( pt->name );
    close( h1 );
    return( -1 );
    }
 if ( read( h1, (char *)&pt->end, 2 ) != 2 ) {
    do_error( pt->name );
    pt->nd_open = CLOSED;
    close( h1 );
    return( -1 );
    }
 l = (pt->end - pt->start + 1);
 ip = new int[l];
 if ( ip == NULL ) {
    do_mem_error(0);
    pt->nd_open = CLOSED;
    close( h1 );
    return( -1 );
    }
 l *= 2;
 pt->nd_open = MEM;
 if ( read( h1, (char *)ip, l ) != l ) {
    do_error( pt->name );
    if ( pt->nd_open == MEM )
       delete ip;
    pt->nd_open = CLOSED;
    close( h1 );
    return( -1 );
    }
 pt->index = ip;

 ll = filelength( h1 );
 if ( ll == -1L ) {
    do_error( pt->name );
    pt->tb_open = CLOSED;
    close( h1 );
    return( -1 );
    }
 ll -= 520L;
 tx = new char[ll];
 if ( tx == NULL ) {
    do_mem_error(0);
    pt->tb_open = CLOSED;
    close( h1 );
    return( -1 );
    }
 lseek( h1, 520L, SEEK_SET );
 if ( read( h1, (char *)tx, (unsigned)ll ) != (unsigned) ll ) {
    do_error( pt->name );
    delete tx;
    pt->tb_open = CLOSED;
    close( h1 );
    return( -1 );
    }
 pt->text = tx;
 pt->tb_open = MEM;
 close( h1 );
 return( table_num );
}
