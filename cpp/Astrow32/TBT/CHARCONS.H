#ifndef _CHARCONS_H___
#define _CHARCONS_H___

#define CHARCONS_SEEN 1

#define motion_str(m) ((m) > 2 ? "" : motstr[(m)])

#define ERROR1 _ERROR1
#define ERROR2 _ERROR2

extern "C" {
extern char _far _ERROR1[];
extern char _far _ERROR2[];
extern char _far error1[];
extern char _far error2[];
extern char _far warn1[];
extern char _far warn2[];
extern char *oa[];
extern char _far fil_dev_prompt[];
extern char *housmod[];
extern char _far btunknownstr[];
extern char *apstr[];
extern char *rectstr[];
extern char _far siderealstr[];
extern char _far tropicstr[];
extern char _far zodhsmethstr[];
extern char _far sidtim4calc[];
extern char _far geogcoordstr[];
extern char _far countrystatelocstr[];
extern char _far PLANET_FILE_name[];
extern char _far HOUSE_FILE_name[];
extern char _far ASPECT_FILE_name[];
extern char _far SUMMARY_FILE_name[];
extern char _far COMPAT_HOUSES_name[];
extern char _far COMPAT_SUMMARY_name[];
extern char _far TRANSITS_HOUSES_name[];
extern char _far TRANSITS_ASPECTS_name[];
extern char _far PROGRESS_ASPECTS_name[];
extern char _far COMPAT_ASPECTS_name[];
extern char _far MIDPOINT_SIGN_name[];
extern char _far SIGN_HOUSE_FILE_name[];
extern char _far LOCATION_INDEX_name[];
extern char _far LOCATION_DATA_name[];
extern char _far BIRTHBAS_INDEX_name[];
extern char _far BIRTHBAS_DATA_name[];
extern char _far LOCATION_POPUP_name[];
extern char _far BIRTHBAS_POPUP_name[];
extern char _far LOC_POPUP_INDEX_name[];
extern char _far norml[];
extern char _far retrg[];
extern char _far still[];
extern char *motstr[];
extern char _far decanstr[];
extern char _far anaretstr[];
extern char _far criticstr[];
extern char _far onacuspstr[];
extern char _far interceptstr[];
extern char _far sign_inteceptstr[];
extern char _far asfilelistname[];
extern char *timezones[];
extern char *speccodes[];
extern char far types[32][15];
extern char far long_types[32][35];
};
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#endif /* _CHARCONS_H___ */
