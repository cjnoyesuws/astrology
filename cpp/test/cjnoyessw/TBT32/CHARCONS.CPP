#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdio.h>
#include "charcons.h"

char _far _ERROR1[] = "ERROR!";
char _far _ERROR2[] = "ERROR!!";
char _far error1[] = "Error!";
char _far error2[] = "Error!!";
char _far warn1[]  = "Warning!";
char _far warn2[]  = "Warning!!";
char *oa[]    = { "Append", "Open", NULL };
char _far fil_dev_prompt[] = "Enter File Name or Device.";
char *housmod[] = { "Equal House", "Koch", "Placidus",
		    "M House", "Campanus",
		    "Regiomantanus", "Morinus", NULL };
char norml[] = "Direct", retrg[] = "Retrograde", still[] = "Still";
char *motstr[] = { norml, retrg, still };
char *apstr[] = { "AM", "PM", NULL };
char *rectstr[]    =  { "Solar Chart Method", "Flat Chart Method",
	"Sunrise Birth-Time", "Trial & Error", "Use Known Angle" };
char _far siderealstr[] = "Sidereal";
char _far tropicstr[]   = "Tropical";
char *timezones[] = { "Eastern Atlantic", "Atlantic Standard", "Eastern Standard",
   "Central Standard", "Mountain Standard", "Pacific Standard", "Hawaii",
   "Greenwich Mean", "Western European", "Eastern Europe", "Eurasia",
   "China", "Japan", "Indochina", "New Zealand", "E. Australia",
   "S. Australia", "W. Australia", "India", "Samoa", "Int'l Date Line",
   "Other", NULL };

char *speccodes[] = { "Standard Time", "War Time", "Daylight Savings",
	       "Double British Summer", "Summer Time", "Winter Time",
	       "Other", NULL };
char *angles[] = { "1st House/Asc.", "2nd House", "3rd House",
  "4th House/IC", "5th House", "6th House", "7th House/Desc.",
  "8th House", "9th House", "10th House/MC", "11th House", "12th House",
  "Ascendant", "Descendant", "Medium Coeli/Midheaven", "Immum Coeli/Nadir", NULL };


char _far PLANET_FILE_name[] = "PLANETS";
char _far HOUSE_FILE_name[]       = "HOUSES";
char _far ASPECT_FILE_name[]      = "ASPECTS";
char _far SUMMARY_FILE_name[]     = "SUMMARY";
char _far COMPAT_HOUSES_name[]    = "COMPAHSE";
char _far COMPAT_SUMMARY_name[]   = "COMPASUM";
char _far TRANSITS_HOUSES_name[]  = "TRANSHSE";
char _far TRANSITS_ASPECTS_name[] = "TRANSASP";
char _far PROGRESS_ASPECTS_name[] = "PROGRASP";
char _far SIGN_HOUSE_FILE_name[]  = "SIGHOUSE";
char _far COMPAT_ASPECTS_name[]   = "COMPTASP";
char _far MIDPOINT_SIGN_name[]    = "MIDPTSIN";
char _far LOCATION_INDEX_name[]   = "NLOCATIN.NDX";
char _far LOCATION_DATA_name[]    = "NLOCATIN.DAT";
char _far BIRTHBAS_INDEX_name[]   = "NBIRTHBS.NDX";
char _far BIRTHBAS_DATA_name[]    = "NBIRTHBS.DAT";
char _far LOCATION_POPUP_name[]   = "NLOCATIN.LST";
char _far BIRTHBAS_POPUP_name[]   = "NBIRTHBS.LST";
char _far LOC_POPUP_INDEX_name[]  = "LPOPLIST.NDX";
char _far asfilelistname[] = "NASTFIL.LST";

char far types[32][15] = { "", "Natal", "Compat", "Transits", "Progressed",
    "Numeric", "Sun Return", "Moon Return", "Relocation", "Composite",
    "Fixed Star", "Arabic Parts", "Heliocentric", "Problem", "Compos Transit",
    "", "Natal-Graph", "Compat-Graph", "Trans-Graph", "Prog-Graph",
    "Numer-Graph", "", "", "Reloc-Graph", "Compos-Graph", "", "", "", "",
    "CompTran-Gra" };

char far long_types[][35] = { "", "Birth Output File", "Compatability Output File",
    "Transits Output File", "Progressed Birth Output File",
    "Numeric Birth Output File", "Solar Return File", "Moon Return File",
    "Relocation File",  "Composite Output File", "Fixed Star Output File",
    "Arabic Parts Output File", "Heliocentric Birth Output File",
    "Astrological Problem Output File", "Composite Transits File", "",
    "Birth Graphics File", "Compatability Graphics File",
    "Transits Graphics File", "Progressed Birth Graphics File",
    "Numeric Birth Graphics File", "", "", "Reloction Graphics File",
    "Composite Graphics File", "", "", "", "",
    "Composite Transits Graphics File" };


