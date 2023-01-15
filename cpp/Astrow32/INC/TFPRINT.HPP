#ifndef _TFPRINT__HPP_
#define _TFPRINT__HPP_

class TbtFilePrinter : public zEvH {
protected:
	int cxChar, cyChar, cxClient, cyClient;
	zFont *pfReg, *pfBold, *pfItal, *pfHead, *pfHeader;
	zBrush *pbBack;
	zColor ctReg, ctBold, ctItal, ctHead;
	int cyCur, cxCur, cyBottom, cyTop, cxStart, cxTab, cyCharHead;
	int *pnWidReg, *pnWidItal, *pnWidBold, *pnWidHead, *pnWidHeader;
	zRect rPage, rMargins, rActive;
	FILE *stream;
	int nPage, fDrawLine, fHeadP1, nLofs, nLlen, fCenterHeads;
	zPen *pLinePen;
	zPrinterDisplay *pdr;
	int doRange, first, last, fno, dirtype, theAtr;
	char name[150], *tbuf;
public:
      TbtFilePrinter(char *pName);
      TbtFilePrinter();
      ~TbtFilePrinter();
      void setRange(int dr, int f=-1, int l=-1) {doRange = dr; first = f; last = l; }
      virtual int printSetup(zPrinterDisplay *pr, zPrintJob *pj);
      int getDepth( char *pTxt, int len, int flags, int &depth );
      int drawPara( char *pTxt, int len, int &flags, int &ofs );
      virtual BOOL morePages();
      virtual int print(zPrinterDisplay *pd, zRect *r);
      void setMargins( zRect &r ) { rMargins = r; }
      int printHeader();
      int checkDepth( char *pt, int len, int atr, int &depth );
      int doPrint();
      };


class TbtFilePrintJobDlg : public zPrJobDlg {
int pgnum;
zDefPushButton *cancel;
zStaticText *pageInfo ;
public:
      TbtFilePrintJobDlg();
      ~TbtFilePrintJobDlg();
      virtual void setPage( int page );
      int doCancel(zEvent *e );
      };



#endif /* _TFPRINT__HPP_ */
