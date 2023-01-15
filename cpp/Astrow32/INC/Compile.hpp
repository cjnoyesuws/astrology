#ifndef _COMPILE_HPP_
#define _COMPILE_HPP_
#pragma once

#include <afxcoll.h>

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
      XPFILE_DB *out_file_ptr, *graph_ptr, *grid_ptr;
      XPFILE_DB wizfileinfo;
	  CWnd *pParw;
	  ProcMsg *pm;
	  BOOL bWizard;
	  BOOL bAutoOpen;
	  CPtrArray *pDataArray;
public:
	  void SetWizFileInfo( XPFILE_DB &info ) { wizfileinfo = info; } 
	  void SetPtrDataArray( CPtrArray *par ) { pDataArray=par; };
	  int hasGraphFile( int type );
      ChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL)  { pParw = pPar; chartType = tp; stream = NULL; out_file_ptr =NULL; graph_ptr = NULL; bWizard=wiz; with_rec = wr; pDataArray = NULL; bAutoOpen=FALSE;}
      virtual ~ChartCompiler() {memset(birth_inf,0,sizeof(AS_INF)*30); memset(alt_inf,0,sizeof(AS_INF)*30); memset(birth_ext,0,sizeof(AS_INF_EXT)*30); memset(house_cusps,0,sizeof(short)*12); memset(alt_cusps,0,sizeof(short)*12);}
      FILE *openFile( char *file, int rpt=1 );
      int makeFile( int type, int grsave, char *name, char *cmt, int folder=-1 );
      int testErrno();
	  void setAutoOpen(BOOL bAuto=TRUE) { bAutoOpen=bAuto; }
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
      XPFILE_DB *getOutFp() { return out_file_ptr; }
      XPFILE_DB *getGraphFp() { return graph_ptr; }
	  XPFILE_DB *getGridFp() { return grid_ptr; }
      };

#ifndef _QDTRAN_
class NatalChartCompiler : public ChartCompiler {
public:
      NatalChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL) : ChartCompiler(pPar,tp,wiz,wr) {}
      virtual ~NatalChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
      };

class CompChartCompiler : public ChartCompiler {
public:
	CompChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(pPar,tp,wiz) {}
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
      ProgChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(pPar,tp,wiz) {}
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
      SolarChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(pPar,tp,wiz) {}
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
      HarmonicChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(pPar,tp,wiz) {}
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
      TransChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL) : ChartCompiler(pPar,tp,wiz,wr) {}
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
      OtherChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(pPar,tp,wiz) {}
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
      ReturnChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE, BIRTH_DB *wr=NULL) : ChartCompiler(pPar,tp,wiz,wr) {}
      virtual ~ReturnChartCompiler() {}
      virtual int doSetup();
      virtual int doReport();
	  virtual int writeGrid();
      };
#endif
#ifdef PRO
class ComTrnChartCompiler : public ChartCompiler {
public:
      ComTrnChartCompiler(CWnd *pPar, enum ChartType tp, BOOL wiz=FALSE) : ChartCompiler(pPar,tp,wiz) {}
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
