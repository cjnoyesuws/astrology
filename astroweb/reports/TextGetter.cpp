#include "stdafx.h"
#include "TextGetter.h"
#include "errors.fns"
#include "report_def.h"
#include <assert.h>
#include <map>
#include <utility>
#include <string>
#include "sqlite3pp.h"

extern bool bHasLanguage;
#define LEN_COUNT 13
static short array_ids[] = {ST__MONTH,ST__SIGN,ST__PLANET,ST__NUMBERS,ST__ASPECTS,
ST__SIGN3, ST__ERROR, ST__HOUSE_MODES,ST__SIDE_TROP,ST__RETROGRADE,ST__RECT_METH,
TR__AFFECTS, ST__ARABN};
static short array_size[] = {13,13,60,12,13,13,6,13,3,4,6,13,150};

std::string GenericTextGetter::query( const char *sql )
{
 std::string value="";

  sqlite3pp::query qry(*getDb(),  sql);
  printf(sql);
 for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
     (*i).getter() >> value;
 }
 return value;
}

std::string RegTextGetter::getText( int k1, int k2 )
{
  char sqlbuf[200];

  sprintf( sqlbuf, "select Text from %s where TextType='%s' and Key1num=%d and Key2num=%d",getTable().c_str(), getTextType().c_str(), k1, k2 );
  std::string text = query(sqlbuf);
  return text;
}


std::string AspTextGetter::getText( int k1, int k2, int k3 )
{
  char sqlbuf[200], altbuf[100];
  std::string value1, value2;
  sprintf( sqlbuf, "select Text from %s where TextType='%s' and Planet1num=%d and Planet2num=%d and AspectNum=%d", m_table.c_str(), m_textType.c_str(), k1, k2, k3 );
  sprintf( altbuf, "select Text from %s where TextType='%s' and Planet2num=%d and Planet1num=%d and AspectNum=%d", m_table.c_str(), m_textType.c_str(), k1, k2, k3 );
  value1 = query(sqlbuf);
  value2 = query(altbuf);
  if (value1.length() > 0) {
     return value1;
  }
  else if (value2.length() > 0) {
     return value2;
  }
  else {
     return std::string("");
  }
}

std::string ReportTextGetter::getText( int k1, int ind )
{
 char sqlbuf[200];
 sprintf(sqlbuf,"select Text from %s where TextType='%s' and iTextKey=%d and iIndex=%d", m_table.c_str(), m_textType.c_str(), k1, ind );
 std::string value = query(sqlbuf);
 return value;
}

