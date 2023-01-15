extern "C" {
#include "cgic205/cgic.h"
}
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "charcons.h"
#include "errors.fns"

#define START "<html><body>"
#define ENDS  "<br></body></html>"


#define PROGNAME "Numero Uno"

/* routine to handle out of memory errors */

void do_mem_error( int fatal )
{
 fprintf( cgiOut, START "Out of Memory Error" ENDS );
}

#define NON_FATAL 0

static char buf[500];
static char a_title[] = "A Message from " PROGNAME;
static char stdmsg[] = { "%s : System Error #%d--%s" };

#ifdef _MSC_VER
char *errors[] = { stdmsg, NULL, "File or Directory Does Not Exist!",
   NULL, NULL, NULL,  NULL, stdmsg, 
   "File is Not an executable File!", stdmsg, NULL, NULL,
   "Not Enough Memory Exists!", "Access To File or Device Denied!",
   NULL, NULL, NULL, "File Exists!", "Trying to Rename File to Another"  
   "Directory or Drive!", NULL, NULL, NULL, stdmsg, NULL,
   "Not Enough Files in CONFIG.SYS need at least 12", NULL, NULL, NULL,
   "No Space Left on Drive", NULL, NULL, NULL, NULL, stdmsg, stdmsg,
   NULL, stdmsg, NULL, "Error or Printer Not Ready!" };
#else
char *errors[] = { "No Error!", stdmsg, "File or Directory Does Not Exist!",
   "File or Directory Does Not Exist!", "Too Many Open Files!",
   "Access To File or Device Denied!", stdmsg, "Memory Blocks Destroyed!",
   "Not Enough Memory Exists!", stdmsg, stdmsg, stdmsg, stdmsg, stdmsg,
   stdmsg, "No Such Device!", stdmsg, stdmsg, "Not Enough Files in CONFIG.SYS!",
   stdmsg, stdmsg, stdmsg, stdmsg, stdmsg, stdmsg, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, "Bad Math Argument!", "File Already Exists!",
   "File Locking Error!", NULL, NULL, NULL, NULL };
#endif


int alert_box( char *title, char *fmt, ... )
{
 int result;
 char *a_title = "A Message from " PROGNAME;
 va_list marker;

 if ( title == NULL || !strcmp(title, "")  )
    title = a_title;
 va_start( marker, fmt );
 fputs(START,cgiOut);
 vfprintf( cgiOut, fmt, marker );
 fputs(ENDS,cgiOut);
 va_end( marker );
 return( 1 );
}

int alert_box_ext( char *title, unsigned int options, char *fmt, ... )
{
 int result;
 char *a_title = "A Message from " PROGNAME;
 va_list marker;

 if ( title == NULL || !strcmp(title, "") )
    title = a_title;
 fputs(START,cgiOut);
 va_start( marker, fmt );
 vfprintf( cgiOut, fmt, marker );
 fputs(ENDS, cgiOut );
 va_end( marker );
 return( 1 );
}

/* function to handle file and other errors reported in errno */

void do_error( char *file )
{
 static char spmsg[] = { "Call Technical Support With This Error!" };

 if ( errno == ENOMEM ) {
    do_mem_error( 0 );
    return;
    }
 else if ( errno == 0 )
    return;
 if ( errno > 40 )
    alert_box_ext( ERROR2, 0, "ILLEGAL ERROR #%d--%s", errno, spmsg );
 else if ( errors[errno] == NULL )
    alert_box_ext( ERROR2, 0, "UNDEFINED ERROR #%d--%s", errno, spmsg );
 else if ( errors[errno] == stdmsg )
    alert_box_ext( ERROR2, 0, stdmsg, file, errno, spmsg );
 else
    alert_box_ext( ERROR2, 0, "%s : %s ", errors[errno], file );
 errno = 0;
}

int valert_box_ext( char *title, unsigned int options, char *fmt, va_list marker )
{
 int result;
 char *a_title = "A Message from " PROGNAME;

 if ( title == NULL || !strcmp(title, "") )
    title = a_title;
 fputs(START,cgiOut);
 va_start( marker, fmt );
 vfprintf( cgiOut, fmt, marker );
 fputs(ENDS, cgiOut );
 va_end( marker );
 return( 1 );
}



