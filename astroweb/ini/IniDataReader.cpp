#include <string>
#include <stdio.h>
#include <cstring>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "stdlib.h"
#include <string>
#include "AbstractReader.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "IniDataReader.h"
#include "errors.fns"

using namespace std;
using std::string;

extern char *strclip(char *pStr);


int IniDataReader::readBirth(BIRTH_DB &rec) {
   int rsp;
   while ((rsp=readLine())==VARIABLE_RD) {
      if (strlen(value)==0) {
         continue;
      }
      if (strcmp(key,"name")==0) {
         strcpy(rec.name,value);
      }
      if (strcmp(key,"country")==0) {
         strcpy(rec.country,value);
      }
      if (strcmp(key,"state")==0) {
         strcpy(rec.state,value);
      }
      if (strcmp(key,"location")==0) {
         strcpy(rec.location,value);
      }

      if (strcmp(key,"date")==0) {
         parseDate(rec.birth_data.birth_date);
      }
      else if (strcmp(key,"time")==0) {
         parseTime(rec.birth_data.birth_time);
      }
      else if (strncmp(key,"long",4)==0) {
         parseLongLat(rec.birth_data.longitude,0);
      }
      else if (strncmp(key,"lat",3)==0) {
         parseLongLat(rec.birth_data.latitude,1);
      }
      else if (strcmp(key,"tzhours")==0) {
         parseInt(rec.birth_data.local_minutes);
      }
      else if (strcmp(key,"tzminutes")==0) {
         parseInt(rec.birth_data.local_minutes);
      }
      else if (strcmp(key,"sex")==0) {
         parseInt(rec.sex);
      }
      else if (strcmp(key,"time_zone")==0) {
         parseInt(rec.time_zone);
      }
      else if (strcmp(key,"special_code")==0) {
         parseInt(rec.special_code);
      }
   }
   return END_SECTION_RD;
}

int IniDataReader::parseDate(DATES &date) {
  return sscanf(value,"%hd/%hd/%hd", &date.month, &date.day, &date.year );
}

int IniDataReader::parseTime(TIM &time) {
  return sscanf(value, "%hd:%hd:%hd",&time.hours,&time.minutes,&time.seconds);
}

int IniDataReader::parseLongLat(DEG_MIN &degs, int lat) {
  char buf[5];
  int ret = sscanf(value, "%hd %hd %s", &degs.degrees, &degs.minutes, buf);
  degs.dir = buf[0];
  return VARIABLE_RD;
}

int IniDataReader::readRect(RECT_DATA &rect) {
  int rsp;
  while ((rsp=readLine())!=END_RD) {
      if (strlen(value)==0) {
         continue;
      }
      if (strcmp(key,"known")==0) {
         parseInt(rect.birth_time_known);
      }
      else if (strcmp(key,"system")==0) {
         parseInt(rect.rect_system);
      }
   }
   return END_SECTION_RD
}

int IniDataReader::readTrans(TRANS_DATA &trans) {
   int rsp;
   while ((rsp=readLine())!=END_RD) {
   }
   return END_SECTION_RD;
}


int IniDataReader::readProg(PROGR_DATA &prog) {
   int rsp;
  while ((rsp=readLine()) != END_RD) {
      if (strlen(value)==0) {
         continue;
      }
      if (strcmp(key,"date")==0) {
         parseDate(prog.offset);
      }
      else if (strcmp(key,"system")==0) {
         parseInt(prog.progress_system);
      }
   }
   return END_SECTION_RD;
}

