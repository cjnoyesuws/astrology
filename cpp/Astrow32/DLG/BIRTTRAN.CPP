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
#include "birttrans.hpp"
#include "datetime.fns"
#include "output.fns"
#include "errors.fns"
#undef memcpy(s,d,n)
#include <string.h>
#include <dos.h>
#include "basedcs.h"
#include "charcons.h"
#include "resstr.hpp"


extern char *strclip( char *pStr );

// Classes to get Birth and Transits Data.
// Useage:
//
//   LOC_DB lData;
//   BIRTH_DB bData;
//   RECT_DATA rData;
//
//   BirthTransDataDlgf *ld = new BirthTransDataDlgf( out, &bData, &lData, &rData);
//   if ( ld->completed() ) {
//      out->printf( "Name = %s\n", bData.name );
//      out->printf( "Date = %02d-%02d-%04d\n",
//         bData.birth_data.birth_date.month,
//         bData.birth_data.birth_date.day,
//         bData.birth_data.birth_date.year );
//      out->printf( "Time = %2d:%2d %s\n",
//         bData.birth_data.birth_time.hours,
//         bData.birth_data.birth_time.minutes, am[bData.am_pm] );
//      out->printf( "Country = %s\n", bData.country );
//      out->printf( "State = %s\n", bData.state );
//      out->printf( "Location = %s\n", bData.location );
//      out->printf( "%03d %c %02d\n",
//         bData.birth_data.longitude.degrees,
//         bData.birth_data.longitude.dir,
//         bData.birth_data.longitude.minutes );
//      out->printf( " %02d %c %02d\n",
//         bData.birth_data.latitude.degrees,
//         bData.birth_data.latitude.dir,
//         bData.birth_data.latitude.minutes );
//      out->printf( "tz = %d %s\n", bData.time_zone,
//         timezones[bData.time_zone] );
//      out->printf( "sc = %d %s\n", bData.special_code,
//         speccodes[bData.special_code] );
//      out->printf( "gmt = %d:%d\n",
//         bData.birth_data.local_adjust, bData.birth_data.local_minutes );
//      }
//     delete ld;
//
//     higher level interface
//
//     TransitsInfoDlg *tid = new TransitsInfoDlg( pWnd, &bData );
//     delete tid;
//


static char *am[] = { "AM", "PM" };

BirthTransDataDlgf::BirthTransDataDlgf(zWindow *pPar,
    BIRTH_DB *pB, LOC_DB *pL, RECT_DATA *pR, char *dlg) :
	 LocationDataDlgf(pPar,birth2Loc(pB,pL), dlg)
{
 long lrec;
 int r;
 dlg_birth = pB;
 dlg_rect = pR;

 pCbam = new zAstComboBoxStatic(this, IDC_BDAM );
// for ( int i = 0; i < 2; i++ )
//     pCbam->add( zString(am[i]) );
 pCbam->addResStrings(SB_AMPM);
 pCbam->setNotifySelChange(this,
	(NotifyProc)&BirthTransDataDlgf::selchgStatic);
 preAdjustTime();
 pCbam->selection(dlg_birth->am_pm);

 pBirthDb = new BirthDatabase();
 if ( pBirthDb != NULL )
    pBirthDb->startup();

 pCbnm = new zAstComboBoxFull(this, IDC_BDNM );
 pCbnm->loadList( BIRTHBAS_POPUP, 0 );
 if ( strlen( dlg_birth->name ) ) {
    r = pCbnm->selection(zString(strclip(dlg_birth->name)));
    if ( r == LB_ERR )
       pCbnm->zControl::text(zString(dlg_birth->name));
    }
 pCbnm->setNotifySelChange(this,
	(NotifyProc)&BirthTransDataDlgf::selchgFull);
 pCbnm->setNotifyEditUpdate(this,
	(NotifyProc)&BirthTransDataDlgf::editUpdate);
 /*
 pCbnm->setNotifyKillFocus(this,
	(NotifyProc)&BirthTransDataDlgf::killFocus);
 */
 new zNumFieldRng( this, IDC_BDMO,
	  (int *)&dlg_birth->birth_data.birth_date.month,
	  12, 1);
 new zNumFieldRng( this, IDC_BDDAY,
	  (int *)&dlg_birth->birth_data.birth_date.day,
	  31, 1);
 new zNumFieldRng( this, IDC_BDYR,
	  (int *)&dlg_birth->birth_data.birth_date.year,
	  2300, -4200);

 new zNumFieldRng( this, IDC_BDHR,
	  (int *)&dlg_birth->birth_data.birth_time.hours,
	  12, 0);
 new zNumFieldRng( this, IDC_BDMIN,
	  (int *)&dlg_birth->birth_data.birth_time.minutes,
	  59, 0);
 zDefPushButton *b = new zDefPushButton(this, IDOK);
 b->setNotifyClicked(this,(NotifyProc)&BirthTransDataDlgf::doOk);
 updateCombos(BRTTRNONLY);
 setId(HELPID_DLG_TRINFO);
}


