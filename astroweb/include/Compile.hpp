#ifndef _COMPILE_HPP_
#define _COMPILE_HPP_
#pragma once

#include <cstring>

enum ChartType { DefaultChart=1,BirthSgnOnly,BirthSgnHse,SgnHseAsp,Complete,
	CompleteBMid,CompleteFMid,Compatibility,Transits,Progress,Numeric, Helio,
	CReturn, Reloc, Compos, ComposTrans,Arabic,Fixed,Problem,
	SolarArc,Harmonic,Messier,CReturnReloc,CReturnTrans, Horary };

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
      BOOL bWizard;
	  BOOL bAutoOpen;
      char *format;
      char *basename;
      int maxpt;
      Options options;
    public:
	  void SetWizFileInfo( XPFILE_DB &info ) { wizfileinfo = info; }
	  int hasGraphFile( int type );
      ChartCompiler(enum ChartType tp, char *_basename, char *_format)  { chartType = tp; basename = _basename, format=_format; stream = NULL; out_file_ptr =NULL; graph_ptr = NULL;  bAutoOpen=FALSE;}
      virtual ~ChartCompiler() {memset(birth_inf,0,sizeof(AS_INF)*30); memset(alt_inf,0,sizeof(AS_INF)*30); memset(birth_inf,0,sizeof(AS_INF)*30); memset(house_cusps,0,sizeof(short)*12); memset(alt_cusps,0,sizeof(short)*12);}
      FILE *openFile( char *file, int rpt=1 );
      int makeFile( int type, int grsave, char *name, char *cmt, int folder=-1 );
      int testErrno();
      int setup();
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
      char *getBasename() {return basename;}
      char *getFormat() { return format; }
      void setFormat(char *_format) { format=_format; }
      void setOptions(Options &opt) {
            options = opt;
            op = opt;
        }
      };


class NatalChartCompiler : public ChartCompiler {
public:
      NatalChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {dp=birth_dp;}
      virtual ~NatalChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
      };

class HoraryChartCompiler : public ChartCompiler {
public:
      HoraryChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {dp=horary_dp;}
      virtual ~HoraryChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
      };


class CompChartCompiler : public ChartCompiler {
public:
	CompChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {}
      virtual ~CompChartCompiler() {dp=comp_dp;}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
	  virtual int writeGrid();
      };

class ProgChartCompiler : public ChartCompiler {
public:
      ProgChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp, _basename,_format) {dp=progr_dp;}
      virtual ~ProgChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
      virtual int writeGraph();
      };

class SolarChartCompiler : public ChartCompiler {
public:
      SolarChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp,_basename,_format) {dp=solar_dp;}
      virtual ~SolarChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
      virtual int writeGraph();
      };
/*class HarmonicChartCompiler : public ChartCompiler {
public:
      HarmonicChartCompiler(enum ChartType tp,char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {}
      virtual ~HarmonicChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
#ifdef NEW
      virtual int writeGraph();
#endif
      };*/
class TransChartCompiler : public ChartCompiler {
public:
      TransChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {dp = trans_dp;}
      virtual ~TransChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
	  virtual int writeGrid();
      };

class OtherChartCompiler : public ChartCompiler {
public:
      OtherChartCompiler(enum ChartType tp,char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {}
      virtual ~OtherChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
	  virtual int writeGrid();
      int cleanUp(int ok);
      };

class ReturnChartCompiler : public ChartCompiler {
public:
      ReturnChartCompiler(enum ChartType tp,char *_basename, char *_format) : ChartCompiler(tp,_basename, _format) {}
      virtual ~ReturnChartCompiler() {}
      virtual int doSetup();
      virtual int doReport();
	  virtual int writeGrid();
      };

class ComTrnChartCompiler : public ChartCompiler {
public:
      ComTrnChartCompiler(enum ChartType tp, char *_basename, char *_format) : ChartCompiler(tp, _basename, _format) {}
      virtual ~ComTrnChartCompiler() {}
      virtual int doSetup();
      virtual int compile();
      virtual int doReport();
      virtual int writeData();
      virtual int writeGraph();
	  virtual int writeGrid();
      };
extern int x_kb_check();

/* _COMPILE_HPP_ */
#endif
