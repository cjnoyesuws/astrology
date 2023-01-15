#include "stdafx.h"
#include "asdrawbs.hpp"
#include "gracolor.hpp"
#include "inifile.hpp"

int styles[16];

COLORREF colors[18];
static int init;
int icolors, ires;
int nPixels;
COLORREF blk, wht;
int isMono;
int monoSwap;

void setMono( int m )
{
 isMono = m;
}

void swapMonoClr(int i)
{
 monoSwap = i;
}

AstDrawBase::AstDrawBase(CDC* z, int tp)
{
 zd = z;
 _type = tp;
 _prtype = 0;
 _tech = zd->GetDeviceCaps(TECHNOLOGY); 
 monoSwap = 0;
 isMono = 0;
 zd = z;
 if ( !init )
    doInit();
 else {
    nColors = icolors;
    res = ires;
    nPixels = res/50;
    pixels = nPixels;
    }
}

COLORREF &AstDrawBase::getColor(int i)
{
 static COLORREF cr;

 if ( nColors > 2 )
    return colors[i];
 else if ( nColors == 2 ) {
    if ( i )
       return( wht );
    else
       return( blk );
    }
 else {
    cr = RGB(i,i,i);
    return( cr );
    }
}


void AstDrawBase::doInit()
{						
 						 
 nColors = zd->GetDeviceCaps(NUMCOLORS);
 if ( _type == _TYPE_WIN && nColors == -1)
	nColors = 16;
 _tech = zd->GetDeviceCaps(TECHNOLOGY);
 if (zd->IsPrinting())
	_type = _TYPE_PRINT;
 else if ( _tech == DT_METAFILE )
	_type = _TYPE_WMF;
 if ( _type == _TYPE_BMPM )
    nColors = 2;
 else if ( _type == _TYPE_BMPC || _type == _TYPE_BMPJ )
    nColors = 16;
 else if ( _type == _TYPE_WMF && !isMono )
    nColors = 16;
 else if ( _type == _TYPE_WMF && isMono )
    nColors = 2;
 else if ( _type == _TYPE_DIB )
	nColors = -1;
 if ( nColors == 2 && _type == _TYPE_PRINT )
    monoSwap = 1;
 res = zd->GetDeviceCaps(LOGPIXELSX);
 nPixels = res/60;
 pixels = nPixels;
  if (!init || (res != ires) || (icolors != nColors) || _type != _prtype ) {
    if ( nColors == 2 )
       makeBW();
    else if (_type == _TYPE_PRINT || (_type != _TYPE_WIN && monoSwap) ) {
       makePrnColor();
       }
	else if (_type == _TYPE_BMPJ )
	   makeBrColor();
    else {
       makeColor();
       }
    init = 1;
    ires = res;
    icolors = nColors;
    if (_type == _TYPE_PRINT && nColors > 2  ) {
       GraphicColors gcp(this);
       gcp.getFromIni(GraphPrintOpt_SEC);
       if ( gcp.getRevBack() == TRUE )
	      RevPrnColors();
	   }
    else if (_type != _TYPE_PRINT && nColors > 2 && _type != _TYPE_BMPJ ) {
       GraphicColors gc(this);
       gc.getFromIni(GraphicsOptions_SEC);
       }
    }
}

void AstDrawBase::newDisplay(CDC *z, int tp)
{
 _prtype = _type;
 _type = tp;  
 zd = z;
 _tech = zd->GetDeviceCaps(TECHNOLOGY); 
 doInit();
 nColors = icolors;
 res = ires;
 nPixels = res/60;
 pixels = nPixels;
}


void AstDrawBase::deInit()
{
 init = 0;
 icolors = 0;
 ires = 0;
}

void AstDrawBase::makeBW()
{
 static int done = 0;
 int i;

 nPixels = 1;
 pixels = 1;
 if (monoSwap) {
    wht = RGB(0,0,0);	
    blk = RGB(0xff,0xff,0xff);
    }
 else {
    wht = RGB(0xff,0xff,0xff);
    blk = RGB(0,0,0);
    }
 if ( done )
    return;
 for ( i = 0; i < 16; i++ )
     styles[i] =	PS_SOLID;
 styles[HOUS] =		PS_DOT;
 styles[BR+HOUS] =	PS_DOT;
 styles[SIGN] =		PS_DASH;
 styles[BR+SIGN] =	PS_DASH;
 styles[RISE] =		PS_DASHDOT;
 styles[BR+RISE] =	PS_DASHDOT;
 done = 1;
}
#pragma pack(8)
typedef struct tagMYLOGPALETTE { // lgpl 
    WORD         palVersion; 
    WORD         palNumEntries; 
    PALETTEENTRY palPalEntry[16]; 
} MYLOGPALETTE; 
#pragma pack()
 
#define setupPalEntry(n) lp.palPalEntry[n].peGreen=GetGValue(colors[n]);\
						   lp.palPalEntry[n].peBlue=GetBValue(colors[n]);\
						   lp.palPalEntry[n].peRed=GetRValue(colors[n]);\
						   lp.palPalEntry[n].peFlags=PC_EXPLICIT

void AstDrawBase::makePalette()
{
 int i;
 MYLOGPALETTE lp;
 lp.palVersion = 0x300;
 lp.palNumEntries = 16;
 for ( i = 0; i < 16; i ++ ) {
	 setupPalEntry(i);
     }
 pal.CreatePalette((LOGPALETTE *)&lp);
}


