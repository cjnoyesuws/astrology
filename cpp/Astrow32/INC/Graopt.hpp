#ifndef _GRAOPT___HPP_
#define _GRAOPT___HPP_

class GraphOptions {
   unsigned short drawMode;
   short fontSize;
public:
   GraphOptions() { drawMode = HOUSE_DEG | HOUSE_NUM | SHOW_ASPT | SIGN_TICK| DEC_TICK | DEG_TICK;
		    fontSize = 100; }
   ~GraphOptions() {}
   short &getFontSize() { return fontSize; }
   unsigned short &getDrawMode() { return drawMode; }
   int getOpt(unsigned short o) {return drawMode & o;}
   void setOpt(unsigned short o, short v) { if (v) drawMode |= o; else drawMode &= (o^0xffff); }
   int saveToIni( char *sec );
   int getFromIni( char *sec );
   };

/*

class GraphOptionsDlgf : public FormDlgf {
int showhcd, showhcn, showsigl, showaspl, usegl, signtick;
int dectick, degtick, show_signname, plotclass, hsnmout, showdegs;
#ifdef NEW
int agrid;
#endif
int type;
GraphOptions *gr;
public:
      GraphOptionsDlgf(zWindow *pPar, GraphOptions *g, int t=0);
      ~GraphOptionsDlgf() {}
      virtual int command( zCommandEvt *e );
      void getData();
      };

class GraphOptionsScreen {
GraphOptions bg, *gp;
public:
      GraphOptionsScreen(zWindow *pPar, GraphOptions *g, int t=0);
      ~GraphOptionsScreen() {}
      };

*/
#endif /* _GRAOPT___HPP_ */
