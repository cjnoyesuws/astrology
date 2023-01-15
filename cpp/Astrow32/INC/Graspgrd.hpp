#ifndef _GRASPGRD_HPP_
#define _GRASPGRD_HPP_

class AspectGrid : public AstDrawBase {
private:
  CDC *d;
  int cellw, cellh;
  int hfcell, thcell;
  CPoint at;
  GR_ASPT *data;
  int count, planets;
public:
  AspectGrid(CDC *z, CPoint p, CSize c, GR_ASPT *pt, int cnt, int pl );
  ~AspectGrid() {}
  int draw();
  int drawGrid();
  int drawGridKey();
  int drawOne(GR_ASPT *p);
  CPoint loc(int x, int y, int key=1);
  char *text(int i);
  };


#endif /* _GRASPGRD_HPP_ */
