#ifndef _FPRINT___HPP_
#define _FPRINT___HPP_

class FilePrinter : public CObject {
protected:
	int cxChar, cyChar, cxClient, cyClient;
	CFont *pfReg, *pfBold, *pfItal, *pfHead;
	CBrush *pbBack;
	COLORREF ctReg, ctBold, ctItal, ctHead;
	int cyCur, cxCur, cyBottom, cyTop, cxStart, cxTab, cyCharHead;
	int *pnWidReg, *pnWidItal, *pnWidBold, *pnWidHead;
	CRect rPage, rMargins, rActive;
	TextDecompressor *pTd;
	int nPage, fDrawLine, fHeadP1, nLofs, nLlen, fCenterHeads;
	CPen *pLinePen;
	CDC *dcPrint;
	int doRange, first, last, fno, dirtype, theAtr;
	char **flist, **tlist;
public:
      FilePrinter(char **pNames, int dir, char **pTlist=NULL );
      FilePrinter();
      ~FilePrinter();
      void setRange(int dr, int f=-1, int l=-1) {doRange = dr; first = f; last = l; }
      int getDepth( char *pTxt, int len, int flags, int &depth );
      int drawPara( char *pTxt, int len, int &flags, int &ofs );
      virtual BOOL morePages();
      virtual int print(CDC *pd, CRect *r);
      void setMargins( CRect &r ) { rMargins = r; }
      int printHeader();
      int checkDepth( char *pt, int len, int atr, int &depth );
      int doPrint();
      int newFile(char *pNames);
      void setFileDB( FILE_DB *f ) { *pTd->getFpt() = *f; }
      };



#endif /* _FPRINT___HPP_ */
