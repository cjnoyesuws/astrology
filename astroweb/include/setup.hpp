#ifndef _SETUP___HPP_
#define _SETUP___HPP_

struct OPTIONS {
    unsigned int flags;
    short house_mode;
    short charts;
    int chart_code;
    int datafile;
	int def_rectmethod;
	char format[10];
    };

class Options {
private:
    OPTIONS op;
public:
    Options() { op.datafile = -1; }
    ~Options() {}
    OPTIONS &getOpt() { return op; }
    void setOpt( unsigned int fl, short hm, short ch, short chc, short dr ) {
		op.flags = fl; op.house_mode = hm; op.charts = ch; op.chart_code = chc; op.def_rectmethod=dr; }
    unsigned int &getFlags() { return op.flags; }
    void setFlags(unsigned int flags) { op.flags = flags;}
    short &getHouseMode() { return op.house_mode; }
    void setHouseMode(short val) { op.house_mode = val;}
    short &getCharts() { return op.charts; }
    void setChartCode(int val) { op.chart_code = val;}
    int &getChartCode() { return op.chart_code; }
    void setDatafile( int val ) { op.datafile = val; }


    int &getDatafile() { return op.datafile; }
	int &getDefRectMethod() { return op.def_rectmethod; }
	void setDefRectMethod( short val ) { op.def_rectmethod = val; }
	char *getFormat() { return op.format;}
	void setFormat(const char *fmt) { strcpy(op.format,fmt);}
	};

// Useful Macros

#define is_set(x,n)   (((x)&(n))?1:0)
#define set_it(v,n,x) v|=((x)?(n):0)


#endif /* _SETUP___HPP_ */

