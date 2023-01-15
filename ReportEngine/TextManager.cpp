// TextManager.cpp: implementation of the CTextManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Astrow.h"
#include "TextManager.h"
#include "dregtext.h"
#include "dreporttext.h"
#include "daspecttext.h"
#include "textgetter.h"
#include "direc.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "textptr.h"
#include "output.fns"
#include "errors.fns"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void kill_txptps();

BOOL bHasLanguage = FALSE;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*

class CTextManager  
{
protected:
   BOOL bUseDBText;
   static CTextManager *pManager;
   CTextManager();
   CPtrArray RegTextGetterManagers;
   CPtrArray AspTextGetterManagers;
   CPtrArray ReportGetterManagers;
   CDaoDatabase *pDatabase;
public:
	static CTextManager *GetManager();
	virtual ~CTextManager();
   int OpenText( char *p );
   void CloseText( int file );
   void CloseAspText( int file );
   int OpenAspectsText( char *p );
   int OpenReportText(char *p );
   int CloseReport(int rep );
   const char *GetReportText( int rep, int item, int index );
   int GetReportText( int rep, int item, int index, FILE *stream );
   int GetRegText( int txt, int k1, int k2, FILE *stream );
   int GetAspText( int txt, int k1, int k2, int k3, FILE *stream );
   const char *GetRegText( int txt, int k1, int k2);
   const char *GetAspText( int txt, int k1, int k2);
};

*/


void kill_textmgr()
{
 if ( pManager != NULL )
	 delete pManager;
}

CTextManager *pManager;

CTextManager::CTextManager()
{
 bUseDBText = theDirectories.getDatabaseText();
 pDatabase = theDirectories.m_pTextDatabase;
 pManager = this;
 RegTextGetterManagers.SetSize(8);
 AspTextGetterManagers.SetSize(8);
 ReportGetterManagers.SetSize(8);
#ifdef _UNICODEVER
 try {
     CDaoTableDefInfo info;
	 pDatabase->GetTableDefInfo("Languages", info );
	 bHasLanguage = TRUE;
	}
 catch ( CDaoException *e ) {
	 bHasLanguage = FALSE; 
	 }
#endif
}

CTextManager::~CTextManager()
{
 int i;
 for ( i = 0; i < RegTextGetterManagers.GetSize(); i++ ) {
    if ( RegTextGetterManagers[i]!=NULL )
       delete (RegTextGetter *)RegTextGetterManagers[i];
    }
 RegTextGetterManagers.RemoveAll();
 for ( i = 0; i < AspTextGetterManagers.GetSize(); i++ ) {
    if ( AspTextGetterManagers[i]!=NULL )
       delete (AspTextGetter *)AspTextGetterManagers[i];
    }
 AspTextGetterManagers.RemoveAll();
 for ( i = 0; i < ReportGetterManagers.GetSize(); i++ ) {
    if ( ReportGetterManagers[i]!=NULL )
       delete (ReportTextGetter *)ReportGetterManagers[i];
    }
 ReportGetterManagers.RemoveAll();
 if ( bUseDBText == FALSE )
    kill_txptps();
}


int CTextManager::OpenText( char *p )
{
 int i;
 if ( bUseDBText==FALSE )
    return (x_open_files_old(p,2) );
 for ( i = 0; i < RegTextGetterManagers.GetSize(); i++ ) {
    if ( RegTextGetterManagers[i] == NULL ) {
       RegTextGetterManagers.SetAt(i,new RegTextGetter(p,pDatabase));
       return( i );
       }
    }
 RegTextGetterManagers.SetAtGrow(i,new RegTextGetter(p,pDatabase));
 return(i);
}

CTextManager *CTextManager::GetManager()
{
 if (pManager==NULL)
    pManager = new CTextManager();
 return( pManager );
}

int CTextManager::CloseText( int file )
{
 if ( file == -1 )
   return( -1 ); 
 if ( bUseDBText==FALSE ) {
    return( close_files_old(file));
    }
 RegTextGetter *pget = (RegTextGetter *)RegTextGetterManagers[file]; 
 if ( pget == NULL )
    return( -1 );
 delete pget;
 RegTextGetterManagers.SetAt(file,NULL);
 return( 0 );
}


int CTextManager::CloseAspText( int file )
{
 if ( file == -1 )
   return( -1 ); 
 if ( bUseDBText==FALSE )
    return( close_files_old(file) );
 AspTextGetter *pget = (AspTextGetter *)AspTextGetterManagers[file]; 
 if ( pget == NULL )
    return( -1 );
 delete pget;
 AspTextGetterManagers.SetAt(file,NULL);
 return( 0 );
}


