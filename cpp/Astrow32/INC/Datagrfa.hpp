#ifndef _DATAGRFA_HPP_
#define _DATAGRFA_HPP_

class Grfa {
char buf[15];
int  adj;
int  rad;
public:
      Grfa()  { buf[0]='\0'; rad = -1, adj = -1;}
      ~Grfa() {}
      void format( int d, int mode );
      char *get() { return buf; }
      void setAdj(int a) { adj = a; }
      int &getAdj() { return adj; }
      int &getRad() { return rad; }
      void setRad(int r) { rad = r; }
      void offsetMin( int min, int offset, int asc, int mode );
      };

class PlanGrfa {
protected:
    Grfa gr[30];
    short  *array;
	int  mode;
	int  count;
    int  house_offset;
	int  asc_min;
public:
	PlanGrfa() {}
	~PlanGrfa() {}
	void doGrfdArray(int ofs);
	void setAscMin( int a ) { asc_min = a; }
	int getCount() { return count; }
	void setCount(int c) { count = c; }
	char *getGrfa( int i ) { return gr[i].get(); }
	int &getAdj( int i ) { return gr[i].getAdj(); }
	int &getRad( int i ) { return gr[i].getRad(); }
	void setRad( int i, int r ) { gr[i].setRad(r); }
	char *get( int i, int &r, int &d ) { r = getRad(i); d = getAdj(i);
					     return gr[i].get(); }
	int getMode() { return mode; }
	short *getArray() { return array; }
	void setArray(short *a) { array = a; }
	void setMode( int m ) { mode = m; }
	void doAdjs(int ofs);
	int doGrf( short *ar, int mo, int points, int force );
	void doOffset();
    void setOffset(int o) { house_offset = o; }
	int find(int d, int r, int w, int h, int &ps, int &min );
	};

class HouseGrfa : public PlanGrfa {
public:
      HouseGrfa() { count = 12; }
      ~HouseGrfa() {}
      int houseMidpoint( int h1, int h2 );
      int &getMhp( int i ) { return gr[i].getRad(); }
      void getMhps();
      int doGrf( short *ar, int mo, int force );
      int getHouse(int d, int &s);
      };


class GraphicDataGroup {
HouseGrfa hs;
PlanGrfa pl;
int asp_cnt;
GR_ASPT *pAspect;
int offset;
int inited;
int asc_min;
int amin;
public:
      GraphicDataGroup() { inited = 0; amin = -1; pAspect = 0; asp_cnt = 0; offset = 0; asc_min = 0; }
      HouseGrfa *getHouses() {return &hs;}
      PlanGrfa *getPlanets() {return &pl;}
      ~GraphicDataGroup() {inited = 0; if (pAspect) delete pAspect; }
      void doGrfs( short *pl, int pt, short *hs, int mode, int am );
      void adjAsc( int &adj, int a );
      int getAsc() { return( asc_min ); }
      void increaseHouses() { offset += 60; }
      void decreaseHouses() { offset -= 60; }
      void resetHouses()    { offset = 0;  }
      void doAspects( GR_ASPT *as, int n );
      GR_ASPT *getAspects(short &n) {n=asp_cnt; return( pAspect ); }
      int getOffset() { return offset; }
      int getHouse(int d, int &s) { return hs.getHouse(d, s); }
      };

extern int adj_degrees( int d, int asc_min);

#endif /* _DATAGRFA_HPP_ */

