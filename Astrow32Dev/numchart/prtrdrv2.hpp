
extern char *tab_out_buf( Tabs *t, char *buf, int *col, int *len );
extern char *real_tab_out( Tabs *t, char *buf, int *col, int *sz );


class TextConvDriver {
protected:
      int mul;
      int col;
      int div;
      int ansi;
      int toOem;
      int left;
      int width;
      int bold_mode;
      int head_mode;
      int ul_mode;
      int center;
      int justify;
      char *margin;
      char *hard_crs, *soft_crs;
      Tabs *pTabs;
      SexCodes *pSxc;
      struct FIL_ATTRIB atrb;
      FILE *istream, *ostream;
public:
      TextConvDriver( int ans, int Oem=1 ) { ansi = ans; mul = 1;  toOem = Oem;
	  div = 1; pTabs = new Tabs(); pSxc = new SexCodes; }
      void setCenter( int ctr ) { center = ctr; }
      void setJustify( int jst ) { justify = jst; }
      ~TextConvDriver() { delete pTabs; }
      void setStreams( FILE *i, FILE *o ) {istream = i; ostream = o;}
      void setCrs( char *hard, char *soft ) { hard_crs = hard; soft_crs = soft; }
      virtual void initDriver( FIL_ATTRIB *a ) { atrb = *a; }
      virtual void initDecomp( int width );
      virtual int foreign(unsigned char the_char);
      virtual char *tabOut( char *buf, int *col, int *sz )
			 { return( tab_out_buf( pTabs, buf, col, sz ) ); }
      virtual char *tabSet( char *buf, int *sz ) { return( buf ); }
      virtual unsigned int decompress(char *outbuf,
			  unsigned out_size, int *lines, int mode );
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual int stringPrint( char *string );
      void setConvertOem(int c) {toOem = c;}
      virtual void finishUpFile() { fputc( '\x0c', ostream ); }
      virtual void finishUpJob() {}
      virtual char *getOpenMode() { return "wt"; }
      virtual char *getAppendMode() { return "at"; }
      virtual void setStyles(ReportStyles *rs) {}
      char *moveStr( unsigned char *p, unsigned char *d, unsigned int *l);
      };


class TextConvDriverPlainAscii : public TextConvDriver {
public:
      TextConvDriverPlainAscii( int ans, int oem ) : TextConvDriver(ans,oem)  {}
      ~TextConvDriverPlainAscii() {}
      virtual void initDriver( FIL_ATTRIB *a );
      };

class TextConvDriverWriAscii : public TextConvDriverPlainAscii {
public:
      TextConvDriverWriAscii( int ans, int oem ) : TextConvDriverPlainAscii(ans,oem)  {}
      ~TextConvDriverWriAscii() {}
      virtual char *tabOut( char *buf, int *col, int *sz )
			 { return( real_tab_out( pTabs, buf, col, sz ) ); }
      virtual void initStringPrint(int left, int width, int version, int code )
	{ TextConvDriver::initStringPrint(0, 18000, version, code ); }
      };



class TextConvDriverWP5 : public TextConvDriver {
public:
      TextConvDriverWP5( int ans ) : TextConvDriver(ans,1)  {}
      ~TextConvDriverWP5() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      };


#define _REG_   0
#define _HEAD_  1
#define _BOLD_  2
#define _UITAL_  3

class TextConvDriverRTF : public TextConvDriverWFnt {
char reg[40];
char par[50];
int colors[4];
int fonts[4];
public:
      TextConvDriverRTF( int ans, int oem ) : TextConvDriverWFnt(ans,oem)  {}
      ~TextConvDriverRTF() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual void finishUpFile();
      virtual void finishUpJob();
      void makeColorTable(int doTable);
      void makeFontTable(int doTable);
      void makeAttrib(char *buf, int i, LPLOGFONT f, int ctr, int sz);
      void makeAttribs(int doTable);
      };

