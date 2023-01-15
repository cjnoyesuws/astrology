#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "dialogs.h"
#include "acombbox.hpp"
#include <print.h>
#include "asfrmdlg.hpp"
#include "prntsetp.hpp"
#include "asgflags.h"
#include "graopt.hpp"
#include "printopt.hpp"
#include "inifile.hpp"
#include "asdrawbs.hpp"
#include "gracolor.hpp"
#include "repstyle.hpp"
#include "errors.fns"
#include "charcons.h"
#include "resstr.hpp"


PrinterSetup::PrinterSetup()
{
 pMode = 0;
 orientation = -1;
 color = -1;
 copies = -1;
 yres = -1;
 scale = -1;
 quality = -999;
 duplex = -1;
 source = -1;
 size = -1;
 ps = new zPrinterSpec(0);
}

DEVMODE *PrinterSetup::toDevMode(zWindow *w, int prompt)
{
 char buf[30];
 int len;
 HANDLE hm;
 WORD fuMode = DM_IN_BUFFER|DM_OUT_BUFFER;
 int (_far PASCAL *xDevMode)(HWND,HANDLE,LPDEVMODE,LPSTR,LPSTR,LPDEVMODE,LPSTR,WORD);

 if ( ps == NULL ) {
    alert_box(_PRS_NOPRSEL/*"","No Printer Was Selected!"*/ );
    return( NULL );
    }
 strcpy( buf, ps->driverName() );
 strcat( buf, ".DRV" );
 hm = LoadLibrary(buf);
 if ( hm < HINSTANCE_ERROR ) {
    return( NULL );
    }
 xDevMode = (int (_far PASCAL *)(HWND,HANDLE,LPDEVMODE,LPSTR,LPSTR,LPDEVMODE,LPSTR,WORD))
       GetProcAddress(hm,"EXTDEVICEMODE");
 if ( !xDevMode ) {
    return( NULL );
    }
 len = xDevMode(0, hm, 0, ps->deviceName(), ps->output(), 0, NULL, 0);
 if ( pMode )
    delete pMode;
 pMode = (DEVMODE _far *)new char[len+1];
 if ( pMode == NULL )
    return( NULL );
 if ( xDevMode(0, hm, pMode, ps->deviceName(), ps->output(), NULL, NULL, DM_OUT_BUFFER) != IDOK ) {
    if ( hm > HINSTANCE_ERROR )
       FreeLibrary(hm);
    return( NULL );
    }
 if ( orientation != -1 ) {
    if (!(pMode->dmFields & DM_ORIENTATION))
       pMode->dmFields |= DM_ORIENTATION;
    pMode->dmOrientation = orientation;
    }
 if ( color != -1 ) {
    if (!(pMode->dmFields & DM_COLOR))
       pMode->dmFields |= DM_COLOR;
    pMode->dmColor = color;
    }
 if ( copies != -1 ) {
    if (!(pMode->dmFields & DM_COPIES))
       pMode->dmFields |= DM_COPIES;
    pMode->dmCopies = copies;
    }
 if ( yres != -1 ) {
    if (!(pMode->dmFields & DM_YRESOLUTION))
       pMode->dmFields |= DM_YRESOLUTION;
    pMode->dmYResolution = yres;
    }
 if ( quality != -999 ) {
    if (!(pMode->dmFields & DM_PRINTQUALITY))
       pMode->dmFields |= DM_PRINTQUALITY;
    pMode->dmPrintQuality = quality;
    }
 if ( scale != -1 ) {
    if (!(pMode->dmFields & DM_SCALE))
       pMode->dmFields |= DM_SCALE;
    pMode->dmScale = scale;
    }
 if ( duplex != -1 ) {
    if (!(pMode->dmFields & DM_DUPLEX))
       pMode->dmFields |= DM_DUPLEX;
    pMode->dmDuplex = duplex;
    }
 if ( source != -1 ) {
    if (!(pMode->dmFields & DM_DEFAULTSOURCE))
       pMode->dmFields |= DM_DEFAULTSOURCE;
    pMode->dmDefaultSource = source;
    }
 if ( size != -1 ) {
    if (!(pMode->dmFields & DM_PAPERSIZE))
       pMode->dmFields |= DM_PAPERSIZE;
    pMode->dmPaperSize = size;
    }
 if ( !prompt ) {
    if ( hm > HINSTANCE_ERROR )
       FreeLibrary(hm);
    return( pMode );
    }
 else
    fuMode |= DM_IN_PROMPT;
 if ( xDevMode(*w, hm, pMode, ps->deviceName(), ps->output(), pMode, NULL, fuMode) == IDOK ) {
    if (pMode->dmFields & DM_ORIENTATION)
       orientation = pMode->dmOrientation;
    else
       orientation = -1;
    if (pMode->dmFields & DM_COLOR)
       color = pMode->dmColor;
    else
       color = -1;
    if (pMode->dmFields & DM_COPIES)
       copies = pMode->dmCopies;
    else
       copies = -1;
    if (pMode->dmFields & DM_YRESOLUTION)
       yres = pMode->dmYResolution;
    else
       yres = -1;
    if (pMode->dmFields & DM_PRINTQUALITY )
       quality = pMode->dmPrintQuality;
    else
       quality = -999;
    if (pMode->dmFields & DM_SCALE)
       scale = pMode->dmScale;
    else
       scale = -1;
    if (pMode->dmFields & DM_DUPLEX)
       duplex = pMode->dmDuplex;
    else
       duplex = -1;
    if (pMode->dmFields & DM_PAPERSIZE)
       size = pMode->dmPaperSize;
    else
       size = -1;
    if (pMode->dmFields & DM_DEFAULTSOURCE)
       source = pMode->dmDefaultSource;
    else
       source = -1;
    if ( hm > HINSTANCE_ERROR )
       FreeLibrary(hm);

    return( pMode );
    }
 else {
    if ( hm > HINSTANCE_ERROR )
       FreeLibrary(hm);
    return( NULL );
    }
}

