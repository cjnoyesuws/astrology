/* database functions used for locbase and for astro for
   location and birthbas handling procedures */
#include "stdafx.h"
#include <afxdisp.h>
#include "databaseodbc.hpp"
//#include "uicvt.fns"
#include "errors.fns"
#include "direc.hpp"

int DaoDatabase::doExecDelete( char *p )
{
 char erbuf[500];
 try {
	 theDirectories.m_pDatabase->Execute(p, dbSQLPassThrough);
	}
 catch ( CDaoException *e ) {
	e->GetErrorMessage(erbuf,499);    
	alert_box("Error", erbuf );
	}
 return( 1 );	

}

CString &DaoDatabase::fmtLongLat( DEG_MIN &rec, CString &str )
{
 char buf[15];
 sprintf( buf, "%02d%c%02d", rec.degrees, rec.dir, rec.minutes );
 str = buf;
 return ( str );

}

 CString &DaoDatabase::quote( const char *pChar, CString & str )
{
 char buf[100], *d;
 const char *p;
 buf[0] = '\'';
 for ( p=pChar, d=buf+1; *p!='\0'; p++ ) {
     if ( *p == '\'' ) {
	    *d++= '\'';
		*d++=*p;
		}
     else 
		 *d++=*p;
	}
  *d++='\'';
  *d++='\0';
  str=buf;
  return( str );
 }

void DaoDatabase::parseLongLat( CString &str, DEG_MIN &dat )
{
 char degb[6];
 char dirb[3];
 sscanf((const char *)str,"%[^A-Za-z]%[NSEW]%d", degb, dirb, &dat.minutes );
 dat.degrees = atoi(degb);
 dat.dir=dirb[0];
}

void DaoDatabase::extractDate( COleDateTime &date, DATES &dt )
{
 dt.day = date.GetDay();
 dt.month = date.GetMonth();
 dt.year = date.GetYear();
}

int DaoDatabase::find()
{
  if ( checkRec() )
	  return( 0 );
  transfer();
  return( 1 );
}


int DaoDatabase::dosave()
{
	char erbuf[500];

	try {
		if ( checkRec() ) {
		  if ( !pSet->IsOpen() )
			  pSet->Open();
		  else {
		      pSet->Close();
			  pSet->Open();
		  }
		   pSet->AddNew();
		}
	  else
		  pSet->Edit();
      transfer(1);
      pSet->Update();
	} catch ( CDaoException * e ) {
	  e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	  return( 0 );
	}
 return( 1 );
}


/* class DaoLocDatabase : public DaoDatabase {
protected:
public:
      LOC_DB loc;
	  CLocationSet locset;
	  DaoLocDatabase()  : DaoDatabase() {}
      ~DaoLocDatabase() {}*/
int DaoLocDatabase::checkRec( int wh )
{
 char sqlbuf[500];
 char erbuf[500];
 CString co, st, lo;
 sprintf( sqlbuf,"select * from locations where country=%s and location=%s and state=%s", (const char *)quote(loc.country,co), (const char *)quote(loc.location,lo), (const char *)quote(loc.state,st) ); 	
 
 try {
	if ( locset.IsOpen() )
		locset.Close();
	locset.Open( dbOpenDynaset, sqlbuf );
	if ( !locset.IsOpen() || locset.IsBOF() )
		return( 1 );
	else
		return( 0 );
 } catch ( CDaoException *e ) {
    e->GetErrorMessage(erbuf,499);
    alert_box("Error", erbuf );
	return(1);
 }
}


int DaoLocDatabase::dodelete()
{
 char buf[250];
 CString co, st, lo;
 sprintf( buf, "delete from locations where country=%s and state=%s and location=%s",
	 (const char *)quote(loc.country, co), (const char *)quote(loc.state, st), (const char *)quote(loc.location, lo));
 return ( doExecDelete( buf ) );
}


int DaoLocDatabase::transfer( int save )
{

	if ( save ) {
		locset.m_country=loc.country;
		locset.m_location=loc.location;
		locset.m_state=loc.state;
		locset.m_houroff=loc.hrs_offset;
		locset.m_minoff=loc.min_offset;
		locset.m_specialcode=loc.special_code;
		locset.m_timezone=loc.time_zone;
		locset.m_latitude=fmtLongLat(loc.latitude, locset.m_latitude);
		locset.m_longitude=fmtLongLat(loc.longitude, locset.m_longitude);
	}
	else {
		strcpy(loc.country,(const char *)locset.m_country);
		strcpy(loc.state,(const char *)locset.m_state );
		strcpy(loc.location, (const char *)locset.m_location);
		parseLongLat(locset.m_longitude, loc.longitude);
		parseLongLat(locset.m_latitude,loc.latitude);
		loc.hrs_offset=locset.m_houroff;
		loc.min_offset=locset.m_minoff;
		loc.special_code=locset.m_specialcode;
		loc.time_zone=locset.m_timezone;
	}
 return ( 1 );
}


