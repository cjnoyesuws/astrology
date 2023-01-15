#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "fieldrng.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dialogs.h"
#include "charcons.h"
#include "database.hpp"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "relocscr.hpp"
#include "astromn.H"

static LOC_DB save_loc;
static int loc_saved = 0;
extern WORD   wCurrentMenuCmd;
extern DWORD  dwCurrentMenuBits;

//  Screen and related objects to get relocation info
//  from user.
//
//  LOC_DB data;
//
//  LocationDataDlgf *ld = new LocationDataDlgf( out, &data ), &data );
//  if ( ld->completed() ) {
//     out->printf( "Country = %s\n", data.country );
//     out->printf( "State = %s\n", data.state );
//     out->printf( "Location = %s\n", data.location );
//     out->printf( "%03d %c %02d\n",
//       data.longitude.degrees, data.longitude.dir,
//       data.longitude.minutes );
//     out->printf( " %02d %c %02d\n",
//       data.latitude.degrees, data.latitude.dir,
//       data.latitude.minutes );
//     out->printf( "tz = %d %s\n", data.time_zone,
//       timezones[data.time_zone] );
//     out->printf( "sc = %d %s\n", data.special_code,
//       speccodes[data.special_code] );
//     out->printf( "gmt = %d:%d\n",
//       data.hrs_offset, data.min_offset );
//       }
//  delete ld;
//
//  a second higher level form. data is not changed unless OK is pressed.
//
//  RelocationDataDlg *rd = new RelocationDataDlg( pPar, &data );
//  delete rd;
//

extern char *strclip( char *pStr );

#define TZ_OTHER 21
#define SC_OTHER 6
/*
static char *ns[] = { "North", "South", NULL };
static char *ew[] = { "West", "East", NULL };
*/
static char spec_vals[] = { 0, -1, -1, -2, -1, 1, 0 };
static char tim_vals[] = { 3, 4, 5, 6, 7, 8, 10, 0, -1, -2, -3, -8, -9, -7, -12,
		   -10, -8, -8, 5, 11, 12, 0 };

/* duplicated in charcons.cpp
char *timezones[] = { "Eastern Atlantic", "Atlantic Standard", "Eastern Standard",
   "Central Standard", "Mountain Standard", "Pacific Standard", "Hawaii",
   "Greenwich Mean", "Western European", "Eastern Europe", "Eurasia",
   "China", "Japan", "Indochina", "New Zealand", "E. Australia",
   "S. Australia", "W. Australia", "India", "Samoa", "Int'l Date Line",
   "Other", NULL };

char *speccodes[] = { "Standard Time", "War Time", "Daylight Savings",
	       "Double British Summer", "Summer Time", "Winter Time",
	       "Other", NULL };
*/



LocationDataDlgf::LocationDataDlgf(zWindow *pPar, LOC_DB *pL, char *pDlg)
			    :  FormDlgf(pPar,zResId(pDlg), HELPID_DLG_RELOC )
{
 long lrec;
 int r;
 dlg_data = pL;

 pCbns = new zAstComboBoxStatic(this, IDC_BDLANS );
 pCbns->addResStrings(SB_NORTH);
// for ( int i = 0; i < 2; i++ )
//     pCbns->add( zString(ns[i]) );
 if ( !dlg_data->latitude.dir )
    dlg_data->latitude.dir = 'N';
 pCbns->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgStatic);

 pCbew = new zAstComboBoxStatic(this, IDC_BDLOEW );
 pCbew->addResStrings( SB_WEST );
// for ( i = 0; i < 2; i++ )
//     pCbew->add( zString(ew[i]) );
 if ( !dlg_data->longitude.dir )
    dlg_data->longitude.dir = 'W';
 pCbew->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgStatic);

 pCbsc = new zAstComboBoxStatic(this, IDC_BDSC );
 pCbsc->addResStrings(SB_SPECC);
// for ( i = 0; i < SC_OTHER+1; i++ )
//     pCbsc->add( zString(speccodes[i]) );
 pCbsc->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgStatic);

 pCbtz = new zAstComboBoxStatic(this, IDC_BDTZ );
 pCbtz->addResStrings(SB_TZONE);
