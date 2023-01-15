#ifndef _GRASPCIR_HPP_
#define _GRASPCIR_HPP_

class AspectCircle : public AstDrawBase {
private:
	CBrush *pBrFill;
protected:
	int glyph;
	int state;
	int cyChar;
	int draw_circ;
        GR_ASPT *pAspects;
	PolarCoord pc;
	int asp_count;
	int draw_asp(GR_ASPT *p);
	void getPoints(GR_ASPT *p, CPoint &f, CPoint &s );
	void getMid(CPoint &f, CPoint &s, CPoint &m);
public:
	AspectCircle(CDC *z, GR_ASPT *p, int cnt, int rad, int cy, int gl=0, int dc=1);
	~AspectCircle() {}
	void setFillBrush( CBrush *pB=0 ) { pBrFill = pB; }
	void changeCirc( int d ) { pc.setRad(d); }
	void draw();
    };


#endif /* _GRASPCIR_HPP_  */                       