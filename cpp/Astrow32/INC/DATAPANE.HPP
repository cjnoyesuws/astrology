#ifndef _DATAPANE_HPP_
#define _DATAPANE_HPP_


class AstDataPane : public zPane {
AstData *data;
public:
      AstDataPane( zWindow *w, int wh, GraphData *pData );
      ~AstDataPane();
      virtual int draw( zDrawEvt *e );
      virtual void setMetrics();
      virtual int size( zSizeEvt *e);
      int menuCommand( zCommandEvt *e );
      int command( zCommandEvt *e );
      void setupMenu();
      int doPrint(zEvent *);
      virtual int morePages();
      virtual int print(zPrinterDisplay *pd, zRect *);
      void copyToClipboard();
      int export();
      };

class AstDataFrame : public zMDIChildFrame {
AstDataPane *pane;
public:
	AstDataFrame(zFrameWin *pPar, int wh, GraphData *pData );
	~AstDataFrame() {}
	virtual int focus(zFocusEvt *focEvt);
	virtual int MDIActivate(zActivateEvt *actEvt);
	void setFocus() { pane->setFocus(); }
	};

#endif /* _DATAPANE_HPP_ */
