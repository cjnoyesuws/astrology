#ifndef _KEY______HPP_
#define _KEY______HPP_

class WheelKey : public AstDrawBase {
int type, yStart, xWidth, yDeep;
CFont *fnt, *bfnt;
int label;
public:
      WheelKey( CDC *z, CFont *f, CFont *fb, int yst, int xw, int yd );
      ~WheelKey() {}
      void title();
      void drawAKey(LPCTSTR text,int color, int key );
      int lineKey(int color, int y);
      int colorKey(int color, int y);
      void drawKeys();
      };

class StatusKey : public AstDrawBase {
int x, y, color, align;
CFont *fnt;
public :
      StatusKey(CDC *z, int color, int x, int y, int align, CFont *fnt);
      ~StatusKey()  {}
      void draw(char *txt);
      };

#endif /* _KEY______HPP_ */