int PrinterSetup::getFromIni(char *sec)
{
 char buf[100], buf2[100];

 zPrinterSpec *xps = new zPrinterSpec(0);
 sprintf( buf2, "%s,%s,%s", xps->deviceName(), xps->driverName(), xps->output() );
 if ( !GetPrivateProfileString( sec, "Printer", buf2, buf, 99, APPNAME ) ) {
    delete xps;
    return( 0 );
    }
 delete xps;
 if ( ps )
    delete ps;
 ps = new zPrinterSpec(buf);
 orientation = GetPrivateProfileInt( sec, "Orient", orientation, APPNAME );
 copies = GetPrivateProfileInt( sec, "Copies", copies, APPNAME );
 color = GetPrivateProfileInt( sec, "Color", color, APPNAME );
 yres = GetPrivateProfileInt( sec, "YRes", yres, APPNAME );
 scale = GetPrivateProfileInt( sec, "Scale", scale, APPNAME );
 quality = GetPrivateProfileInt( sec, "Quality", quality, APPNAME );
 duplex = GetPrivateProfileInt( sec, "Duplex", duplex, APPNAME );
 source = GetPrivateProfileInt( sec, "Source", source, APPNAME );
 size = GetPrivateProfileInt( sec, "Size", size, APPNAME );
 return( 1 );
}


int PrinterSetup::saveToIni(char *sec)
{
 char buf[100];

 sprintf( buf, "%s,%s,%s", ps->deviceName(), ps->driverName(), ps->output() );
 WritePrivateProfileString( sec, "Printer", buf, APPNAME );
 sprintf( buf, "%d", orientation );
 WritePrivateProfileString( sec, "Orient", buf, APPNAME );
 sprintf( buf, "%d", copies );
 WritePrivateProfileString( sec, "Copies", buf, APPNAME );
 sprintf( buf, "%d", color );
 WritePrivateProfileString( sec, "Color", buf, APPNAME );
 sprintf( buf, "%d", yres );
 WritePrivateProfileString( sec, "YRes", buf, APPNAME );
 sprintf( buf, "%d", quality );
 WritePrivateProfileString( sec, "Quality", buf, APPNAME );
 sprintf( buf, "%d", scale );
 WritePrivateProfileString( sec, "Scale", buf, APPNAME );
 sprintf( buf, "%d", duplex );
 WritePrivateProfileString( sec, "Duplex", buf, APPNAME );
 sprintf( buf, "%d", source );
 WritePrivateProfileString( sec, "Source", buf, APPNAME );
 sprintf( buf, "%d", size );
 WritePrivateProfileString( sec, "Size", buf, APPNAME );
 return( 1 );
}

int PrinterSetup::newChoice( char *c )
{
 char buf[90], buf2[90], buf3[120], *p;
 if ( ps )
    delete ps;
 strcpy( buf, c );
 p = strstr( buf, " on " );
 if ( p != NULL )
    *p = '\0';
 GetProfileString( "Devices", buf, "", buf2, 119 );
 sprintf( buf3, "%s,%s", buf, buf2 );
 ps = new zPrinterSpec(buf3);
 orientation = -1;
 color = -1;
 copies = -1;
 yres = -1;
 scale = -1;
 quality = -999;
 duplex = -1;
 source = -1;
 size = -1;
 return( 0 );
}



