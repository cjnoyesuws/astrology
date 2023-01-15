#ifndef CHARCONS_H_INCLUDED
#define CHARCONS_H_INCLUDED

#define CHARCONS_SEEN 1

#define ERROR1 "ERROR!"
#define ERROR2 "ERROR!!"

//extern char _ERROR1[];
//extern char _ERROR2[];
extern const char error1[];
extern const char error2[];
extern const char warn1[];
extern const char warn2[];

 extern const char asfilelistname[];
 extern const char *long_types[];
 extern const char *types[];

extern const char *oa[];
extern const char fil_dev_prompt[];
extern const char *housmod[];
extern const char norml[], retrg[], still[];
extern const char *motstr[];
#define motion_str( r ) (motstr[r])
extern const char *apstr[];
extern const char *rectstr[];
extern const char siderealstr[];
extern const char tropicstr[];
extern const char *timezones[];
extern const char *speccodes[];
extern const char *angles[];




extern const char  PLANET_FILE_name[];
extern const char  HOUSE_FILE_name[];
extern const char  ASPECT_FILE_name[];
extern const char  SUMMARY_FILE_name[];
extern const char  COMPAT_HOUSES_name[];
extern const char  COMPAT_SUMMARY_name[];
extern const char  TRANSITS_HOUSES_name[];
extern const char  TRANSITS_ASPECTS_name[];
extern const char  PROGRESS_ASPECTS_name[];
extern const char  SIGN_HOUSE_FILE_name[];
extern const char  COMPAT_ASPECTS_name[];
extern const char  MIDPOINT_SIGN_name[];
extern const char  LOCATION_INDEX_name[];
extern const char  LOCATION_DATA_name[];
extern const char  BIRTHBAS_INDEX_name[];
extern const char  BIRTHBAS_DATA_name[];
extern const char  LOCATION_POPUP_name[];
extern const char  BIRTHBAS_POPUP_name[];
extern const char  LOC_POPUP_INDEX_name[];
extern const char ARABIC_SIGN_name[];
extern const char ARABIC_HOUSE_name[];
extern const char ARABIC_ASPECTS_name[];
extern const char FIXEDST_SIGN_name[];
extern const char FIXEDST_HOUSE_name[];
extern const char FIXEDST_ASPECTS_name[];
extern const char SOLAR_PLANET_name[];
extern const char SOLAR_HOUSE_name[];
extern const char SOLAR_ASPECT_name[];
extern const char  CM_PLANET_FILE_name[];
extern const char  CM_HOUSE_FILE_name[];
extern const char  CM_ASPECT_FILE_name[];
extern const char  CM_TRANSITS_HOUSES_name[];
extern const char  CM_TRANSITS_ASPECTS_name[];




#endif // CHARCONS_H_INCLUDED
