// AstInstCalc2.cpp : Implementation of CAstInstCalc

#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "julian.h"
#include "AstInstCalc2.h"
#include <atlcomcli.h>

short house_cusps[13];

extern void do_calc( DATES &birth, TIM &btime, DEG_MIN &longitude, DEG_MIN &latitude, int gmt_hrs, int gmt_min, short *mins );

CAstInstCalc::CAstInstCalc()
{
  //GetSystemTime(&curr);
  gmt_hours = -1;
  memset(txtbuf, 0, 20*sizeof(char *));
  //StartAt( curr.wMonth, curr.wDay, curr.wYear, (curr.wHour*24)+curr.wMinute );

}


// CAstInstCalc

char *format_degs( MINU min, char *buf )
{
 static char *signs[12] = { "ARI", "TAU", "GEM", "CAN", "LEO", "VIR",
	 "LIB", "SCO", "SAG", "CAP", "AQU", "PIS" };
 const char *p;
 char retr = ' ';
 if ( min < 0 )
	 retr = 'R';
 min = abs(min);
 sprintf( buf, "%-2.2d%3s%-2.2d%C", minor_degrees( min ), signs[ sign(min) ],
	  minor_minutes( min ), retr );
 return( buf );
}

STDMETHODIMP CAstInstCalc::get_Value(VARIANT* pVal)
{
	// TODO: Add your implementation code here
    int n = index;
    CComBSTR bstr(8,txtbuf[n]);
	CComVariant var((BSTR)bstr);
	*pVal = (VARIANT)var;
	return S_OK;
}

STDMETHODIMP CAstInstCalc::put_Index(LONG newVal)
{
	// TODO: Add your implementation code here
    index = newVal;
	return S_OK;
}

void parsedgm(char *buf, DEG_MIN &dgm ) {
  int pos;
  dgm.degrees = atoi(buf);
  if ( dgm.degrees > 99 )
     pos = 3;
  else if ( dgm.degrees > 9 )
     pos = 2;
  else 
	 pos = 2;
  dgm.dir = buf[pos++];
  dgm.minutes = atoi(&buf[pos]);
}

void parsetim(char *buf, int &hrs, int &mins ) {
	int pos;
	hrs = atoi(buf);
	if ( hrs > 9 )
       pos = 3;
	else if ( hrs < -9 )
	   pos = 4;
	else if ( hrs < 0 )
	   pos = 3;
	else
	   pos = 2;
	mins = atoi(&buf[pos]);
}



STDMETHODIMP CAstInstCalc::StartAt(LONG month, LONG day, LONG year, LONG hour)
{
	// TODO: Add your implementation code here
    DATES dt; 
    ULONG len;
    char degval[4], minval[4], dirval[3]; 
	if ( gmt_hours == -1 ) {
	  CRegKey key;
	  if ( key.Open(HKEY_CURRENT_USER,"Software\\Christopher J. Noyes Software\\InstCalc" )
		    != ERROR_SUCCESS ) { 
         strcpy( longbuf, "74W00" );	  
		 strcpy( latbuf, "45N00" ); 
		 strcpy( gmtbuf, "5:00" ); 
		}
	  else {
	     len = 15;
		 key.QueryStringValue("Longitude",longbuf, &len );
	     longbuf[len] = '\0';
	     if ( !strlen(longbuf ) )
		     strcpy( longbuf, "74W00" ); 
	     len =15;
		 key.QueryStringValue("Latitude",latbuf, &len );
	     latbuf[len] = '\0';
	     if ( !strlen(latbuf) )
		    strcpy( latbuf, "45N00" ); 
	     len = 10;
		 key.QueryStringValue("GmtOffset",gmtbuf, &len );
	     gmtbuf[len] = '\0';
	     if ( !len )
		     strcpy( gmtbuf, "5:00" );
		 else if ( len==2)
			 strcat(gmtbuf,":00");
		 key.Close();
	  }
	  memset(&longitude,0,sizeof(DEG_MIN));
	  memset(&latitude,0,sizeof(DEG_MIN));
	  gmt_hours = 0;
	  gmt_min = 0;
	  parsedgm(longbuf,longitude);
	  parsedgm(latbuf,latitude);
	  parsetim(gmtbuf, gmt_hours, gmt_min);

	}
	the_date.day = day;
	the_date.month = month;
	the_date.year = year;
    the_time.hours = hour / 60;
	the_time.minutes = hour % 60;
	the_time.seconds = 0;
	memset(&minutes,0,sizeof(TIM));
	do_calc( the_date, the_time, longitude, latitude, gmt_hours, gmt_min, minutes );
	for ( int i = 0; i <= PART_FORTU; i++ ) {
	    if ( txtbuf[i] == NULL )
			txtbuf[i] = new char[20];
		memset(txtbuf[i],0,20);
		format_degs(minutes[i],txtbuf[i]);
	}
	return S_OK;
}
