#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "fieldrng.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dialogs.h"
#include "charcons.h"
#include "database.hpp"
#include "acombbox.hpp"
#include "astromn.h"
#include "asfrmdlg.hpp"
#include "relocscr.hpp"
#include "birttran.hpp"
#include "rectscr.hpp"
#include "birthscr.hpp"
#undef memcpy(s,d,n)
#include <string.h>

static BIRTH_DB save_birth;
static RECT_DATA save_rect;
static int birth_saved = 0;


// Classes for Getting Birth Information
// Useage
//
//  LOC_DB lData;
//  BIRTH_DB bData;
//  RECT_DATA rData;
//  static char *am[] = { "AM", "PM" };
//
//    BirthDataDlgf *bd = new BirthDataDlgf( out, &bData, &lData, &rData, "This is a test");
//    if ( bd->completed() ) {
//       out->printf( "Name = %s\n", bData.name );
//       out->printf( "Male or Female = %s\n", sex[bData.sex] );
//       out->printf( "Date = %02d-%02d-%04d\n",
//          bData.birth_data.birth_date.month,
//          bData.birth_data.birth_date.day,
//          bData.birth_data.birth_date.year );
//       out->printf( "Time = %2d:%2d %s\n",
//          bData.birth_data.birth_time.hours,
//          bData.birth_data.birth_time.minutes, am[bData.am_pm] );
//       out->printf( "Country = %s\n", bData.country );
//       out->printf( "State = %s\n", bData.state );
//       out->printf( "Location = %s\n", bData.location );
//       out->printf( "%03d %c %02d\n",
//          bData.birth_data.longitude.degrees,
//          bData.birth_data.longitude.dir,
//          bData.birth_data.longitude.minutes );
//       out->printf( " %02d %c %02d\n",
//          bData.birth_data.latitude.degrees,
//          bData.birth_data.latitude.dir,
//          bData.birth_data.latitude.minutes );
//       out->printf( "tz = %d %s\n", bData.time_zone,
//          timezones[bData.time_zone] );
//       out->printf( "sc = %d %s\n", bData.special_code,
//          speccodes[bData.special_code] );
//       out->printf( "gmt = %d:%d\n",
//          bData.birth_data.local_adjust, bData.birth_data.local_minutes );
//       if (rData.birth_time_known )
//          out->printf("Birth Time is Known\n" );
//       else {
//          out->printf("Birth Time is Not Known\n" );
//          out->printf("Rect_system = %d\n", rData.rect_system );
//          out->printf("Trial Time = %d:%d %s\n",
//             rData.trial.hours,
//             rData.trial.minutes,
//             (rData.am_pm?"PM":"AM"));
//          out->printf( "Angle = %d\n", rData.angle );
//          out->printf( "Sign = %d, deg:min = %d:%d\n",
//             rData.sign, rData.degree.degrees,
//             rData.degree.minutes );
//          out->printf( "total_minutes = %d\n", rData.total_minutes );
//          }
//       }
//    delete bd;
//
//

extern char *strclip( char *pStr );

// static char *sex[] = { "Male", "Female" };


BirthDataDlgf::BirthDataDlgf(zWindow *pPar,
       BIRTH_DB *pB, LOC_DB *pL, RECT_DATA *pR, char *title) :
         BirthTransDataDlgf(pPar,pB,pL,pR,"BIRTH_INF")
{
 pCbsx = new zAstComboBoxStatic(this, IDC_BDSX );
// for ( int i = 0; i < 2; i++ )
//     pCbsx->add( zString(sex[i]) );
 pCbsx->addResStrings(SB_MALE);
 pCbsx->setNotifySelChange(this,
    (NotifyProc)&BirthDataDlgf::selchgStatic);
 pCbsx->selection(dlg_birth->sex);

 pBbdb = new zPushButton(this, IDC_BDBDM);
 pBbdb->setNotifyClicked(this,
      (ClickProc)&BirthDataDlgf::birthMenuBtnClick );
 pBDmenu = NULL;

 pBrect = new zPushButton(this, IDC_BDREC);
 pBrect->setNotifyClicked(this,
      (ClickProc)&BirthDataDlgf::rectBtnClick );
 if ( title != NULL )
    caption(zString(title));
 updateCombos(BRTTRNONLY);
 setId(HELPID_DLG_BINFO);
}

