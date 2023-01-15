#include "astro.h"
#include "flags.h"
#include "useri.h"
#include "dataext.h"
#include "ConfigHelper.h"
#include "cstring"
#include <string.h>
#include <assert.h>

static entry progressed[3]={{"secondary",SECONDARY_PR}, {"tertiary",TERTIARY_PR}, {"minor",MINOR_PR}};
static entry rect[2]={{"solar",SOLARCHART},{"flat",FLATCHART}};
static entry charts[5]={{"natal",NATAL_CH},{"progressed",PROGR_CH},{"compatibility",COMPA_CH},{"transits",TRANS_CH},{"composite",COMPO_CH}};
static entry house[10] = {{"equal", EQUAL},{"koch",KOCH},{"placidus",PLACIDUS},{"m-house",M_HOUSE},{"companus",COMPANUS},
    {"regiomontanus",REGIOMONT},{"morinus",MORINUS},{"topocentric",TOPOCENTRIC},{"meridian",MERIDIAN},{"porphryryx",PORPHYRYX}};
static entry flags[8] = {{"default",DEFAULTFLGS},{"sidereal",SIDEREAL},{"houses",HOUSES},{"aspects",ASPECTS},{"extra-aspects", EXT_ASPECTS},
    {"vertext-eastpoint",VERT_EAST},{"rectify",NOBIRTHTIM},{"asteroids",ASTEROID}};


unsigned short ConfigHelper::parseFlags(const char *text) {
    unsigned short flagsval= 0;
    int pos=0;
    char buf[40];

    memset(buf,0,40);

    if (strchr(text,'|')==0) {
        return (unsigned short)findEntry(text,flags,8,DEFAULTFLGS);
    }

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] != '|') {
            buf[pos++]=text[i];
        }
        else {
            buf[pos++]='\0';
            flagsval |= findEntry(buf,flags,8,0);
            pos=0;
        }
    }

    buf[pos++]='\0';
    flagsval |= findEntry(buf,flags,8,0);
    return flagsval;
}

short ConfigHelper::findHouses(const char *text) {
    return findEntry(text,house,10,PLACIDUS);
}


short ConfigHelper::findRect(const char *text) {
    return findEntry(text,rect,3,SOLARCHART);
}


short ConfigHelper::findProgressed(const char *text) {
    return findEntry(text,progressed,3,SECONDARY_PR);
}


short ConfigHelper::findChartCode(const char *text) {
    return findEntry(text,charts,5,NATAL_CH);
}

short ConfigHelper::findEntry(const char *text, entry *entries, int count, int dflt) {
   assert(entries != 0);
   assert(text != 0);

   for (int i = 0;  i < count; i++ ) {
       if (strcmp(entries[i].label, text)==0) {
           return entries[i].value;
       }
   }
   return dflt;
}
