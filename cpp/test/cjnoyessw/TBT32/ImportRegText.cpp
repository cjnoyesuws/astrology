// ImportRegText.cpp: implementation of the ImportRegText class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning ( disable : 4995 )
#include "stdafx.h"
#include "TBT32.h"
#include "dregtext1.h"
#include "textbloc.hpp"
#include "progress.h"
#include "ImportRegText.h"
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



void ImportRegText::Process()
{
 char path[500];
#ifndef _UNICODE
 if ( m_dir.GetLength() > 0 )
	  strcpy(path, (const char *) m_dir );
 else
      strcpy(path, (const char *) GetSrcDir() );
#else
 memset(path,0,500);
 if ( m_dir.GetLength() > 0 )
	wcstombs(path, m_dir, m_dir.GetLength() );
 else
    wcstombs(path, GetSrcDir(), GetSrcDir().GetLength() );
#endif
 if ( path[strlen(path)-1]!= '\\' )
    strcat( path, "\\" );
 strcat( path, filename );
 m_pProg->SetFile(CString(filename));
 strcat( path, ".AST" );
 CTextBlockAry *pAry= new CTextBlockAry(2,500);
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



int ImportRegText::ProcessItem(CTextBlock *pBlk ) 
{
 TCHAR errbuf[500];
 char buf[25], id[25], id2[25], sqlbuf[125],alang[11];
 strcpy( buf, _strupr( textitem ) );
 pBlk->GetIDParts(id, id2);
 try {
   m_pProg->IncProgress();
   if ( !stricmp(id,"@@COMMENT") )
	   return 1;
   CString Lang = GetCurLanguage();
   memset(alang,0,11);
#ifdef _UNICODE
   wcstombs(alang, (LPCTSTR)Lang, Lang.GetLength());
#else
   strcpy(alang,(LPCTSTR)Lang);
#endif
   sprintf( sqlbuf, "select * from RegularText where Key1='%s' and Key2='%s' and TextType='%s' and Lang='%s'",
      id, id2, buf, alang );
   if ( set.IsOpen() )
	   set.Close();
   set.Open(dbOpenDynaset,CString(sqlbuf));
   if ( set.IsBOF() )
	   set.AddNew();
   else
	   set.Edit();
   set.m_Key1 = id;
   set.m_key2 = id2;
   set.m_TextType = buf;
   set.m_Text = pBlk->text();
   CSymbol *pSym=pRegSymbols->Find(id,1,0);
   if ( pSym == NULL ) {
	   alert_box("Bad Symbol", "Can't Find Symbol %s", id );
       return( 0 );
	}
   set.m_Key1num=pSym->value();
   pSym=pRegSymbols->Find(id2,2,0);
   if ( pSym == NULL ) {
	   alert_box("Bad Symbol", "Can't Find Symbol %s", id2 );
       return( 0 );
		}
   set.m_Key2num=pSym->value();
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
