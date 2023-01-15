#ifndef _PLOTHOUS_HPP_
#define _PLOTHOUS_HPP_

class HousePlotter : AstDrawBase {
int house_out, asc;
CFont *pFnt, *pNumFnt;
HouseGrfa *hs;
PlotAroundCircle *cNum, *cDeg;
PolarCoord inside, outside, middle, midpoint;
public:
      HousePlotter(CDC *d,HouseGrfa *h,int ho,int a);
      ~HousePlotter() { delete cNum; delete cDeg;}
      void setCirc(int ir, int or, int mid, int inc );
      void setFont( CFont *fnt ) {pFnt = fnt; pNumFnt = fnt;}
      void setNumFont( CFont *fnt ) {pNumFnt = fnt;}
      void plotHouseLines();
      void plotHouseDegrees();
      void plotHouseNumbers();
      void plot(int mode);
      };

#endif /* _PLOTHOUS_HPP_ */

