#include "stdafx.h"
#include "dregtext.h"
#include "daspecttext.h"
#include "dreporttext.h"
#include "textgetter.h"
#include "errors.fns"
#include "report.h"
#include <assert.h>
#include "direc.hpp"

extern BOOL bHasLanguage;
/*class GenericTextGetter {
   protected:
      CDaoRecordset *pSet;
      CDaoQueryDef *pQuery;
      CDaoDatabase *pDatabase;
      CString texttype;
      CString dummyText;
   public:
      GenericTextGetter( char *p, CDaoDatabase *pDb ) {}
      virtual ~GenericTextGetter() { if (pSet->IsOpen()) pSet->Close(); if (pQuery->IsOpen() ) pQuery->Close(); delete pQuery; delete pSet; }
   }


class RegTextGetter : GenericTextGetter {
   public:
      RegTextGetter( char *p, CDaoDatabase *pDb );
      int GetText( int k1, int k2, FILE *stream );
      const char *GetText( int k1, int k2 );
   };



class AspTextGetter : GenericTextGetter {
   public:
      AspTextGetter( char *p, CDaoDatabase *pDb );
      int GetText( int k1, int k2, int k3, FILE *stream );
      const char *GetText( int k1, int k2, int k3 );
   };


class ReportTextGetter : GenericTextGetter {
   public:
      ReportTextGetter( char *p, CDaoDatabase *pDb );
      const char *GetText( int k, int ind );
      int GetText( int k, int ind, FILE *stream );
   
   
   };

*/
#define LEN_COUNT 13
static short array_ids[] = {ST__MONTH,ST__SIGN,ST__PLANET,ST__NUMBERS,ST__ASPECTS,
ST__SIGN3, ST__ERROR, ST__HOUSE_MODES,ST__SIDE_TROP,ST__RETROGRADE,ST__RECT_METH,
TR__AFFECTS, ST__ARABN};
static short array_size[] = {13,13,60,12,13,13,6,13,3,4,6,13,150};

void GenericTextGetter::OpenSetAndQuery( char *tt, char *qry )
{
 char errbuf[500];
 try {
    pQuery->Open(qry);
    pQuery->SetParamValue("TextTypeParam",COleVariant(tt,VT_BSTR));
#ifdef _UNICODEVER   
	if ( bHasLanguage == TRUE )
	   pQuery->SetParamValue("LangParam",COleVariant(GetCurLanguage(),VT_BSTR));
#endif	
	pSet->Open(pQuery);
    }
 catch ( CDaoException *e ) {
    e->GetErrorMessage( errbuf, 500 );
    alert_box("Database Error",errbuf );
    bErrorState=TRUE;
    }
}


RegTextGetter::RegTextGetter( char *p, CDaoDatabase *pDb ) : GenericTextGetter(p,pDb)
{
 pSet = new CDRegText(pDb);
 OpenSetAndQuery(p,"RegTextQuery");
}

const char *RegTextGetter::GetText( int k1, int k2 )
{
 char errbuf[500], sqlbuf[100];
 if ( bErrorState  == TRUE)
    return ( (const char *)dummyText );
 sprintf( sqlbuf, "Key1num=%d and Key2num=%d", k1, k2 );
 try {
    if ( pSet->FindFirst(sqlbuf) )
       return( (const char *)((CDRegText *)pSet)->m_Text );
    else
       return( (const char *)dummyText);
    }
 catch ( CDaoException *e ) {
    e->GetErrorMessage( errbuf, 500 );
    alert_box("Database Error",errbuf );
    return( (const char *)dummyText);
    }
 return( (const char *)dummyText);
}


int RegTextGetter::GetText( int k1, int k2, FILE *stream )
{
  return ( fputs(GetText(k1,k2),stream ) );
}


AspTextGetter::AspTextGetter( char *p, CDaoDatabase *pDb ) : GenericTextGetter(p,pDb)
{
 pSet = new CDAspectText(pDb);
 OpenSetAndQuery(p,"AspectQuery");
}


int AspTextGetter::GetText( int k1, int k2, int k3, FILE *stream )
{
  return ( fputs(GetText(k1,k2,k3),stream ) );
}


