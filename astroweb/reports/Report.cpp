#include "Report.h"
#include "ReportManager.h"
#include "TextManager.h"
#include "ReportConfig.h"
#include "ConfigData.h"
#include <exception>
#include "cJSON.h"
#include "report_def.h"
#include "aspect.h"
#include "misccalc.h"

Report::Report()
{

}

Report::Report(ConfigData &configData, ReportConfig &reportConfig)
{
  m_rConfig = configData;
  m_rReportConfig = reportConfig;
  m_name = reportConfig.getName();
  m_comments = reportConfig.getComments();
  m_ext = reportConfig.getExt();
  m_path = reportConfig.getReportPath();
  m_type = reportConfig.getType();
  m_pDocument = cJSON_CreateObject();
  m_pReport = cJSON_CreateObject();
  m_pBody = cJSON_CreateObject();
}


Report::~Report()
{
   if (m_pStream != NULL) {
      fclose(m_pStream);
   }
   if (m_pReportManager != NULL) {
      delete m_pReportManager;
   }
   if (m_pTextManager != NULL) {
      delete m_pTextManager;
   }

   delete m_pDocument;
   delete m_pBody;
   delete m_pReport;

}


bool Report::open() {
  char buf[256];
  m_pStream = fopen(m_path.c_str(),"wt");
  if (m_pStream == NULL) {
     sprintf(buf,"Can't Open %s", m_path.c_str());
     throw new std::domain_error(buf);
  }
  if (ferror(m_pStream)) {
     return false;
  }
  else {
     return true;
  }
}

cJSON *Report::getMetadata() {
    cJSON *pEle;
    cJSON *pObject = cJSON_CreateObject();
    pEle = cJSON_CreateString(m_name.c_str());
    cJSON_AddItemToObject(pObject, "name", pEle);
    pEle = cJSON_CreateString(m_comments.c_str());
    cJSON_AddItemToObject(pObject, "comments", pEle);
    pEle = cJSON_CreateString(m_type.c_str());
    cJSON_AddItemToObject(pObject, "type", pEle);
    return pObject;
}

bool Report::writeDocument() {
   cJSON_AddItemToObject(m_pReport,"body", m_pBody);
   cJSON_AddItemToObject(getMetadata(),"metadata",m_pDocument);
   cJSON_AddItemToObject(m_pDocument,"report",m_pReport);
   char *content = cJSON_Print(m_pDocument);
   fwrite(content, 1, strlen(content), m_pStream);
   delete content;
   return true;
}

bool Report::addBodyItem(cJSON *item, char *key) {
   cJSON_AddItemToObject(item, key, m_pBody);
   return true;
}

bool Report::addText( char *text, char *key) {
   cJSON_AddStringToObject(m_pBody,key, text);
   return true;
}

bool Report::generateReport() {
   if (open()) {
      if (writeDocument()) {

      }
      close();
      return true;
   }
   else {
      return false;
   }
}

bool Report::commit(char *key) {
   std::string str = m_pReportManager->getBuffer();
   addText((char *)str.c_str(),key);
   return true;
}



/* functions to print out summary */
#define SENSE  2
#define THRESH 11

/* function that tests value and determines which is larger. The function
   is initialized with tval == -1. When setting data pointers are set to
   NULL. Use index == -1 to evaluate data. ret & ret2 return index
   associated with tval. If ret2 == -1 then it should be ignored. ret == 0
   indicates a balanced state
*/

void testval( int tval, int index, int *ret, int *ret2 )
{
 static int vals[14], indexes[14];
 int i, j, temp, entries;

 if ( tval == -1 ) {
    entries = 0;
    return;
    }
 else if ( index != -1 ) {
   vals[entries] = tval;
   indexes[entries] = index;
   ++entries;
   return;
   }
 for ( i = 0; i < entries -1; ++i ) {      /* sort list */
     for ( j = i+1; j < entries; ++j ) {
	 if ( vals[j] > vals[i] ) {
	    temp = vals[i];
	    vals[i] = vals[j];
	    vals[j] = temp;
	    temp = indexes[i];
	    indexes[i] = indexes[j];
	    indexes[j] = temp;
	    }
	 }
     }
 if ( entries == 2 ) {
    if ( vals[0] - SENSE > vals[1]  ) {
       *ret = indexes[0];
       *ret2 = -1;
       return;
       }
    else {
       *ret = 0;
       *ret2 = -1;
       }
    }
 else if ( vals[0] - SENSE > vals[1] || vals[1] - SENSE > vals[2] ) {
    *ret = indexes[0];
    if ( vals[1] - SENSE > vals[2] ) {
       *ret2 = indexes[1];
       return;
       }
    else
       *ret2 = -1;
    }
 else {
    *ret = 0;
    *ret2 = -1;
    }
 if ( *ret == 0 && vals[0] >= THRESH )
    *ret = indexes[0];
 else if ( *ret2 == -1 && vals[1] >= THRESH )
    *ret = indexes[1];
}

