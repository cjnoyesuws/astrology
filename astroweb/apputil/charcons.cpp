
#include <stdio.h>
#include "charcons.h"

/*char *_ERROR1 = "ERROR!";
char *_ERROR2 = "ERROR!!";
char *__ERROR1 = "ERROR!";
char *__ERROR2 = "ERROR!!";*/
const char error1[] = "Error!";
const char error2[] = "Error!!";
const char warn1[]  = "Warning!";
const char warn2[]  = "Warning!!";
const char *housmod[] = { "Equal House", "Koch", "Placidus",
		    "M House", "Campanus",
		    "Regiomantanus", "Morinus","Porphyrx","Topocentric","Meridian", NULL };
const char norml[] = "Direct", retrg[] = "Retrograde", still[] = "Still";
const char *motstr[] = { norml, retrg, still };
const char *apstr[] = { "AM", "PM", NULL };
const char *rectstr[]    =  { "Solar Chart Method", "Flat Chart Method",
	"Sunrise Birth-Time", "Trial & Error", "Use Known Angle" };
const char siderealstr[] = "Sidereal";
const char tropicstr[]   = "Tropical";
const char *timezones[] = { "Eastern Atlantic", "Atlantic Standard", "Eastern Standard",
   "Central Standard", "Mountain Standard", "Pacific Standard", "Hawaii",
   "Greenwich Mean", "Western European", "Eastern Europe", "Eurasia",
   "China", "Japan", "Indochina", "New Zealand", "E. Australia",
   "S. Australia", "W. Australia", "India", "Samoa", "Int'l Date Line",
   "Other", NULL };

const char *speccodes[] = { "Standard Time", "War Time", "Daylight Savings",
	       "Double British Summer", "Summer Time", "Winter Time",
	       "Other", NULL };
const char *angles[] = { "1st House/Asc.", "2nd House", "3rd House",
  "4th House/IC", "5th House", "6th House", "7th House/Desc.",
  "8th House", "9th House", "10th House/MC", "11th House", "12th House",
  "Ascendant", "Descendant", "Medium Coeli/Midheaven", "Immum Coeli/Nadir", NULL };


const char PLANET_FILE_name[] = "PLANETS";
const char HOUSE_FILE_name[]       = "HOUSES";
const char ASPECT_FILE_name[]      = "ASPECTS";
const char SUMMARY_FILE_name[]     = "SUMMARY";
const char COMPAT_HOUSES_name[]    = "COMPAHSE";
const char COMPAT_SUMMARY_name[]   = "COMPASUM";
const char TRANSITS_HOUSES_name[]  = "TRANSHSE";
const char TRANSITS_ASPECTS_name[] = "TRANSASP";
const char PROGRESS_ASPECTS_name[] = "PROGRASP";
const char SIGN_HOUSE_FILE_name[]  = "SIGHOUSE";
const char COMPAT_ASPECTS_name[]   = "COMPTASP";
const char MIDPOINT_SIGN_name[]    = "MIDPTSIN";
const char LOCATION_INDEX_name[]   = "NLOCATIN.NDX";
const char LOCATION_DATA_name[]    = "NLOCATIN.DAT";
const char BIRTHBAS_INDEX_name[]   = "NBIRTHBS.NDX";
const char BIRTHBAS_DATA_name[]    = "NBIRTHBS.DAT";
const char LOCATION_POPUP_name[]   = "NLOCATIN.LST";
const char BIRTHBAS_POPUP_name[]   = "NBIRTHBS.LST";
const char LOC_POPUP_INDEX_name[]  = "LPOPLIST.NDX";
const char asfilelistname[] = "NASTFIL.LST";
const char ARABIC_SIGN_name[] = "ARABICSGN";
const char ARABIC_HOUSE_name[] = "ARABICHSE";
const char ARABIC_ASPECTS_name[] = "ARABICASP";
const char FIXEDST_SIGN_name[] = "FIXEDSTSGN";
const char FIXEDST_HOUSE_name[] = "FIXEDSTHSE";
const char FIXEDST_ASPECTS_name[] = "FIXEDSTASP";
const char SOLAR_PLANET_name[] = "SOLARPLN";
const char SOLAR_HOUSE_name[] = "SOLARHSE";
const char SOLAR_ASPECT_name[] = "SOLARASP";
const char CM_PLANET_FILE_name[] = "CMPLANETS";
const char CM_HOUSE_FILE_name[]       = "CMHOUSES";
const char CM_ASPECT_FILE_name[]      = "CMASPECTS";
const char CM_TRANSITS_HOUSES_name[]  = "CMTRANSHSE";
const char CM_TRANSITS_ASPECTS_name[] = "CMTRANSASP";
const char *types[] = { "", "Natal", "Compat", "Transits", "Progressed",
    "Numeric", "Sun Return", "Moon Return", "Relocation", "Composite",
    "Fixed Star", "Arabic Parts", "Heliocentric", "Problem", "Compos Transit",
    "Solar Arc", "Harmonic", "", "", "", "", "","", "", "","",
	"Natal-Graph", "Compat-Graph", "Trans-Graph", "Prog-Graph",
    "Numer-Graph", "", "", "Reloc-Graph", "Compos-Graph", "", "", "", "",
	"CompTran-Gra", "Solar-Graph", "Harmonic-Graph", "", "", "", "", "",
    "", "", "", "", "Natal-Grid", "Compat-Grid", "Transits-Grid", "Progressed-Grid",
    "Numeric-Grid", "Sun Return Grid", "Moon Return Grid", "Relocation-Grid", "Composite-Grid",
    "Fixed Star Grid", "Arabic Parts Grid", "Heliocentric-Grid", "Problem-Grid", "Compos Transit Grid",
    "Solar Arc-Grid", "Harmonic-Grid", "", "", "", "", "","", "", "","",};

const char *long_types[] = { "", "Birth Output File", "Compatability Output File",
    "Transits Output File", "Progressed Birth Output File",
    "Numeric Birth Output File", "Solar Return File", "Moon Return File",
    "Relocation File",  "Composite Output File", "Fixed Star Output File",
    "Arabic Parts Output File", "Heliocentric Birth Output File",
    "Astrological Problem Output File", "Composite Transits File", "Solar Arc File",
    "Harmonic File", "", "", "", "","", "", "", "", "",
	"Birth Graphics File", "Compatability Graphics File",
    "Transits Graphics File", "Progressed Birth Graphics File",
    "Numeric Birth Graphics File", "", "", "Reloction Graphics File",
    "Composite Graphics File", "", "", "", "",
    "Composite Transits Graphics File", "Solar Arc Graphics File", "Harmonic Graphics File", "", "", "", "", "", "", "",
    "", "", "Birth Grid File", "Compatability Grid File",
    "Transits Grid File", "Progressed Birth Grid File",
    "Numeric Birth Grid File", "Solar Return Grid File", "Moon Return Grid File",
    "Relocation Grid File",  "Composite Grid File", "Fixed Star Grid File",
    "Arabic Parts Grid File", "Heliocentric Birth Grid File",
    "Astrological Problem Grid File", "Composite Transits Grid File", "Solar Arc Grid File",
    "Harmonic Grid File", "", "", "", "","", "", "", "", ""
};


