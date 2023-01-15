// TextManager.h: interface for the CTextManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTMANAGER_H__4F3FA750_D8D3_446B_9863_FCF3FC9B583C__INCLUDED_)
#define AFX_TEXTMANAGER_H__4F3FA750_D8D3_446B_9863_FCF3FC9B583C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ConfigData.h"
#include "TextGetter.h"


class TextManager
{
friend class RegTextGetter;
friend class GenericTextGetter;
friend class AspTextGetter;
friend class ReportTextGetter;
protected:
   sqlite3pp::database *m_database;
   sqlite3pp::database &getDb() { return *m_database;}
public:
   TextManager(ConfigData &config);
   TextManager();
   void setDb(sqlite3pp::database *database) {
      m_database = database;
   }
   vector<RegTextGetter *> m_regTextGetters;
   vector<AspTextGetter *> m_aspTextGetters;
   vector<ReportTextGetter *> m_reportGetters;
   static void setConfig(ConfigData &config);
   static TextManager *getManager(ConfigData &config);
   static TextManager *getManager();
   virtual ~TextManager() {}
   int openText( std::string type );
   int closeText( int file );
   int closeAspText( int file );
   int openAspectsText( std::string type );
   int openReportText( std::string type );
   int closeReport(int rep );
   const char *getReportText( int rep, int item, int index );
   const char *getRegText( int txt, int k1, int k2);
   const char *getAspText( int txt, int k1, int k2, int k3);
};

extern TextManager *Manager;

#endif // !defined(AFX_TEXTMANAGER_H__4F3FA750_D8D3_446B_9863_FCF3FC9B583C__INCLUDED_)
