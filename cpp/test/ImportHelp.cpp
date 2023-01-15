// ImportHelp.cpp: implementation of the ImportHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TBT32.h"
#include <stdlib.h>
#include <io.h>
#include "progress.h"
#include "ImportHelp.h"
#include "dhelptxt1.h"
#include "fileary.hpp"
#include "strtransform.h"
#include "textbloc.hpp"
#include "string.h"
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



int ImportHelp::ProcessItem(char *item)
{
  TCHAR errbuf[500];
  char buf[25], path[250], sqlbuf[100], alang[11];
  int len, id;
  try {
	  m_pProg->SetFile(CString(item));
	  m_pProg->IncProgress();
	  strcpy(buf, _strupr(item));
      CString Lang = GetCurLanguage();
      memset(alang,0,11);
#ifdef _UNICODE
	  wcstombs(alang, (LPCTSTR)Lang, Lang.GetLength());
#else
	  strcpy(alang, (LPCTSTR)Lang);
#endif
	  sprintf( sqlbuf, "select * from helptext where texttype='%s' and Lang='%s' order by iChunk", buf, alang );
      if ( set.IsOpen() )
		  set.Close();
	  set.Open(dbOpenDynaset,CString(sqlbuf));
#ifndef _UNICODE	  
	  strcpy( path, dir );
#else
      memset(path,0,250);
	  wcstombs(path, dir,dir.GetLength());
#endif
	  if ( path[strlen(path)-1]!='\\' )
		  strcat( path, "\\" );
	  strcat(path, item );
	  strcat(path, ".ast");
	  CTextBlockAry *pAr= new CTextBlockAry(2,15);
      if ( !pAr->Load(path, 1) ) {
		  delete pAr;
		  return ( 0 );
	  }
	  id = 0;
	  CTextBlock *pBlk;
	  while ((pBlk = pAr->next()) != NULL ) {	     
	     pTransformers->ToReplacements(set.m_Text);
	     if ( set.IsBOF() || set.IsEOF() )
		    set.AddNew();
	     else
		    set.Edit();
	     set.m_Text = pBlk->text();
	     set.m_texttype = buf;
	     set.m_iChunk = id++;
	     set.Update();
		 if ( !set.IsBOF() && !set.IsEOF() )
		    set.MoveNext();
	  }
      set.Close();
	  delete pAr;
	  
  }
  catch ( CDaoException *e ) {
     e->GetErrorMessage(errbuf,499);
	 alert_box(_T("Error on Database"), errbuf );
	 return ( 0 );
  }
 
  return( 1 );
}



void ImportHelp::Process()
{
	char buf[25];
	CAsFile *pFile=pFileList->array();
	//dir = GetSrcDir();
	int cnt = pFileList->getCount(0);
	m_pProg->SetMax(cnt);
	for ( int i = 0; i < pFileList->nElements(); i++, pFile++ ) {
		if ( !pFile->type()	) {
			if ( m_bExport == FALSE )
				strcpy(buf, pFile->name());
			else
				sprintf(buf,"0-%s", pFile->name());
			if ( !ProcessItem(buf) )
				return;
		    }
	    }

}
