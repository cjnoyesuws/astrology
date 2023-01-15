#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "adbcombbox.hpp"
#include "errors.fns"

/*
int zAstComboBoxStatic::addResStrings( int id )
{
 char *p;
 int e;
 ResStrBlock *px;

 px = new ResStrBlock(id);
 while ( ( p = px->get() ) != NULL )
       e = add( zString(p) );
 delete px;
 return( e );
}

int zAstComboBoxStatic::insertResStrings( int id, int nAt )
{
 ResStrBlock x(id);
 int e;
 char *p;

 while ( ( p = x.get() ) != NULL )
       e = insert( zString(p), (nAt != -1?nAt++:-1) );
 return( e );
}
*/

 CString &CAstComboBox::quote( const char *pChar, CString & str )
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

void CAstComboBox::doFillCombo(char *sql, char *fld)
{
 char buf[500];
 try {
    set.m_field = fld;
    pCombo->ResetContent(); 
    set.Open(dbOpenDynaset, sql);
    if ( !set.IsBOF() ) {
	    while ( !set.IsEOF() ) {
	         pCombo->AddString(set.m_data);
		      set.MoveNext();
          }
       }
    set.Close();
    }
 catch ( CDaoException *e ) {
    e->GetErrorMessage(buf,500);
    alert_box("Database Error", buf );
    }
}

int CLocationComboBox::loadList( )
{
 doFillCombo("select distinct country from locations","[country]");
 /*pCombo->ResetContent(); 
 set.Open(dbOpenDynaset, "select distinct country from locations" );
 if ( !set.IsBOF() ) {
	 while ( !set.IsEOF() ) {
	       pCombo->AddString(set.m_country);
		   set.MoveNext();
	 }
 }
 set.Close();*/
 return( 1 );
}

int CLocationComboBox::loadList( CString & country )
{
 char buf[130];
 CString co;
 sprintf( buf, "select distinct state from locations where country=%s", (const char *)quote((const char *)country, co ));
 doFillCombo(buf,"[state]");
 /*pCombo->ResetContent(); 
 try {
   set.Open(dbOpenDynaset, buf );
   if ( !set.IsBOF() ) {
	   while ( !set.IsEOF() ) {
	       pCombo->AddString(set.m_country);
		    set.MoveNext();
	   }
   }
   set.Close();
   }
 catch ( CDaoException *e ) {
    e->GetErrorMessage(errbuf,500);
    alert_box("Error on Database", errbuf );
    return 0;
    }
*/
 return( 1 );
}

int CLocationComboBox::loadList( CString & country, CString & state, int cdp)
{
 char buf[200];
 CString co;
 CString st;
 char *pCdp;
 if ( cdp ) 
	 pCdp = "";
 else
	 pCdp = "and not location like '*CDP' and not location like '*CCD'";
 sprintf( buf, "select distinct location from locations where country=%s and state=%s %s", 
	 (const char *)quote( (const char *) country, co ), (const char *) quote( (const char *) state, st), pCdp );
 doFillCombo(buf,"[location]");
 /*pCombo->ResetContent(); 
 try {
   set.Open(dbOpenDynaset, buf );
   if ( !set.IsBOF() ) {
	    while ( !set.IsEOF() ) {
	      pCombo->AddString(set.m_country);
		   set.MoveNext();
	      }
      }
   set.Close();
   }
 catch ( CDaoException *e ) {
    e->GetErrorMessage(errbuf,500);
    alert_box("Error on Database", errbuf);
    return 0;
    }*/
 return( 1 );
 
}

int CBirthComboBox::loadList( )
{
 doFillCombo("select name from births", "[name]");
 /*char errbuf[500];
 pCombo->ResetContent(); 
 try {
   set.Open(dbOpenDynaset, "select * from births" );
   if ( !set.IsBOF() ) {
	   while ( !set.IsEOF() ) {
	       pCombo->AddString(set.m_name);
		    set.MoveNext();
	      }
      }
    set.Close();
    }
 catch ( CDaoException *e ) {
    e->GetErrorMessage(errbuf,500);
    alert_box("Error on Database", errbuf);
    return ( 0 );
    }*/
 return( 1 );
}

int CTransitComboBox::loadList( CString & name )
{
 char buf[150];
 CString nm;
 sprintf( buf, "select event from transits where name=%s", (const char *)quote((const char *)name,nm) );
 doFillCombo(buf,"[event]");
 /*pCombo->ResetContent(); 
 try {
   set.Open(dbOpenDynaset, buf );
   if ( !set.IsBOF() ) {
	   while ( !set.IsEOF() ) {
	      pCombo->AddString(set.m_event);
		   set.MoveNext();
	      }
      }
   set.Close();
   }
 catch ( CDaoException *e ) {
   e->GetErrorMessage( errbuf, 500 );
   alert_box("Error on Database", errbuf );
   }*/
 return( 1 );
}

int CTransitComboBox::loadList()
{
 doFillCombo("select event from transits","[event]");
 /*pCombo->ResetContent(); 
 try {
   set.Open(dbOpenDynaset, buf );
   if ( !set.IsBOF() ) {
	   while ( !set.IsEOF() ) {
	      pCombo->AddString(set.m_event);
		   set.MoveNext();
	      }
      }
   set.Close();
   }
 catch ( CDaoException *e ) {
   e->GetErrorMessage( errbuf, 500 );
   alert_box("Error on Database", errbuf );
   }*/
 return( 1 );
}


int CRelocateComboBox::loadList( CString &name )
{
 char buf[150];
 CString nm;
 sprintf( buf, "select personal from relocations where name=%s", (const char *)quote((const char *)name,nm) );
 doFillCombo(buf,"[personal]");
 /*pCombo->ResetContent(); 
 try {
   set.Open(dbOpenDynaset, buf );
   if ( !set.IsBOF() ) {
	    while ( !set.IsEOF() ) {
		   pCombo->AddString(set.m_personal);
		   set.MoveNext();
	      }
      }
   set.Close();
   }
 catch ( CDaoException *e ) {
   e->GetErrorMessage( errbuf, 500 );
   alert_box( "Error on Database", errbuf );
   return( 0 );
   }*/
 return( 1 );
}


/*
ResStrBlock::ResStrBlock(int id)
	: zUserResource(zResId(id),zString("ST_BLK"))
{
 char *p = (char *)(void *)*this;
 block = new char[strlen(p)+2];
 strcpy( block, p );
 ptrs[0] = block;
 char *pp = strchr( block, '\1' );
 int i = 1;
 while ( pp != NULL ) {
       *pp='\0';
       pp++;
       ptrs[i++] = pp;
       pp = strchr( pp, '\1' );
       }
 ptrs[i++] = pp;
 count = i-1;
 next = 0;
}


char *ResStrBlock::get()
{
 char *p;

 if ( next < count ) {
    p = ptrs[next];
    next++;
    }
 else p = NULL;
 return( p );
}

char *ResStrBlock::operator [] (int i)
{
 if ( i < count )
    return( ptrs[i] );
 else
    return( NULL );
}

*/