// ImportLocations.cpp: implementation of the CImportLocations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "importtool.h"
#include "importerdata.h"
#include "importtooldlg.h"
#include "ImportLocations.h"
#include "errors.fns"
#include "uicvt.fns"
#include <stdlib.h>
#include <share.h>
#include "freesp.hpp"
#include "charcons.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CString &quote( char *pChar, CString & str );
extern CString &fmtLongLat( DEG_MIN &rec, CString &str );

CImportLocations::CImportLocations()
{

}

CImportLocations::~CImportLocations()
{
 theSet.Close();
}

void CImportLocations::process()
{
 FILE * stream;
 char buf[200];
 int flen;
 short len=0, offset, x=0, size = sizeof(D_LOC_DB);
 int addupd;
 strcpy( buf, (const char * )mDir );
 if ( buf[strlen(buf)-1] != '\\' )
	 strcat( buf, "\\" );
 strcat(buf,"nlocatin.dat");
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
 fseek( stream, 0, SEEK_END);
 flen = ftell(stream);
 flen -= (sizeof(short) + (20 * sizeof( FREE_SP )));
 flen /= sizeof(D_LOC_DB);
 m_pImporterData->m_progress->m_records.SetRange(0,flen);
 m_pImporterData->m_progress->m_records.SetStep(1);
 fseek( stream,  sizeof(short) + (20 * sizeof( FREE_SP )), SEEK_SET );
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
     if (( fread( ((char *)&locbuffer)+2, len-2, 1, stream ) != 1) && !feof( stream ) ) {
	    do_error( buf );
	    break;
	    }
     locbuffer.len = len;
     if ( locbuffer.freer == 1 )
	    continue;
     if ( !feof( stream ) ) {
        cvt_dsk_2_nlocdb( &loc, &locbuffer );
        addupd = checkRow();
        doDbRow(addupd);
		}
	 m_pImporterData->m_progress->m_records.StepIt();
     }
 fclose( stream );
 theSet.Close();
}

int CImportLocations::checkRow()
{
 char msgbuf[125];
 char sqlbuf[500];
 char erbuf[500];
 CString co, st, lo;
 sprintf( msgbuf, "Importing %s, %s, %s", loc.country, loc.state, loc.location );
 strcpy(pBuf,(const char *)msgbuf);
 sprintf( sqlbuf,"select * from locations where country=%s and location=%s and state=%s", (const char *)quote(loc.country,co), (const char *)quote(loc.location,lo), (const char *)quote(loc.state,st) ); 	
 
 try {
	if ( theSet.IsOpen() )
		theSet.Close();
	theSet.Open( -1, sqlbuf );
	if ( !theSet.IsOpen() || theSet.IsBOF() )
		return( 1 );
	else
		return( 0 );
 } catch ( CDaoException *e ) {
    e->GetErrorMessage(erbuf,499);
    alert_box("Error", erbuf );
	return(1);
 }

}

int CImportLocations::doDbRow( int bAdd) 
{
	char erbuf[500];
	try {
	   if ( bAdd ) {
	     theSet.AddNew();
	   }
	   else {
	     theSet.Edit();
	   }
       theSet.m_location = loc.location;
	   theSet.m_state = loc.state;
	   theSet.m_country = loc.country;
	   theSet.m_timezone = loc.time_zone;
	   theSet.m_specialcode = loc.special_code;
       theSet.m_longitude = fmtLongLat(loc.longitude, theSet.m_longitude );
	   theSet.m_latitude = fmtLongLat(loc.latitude,theSet.m_latitude );
       theSet.m_houroff = loc.hrs_offset;
	   theSet.m_minoff = loc.min_offset;
       theSet.Update();
	}
	catch ( CDaoException * e ) {
	    e->GetErrorMessage(erbuf,499);
		alert_box("Error", erbuf  );
	}
    return( 1 );
}
