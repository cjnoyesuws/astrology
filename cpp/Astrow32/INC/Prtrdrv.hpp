
extern char *tab_out_buf( Tabs *t, char *buf, int *col, int *len );
extern char *real_tab_out( Tabs *t, char *buf, int *col, int *sz );


class TextConvDriver {
protected:
	  BOOL bTableMode;
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
	  int doGlyph;
	  int glyphFont;
      struct FIL_ATTRIB atrb;
      FILE *istream, *ostream;
public:
	  int IsMbString;
	  int Unicode16LEFile;
      TextConvDriver( int ans, int Oem=1 ) { ansi = ans; mul = 1;  toOem = Oem; doGlyph=0; glyphFont=0;
	  div = 1; pTabs = new Tabs(); pSxc = new SexCodes; bTableMode = FALSE; IsMbString=0; Unicode16LEFile=0; }
      void setCenter( int ctr ) { center = ctr; }
	  void setMbString( int mb ) { IsMbString = mb; }
      void setJustify( int jst ) { justify = jst; }
      ~TextConvDriver() { delete pTabs; delete pSxc; }
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
	  virtual char *TableCode(char *buf, int *sz ) { return buf; }
	  virtual char *TablePct(int pct, char *buf, int *sz ) { return buf; }
      virtual char *TableRow(char *buf, int *sz ) { 
		  *buf = '\n';
          *sz++;
		  return buf+1; }
	  virtual void mbforeign( char *ptr ) { fwrite(ptr,2,1,ostream); }
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual int stringPrint( char *string );
      void setConvertOem(int c) {toOem = c;}
      virtual void finishUpFile() { fputc( '\x0c', ostream ); }
      virtual void finishUpJob() {}
      virtual char *getOpenMode() { return "wt"; }
      virtual char *getAppendMode() { return "at"; }
      virtual void setStyles(ReportStyles *rs) {}
      char *moveStr( unsigned char *p, unsigned char *d, unsigned int *l);
	  virtual void PlanetGlyph(int n) {}
	  virtual void SignGlyph(int n) {}
	  virtual void GlyphFont(int n) {}
	  void setGlyphOpt(int dog, int gf) {doGlyph=dog; glyphFont=gf;}
	  virtual char *Nbsp(char *buf, int *sz) {return buf;}
      int op_make_printer_string( char *instring, FILE *outstream );
	  int fputcs(char *s,FILE *out);
	  int fputcsw(char *s,FILE *out);
};


