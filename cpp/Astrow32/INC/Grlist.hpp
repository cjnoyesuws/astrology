#ifndef _GRLIST___HPP_
#define _GRLIST___HPP_

class PlanetListElement {
int degs;
int radius;
public:
   PlanetListElement()  { degs = 0; radius = 0; }
   ~PlanetListElement() {}
   void setDegs( int d ) { degs = d; }
   void setRad( int r ) { radius = r; }
   int getRad() { return radius; }
   int compare(int degs, int var, int var2);
   };

class PlanetList {
int min;
short *var;
int failOverlap;
public:
      PlanetList(int i, int m, short *v, int fo ) { count = 0;
	 init = i; min =m; var = v; failOverlap = fo; }
      ~PlanetList() { count = 0; }
      virtual int checknAdd(int &degs);
      void setMin(int m) { min = m; }
      void setWidth(int w, int h) { width = w; height = h; }
protected:
      PlanetListElement array[30];
      int count;
      int width, height;
      int init;
      int getVar( int degs, int &v2 );
      int check(int degs, int var, int var2, int &rads);
      int add(int degs, int rads );
      int compWidth(int d);
      int checkDeg(int deg ) { if ( deg <= 0 )
				     return 360 + deg;
			       else if ( deg > 360 )
				     return deg - 360;
				  else
				     return( deg ); }
      };

class PlanetListClassical : public PlanetList {
int shift;
public:
      PlanetListClassical(int i, int sh) : PlanetList(i,0,0,0) {shift = sh;}
      ~PlanetListClassical() {}
      virtual int checknAdd(int &degs);
      };


inline int PlanetListElement::compare(int dg, int var, int var2)
{
 dg = abs(dg - degs);

 if ( dg < var || dg > var2 )
    return( 1 );
 else
    return( 0 );
}


#endif /* _GRLIST___HPP_ */
