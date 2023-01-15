#ifndef _PRNTSETP_HPP_
#define _PRNTSETP_HPP_

class PrinterSetup {
DEVMODE *pMode;
int orientation;
int color;
int copies;
int yres;
int scale;
int quality;
int duplex;
int source;
int size;
zPrinterSpec *ps;
public:
      PrinterSetup();
      ~PrinterSetup() {if (ps) delete ps; if (pMode) delete pMode; }
      int saveToIni( char *sec );
      int getFromIni( char *sec );
      zPrinterSpec *getSpec() { return ps; }
      int newChoice( char *c );
      DEVMODE *toDevMode(zWindow *w, int prompt);
      int getColor() { return color; }
      };

class PrinterSetupDlgf : public FormDlgf {
zWindow *pw;
zListBox *box;
PrinterSetup *data;
int type;
zString choice;
public:
      PrinterSetupDlgf(zWindow *pPar, PrinterSetup *d, int t);
      ~PrinterSetupDlgf() {}
      virtual int command(zCommandEvt *e);
      int doOk(zEvent *e);
      void doSetup(int d);
      int printerChanged();
      };


#endif /* _PRNTSETP_HPP_  */
