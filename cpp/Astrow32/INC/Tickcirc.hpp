#ifndef _TICKCIRC_HPP_
#define _TICKCIRC_HPP_

class SignTickCircle : public AstDrawBase {
protected:
      PolarCoord out, in;
	  int inradius;
      int thick, asc_min;
public:
      SignTickCircle( CDC *zd, int inrad, int outrad, int asc);
      ~SignTickCircle() {}
      void draw();
      void drawCirc();
      };


class DecanTickCircle : public SignTickCircle {
public:
      DecanTickCircle( CDC *zd,int inrad, int outrad, int asc)
			  : SignTickCircle(zd, inrad,outrad, asc) {}
      ~DecanTickCircle() {}
      void draw();
      };


class DegreeTickCircle : public SignTickCircle {
int incrmnt;
public:
      DegreeTickCircle( CDC *zd,int inrad, int outrad, int asc );
      ~DegreeTickCircle() {}
      void draw();
      };

class PlainCircle : public SignTickCircle {
public:
      PlainCircle( CDC *zd, int rad)
		   : SignTickCircle(zd, 0, rad, 0) {}
      ~PlainCircle() {}
      void draw() { drawCirc(); }
      };

class DecanDegreeTickCircle : public SignTickCircle {
CFont *pFont;
CBrush *pBrush;
public:
      DecanDegreeTickCircle( CDC *zd,int inrad, int outrad, int asc, CFont *pFnt, CBrush *pBrs)
			  : SignTickCircle(zd, inrad,outrad, asc) { pFont = pFnt; pBrush = pBrs;}
      ~DecanDegreeTickCircle() {}
      void draw();
      };
#endif /* _TICKCIRC_HPP_  */
