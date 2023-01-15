#include "batch.hpp"
#include "basedcs.h"
#include "errors.fns"
#include "charcons.h"

#define __NOIF__     0
#define __IFTRUE__   1
#define __IFFALSE__  2
#define __INIFB__    4
#define __INELSEB__  8

long labels[25];
long returns[25];
long repeat_target[6] = { -1L,-1L,-1L,-1L,-1L,-1L };
int repeat_count[6] = { 0,0,0,0,0,0 };
int go_no = 0, rep_no = 0;
int ifs[5];
int status[5];
int if_no=-1;

int repeat_proc( FILE *stream, CMD *cm )
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


int label_proc( FILE *stream, CMD *cm )
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


int gosub_proc( FILE *stream, CMD *cm )
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


int return_proc( FILE *stream, CMD *cm )
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

int end_repeat_proc( FILE *stream, CMD *cm )
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


int find_endif( FILE *stream )
{
 char buf[25];

 if ( checkif(0) )
    return( 0 );
 do {
   fscanf( stream, "%s", buf );
   eat_line( stream );
 } while ( blnicmp( buf, "ENDIF" ) && blnicmp( buf, "EIF" ) );
 ifs[ifno] ^= __INIFB__;
 return( 0 );
}

int find_endelse( FILE *stream )
{
 char buf[25];

 if ( checkif(1) )
    return( 0 );
 do {
   fscanf( stream, "%s", buf );
   eat_line( stream );
 } while ( blnicmp( buf, "ENDELSE" ) && blnicmp( buf, "EEL" ) );
 ifs[ifno] ^= __INELSEB__;
 return( 1 );
}

do_if( FILE *stream )
{
 if ( checkif(0) )
    return( 0 );
 ifs[ifno] ^= __INIFB__;
 if ( !(ifs[ifno] & __IFTRUE__) ) {
    find_endif(stream);
    ifno--;
    }
 return( 1 );
}

do_else( FILE *stream )
{
 if ( checkif(1) )
    return( 0 );
 ifno++;
 ifs[ifno] ^= __INELSEB__;
 if ( ifs[ifno] & __IFTRUE__ ) {
    find_endelse(stream);
    ifno--;
    }
 return( 1 );
}

do_endif( FILE *stream )
{
 if ( checkif(0) )
    return( 0 );
 ifs[ifno] ^= __INIFB__;
 ifno--;
 return( 1 );
}

do_endelse( FILE *stream )
{
 if ( checkif(1) )
    return( 0 );
 ifs[ifno] ^= __INELSEB__;
 ifno--;
 return( 1 );
}

int checkif(int i)
{
 char BCS msg1[] = { "Illegal if/endif Error!"   };
 char BCS msg2[] = { "Else Without If Error, or Illegal elsif Error!"   };
 if ( ifno > 0 && ifno < 5 )
    return( 0 );
 else {
    alert_box( ERROR1, (i?(char _far *)msg1:(char _far *)msg2) );
    return( 1 );
    }
}

int if_status( FILE *stream, CMD *cm )
{
 ifno++;
 if ( status[ifno] )
    ifs[ifno] |= __IFTRUE__|__INIFB__;
 else
    ifs[ifno] |= __IFFALSE__|__INIFB__;
 return( do_if( stream, cm  ) );
}


int do_if( FILE *stream, CMD *cm )
{
 char BCS msg[] = {"Illegal Variable Number %s"};
 char BCS msg2[] = {"Illegal Comparison %s"};
 char var[5], cmp[5];
 ArgType check;
 zString data;

 ifno++;
 fscanf( stream, "%s %s ", var, cmp );
 check.read(stream);
 if ( isalpha(var[0])) {
    c = toupper( var[0] );
    vn = c - 'A';
    }
 else
    vn = atoi(var);
 if ( vn > 0 && vn < 10 ) {
    data = get(vn).get();
    }
 else {
    alert_box( ERROR, msg, var );
    return(0);
    }
 if (!strcmp(cmp, "=" )) {
    if ( data == check.get() )
       ifs[ifno] |= __IFTRUE__|__INIFB__;
    else
       ifs[ifno] |= __IFFALSE__|__INIFB__;
    }
 else if (!strcmp(cmp, "<>" )) {
    if ( data != check.get() )
       ifs[ifno] |= __IFTRUE__|__INIFB__;
    else
       ifs[ifno] |= __IFFALSE__|__INIFB__;
    }
 else if (!strcmp(cmp, "<" )) {
    if ( data < check.get() )
       ifs[ifno] |= __IFTRUE__|__INIFB__;
    else
       ifs[ifno] |= __IFFALSE__|__INIFB__;
    }
 else if (!strcmp(cmp, ">" )) {
    if ( data > check.get() )
       ifs[ifno] |= __IFTRUE__|__INIFB__;
    else
       ifs[ifno] |= __IFFALSE__|__INIFB__;
    }
 else if (!strcmp(cmp, "<=" ) || !strcmp(cmp, "=<" ) ) {
    if ( data <= check.get() )
       ifs[ifno] |= __IFTRUE__|__INIFB__;
    else
       ifs[ifno] |= __IFFALSE__|__INIFB__;
    }
 else if (!strcmp(cmp, ">=" ) || !strcmp(cmp, "=<" ) ) {
    if ( data >= check.get() )
       ifs[ifno] |= __IFTRUE__|__INIFB__;
    else
       ifs[ifno] |= __IFFALSE__|__INIFB__;
    }
 else {
    alert_box( ERROR, msg2, cmp );
    return(0);
    }
 return( 1 );
}





