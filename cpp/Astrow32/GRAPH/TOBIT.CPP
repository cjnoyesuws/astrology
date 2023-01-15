#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "dib.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "grappane.hpp"
#include "errors.fns"
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include "grafilop.hpp"
#include "grconv.hpp"

extern void setMono(int i);
extern void swapMonoClr(int i);

extern int fixupMetafile( char *temp, char *name );

int AstGraphicsPane::toWMF(char *name, int place, int color, int rev)
{
 char buf[75];
 int ft;
 int left = cxLeftOffset, top = cyTopOffset;
 zMetafileDisplay *meta;

 if ( !color )
    setMono(1);
 if ( rev )
    swapMonoClr(1);
 if ( place ) {
    GetTempFileName( 0, "ASTW", 0, buf );
    meta = new zMetafileDisplay(canvas(), buf);
    }
 else
    meta = new zMetafileDisplay(canvas(), name);
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 pushDisplay(meta);
 draw(0);
 popDisplay();
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 delete meta;
 if ( !color )
    setMono(0);
 if ( rev )
    swapMonoClr(0);
 if ( place )
    fixupMetafile( buf, name );
 return( 1 );
}
/*
int AstGraphicsPane::toBitmap( zBitmap *bm )
{
 int ft;
 int left = cxLeftOffset, top = cyTopOffset;

 zBitmapDisplay *bit = new zBitmapDisplay(canvas(), bm );
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 pushDisplay(bit);
 draw(0);
 popDisplay();
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 bit->setBitmap(0);
 delete bit;
 return( 1 );
}

int AstGraphicsPane::toDib( zDib *db, int color, int rev )
{
 extern zColor colors[];
 zColor bwclr[2];
 int ft;
 int left = cxLeftOffset, top = cyTopOffset;

 if ( rev && !color ) {
    bwclr[1] = zColor();
    bwclr[0] = zColor(0xff,0xff,0xff);
    }
 else {
    bwclr[0] = zColor();
    bwclr[1] = zColor(0xff,0xff,0xff);
    }
 zDibDisplay *dib = new zDibDisplay( db );
 if ( rev )
    swapMonoClr(1);
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 pushDisplay(dib);
 draw(0);
 if ( color )
    db->setColors( colors, 16 );
 else
    db->setColors( bwclr, 2 );
 popDisplay();
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 delete dib;
 if ( rev )
    swapMonoClr(0);
 return( 1 );
}


int AstGraphicsPane::export()
{
 GraphicFileConverter *gfc;

 gfc = new GraphicFileConverter(this);
 if ( !gfc->getSetup() ) {
    delete gfc;
    return( 0 );
    }
 if ( !gfc->getFile()  ) {
    delete gfc;
    return( 0 );
    }
 gfc->setPane(this);
 if ( !gfc->doConvert() ) {
    delete gfc;
    return( 0 );
    }
 delete gfc;
 return( 1 );
}


*/