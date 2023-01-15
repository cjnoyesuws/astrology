#ifndef _VIRTTEXT_HPP_
#define _VIRTTEXT_HPP_

#ifndef _BOLD_DEF
#define _BOLD_ 2
#define _HEAD_ 1
#define _ITAL_ 4
#define _CHNG_ 8
#endif
typedef union ucl {
      long l;
      unsigned char uc[4];
      long getOfs() { return(l & 0xffffff); }
      unsigned char getFlags() { return( uc[3] ); }
      void set(long ll, unsigned char u) { l = ll; uc[3] = u; }
      } ucl_t;

typedef struct uclwlen {
      union ucl uucl;
      int len;
      long getOfs() { return( uucl.getOfs() ); }
      unsigned char getFlags() { return( uucl.getFlags() ); }
      void set(long ll, unsigned char u, int l=0) {len=l; uucl.set(ll,u); }
      int getLen() { return len; }
      } uclwlen_t;

class VirtualTextBuffer {
      XPFILE_DB fpt;
      CString acvFileName;
      CString acvSourceName;
      char *pvBuf;
      FILE *pvStream;
      int  nParas;
      int  nParaAlloc;
      int  nvbSizeAlloc;
      int  nvbLen, cmdLast, cmdPara;
      int spares;
      uclwlen *pParaOfs;
      uclwlen uclVofs, cmdUcl;
      int  nVpar;
      Tabs *pTabs;
      int _dirty;
	  int IsMbString;
protected:
      void setupSearch( char *bufu, char *bufl, char *search );
      int matchText(char *buf, int len, char *searchu, char *searchl);
public:
      VirtualTextBuffer( int size = 1000, int vbsize = 15000 );
      ~VirtualTextBuffer();
      int virtualizeFile( char *name, int dir );
      int resize( int size );
      int getSize( int nPar );
      int openVbuf();
      void closeVbuf();
      char *getBuf(int &len) { len = nvbLen; return pvBuf; }
      int findPar( int nPar, long lOfs );
      char *getText(int nPar, int &len, unsigned char &flags);
      int getLen() { return uclVofs.getLen(); }
      long getOfs() { return uclVofs.getOfs(); }
      int  getPar() { return nVpar; }
      XPFILE_DB &getFileDb() { return fpt; }
      CString &getSourceName() { return acvSourceName; }
	  void tab_init( int total_width, int mul=1, int div=1, int left=0 ) {
	    if (pTabs != NULL)
	       pTabs->init( total_width, mul, div, left ); }
      int getParaCount() { return nParas; }
      long getOfsAt(int i);
      unsigned char getFlagsAt(int i);
      void tab_out( int *col, int *sz );
      int getVBlen() { return nvbLen; }
      int findFirst(char *find);
      int findCont(char *find, int paraStart);
      int &dirty() { return _dirty; }
      int saveFile();
      int deletePara(int para);
      int insertParaAt(int para);
      int replaceParaAt(int para, unsigned char fl, char *txt );
      int undo();
	  };


#ifndef _BOLD_DEF
#define _BOLD_DEF
inline int isBold(unsigned char f) { return( f & _BOLD_ ); }

inline int isHead(unsigned char f) { return( f & _HEAD_ ); }

inline int isItal(unsigned char f) { return( f & _ITAL_ ); }

inline int isChange(unsigned char f) { return( f & _CHNG_ ); }
#endif

typedef struct LOC {
      int para;
      int ofs;
      int len;
      unsigned char flags;
      void set( int p, long o, int l, unsigned char f ) { para = p;
						   ofs = o;
						   len = l;
						   flags = f;  }
      void get( VirtualTextBuffer *pV, int p ) { para = p;
						 ofs = 0;
						 flags = pV->getFlagsAt(p);
						 len = pV->getSize(p);
						 }
      };





#endif  /* _VIRTTEXT_HPP_ */

