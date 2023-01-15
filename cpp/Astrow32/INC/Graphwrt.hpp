#ifndef _GRAPHWRT_HPP_
#define _GRAPHWRT_HPP_

class GraphWriter : public GraphData {
protected:
   void nameDateTime1( char *n, char *d, char *t ) { strcpy(data->name1,n); strcpy( data->date1,d); strcpy( data->time1,t);  }
   void nameDateTime2( char *n, char *d, char *t ) { strcpy(data->name2,n); strcpy( data->date2,d); strcpy( data->time2,t);  }
   void tropHouseProc( char *tr, char *hs ) { strcpy(data->trop_side,tr); strcpy(data->house_proc,hs); }
   void houseCusps( short *h, short *h2=NULL ) { memcpy( &data->natal_house_cusps, h, 24 ); if (h2) memcpy( &data->other_house_cusps, h2, 24 ); }
   void planets( AS_INF * i, int c, int w=1, short *array=NULL, int start=0 );
#ifdef DELUXE
   int countGridAspects(AS_INF *inf, int cnt);
#endif
   int countAspects(AS_INF *inf, int cnt);
   int setupAspects(AS_INF *inf, int cnt);
#ifdef DELUXE
   GR_ASPT *setupGridAspects(AS_INF *inf, int cnt, int &n, int start = 0);
   GR_DATALST *setupDataList(AS_INF *inf, int cnt, int mode, int &n);
#endif
public:
   GraphWriter() {}
   GraphWriter( BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr);
   ~GraphWriter() {}
   };

#ifndef _QDTRAN_
#ifdef DELUXE
class ProgGraphWriter : public GraphWriter {
   public:
   ProgGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr, PROGR_DATA *p, AS_INF *alt, AS_INF *prog);
   ~ProgGraphWriter() {}
   };

class SolarGraphWriter : public GraphWriter {
   public:
   SolarGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr, DIREC_DATA *p, AS_INF *alt);
   ~SolarGraphWriter() {}
   };

class HarmonicGraphWriter : public GraphWriter {
   public:
   HarmonicGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr, int harmonic, AS_INF *alt);
   ~HarmonicGraphWriter() {}
   };
#endif

class CompGraphWriter : public GraphWriter {
   public:
   CompGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr, AS_INF *alt, BIRTH_DB *other, int mode2 );
   ~CompGraphWriter() {}
   };
#endif

class TransGraphWriter : public GraphWriter {
   public:
   TransGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr, BIRTH_DB *trans, TRANS_DATA *tp, AS_INF **alt, DATES *dates_ptr);
   ~TransGraphWriter() {}
   };

#ifndef _QDTRAN_
#ifdef PRO
class CompTransGraphWriter : public TransGraphWriter {
   public:
   CompTransGraphWriter(BIRTH_DB *birth, AS_INF *inf, int type, int mode, int house_proc, XPFILE_DB *ptr, BIRTH_DB *trans, TRANS_DATA *tp, AS_INF **alt, DATES *dates_ptr, BIRTH_DB *other );
   ~CompTransGraphWriter() {}
   };
#endif
#endif
#endif /* _GRAPHWRT_HPP_ */

