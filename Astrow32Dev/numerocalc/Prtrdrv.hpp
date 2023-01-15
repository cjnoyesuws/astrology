
extern char *tab_out_buf( Tabs *t, char *buf, int *col, int *len );
extern char *real_tab_out( Tabs *t, char *buf, int *col, int *sz );


typedef struct FONT {
      char   lfFaceName[40];
      short  lfHeight;
      short  lfWeight;
      short  lfItalic;
      short  lfUnderline;
      unsigned short  lfPitchAndFamily;
      } FONT;


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
      char *name;
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
      virtual void initDriver( FIL_ATTRIB *a ) { atrb = *a; margin = ""; }
      virtual void initDecomp( int width );
      virtual int foreign(unsigned char the_char) {return 0;}
      virtual char *tabOut( char *buf, int *col, int *sz )
			 { return( tab_out_buf( pTabs, buf, col, sz ) ); }
      virtual char *tabSet( char *buf, int *sz ) { return( buf ); }
      virtual unsigned int decompress(char *outbuf,
			  unsigned out_size, int *lines, int mode );
      virtual void initStringPrint(int lft, int wid ) {margin="";}
      virtual int stringPrint( char *string );
      void setConvertOem(int c) {toOem = c;}
      virtual void finishUpFile() { fputc( '\x0c', ostream ); }
      virtual void finishUpJob() {}
      virtual char *getOpenMode() { return "wt"; }
      virtual char *getAppendMode() { return "at"; }
      char *moveStr( unsigned char *p, unsigned char *d, unsigned int *l);
      virtual void setupFonts( FONT *pFnt ) {}
      virtual void setupColors( COLORREF *pClr ) {}
      virtual void setupPrinterDev( char *d ) {}
      virtual void setupName( char *n ) { name = n;}
      };

class TextConvDriverPlainAscii : public TextConvDriver {
public:
            TextConvDriverPlainAscii() : TextConvDriver(0,0)  {setCrs("\n","\n");}
      ~TextConvDriverPlainAscii() {}
      virtual void initStringPrint(int lft, int wid ) {left=lft;width=wid;if (lft) {margin = new char[left+2]; memset(margin,' ',left);margin[left]='\0';}else margin="";fputs(margin,ostream);}
      };

class TextConvDriverWP5 : public TextConvDriver {
public:
      TextConvDriverWP5() : TextConvDriver(0,1)  {}
      ~TextConvDriverWP5() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width);
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      };

class TextConvDriverWP6 : public TextConvDriver {
public:
      TextConvDriverWP6() : TextConvDriver(0,1)  {}
      ~TextConvDriverWP6() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width);
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      virtual void finishUpJob();
      virtual int stringPrint( char *string );
      void HeadOn();
      void HeadOff();
      };



class TextConvDriverWPint : public TextConvDriver {
FONT fonts[4];
COLORREF colors[4];
public:
      TextConvDriverWPint() : TextConvDriver(0,0)  {}
      ~TextConvDriverWPint() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width);
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      void setupFonts( FONT *pFnt ) {memcpy(fonts,pFnt,4 * sizeof(FONT)); }
      virtual void finishUpFile() {} 
      virtual void finishUpJob();
};


#define _REG_   0
#define _HEAD_  1
#define _BOLD_  2
#define _UITAL_  3

class TextConvDriverRTF : public TextConvDriver {
FONT fonts[4];
COLORREF colors[4];
char reg[40];
char par[50];
int iColors[4];
int iFonts[4];
public:
      TextConvDriverRTF() : TextConvDriver(0,0)  {}
      ~TextConvDriverRTF() {}
      int foreign(unsigned char the_char);
      void initDriver( FIL_ATTRIB *a );
      char *tabSet( char *buf, int *sz );
      char *tabOut( char *buf, int *col, int *sz );
      void initStringPrint(int left, int width );
      void finishUpFile();
      void finishUpJob();
      void makeColorTable(int doTable);
      void makeFontTable(int doTable);
      void makeAttrib(char *buf, int i, FONT *f, int ctr, int sz);
      void makeAttribs(int doTable);
      void setupFonts( FONT *pFnt ) {memcpy(fonts,pFnt,4 * sizeof(FONT)); }
      void setupColors( COLORREF *pClr ) {memcpy(colors,pClr, 4 * sizeof(COLORREF)); }
      };

class TextConvDriverAmi : public TextConvDriver {
FONT fonts[4];
COLORREF colors[4];
char reg[100];
char par[150];
char tabs[100];
char prtdev[100];
public:
      TextConvDriverAmi() : TextConvDriver( 0, 0 )  {}
      ~TextConvDriverAmi() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      void initStringPrint(int left, int width);
      virtual void finishUpFile();
      virtual void finishUpJob();
      void makeAttrib(char *buf, int i, FONT *f, int ctr, int sz, COLORREF c );
      void makeAttribOff(char *buf, int i, FONT *f, int ctr, int sz, FONT *o, COLORREF c );
      void makeAttribs();
      void setupFonts( FONT *pFnt ) {memcpy(fonts,pFnt,4 * sizeof(FONT)); }
      void setupColors( COLORREF *pClr ) {memcpy(colors,pClr, 4 * sizeof(COLORREF)); }
      virtual void setupPrinterDev( char *d ) {strcpy( prtdev, d );}
      };

class TextConvDriverHTML : public TextConvDriver {
public:
      TextConvDriverHTML() : TextConvDriver(0,1)  {}
      ~TextConvDriverHTML() {}
      virtual int foreign(unsigned char the_char);
      virtual void initDriver( FIL_ATTRIB *a );
      virtual void initStringPrint(int left, int width);
      virtual void finishUpJob();
      };

#include "txtdrv.h"

