#ifndef _PLOTPLAN_HPP_
#define _PLOTPLAN_HPP_

#define WH_OUTER 0
#define WH_INNER 1

class PlanetPlotter : public AstDrawBase {
protected:
int createFont, theWidth, theHeight;
int showDegs;
PlanGrfa *pgp;
PlanetList *pList;
LOGFONT *pFontg, *pFontd;	
CFont *glyph, *deg;
public:
      PlanetPlotter(CDC *c, PlanGrfa *p, int init, int failolp, int min, int wheel=WH_OUTER );
      ~PlanetPlotter();
      virtual void doPlot();
      void plotGlyphs();
      void plotDegs();
      void setFonts(LOGFONT *pFg, LOGFONT *pFd);
      void setRads();
#ifdef NEW
      int find(int d, int r, int &psign, int &min ) { return pgp->find(d,r,theWidth,theHeight, psign, min); }
#endif

      };

class PlanetPlotterClassical : public PlanetPlotter {
int shift;
public:
      PlanetPlotterClassical(CDC *z, PlanGrfa *p, int init, int wh = WH_OUTER) :
		  PlanetPlotter(z, p, init, 0, 0 )   { theWidth=init;
	 if (wh == WH_OUTER) shift = 5; else shift = 8;
         delete pList;
	 pList = (PlanetList *) new PlanetListClassical(init, shift); createFont=0; }
      ~PlanetPlotterClassical() {}
      virtual void doPlot();
      void plotOne(int i);
      void setFonts(LOGFONT *pFg );
      void setRads();
      };

#endif /* _PLOTPLAN_HPP_ */




