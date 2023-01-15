#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "errors.fns"
#include "resource.h"
//#include "charcons.h"

char *ERROR2 = "ERROR!!";

#define PROGNAME "Astro For Windows"

TCHAR *UERROR2 = _T("ERROR!!");


#define UPROGNAME _T("Astro For Windows")

/* routine to handle out of memory errors */

void  do_mem_error( int fatal )
{
 if ( fatal )
    FatalAppExit(0, _T("Fatal Out of Memory Error!") );
 OutputDebugString( _T("do_mem_error\n") );
 alert_box_ext( ERROR2, MB_OK|MB_ICONSTOP, "Out of Memory Error!" );
}

#define NON_FATAL 0

static char buf[500];
static char a_title[] = "A Message from " PROGNAME;
static char stdmsg[] = { "%s : System Error #%d--%s" };

#ifdef _UNICODE
static TCHAR ubuf[500];
static TCHAR ua_title[] = L"A Message from " UPROGNAME;
static TCHAR ustdmsg[] = { L"%ls : System Error #%d--%ls" };
#endif


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
#ifdef _UNICODE
TCHAR *uerrors[] = { ustdmsg, NULL, L"File or Directory Does Not Exist!",
   NULL, NULL, NULL,  NULL, ustdmsg, 
   L"File is Not an executable File!", ustdmsg, NULL, NULL,
   L"Not Enough Memory Exists!", L"Access To File or Device Denied!",
   NULL, NULL, NULL, L"File Exists!", L"Trying to Rename File to Another"  
   L"Directory or Drive!", NULL, NULL, NULL, ustdmsg, NULL,
   L"Not Enough Files in CONFIG.SYS need at least 12", NULL, NULL, NULL,
   L"No Space Left on Drive", NULL, NULL, NULL, NULL, ustdmsg, ustdmsg,
   NULL, ustdmsg, NULL, L"Error or Printer Not Ready!" };
#endif
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

int alert_box( UINT nTitle, const char *fmt, ... )
{
 int result;
 HWND handle;
 va_list marker;
 CString strBuf;
 CString strTitle;
 if ( !nTitle )
    strTitle.LoadString(IDS_STDTITLE);
 else
    strTitle.LoadString(nTitle);
 
 va_start( marker, fmt );
 vsprintf( buf, fmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 strBuf = buf;
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, strBuf, strTitle, MB_OK|MB_ICONINFORMATION );
 return( result );
}

int alert_box( UINT nFmt, ... )
{
 int result;
 HWND handle;
 va_list marker;
 CString strBuf;
 CString strTitle, strFmt;

 strTitle.LoadString(IDS_STDTITLE);
 strFmt.LoadString(nFmt);

 va_start( marker, nFmt );
 vsprintf( buf, (LPCTSTR)strFmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 strBuf = buf;
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, strBuf, strTitle, MB_OK|MB_ICONINFORMATION );
 return( result );
}


int alert_box( UINT nTitle, UINT nFmt, ... )
{
 int result;
 HWND handle;
 va_list marker;
 CString strBuf, strFmt;
 CString strTitle;
 if ( !nTitle )
    strTitle.LoadString(IDS_STDTITLE);
 else
    strTitle.LoadString(nTitle);
 strFmt.LoadString(nFmt);
 va_start( marker, nFmt );
 vsprintf( buf, (LPCTSTR)strFmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 strBuf = buf;
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, strBuf, strTitle, MB_OK|MB_ICONINFORMATION );
 return( result );
}

int alert_box( char *title, const char *fmt, ... )
{
 int result;
 char *a_title = "A Message from " PROGNAME;
 HWND handle;
 va_list marker;
  
 if ( title == NULL || !strcmp(title, "")  )
    title = a_title;
 va_start( marker, fmt );
 vsprintf( buf, fmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, CString(buf), CString(title), MB_OK|MB_ICONINFORMATION );
 return( result );
}

int alert_box_ext( char *title, UINT options, const char *fmt, ... )
{
 int result;
 HWND handle;
 char *a_title = "A Message from " PROGNAME;
 va_list marker;

 if ( title == NULL || !strcmp(title, "") )
    title = a_title;
 va_start( marker, fmt );
 vsprintf( buf, fmt, marker );
 va_end( marker );
 assert( strlen( buf ) < sizeof( buf ) );
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, CString(buf), CString(title), options );
 return( result );
}

/* function to handle file and other errors reported in errno */

void do_error( const char *file )
{
 static char spmsg[] = { "Call Technical Support With This Error!" };

 OutputDebugString( CString(file) );
 if ( errno == ENOMEM ) {
    do_mem_error( FALSE );
    return;
    }
 else if ( errno == 0 )
    return;
 if ( errno > 40 )
    alert_box_ext( ERROR2, MB_OK|MB_ICONSTOP, "ILLEGAL ERROR #%d--%s", errno, spmsg );
 else if ( errors[errno] == NULL )
    alert_box_ext( ERROR2, MB_OK|MB_ICONSTOP, "UNDEFINED ERROR #%d--%s", errno, spmsg );
 else if ( errors[errno] == stdmsg )
    alert_box_ext( ERROR2, MB_OK|MB_ICONSTOP, stdmsg, file, errno, spmsg );
 else
    alert_box_ext( ERROR2, MB_OK|MB_ICONSTOP, "%s : %s ", errors[errno], file );
 errno = 0;
}

