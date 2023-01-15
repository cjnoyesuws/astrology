#ifndef _WRITE____HPP_
#define _WRITE____HPP_

typedef struct PAGES {
	unsigned para;
	unsigned footn;
	unsigned sectp;
	unsigned sectd;
	unsigned paget;
	unsigned font;
	unsigned getParaPage() { return para; }
	unsigned getSectpPage() { return sectp; }
	unsigned getSectdPage() { return sectd; }
	unsigned getPagetPage() { return paget; }
	unsigned getFontPage() { return font; }
	unsigned getFootnotePage() { return footn; }
	void setParaPage(unsigned p) { para = p; }
	void setSectpPage(unsigned p) { sectp = p; }
	void setSectdPage(unsigned p) { sectd = p; }
	void setPagetPage(unsigned p) { paget = p; }
	void setFontPage(unsigned p) { font = p; }
	void setFootnotePage(unsigned p) { footn = p; }
	} PAGES;

typedef struct WRI_HEADER {
	unsigned  id;
	unsigned dty;
	unsigned wTool;
	unsigned res[4];
	long     fcMac;
	PAGES    pageOfs;
	char     szSsht[66];
	unsigned pnMac;
	char     blank[30];
	unsigned getPnChar() { return( (fcMac+127)/128 ); }
	unsigned getPageMac() { return pnMac; }
	long     getFcMac()   { return fcMac; }
	PAGES    &getPages()  { return pageOfs; }
	void setPageMac(unsigned p) { pnMac = p; }
	void setFcMac(long l)   { fcMac = l; }
	} WRI_HEADER;

typedef struct FOD {
	long ofsNextChar;
	unsigned bofsProp;
	void setNextChar( long l ) { ofsNextChar = l; }
	void setOfsProp( unsigned o ) { bofsProp = o; }
	void set( long l, unsigned o ) { ofsNextChar = l; bofsProp = o;  }
	unsigned getOfsProp() { return( bofsProp ); }
	void chOfsProp( int o ) { bofsProp += o; }
	} FOD;


typedef struct CHPX {
	int ftc : 6;
	int fItalic : 1;
	int fBold : 1;
	int res : 8;
	unsigned char size;
	char fUline;
	void setSize( int s=24 ) { size = s; }
	void setFtc( int f=0 )  { ftc = f; }
	void setItal( int i=0 ) { fItalic = i; }
	void setBold( int b=0 ) { fBold = b; }
	void setUline( int u=0 ) { fUline = 0; }
	} CHPX;

#define CHP_SIZE 4

typedef struct FPROP_CHP {
	unsigned char count;
	CHPX chp;
	void set( int s, int f=0, int i=0, int b=0, int usi=0 )
	      { chp.setSize(s); chp.setFtc(f); chp.setBold(b);
		if ( usi ) {
		   chp.setUline(0);
		   chp.setItal(i);
		   }
		else {
		   chp.setUline(i);
		   chp.setItal(0);
		   }
	      count = CHP_SIZE;  }
	} FPROP_CHP;

#define OFFREG   (sizeof(FOD)*17)
#define OFFBOLD  ((sizeof(FOD)*17)+sizeof(FPROP_CHP))
#define OFFHEAD  ((sizeof(FOD)*17)+(sizeof(FPROP_CHP)*2))
#define OFFITAL  ((sizeof(FOD)*17)+(sizeof(FPROP_CHP)*3))

#define MAX_FOD 17

typedef struct CHP_PAGE {
	long fcFirst;
	FOD fods[MAX_FOD];
	FPROP_CHP reg;
	FPROP_CHP bold;
	FPROP_CHP head;
	FPROP_CHP ital;
	int  nProp;
	void setFirst( long ofs ) { fcFirst = ofs; }
	int addBold( long ofs );
	int addReg( long ofs );
	int  addHead( long ofs );
	int  addItal( long ofs );
	int getFodCount() { return( nProp ); }
	void init( ReportStyles *rs );
	int write( FILE *stream ) { return( fwrite( &fcFirst, 128, 1, stream ) ); }
	void initFodCount() { nProp = 0; }
	} CHP_PAGE;

#define TNORMAL 0
#define TDECMAL 3

typedef struct TBD {
	unsigned indent;
	char type;
	char align;
	void set( unsigned i ) { indent = i; type = 0, align = 0;}
	} TBD;

#define JLEFT 0
#define JCNTR 1

typedef struct PAP {
	char res;
	char just;
	unsigned res1;
	unsigned rightIndent;
	unsigned leftIndent;
	unsigned firstLine;
	unsigned lineSpace;
	unsigned before;
	unsigned after;
	unsigned rhcPage;
	long res2;
	TBD  tabs[14];
	void setLeft(int l=0) { leftIndent = l; }
	void setRight(int r=0) { rightIndent = r; }
	void setFirst(int f=0) { firstLine = f; }
	void setSpace(int s = 240) { lineSpace = s; }
	void setJust( char j=JLEFT ) { just = j;   }
	} PAP;

extern PAP defPap;

typedef struct XPAP {
	int tabCount;
	int ofs;
	unsigned char count;
	PAP thePap;
	void addTab(int i);
	void tabStart() { tabCount = 0; }
	int getLen();
	void setOfs(int o) { ofs = o; }
	void setCount() { count = getLen(); }
	void copyBase( PAP *base )
	   { memcpy( &thePap.res, base, sizeof(PAP)-(14 * sizeof(TBD))); }
        int write( FILE *stream );
        int getCount() { return count; }
        void init();
	} XPAP;

typedef struct XPAP_GROUP {
	long fcFirst;
	FOD fods[18];  /* variable count */
	XPAP paps[7];  /* variable length, variable count */
	int nProp;     /* at offset 126 (FOD count) */
	int curr_ofs;  /* this doesn't get written */
	int pap_count; /* this doesn't get written */
	void adjustOfs();
	int getPageLen();
	void setFirst( long l ) { fcFirst = l; }
	int addFod( long o );
	int addPap( long o, XPAP &p );
	int write( FILE *stream );
	void initFodCount() { nProp = 0; pap_count = 0; curr_ofs = 0; }
	int getFodCount() { return( nProp ); }
        void init();
	} XPAP_GROUP;

typedef struct FFN {
	int len;
	unsigned char ffid;
	char szFfn[100];
	void set( unsigned char id, char *fn )
	      { ffid = id;  strcpy( szFfn, fn ); len = strlen(fn)+2; }
	} FFN;

typedef struct PGD {
	int pgn;
	long cpMin;
	} PGD;

typedef struct PGTB {
	int cpgd;
	int res;
	PGD pg;
	} PGTB;

#endif /* _WRITE____HPP_ */
