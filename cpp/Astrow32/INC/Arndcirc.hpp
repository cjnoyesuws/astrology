#ifndef _ARNDCIRC_HPP_
#define _ARNDCIRC_HPP_

class PlotAroundCircle : public AstDrawBase {
protected:
int asc_min;
PolarCoord circ;
public:
      PlotAroundCircle(CDC *z) : AstDrawBase(z) {}
      PlotAroundCircle(CDC *z, int r) : AstDrawBase(z)
					   { circ.setRad(r); }
      ~PlotAroundCircle() {}
      int plot(int deg, char *text);
      void setAscMin( int a ) { asc_min = a; }
      void setCirc( int rad) { circ.setRad(rad); }
      };


class PlotSigns : public PlotAroundCircle {
CFont *fnt;
public:
      PlotSigns(CDC *z, int r, CFont *f, int asc)
	: PlotAroundCircle(z, r) { fnt = f; setAscMin(asc);}
      PlotSigns(CDC *z) : PlotAroundCircle(z) {}
      void plot(int mode);
      };

#endif /* _ARNDCIRC_HPP_  */