int IniDataReader::readReloc(LOC_DB &rec)
{
   int rsp;
   while ((rsp=readLine())!= END_RD) {
    if ( strlen(value)==0 ) {
       continue;
    }
    if (strcmp(key,"country")==0) {
         strcpy(rec.country,value);
      }
      if (strcmp(key,"state")==0) {
         strcpy(rec.state,value);
      }
      if (strcmp(key,"location")==0) {
         strcpy(rec.location,value);
      }
    if(strncmp(key,"long",4)==0) {
        parseLongLat(rec.longitude,0);
    }
    else if (strncmp(key,"lat",3)==0) {
        parseLongLat(rec.latitude,1);
    }
    else if (strcmp(key,"tzhours")==0) {
        parseInt(rec.hrs_offset);
    }
    else if (strcmp(key,"tzminutes")==0) {
        parseInt(rec.min_offset);
    }
    else if (strcmp(key,"time_zone")==0) {
         parseInt(rec.time_zone);
      }
      else if (strcmp(key,"special_code")==0) {
         parseInt(rec.special_code);
      }
   }
   return END_SECTION_RD;
}

int IniDataReader::readLine() {
   char buf[150];
   char * line;
   line = fgets(buf,150, stream);
   if (line ==NULL) {
      return END_RD;
   }
   line = strclip(line);
   if (line ==NULL) {
      return END_RD;
   }
   int len  = strlen(line);
   if (line == NULL && !feof(stream)) {
      do_error(m_path.c_str());
      return ERROR_RD;
   }
   if (strlen(line)==0) {
      return COMMENT_RD;
   }
   else if (feof(stream)) {
      fclose(stream);
      return END_RD;
   }
   if (line[0]=='[') {
      char *end = strchr(line,']');
      if (end !=NULL) {
         *end='\0';
      }
      strcpy(section,&line[1]);
      return SECTION_RD;
   }
   else {
      char *sep = strchr(line,'=');
      if (sep == NULL) {
         do_error("= between key and value is required");
         return ERROR_RD;
      }
      strcpy(value,sep+1);
      *sep = '\0';
      strcpy(key,line);
      return VARIABLE_RD;
   }
   return ERROR_RD;
}


int IniDataReader::read() {
  stream = fopen(m_path.c_str(),"r");
  if (stream == NULL) {
     do_error(m_path.c_str());
     return -1;
  }
  int response;
  response = readLine();
  if (response ==ERROR_RD) {
     do_error(m_path.c_str());
     fclose(stream);
     stream = NULL;
     return -1;
  }
  while (response != END_RD) {
     switch (response) {
     case SECTION_RD:
        if (strcmp(section,"Birth")==0) {
            readBirth(birth_rec);
        }
        else if (strcmp(section,"Comp")==0) {
            readBirth(comp_rec);
        }
        else if (strcmp(section,"Trans")==0) {
            readBirth(trans_rec);
        }
        else if (strcmp(section,"BirthRect")==0) {
            readRect(birth_rectd);
        }
        else if (strcmp(section,"CompRect")==0) {
            readRect(comp_rectd);
        }
        else if (strcmp(section,"TransData")==0) {
            readTrans(transit_data);
        }
        else if (strcmp(section,"ProgrData")==0) {
            readProg(progress_data);
        }
        else if (strcmp(section,"RelocData")==0) {
            readReloc(reloc_data);
        }
        break;
            case VARIABLE_RD:
            if (strcmp(section,"Birth")==0) {
                readBirth(birth_rec);
            }
            else if (strcmp(section,"Comp")==0) {
                readBirth(comp_rec);
            }
            else if (strcmp(section,"Trans")==0) {
                readBirth(trans_rec);
            }
            else if (strcmp(section,"BirthRect")==0) {
                readRect(birth_rectd);
            }
            else if (strcmp(section,"CompRect")==0) {
                readRect(comp_rectd);
            }
            else if (strcmp(section,"TransData")==0) {
                readTrans(transit_data);
            }
            else if (strcmp(section,"ProgrData")==0) {
                readProg(progress_data);
            }
            else if (strcmp(section,"RelocData")==0) {
                readReloc(reloc_data);
            }
        break;
            case COMMENT_RD:
        break;
            case END_RD:
        break;
    }
    response=readLine();
  }
  return 0;
}
