#ifndef _DATAKEY__HPP_
#define _DATAKEY__HPP_

#define OLD 0
#define PRX 1
#define TWO 2
#define WIN 3
#define PRG 4
#define TRN 5
#define CPT 6
#define SOL 7
#define HRM 8

class DataKey : public AstDrawBase {
short fudge;
CDC *zd;
CFont *fnt, *bfnt;
GR_DAT *data;
int yDeep;
char *date2;
public:
      DataKey(CDC *z, CFont *f, CFont *fb, int yd, GR_DAT *d );
      ~DataKey() { }	 
      int type();
      void drawKey();
      void tropSideHpc(int w);
      void title();
      void nameDateTime(int w);
      void setDate2( char *d ) { date2 = d; }
      void compTran();
      };

#ifdef NEW
#ifdef DELUXE
class PlanetsKey : public AstDrawBase {
int yDeep, xClient;
CDC *zd;
CFont *fnt;
PlanGrfa *p;
public:
      PlanetsKey(CDC *z, CFont *f, int yd, int x, GraphicDataGroup *d );
      ~PlanetsKey() {  }
      void draw();
      };
#endif
#endif


#endif /* _DATAKEY__HPP_ */
