// ImportReportText.cpp: implementation of the ImportReportText class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning( disable 4995 )
#include "stdafx.h"
#include "TBT32.h"
#include "dreporttext1.h"
#include "textbloc.hpp"
#include "progress.h"
#include "ImportReportText.h"
#include "symbol.hpp"
#include "strtransform.h"
#include "setup.h"
#include "errors.fns"
#include "setlanguage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImportReportText::ImportReportText(char *fnamestr, char *item, CProgress *prg, CString &dir) 
{ 
	m_dir = dir; 
	strcpy(filename,fnamestr); 
	strcpy(textitem,item); 
	m_pProg=prg; 
}


void TrimTraillfcr(CString &s)
{
 TCHAR *p;
 int l;

 l = s.GetLength();
 p = s.LockBuffer()+(l-1);
 while ( (*p==_T('\r') || *p==_T('\n')) && l ) {
    *p-- = _T('\0');
	l--;
 }
 s.UnlockBuffer();
}

int getTTCount( char *str )
{
 int cnt=1;
 char *p =strchr(str,';');
 if ( p==NULL)
	 return cnt;
 cnt++;
 p++;
 p = strchr(p,';');
 if ( p==NULL)
	 return cnt;
 cnt++;
 p++;
 p = strchr(p,';');
 if ( p==NULL)
	 return cnt;
 return( cnt );
}

void ImportReportText::Process()
{
 char path[500], ttbuf[25], ttbuf2[25], ttbuf3[25], ttbuf4[25], dummy;
 int ttcount;
 char *tts[] = { ttbuf, ttbuf2, ttbuf3, ttbuf4 };

#ifndef _UNICODE
 if ( m_dir.GetLength() > 0 )
    strcpy(path, m_dir );
 else
     strcpy(path,GetSrcDir() );
 if ( path[strlen(path)-1]!= '\\' )
    strcat( path, "\\" );
#else
 memset(path,0,500);    
 if ( m_dir.GetLength() > 0 )
    wcstombs(path, m_dir, m_dir.GetLength() );
 else
    wcstombs(path,GetSrcDir(),GetSrcDir().GetLength() );
 if ( path[strlen(path)-1]!= '\\' )
    strcat( path, "\\" );
#endif
 ttcount = getTTCount(textitem);
 memset(ttbuf,0,25);
 memset(ttbuf2,0,25);
 memset(ttbuf3,0,25);
 memset(ttbuf4,0,25);
 if ( ttcount==2 ) {
    sscanf(textitem,"%[^;]%c%s", ttbuf, &dummy, ttbuf2 );
    }
 if ( ttcount==3 ) {
	 sscanf(textitem,"%[^;]%c%[^;]%c%s", ttbuf, &dummy, ttbuf2, &dummy, ttbuf3 );
    }
 if ( ttcount==4 ) {
	 sscanf(textitem,"%[^;]%c%[^;]%c%[^;]%c%s", ttbuf, &dummy, ttbuf2, &dummy, ttbuf3, dummy, ttbuf4 );
    }
 else if ( ttcount==1 ) {
    strcpy( ttbuf,textitem);
    ttcount=1;
    }
 m_pProg->SetFile(CString(filename));
 //sscanf(textitem,"%[^;]%c%s", ttbuf, &dummy, ttbuf2 );
 strcat( path, filename );
 strcat( path, ".AST" );
 CTextBlockAry *pAry= new CTextBlockAry(1,500);
 if ( !pAry->Load(path) ) {
    delete pAry;
	return;
	}
 m_pProg->SetMax(pAry->nElements());
 m_pProg->Reset();
 CTextBlock *pBlk;
 while ( ( pBlk=pAry->next() ) != NULL ) {
	 for ( int j = 0; j < ttcount; j++ ) {    
	     if ( !ProcessItem(pBlk, tts[j]) )
		    break;
         }
    }
 delete pAry;
}



int ImportReportText::ProcessItem(CTextBlock *pBlk, char *tt ) 
{
 TCHAR errbuf[500];
 char buf[25], id[35], sqlbuf[150], alang[11];
 int index;
 strcpy( buf, _strupr( tt ) );
 pBlk->GetIDParts(id, &index);
 try {
   m_pProg->IncProgress();
   if ( !stricmp(id,"@@COMMENT") )
	   return 1;
   CString Lang = GetCurLanguage();
   memset(alang,0,11);
#ifdef _UNICODE
   wcstombs(alang, (LPCTSTR)Lang, Lang.GetLength());
#else
   strcpy(alang, (LPCTSTR)Lang );
#endif
   sprintf(sqlbuf, "select * from ReportText where texttype='%s' and textkey='%s' and iIndex=%d and Lang='%s'",
      buf, id, index, alang );
   if ( set.IsOpen() )
	   set.Close();
   set.Open(dbOpenDynaset, CString(sqlbuf));
   if ( set.IsBOF() )
	   set.AddNew();
   else
	   set.Edit();
   set.m_textkey = id;
   set.m_iIndex = index;
   set.m_texttype = buf;
   set.m_text = pBlk->text();
   TrimTraillfcr(set.m_text);
   CSymbol *pSym=pRepSymbols->Find(id,0);
   if ( pSym == NULL ) {
	   alert_box("Bad Symbol", "Can't Find Symbol %s", id );
       return( 0 );
		}
   set.m_iTextKey=pSym->value();
   pTransformers->ToReplacements(set.m_text);
   set.Update();
   set.Close();
 }
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return ( 0 );
  }
 return ( 1 );

}