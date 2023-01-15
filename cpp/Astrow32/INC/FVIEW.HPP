#ifndef  _FVIEW____HPP_
#define _FVIEW____HPP_


class FileViewPane : public zPane {
LOC top, bottom;
int cxChar, cyChar, cxClient, cyClient;
zFont *pfReg, *pfBold, *pfItal, *pfHead;
zBrush *pbBack;
zColor ctReg, ctBold, ctItal, ctHead;
zColor cbReg, cbSel, cbUsed;
int cyCur, cxCur, cyLines, cxStart, cxTab;
zRect rActive;
zString search;
int selPara, dirty;
int *pLineParaTrans;
int dblclkTime;
public:
      VirtualTextBuffer *pVTBuf;
      zMenu *pMenu;
      FileViewPane( char *name, zWindow *w, int dir);
      ~FileViewPane();
      virtual int draw( zDrawEvt *e );
      int drawPara( char *pTxt, int len, unsigned char &flags, int &ofs );
      virtual void setMetrics();
      virtual int size( zSizeEvt *e);
      virtual int scroll( zEvent *e );
      void updateScroller();
      virtual int mouseButtonDown( zMouseClickEvt *e );
      int kbhnd( zKeyEvt *e );
      virtual int command( zCommandEvt *e );
      int up1Page();
      int getPrevBreak( char *pText, int len, int offset, unsigned char &flags );
      int getNextBreak( char *pText, int len, int offset, unsigned char &flags );
      int getBreaks( char *pTxt, int len, unsigned char flags,
	    int *array, unsigned char *flary, int nBrkMax );
      int findTopic( char *topic );
      void updateLineParaTrans(int ofs );
      };

class FileViewFrame : public zMDIChildFrame {
FileViewPane *pane;
int _dir;
zString name;
public:
	FileViewFrame(zFrameWin *pPar, char *pName, int dir);
	~FileViewFrame() {}
	virtual int focus(zFocusEvt *focEvt);
	virtual int MDIActivate(zActivateEvt *actEvt);
	void setFocus() { pane->setFocus(); }
	void setFileDb(FILE_DB *f) { pane->pVTBuf->getFileDb() = *f; }
	void setupEditMenu(int i);
	virtual int kill(zEvent *e);
	int findTopic( char *topic ) { return( pane->findTopic( topic ) ); }
	};

#endif /* _FVIEW____HPP_ */
