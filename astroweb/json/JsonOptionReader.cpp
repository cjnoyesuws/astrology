#include <cstring>
#include "setup.hpp"
#include "rapidjson/reader.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "errors.fns"
#include "ConfigHelper.h"
#include "JsonOptionReader.h"


using namespace rapidjson;
using namespace std;
extern char *strclip( char *pStr );


JsonOptionReader::JsonOptionReader(const JsonOptionReader& other)
{
   m_path = other.m_path;
   read();
}

int JsonOptionReader::read()
{
    char * buff = new char[4096];
    char * line = new char[125];
    FILE *stream = fopen(m_path.c_str(),"rt");
    if (stream == NULL) {
        do_error(m_path.c_str());
        return -1;
    }
    strcpy(buff,"");
    while (!feof(stream)) {
      char * read =fgets(line,124,stream);
      if (read == NULL && !feof(stream)) {
         do_error(m_path.c_str());
         fclose(stream);
         return -1;
      }
      else  if (read != NULL){
        strclip(read);
        strcat(buff,read);
      }
    }

    strclip(buff);
    fclose(stream);
    Reader reader;
    StringStream ss(buff);
    OptionsHandler handler;
    reader.Parse(ss, handler);
    m_options = static_reader.getOptions();
    delete buff;
    return 0;
}

int JsonOptionReader::handleKey(const char *key, const char *val) {
   ConfigHelper h;
   int value = atoi(val);
   if (strcmp(key,"flags")==0) {
        if (value > 0) {
           m_options.getOpt().flags = value;
        }
        else {
           m_options.getOpt().flags = h.parseFlags(val);
        }
        return 1;
    }
    else if (strcmp(key,"houses")==0) {
        if (value > 0) {
           m_options.getOpt().house_mode  = value;
        }
        else {
           m_options.getOpt().house_mode  = h.findHouses(val);
        }
        return 2;
    }
    else if (strcmp(key, "charts")==0) {
        if (value > 0) {
           m_options.getOpt().chart_code =value;
        }
        else {
           m_options.getOpt().chart_code =h.findChartCode(val);
        }
        return 3;
    }
    else if (strcmp(key,"code")==0) {
        if ( value > 0 ) {
           m_options.getOpt().chart_code = value;
        }
        else {
            m_options.getOpt().chart_code = h.findChartCode(val);
        }
        return 4;
    }
    else if (strcmp(key,"rectify")==0) {
        if (value != -1 ) {
            m_options.getOpt().def_rectmethod = value;
        }
        else {
            m_options.getOpt().def_rectmethod = h.findRect(val);
        }
        return 5;
    }
    else if (strcmp(key,"format")==0) {
        m_options.setFormat(val);
    }
}


int JsonOptionReader::handleKey(const char *key, unsigned int val) {
    if (strcmp(key,"flags")==0) {
        m_options.getOpt().flags=val;
        return 1;
    }
    else if (strcmp(key,"houses")==0) {
        m_options.getOpt().house_mode = (short)val;
        return 2;
    }
    else if (strcmp(key, "charts")==0) {
        m_options.getOpt().charts = (short)val;
        return 3;
    }
    else if (strcmp(key,"code")==0) {
        m_options.getOpt().chart_code = val;
        return 4;
    }
    else if (strcmp(key,"rectify")==0) {
        m_options.getOpt().def_rectmethod = val;
        return 5;
    }
    else if (strcmp(key,"datafile")==0) {
        m_options.getOpt().datafile = val;
        return 6;
    }

}


