#ifndef _SEXCODES__HPP_
#define _SEXCODES__HPP_

class SexCodes {
   char nul[2];
   char *sex1_ptrs[17];
   char *buf1;
   char *sex2_ptrs[17];
   char *buf2;
   char *style_ptrs[17];
   int  style_len[17];
   char *style_buf;
public:
   SexCodes() { nul[0] = '\0'; buf1 = NULL; buf2 = NULL; style_buf = NULL; }
   ~SexCodes();
   int output( FILE *stream, int sex, int sexno, int table );
   char *read( FILE *stream, char *buf, char **ar );
   int readStyle( char *name );
   char *doACode( int p, int code, char **outbuf, int *sz );
   char *doCodes( FILE *stream, char **outbuf, int *sz, Tabs *t );
   };

#endif /*  _SEXCODES__HPP_  */
