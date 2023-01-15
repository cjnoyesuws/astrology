
#include <string.h>
#include "ctype.h"


bool is_white_space( int ch ) {
  if (ch == ' ' || ch== '\r' || ch== '\n' || ch== '\x9') {
     return true;
  }
  else {
     return false;
  }
}

char *strclip( char *pStr )
{
 if (pStr == NULL) {
    return pStr;
 }
 int l = strlen( pStr );
 char *s=(pStr+l)-1;
 while( is_white_space(*s) && l > 0 ) {
    *s='\0';
    s--;
    l--;
    }
 return( pStr );
}

char *enquote_strclip( char *str, char *buf )
{
 char buffer[200];

 strcpy(buffer, str);
 strclip(buffer);
 return strcpy(buffer, buf);
}

char *xstrupr( char *src, char *buf )
{
  while (*src) {
    *buf++ = toupper(*src);
  }
  return buf;
}