// for ( i = 0; i < TZ_OTHER+1; i++ )
//     pCbtz->add( zString(timezones[i]) );
 pCbtz->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgStatic);

 pLocDb = new LocDatabase();
 if ( pLocDb != NULL )
    pLocDb->startup();

 pCbco = new zAstComboBoxFull(this, IDC_BDCO );
 pCbco->loadList( LOCATION_POPUP, 0L );
 pCbco->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgFull);
 pCbco->setNotifyEditUpdate(this,
	(NotifyProc)&LocationDataDlgf::editUpdate);
 pCbco->setNotifyKillFocus(this,
	(NotifyProc)&LocationDataDlgf::killFocus);

 pCbst = new zAstComboBoxFull(this, IDC_BDST );
 if ( (lrec = pLocDb->find_loc(dlg_data->country,
		NULL, NULL, "1:" )) != -1L )
    pCbst->loadList( LOCATION_POPUP, lrec );
 pCbst->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgFull);
 pCbst->setNotifyEditUpdate(this,
	(NotifyProc)&LocationDataDlgf::editUpdate);
 pCbst->setNotifyKillFocus(this,
	(NotifyProc)&LocationDataDlgf::killFocus);

 pCblo = new zAstComboBoxFull(this, IDC_BDLO );
 pCblo->setNotifySelChange(this,
	(NotifyProc)&LocationDataDlgf::selchgFull);
 pCblo->setNotifyEditUpdate(this,
	(NotifyProc)&LocationDataDlgf::editUpdate);
 pCblo->setNotifyKillFocus(this,
	(NotifyProc)&LocationDataDlgf::killFocus);
 pBLoc = new zPushButton(this, IDC_BDLOMEN);
 pBLoc->setNotifyClicked(this,
      (ClickProc)&LocationDataDlgf::locMenuBtnClick );
 pMenu = NULL;
 new zNumFieldRng(this, IDC_BDLOD, (int *)&dlg_data->longitude.degrees,
	  180, 0);
 new zNumFieldRng(this, IDC_BDLOM, (int *)&dlg_data->longitude.minutes,
	  59, 0);

 new zNumFieldRng(this, IDC_BDLAD, (int *)&dlg_data->latitude.degrees,
	  90, 0);
 new zNumFieldRng(this, IDC_BDLAM, (int *)&dlg_data->latitude.minutes,
	  59, 0);

 new zNumFieldRng(this, IDC_BDGH, (int *)&dlg_data->hrs_offset,
	  12, -12);
 new zNumFieldRng(this, IDC_BDGM, (int *)&dlg_data->min_offset,
	  59, 0);
 updateCombos();
}


int LocationDataDlgf::command( zCommandEvt *e )
{
 switch( e->cmd() ) {
       default:
	    return( 0 );
	    break;
       }
}


void LocationDataDlgf::updateCombos(int nCode)
{
 long lrec;
 int r;

 pCbns->selection((dlg_data->latitude.dir=='S'?1:0));
 pCbew->selection((dlg_data->longitude.dir=='E'?1:0));
 pCbsc->selection(dlg_data->special_code);
 pCbtz->selection(dlg_data->time_zone);
 if ( nCode >= 0 ) {
    r = pCbco->selection(zString(strclip(dlg_data->country)));
    if ( r == LB_ERR )
       pCbco->zControl::text(zString(dlg_data->country));

    if ( (lrec = pLocDb->find_loc(strclip(dlg_data->country),
		NULL, NULL, "1:", nCode )) != -1L )
       pCbst->loadList( LOCATION_POPUP, lrec );
    r = pCbst->selection(zString(dlg_data->state));
    if ( r == LB_ERR )
       pCbst->zControl::text(zString(dlg_data->state));
    if ( (lrec = pLocDb->find_loc(strclip(dlg_data->country),
	strclip(dlg_data->state), NULL, "2:", nCode )) != -1L )
       pCblo->loadList( LOCATION_POPUP, lrec );
    if ( strlen( dlg_data->location ) )
       r = pCblo->selection(zString(dlg_data->location));
    else {
      r = 0;
      pCblo->zControl::text(zString(""));
      }
    if ( r == LB_ERR )
       pCblo->zControl::text(zString(dlg_data->location));
    }
 if ( dlg_data->time_zone != TZ_OTHER ) {
    enableField( IDC_BDGH, 0 );
    enableField( IDC_BDGM, 0 );
    }
 else {
    enableField( IDC_BDGH, 1 );
    enableField( IDC_BDGM, 1 );
    }
}

LocationDataDlgf::~LocationDataDlgf()
{
  if ( pLocDb != NULL ) {
     pLocDb->shutdown();
     delete pLocDb;
     }
  if ( pMenu != NULL ) {
     delete pMenu;
     pMenu = NULL;
     }
}