/* macros to make calling testval() easier */


#define inittv() testval( -1, 0, NULL, NULL )
#define addtv(a,b) testval( a, b, NULL, NULL )
#define gettv() testval( 0, -1, &index, &index2 )


bool Report::printSummary() {
{
 char *name = (char *)getReportConfig().getName();
 char *comments = (char *)getReportConfig().getComments();
 char *text;
 const char *report;
 int file = -1, index, index2;

 if ( getReportConfig().getMode() & TEXT ) {
    if ( ( m_summary = getReportManager()->getTextManager()->openText("SUMMARY") ) == -1 )
       getReportConfig().getMode() &= ( 0xffff ^ TEXT );
    }
 if ( getReportConfig().getMode() & HOUSES ) {
    if ( ( report = getReportManager()->getKey( CHS_SCOUT_PL, 0 ) ) == NULL ) {
       return false;
       }
    else
       getReportManager()->scoutPlanet((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), scout_planet, (char *)report);
    if ( getReportConfig().getMode() & TEXT ) {
       text = getReportManager()->getTextManager()->getRegText(m_summary, 5, scout_planet);
       getReportManager()->getStream() << text;
       }
       commit((char *)"scout_planet");
    }
    if ( ( report = getReportManager()->getKey(CHS_SUMARY_TITLE, 0 ) ) == NULL ) {
    return false;
    }
 else
    getReportManager()->title( (char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), "", (char *)report );
 if ( ( report = getReportManager()->getKey(CHS_SIGN_COUNT, 0 ) ) == NULL ) {
    return false;
    }
 else
    getReportManager()->signCount((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
/*
 if ( mode & TEXT ) {
    inittv();
    addtv( sign_count[ARIES], ARIES+1 );
    addtv( sign_count[TAURUS], TAURUS+1 );
    addtv( sign_count[GEMINI], GEMINI+1 );
    addtv( sign_count[CANCER], CANCER+1 );
    addtv( sign_count[LEO], LEO+1 );
    addtv( sign_count[VIRGO], VIRGO+1 );
    addtv( sign_count[LIBRA], LIBRA+1 );
    addtv( sign_count[SCORPIO], SCORPIO+1 );
    addtv( sign_count[SAGITARIUS], SAGITARIUS+1 );
    addtv( sign_count[CAPRICORN], CAPRICORN+1 );
    addtv( sign_count[AQUARIUS], AQUARIUS+1 );
    addtv( sign_count[PISCES], PISCES+1 );
    gettv();
    --index;
    if ( index != -1 )
       get_transfer_text( 0, index, file, stream );
    if ( index2 != -1 )
       get_transfer_text( 0, index2, file, stream );
    }
*/
 if ( ( report = getReportManager()->getKey( CHS_GENDER_COUNT, 0 ) ) == NULL ) {
    return false;
    }
 else
     getReportManager()->summGenders((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
 if ( getReportConfig().getMode() & TEXT ) {
    inittv();
    addtv( genders.feminine, 2 );
    addtv( genders.masculine, 1 );
    gettv();
    text = (char *)getReportManager()->getTextManager()->getRegText(m_summary, 2, index);
    getReportManager()->getStream() << text;
    commit("genders");
    }

 if ( ( report = getReportManager()->getKey( CHS_ELEMENT_COUNT, 0 ) ) == NULL ) {
    return false;
    }
 else
    getReportManager()->summElements((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
 if ( getReportConfig().getMode() & TEXT ) {
    inittv();
    addtv( elements.fire, 1 );
    addtv( elements.earth, 2 );
    addtv( elements.air, 3 );
    addtv( elements.water, 4 );
    gettv();
    text = (char *)getReportManager()->getTextManager()->getRegText(m_summary, 1, index);
    getReportManager()->getStream() << text;
    if ( index2 != -1 )
        text = (char *)getReportManager()->getTextManager()->getRegText(m_summary, 1, index2);
        getReportManager()->getStream() << text;
        commit("elements");
    }
 if ( ( report = getReportManager()->getKey(CHS_QUALITIES_COUNT, 0 ) ) == NULL ) {
    return false;
    }
 else
    getReportManager()->summQualities((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
 if ( getReportConfig().getMode() & TEXT ) {
    inittv();
    addtv( qualities.cardinal, 1 );
    addtv( qualities.fixed, 2 );
    addtv( qualities._mutable, 3 );
    gettv();
    text = (char *)getReportManager()->getTextManager()->getRegText(m_summary, 3, index);
    getReportManager()->getStream() << text;
    if ( index2 != -1 )
        text = getReportManager()->getTextManager()->getRegText(m_summary, 3, index2);
        getReportManager()->getStream() << text;
        commit("qualities");
    }

 if ( getReportConfig().getMode() & HOUSES ) {
    if ( ( report = getReportManager()->getKey(CHS_HOUSE_COUNT, 0 ) ) == NULL ) {
        return false;
       }
    else {
       getReportManager()->houseCount((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
    }
/*
    if ( mode & TEXT ) {
       inittv();
       addtv( house_count[1], 1 );
       addtv( house_count[2], 2 );
       addtv( house_count[3], 3 );
       addtv( house_count[4], 4 );
       addtv( house_count[5], 5 );
       addtv( house_count[6], 6 );
       addtv( house_count[7], 7 );
       addtv( house_count[8], 8 );
       addtv( house_count[9], 9 );
       addtv( house_count[10], 10 );
       addtv( house_count[11], 11 );
       addtv( house_count[12], 12 );
       gettv();
       --index;
       if ( index != -1 )
	  get_transfer_text( 0, index, file, stream );
       if ( index2 != -1 )
	  get_transfer_text( 0, index2, file, stream );
       }
*/
    if ( ( report = getReportManager()->getKey( CHS_HEMISPHERES_COUNT, 0 ) ) == NULL ) {
       return false;
       }
    else
       getReportManager()->summHemispheres((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
    if ( getReportConfig().getMode() & TEXT ) {
       inittv();
       addtv( hemispheres.east, 1 );
       addtv( hemispheres.west, 2 );
       addtv( hemispheres.north, 4 );
       addtv( hemispheres.south, 4 );
       gettv();
       text = getReportManager()->getTextManager()->getRegText(m_summary, 4, index);
       getReportManager()->getStream() << text;
       if ( index2 != -1 ) {
          text = getReportManager()->getTextManager()->getRegText(m_summary, 4, index2);
          getReportManager()->getStream() << text;
          commit("hemispheres");
          }
       }
    if ( ( report = getReportManager()->getKey(CHS_FUNCTIONAL_COUNT, 0 ) ) == NULL ) {
       return false;
       }
    else
       getReportManager()->functionals((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
    if ( getReportConfig().getMode() & TEXT ) {
       inittv();
       addtv( functionals.individual, 1 );
       addtv( functionals.relative, 2 );
       addtv( functionals.temporal, 3 );
       addtv( functionals.terminal, 4 );
       gettv();
       text = getReportManager()->getTextManager()->getRegText(m_summary, 1, index);
       getReportManager()->getStream() << text;
       if ( index2 != -1 ) {
          text = getReportManager()->getTextManager()->getRegText(m_summary, 1, index2);
          getReportManager()->getStream() << text;
         }
         commit("functionals");
       }
    if ( ( report = getReportManager()->getKey(CHS_MODAL_COUNT, 0 ) ) == NULL ) {
       return false;
       }
    else
       getReportManager()->summModals((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
    if ( getReportConfig().getMode() & TEXT ) {
       inittv();
       addtv( modals.cadent, 1 );
       addtv( modals.angular, 2 );
       addtv( modals.succedent, 3 );
       gettv();
       text = getReportManager()->getTextManager()->getRegText(m_summary, 3, index);
       getReportManager()->getStream() << text;
       if ( index2 != -1 ) {
          text = getReportManager()->getTextManager()->getRegText(m_summary, 3, index2);
          getReportManager()->getStream() << text;
          }
          commit("modals");
       }
    }
 if ( getReportConfig().getMode() & ASPECTS ) {
    if ( ( report = getReportManager()->getKey( CHS_ASPECT_COUNT, 0 ) ) == NULL ) {
       return false;
       }
    else
       getReportManager()->aspectCount((char *)getReportConfig().getName(), (char *)getReportConfig().getComments(), (char *)report );
    if ( getReportConfig().getMode() & TEXT ) {
       inittv();
       addtv( aspect_count[CONJUNCT], CONJUNCT+1 );
       addtv( aspect_count[TRINE], TRINE+1 );
       addtv( aspect_count[SEXTILE], SEXTILE+1 );
       addtv( aspect_count[SQUARED], SQUARED+1 );
       addtv( aspect_count[OPPOSITION], OPPOSITION+1 );
       gettv();
       --index;
       if ( index != -1 ) {
          text = getReportManager()->getTextManager()->getRegText(m_summary, 0, index2);
          getReportManager()->getStream() << text;
          }
       if ( index2 != -1 ) {
             text = getReportManager()->getTextManager()->getRegText(m_summary, 0, index2);
          getReportManager()->getStream() << text;
          }
          commit("aspects");
          }
       }
    }
 if ( getReportConfig().getMode() & TEXT ) {
    getReportManager()->getTextManager()->closeText(m_summary);
    }
}

