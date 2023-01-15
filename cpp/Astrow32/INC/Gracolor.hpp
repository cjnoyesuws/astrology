#ifndef _GRACOLOR_HPP_
#define _GRACOLOR_HPP_

class GraphicColors {
AstDrawBase *pBase;
int dodel;
int RevBack;
public:
    GraphicColors( CDC *d ) { pBase = new AstDrawBase(d); dodel=1; }
    GraphicColors( AstDrawBase *b ) { pBase = b; dodel=0; }
    ~GraphicColors() { if ( dodel ) { pBase->deInit(); delete pBase; } }
    int &getRevBack() {return RevBack;}
	COLORREF &getColor(int i) { return pBase->getColor(i); }
    int getFromIni(char *sec);
    int saveToIni(char *sec);
    AstDrawBase *getBase() { return pBase; }
    };

/*
class GraphicColorsDlgf : public FormDlgf {
GraphicColors *data;
public:
      GraphicColorsDlgf(zWindow *par, GraphicColors *g);
      ~GraphicColorsDlgf() {}
      virtual int command(zCommandEvt *e);
      };

*/
#endif /* _GRACOLOR_HPP_  */

