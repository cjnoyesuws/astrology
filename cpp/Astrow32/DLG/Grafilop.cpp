#include <stdafx.h>
#include <stdlib.h>
#include "attrib.h"
#include "inifile.hpp"
#include "grafilop.hpp"


static float untodot[] = {0.0, 100.0, 150.0, 180.0, 300.0 };
/*static char BCS hd[] = "&Height (Dots):";
static char BCS hi[] = "&Height (Inch):";
static char BCS hm[] = "&Height (mm):";
static char BCS wd[] = "&Width (Dots):";
static char BCS wi[] = "&Width (Inch):";
static char BCS wm[] = "&Width (mm):";
static char *hdims[] = {hd,hi,hm,0 };
static char *wdims[] = {wd,wi,wm,0 };*/

//static int hdims[] = {_GFP_DOTSH,_GFP_INCHH,_GFP_MMSH,0 };
//static int wdims[] = {_GFP_DOTSW,_GFP_INCHW,_GFP_MMSW,0 };


static char *sec = "GraphFileOpt";

GraphFileData::GraphFileData()
{
 height=400.0;
 width=600.0;
 format = 0;
 units=0;
 resolution=0;
 reverse=0;
}

int GraphFileData::isFormatColor()
{
 static char ic_list[] = {0,1,0,1,0,1,1,1,0,1,0,1,1,1,1};

 if ( format < 0 || format > GF_JPG )
    return( -1 );
 return( ic_list[format] );
}

int GraphFileData::getFormatBits()
{
 static char fb_list[] = {1,8,1,8,1,8,8,8,1,8,1,8,8,24,24};

 if ( format < 0 || format > GF_JPG )
    return( -1 );
 return( fb_list[format] );
}

int GraphFileData::saveToIni()
{
 CWinApp *app;
 CString b;
 int f=1;
 
 app = AfxGetApp();
 app->WriteProfileInt( sec, "Format", format);
 app->WriteProfileInt( sec, "Units", units );
 app->WriteProfileInt( sec, "Res", resolution );
 app->WriteProfileInt( sec, "RevMono", reverse );
 b.Format("%lf", width );
 app->WriteProfileString( sec, "Width", b );
 b.Format("%lf", height );
 app->WriteProfileString( sec, "Height", b );
 return( f );
}

int GraphFileData::getFromIni()
{
 CString b;
 CWinApp *app;
 
 app = AfxGetApp();
 format = (int) app->GetProfileInt( sec, "Format", format);
 units = (int) app->GetProfileInt( sec, "Units", units);
 resolution = (int) app->GetProfileInt( sec, "Res", resolution );
 reverse = (int) app->GetProfileInt( sec, "RevMono", reverse );
 b.Format( "%-5.3f", width );
 b = app->GetProfileString( sec, "Width", b );
 sscanf( b, "%f", &width );
 b.Format("%-5.3f", height );
 b = app->GetProfileString( sec, "Height", b );
 sscanf( b, "%f", &height );
 return( 1 );
}

int GraphFileData::getDotWidth()
{
 float w;

 switch( units ) {
       case GF_DOTS :
	    return( (int)width );
	    break;
       case GF_INCHES :
	    if ( !resolution ) {
	       CDC *dc = new CDC();
		   dc->CreateIC("DISPLAY",NULL,NULL,0);
		   w = width * dc->GetDeviceCaps(LOGPIXELSX);
		   delete dc;		   
		   return( (int) w );
	       }
	    return((int)untodot[resolution] * width );
	    break;
       case GF_MILIM :
	    if ( !resolution ) {
	       CDC *dc = new CDC();
		   dc->CreateIC("DISPLAY",NULL,NULL,0);
		   w = width * dc->GetDeviceCaps(LOGPIXELSX);
		   delete dc;
	       w /= 25.4;
	       return( (int) w );
	       }
	    return((int) (untodot[resolution] * width)/25.4 );
	    break;
       default :
	    return( 0 );
	    break;
       }
 return( 0 );
}

