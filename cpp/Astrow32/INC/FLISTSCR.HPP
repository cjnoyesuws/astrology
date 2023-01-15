#ifndef _FLISTSCR_HPP_
#define _FLISTSCR_HPP_

class FileListPane : public zPane {
zExchangeFmt *pxText, *pxGraph;
FILE_DB cut_buf, *cut_at, *curMrk, *ins_at;
int was_cut;
int cxChar, cyChar, cxStart, cyStart;
int cxWidName, cyDepth, cyRule, cxWid, cxClient, cyClient;
int cxWidFlags, cxLeft, yCnt, shiftState;
zFont *pFnt;
zPen *ppnNorm, *ppnSel;
zBrush *pbrSel, *pbrNorm;
zBitmap *pbmGra, *pbmTxt, *pbmChk;
int nTopItem, dblclkTime;
protected:
      int yCursor, type;
public:
      zClipboard *pClip;
      FileListArray *pFla;
      zMenu *pMenu;
      FileListPane(FileListArray *a, int t, zWindow *w);
      ~FileListPane();
      virtual draw( zDrawEvt *e );
      int drawHeader();
      int drawItem(FILE_DB *i, int y, int mrk);
      virtual void setMetrics();
      virtual int size( zSizeEvt *e);
      virtual int scroll( zEvent *e );
      void updateScroller();
      virtual int mouseButtonDown( zMouseClickEvt *e );
      int kbhnd( zKeyEvt *e );
      void hideCursor(FILE_DB *fdpx=NULL, int ofs=0 );
      void showCursor(FILE_DB *fdpx=NULL, int ofs=0);
      virtual int doCommand( zCommandEvt *e );
      virtual void dofunc(FILE_DB *p);
      FILE_DB *getCursor() {return (FILE_DB far *)pFla->topPlus(yCursor,type); }
      int update();
      void setupEditMenu();
      int getType() { return type; }
      };

class FileListFrame : public zMDIChildFrame {
protected:
FileListPane *pane;
public:
	FileListFrame(zFrameWin *pPar, FileListArray *a, int t, char *name);
	~FileListFrame() { }
	virtual int focus(zFocusEvt *focEvt);
	virtual int MDIActivate(zActivateEvt *actEvt);
	virtual int kill( zEvent *e );
	int update() { return( pane->update() ); }
	};

#endif /* _FLISTSCR_HPP_ */
