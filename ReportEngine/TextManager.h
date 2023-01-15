// TextManager.h: interface for the CTextManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTMANAGER_H__4F3FA750_D8D3_446B_9863_FCF3FC9B583C__INCLUDED_)
#define AFX_TEXTMANAGER_H__4F3FA750_D8D3_446B_9863_FCF3FC9B583C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning( disable : 4995 )

class CTextManager  
{
protected:
   BOOL bUseDBText;
   CTextManager();
   CPtrArray RegTextGetterManagers;
   CPtrArray AspTextGetterManagers;
   CPtrArray ReportGetterManagers;
   CDaoDatabase *pDatabase;
public:
	static CTextManager *GetManager();
	virtual ~CTextManager();
   int OpenText( char *p );
   int CloseText( int file );
   int CloseAspText( int file );
   int OpenAspectsText( char *p );
   int OpenReportText(char *p );
   int CloseReport(int rep );
   const char *GetReportText( int rep, int item, int index );
   int GetReportText( int rep, int item, int index, FILE *stream );
   int GetRegText( int txt, int k1, int k2, FILE *stream );
   int GetAspText( int txt, int k1, int k2, int k3, FILE *stream );
   const char *GetRegText( int txt, int k1, int k2);
   const char *GetAspText( int txt, int k1, int k2, int k3);
};

extern CTextManager *pManager;

#endif // !defined(AFX_TEXTMANAGER_H__4F3FA750_D8D3_446B_9863_FCF3FC9B583C__INCLUDED_)
