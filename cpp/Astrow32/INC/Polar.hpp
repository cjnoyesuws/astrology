#ifndef _POLAR____HPP_
#define _POLAR____HPP_

extern short isin( short degs, short max, short sc = 1 );
extern short icos( short degs, short max, short sc = 1 );

extern int enblScPol;

class PolarScaler {
public:
      PolarScaler() { enblScPol = 0; }
      ~PolarScaler() {}
      void enable(int e);
      int isEnabled() { return enblScPol; }
      void setScale(int xm, int ym, int xd, int yd );
      int scaleX( int x );
      int scaleY( int y );
      int invScaleX( int x );
      int invScaleY( int y );
      void setupResolutions( int x, int y );
      };

extern PolarScaler thePolarScaler;


class PolarCoord {
int radius;
CPoint pt;				 
public:
      PolarCoord() { radius = 0; }
      PolarCoord(int r) {radius = r;}
      ~PolarCoord() {}
      void setRad( int r) { radius = r; }
      int operator++() { radius++; return radius; }
      int operator--() { radius--; return radius; }
      int x(int deg) { return(icos(deg,radius)); }
      int y(int deg) { return(-isin(deg,radius)); }
      CPoint &asPoint() { pt.x = thePolarScaler.scaleX(radius);
	   pt.y = thePolarScaler.scaleY(radius); return pt; }
      CPoint &xy(int deg) { pt.x = icos(deg,radius);
	    pt.y = -isin(deg,radius);
	    return pt; }
      CPoint &xy(int deg, int rad) {
            radius = rad;
	    pt.x = icos(deg,radius);
	    pt.y = -isin(deg,radius);
	    return pt; }    
      };



#endif /* _POLAR____HPP_  */