const char *AspTextGetter::GetText( int k1, int k2, int k3 )
{
 char errbuf[500], sqlbuf[100], altbuf[100];
 if ( bErrorState == TRUE )
    return ( (const char *)dummyText );
 sprintf( sqlbuf, "Planet1num=%d and Planet2num=%d and AspectNum=%d", k1, k2, k3 );
 sprintf( altbuf, "Planet2num=%d and Planet1num=%d and AspectNum=%d", k1, k2, k3 );
 try {
    if ( pSet->FindFirst(sqlbuf) )
       return( (const char *)((CDAspectText *)pSet)->m_Text );
    else if (pSet->FindFirst(altbuf) )
       return( (const char *)((CDAspectText *)pSet)->m_Text );
    else
       return( (const char *)dummyText);
    }
 catch ( CDaoException *e ) {
    e->GetErrorMessage( errbuf, 500 );
    alert_box("Database Error",errbuf );
    return( (const char *)dummyText);
    }
 return( (const char *)dummyText);
}

ReportTextGetter::ReportTextGetter( char *p, CDaoDatabase *pDb ) : GenericTextGetter(p,pDb)
{
 pLens = new short[200];
 for ( int i = 0; i < 200; i++ )
	 pLens[i] = 1;
 for ( int j = 0; j < LEN_COUNT; j++ )
	 pLens[array_ids[j]] = array_size[j];
 pSet = new CDReportText(pDb);
 OpenSetAndQuery(p,"ReportTextQuery");  
}

const char *ReportTextGetter::GetText( int k1, int ind )
{
 char errbuf[500], sqlbuf[100];
 if ( bErrorState == TRUE)
    return ( (const char *)NULL);
 MapHandler *pHnd;
 if ( !cache.Lookup(k1,(void *&)pHnd) ) {
    pHnd = new MapHandler(pLens[k1]);
	cache.SetAt(k1,(void *)pHnd);
    }
 if ( ind >= 0 && pHnd->IsSet(ind) ) {
    return( pHnd->GetAt(ind) );
    }
 sprintf(sqlbuf,"iTextKey=%d and iIndex=%d", k1, ind );
 try {
    if ( pSet->FindFirst(sqlbuf) ) {
	   //if (((CDReportText *)pSet)->m_text.FindOneOf("\x80\r\n")!= -1 )
       //   ((CDReportText *)pSet)->m_text += "\x80";
       const char *pbf = _strdup((const char *)((CDReportText *)pSet)->m_text);
	   pHnd->SetAt(ind,pbf);
       return( pbf );
       }
    else
       return( (const char *)NULL);
    }
 catch ( CDaoException *e ) {
    e->GetErrorMessage( errbuf, 500 );
    alert_box("Database Error",errbuf );
    return( (const char *)NULL);
    }
 return( (const char *)NULL);
}

int ReportTextGetter::GetText( int k1, int ind, FILE *stream )
{
  return ( fputs(GetText(k1,ind),stream ) );
}

ReportTextGetter::~ReportTextGetter()
{  
 POSITION pos;
 WORD key;
 MapHandler *pHnd;
 for ( pos = cache.GetStartPosition(); pos != NULL; )
   {
   cache.GetNextAssoc( pos, key, (void *&)pHnd );
   delete pHnd;
   }
 cache.RemoveAll();  
 delete pLens;
}



void MapHandler::SetAt(int i, const char *p)
{
 if ( (type == notset) || (type==stringt && item == i ) || (i==0 && len==1) ){
	 pStr = p;
	 type = stringt;
	 item = i;
	 bits[i] = true;
     }
 else if ( i >= 0 && (type == stringt ) ) {
    pStrArray = new CPtrArray;
	pStrArray->SetSize(len,1);
	for ( int j = 0; j < len; j++ )
		pStrArray->SetAt(j,(void *)NULL);
	pStrArray->SetAtGrow(item,(void *) pStr);
	pStr = NULL;
	pStrArray->SetAtGrow(i,(void *)p);
	bits[i] = true;
    bits[item] = true;
	type = array;
    }
 else if ( i >= 0 ) {
	pStrArray->SetAtGrow(i,(void *)p);
	bits[i] = true;
    }
}

bool MapHandler::IsSet(int i)
{
 if ( type == stringt && i == item ) 
	 return( true );
 else if ( type == stringt )
	 return( false );
 else if ( type == notset )
	 return( false );
 return ( bits[i] );
}

const char *MapHandler::GetAt(int i)
{
 if ( i==item && type == stringt )
	 return pStr;
 else
	 return (const char *)pStrArray->GetAt(i);
}

MapHandler::~MapHandler()
{
 if ( pStrArray != NULL ) { 
	 for ( int i= 0; i < pStrArray->GetSize(); i++ ) {
	   const char *p = (const char *)pStrArray->GetAt(i);
	   if ( p != NULL )
		   delete p;
	 }
  delete pStrArray;
 }
 if ( pStr != NULL )
	 delete pStr;
}