void AstDrawBase::makeColor()
{
 COLORREF c;
 int i;

 c = RGB(0,0,0);
 for ( i = 0; i < 16; i++ )
     colors[i] = c;
 colors[CIRC] =		RGB(0x80, 0x80, 0x80);
 colors[BR+PLAN] =	RGB(0xff, 0xff, 0xff);
 colors[PLAN] =		RGB(0xa0, 0xa0, 0xa0);
 colors[SIGN] =		RGB(0, 0x80, 0);
 colors[BR+SIGN] =	RGB(0, 0xff, 0);
 colors[HOUS] =		RGB(0x80, 0, 0);
 colors[BR+HOUS] =	RGB(0xff, 0, 0);
 colors[RISE] =		RGB(0x80, 0x80, 0);
 colors[BR+RISE] =	RGB(0xff, 0xff, 0 );
 for ( i = 0; i < 16; i++ )
     styles[i] = PS_SOLID;
 colors[ASPECTBR] = RGB(0x0, 0x10, 0x10);
// makePalette();
}

void AstDrawBase::makeBrColor()
{
 COLORREF c;
 int i;

 c = RGB(0,0,0);
 for ( i = 0; i < 16; i++ )
     colors[i] = c;
 colors[CIRC] =		RGB(0xb0, 0xb0, 0xb0);
 colors[BR+PLAN] =	RGB(0xff, 0xff, 0xff);
 colors[PLAN] =		RGB(0xb0, 0xb0, 0xb0);
 colors[SIGN] =		RGB(0, 0xff, 0);
 colors[BR+SIGN] =	RGB(0, 0xff, 0);
 colors[HOUS] =		RGB(0xff, 0, 0);
 colors[BR+HOUS] =	RGB(0xff, 0, 0);
 colors[RISE] =		RGB(0xff, 0xff, 0);
 colors[BR+RISE] =	RGB(0xff, 0xff, 0 );
 for ( i = 0; i < 16; i++ )
     styles[i] = PS_SOLID;
 colors[ASPECTBR] = RGB(0x0, 0x10, 0x10);
// makePalette();
}

CPen *AstDrawBase::getPen(int i, int th)
{
 CPen *pn;
						   
 if ( nColors > 2 ) {
    if ( th == P_APLIN ) 
       pn = new CPen(PS_SOLID, 1, colors[i]);
    else
       pn = new CPen(PS_SOLID, pixels, colors[i]);
    /*
    if ( th == P_DEF )
       pn = new CPen(colors[i],Solid, pixels);
    else if ( th == P_THIN )
       pn = new CPen(colors[i],Solid, 1);
    else
       pn = new CPen(colors[i],Solid, 2 );
    */
    }
 else if ( nColors == 2 ) {
    if ( th == P_DEF )
       pn = new CPen(styles[i], pixels,(i?wht:blk));
    else if ( th == P_THIN || th == P_APLIN )
       pn = new CPen(styles[i], 1, (i?wht:blk));
    else
       pn = new CPen(PS_SOLID, 2, (i?wht:blk));
    }
 else {
    if ( th == P_APLIN )
       pn = new CPen(PS_SOLID, 1, RGB(i,i,i) );
    else
       pn = new CPen(PS_SOLID, pixels, RGB(i,i,i));
    /*
    if ( th == P_DEF )
       pn = new CPen(RGB(i,i,i),Solid, pixels);
    else if ( th == P_THIN )
       pn = new CPen(RGB(i,i,i),Solid, 1);
    else
       pn = new CPen(RGB(i,i,i),Solid, 2);
    */
    }
 return( pn );
}

CBrush *AstDrawBase::getBrush(int i)
{
 CBrush *pn;	   

 if ( i >= 16 && nColors != 2 )
    pn = new CBrush(colors[i]);
 else if ( nColors == 2 )			 
    pn = new CBrush((i?wht:blk));
 else if ( nColors == -1  )
    pn = new CBrush(RGB(i,i,i));
 else
    pn = new CBrush(colors[i]);
 return( pn );
}

void AstDrawBase::makePrnColor()
{
 COLORREF c;
 int i;
 c = RGB(0,0,0);
 for ( i = 1; i < 16; i++ )
     colors[i] = c;
 colors[0] =		RGB(0xff,0xff,0xff);
 colors[CIRC] =		RGB(0,0,0);
 colors[BR+PLAN] =	RGB(0,0,0);
 colors[PLAN] =		RGB(0,0,0);
 colors[SIGN] =		RGB(0,0xff,0);
 colors[BR+SIGN] =	RGB(0x0,0xff,0x0);
 colors[HOUS] =		RGB(0xff,0,0);
 colors[BR+HOUS] =	RGB(0xff,0,0);
 colors[RISE] =		RGB(0,0xff,0xff);
 colors[BR+RISE] =	RGB(0,0xff,0xff);
 for ( i = 0; i < 16; i++ )
     styles[i] = PS_SOLID;
 colors[ASPECTBR] = RGB(0, 0x10, 0x10);
}



void AstDrawBase::RevPrnColors()
{
 colors[0] ^= 0x00ffffff;
 colors[CIRC] ^= 0x00ffffff;		
 colors[BR+PLAN] ^= 0x00ffffff;	
 colors[PLAN] ^= 0x00ffffff;		
 colors[SIGN] ^= 0x00ffffff;		
 colors[BR+SIGN] ^= 0x00ffffff;	
 colors[HOUS] ^= 0x00ffffff;		
 colors[BR+HOUS] ^= 0x00ffffff;	
 colors[RISE] ^= 0x00ffffff;		
 colors[BR+RISE] ^= 0x00ffffff;	
}
