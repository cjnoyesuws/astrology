#ifndef _DIB_______HPP_
#define _DIB_______HPP_

class CDib {
	BITMAPINFOHEADER head;
	COLORREF colors[16];
	BITMAPINFOHEADER dibptr;
	friend class CDibDC;
public:
	CDib();
	CDib( BITMAPINFOHEADER huge *d ); // Full Specification.
	void setColors( COLORREF *clr, int cnt );
	COLORREF *getColors();
	BITMAPINFOHEADER *getData() { return dibptr; }
	CSize size();
	~CDib() {}
};


class CDibDC : public CDC {
	CDib* curDib;
public:
	CDibDisplay(CDib *);
	virtual ~CDibDisplay();

	CDib *getDib() { return curDib; }
	CDib *setDib(CDib *);
	virtual void getVisible(CRect & r);
	virtual void getDirty(CRect& r);

};

#endif /* _DIB_______HPP_  */


