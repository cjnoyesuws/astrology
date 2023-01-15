#ifndef _SETUP___HPP_
#define _SETUP___HPP_



typedef struct OPTIONS {
    unsigned short flags;
    short house_mode;
    short charts;
    int chart_code;
    short datafile;
	short def_rectmethod;
    } OPTIONS;

class Options {
private:
    OPTIONS op;
public:
    Options() { op.datafile = -1; }
    ~Options() {}
    OPTIONS &getOpt() { return op; }
    void setOpt( unsigned short fl, short hm, short ch, short chc, short dr ) {
		op.flags = fl; op.house_mode = hm; op.charts = ch; op.chart_code = chc; op.def_rectmethod=dr; }
    int readFromIni( char *var, char *section=ChartSetup_SEC );
    int saveToIni( char *var, char *section=ChartSetup_SEC );
    unsigned short &getFlags() { return op.flags; }
    short &getHouseMode() { return op.house_mode; }
    short &getCharts() { return op.charts; }
    int &getChartCode() { return op.chart_code; }
    short &getDatafile() { return op.datafile; }
	short &getDefRectMethod() { return op.def_rectmethod; }
	};

class ChartSetup {
private:
      Options birth;
      Options compat;
      Options trans;
      Options progr;
      Options numer;
      Options reloc;
      Options compos;
      Options fixstar;
      Options arabpt;
      Options comptr;
      Options solar;
	  Options harmonic;
public:
      ChartSetup() { init(); }
      ~ChartSetup() {}
      void init();
      Options &getBirthOpt() { return birth; }
      Options &getCompatOpt() { return compat; }
      Options &getTransOpt() { return trans; }
      Options &getProgrOpt() { return progr; }
      Options &getNumerOpt() { return numer; }
      Options &getRelocOpt() { return reloc; }
      Options &getComposOpt() { return compos; }
      Options &getFixstarOpt() { return fixstar; }
      Options &getArabptOpt() { return arabpt; }
      Options &getComptrOpt() { return comptr; }
      Options &getSolarOpt() { return solar; }
	  Options &getHarmonicOpt() { return harmonic; }
      int readFromIni( char *section=ChartSetup_SEC );
      int saveToIni( char *section=ChartSetup_SEC );
      };

extern ChartSetup setup_dat;

// Useful Macros

#define is_set(x,n)   (((x)&(n))?1:0)
#define set_it(v,n,x) v|=((x)?(n):0)


#endif /* _SETUP___HPP_ */

