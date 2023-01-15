#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "attrib.h"
#include "inifile.hpp"
#include "convopt.hpp"
#include "repstyle.hpp"
#include "txtdrv.h"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

//  Classes to handle Data for text conversion. Classes to get data
//  from user
//
//  Useage of these classes
//
//  ConvDataForm *cd = new ConvDataForm(
//      new ConvDataDlgf(out,&conversionData),
//      &conversionData );
//  if ( cd->completed() ) {
//     cd->getData();
//     out->printf("left = %d\n", (int) conversionData.getLeft() );
//     out->printf("width = %d\n", (int) conversionData.getWidth()  );
//     out->printf("print Comment = %d\n", (int) conversionData.getCmt()  );
//     out->printf("Print Cover Page = %d\n", (int) conversionData.getCpg()  );
//     out->printf("Format = %d\n", (int) conversionData.getFmt()  );
//     }
//  delete cd;
//
//
/*
char *fmts[] = {  "Plain ASCII Text (DOS)", "Plain ASCII Text (Windows)",
 "Plain ASCII No Line Breaks (DOS)", "Plain ASCII No Line Breaks (Windows)",
 "Coded ASCII Text (DOS)",   "Coded ASCII Text (Windows)",
 "Coded ASCII No Line Breaks (DOS)",  "Coded ASCII No Line Breaks (Windows)",
 "WordStar Version 3.x", "WordStar Version 4.x",
 "WordPerfect 4.x", "WordPerfect 5.x",
 "XYWrite", "XYWrite No Line Breaks",
 "Microsoft Word DOS (RTF)", "Microsoft Word Windows (RTF)", "Windows Write" };
*/
//     out->printf("left = %d\n", (int) conversionData.getLeft() );
//     out->printf("width = %d\n", (int) conversionData.getWidth()  );
//     out->printf("print Comment = %d\n", (int) conversionData.getCmt()  );
//     out->printf("Print Cover Page = %d\n", (int) conversionData.getCpg()  );
//     out->printf("Format = %d\n", (int) conversionData.getFmt()  );


int ConvData::saveToIni()
{
 CWinApp *app = AfxGetApp();
 CString a;


 a.Format("%d",left);
 app->WriteProfileString( ConvData_SEC, "LeftMarg", a );
 a.Format("%d",width);
 app->WriteProfileString( ConvData_SEC, "Width", a );
 a.Format("%d",fmt);
 app->WriteProfileString( ConvData_SEC, "FileFormat", a );
 app->WriteProfileString( ConvData_SEC, "CenterHeads", (ctr?"1":"0") );
 app->WriteProfileString( ConvData_SEC, "Justify", (just?"1":"0") );
#ifdef DELUXE
 app->WriteProfileString( ConvData_SEC, "DoGlyphs", (doGlyph?"1":"0") );
 a.Format("%d",glyphFont);
 app->WriteProfileString( ConvData_SEC, "GlyphFont", a );
#endif
#ifdef PRO
 app->WriteProfileString( ConvData_SEC, "PrintCoverPage", (cpg?"1":"0") );
 app->WriteProfileString( ConvData_SEC, "PrintComment", (cmt?"1":"0") );
 app->WriteProfileString( ConvData_SEC, "CommentBefore", (cmtf?"1":"0") );
#endif
 app->WriteProfileString( "SmartAscii", "StartBold", fa.bold_on );
 app->WriteProfileString( SmartAscii_SEC, "EndBold", fa.bold_off );
 app->WriteProfileString( SmartAscii_SEC, "StartScore", fa.uscore_on );
 app->WriteProfileString( SmartAscii_SEC, "EndScore", fa.uscore_off );
 app->WriteProfileString( SmartAscii_SEC, "StartHead", fa.head_on );
 app->WriteProfileString( SmartAscii_SEC, "EndHead", fa.head_off );
 return( 1 );
}

int ConvData::getFromIni()
{
 char buf[10];
 CWinApp *app = AfxGetApp();
 left = (int) atoi(app->GetProfileString( ConvData_SEC, "LeftMarg", itoa(left,buf,10) ));
 width = (int) atoi(app->GetProfileString( ConvData_SEC, "Width", itoa(width,buf,10) ));
 fmt = (int) atoi(app->GetProfileString( ConvData_SEC, "FileFormat", itoa(fmt,buf,10)));
 ctr = (int) atoi(app->GetProfileString( ConvData_SEC, "CenterHeads", itoa(ctr,buf,10) ));
 just = (int) atoi(app->GetProfileString( ConvData_SEC, "Justify", itoa(just,buf,10) ));
#ifdef PRO
 cpg = (int) atoi(app->GetProfileString( ConvData_SEC, "PrintCoverPage", itoa(cpg,buf,10) ));
 cmt = (int) atoi(app->GetProfileString( ConvData_SEC, "PrintComment", itoa(cmt,buf,10) ));
 cmtf = (int) atoi(app->GetProfileString( ConvData_SEC, "CommentBefore", itoa(cmtf,buf,10) ));
#endif
 fa.bold_on = app->GetProfileString( SmartAscii_SEC, "StartBold", F_BOLD_ON );
 fa.bold_off = app->GetProfileString( SmartAscii_SEC, "EndBold", F_BOLD_OFF  );
 fa.uscore_on = app->GetProfileString( SmartAscii_SEC, "StartScore", F_SCOR_ON );
 fa.uscore_off = app->GetProfileString( SmartAscii_SEC, "EndScore", F_SCOR_OFF  );
 fa.head_on = app->GetProfileString( SmartAscii_SEC, "StartHead", F_HEAD_ON );
 fa.head_off = app->GetProfileString( SmartAscii_SEC, "EndHead", F_HEAD_OFF  );
#ifdef DELUXE
 doGlyph = (int) atoi(app->GetProfileString( ConvData_SEC, "DoGlyph", itoa(doGlyph,buf,10) ));
 glyphFont = (int) atoi(app->GetProfileString( ConvData_SEC, "GlyphFont", itoa(glyphFont,buf,10) ));
#endif
 return( 1 );
}

