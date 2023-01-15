#ifndef _DIREC____HPP_
#define _DIREC____HPP_

#include "paths.hpp"

class Directories {
CString main;
CString help;
CString db;
CString data;
CString user;
CString temp;
CString dbName;
CString txtdbName;
BOOL    bAccess97;
BOOL    bDatabaseText;
public:
#ifndef INSTCALC
	  CDaoWorkspace m_workspace;
	  CDaoDatabase *m_pDatabase;
	  CDaoDatabase *m_pTextDatabase;
#endif
      Directories() {}
      ~Directories(); 
      CString &getMain() {return main;}
      CString &getHelp() {return help;}
      CString &getDB()   {return db;}
      CString &getData() {return data;}
      CString &getUser() {return user;}
      CString &getTemp() {return temp;}
      void setMain(char *s) {main = s;}
      void setHelp(char *s) {help = s;}
      void setDB(char *s)   {db = s;}
      void setData(char *s) {data = s;}
      void setUser(char *s) {user = s;}
      void settemp(char *s) {temp = s;}
      int saveToIni();
      int getFromIni();
      CString getProgDefDir();
	  CString getDataDefDir();
      CString &getDbName() { return dbName; }
	  CString &getTxtDbName() { return txtdbName; }
      BOOL &getAccess97() { return bAccess97; }
      BOOL &getDatabaseText() { return bDatabaseText; }
      void CloseDb();
	  void ReopenDb();
};

extern Directories theDirectories;

extern CString GetDatabaseName();
extern CString GetTextDatabaseName();
CString &GetCurLanguage();

/* class DirectDlgf : public FormDlgf {
public:
      DirectDlgf(zWindow *pPar, Directories *d);
      ~DirectDlgf() { }
      };
*/
#endif /*  _DIREC____HPP_  */