int LocationDataDlgf::selchgStatic( zEvent *e )
{
 int v;

 switch( e->parm1() ) {
       case IDC_BDLANS:
	    if ( ( v = pCbns->selection()) == LB_ERR )
	       v = 0;
	    if ( v )
	       dlg_data->latitude.dir = 'S';
	    else
	       dlg_data->latitude.dir = 'N';
	    break;
       case IDC_BDLOEW:
	    if ( ( v = pCbew->selection()) == LB_ERR )
	       v = 0;
	    if ( v )
	       dlg_data->longitude.dir = 'E';
	    else
	       dlg_data->longitude.dir = 'W';
	    break;
       case IDC_BDSC:
	    if ( ( v = pCbsc->selection()) == LB_ERR )
	       v = 0;
	    dlg_data->special_code = v;
	    storeData();
	    updateGMT();
	    setControlsToDefault();
	    break;
       case IDC_BDTZ:
	    if ( ( v = pCbtz->selection()) == LB_ERR )
	       v = 0;
	    dlg_data->time_zone = v;
	    storeData();
	    updateGMT();
	    setControlsToDefault();
	    break;
       default :
	    break;
       }
 return( 1 );
}

int LocationDataDlgf::selchgFull( zEvent *e )
{
 int i;
 zString s;

 switch( e->parm1() ) {
       case IDC_BDCO:
	    if ( ( i = pCbco->selection()) == LB_ERR )
	       s = "";
	    else
	       s = pCbco->text(i);
	    strcpy( dlg_data->country, s );
	    break;
       case IDC_BDST:
	    if ( (i = pCbst->selection()) == LB_ERR )
	       s = "";
	    else
	       s = pCbst->text(i);
	    strcpy( dlg_data->state, s );
	    break;
       case IDC_BDLO:
	    storeData();
	    if ( (i = pCblo->selection()) == LB_ERR )
	       s = "";
	    else
	       s = pCblo->text(i);
	    strcpy( dlg_data->location, s );
	    if ( s.length() ) {
	       if ( !pLocDb->read_loc( strclip(dlg_data->country),
	              strclip(dlg_data->state),
		      strclip(dlg_data->location),
		      dlg_data ) ) {
		  updateGMT();
	          setControlsToDefault();
		  updateCombos(NOLOOKUP);
	          }
               }
            break;
       default :
	    break;
       }

 return( 1 );
}


int LocationDataDlgf::editUpdate( zEvent *e )
{
 int i;
 zString s;

 switch( e->parm1() ) {
       case IDC_BDCO:
	    s = pCbco->zControl::text();
	    strcpy( dlg_data->country, s );
	    break;
       case IDC_BDST:
	    s = pCbst->zControl::text();
	    strcpy( dlg_data->state, s );
	    break;
       case IDC_BDLO:
	    s = pCblo->zControl::text();
	    strcpy( dlg_data->location, s );
	    break;
       default :
	    break;
       }

 return( 1 );
}


int LocationDataDlgf::killFocus( zEvent *e )
{
 int i;
 zString s;

 switch( e->parm1() ) {
       case IDC_BDCO:
	    updateCombos();
	    break;
       case IDC_BDST:
	    updateCombos();
	    break;
       case IDC_BDLO:
	    break;
       default :
	    break;
       }
  return( 1 );
}



void LocationDataDlgf::updateGMT()
{
 if ( dlg_data->time_zone != TZ_OTHER ) {
       dlg_data->hrs_offset =
       tim_vals[dlg_data->time_zone] + spec_vals[dlg_data->special_code];
    dlg_data->min_offset =
       (( dlg_data->time_zone == 16 || dlg_data->time_zone == 18 ) ? 30 : 0 );
    enableField( IDC_BDGH, 0 );
    enableField( IDC_BDGM, 0 );
    }
 else {
    enableField( IDC_BDGH, 1 );
    enableField( IDC_BDGM, 1 );
    }
}