/*
ConvDataDlgf::ConvDataDlgf( zWindow *pPar, ConvData *pC ) :
		    FormDlgf(pPar,zResId("CONV_OPT"), HELPID_DLG_FCONV )
{
 char buf[10];
 dlg_data = pC;

 sprintf( buf, "%01d.%02d", dlg_data->getLeft()/100, dlg_data->getLeft()%100 );
 lft = buf;
 new zStringEdit(this, IDC_CVLFT, &lft, "9'.'99", FLD_COMPLETE );
 sprintf( buf, "%02d.%02d", dlg_data->getWidth()/100, dlg_data->getWidth()%100 );
 wid = buf;
 new zStringEdit(this, IDC_CVWID, &wid, "99'.'99", FLD_COMPLETE  );
#ifdef PRO
 new zCheckBox(this, IDC_CVCMT, &dlg_data->getCmt() );
 new zCheckBox(this, IDC_CVCPG, &dlg_data->getCpg() );
 new zCheckBox(this, IDC_CVCB4, &dlg_data->getCmtFst() );
#endif
 pCb = new zAstComboBoxStatic(this, IDC_CVFMT );
//for ( int i = 0; i < 17; i++ )
//       pCb->add(fmts[i]);
 pCb->addResStrings(SB_WPFMT);
 pCb->selection(dlg_data->getFmt() );
 pCb->setNotifySelChange(this,(NotifyProc)&ConvDataDlgf::selchg);
 selchg( 0 );
 run();
}

void ConvDataDlgf::getData()
{
 float v;

 v = atof(lft);
 dlg_data->setLeft(v * 100);
 v = atof(wid);
 dlg_data->setWidth(v * 100);
}



int ConvDataDlgf::selchg( zEvent *e )
{
 if ( pCb->selection() != LB_ERR )
    dlg_data->setFmt( pCb->selection());
 else
    dlg_data->setFmt( 0 );
 if ( dlg_data->getFmt() == MS_RTFDOS || dlg_data->getFmt() == MS_RTFANS ||
      dlg_data->getFmt() == AMIPRO /*|| dlg_data->getFmt() == WORDPFCI*//*)
    enableField( IDC_CVSTYLES, 1 );
 else
    enableField( IDC_CVSTYLES, 0 );
 if ( dlg_data->getFmt() >= ASCIITXDOS && dlg_data->getFmt() <= ASCIINBDOS )
    enableField( IDC_CVPSEUDO, 1 );
 else
    enableField( IDC_CVPSEUDO, 0 );
 return( 1 );
}


int ConvDataDlgf::command(zCommandEvt *e)
{
 switch( e->cmd() ) {
      case IDC_CVPSEUDO:
	   {
	   FIL_ATTRIB fa = *dlg_data->getFileAttribs();
	   PseudoAsciiDlgf *psd = new PseudoAsciiDlgf(this, &fa );
	   if ( psd->completed() ) {
	      psd->getData();
	      *dlg_data->getFileAttribs() = fa;
	      }
	   delete psd;
	   return( 1 );
	   break;
	   }
      case IDC_CVSTYLES :
	   {
	   zWinDisplay *zd = new zWinDisplay(this);
	   ReportStyles rs(zd);
	   rs.getFromIni(ConvData_SEC);
	   ReportStylesDlgf *rsd = new ReportStylesDlgf(this, &rs, zd);
	   if ( rsd->completed() )
	      rs.saveToIni(ConvData_SEC);
	   delete zd;
	   delete rsd;
	   return( 1 );
	   }
	   break;
      default :
	   return( 0 );
	   break;
      }
 return( 0 );


}


PseudoAsciiDlgf::PseudoAsciiDlgf( zWindow *pPar, FIL_ATTRIB *d ) :
		      FormDlgf(pPar,zResId("PSEUDO_DAT"), HELPID_DLG_PSEUDO )
{
 data = d;
 char *pic = "X(45)";
 sh = d->head_on;
 new zStringEdit(this, IDC_PASHEAD, &sh, pic, FLD_ALPHANUMERIC);
 eh = d->head_off;
 new zStringEdit(this, IDC_PAEHEAD, &eh, pic, FLD_ALPHANUMERIC);
 sb = d->bold_on;
 new zStringEdit(this, IDC_PASBOLD, &sb, pic, FLD_ALPHANUMERIC);
 eb = d->bold_off;
 new zStringEdit(this, IDC_PAEBOLD, &eb, pic, FLD_ALPHANUMERIC);
 su = d->uscore_on;
 new zStringEdit(this, IDC_SASSCORE, &su, pic, FLD_ALPHANUMERIC);
 eu = d->uscore_off;
 new zStringEdit(this, IDC_SAESCORE, &eu, pic, FLD_ALPHANUMERIC);
 centerDialog(this);
 show();
 modal();
}

void PseudoAsciiDlgf::getData()
{
 strcpy( data->bold_on, (char *)sb );
 strcpy( data->bold_off, (char *)eb );
 strcpy( data->head_on, (char *)sh );
 strcpy( data->head_off, (char *)eh );
 strcpy( data->uscore_on, (char *)su );
 strcpy( data->uscore_off, (char *)eu );
}
*/