class TextConvDriverXYW : public TextConvDriver {
public:
      TextConvDriverXYW( int ans ) : TextConvDriver(ans,1)  {}
      ~TextConvDriverXYW() {}
      virtual void initDriver( FIL_ATTRIB *a );
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

class TextConvDriverWStar : public TextConvDriver  {
public:
      TextConvDriverWStar( int ans ) : TextConvDriver(ans,1)  {}
      ~TextConvDriverWStar() {}
      virtual void initDriver( FIL_ATTRIB *a );
      virtual int foreign(unsigned char the_char);
      virtual char *tabSet( char *buf, int *sz ) { return buf; }
      virtual char *tabOut( char *buf, int *col, int *sz )
		 { return( real_tab_out( pTabs, buf, col, sz ) ); }
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      };

class TextConvDriverWStar3 : public TextConvDriverWStar {
public:
      TextConvDriverWStar3(int ans ) : TextConvDriverWStar(ans) {}
      ~TextConvDriverWStar3() {}
      virtual char *tabSet( char *buf, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      };

class TextConvDriverWStar4 : public TextConvDriverWStar {
public:
      TextConvDriverWStar4(int ans) : TextConvDriverWStar(ans) {}
      ~TextConvDriverWStar4() {}
      virtual char *tabSet( char *buf, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      };


class TextConvDriverWP4 : public TextConvDriver {
public:
      TextConvDriverWP4( int ans ) : TextConvDriver(ans,1)  {}
      ~TextConvDriverWP4() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz )
		 { return( real_tab_out( pTabs, buf, col, sz ) ); }
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual void finishUpJob();
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
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


class TextConvDriverWP6 : public TextConvDriver {
public:
      TextConvDriverWP6( int ans ) : TextConvDriver(ans,1)  {}
      ~TextConvDriverWP6() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      virtual int stringPrint( char *string );
      virtual void finishUpJob();
      void HeadOn();
      void HeadOff();
      };



class TextConvDriverWFnt : public TextConvDriver {
protected:
      ReportStyles *pRs;
public:
      TextConvDriverWFnt( int ans, int oem ) : TextConvDriver(ans,oem) {}
      ~TextConvDriverWFnt() {}
      virtual void setStyles(ReportStyles *p ) { pRs = p; }
      ReportStyles *getStyles() { return pRs; }
      };

#define _REG_   0
#define _HEAD_  1
#define _BOLD_  2
#define _UITAL_  3

class TextConvDriverRTF : public TextConvDriverWFnt {
CString reg;
CString par;
int colors[6];
int fonts[6];
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
protected:
      void makeColorTable(int doTable);
      void makeFontTable(int doTable);
      void makeAttrib(CString &, int i, LPLOGFONT f, int ctr, int sz);
      void makeAttribs(int doTable);
	  virtual char *TableCode(char *buf, int *sz );
	  virtual char *TableRow(char *buf, int *sz );
	  virtual void PlanetGlyph(int n);
	  virtual void SignGlyph(int n);
	  virtual void GlyphFont(int n) {}
      virtual void mbforeign( char *ptr );      
};

class TextConvDriverAmi : public TextConvDriverWFnt {
CString reg;
CString par;
char tabs[100];
public:
      TextConvDriverAmi( int ans ) : TextConvDriverWFnt(ans,0)  {}
      ~TextConvDriverAmi() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual void finishUpFile();
      virtual void finishUpJob();
protected:      
      void makeAttrib(CString &b, int i, LPLOGFONT f, int ctr, int sz, COLORREF &c );
      void makeAttribOff(CString &b, int i, LPLOGFONT f, int ctr, int sz, LPLOGFONT o, COLORREF &c );
      void makeAttribs();
      };

/*
class TextConvDriverWPi : public TextConvDriverWFnt {
LOGFONT *fonts[4];
COLORREF colors[4];
public:
      TextConvDriverWPi( int ans ) : TextConvDriverWFnt(ans,0)  {}
      ~TextConvDriverWPi() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual void finishUpFile();
      virtual void finishUpJob();
      protected:
	  void cvtFontSize( LOGFONT *f);
	  void cvtFont();
	  void cvtFonts();
      };
*/

class TextConvDriverHTML : public TextConvDriverWFnt {
public:
	  int percent;
      TextConvDriverHTML( int ans ) : TextConvDriverWFnt(ans,1)  { percent=-1;}
      ~TextConvDriverHTML() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabOut( char *buf, int *col, int *sz );
		 //{ return( tab_out_buf( pTabs, buf, col, sz ) ); }
      virtual void initStringPrint(int left, int width, int version, int code );
      virtual void finishUpJob();
      virtual char *getOpenMode() { return "wt"; }
      virtual char *getAppendMode() { return "at"; }
      virtual char *TableCode(char *buf, int *sz );
	  virtual char *TableRow(char *buf, int *sz );
	   virtual char *TablePct(int pct, char *buf, int *sz );
	  virtual void PlanetGlyph(int n);
	  virtual void SignGlyph(int n);
	  virtual void GlyphFont(int n) {}
	  virtual char *Nbsp(char *buf, int *sz);
      void writestyles( FILE *stream );
	  const char *lftofs( LOGFONT *fnt );
      const char *lftowt( LOGFONT *fnt );
	  virtual void mbforeign( char *ptr );
	  void writestyle(FILE *stream, const char *tag, const char *font, const char *weight, const char *style, COLORREF &color, int size );
      };


#include "txtdrv.h"
