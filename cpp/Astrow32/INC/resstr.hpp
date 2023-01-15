#ifndef RESSTR___HPP
#define RESSTR___HPP

class ResStr : public CString {
public:
   ResStr( int i ) : CString( zResId(i)) {}
   ResStr( char *p ) : zString( zResId(p)) {}
   ResStr( zString &s ) : zString( zResId(s)) {}
   };

#define CResStr(x) ((char *)ResStr(x))

#include "resstrid.h"


#endif /* RESSTR___HPP */