int  valert_box_ext( LPCSTR title, UINT options, LPCSTR fmt, va_list marker )
{
 int result;
 HWND handle;
 char *a_title = "A Message from " PROGNAME;

 if ( title == NULL || !strcmp(title, "") )
    title = a_title;
 vsprintf( buf, fmt, marker );
 assert( strlen( buf ) < sizeof( buf ) );
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, CString(buf), CString(title), options );
 return( result );
}

int  valert_box_ext( UINT nTitle, UINT options, LPCSTR fmt, va_list marker )
{
 int result;
 HWND handle;
 CString strTitle;

 if ( !nTitle )
    strTitle.LoadString(IDS_STDTITLE);
 else
    strTitle.LoadString(nTitle);
 vsprintf( buf, fmt, marker );
 assert( strlen( buf ) < sizeof( buf ) );
 OutputDebugString( CString(buf) );
 handle = GetFocus();
 result = MessageBox( handle, CString(buf), strTitle, options );
 return( result );
}

int  valert_box_ext( UINT nTitle, UINT options, UINT nFmt, va_list marker )
{
 int result;
 HWND handle;
 CString strFmt, strBuf, strTitle;

 if ( !nTitle )
    strTitle.LoadString(IDS_STDTITLE);
 else
    strTitle.LoadString(nTitle);
 strFmt.LoadString(nFmt);
 vsprintf( buf, (LPCTSTR)strFmt, marker );
 assert( strlen( buf ) < sizeof( buf ) );
 OutputDebugString( CString(buf) );
 strBuf = buf;
 handle = GetFocus();
 result = MessageBox( handle, strBuf, strTitle, options );
 return( result );
}

#ifdef _UNICODE
int alert_box( TCHAR *title, const TCHAR *fmt, ... )
{
 int result;
 TCHAR *a_title = L"A Message from " UPROGNAME;
 HWND handle;
 va_list marker;
  
 if ( title == NULL || !_tcscmp(title, L"")  )
    title = a_title;
 va_start( marker, fmt );
 _vstprintf( ubuf, fmt, marker );
 va_end( marker );
 assert( _tcslen( ubuf ) < sizeof( ubuf ) );
 OutputDebugString( ubuf );
 handle = GetFocus();
 result = MessageBox( handle, ubuf, title, MB_OK|MB_ICONINFORMATION );
 return( result );
}

int alert_box_ext( TCHAR *title, UINT options, const TCHAR *fmt, ... )
{
 int result;
 HWND handle;
 TCHAR *a_title = L"A Message from) " UPROGNAME;
 va_list marker;

 if ( title == NULL || !_tcscmp(title, L"") )
    title = a_title;
 va_start( marker, fmt );
 _vstprintf( ubuf, fmt, marker );
 va_end( marker );
 assert( _tcslen( ubuf ) < sizeof( ubuf ) );
 OutputDebugString( ubuf );
 handle = GetFocus();
 result = MessageBox( handle,ubuf, title, options );
 return( result );
}

/* function to handle file and other errors reported in errno */

void do_error( const TCHAR *file )
{
 static TCHAR spmsg[] = { L"Call Technical Support With This Error!" };

 OutputDebugString( file );
 if ( errno == ENOMEM ) {
    do_mem_error( FALSE );
    return;
    }
 else if ( errno == 0 )
    return;
 if ( errno > 40 )
    alert_box_ext( UERROR2, MB_OK|MB_ICONSTOP, L"ILLEGAL ERROR #%d--%ls", errno, spmsg );
 else if ( uerrors[errno] == NULL )
    alert_box_ext( UERROR2, MB_OK|MB_ICONSTOP, L"UNDEFINED ERROR #%d--%ls", errno, spmsg );
 else if ( uerrors[errno] == ustdmsg )
    alert_box_ext( UERROR2, MB_OK|MB_ICONSTOP, ustdmsg, file, errno, spmsg );
 else
    alert_box_ext( UERROR2, MB_OK|MB_ICONSTOP, L"%ls : %ls ", uerrors[errno], file );
 errno = 0;
}

int  valert_box_ext( const TCHAR *title, UINT options, const TCHAR *fmt, va_list marker )
{
 int result;
 HWND handle;
 TCHAR *a_title = L"A Message from " UPROGNAME;

 if ( title == NULL || !_tcscmp(title, L"") )
    title = a_title;
 _vstprintf( ubuf, fmt, marker );
 assert( _tcslen( ubuf ) < sizeof( ubuf ) );
 OutputDebugString( ubuf );
 handle = GetFocus();
 result = MessageBox( handle, ubuf, title, options );
 return( result );
}
#endif