int GraphFileData::getDotHeight()
{
 float h;

 switch( units ) {
       case GF_DOTS :
	    return( height );
	    break;
       case GF_INCHES :
	    if ( !resolution ) {
	       CDC *dc = new CDC();
		   dc->CreateIC("DISPLAY",NULL,NULL,0);
		   h = height * dc->GetDeviceCaps(LOGPIXELSY);
		   delete dc;
	       return( (int) h );
	       }
	    return((int)untodot[resolution] * height );
	    break;
       case GF_MILIM :
	    if ( !resolution ) {
	       CDC *dc = new CDC();
		   dc->CreateIC("DISPLAY",NULL,NULL,0);
		   h = height * dc->GetDeviceCaps(LOGPIXELSY);
		   h /= 25.4;
	       delete dc;
		   return( (int) h );
	       }
	    return((int) (untodot[resolution] * height)/25.4 );
	    break;
       default :
	    return( 0 );
	    break;
       }
 return( 0 );
}

/*
GraphFileDataDlgf::GraphFileDataDlgf( zWindow *pPar, GraphFileData *pg ) :
	      FormDlgf(pPar,zResId("GRAPH_FILE_OPT"), HELPID_DLG_DEFAULT )
{
 char buf[10];
 dlg_data = pg;

 // Format
 pCbFmt = new zAstComboBoxStatic(this, IDC_GFFORMAT );
 pCbFmt->addResStrings(SB_GFFORMAT);
 pCbFmt->selection(dlg_data->getFormat() );
 pCbFmt->setNotifySelChange(this,(NotifyProc)&GraphFileDataDlgf::selchg);

 // Units
 pCbUnt = new zAstComboBoxStatic(this, IDC_GFUNITS );
 pCbUnt->addResStrings(SB_SIZEUNIT);
 pCbUnt->selection(dlg_data->getUnits() );
 pCbUnt->setNotifySelChange(this,(NotifyProc)&GraphFileDataDlgf::selchg);
 enableUnitsFields(dlg_data->getUnits());
 // Resolution
 pCbRes = new zAstComboBoxStatic(this, IDC_GFRESOLUTION );
 pCbRes->addResStrings(SB_RESOLUTION);
 pCbRes->selection(dlg_data->getResolution() );
 pCbRes->setNotifySelChange(this,(NotifyProc)&GraphFileDataDlgf::selchg);

 pStW = new zStaticText(this, IDC_GFSTWD );
 pStW->text( (zString) ResStr(wdims[dlg_data->getUnits()]) );

 pStH = new zStaticText(this, IDC_GFSTHT );
 pStH->text( (zString) ResStr(hdims[dlg_data->getUnits()]) );

 new zFloatEdit(this, IDC_GFHEIGHT, &dlg_data->getHeight(), "####.##");
 new zFloatEdit(this, IDC_GFWIDTH, &dlg_data->getWidth(), "####.##");

 new zCheckBox(this, IDC_GFREVERSE, &dlg_data->getReverse() );
 selchg( 0 );
 run();
}

int GraphFileDataDlgf::enableMonoFields(int en)
{
 enableField(IDC_GFREVERSE, en );
 return( 1 );
}

int GraphFileDataDlgf::enableUnitsFields(int en)
{
 enableField(111, en );
 enableField(IDC_GFRESOLUTION, en );
 return( 1 );
}



int GraphFileDataDlgf::selchg( zEvent *e )
{
 if ( !e || e->parm1() == IDC_GFFORMAT ) {
    if ( pCbFmt->selection() != LB_ERR )
       dlg_data->getFormat() = pCbFmt->selection();
    else
       dlg_data->getFormat() = 0;
    // enableMonoFields( !dlg_data->isFormatColor() );
    }
 else if ( !e || e->parm1() == IDC_GFUNITS ) {
    if ( pCbUnt->selection() != LB_ERR )
       dlg_data->getUnits() = pCbUnt->selection();
    else
       dlg_data->getUnits() = 0;
    enableUnitsFields(dlg_data->getUnits());
    pStW->text( (zString) ResStr(wdims[dlg_data->getUnits()]) );
    pStH->text( (zString) ResStr(hdims[dlg_data->getUnits()]) );
    }
 else if ( !e || e->parm1() == IDC_GFRESOLUTION ) {
    if ( pCbRes->selection() != LB_ERR )
       dlg_data->getResolution() = pCbRes->selection();
    else
       dlg_data->getResolution() = 0;
    }
 return( 1 );
}


*/