PrinterSetupDlgf::PrinterSetupDlgf(zWindow *par, PrinterSetup *d, int t) : FormDlgf(par,zResId("PR_SETUP"), HELPID_DLG_SETPR )
{
 char buf[100];
 zPrinterSpec *ps;
 type = t;
 data = d;
 box = new zListBox(this, IDC_PRPRINTERS, &choice);
 zSystemInfo *si = new zSystemInfo();
 zPrinterSpecSlist *print = si->getPrinterList();
 zPrinterSpecSlistIter i(print);
 while ((ps = i()) != NULL) {
       sprintf( buf, "%s on %s", ps->deviceName(), ps->output() );
       box->add(buf);
       }
 sprintf( buf, "%s on %s", d->getSpec()->deviceName(), d->getSpec()->output() );
 box->selection(buf);
 si->releasePrinterList(print);
 delete si;
 zDefPushButton *b = new zDefPushButton(this, IDOK );
 b->setNotifyClicked(this,(NotifyProc)&PrinterSetupDlgf::doOk );
 run();
}

int PrinterSetupDlgf::doOk( zEvent *e )
{
 char buf[100];
 storeData();
 if ( !choice.length() ) {
    alert_box(_PRS_NOPRSEL/*"", "No Printer Was Selected!"*/ );
    (get(IDC_PRPRINTERS))->setFocus();
    return( 1 );
    }
 if ( data->getSpec() != NULL ) {
    if ( !printerChanged() ) {
       data->toDevMode(this,0);
       endOk(e);
       return( 1 );
       }
    }
 data->newChoice((char *)choice);
 doSetup(0);
 endOk(e);
 return( 1 );
}

void PrinterSetupDlgf::doSetup(int d)
{
 DEVMODE far *pm;

 pm = data->toDevMode(this, d);
 zPrinterDisplay *pd = new zPrinterDisplay(data->getSpec(), pm);
 if ( type ) {
    ReportStyles *rs = new ReportStyles((zDisplay *)pd);
    rs->saveToIni(PrintData_SEC);
    delete rs;
    }
 else {
    zDisplayInfo *pDi = new zDisplayInfo(pd);
    pDi->lock();
    if ( pDi->numColors() > 2 ) {
       GraphicColors *gc = new GraphicColors((zDisplay *)pd);
       gc->saveToIni(GraphPrintOpt_SEC);
       delete gc;
       }
    delete pDi;
    }
 delete pd;
}

int PrinterSetupDlgf::printerChanged()
{
 char buf[100];

 sprintf( buf, "%s on %s", data->getSpec()->deviceName(),
       data->getSpec()->output() );
 if (choice == buf)
    return( 0 );
 else
    return( 1 );
}

int PrinterSetupDlgf::command( zCommandEvt *e )
{
 char buf[100];
 DEVMODE far *pm;
 zPrinterDisplay *pd;

 switch( e->cmd() ) {
      case IDC_PRSETUP :
	   storeData();
	   if ( !choice.length() ) {
	      alert_box(_PRS_NOPRSEL/*"", "No Printer Was Selected!"*/ );
	      (get(IDC_PRPRINTERS))->setFocus();
	      return( 1 );
	      }
	   if ( data->getSpec() ) {
	      if ( !printerChanged() ) {
		 doSetup(1);
		 return( 1 );
		 }
	      }
	   data->newChoice((char *)choice);
	   doSetup(1);
	   return( 1 );
	   break;
      case IDC_PROPTIONS :
	   storeData();
	   if ( !choice.length() ) {
	      alert_box(_PRS_NOPRSEL/*"", "No Printer Was Selected!"*/ );
	      (get(IDC_PRPRINTERS))->setFocus();
	      return( 1 );
	      }
	   if ( printerChanged() )
	      doSetup(0);
	   if ( type ) {
	      PrintData *pdt = new PrintData();
	      pdt->getFromIni();
	      PrintDataDlgf *pdf = new PrintDataDlgf(this, pdt );
	      if ( !pdf->completed() ) {
		 delete pdf;
		 delete pdt;
		 return( 0 );
		 }
	      else {
		 pdf->getData();
		 delete pdf;
		 }
	      pdt->saveToIni();
	      delete pdt;
	      }
	   else {
	      GraphOptions ogd;
	      ogd.getFromIni(GraphPrintOpt_SEC);
	      GraphOptionsScreen *gos = new
		  GraphOptionsScreen((zWindow *)this, &ogd, 1);
	      delete gos;
	      ogd.saveToIni(GraphPrintOpt_SEC);
	      }
	   break;
      default :
	   break;
      }
 return( 0 );
}

