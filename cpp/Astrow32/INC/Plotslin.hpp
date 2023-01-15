#ifndef _PLOTSLIN_HPP_
#define _PLOTSLIN_HPP_

class SignLinePlotter : AstDrawBase {
int asc;
PolarCoord inside, outside;
public:
      SignLinePlotter(CDC *d, int a) :
                AstDrawBase(d) { asc = a; }
      ~SignLinePlotter() {}
      void setCirc(int ir, int or);
      void plot();
      };

#endif /* _PLOTSLIN_HPP_ */

