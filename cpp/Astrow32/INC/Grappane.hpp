#ifndef _GRAPPANE_HPP_
#define _GRAPPANE_HPP_

typedef struct Radius {
	int offset;
	int outsideCirc;
	int aspectCirc;
	int secondCirc;
	int degreeTick;
	int signTick;
	int decanTick;
	int midCirc;
	int mainCirc;
	int margin;
	int points;
	int inCirc;
	int getOffset() { return offset; }
	int getOutsideCirc() { return outsideCirc; }
	int getAspectCirc() { return aspectCirc; }
	int getSecondCirc() { return secondCirc; }
	int getDegreeTick() { return degreeTick; }
	int getSignTick() { return signTick; }
	int getDecanTick() { return decanTick; }
	int getMidCirc() { return midCirc; }
	int getMainCirc() { return mainCirc; }
	int getMargin() { return margin; }
	int getPoints() { return points; }
	int getInCirc() { return inCirc; }
#ifdef NEW
	int isInOusideCirc(int r) { return r < outsideCirc; }
	int isInAspectCirc(int r) { return r < aspectCirc; }
	int isInSecondCirc(int r) { return r < secondCirc; }
	int isInMainCirc(int r) { return r < mainCirc; }
#endif
} Radius;

class AstGraphicsPane : public zPane {
int cxClient, cyClient, cxChar, cyChar;
zRect rActive;
int fToFit;
int cxLeftOffset, cyTopOffset;
int cxLeftMgn, cyTopMgn;
float scale, fontScale;
Radius radiusData;
GraphicDataGroup *dataGroup, *compGroup;
zFontSpec *pGlyphSpec, *pDegSpec, *pTickGlyphSpec;
zFont *pDataFnt, *pGlyphFnt, *pDegFnt, *pTickGlyphFnt;
zFont *pBdDataFnt;
AstDrawBase *baseMetrics;
zBrush *pbBack;
int _isOk;
unsigned drawMode;
int which_houses, asc_min, offset, old_asc_min;
GR_CHART *pCurChart;
#ifdef NEW
unsigned long dblclkTime;
PlanetPlotter *plot;
PlanetPlotter *plot2;
zFont *pGridFont;
int gridMaxpt;
GR_ASPT *gridAspts;
int gridCnt;
#endif
public:
      GraphData *data;
      zMenu *pgMenu, *parMenu;
      zClipboard *pClip;
      AstGraphicsPane( char *name, zWindow *w, int dir);
      ~AstGraphicsPane();
      virtual int draw( zDrawEvt *e );
      virtual void setMetrics();
      virtual int size( zSizeEvt *e);
      virtual int scroll( zEvent *e );
      void updateScroller();
      virtual int mouseButtonDown( zMouseClickEvt *e );
      int kbhnd( zKeyEvt *e );
      int isOk() { return _isOk; }
      unsigned int &getDrawMode() {return drawMode; }
      int fontSize(int div);
      void computeRadiusData();
      void updateGrfas();
      int menuCommand( zCommandEvt *e );
      int command( zCommandEvt *e );
      void setupMenu();
      int doPrint(zEvent *);
      virtual int morePages();
      virtual int print(zPrinterDisplay *pd, zRect *);
      void copyToClipboard();
      int toWMF(char *name, int place=1, int color=1, int rev=0);
      int toBitmap( zBitmap *bm );
      int toDib( zDib *bm, int color, int rev );
      int export();
#ifdef NEW
      GR_ASPT *findAspect( zPoint &p );
      int toDegrees( zPoint &p, int &rad );
      int doPop( zPoint &p, char *file );
#endif
      };

class AstGraphicsFrame : public zMDIChildFrame {
int _dir;
zString name;
AstGraphicsPane *pane;
int _isOk;
public:
	AstGraphicsFrame(zFrameWin *pPar, char *pName, int dir);
	~AstGraphicsFrame() {} 
	virtual int focus(zFocusEvt *focEvt);
	virtual int MDIActivate(zActivateEvt *actEvt);
	void setFocus() { pane->setFocus(); }
	int isOk() { return _isOk; }
	virtual int kill(zEvent *e);
	};

extern int doPrintSelGraphFile(zWindow *pPar, FileListArray *fla );

#endif /* _GRAPPANE_HPP_ */
