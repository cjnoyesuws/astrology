// ZipCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "astro.h"
#include "useri.h"
#include "ZipCodeDlg.h"
#include "zip_code_latlong.h"
#include "errors.fns"
#include "math.h"
#include "dlocationset.h"
// ZipCodeDlg dialog

IMPLEMENT_DYNAMIC(ZipCodeDlg, CDialog)
ZipCodeDlg::ZipCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ZipCodeDlg::IDD, pParent)
	, m_zip_code(_T(""))
{
}

ZipCodeDlg::~ZipCodeDlg()
{
}

void ZipCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZIPCODE, m_zip_code);
}


BEGIN_MESSAGE_MAP(ZipCodeDlg, CDialog)
END_MESSAGE_MAP()


// ZipCodeDlg message handlers

void ZipCodeDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	m_zip_code = "00000" + m_zip_code;
	m_zip_code = m_zip_code.Right(5);
    Czip_code_latlong latlongset;
	char buf[200];
    sprintf(buf,"select * from zip_code_latlong where zip_code='%s'", (LPCSTR)m_zip_code);
	try {
	   latlongset.Open(-1,buf);
	   if ( latlongset.IsBOF() )
          alert_box("Not Found", "Zip Code Was Not Found" );
	   else {
		   toDegMin(latlongset.m_latitude, m_loc_db_rec->latitude, TRUE);
           toDegMin(latlongset.m_longitude, m_loc_db_rec->longitude, TRUE);
	   }
	   latlongset.Close();
	   CDLocationset locset;
	   sprintf(buf,"select * from locations where longitude like '%dW%d?' and latitude like '%02dN%d?'",
		   m_loc_db_rec->longitude.degrees, m_loc_db_rec->longitude.minutes/10, m_loc_db_rec->latitude.degrees, m_loc_db_rec->latitude.minutes/10);
       locset.Open(-1,buf);
	   if ( !locset.IsBOF() ) {
		   strcpy(m_loc_db_rec->country, "United States");
		   m_loc_db_rec->time_zone = locset.m_timezone;
		   m_loc_db_rec->special_code = 0;
		   m_loc_db_rec->hrs_offset = locset.m_houroff;
		   m_loc_db_rec->min_offset = 0;
	   } else {
		  locset.Close();
		  sprintf(buf,"select * from locations where longitude like '%dW*' and latitude like '%02dN*'",
			   m_loc_db_rec->longitude.degrees, m_loc_db_rec->latitude.degrees);
	      locset.Open(-1,buf);
	      if ( !locset.IsBOF() ) {
		   strcpy(m_loc_db_rec->country, "United States");
		   m_loc_db_rec->time_zone = locset.m_timezone;
		   m_loc_db_rec->special_code = 0;
		   m_loc_db_rec->hrs_offset = locset.m_houroff;
		   m_loc_db_rec->min_offset = 0;
	      }
	   }
	   locset.Close();
	}
	catch( CDaoException *e )
	{
	  char errbuf[500];
	  e->GetErrorMessage(errbuf,499);    
	  alert_box("Error", errbuf );
	}
	CDialog::OnOK();
}

void ZipCodeDlg::toDegMin( CString &str, DEG_MIN &deg, BOOL bLat)
{
 double ddeg = atof((LPCSTR)str);
 ddeg = fabs(ddeg);
 if ( bLat )
	 deg.dir = 'N';
 else
	 deg.dir = 'W';
 deg.degrees = (int) floor(ddeg);
 ddeg -= (double)deg.degrees;
 ddeg *= 60;
 deg.minutes = (int)ddeg;
}