// ImportBirths.cpp: implementation of the CImportBirths class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "importtool.h"
#include "importerdata.h"
#include "importtooldlg.h"
#include "ImportBirths.h"
#include "errors.fns"
#include "uicvt.fns"
#include <share.h>
#include <stdlib.h>
#include "freesp.hpp"
#include "charcons.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString &quote( char *pChar, CString & str );
extern CString &fmtLongLat( DEG_MIN &rec, CString &str );
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImportBirths::CImportBirths()
{

}

CImportBirths::~CImportBirths()
{
 if ( rectset.IsOpen() )
	 rectset.Close();
 if ( birthset.IsOpen() )
	 birthset.Close();
}

void CImportBirths::process()
{
 FILE * stream;
 char buf[200];
 int flen, headlen;
 short len=0, offset, size = sizeof(D_RBIRTH_DB), x=0;
 int addupd, addupdrel;
 strcpy( buf, (const char * )mDir );
 if ( buf[strlen(buf)-1] != '\\' )
	 strcat( buf, "\\" );
 strcat(buf,"nbirthbs.dat");
 if ( ( stream = _fsopen( buf, "rb", SH_DENYWR ) ) == NULL ) {
    do_error( buf );
    return;
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	      setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 fseek( stream,  sizeof(short) + (20 * sizeof( FREE_SP )), SEEK_SET );
 headlen = ftell(stream);
 fseek(stream, 0, SEEK_END);
 flen = ftell(stream);
 fseek( stream,  sizeof(short) + (20 * sizeof( FREE_SP )), SEEK_SET );
 flen -= headlen;
 flen/= size;
 m_pImporterData->m_progress->m_records.SetRange(0,flen);
 m_pImporterData->m_progress->m_records.SetStep(1);
 for ( offset = sizeof(short) + (20 * sizeof( FREE_SP ));
	   !feof( stream ) && !ferror( stream );
	                         offset += len, ++x ) {
     if (( fread( &len, 2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( buf );
        break;
	    }
     if ( len < sizeof(D_LOC_DB)-L_WIDTH || len > size ) {
	    alert_box( ERROR2, "Possible Corrupted Data File len = %d, offset = %lx", len, offset );
	    break;
	    }
     if (( fread( ((char *)&birthrec)+2, len-2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( buf );
	    break;
	    }
     birthrec.len = len;
     if ( birthrec.freer == 1 )
	    continue;
     if ( !feof( stream ) ) {
        cvt_dsk_2_nbirthdb( &birthdata, (DBR*) &birthrec, &rect );
        addupd = checkRow();
		addupdrel = checkRow(1);
        doDbRow(addupd, addupdrel);
		m_pImporterData->m_progress->m_records.StepIt();
		}
     }
 fclose( stream );
 if (birthset.IsOpen() )
	 birthset.Close();
 if (rectset.IsOpen() )
    rectset.Close();
}

int CImportBirths::checkRow(int which)
{
char msgbuf[100];
char sqlbuf[500];
char erbuf[500];
 CString n;
 sprintf( msgbuf, "Importing %s", birthdata.name );
 strcpy(pBuf,(const char *)msgbuf);
 if ( !which ) {
	sprintf( sqlbuf,"select * from births where name=%s", quote(birthdata.name,n) ); 	
    try {
      if ( birthset.IsOpen() )
	     birthset.Close();
	   birthset.Open( -1, sqlbuf );
	   if ( !birthset.IsOpen() || birthset.IsBOF() || birthset.IsEOF() )
	    	return( 1 );
	   else
	    	return( 0 );
	} catch ( CDaoException *e ) {
      e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	}
 }
 else {
	    sprintf( sqlbuf,"select * from rectification where name=%s", (const char *)quote(birthdata.name,n) ); 	
    try {
      if ( rectset.IsOpen() )
	     rectset.Close();
	   rectset.Open( -1, sqlbuf );
	   if ( !rectset.IsOpen() || rectset.IsBOF() || rectset.IsEOF() )
	    	return( 1 );
	   else
	    	return( 0 );
	} catch ( CDaoException *e ) {
      e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	}
 }
	  return(1);


}

int CImportBirths::doDbRow( int bAdd, int bAddrel ) 
{
	char erbuf[500];
    COleDateTime birthdt = COleDateTime( birthdata.birth_data.birth_date.year, birthdata.birth_data.birth_date.month,
		birthdata.birth_data.birth_date.day, 0, 0, 0 );
	try {
	   if ( bAdd ) 
	     birthset.AddNew();
	   else {
	     birthset.Edit();
	   }
	   if ( bAddrel ) {
	     if ( birthrec.with_rect==1 ) 
			rectset.AddNew();
		 }
	   else if ( birthrec.with_rect==1 )
		   rectset.Edit();
	   if ( birthrec.with_rect==1 ) {
	      rectset.m_name = birthdata.name;
		  rectset.m_birthdate = birthdt;
		  rectset.m_am_pm = rect.am_pm;
		  rectset.m_angle = rect.angle;
		  rectset.m_birth_time_known = rect.birth_time_known;
		  rectset.m_hours = rect.trial.hours;
		  rectset.m_minutes = rect.trial.minutes;
		  rectset.m_rect_system = rect.rect_system;
		  rectset.m_sign = rect.sign;
		  rectset.m_totalminutes = rect.total_minutes;
		  rect.degree.dir='D';
		  rectset.m_degree=fmtLongLat(rect.degree,rectset.m_degree);

	   }
       birthset.m_name = birthdata.name;
	   birthset.m_country = birthdata.country;
	   birthset.m_state = birthdata.state;
	   birthset.m_location = birthdata.location;
	   birthset.m_sex = birthdata.sex;
	   birthset.m_rect = (birthrec.with_rect==1?TRUE:FALSE);
	   birthset.m_birthdate = birthdt;
	   birthset.m_AMPM = (birthdata.am_pm==1?TRUE:FALSE);
	   birthset.m_longitude = fmtLongLat(birthdata.birth_data.longitude, birthset.m_longitude);
	   birthset.m_latitude = fmtLongLat(birthdata.birth_data.latitude,birthset.m_latitude);
	   birthset.m_hours = birthdata.birth_data.birth_time.hours;
	   birthset.m_minutes = birthdata.birth_data.birth_time.minutes;
	   birthset.m_timezone = birthdata.time_zone;
	   birthset.m_specialcode = birthdata.special_code;
	   birthset.m_houroff = birthdata.birth_data.local_adjust;
	   birthset.m_minoff = birthdata.birth_data.local_minutes;
	   birthset.Update();
	   if ( birthrec.with_rect == 1 ) {
		   rectset.Update();
	       rectset.Close();
	   }
	}
	catch ( CDaoException * e ) {
	  e->GetErrorMessage(erbuf, 499);
	  alert_box("Error", erbuf );
	}
   return( 0 );
}

