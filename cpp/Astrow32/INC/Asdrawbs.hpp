#ifndef _ASDRAWBS_HPP_
#define _ASDRAWBS_HPP_

#define BR 8
#define RISE 6
#define PLAN 7
#define SIGN 2
#define HOUS 4
#define CIRC 8
#define ASPECTBR  16
#define SIGNCRBR  17

#define P_THIN   1
#define P_THICK  -1
#define P_DEF    0
#define P_APLIN  2


#define _TYPE_WIN   0
#define _TYPE_PRINT 1
#define _TYPE_WMF   2
#define _TYPE_BMPC  3
#define _TYPE_BMPM  4
#define _TYPE_DIB   5
#define _TYPE_BMPJ  6


extern int styles[16];	 
extern COLORREF colors[18];   


class AstDrawBase {
protected:
CDC *zd;
int _tech;
int _type;
int _prtype;
int nColors;
int pixels;
int res;
CPalette pal;
		
        void makeColor();
		void makeBrColor();
		void makePrnColor();
		void makeBW();
		void makePalette();
public:
      AstDrawBase(CDC *z, int tp = 0);
      ~AstDrawBase() {}
      void doInit();
      void newDisplay(CDC *z, int tp = 0);
      COLORREF &getColor(int i);
      CPen *getPen(int i, int th=P_DEF);
      CBrush *getBrush(int i);
      int getRes() { return res; }
      CDC *disp() { return zd; }
      void deInit();
      int getColorCount() { return nColors; }
      int getPixels() { return pixels; }
      int type() { return _type; }
      int tech() { return _tech; }
      CPalette &getPalette() { return pal; }
      void RevPrnColors();
};
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#endif /* _ASDRAWBS_HPP_ */