int LocationDataDlgf::locMenuBtnClick( zNotifyEvt *e )
{
 zRect r;

 if ( pMenu == NULL ) {
    getInterior(r);
    zPoint pt = r.topLeft();
    zPoint xp( r.width()/3, r.height()/3);
    pt += xp;
    pMenu = new zPopupMenu(pt, this, zResId("LOCAT"));
    if ( pMenu == NULL )
       return( 1 );
    /*
    pMenu->appendItem(IDM_LDBGET,"Get A Location From Database.",
	MF_STRING|MF_GRAYED|MF_DISABLED );
    pMenu->appendItem(IDM_LDBADD,"Add A New Location To Database.",
	MF_STRING|MF_GRAYED|MF_DISABLED );
    pMenu->appendItem(IDM_LDBREPLACE,"Replace A Location In Database.",
	MF_STRING|MF_GRAYED|MF_DISABLED );
    pMenu->appendItem(IDM_LDBDEL,"Delete A Location From Database.",
	MF_STRING|MF_GRAYED|MF_DISABLED );
    pMenu->appendItem(IDM_LDBGETSV,"Get Saved Location.",
	MF_STRING|MF_GRAYED|MF_DISABLED );
    pMenu->appendItem(IDM_LDBRETURN,"Return.", MF_STRING|MF_ENABLED );
    */
    pMenu->setHilite(this,(NotifyProc)&LocationDataDlgf::menuSelect);
    pMenu->setCommand(this,(NotifyProc)&LocationDataDlgf::locMenuCmd,
       IDM_LDBGET, IDM_LDBRETURN );
    }
 if ( pLocDb->has_Loc() ) {
    pMenu->enableItem(IDM_LDBDEL, TRUE );
    pMenu->enableItem(IDM_LDBREPLACE, TRUE );
    }
 else {
    pMenu->enableItem(IDM_LDBDEL, FALSE );
    pMenu->enableItem(IDM_LDBREPLACE, FALSE );
    pMenu->grayItem(IDM_LDBDEL, TRUE );
    pMenu->grayItem(IDM_LDBREPLACE, TRUE );
    }
 if ( strlen(dlg_data->country) && strlen(dlg_data->state) &&
      strlen(dlg_data->location) ) {
    pMenu->enableItem(IDM_LDBADD, TRUE );
    pMenu->enableItem(IDM_LDBREPLACE, TRUE );
    pMenu->enableItem(IDM_LDBGET, TRUE );
    }
 else {
    pMenu->enableItem(IDM_LDBADD, FALSE );
    pMenu->enableItem(IDM_LDBREPLACE, FALSE );
    pMenu->enableItem(IDM_LDBGET, FALSE );
    pMenu->grayItem(IDM_LDBADD, TRUE );
    pMenu->grayItem(IDM_LDBREPLACE, TRUE );
    pMenu->grayItem(IDM_LDBGET, TRUE );
    }
 pMenu->go();
 return( 1 );
}

int LocationDataDlgf::locMenuCmd( zEvent *e )
{
 switch( e->parm1() ) {
       case IDM_LDBGET :
	    storeData();
	    if ( !pLocDb->read_loc( strclip(dlg_data->country),
		 strclip(dlg_data->state),
		 strclip(dlg_data->location), dlg_data ) ) {
	       updateGMT();
	       updateCombos(NOLOOKUP);
	       setControlsToDefault();
	       }
	    break;
       case IDM_LDBADD :
	    storeData();
	    pLocDb->write_loc( dlg_data );
	    break;
       case IDM_LDBREPLACE:
	    storeData();
	    pLocDb->replace_loc( dlg_data );
	    break;
       case IDM_LDBDEL :
	    pLocDb->delete_loc( strclip(dlg_data->country),
		 strclip(dlg_data->state),
		 strclip(dlg_data->location) );
       case IDM_LDBCLEAR :
	    storeData();
	    memset( dlg_data, 0, sizeof(LOC_DB) );
	    updateGMT();
	    updateCombos();
	    setControlsToDefault();
	    return( 1 );
	    break;
       case IDM_LDBCOPY :
	    if ( !storeData() )
	       break;
	    save_loc = *dlg_data;
	    loc_saved = 1;
	    break;
       case IDM_LDBPASTE :
	    storeData();
	    *dlg_data = save_loc;
	    updateGMT();
	    updateCombos();
	    setControlsToDefault();
	    break;
       case IDM_LDBRETURN:
       default:
	    break;
       }
 delete pMenu;
 pMenu = NULL;
 return( 1 );
}

int LocationDataDlgf::menuSelect(zEvent *e)
{
 zMenuHiliteEvt *ev = (zMenuHiliteEvt *)e;

 wCurrentMenuCmd = ev->id();
 dwCurrentMenuBits = ev->flags();
 return( 1 );
}

int LocationDataDlgf::doMessage( char *title, char *string )
{
 zMessage *mp = new zMessage( this, string, title );
 delete mp;
 return( 1 );
}

RelocationDataDlg::RelocationDataDlg( zWindow *pWnd, LOC_DB *pL )
{
  pLoc = pL;
  save = *pL;

  pLdDf = new LocationDataDlgf( pWnd, &save );
  pLdDf->run();
  if ( pLdDf->completed() )
     *pLoc = save;
 }
