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
#include "errors.fns"
#include "cJSON.h"
#include "JsonDataReader.h"

JsonDataReader::JsonDataReader()
{
    //ctor
}

JsonDataReader::~JsonDataReader()
{
    //dtor
}


int JsonDataReader::read() {
  char line[100];
  stream = fopen(m_path.c_str(),"r");
  if (stream == NULL) {
     do_error(m_path.c_str());
     return -1;
  }
  long len = fseek(stream, 0, SEEK_END);
  len = ftell(stream);
  fseek(stream, 0, SEEK_SET);
  char *buff = new char[len+10];
  memset(buff,'\0',len+10);
  int read =fread(buff,1,len+1,stream);
  if (read < len) {
     alert_box("Error reading", m_path.c_str());
  }
  fclose(stream);
  const char *endptr;
  cJSON *obj = cJSON_ParseWithOpts(buff, &endptr, 1);
  if (obj == NULL) {
    strcpy(line,cJSON_GetErrorPtr());
    alert_box("Error Parsing",line);
    delete buff;
    return -1;
    }
  else if (obj->child == NULL) {
     alert_box("Error", "No data");
     delete buff;
     return -1;
  }
  delete buff;
  object = obj->child;
  while (object != NULL) {
     if (strcmp(object->string,"Birth")==0 && object->type==cJSON_Object) {
        readBirth(birth_rec,object);
        }
     else if (strcmp( object->string, "Compat") && object->type == cJSON_Object) {
        readBirth(comp_rec, object);
     }
     else if (strcmp( object->string, "Compat") && object->type == cJSON_Object) {
        readBirth(comp_rec, object);
     }
     else if (strcmp( object->string, "Trans") && object->type == cJSON_Object) {
        readBirth(trans_rec, object);
     }
     else if (strcmp( object->string, "BirthRect") && object->type == cJSON_Object) {
        readRect(birth_rectd, object);
     }
     else if (strcmp( object->string, "CompatRect") && object->type == cJSON_Object) {
        readRect(comp_rectd, object);
     }
     else if (strcmp( object->string, "CompatRect") && object->type == cJSON_Object) {
        readRect(comp_rectd, object);
     }
     else if (strcmp( object->string, "TransData") && object->type == cJSON_Object) {
        readTrans(transit_data, object);
     }
     else if (strcmp( object->string, "ProgrData") && object->type == cJSON_Object) {
        readProg(progress_data, object);
     }
     if (object->next != NULL) {
        object = object->next;
     }
     else {
        break;
     }
  }
  delete obj;
  return 0;
}

int JsonDataReader::parseInt( short & num,cJSON *obj  ) {
   if (obj->type ==cJSON_Number) {
      num = obj->valueint;
      return 0;
   }
   else {
      return -1;
   }
}


int JsonDataReader::readBirth(BIRTH_DB &rec, cJSON *child) {
   cJSON *obj = child->child;
   while (obj->next != NULL) {
      if (strcmp(obj->string,"name")==0 && obj->type==cJSON_String) {
         strcpy(rec.name,obj->valuestring);
      }
      if (strcmp(obj->string,"country")==0 && obj->type==cJSON_String) {
         strcpy(rec.country,obj->valuestring);
      }
      if (strcmp(obj->string,"state")==0 && obj->type==cJSON_String) {
         strcpy(rec.state,obj->valuestring);
      }
      if (strcmp(obj->string,"location")==0 && obj->type==cJSON_String) {
         strcpy(rec.location,obj->valuestring);
      }
      if (strcmp(obj->string,"sex")==0 && obj->type==cJSON_Number) {
         parseInt(rec.sex, obj);
      }
      if (strcmp(obj->string,"long")==0 && obj->type==cJSON_String) {
         parseLongLat(rec.birth_data.longitude, obj);
      }
      if (strcmp(obj->string,"lat")==0 && obj->type==cJSON_String) {
         parseLongLat(rec.birth_data.latitude, obj);
      }
      if (strcmp(obj->string,"date")==0 && obj->type==cJSON_String) {
         parseDate(rec.birth_data.birth_date, obj);
      }
      if (strcmp(obj->string,"time")==0 && obj->type==cJSON_String) {
         parseTime(rec.birth_data.birth_time, obj);
      }
      if (strcmp(obj->string,"tzhours")==0 && obj->type==cJSON_Number) {
         parseInt(rec.birth_data.hour_adjust, obj);
      }
      if (strcmp(obj->string,"tzminutes")==0 && obj->type==cJSON_Number) {
         parseInt(rec.birth_data.hour_adjust, obj);
      }
      obj=obj->next;
   }
   return 0;
}

int JsonDataReader::parseDate(DATES &date, cJSON *obj ) {
   if (obj->type == cJSON_String) {
        return sscanf(obj->valuestring,"%hd/%hd/%hd", &date.month, &date.day, &date.year );
   }
   else {
      return -1;
   }
}

int JsonDataReader::parseTime(TIM &time,cJSON *obj ) {
   if (obj->type == cJSON_String) {
      return sscanf(obj->valuestring, "%hd:%hd:%hd",&time.hours,&time.minutes,&time.seconds);
      }
   else {
      return -1;
   }
}


int JsonDataReader::parseLongLat(DEG_MIN &degs, cJSON *obj ) {
   char buf[5];
   if (obj->type == cJSON_String) {
        int ret = sscanf(obj->valuestring, "%hd %hd %s", &degs.degrees, &degs.minutes, buf);
        degs.dir = buf[0];
        return ret;
   }
   else {
        return -1;
   }
}


int JsonDataReader::readRect(RECT_DATA &rect, cJSON *child ) {
  return 0;
}


int JsonDataReader::readTrans(TRANS_DATA &trans, cJSON *child ) {
  return 0;
}


int JsonDataReader::readProg(PROGR_DATA &prog, cJSON * child) {
  return 0;
}


int JsonDataReader::readReloc(LOC_DB &reloc, cJSON *child) {

}
