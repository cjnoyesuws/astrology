
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
      virtual void setupPrinterDev( char *d ) {}
      virtual void setupName( char *n ) { name = n;}
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

