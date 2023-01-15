#ifndef _COMPILE_HPP_
#define _COMPILE_HPP_
#pragma once
#include <cstring>

enum ChartType { DefaultChart=1,BirthSgnOnly,BirthSgnHse,SgnHseAsp,Complete,
	CompleteBMid,CompleteFMid,Compatibility,Transits,Progress,Numeric, Helio,
	CReturn, Reloc, Compos, ComposTrans,Arabic,Fixed,Problem,
	SolarArc,Harmonic,Messier,CReturnReloc,CReturnTrans };

class ChartCompiler {
protected:
      FILE *stream;
      int mode, ftype;
      enum ChartType chartType;
      Options op;
      DATA_PACKET dp;
	  BIRTH_DB *with_rec;
      char ast_file[150], graph_file[150], grid_file[150];
      char comment_buf[80];
      char format[20];
      XPFILE_DB *out_file_ptr, *graph_ptr, *grid_ptr;
      XPFILE_DB wizfileinfo;
      bool bWizard;
	  int maxpt;
public:
	  void SetWizFileInfo( XPFILE_DB &info ) { wizfileinfo = info; }
	  int hasGraphFile( int type );
      ChartCompiler(enum ChartType tp, bool wiz=false, BIRTH_DB *wr=NULL)  { chartType = tp; stream = NULL; out_file_ptr =NULL; graph_ptr = NULL; bWizard=wiz; with_rec = wr;}
      virtual ~ChartCompiler() {memset(house_cusps,0,sizeof(short)*12); memset(alt_cusps,0,sizeof(short)*12);}
      FILE *openFile( char *file, int rpt=1 );
      int makeFile( int type, int grsave, char *name, char *cmt, int folder=-1 );

      int testErrno();
	  int customizeScreen( char *scr );
      virtual int doSetup();
      virtual int compile() {return 1;}
      virtual int doReport() {return 1;}
      virtual int writeData() {return 1;}
      virtual int writeGraph();
	  virtual int writeGrid();
      virtual int runChart();
      virtual int cleanUp(int ok);
	  void disclaim();
	  int setup();
	  void setFormat(const char *fmt) { strcpy(format, fmt);}
      XPFILE_DB *getOutFp() { return out_file_ptr; }
      XPFILE_DB *getGraphFp() { return graph_ptr; }
	  XPFILE_DB *getGridFp() { return grid_ptr; }
      };

#ifndef _QDTRAN_
class NatalChartCompiler : public ChartCompiler {
public:
      NatalChartCompiler(enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL) : ChartCompiler(tp,wiz,wr) {}
      virtual ~NatalChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
      };

class CompChartCompiler : public ChartCompiler {
public:
	CompChartCompiler(enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(tp,wiz) {}
      virtual ~CompChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
	  virtual int writeGrid();
      };

#ifdef DELUXE
class ProgChartCompiler : public ChartCompiler {
public:
      ProgChartCompiler(enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(tp,wiz) {}
      virtual ~ProgChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
#ifdef NEW
      virtual int writeGraph();
#endif
      };

class SolarChartCompiler : public ChartCompiler {
public:
      SolarChartCompiler(enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(tp,wiz) {}
      virtual ~SolarChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
#ifdef NEW
      virtual int writeGraph();
#endif
      };
class HarmonicChartCompiler : public ChartCompiler {
public:
      HarmonicChartCompiler(enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(tp,wiz) {}
      virtual ~HarmonicChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
#ifdef NEW
      virtual int writeGraph();
#endif
      };
#endif
#endif
class TransChartCompiler : public ChartCompiler {
public:
      TransChartCompiler(enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL) : ChartCompiler(tp,wiz,wr) {}
      virtual ~TransChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
	  virtual int writeGrid();
      };

#ifndef _QDTRAN_
#ifdef PRO
class OtherChartCompiler : public ChartCompiler {
public:

      OtherChartCompiler(enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(tp,wiz) {}
      virtual ~OtherChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
      int cleanUp(int ok);
      };
#endif
#ifdef DELUXE
class ReturnChartCompiler : public ChartCompiler {
public:
      ReturnChartCompiler(enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL) : ChartCompiler(tp,wiz,wr) {}
      virtual ~ReturnChartCompiler() {}
      virtual int doSetup();
      virtual int doReport();
	  virtual int writeGrid();
      };
#endif
#ifdef PRO
class ComTrnChartCompiler : public ChartCompiler {
public:
      ComTrnChartCompiler(enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(tp,wiz) {}
      virtual ~ComTrnChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
	  virtual int writeGrid();
      };
#endif
#endif
extern int x_kb_check();

#endif /* _COMPILE_HPP_ */
