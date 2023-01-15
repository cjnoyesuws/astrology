// TextManager.cpp: implementation of the CTextManager class.
//
//////////////////////////////////////////////////////////////////////

#include "sqlite3pp.h"
#include "TextGetter.h"
#include "TextManager.h"
#include "errors.fns"
#include "vector"
#include "exception"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void kill_txptps();

bool bHasLanguage = false;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

std::string configDir;

TextManager *pManager;


void TextManager::setConfig(ConfigData &config) {
 std::string db = config.getDataDir() + "/" + config.getReportDb();
 configDir = db;
}

TextManager::TextManager(ConfigData &config)
{
 std::string db = config.getDataDir() + "/" + config.getReportDb();
 configDir = db;
 m_database = new sqlite3pp::database(db.c_str());
 m_regTextGetters.resize(10);
 m_reportGetters.resize(10);
 m_aspTextGetters.resize(10);
 std::string str = "dummy";
 openText(str);
 //make sure position 0 is occupied;
 pManager = this;
 }

TextManager::TextManager()
{
  if (configDir == NULL || configDir.length() == 0) {
    throw std::invalid_argument("No config dir set");
  }
  TextManager *pManager = new TextManager();
  sqlite3pp::database *pDatabase = new sqlite3pp::database(configDir.c_str());
  pManager->setDb(pDatabase);
}


int TextManager::openText(std::string type )
{
   int pos = m_regTextGetters.size();
   m_regTextGetters[pos] = new RegTextGetter(m_database, type);
   return pos;
}

TextManager *TextManager::getManager(ConfigData &config)
{
 pManager = new TextManager(config);
 return( pManager );
}

int TextManager::closeText( int file )
{
 if ( file == -1 )
   return( -1 );
 m_regTextGetters[file]->close();
 return( 0 );
}


int TextManager::closeAspText( int file )
{
 if ( file == -1 )
   return( -1 );
  m_aspTextGetters[file]->close();
  return( 0 );
}



int TextManager::openAspectsText( std::string type )
{
  int pos;
  pos = m_aspTextGetters.size();
  m_aspTextGetters[pos] = new AspTextGetter(&getDb(),type);
  return(pos);
}



int TextManager::openReportText( std::string type )
{
 int pos;
 pos = m_reportGetters.size();
 m_reportGetters[pos] = new ReportTextGetter(&getDb(), type);
 return(pos);
}



int TextManager::closeReport(int rep )
{
 if ( rep == -1 )
   return( -1 );
 m_reportGetters[rep]->close();
 return( 0 );
}


const char *TextManager::getReportText( int rep, int item, int index )
{
 if ( rep == -1 )
    return("");
 if (rep > m_reportGetters.size()) {
    throw std::out_of_range("report text");
 }/
 ReportTextGetter *ref = m_reportGetters[rep];
 if (ref->m_open == false ) {
    throw std::domain_error("File is closed");
 }
 std::string str = ref->getText(item,index);
 return str.c_str();
}


const char *TextManager::getRegText( int txt, int k1, int k2)
{
 if ( txt == -1 )
    return( 0 );
 if (txt == 0) {
    throw std::out_of_range("Unintialized reg text");
 }
 if (txt > m_reportGetters.size()) {
    throw std::out_of_range("reg text");
 }

 RegTextGetter *ref = m_regTextGetters[txt];
 if (ref->m_open == false ) {
    throw std::domain_error("File is closed");
 }
 std::string str = ref->GetText(k1, k2);
 return str.c_str();
 }


const char *TextManager::getAspText( int txt, int k1, int k2, int k3)
{
 if ( txt == -1 )
    return( 0 );
 if (txt == 0) {
    throw std::out_of_range("Unintialized Asp text");
 }
 if (txt > m_aspTextGetters.size()) {
    throw std::out_of_range("asp text");
 }
 AspTextGetter *ref = m_aspTextGetters[txt];
 if (ref->m_open == false ) {
    throw std::domain_error("File is closed");
 }
 std::string str = ref->GetText(k1,k2,k3));
 return str.c_str();
}

