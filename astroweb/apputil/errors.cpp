
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "errors.fns"
#include "charcons.h"
#include <stdio.h>
#include "files.h"
#include <string.h>

static const char *_ERROR2 = "ERROR!!";

/* routine to handle out of memory errors */

void do_mem_error( int fatal )
{
 fprintf(getErrorFile(),"Out of Memory\n");
 if (fatal) {
	 exit(99);
   }
}
#define NON_FATAL 0

static char buf[500];
static const char a_title[] = "Error";
static const char stdmsg[] = { "%s : System Error #%d--%s" };

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
const char *errors[] = { "No Error!", stdmsg, "File or Directory Does Not Exist!",
   "File or Directory Does Not Exist!", "Too Many Open Files!",
   "Access To File or Device Denied!", stdmsg, "Memory Blocks Destroyed!",
   "Not Enough Memory Exists!", stdmsg, stdmsg, stdmsg, stdmsg, stdmsg,
   stdmsg, "No Such Device!", stdmsg, stdmsg, "Not Enough Files in CONFIG.SYS!",
   stdmsg, stdmsg, stdmsg, stdmsg, stdmsg, stdmsg, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, "Bad Math Argument!", "File Already Exists!",
   "File Locking Error!", NULL, NULL, NULL, NULL };
#endif


int error_message(const char *fmt, ... )
{
	va_list marker;
	va_start( marker, fmt );
	vsprintf( buf, fmt, marker );
    va_end( marker );
    assert( strlen( buf ) < sizeof( buf ) );
    fprintf(getErrorFile(),"Error--%s\n",buf);
    return( 1 );
}

int alert_box(const char *title,const  char *fmt, ... )
{
 const char *a_title = "Error";
 va_list marker;

 if ( title == NULL || !strcmp(title, "")  )
    title = a_title;
 va_start( marker, fmt );
 vsprintf( buf, fmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 fprintf(getErrorFile(),"%s--%s\n",title,buf);
 return( 1 );
}

int alert_box_ext( const char *title, const char *fmt, ... )
{
 int result;
 const char *a_title = "Error";
 va_list marker;

 if ( title == NULL || !strcmp(title, "") )
    title = a_title;
 va_start( marker, fmt );
 vsprintf( buf, fmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 fprintf(getErrorFile(),"%s--%s\n",title,buf);
 return( 1 );
}

/* function to handle file and other errors reported in errno */

void do_error( const char *file )
{
 static const char spmsg[] = { "Call Technical Support With This Error!" };

 if ( errno == ENOMEM ) {

    do_mem_error( false);
    return;
    }
 else if ( errno == 0 )
    return;
 if ( errno > 40 )
    alert_box_ext( ERROR2,"ILLEGAL ERROR #%d--%s", errno,spmsg );
 else if ( errors[errno] == NULL )
    alert_box_ext( ERROR2, "UNDEFINED ERROR #%d--%s", errno,spmsg );
 else if ( errors[errno] == stdmsg )
    alert_box_ext( ERROR2, stdmsg, file, errno, spmsg );
 else
    alert_box_ext( ERROR2, "%s : %s ", errors[errno], file );
 errno = 0;
}
