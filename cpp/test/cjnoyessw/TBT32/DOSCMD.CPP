#include "stdafx.h"
#include <toolhelp.h>
#include <direct.h>
#include "tbtutil.h"

extern void zYield(int i = 1 );
static int done;
HTASK theTask;

BOOL __export CALLBACK notify(WORD wID, DWORD dwData)
{
 if ( wID == NFY_EXITTASK ) {
    done = 1;
    NotifyUnRegister(theTask);
    return( FALSE );
    }
 else
    return( FALSE );
}


void waitForTask(UINT hInst )
{
 TASKENTRY te;

 memset( &te, 0, sizeof(TASKENTRY ) );
 te.dwSize = sizeof(TASKENTRY );
 TaskFirst(&te);
 if ( te.hInst != hInst ) {
    do {
       if ( !TaskNext(&te) )
	  return;
       } while( te.hInst != hInst );
    }
 theTask = te.hTask;
 NotifyRegister(te.hTask, &notify, NF_TASKSWITCH);
 done = 0;
 while ( !done )
       Yield();
}

#define NDLL 25

static char *wdllfunc[] =
{
 "WSTOAST",
 "WP5TOAST",
 "WSTOAST",
 "RTFTOAST",
 "WP4TOAST",
 "DOCTOAST",
 "ASCTOAST",
 "ASCTOASTI",
 "AMITOAST",
 "BUILDTXT",
 "BUILDRPT",
 "3DBLDTXT",
 "STRTABLE",
 "MKSTRB",
 "MKBSR",
 "MKRBSR",
 "AST2WS",
 "AST2WP5",
 "AST2DOC",
 "AST2RTF",
 "ASTWP4",
 "AST2ASC",
 "AST2AMI"
};

int checkDllFunc( char *fnc )
{
for ( int i = 0; i < NDLL; i++ ) {
     if ( !strnicmp(fnc,wdllfunc[i],strlen(wdllfunc[i]) ) ) {
	return( 1 );
     }
    }
 return( 0 );
}


#define NINT 11

static char * winternal[] =
{
    "CD",
    "CHDIR",
    "DEL",
    "ERASE",
    "MD",
    "MKDIR",
    "RD",
    "RMDIR",
    "REN",
    "RENAME",
    "COPY"
};


int copyFile( char *src, char *dst )
{
 FILE *in, *out;
 char *buf;
 int r;
 
 in = fopen( src, "rb" );
 if ( in == NULL )  {
    zYield();
    return( 0 );
    }
 out = fopen( dst, "wb" );
 if ( out == NULL )  {
    fclose(in);
    zYield();
    return( 0 );
    }
 buf = new char[8194];
 do {
    r = fread(buf, 1, 8192, in );
    if ( r )
       r = fwrite(buf, 1, r, out ); 
    } while ( r );
 delete buf;
 fclose( in );
 fclose( out );
 zYield();
 return( 0 );
}

int doDosCmd( char *fnc, char *p1, char *p2 )
{
 char buf[150], *p;
 int i;

 zYield();
 for ( i = 0; i < NINT; i++ ) {
     if ( !strcmpi(fnc,winternal[i] ) ) {
	switch( i ) {
	      case 0:
	      case 1:
		  _chdir( p1 );
		  return( 0 );
		  break;
	      case 2:
	      case 3:
		  _unlink( p1 );
		  return( 0 );
		  break;
	      case 4:
	      case 5:
		  _mkdir( p1 );
		  return( 0 );
		  break;
	      case 6:
	      case 7:
		  _rmdir( p1 );
		  return( 0 );
		  break;
	      case 8:
	      case 9:
		  strcpy( buf, p1 );
		  p = strrchr( buf, '\\' );
		  if ( p != NULL )
		     strcpy( p+1, p2 );
		  else
		     strcpy( buf, p2 );   
		  rename( p1, buf );
		  return( 0 );
		  break;
		  case 10:
		  copyFile( p1, p2 );
		  return( 0 );
		  break;
		  break;
	      }
	}
     }
 return( 1 );
}

int win_System( char *p )
{
 static char buf[150];
 static char buf2[150];
 FILE *stream;
 char *pt;
 UINT e;

 unlink("$$$CMD$$.$$$");
 sprintf( buf, "command.com /c %s > $$$CMD$$.$$$", p );
 if ( ( e = WinExec( buf, SW_SHOWNA ) ) < 32 ) {
    alert_box("Error Executing", buf );
    return( 1 );
    }
 else
    waitForTask(e);
 if ( !access("$$$CMD$$.$$$",4) ) {
    stream = fopen("$$$CMD$$.$$$", "rt" );
    if ( stream == NULL ) {
       do_error("$$$CMD$$.$$$");
       return( 0 );
       }
    do {
       pt = fgets(buf2, 149, stream );
       if ( pt != NULL )
	  LogOutput(pt);
       } while ( pt != NULL );
    fclose( stream );
    }
 return( 0 );
}

