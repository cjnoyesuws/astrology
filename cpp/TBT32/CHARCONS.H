#ifndef _CHARCONS_H___
#define _CHARCONS_H___

#define CHARCONS_SEEN

#define ERROR1 _ERROR1
#define ERROR2 _ERROR2

extern "C" {
extern char  _ERROR1[];
extern char  _ERROR2[];
extern char  error1[];
extern char  error2[];
extern char  warn1[];
extern char  warn2[];
}
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#endif /* _CHARCONS_H___ */
