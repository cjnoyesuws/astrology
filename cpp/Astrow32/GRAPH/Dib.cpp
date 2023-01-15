#include "stdafx.h"
#include "dib.hpp"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

CDib::CDib() {
	}

CDib::CDib(BITMAPINFOHEADER *data ) {
	//f Creates a {\c zDib} of the specified width and height.
	//p     int width - the {\c zDib}'s width in pixels.
	//p     int height - the {\c zDib}'s height in pixels.
	//p	int depth - the number of color bits per pixel.
	//p int planes - the number of color planes in the {\c zDib}.
	//n This constructor creates an "empty" bitmap, though
	//      the memory comprising the {\c zDib} is uninitialized.
	//  (In other words, the picture is not blank as in white.)
	//w	CreateBitmap
	memcpy( &head, data, sizeof(BITMAPINFOHEADER) );
	dibptr = data;
}


CSize zDib::size() {
//f This member function returns a {\c zDimension}, specifying
//  the x and y size of the bitmap.
//r CSize - width and height of bitmap in pixels.
	CSize x;
	x.cx = head.biWidth;
	x.cy = head.biHeight;
	return( x );
}

CDibDC::CDibDC(CDib *bp) {
	hDC = CreateDC("DIB", 0, 0, bp->getData());
	curDib = bp;
}

CDibDC::~CDibDC() {
	//f Destroys and frees the resources used by the 
	//	{\c zBitmapDisplay}, including the currently selected {\c zBitmap}.
    //n If the currently selected {\c zBitmap} should not be freed,
	//	the following code may be used:
	///		zBitmapDisplay *bd;
	///			.
	///			.
	///             bd->setDib(0);
	///		delete bd;
	DeleteDC(hDC);
}


void zDibDisplay::getVisible(CRect &r) {
	if (curDib) {
		CSize d = curDib->size();
		r=CRect(0,0,d.cx,d.cy);
	} else
		r=CRect(0,0,0,0);
}

void zDibDisplay::getDirty(zRect &r) {
	if (curDib) {
		zDimension d(curDib->size());
		r=zRect(0,0,d.width(),d.height());
	} else
		r=zRect(0,0,0,0);
}

void zDib::setColors( COLORREF clr, int cnt )
{
 int i;
 COLORREF *c;
 BYTE b;

 memcpy( colors, clr, cnt * 4 );
 memcpy( ((char *)dibptr)+sizeof(BITMAPINFOHEADER), clr, cnt * 4 );
 for ( i = 0, c = (COLORREF *)(((char *)dibptr)+sizeof(BITMAPINFOHEADER)); i < cnt; i++, c++ ) {
     b = GetRValue(*c);
     GetRValue(*c) = GetBValue(*c);
     GetBalue(*c) = b;
     }
}

COLORREF *CDib::getColors()
{
 return( colors );
}