int BirthTransDataDlgf::command( zCommandEvt *e )
{
 switch( e->cmd() ) {
       default:
	    return( 0 );
	    break;
       }
}

void BirthTransDataDlgf::updateCombos(int nCode)
{
 int r;

 pCbam->selection(dlg_birth->am_pm);
 if ( strlen( dlg_birth->name ) ) {
    r = pCbnm->selection(zString(strclip(dlg_birth->name)));
    if ( r == LB_ERR )
       pCbnm->zControl::text(zString(dlg_birth->name));
    }
 else
    pCbnm->zControl::text(zString(""));
 if ( nCode != BRTTRNONLY )
    LocationDataDlgf::updateCombos(nCode);
}


BirthTransDataDlgf::~BirthTransDataDlgf()
{
  if ( pBirthDb != NULL ) {
     pBirthDb->shutdown();
     delete pBirthDb;
     }
}

int BirthTransDataDlgf::selchgStatic( zEvent *e )
{
 int v;

 switch( e->parm1() ) {
       case IDC_BDAM:
	    if ( ( v = pCbam->selection()) == LB_ERR )
	       v = 0;
	    if ( v )
	       dlg_birth->am_pm = 1;
	    else
	       dlg_birth->am_pm = 0;
	    break;
       default :
	    break;
       }
 return( 1 );
}

int BirthTransDataDlgf::selchgFull( zEvent *e )
{
 int i;
 zString s;

 switch( e->parm1() ) {
       case IDC_BDNM:
	    storeData();
	    if ( (i = pCbnm->selection()) == LB_ERR )
	       s = "";
	    else
	       s = pCbnm->text(i);
	    strcpy( dlg_birth->name, s );
	    if ( s.length() ) {
	       dlg_rect->birth_time_known = 1;
	       if ( !pBirthDb->read_birth( strclip(dlg_birth->name), dlg_birth, dlg_rect ) ) {
		  preAdjustTime();
		  birth2Loc(dlg_birth,dlg_data);
		  updateGMT();
		  setControlsToDefault();
		  updateCombos();
		  }
	       }
	    break;
       default :
	    break;
       }

 return( 1 );
}


int BirthTransDataDlgf::editUpdate( zEvent *e )
{
 int i;
 zString s;

 switch( e->parm1() ) {
       case IDC_BDNM:
	    s = pCbnm->zControl::text();
	    strcpy( dlg_birth->name, s );
	    break;
       default :
	    break;
       }

 return( 1 );
}


int BirthTransDataDlgf::killFocus( zEvent *e )
{
 int i;
 zString s;

 switch( e->parm1() ) {
       case IDC_BDNM:

	    break;
       default :
	    break;
       }

 return( 1 );
}

void BirthTransDataDlgf::mergeLoc2Birth()
{
 strcpy( dlg_birth->country, dlg_data->country );
 strcpy( dlg_birth->state, dlg_data->state );
 strcpy(dlg_birth->location, dlg_data->location  );
 memcpy( &dlg_birth->birth_data.longitude, &dlg_data->longitude, sizeof(DEG_MIN) );
 memcpy( &dlg_birth->birth_data.latitude, &dlg_data->latitude, sizeof(DEG_MIN) );
 dlg_birth->time_zone = dlg_data->time_zone;
 dlg_birth->special_code = dlg_data->special_code;
 dlg_birth->birth_data.local_adjust = dlg_data->hrs_offset;
 dlg_birth->birth_data.local_minutes = dlg_data->min_offset;
}

void BirthTransDataDlgf::adjustTime()
{
 if ( dlg_birth->am_pm && dlg_birth->birth_data.birth_time.hours != 12 )
    dlg_birth->birth_data.birth_time.hours += 12;
 else if ( !dlg_birth->am_pm &&
	  dlg_birth->birth_data.birth_time.hours == 12 )
    dlg_birth->birth_data.birth_time.hours = 0;
}


void BirthTransDataDlgf::preAdjustTime()
{
 struct dosdate_t date;

 if ( !dlg_birth->am_pm ) {
    if ( dlg_birth->birth_data.birth_time.hours == 12 )
       dlg_birth->am_pm = 1;
    else if ( dlg_birth->birth_data.birth_time.hours == 0 )
       dlg_birth->birth_data.birth_time.hours = 12;
    else {
       if ( dlg_birth->birth_data.birth_time.hours > 12 ) {
       dlg_birth->am_pm = 1;
       dlg_birth->birth_data.birth_time.hours -= 12;
       }
      }
    }
 else {
    if ( dlg_birth->birth_data.birth_time.hours == 0 ) {
       dlg_birth->birth_data.birth_time.hours = 12;
       dlg_birth->am_pm = 0;
       }
    else if ( dlg_birth->birth_data.birth_time.hours > 12 ) {
       dlg_birth->birth_data.birth_time.hours -= 12;
       }
    }
 /* first startup of session load today's date into the structure so
    we can exit legally without entering data if cursor in one of date
    fields */
 if ( dlg_birth->birth_data.birth_date.month == 0 &&
		    dlg_birth->birth_data.birth_date.day == 0 ) {
    _dos_getdate( &date );
    dlg_birth->birth_data.birth_date.day = date.day;
    dlg_birth->birth_data.birth_date.month = date.month;
    dlg_birth->birth_data.birth_date.year = date.year;
    }
 pCbam->selection(dlg_birth->am_pm);
}

