#include "stdafx.h"
#include "astrow.h"
#include <stdlib.h>
#include "inifile.hpp"
#include "printopt.hpp"
#include "repstyle.hpp"

// Classes to handle Print Data and get from user
// Useage:
//
// PrintDataDlgf *pd = new PrintDataDlgf(out,
//   &printData );
// if ( pd->completed() ) {
//    pd->getData();
//    out->printf("print Comment = %d\n", (int) printData.getCmt()  );
//    out->printf("Print Cover Page = %d\n", (int) printData.getCpg()  );
//    out->printf("Print Head P1 = %d\n", (int) printData.getHeadP1()  );
//    out->printf("Draft = %d\n", (int) printData.getDraft()  );
//    out->printf("Copies = %d\n", (int) printData.getCopies()  );
//    if ( !printData.getRange() )
//       out->printf("Print All\n" );
//    else {
//       out->printf("Print Range\n" );
//       out->printf("From = %d\n", (int) printData.getFrom()  );
//       out->printf("To = %d\n", (int) printData.getTo()  );
//       }
//    }
//   delete pd;
//



int PrintData::saveToIni()
{
 int f;
 char buf[30];

 itoa( centerHead, buf, 10 );
 f = WritePrivateProfileString( PrintData_SEC, "CenterHeads", buf, APPNAME );
#ifdef PRO
 itoa( cpg, buf, 10 );
 f = WritePrivateProfileString( PrintData_SEC, "PrintCoverPage", buf, APPNAME );
 itoa( cmt, buf, 10 );
 f = WritePrivateProfileString( PrintData_SEC, "PrintComment", buf, APPNAME );
 itoa( cmtb4, buf, 10 );
 f = WritePrivateProfileString( PrintData_SEC, "CommentBefore", buf, APPNAME );
#endif
 itoa( hdp1, buf, 10 );
 f = WritePrivateProfileString( PrintData_SEC, "HeadP1", buf, APPNAME );
 return( f );
}

int PrintData::getFromIni()
{
 centerHead =  (int) GetPrivateProfileInt( PrintData_SEC, "CenterHeads", centerHead, APPNAME );
 hdp1 = (int) GetPrivateProfileInt( PrintData_SEC, "HeadP1", hdp1, APPNAME );
#ifdef PRO
 cpg = (int) GetPrivateProfileInt( PrintData_SEC, "PrintCoverPage", cpg, APPNAME );
 cmt = (int) GetPrivateProfileInt( PrintData_SEC, "PrintComment", cmt, APPNAME );
 cmtb4 = (int) GetPrivateProfileInt( PrintData_SEC, "CommentBefore", cmtb4, APPNAME );
#endif
 return( 1 );
}
/*
PrintDataDlgf::PrintDataDlgf(zWindow *pPar, PrintData *pd) : FormDlgf( pPar,zResId("PRINT_OPT"), HELPID_DLG_PRINTOPT )
{ 
 form_data = pd;

#ifdef PRO
 new zCheckBox( this, IDC_POCMT, &form_data->getCmt());
 new zCheckBox( this, IDC_POCPG, &form_data->getCpg());
#endif
 new zCheckBox( this, IDC_POHDP1, &form_data->getHeadP1());
#ifdef PRO
 new zCheckBox( this, IDC_POCMTBF, &form_data->getCmtBefore());
#endif
 new zCheckBox( this, IDC_POCNTR, &form_data->getCenterHead());
 form_data->getRange() += IDC_POALL;
 zRadioGroup *rg = new zRadioGroup(this, IDC_POALL, IDC_PORANGE,
	&form_data->getRange() );
 rg->setNotifyClicked(this, (ClickProc)&PrintDataDlgf::click );
 if ( form_data->getRange() == IDC_POALL )
    enableRange(0);
 else
    enableRange(1);
 new zIntEdit( this, IDC_POFROM, &form_data->getFrom(),
	FLD_NUMERIC);
 new zIntEdit( this, IDC_POTO, &form_data->getTo(),
	FLD_NUMERIC|FLD_NOTREQUIRED);
 run();
}

int PrintDataDlgf::click(zNotifyEvt *e)
{
 storeData();
 if ( e->identifier() == IDC_POALL && e->clicked() )
    enableRange( 0 );
 else if ( e->identifier() == IDC_PORANGE && e->clicked() )
    enableRange( 1 );
 else
    return( 0 );
 setControlsToDefault();
 return( 1 );
}


int PrintDataDlgf::enableRange(int en)
{
 enableField(IDC_POFROM, en );
 enableField(IDC_POTO, en );
 enableField(109, en );
 enableField(111, en );
 return( 1 );
}

void PrintDataDlgf::getData()
{
 form_data->getRange() -= IDC_POALL;
 if ( form_data->getRange() ) {
    if ( !form_data->getTo() )
       form_data->getTo() = 999;
    }
}


int PrintDataDlgf::command(zCommandEvt *e)
{
 switch( e->cmd() ) {
      case IDC_POSTYLES:
	   {
	   PrinterSetup ps;
	   ps.getFromIni(PrintData_SEC);
	   zPrinterDisplay *pd = new zPrinterDisplay(ps.getSpec(),
		  ps.toDevMode(this,0));
	   ReportStyles rs(pd);
	   rs.getFromIni(PrintData_SEC);
	   ReportStylesDlgf *rsd = new ReportStylesDlgf(this, &rs, (zDisplay *)pd);
	   if ( rsd->completed() )
	      rs.saveToIni(PrintData_SEC);
	   delete rsd;
	   delete pd;
	   return( 1 );
	   }
	   break;
      default :
	   return( 0 );
	   break;
      }
 return( 0 );


}
*/