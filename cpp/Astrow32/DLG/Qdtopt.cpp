#include "stdafx.h"
#include "inifile.hpp"
#include "qdtopt.hpp"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )


int QdtData::saveToIni()
{
 char buf[30];
 CWinApp *app =AfxGetApp();

		  
 itoa( runOnce, buf, 10 );
 app->WriteProfileString( "QDTrans", "RunOnce", buf);
 itoa( restrictTime, buf, 10 );
 app->WriteProfileString( "QDTrans", "TimeRestrict", buf);
 itoa( firstHours, buf, 10 );
 app->WriteProfileString( "QDTrans", "FirstHours", buf);
 itoa( firstMin, buf, 10 );
 app->WriteProfileString( "QDTrans", "FirstMin", buf);
 itoa( lastHours, buf, 10 );
 app->WriteProfileString( "QDTrans", "LastHours", buf);
 itoa( lastMin, buf, 10 );
 app->WriteProfileString( "QDTrans", "LastMin", buf);
 itoa( lastMonth, buf, 10 );
 app->WriteProfileString( "QDTrans", "LastMonth", buf);
 itoa( lastDay, buf, 10 );
 app->WriteProfileString( "QDTrans", "LastDay", buf);
 app->WriteProfileString( "QDTrans", "Name", name);
 app->WriteProfileString( "QDTrans", "Event", event);
 return( 1 );
}

int QdtData::getFromIni()
{
 CWinApp *app =AfxGetApp();
	
 runOnce = (int) app->GetProfileInt( "QDTrans", "RunOnce", runOnce);
 lastMonth = (int) app->GetProfileInt( "QDTrans", "LastMonth", lastMonth);
 lastDay = (int) app->GetProfileInt( "QDTrans", "LastDay", lastDay);
 restrictTime = (int) app->GetProfileInt( "QDTrans", "TimeRestrict", restrictTime);
 firstMin = (int) app->GetProfileInt( "QDTrans", "FirstMin", firstMin);
 firstHours = (int) app->GetProfileInt( "QDTrans", "FirstHours", firstHours);
 lastMin = (int) app->GetProfileInt( "QDTrans", "LastMin", lastMin);
 lastHours = (int) app->GetProfileInt( "QDTrans", "LastHours", lastHours);
 name= app->GetProfileString( "QDTrans", "Name", "");
 event= app->GetProfileString( "QDTrans", "Event", "");
 return( 1 );
}

/*
QdtDataDlgf::QdtDataDlgf( zWindow *pPar, QdtData *qd ) :
		    FormDlgf(pPar,zResId("QDT_OPTIONS"), HELPID_DLG_FCONV )
{
 data = qd;
 if ( data->getFirstHours() > 12 ) {
    fam = 1;
    data->getFirstHours() -= 12;
    }
 else if ( data->getFirstHours == 0 ) {
    fam = 0;
    data->getFirstHours() = 12;
    }
 else
    fam = 0;
 if ( data->getLastHours() > 12 ) {
    lam = 1;
    data->getLastHours() -= 12;
    }
 else if ( data->getLastHours == 0 ) {
    lam = 0;
    data->getLastHours() = 12;
    }
 else
    lam = 0;
 zAstComboBoxStatic *pCfam = new zAstComboBoxStatic(this, IDC_QDTFAM );
 pCfam->addResStrings(SB_AMPM);
 pCfam->setStoreAddr(&fam);
 pCfam->selection(fam);
 zAstComboBoxStatic *pClam = new zAstComboBoxStatic(this, IDC_QDTLAM );
 pClam->addResStrings(SB_AMPM);
 pClam->setStoreAddr(&lam);
 pClam->selection(lam);
 new zCheckBox( this, IDC_QDTRO, &data->getRunOnce());
 new zCheckBox( this, IDC_QDTRT, &data->getRestrictTime());
 new zNumFieldRng( this, IDC_QDTFH,
	  (int *)&data->getFirstHours(), 12, 0);
 new zNumFieldRng( this, IDC_QDTFM,
	  (int *)&data->getFirstMin(), 59, 0);
 new zNumFieldRng( this, IDC_QDTLH, (int *)&data->getLastHours(), 12, 0);
 new zNumFieldRng( this, IDC_QDTLM, (int *)&data->getLastMin(), 59, 0);
 run();
}

QdtDataDlgf::getData()
{
 storeData();

 if ( fam )
    data->getFirstHours() += 12;
 else if ( !fam && data->getFirstHours() == 12 )
    data->getFirstHours() == 0;
 if ( lam )
    data->getLastHours() += 12;
 else if ( !lam && data->getLastHours() == 12 )
    data->getLastHours() = 0;
 return( 1 );
}
*/