#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "resource.h"
#include "acombbox.hpp"
#include <print.h>
#include "asfrmdlg.hpp"
#include "fileary.hpp"
#include "tfilelst.hpp"
#include "inifile.hpp"
#include "errors.fns"
#include "helpid.h"


FileListDlgf::FileListDlgf(zWindow *par, int t) : FormDlgf(par,zResId(IDD_SELECT_FILE), HELPID_DLG_SELECT )
{
 int tb = 55;
 char buf[100];
 type = t;

 file = "";
 box = new zListBox(this, IDC_LIST1, &file );
 SendMessage(HANDLE(*box),LB_SETTABSTOPS,1,((LONG)((LPVOID)&tb)));
 tbtEditFiles.toListBox(box,t);
 run();
}

CAsFile *FileListDlgf::toFile()
{
 char *p;
 char buf[100];

 strcpy( buf, (char *) file );
 p = strchr( buf, ' ' );
 if ( p != NULL )
    *p = '\0';
 return( tbtEditFiles.Find(buf) );
}



