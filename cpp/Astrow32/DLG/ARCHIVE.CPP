#include "stdafx.h"
#include <stdlib.h>
#include "astrow.h"
#include "attrib.h"
#include "inifile.hpp"
#include "archive.hpp"

ArchiveData::ArchiveData(int _arc, int _zip )
{
  arc = _arc;

  lha_zip = _zip;
  delFile = 0;
  if ( arc && lha_zip==1 )
     command="PKZIP -a %s @%s";
  else if ( !arc && lha_zip==1  )
     command="PKUNZIP %s %s *.*";
  else if ( arc && lha_zip ==0 )
     command="LHA a %s @%s";
  else if ( !arc && lha_zip==0  )
     command="LHA x %s %s *.*";
  else if ( arc && lha_zip==2 )
     command="WZUNIP x %s %s";
  else if ( !arc && lha_zip==2  )
	 command="WZZIP a %s %s -@%s";
}

ArchiveData::getFromIni()
{
 CWinApp *app;
 char *sec;

 if ( arc )
    sec = "Archive";
 else
    sec = "UnArchive";
 app=AfxGetApp();
 delFile = (int) app->GetProfileInt( sec, "Delete", delFile );
 lha_zip = (int) app->GetProfileInt( sec, "UseLhaZip", lha_zip );
 command = app->GetProfileString( sec, "Command", (char *)(LPCTSTR)command );
 path = app->GetProfileString( sec, "Path", (char *)(LPCTSTR)path );
 return( 1 );
}


ArchiveData::saveToIni()
{
 char buf[5];
 CWinApp *app;
 char *sec;
 itoa(lha_zip,buf,10);
 if ( arc )
    sec = "Archive";
 else
    sec = "UnArchive";
 app=AfxGetApp();

 app->WriteProfileString( sec, "Command", (char *)(LPCTSTR)command );
 app->WriteProfileString( sec, "Path", (char *)(LPCTSTR)path );
 app->WriteProfileString( sec, "UseLhaZip", buf );
 app->WriteProfileString( sec, "Delete", (delFile?"1":"0") );
 return( 1 );
}
/*
int ArchiveDataDlgf::click(zNotifyEvt *e)
{
 storeData();
 if ( e->identifier() == IDC_ALHA && e->clicked() ) {
    if ( dlg_data->isArc() )
       dlg_data->getCommand() = "LHA a %s @%s";
    else
       dlg_data->getCommand() = "LHA x %s %s *.*";
    }
 else if ( e->identifier() == IDC_AZIP && e->clicked() ) {
    if ( dlg_data->isArc() )
       dlg_data->getCommand() = "PKZIP -a %s @%s";
    else
       dlg_data->getCommand() = "PKUNZIP %s %s *.*";
    }
 else
    return( 0 );
 setControlsToDefault();
 return( 1 );
}

void ArchiveDataDlgf::getData()
{
 dlg_data->isZip() -= IDC_ALHA;
}

ArchiveDataDlgf::ArchiveDataDlgf(zWindow *par, ArchiveData *d ) :
		  FormDlgf(par, zResId("ARCHIVE_DAT"), HELPID_DLG_ARCHIVE )
{
 dlg_data = d;
 new zStringEdit(this, IDC_AARC, &dlg_data->getPath(), "X(149)" );
 new zStringEdit(this, IDC_APROG, &dlg_data->getCommand(), "X(149)" );
 dlg_data->isZip() += IDC_ALHA;
 zRadioGroup *rg = new zRadioGroup( this, IDC_ALHA, IDC_AZIP, &dlg_data->isZip() );
 rg->setNotifyClicked(this, (ClickProc)&ArchiveDataDlgf::click);

 if ( dlg_data->isZip() ) {
    zRadioButton * rbz = new zRadioButton( this, IDC_AZIP );
    rbz->check(1);
    }
 else {
    zRadioButton * rbl = new zRadioButton( this, IDC_ALHA );
    rbl->check(1);
    }

 zCheckBox *pcb = new zCheckBox( this, IDC_ADEL, &dlg_data->isDel() );
 if ( !d->isArc() )
    pcb->disable();
 run();
}
*/