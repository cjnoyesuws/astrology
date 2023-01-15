#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "dialogs.h"
#include "attrib.h"
#include "inifile.hpp"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "tbtoptn.hpp"
#include "basedcs.h"
#include "resource.h"
#include "helpid.h"

static char *sec = "TBTOptions";

static char *fmts[] = { "AMI-Lotus AMIPro","ASC-ASCII","AST-ASTRO","DOC-ASTRO w/.DOC ext",
       "MSW-Microsoft Word & Write","WS--WordStar","WP4-WordPerfect 4.x",
       "WP5-WordPerfect 5.x","WP5-WordPerfect 6.x", "RTF-Microsoft Word RTF", NULL };

static char fmtKeys[][4] = { "AMI","ASC","AST","DOC",
       "MSW","WS","WP4", "WP5","WP6","RTF", NULL };


TbtOptions::TbtOptions()
{
 enableExtText = 0;
 textFormat = 2;
 txtFmtKey = "AST";
 txtSrcExt = ".AST";
}


int TbtOptions::saveToIni()
{
 int f;
 char buf[30];

 itoa( enableExtText, buf, 10 );
 f = WritePrivateProfileString( sec, "EnableExtText", buf, APPNAME );
 if ( !f )
    return( 0 );
 itoa( textFormat, buf, 10 );
 f = WritePrivateProfileString( sec, "TextFormat", buf, APPNAME );
 f = WritePrivateProfileString( sec, "TextFormatKey", (char *)txtFmtKey, APPNAME );
 txtSrcExt = strupr((char *)txtSrcExt);
 f = WritePrivateProfileString( sec, "TextSourceExt", (char *)txtSrcExt, APPNAME );
 f = WritePrivateProfileString( sec, "SourceAnsi", (srcAnsi?"1":"0" ), APPNAME );
 f = WritePrivateProfileString( sec, "EditAnsi", (editAnsi?"1":"0" ), APPNAME );
 if (textFormat && textFormat < 4 )
    cvtAnsi = editAnsi;
 f = WritePrivateProfileString( sec, "CvtAnsi", (cvtAnsi?"1":"0" ), APPNAME );
 if ( !f )
    return( 0 );
 else
    return( f );
}

int TbtOptions::getFromIni()
{
 int f;
 char buf[30];
 char buf2[30];

 enableExtText = (int) GetPrivateProfileInt( sec, "EnableExtText", enableExtText, APPNAME );
 textFormat = (int) GetPrivateProfileInt( sec, "TextFormat", textFormat, APPNAME );
 f = (int) GetPrivateProfileString( sec, "TextFormatKey", (char *)txtFmtKey, buf, 4, APPNAME );
 txtFmtKey = strupr(buf);
 f = (int) GetPrivateProfileString( sec, "TextSourceExt", (char *)txtSrcExt, buf, 5, APPNAME );
 txtSrcExt = strupr(buf);
 srcAnsi = (int) GetPrivateProfileInt( sec, "SourceAnsi", srcAnsi, APPNAME );
 cvtAnsi = (int) GetPrivateProfileInt( sec, "CvtAnsi", cvtAnsi, APPNAME );
 editAnsi = (int) GetPrivateProfileInt( sec, "EditAnsi", editAnsi, APPNAME );
 return( 1 );
}


TbtOptionsDlgf::TbtOptionsDlgf( zWindow *pPar, TbtOptions *pO ) :
	      FormDlgf(pPar,zResId(IDD_TBT_OPTIONS), HELPID_DLG_SETUP )
{
 char buf[10];
 dlg_data = pO;

 //ExtText
 new zCheckBox(this, IDC_CHECK1, &dlg_data->getEnableExtText() );
 // Format
 pCbFmt = new zAstComboBoxStatic(this, IDC_COMBO1 );
 pCbFmt->addCharStrings(fmts);
 pCbFmt->selection(dlg_data->getTextFormat());
 pCbFmt->setNotifySelChange(this,(NotifyProc)&TbtOptionsDlgf::selchg);
 new zStringEdit(this, IDC_EDIT1, &dlg_data->getTextSourceExt(),
		"XXXX", FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zCheckBox(this, IDC_CHECK2, &dlg_data->getSrcAnsi() );
 new zCheckBox(this, IDC_CHECK3, &dlg_data->getEditAnsi() );
 selchg( 0 );
 run();
}



int TbtOptionsDlgf::selchg( zEvent *e )
{
 if ( !e || e->parm1() == IDC_COMBO1 ) {
    if ( pCbFmt->selection() != LB_ERR )
       dlg_data->getTextFormat() = pCbFmt->selection();
    else
       dlg_data->getTextFormat() = 2;
    dlg_data->getTextFormatKey() = fmtKeys[dlg_data->getTextFormat()];
    switch(dlg_data->getTextFormat()) {
	  case 0 :
	       dlg_data->getEditAnsi()=1;
	       dlg_data->getCvtAnsi()=1;
	       break;
	  case 4 :
	       dlg_data->getEditAnsi()=1;
	       dlg_data->getCvtAnsi()=0;
	       break;
	  case 5 :
	       dlg_data->getEditAnsi()=0;
	       dlg_data->getCvtAnsi()=0;
	       break;
	  case 6 :
	       dlg_data->getEditAnsi()=0;
	       dlg_data->getCvtAnsi()=0;
	       break;
	  case 7 :
	       dlg_data->getEditAnsi()=0;
	       dlg_data->getCvtAnsi()=0;
	       break;
	  default :
	       break;
	  }
    setControlsToDefault();
    }
 return( 1 );
}






