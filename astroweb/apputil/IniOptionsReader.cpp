
#include <string>
#include <cstring>
#include "setup.hpp"
#include "AbstractReader.h"
#include "IniOptionsReader.h"
#include <stdio.h>
#include "errors.fns"
#include "ConfigHelper.h"

extern char *strclip(char *pStr);

using namespace std;
using std::string;

int IniOptionsReader::read() {

FILE *stream;
int num=-1;
char buf[60];
char *line;
char key[32], val[32];
memset(key,0,32);
memset(val,0,32);
stream = fopen(m_path.c_str(),"rt");
ConfigHelper hlpr;
if (stream == NULL) {
   do_error(m_path.c_str());
   return -1;
}
while (!feof(stream) && !ferror(stream)) {
   line = fgets(buf,59,stream);
   if (line == NULL) {
        break;
   }
   line = strclip(line);
   char *pos = strchr(line,'=');
   *pos = '\0';
   strcpy(key,line);
   pos++;
   strcpy(val,strclip(pos));
   if (atoi(val) > 0) {
      num = atoi(val);
   }
   if (strcmp(key,"houses")==0) {
      if (num > -1) {
         m_options.setHouseMode(num);
      }
      else {
         m_options.setHouseMode(hlpr.findHouses(val));
      }
   }
   if (strcmp(key,"code")==0) {
      if (num > -1) {
          m_options.setChartCode(num);
      }
      else {
          m_options.setChartCode(hlpr.findChartCode(val));
      }
   }
   if (strcmp(key,"flags")==0) {
      if (num > -1) {
         m_options.setFlags(num);
      }
      else {
          m_options.setFlags(hlpr.parseFlags(val));
      }
   }
   if (strcmp(key,"rect")==0) {
      if (num > -1) {
         m_options.setDefRectMethod(num);
      }
      else {
         m_options.setDefRectMethod(hlpr.findRect(val));
      }
   }
   if (strcmp(key,"datafile")==0) {
       m_options.setDatafile(num);
   }
   if (strcmp(key,"charts")==0) {
       m_options.getCharts() = num;
   }
   if (strcmp(key,"format")==0) {
      m_options.setFormat(val);
   }
}
fclose(stream);
return 0;
}
