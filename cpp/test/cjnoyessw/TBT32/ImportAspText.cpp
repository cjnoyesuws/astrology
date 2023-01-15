// ImportAspText.cpp: implementation of the ImportAspText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TBT32.h"
#include "textbloc.hpp"
#include "daspecttext1.h"
#include "progress.h"
#include "ImportAspText.h"
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


void ImportAspText::Process()
{
 char path[500];
#ifndef _UNICODE 
 if ( m_dir.GetLength() > 0 )
	  strcpy(path, (const char *) m_dir );
 else
    strcpy(path, (const char *) GetSrcDir() );
#else
 memset(path, 0, 500);
 if ( m_dir.GetLength() > 0 ) 
	 wcstombs(path, m_dir, m_dir.GetLength() );
 else
	 wcstombs(path,GetSrcDir(),GetSrcDir().GetLength() );
 path[GetSrcDir().GetLength()] = '\0';
#endif
 if ( path[strlen(path)-1]!= '\\' )
    strcat( path, "\\" );
 strcat( path, filename );
 strcat( path, ".AST" );
 m_pProg->SetFile(CString(filename));
 CTextBlockAry *pAry= new CTextBlockAry(3,500);
 if ( !pAry->Load(path) ) {
    delete pAry;
	return;
	}
 m_pProg->SetMax(pAry->nElements());
 m_pProg->Reset();
 CTextBlock *pBlk;
 while ( ( pBlk=pAry->next() ) != NULL ) {
    if ( !ProcessItem(pBlk) )
		break;
 }
 delete pAry;
}



int ImportAspText::ProcessItem(CTextBlock *pBlk ) 
{
 TCHAR errbuf[500];
 char buf[25], id[25], id2[25], id3[25], sqlbuf[150], alang[11];
 strcpy( buf, _strupr( textitem ) );
 pBlk->GetIDParts(id, id2, id3);
 m_pProg->IncProgress();
 if ( !stricmp(id,"@@COMMENT") )
	   return 1;
 try {
   CString Lang = GetCurLanguage();
   memset(alang,0,11);
#ifdef _UNICODE
   wcstombs(alang, (LPCTSTR)Lang, Lang.GetLength());
#else
   strcpy(alang,(LPCTSTR)Lang);
#endif
   sprintf( sqlbuf, "select * from AspectText where Planet1='%s' and Planet2='%s' and Aspect='%s' and TextType='%s' and Lang='%s'",
     id, id2, id3, buf, alang );
   if ( set.IsOpen() )
	   set.Close();
   set.Open(dbOpenDynaset,CString(sqlbuf));
   if ( set.IsBOF() )
	   set.AddNew();
   else
	   set.Edit();
   set.m_Planet1 = id;
   set.m_Planet2 = id2;
   set.m_Aspect = id3;
   set.m_TextType = buf;
   set.m_Text = pBlk->text();
   CSymbol *pSym=pRegSymbols->Find(id,1,0);
   if ( pSym == NULL ) {
	   alert_box("Bad Symbol", "Can't Find Symbol %s", id );
       return( 0 );
		}
   set.m_Planet1num=pSym->value();
   pSym=pRegSymbols->Find(id2,2,0);
   if ( pSym == NULL ) {
	   CSymbol *pSym=pRegSymbols->Find(id2,4,0);
	   if ( pSym == NULL ) {
		  alert_box("Bad Symbol", "Can't Find Symbol %s", id2 );
		  return( 0 );
		  }
	}
   set.m_Planet2num=pSym->value();
   pSym=pRegSymbols->Find(id3,3,0);
   if ( pSym == NULL ) {
	   alert_box("Bad Symbol", "Can't Find Symbol %s", id3 );
       return( 0 );
		}
   set.m_Aspectnum=pSym->value();
   pTransformers->ToReplacements(set.m_Text);
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
