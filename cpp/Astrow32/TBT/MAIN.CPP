#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "resource.h"
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include "fileary.hpp"
#include "tdirec.hpp"
#include "tbtoptn.hpp"
#include "tbtframe.hpp"
#include "title.hpp"
#include <direct.h>
#include "inifile.hpp"

CAsFileAry tbtEditFiles;
TbtDirectories theTbtDirectories;
TbtOptions theTbtOptions;

void zApp::main()
{
 char buf[150];

 #ifdef _DEBUG
 debugOn(1);
 #endif
  _getdcwd(_getdrive(),buf,150);
 if ( buf[strlen(buf)-1] != '\\' )
    strcat( buf, "\\" );
 strcat(buf, ini_file );
 strcpy(ini_file, buf );   
 theTbtDirectories.getFromIni();
 theTbtOptions.getFromIni();
 TbtAppFrame *apf = new TbtAppFrame(new
    zSizer);
 apf->show();
 TitleFrame *tf = new TitleFrame(apf);
 tf->show();
 tf->setFocus();
 tbtEditFiles.Load("TFILE.LST", 60 );
 go();
 delete apf;
}