/*class DaoBirthDatabase : public DaoDatabase {
	  CBirthset birthset;
	  CRectset rectset;
	  BIRTH_DB birth;
	  RECT_DATA rect;
	  int isRect;
public:
	DaoBirthDatabase() : DaoDatabase() { isRect = 0; }
      ~DaoBirthDatabase() {}
      	  void setBirth( BIRTH_DB& b ) { birth = b; }
	  void setRect( RECT_DB & r ) { rect= r; isRect=1; }
      BIRTH_DB &getBirth() { return birth; }
	  RECT_DATA &getRect() { return rect; }*/
int DaoBirthDatabase::checkRec( int wh )
{
char msgbuf[100];
char sqlbuf[500];
char erbuf[500];
 CString n;
 if ( !wh ) {
	sprintf( sqlbuf,"select * from births where name=%s", quote(birth.name,n) ); 	
    try {
      if ( birthset.IsOpen() )
	     birthset.Close();
	   birthset.Open( dbOpenDynaset, sqlbuf );
	   if ( !birthset.IsOpen() || birthset.IsBOF() )
	    	return( 1 );
	   else
	    	return( 0 );
	} catch ( CDaoException *e ) {
      e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	}
 }
 else {
	    sprintf( sqlbuf,"select * from rectification where name=%s", (const char *)quote(birth.name,n) ); 	
    try {
      if ( rectset.IsOpen() )
	     rectset.Close();
	   rectset.Open( dbOpenDynaset, sqlbuf );
	   if ( !rectset.IsOpen() || rectset.IsBOF() )
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

int DaoBirthDatabase::dosave()
{
    char erbuf[500];

	try {
		if ( checkRec() ) {
          if ( !birthset.IsOpen() )
			  birthset.Open();
   		  birthset.AddNew();
		}
	  else
		  birthset.Edit();
	  if ( isRect ) {
		  if ( checkRec(1) ) {
            if ( !rectset.IsOpen() )
				rectset.Open();
			rectset.AddNew();
		  }
		else
			rectset.Edit();
	  }
      transfer(1);
      birthset.Update();
	  if ( isRect )
		  rectset.Update();
	} catch ( CDaoException * e ) {
	  e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	  return( 0 );
	}
 return( 1 );
}

int DaoBirthDatabase::dodelete()
{
 char buf[250];
 CString nm;
 sprintf( buf, "delete from births where name=%s",
	 (const char *)quote(birth.name, nm) );
 doExecDelete( buf );
 sprintf( buf, "delete from rectification where name=%s",
	 (const char *)quote(birth.name, nm) );
 return( doExecDelete( buf ) );
}

int DaoBirthDatabase::find()
{
  if ( checkRec() )
	  return( 0 );
  checkRec(1);
  transfer(0);
  return(1);
}
     
int DaoBirthDatabase::transfer( int save )
{

		if ( save ) { 
		birthset.m_birthdate = COleDateTime(birth.birth_data.birth_date.year,
			birth.birth_data.birth_date.month, birth.birth_data.birth_date.day,0,0,0);
		birthset.m_AMPM=birth.am_pm;
		birthset.m_sex = birth.sex;
		birthset.m_rect=isRect;
		birthset.m_hours=birth.birth_data.birth_time.hours;
		birthset.m_minutes=birth.birth_data.birth_time.minutes;
		birthset.m_name=birth.name;
		birthset.m_country=birth.country;
		birthset.m_location=birth.location;
		birthset.m_state=birth.state;
		birthset.m_houroff=birth.birth_data.hour_adjust;
		birthset.m_minoff=birth.birth_data.minutes_adjust;
		birthset.m_specialcode=birth.special_code;
		birthset.m_timezone=birth.time_zone;
		birthset.m_latitude=fmtLongLat(birth.birth_data.latitude, birthset.m_latitude);
		birthset.m_longitude=fmtLongLat(birth.birth_data.longitude, birthset.m_longitude);
		if ( isRect ) {
			rectset.m_birthdate = COleDateTime(birth.birth_data.birth_date.year,
			birth.birth_data.birth_date.month, birth.birth_data.birth_date.day,0,0,0);
		    rectset.m_name=birth.name;
			rectset.m_am_pm=rect.am_pm;
			rectset.m_angle=rect.angle;
			rect.degree.dir='D';
			fmtLongLat(rect.degree,rectset.m_degree);
			rectset.m_birth_time_known=rect.birth_time_known;
			rectset.m_hours=rect.trial.hours;
			rectset.m_minutes=rect.trial.minutes;
			rectset.m_rect_system=rect.rect_system;
			rectset.m_sign=rect.sign;
			rectset.m_totalminutes=rect.total_minutes;
		}
	}
	else {
		strcpy( birth.name, birthset.m_name);
		strcpy(birth.country,(const char *)birthset.m_country);
		strcpy(birth.state,(const char *)birthset.m_state );
		strcpy(birth.location, (const char *)birthset.m_location);
		extractDate(birthset.m_birthdate,birth.birth_data.birth_date);
		birth.birth_data.birth_time.hours=birthset.m_hours;
		birth.birth_data.birth_time.minutes=birthset.m_minutes;
		birth.am_pm=birthset.m_AMPM;
		birth.sex = birthset.m_sex;
		parseLongLat(birthset.m_longitude, birth.birth_data.longitude);
		parseLongLat(birthset.m_latitude,birth.birth_data.latitude);
		birth.birth_data.hour_adjust=birthset.m_houroff;
		birth.birth_data.minutes_adjust=birthset.m_minoff;
		birth.special_code=birthset.m_specialcode;
		birth.time_zone=birthset.m_timezone;
		if ( !rectset.IsBOF() ) {
		  isRect=1;
		  rect.am_pm=rectset.m_am_pm;
		  rect.angle=rectset.m_angle;
		  rect.birth_time_known=rectset.m_birth_time_known;
	      parseLongLat(rectset.m_degree,rect.degree);
          rect.sign=rectset.m_sign;
		  rect.rect_system=rectset.m_rect_system;
		  rect.angle=rectset.m_angle;
		  rect.trial.hours=rectset.m_hours;
		  rect.trial.minutes=rectset.m_minutes;
		  rect.total_minutes=rectset.m_totalminutes;
		}
		else {
			memset(&rect,0,sizeof(RECT_DATA));
			rect.birth_time_known=1;
		}
	}
 return ( 1 );

}


/* class DaoTransitDatabase : public DaoDatabase {
	  CTransitset rectset;
	  BIRTH_DB birth, trans;
public:
	  DaoTransitDatabase()  : DaoDatabase() {}
      ~TransitDatabase() {}
      	  void setBirth( BIRTH_DB& b ) { birth = b; }
	  void setT( RECT_DB & r ) { rect= r; isRect=1; }
      BIRTH_DB &getBirth() { return birth; }
	  RECT_DATA &getRect() { return rect; }*/
int DaoTransitDatabase::checkRec( int wh )
{
char msgbuf[100];
char sqlbuf[500];
char erbuf[500];
 CString n, e;

	sprintf( sqlbuf,"select * from transits where name=%s and event=%s", quote(birth.name,n), quote(trans.name,e) ); 	
    try {
      if ( transset.IsOpen() )
	     transset.Close();
	   transset.Open( dbOpenDynaset, sqlbuf );
	   if ( !transset.IsOpen() || transset.IsBOF() )
	    	return( 1 );
	   else
	    	return( 0 );
	} catch ( CDaoException *e ) {
      e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	}
	  return(1);


}


int DaoTransitDatabase::dodelete()
{
char buf[250];
 CString ev;
 sprintf( buf, "delete from transits where event=%s",
	 (const char *)quote( trans.name, ev) );
 return ( doExecDelete( buf ) );
}

int DaoTransitDatabase::transfer( int save )
{
 
	if ( save ) { 
		transset.m_birthdate = COleDateTime(birth.birth_data.birth_date.year,
			birth.birth_data.birth_date.month, birth.birth_data.birth_date.day,0,0,0);
		transset.m_transdate = COleDateTime(trans.birth_data.birth_date.year,
			trans.birth_data.birth_date.month, trans.birth_data.birth_date.day,0,0,0);
		transset.m_AMPM=trans.am_pm;
		transset.m_hours=trans.birth_data.birth_time.hours;
		transset.m_minutes=trans.birth_data.birth_time.minutes;
		transset.m_name=birth.name;
		transset.m_event=trans.name;
		transset.m_country=trans.country;
		transset.m_location=trans.location;
		transset.m_state=trans.state;
		transset.m_houroff=trans.birth_data.hour_adjust;
		transset.m_minoff=trans.birth_data.minutes_adjust;
		transset.m_specialcode=trans.special_code;
		transset.m_timezone=trans.time_zone;
		transset.m_latitude=fmtLongLat(trans.birth_data.latitude, transset.m_latitude);
		transset.m_longitude=fmtLongLat(trans.birth_data.longitude, transset.m_longitude);
	}
	else {
		strcpy( trans.name, transset.m_event);
		strcpy(trans.country,(const char *)transset.m_country);
		strcpy(trans.state,(const char *)transset.m_state );
		strcpy(trans.location, (const char *)transset.m_location);
		extractDate(transset.m_transdate,trans.birth_data.birth_date);
		trans.birth_data.birth_time.hours=transset.m_hours;
		trans.birth_data.birth_time.minutes=transset.m_minutes;
		trans.am_pm=transset.m_AMPM;
		parseLongLat(transset.m_longitude, trans.birth_data.longitude);
		parseLongLat(transset.m_latitude,trans.birth_data.latitude);
		trans.birth_data.hour_adjust=transset.m_houroff;
		trans.birth_data.minutes_adjust=transset.m_minoff;
		trans.special_code=transset.m_specialcode;
		trans.time_zone=transset.m_timezone;
	}
 return ( 1 );

}
      

/*class DaoRelocateDatabase : public DaoDatabase {
	  BIRTH_DB birth;
	  LOC_DB reloc;
	  CRelocationSet relocset;
public:
	DaoRelocateDatabase() : DaoDatabase() {}
      ~BirthDatabase() {}
      void setBirth( BIRTH_DB& b ) { birth = b; }
	  void setRelo( LOC_DB & l ) { reloc= l; }
      BIRTH_DB &getBirth() { return birth; }
	  LOC_DB &getRelo() { return reloc; } */

int DaoRelocateDatabase::checkRec( int wh )
{
char msgbuf[100];
char sqlbuf[500];
char erbuf[500];
 CString n, p;

	sprintf( sqlbuf,"select * from relocations where name=%s and personal=%s", (const char *)quote(birth.name,n), (const char *)quote((const char *)personal,p) ); 	
    try {
      if ( relocset.IsOpen() )
	     relocset.Close();
	   relocset.Open( dbOpenDynaset, sqlbuf );
	   if ( !relocset.IsOpen() || relocset.IsBOF() )
	    	return( 1 );
	   else
	    	return( 0 );
	} catch ( CDaoException *e ) {
      e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	}
	  return(1);

}


int DaoRelocateDatabase::dodelete()
{
char buf[250];
 CString pe, nm;
 sprintf( buf, "delete from relocations where personal=%s and name=%s",
	 (const char *)quote((const char *)personal, pe), (const char *)quote(birth.name, nm) );
 return ( doExecDelete( buf ) );
}

    
int DaoRelocateDatabase::transfer( int save )
{

	if ( save ) {
		relocset.m_birthdate = COleDateTime(birth.birth_data.birth_date.year,
			birth.birth_data.birth_date.month, birth.birth_data.birth_date.day,0,0,0);
		relocset.m_name=birth.name;
		relocset.m_personal=personal;
		relocset.m_country=reloc.country;
		relocset.m_location=reloc.location;
		relocset.m_state=reloc.state;
		relocset.m_houroff=reloc.hrs_offset;
		relocset.m_minoff=reloc.min_offset;
		relocset.m_specialcode=reloc.special_code;
		relocset.m_timezone=reloc.time_zone;
		relocset.m_latitude=fmtLongLat(reloc.latitude, relocset.m_latitude);
		relocset.m_longitude=fmtLongLat(reloc.longitude, relocset.m_longitude);
	}
	else {
		personal=relocset.m_personal;
		strcpy(reloc.country,(const char *)relocset.m_country);
		strcpy(reloc.state,(const char *)relocset.m_state );
		strcpy(reloc.location, (const char *)relocset.m_location);
		parseLongLat(relocset.m_longitude, reloc.longitude);
		parseLongLat(relocset.m_latitude,reloc.latitude);
		reloc.hrs_offset=relocset.m_houroff;
		reloc.min_offset=relocset.m_minoff;
		reloc.special_code=relocset.m_specialcode;
		reloc.time_zone=relocset.m_timezone;
	}
 return ( 1 );
}
