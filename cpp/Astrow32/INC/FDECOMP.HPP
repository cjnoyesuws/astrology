#ifndef _FDECOMP__HPP_
#define _FDECOMP__HPP_

#ifndef _BOLD_DEF
#define _BOLD_ 2
#define _HEAD_ 1
#define _ITAL_ 4
#endif

class TextDecompressor {
      FILE_DB fpt;
      int  nSize;
      int  ansi;
      int  atrib;
      char acvFileName[150];
      char *pBuf;
      char *titleName;
      FILE *pStream;
      SexCodes *pSexCodes;
      Tabs *pTabs;
      int  nSlen, nSatr, nEatr;
      int  fFinished;
public:
      TextDecompressor( int size = 5000 );
      ~TextDecompressor();
      int openFile( char *name );
      void setTitle(char *t) { titleName = t;}
      char *decompressPar( int &len, int &startAtr, int &endAtr );
      void tab_init( int total_width, int mul=1, int div=1, int left=0 ) {
	    if (pTabs != NULL)
	       pTabs->init( total_width, mul, div, left ); }
      int anyMore() { return( pStream != NULL && !feof( pStream ) ); }
      int ok() { return( !(pStream==NULL||feof(pStream)||ferror(pStream)) ); }
      char *tab_out( int *col, int *sz, char *buf );
      char *getText( int &len, int &startAtr ) {
	    if ( fFinished )
	       decompressPar( nSlen, nSatr, nEatr );
	    finished(0);
	    len = nSlen; startAtr = nSatr; return pBuf;
	    }
      void finished(int f) { fFinished = f;}
      int isFinished() { return fFinished; }
      FILE_DB *getFpt() { return &fpt; };
      void closeFile();
      int nextTab();
      void resetTab() { pTabs->resetTab(); }
      };

#ifndef _BOLD_DEF
#define _BOLD_DEF 
inline int isBold(unsigned char a) { return( a & _BOLD_ ); }

inline int isHead(unsigned char a) { return( a & _HEAD_ ); }

inline int isItal(unsigned char a) { return( a & _ITAL_ ); }
#endif
#endif  /* _FDECOMP__HPP_ */