int BirthDataDlgf::birthMenuBtnClick( zNotifyEvt *e )
{
 zRect r;

 if ( pBDmenu == NULL ) {
    getInterior(r);
    zPoint pt = r.topLeft();
    zPoint xp( r.width()/3, r.height()/3);
    pt += xp;
    pBDmenu = new zPopupMenu(pt, this, zResId("BIRTH"));
    if ( pBDmenu == NULL )
       return( 1 );
    /*
    pBDmenu->appendItem(IDM_BDBGET,"Get A Birth From Database.",
    MF_STRING|MF_GRAYED|MF_DISABLED );
    pBDmenu->appendItem(IDM_BDBADD,"Add A New Birth To Database.",
    MF_STRING|MF_GRAYED|MF_DISABLED );
    pBDmenu->appendItem(IDM_BDBREPLACE,"Replace A Birth In Database.",
    MF_STRING|MF_GRAYED|MF_DISABLED );
    pBDmenu->appendItem(IDM_BDBDEL,"Delete A Birth From Database.",
    MF_STRING|MF_GRAYED|MF_DISABLED );
    pBDmenu->appendItem(IDM_BDBRETURN,"Rebuild.", MF_STRING|MF_ENABLED );
    pBDmenu->appendItem(IDM_BDBRETURN,"Return.", MF_STRING|MF_ENABLED );
    */
    pBDmenu->setHilite((LocationDataDlgf *)this,(NotifyProc)&LocationDataDlgf::menuSelect);
    pBDmenu->setCommand(this,(NotifyProc)&BirthDataDlgf::birthMenuCmd,
       IDM_BDBGET, IDM_BDBRETURN );
    }
 if ( pBirthDb->has_Birth() ) {
    pBDmenu->enableItem(IDM_BDBDEL, TRUE );
    pBDmenu->enableItem(IDM_BDBREPLACE, TRUE );
    }
 else {
    pBDmenu->enableItem(IDM_BDBDEL, FALSE );
    pBDmenu->enableItem(IDM_BDBREPLACE, FALSE );
    pBDmenu->grayItem(IDM_BDBDEL, TRUE );
    pBDmenu->grayItem(IDM_BDBREPLACE, TRUE );
    }
 if ( strlen(dlg_birth->name) ) {
    pBDmenu->enableItem(IDM_BDBADD, TRUE );
    pBDmenu->enableItem(IDM_BDBREPLACE, TRUE );
    pBDmenu->enableItem(IDM_BDBGET, TRUE );
    }
 else {
    pBDmenu->enableItem(IDM_BDBADD, FALSE );
    pBDmenu->enableItem(IDM_BDBREPLACE, FALSE );
    pBDmenu->enableItem(IDM_BDBGET, FALSE );
    pBDmenu->grayItem(IDM_BDBADD, TRUE );
    pBDmenu->grayItem(IDM_BDBREPLACE, TRUE );
    pBDmenu->grayItem(IDM_BDBGET, TRUE );
    }
 pBDmenu->go();
 return( 1 );
}

int BirthDataDlgf::birthMenuCmd( zEvent *e )
{
 switch( e->parm1() ) {
       case IDM_BDBGET :
	    dlg_rect->birth_time_known = 1;
	    if ( !pBirthDb->read_birth( strclip(dlg_birth->name),
	      dlg_birth, dlg_rect ) ) {
	       preAdjustTime();
	       birth2Loc(dlg_birth,dlg_data);
	       updateGMT();
	       updateCombos();
	       setControlsToDefault();
	       }
	    break;
       case IDM_BDBADD :
	    storeData();
	    mergeLoc2Birth();
	    pBirthDb->write_birth( dlg_birth, dlg_rect );
	    break;
       case IDM_BDBREPLACE:
	    storeData();
	    mergeLoc2Birth();
	    pBirthDb->replace_birth( dlg_birth, dlg_rect );
	    break;
       case IDM_BDBDEL :
	    pBirthDb->delete_birth( strclip(dlg_birth->name) );
	    break;
       case IDM_BDBMKPOP :
	    pBirthDb->makePopup();
	    pCbnm->reset();
	    pCbnm->loadList( BIRTHBAS_POPUP, 0 );
	    break;
       case IDM_BDBCOPY :
	    if ( !storeData() )
	       break;
	    mergeLoc2Birth();
	    save_birth = *dlg_birth;
	    save_rect = *dlg_rect;
	    birth_saved = 1;
	    break;
       case IDM_BDBPASTE :
	    *dlg_birth = save_birth;
	    *dlg_rect = save_rect;
	    preAdjustTime();
	    birth2Loc(dlg_birth,dlg_data);
	    updateGMT();
	    updateCombos();
	    setControlsToDefault();
	    break;
       case IDM_BDBCLEAR :
	    memset( dlg_rect, 0, sizeof(RECT_DATA) );
	    dlg_rect->birth_time_known = 1;
	    memset( dlg_birth, 0, sizeof(BIRTH_DB) );
	    preAdjustTime();
	    birth2Loc(dlg_birth,dlg_data);
	    updateGMT();
	    updateCombos();
	    setControlsToDefault();
	    break;
       case IDM_BDBRETURN :
       default:
	    break;
       }
 delete pBDmenu;
 pBDmenu = NULL;
 return( 1 );
}

int BirthDataDlgf::rectBtnClick( zNotifyEvt *e )
{
  RectDataDlgf *rd = new RectDataDlgf(
       this, dlg_rect, dlg_birth);
  if ( rd->completed() )
     rd->computeAngle();
  delete rd;
  setFocus();
  return( 1 );
}


void BirthDataDlgf::updateCombos(int nCode)
{
 pCbsx->selection(dlg_birth->sex);
 BirthTransDataDlgf::updateCombos(nCode);
}


BirthDataDlgf::~BirthDataDlgf()
{
  if ( pBDmenu != NULL ) {
     delete pBDmenu;
     pBDmenu = NULL;
     }
}

int BirthDataDlgf::selchgStatic( zEvent *e )
{
 int v;

 switch( e->parm1() ) {
       case IDC_BDSX:
        if ( ( v = pCbsx->selection()) == LB_ERR )
           v = 0;
        if ( v )
           dlg_birth->sex = 1;
        else
           dlg_birth->sex = 0;
        break;
       default :
        break;
       }
 return( 1 );
}


BirthDataDialog::BirthDataDialog(zWindow *pPar, BIRTH_DB *pB, RECT_DATA *pR, char *title )
{
 rSave = *pR;
 bSave = *pB;
 pBtd = new BirthDataDlgf( pPar, &bSave, &loc, &rSave, title);
 pBtd->run();
 if ( pBtd->completed() ) {
    *pB = bSave;
    *pR = rSave;
    }
}
