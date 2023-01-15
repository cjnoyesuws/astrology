#ifndef _FILELST__HPP_
#define _FILELST__HPP_

#ifndef WINAPI
#include "stdafx.h"
#endif

#ifndef _ASTRO____H___
#include "astro.h"
#endif

#ifndef _USERI____H___
#include "useri.h"
#endif

typedef struct AryFldItem {
   CPtrArray ar;
   int count;
};


typedef struct AryItem {
	CPtrArray fldAr;
	AryFldItem *fldp;
	CPtrArray *ar;
	int fldcount;
	int totalcount;
	int count;
	CPtrArray *get(int fld);
    void add();
	void addTo(int n);
    void free();
	void SelectAll(BOOL bSelect, int fld=DEFAULT_FLD);
    } AryItem;

typedef struct AryGroup {
	AryItem all;
	AryItem text;
	AryItem graph;
	AryItem grid;
    AryItem &get(int type=ALL_F,int fld=DEFAULT_FLD);
} AryGroup;


class FileListArray {
      char name[150];
      int     last_no;
      int     is_dirty;
      int     _in_mem;
	  int     curFolder;
protected:
      long initFileScan(char *buf, char *ext );
      long fileScanCont( char *buf, long h );
	  int append(XPFILE_DB *f );
	  int fldcheck(int fld) { return (fld==-1?curFolder:fld); }
      XPFILE_DB *addFile( XPFILE_DB *ptr, NUM type );
      void makeFileName( NUM type, XPFILE_DB far *ptr );
      int hasFile( char *name, char *ext );
      int isFileInQue( char *name, int type );
public:
	  AryGroup arraygroup;
      FileListArray() { }
      FileListArray(int doInit, int size = 10);
      ~FileListArray() { free(); }
	  int &GetCurFolder() { return curFolder; }
	  void setName( char *f, int dir = USER_F );
      int getCount(int type =ALL_F,int fld=-1);
      int read();
      int write();
      void release();
      int iTop(int type, int fld = -1);
      int iBottom(int type, int fld = -1);
      XPFILE_DB *top(int type=ALL_F, int fld = -1);
      XPFILE_DB *bottom(int type=ALL_F, int fld = -1);
      XPFILE_DB *topPlus( int n, int type=ALL_F, int fld = -1);
      int iTopPlus( int n, int type=ALL_F, int fld =-1 );
      XPFILE_DB *bottomMinus( int n, int type=ALL_F, int fld = -1 );
      int doAddFile( CWnd *pPar, int type, int graph, char *name, int dogrid,
         char *cmt, char *tfile, char *gfile, char *grdfile, XPFILE_DB **gptr, 
		 XPFILE_DB **tptr, XPFILE_DB **grdptr, int folder, BOOL &bAuto);
      int killFile( XPFILE_DB far *f );
      void killWholeFileList();
      void remFile( char *name );
      void check();
      int quit();
      void free();
      void doFileScan();
	  int DoFileScanLoop(char *ext, int type );
      XPFILE_DB *addEntry( XPFILE_DB *p, int upd=1, BOOL bAdd=FALSE );
      int deleteEntry( XPFILE_DB *p );
      int dirty() { return is_dirty; };
      void dirty( int i) { is_dirty = i; }
      int keep() { return 1; }
      void keep(int k) {}
      int inMem() { return( _in_mem ); }
      void inMem(int i ) {_in_mem = i;}
      CPtrArray &fileDBArray(int t, int fld = -1) { return *arraygroup.get(t,fldcheck(fld)).ar; }
      int &fileCount(int type, int fld = -1) { return arraygroup.get(type,fldcheck(fld)).count; }
	  int selCount( int type=ALL_F, int fld = -1);
      int getSelection(int type, int nSel, CWordArray &nar, int fld = -1 );
      void sortFiles();
      void killSelectedFiles(CWnd *pPar, int type, int fld = -1);
      void killSelectedFilesAll(CWnd *pPar, int type=ALL_F, int fld = -1);
	  int doKillFile(XPFILE_DB *ptr, CWnd *pPar);
      void changeEntry( XPFILE_DB *ptr, CWnd *pPar );
      void scanFiles();
      void clearSel( int type=ALL_F, int fld = -1 );
      int findFirst( CWnd *pPar, int type, int fld = -1 );
      int findCont( int type, int start, int fld = -1 );
      int iCursor(int val, int type=ALL_F, int fld = -1 );
      int isAQueFile(char *name);
      int findPtr( int type, XPFILE_DB *ptr );
      void SortAnArray(int type);
      void Add(int type,XPFILE_DB *p);
	  void UpdatePtr(XPFILE_DB *p);
	  void SelectAll(int type=ALL_F, int fld=-1, BOOL bSelect=TRUE) {
	     if (fld==1)
			 fld =GetCurFolder();
		 arraygroup.get(type,fld).SelectAll(bSelect);
	    }
      };

extern FileListArray AstFileList;



inline int isDelFile(XPFILE_DB *p)
{
 return( p->type == DELETED_FILE );
}

inline int isGraphFile(XPFILE_DB *p)
{
 return( (p->type != DELETED_FILE &&  p->type > LAST_NON_GRAPH && p->type <= LAST_GRAPH) );
}

inline int isGridFile(XPFILE_DB *p)
{
 return( (p->type != DELETED_FILE &&  p->type > LAST_GRAPH) );
}


inline int isTextFile(XPFILE_DB *p)
{
 return( ( p->type != DELETED_FILE && p->type < LAST_NON_GRAPH) );
}

inline void mrkDelFile(XPFILE_DB *p)
{
 p->type = DELETED_FILE;
}

extern char *replace_ext(char *buf, char *name, char *ext );
extern int getFileCount( CWordArray &war, CPtrArray &par, int n, int cmt, int cvr );
extern int getFileList( CStringArray &sar, CWordArray &war, CPtrArray &par, int n, int sz, int b4, int cmt, int cvr );

extern void GetFileListPtrAndType( FileListArray **ptr, int &type, void *p );
extern void FlistDoUpdate(int type);
extern void PutBackFileListPtrAndType( FileListArray *ptr, int type );

#endif /* _FILELST__HPP_ */
