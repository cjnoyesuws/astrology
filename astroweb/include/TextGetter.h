#include <string>
#include "sqlite3.h"
#include "sqlite3pp.h"


class GenericTextGetter {

  public:
  GenericTextGetter(sqlite3pp::database *db, std::string textType) {
      m_textType = textType;
      m_pDb = db;
      m_open = true;
  }

  std::string getTextType() { return m_textType; }
  std::string getTable() { return m_table; }
  std::string query( const char *sql );
  sqlite3pp::database *getDb() { return m_pDb; }
  void close() { m_open = false; }


  virtual ~GenericTextGetter() {}

  protected:
  sqlite3pp::database *m_pDb;
  bool m_open;
  std::string m_table;
  std::string m_textType;

};

class RegTextGetter : public GenericTextGetter {

public:
RegTextGetter( sqlite3pp::database *db, std::string textType) : GenericTextGetter(db, textType) { m_table = "RegularText"; }
virtual ~RegTextGetter() {}
std::string getText( int k1, int k2 );
};


class AspTextGetter : public GenericTextGetter {

public:
AspTextGetter( sqlite3pp::database *db, std::string textType) : GenericTextGetter(db, textType) { m_table = "AspectText"; }
virtual ~AspTextGetter() {}
std::string getText( int k1, int k2, int k3 );


};

class ReportTextGetter : public GenericTextGetter {
public:
ReportTextGetter( sqlite3pp::database *db, std::string textType) : GenericTextGetter(db, textType) { m_table = "ReportText"; }
virtual ~ReportTextGetter() {}
std::string getText( int k1, int ind );




};