LOC_DB *BirthTransDataDlgf::birth2Loc(BIRTH_DB *pBirth, LOC_DB *pLoc)
{
 strcpy( pLoc->country, pBirth->country );
 strcpy( pLoc->state, pBirth->state );
 strcpy( pLoc->location, pBirth->location );
 memcpy( &pLoc->longitude, &pBirth->birth_data.longitude, sizeof(DEG_MIN) );
 memcpy( &pLoc->latitude, &pBirth->birth_data.latitude, sizeof(DEG_MIN) );
 pLoc->time_zone = pBirth->time_zone;
 pLoc->special_code = pBirth->special_code;
 pLoc->hrs_offset = pBirth->birth_data.local_adjust;
 pLoc->min_offset = pBirth->birth_data.local_minutes;
 return( pLoc );
}

int BirthTransDataDlgf::doOk(zEvent *e)
{
 int id = 0;

 if ( !storeData() )
    return( 1 );
  if ( ( id = checkDate() ) ) {
     (get(id))->setFocus();
     return( 1 );
     }
  else {
     endOk(e);
     mergeLoc2Birth();
     adjustTime();
     }
 return( 1 );
}

int BirthTransDataDlgf::checkDate()
{
 /*static char BCS nwp[] = { "WAR TIME May Not Apply For This Date--Please Check!" };
 static char BCS wts[] = { "WAR TIME May Apply For This Date--Please Check!" };
 static char BCS dws[] = { "DAYLIGHT SAVINGS TIME May Be In "
	 "Effect For This Date--Please Check!" };
 static char BCS ndws[] = { "DAYLIGHT SAVINGS TIME May Not Be In "
	 "Effect For This Date--Please Check!" };

 static char BCS nvd[] = { "This Is Not a Valid Date! Try %s." };*/
  static char BCS us[] = {"USA"}, BCS can[] = {"Canada"};
  char buf[150];
  int err, d;
  DATES dx;

 if ( bad_date( &dlg_birth->birth_data.birth_date ) ) {
    if ( dlg_birth->birth_data.birth_date.month == 2 )
       err = 28;
    else
       err = dlg_birth->birth_data.birth_date.day -1;
    memcpy( &dx, &dlg_birth->birth_data.birth_date, sizeof( DATES ) );
    dx.day = err;
    sprintf( buf, CResStr(_INVALIDDATE)/*nvd*/, make_date( &dx ) );
    doMessage( ERROR2, buf );
    return( IDC_BDDAY );
    }
 if (( dlg_birth->birth_data.birth_date.year < 1918
	 || dlg_birth->birth_data.birth_date.year > 1946 ) ||
	 ( dlg_birth->birth_data.birth_date.year > 1919
	 && dlg_birth->birth_data.birth_date.year < 1942 ) ||
	   ( strcmpi( us, dlg_birth->country ) &&
	   strcmpi( can, dlg_birth->country ) ) ) {
    if ( dlg_birth->special_code == 1 ) {
       doMessage( warn1, CResStr(_NOSETWARTIME)/*nwp*/ );
       return(0);
       }
    }
 else {
    d = ( dlg_birth->birth_data.birth_date.month * 100 )
	  + dlg_birth->birth_data.birth_date.day;
    if ( ( dlg_birth->birth_data.birth_date.year == 1918
       || dlg_birth->birth_data.birth_date.year == 1919
       || dlg_birth->birth_data.birth_date.year == 1943
       || dlg_birth->birth_data.birth_date.year == 1944 )
       || ( dlg_birth->birth_data.birth_date.year == 1942 && d >= 209 )
       || ( dlg_birth->birth_data.birth_date.year == 1945 && d <= 930 ) ) {
       if ( dlg_birth->special_code != 1 ) {
	  doMessage( warn1, CResStr(_SETWARTIME) /*wts*/ );
	  return(0);
	  }
       }
    }
 if ( dlg_birth->special_code == 1 ) {
    doMessage( warn1, CResStr(_NOSETWARTIME)/* nwp*/ );
    return(0);
    }
 if ( dlg_birth->special_code > 1 )
    return(0);
 if ( dlg_birth->birth_data.birth_date.year < 1946 || ( strcmpi( us,
      dlg_birth->country ) && strcmpi( can, dlg_birth->country ) ) )
    return(0);
 if ( dlg_birth->birth_data.birth_date.month >= 4 &&
	 dlg_birth->birth_data.birth_date.month <= 10 )
    doMessage( warn1, CResStr(_SETDAYLIGHTT) /*dws*/ );
 return(0);
}


TransitsInfoDlg::TransitsInfoDlg(zWindow *pWnd, BIRTH_DB *pB)
{
 save = *pB;

 pBtd = new BirthTransDataDlgf( pWnd, &save, &loc, &rect);
 pBtd->run();
 if ( pBtd->completed() )
    *pB = save;
 }
