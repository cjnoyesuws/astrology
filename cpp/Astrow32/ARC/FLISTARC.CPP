#include "stdafx.h"
#include <assert.h>
#include "astro.h"
#include "astrow.h"
#include "useri.h"
#include "dataext.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "archive.hpp"
#include "flistarc.hpp"
#include "errors.fns"
#include "archiveData.h"

FileListArchiver::FileListArchiver(FileListArray *pf, int tp, int arc)
{
 pFla = pf;
 type = tp;
 data = new ArchiveData(arc);
}

FileListArchiver::~FileListArchiver()
{
 delete data;
}

int FileListArchiver::setup(CWnd *pPar)
{
  data->getFromIni();
  CArchiveData cad(pPar);
  cad.getCmd()=data->getCommand();
  cad.getDelete()=data->isDel();
  cad.getName()=data->getPath();
  cad.getProgram()=(int)data->isZip();
  if ( cad.DoModal() == IDOK ) {  
     data->getCommand()=cad.getCmd();
	 data->isDel()=cad.getDelete();
     data->getPath()=cad.getName();
	 data->isZip()=cad.getProgram();
     data->saveToIni();
     return( 1 );
     }
 return( 0 );
}

int FileListArchiver::archive(CWnd *pPar, int fld)
{
 DWORD er;
 char buf[250];
 STARTUPINFO sidat;
 PROCESS_INFORMATION pidat;

 if ( !setup( pPar ) )
    return( 0 );
 if ( makeArchiveList(fld) == NULL )
    return( 0 );
 sprintf( buf, (char *)(LPCTSTR) data->getCommand(),
	 (char *)(LPCTSTR)data->getPath(), (char *)name );
 memset(&sidat, 0, sizeof(STARTUPINFO) );
 sidat.cb=17*4;
 if ( !CreateProcess( NULL, buf, NULL, NULL, FALSE, 
	       CREATE_DEFAULT_ERROR_MODE|DETACHED_PROCESS, NULL, NULL,
           &sidat, &pidat ) ) {
     LPVOID lpMsgBuf;
     FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | 
     FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),
     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
     (LPTSTR) &lpMsgBuf, 0, NULL );
     MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	 LocalFree( lpMsgBuf );
	 return( 0 );
	}
 DWORD dw = STILL_ACTIVE;
 while ( dw == STILL_ACTIVE ) {
       if ( GetExitCodeProcess( pidat.hProcess, &dw) == FALSE )  
          return( 0 );
		}
 if ( data->isDel() )
    pFla->killSelectedFiles(pPar, type, fld);
 unlink(name);
 return( 1 );
}

int FileListArchiver::deArchive(CWnd *pPar, int fld)
{
 char buf[250];
 STARTUPINFO sidat;
 PROCESS_INFORMATION pidat;

 if ( !setup( pPar ) )
    return( 0 );
 sprintf( buf, (char *) (LPCTSTR)data->getCommand(),
		  (char *)(LPCTSTR)data->getPath(), set_path("", fld) );
 memset(&sidat, 0, sizeof(STARTUPINFO) );
 sidat.cb=17*4;
 if ( !CreateProcess( NULL, buf, NULL, NULL, FALSE, 
	 CREATE_DEFAULT_ERROR_MODE|CREATE_SHARED_WOW_VDM|DETACHED_PROCESS, NULL, NULL,
		&sidat, &pidat ) ) {
     LPVOID lpMsgBuf;
     FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | 
     FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),
     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
     (LPTSTR) &lpMsgBuf, 0, NULL );
     MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	 LocalFree( lpMsgBuf );
	 return( 0 );
    }
 DWORD dw = STILL_ACTIVE;
 while ( dw == STILL_ACTIVE ) {
       if ( GetExitCodeProcess( pidat.hProcess, &dw) == FALSE )  
          return( 0 );
		}
 pFla->scanFiles();
 return( 1 );
}