int CTextManager::OpenAspectsText( char *p )
{
  int i;
  if ( bUseDBText==FALSE )
     return (x_open_files_old(p,3) );
  for ( i = 0; i < AspTextGetterManagers.GetSize(); i++ ) {
    if ( AspTextGetterManagers[i] == NULL ) {
       AspTextGetterManagers.SetAt(i,new AspTextGetter(p, pDatabase));
       return( i );
       }
    }
 AspTextGetterManagers.SetAtGrow(i,new AspTextGetter(p, pDatabase));
 return(i);
}



int CTextManager::OpenReportText(char *p )
{
 int i;
 if ( bUseDBText == FALSE )
    return( tb_open_file_old(p) );
 for ( i = 0; i < ReportGetterManagers.GetSize(); i++ ) {
    if ( ReportGetterManagers[i] == NULL ) {
       ReportGetterManagers.SetAt(i,new ReportTextGetter(p,pDatabase));
       return( i );
       }
    }
 ReportGetterManagers.SetAtGrow(i,new ReportTextGetter(p,pDatabase));
 return(i);
}



int CTextManager::CloseReport(int rep )
{
 if ( rep == -1 )
   return( -1 ); 
 if ( bUseDBText == FALSE )
    return( tb_close_table_old(rep));
 ReportTextGetter *pget = (ReportTextGetter *)ReportGetterManagers[rep]; 
 if ( pget == NULL )
    return( -1 );
 delete pget;
 ReportGetterManagers.SetAt(rep,NULL);
 return( 0 );
}



const char *CTextManager::GetReportText( int rep, int item, int index )
{
 if ( rep == -1 )
   return( "" ); 
 if ( bUseDBText == FALSE )
    return( tb_get_text_old(rep,item+index));
 ReportTextGetter *pget = (ReportTextGetter *)ReportGetterManagers[rep]; 
 if ( pget == NULL )
    return( "" );
 return( pget->GetText(item,index));
}



int CTextManager::GetReportText( int rep, int item, int index, FILE *stream )
{
 if ( rep == -1 )
   return( 0 ); 
 if ( bUseDBText == FALSE )
    return( tb_write_text_old(stream,rep,item+index));
 ReportTextGetter *pget = (ReportTextGetter *)ReportGetterManagers[rep]; 
 if ( pget == NULL )
    return( 0 );
 return( pget->GetText(item,index,stream));
}



int CTextManager::GetRegText( int txt, int k1, int k2, FILE *stream )
{
if ( txt == -1 )
   return( 0 ); 
if ( bUseDBText == FALSE )
    return( get_transfer_text_asp_old( k1, k2, 0, txt, stream ) );
 RegTextGetter *pget = (RegTextGetter *)RegTextGetterManagers[txt]; 
 if ( pget == NULL )
    return( 0 );
 return( pget->GetText(k1,k2,stream));
}



int CTextManager::GetAspText( int txt, int k1, int k2, int k3, FILE *stream )
{
 if ( txt == -1 )
   return( 0 ); 
 if ( bUseDBText == FALSE )
    return( get_transfer_text_asp_old( k1, k2, k3, txt, stream ));
 AspTextGetter *pget = (AspTextGetter *)AspTextGetterManagers[txt]; 
 if ( pget == NULL )
    return( 0 );
 return( pget->GetText(k1,k2,k3,stream));
}



const char *CTextManager::GetRegText( int txt, int k1, int k2)
{
 if ( txt == -1 )
   return( "" ); 
 if ( bUseDBText == FALSE )
    return( get_text_asp_old( k1, k2, 0, txt ) );
 RegTextGetter *pget = (RegTextGetter *)RegTextGetterManagers[txt]; 
 if ( pget == NULL )
    return( 0 );
 return( pget->GetText(k1,k2));
}


const char *CTextManager::GetAspText( int txt, int k1, int k2, int k3)
{
 if ( txt == -1 )
   return( "" ); 
 if ( bUseDBText == FALSE )
    return( get_text_asp_old( k1, k2, k3, txt ) );
 AspTextGetter *pget = (AspTextGetter *)AspTextGetterManagers[txt]; 
 if ( pget == NULL )
    return( 0 );
 return( pget->GetText(k1,k2,k3));
}


