#include "stdafx.h"
#include "astrow.h"
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "errors.fns"
#include "acombbox.hpp"
#include "grafilop.hpp"
#include "graphfileopts.h"
#include "vicdefs.h"
#include "charcons.h"
#include "radius.h"
#include "AstrographDoc.h"
#include "AstrographView.h"
#include "grconv.hpp"

GraphicFileConverter::getFile()
{
 char outfile[300];
 int ret;
 //static char *types[] = { 0, 0, 0, 0 };

 strcpy( outfile, "GRAPH" );
 strcat( outfile, ext );
 CFileDialog cfd( FALSE, ext, outfile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, types, pPar );
 cfd.m_ofn.lpstrTitle ="Graphic File Name To Export To...";
 ret = cfd.DoModal();
 if ( ret != IDOK && ret != IDYES ) {
    return( 0 );
    }
 strcpy( outfile, cfd.GetPathName() );
 file = outfile;
 return( 1 );
}

int GraphicFileConverter::getSetup()
{
 data.getFromIni();

 CGraphFileOpts gfdd;
 gfdd.SetData( data ); 
 if ( gfdd.DoModal() == IDOK ) {
    gfdd.GetData( data );
    data.saveToIni(); 
    switch( data.getFormat() ) {
       case GF_MPWMF  :
       case GF_MXWMF  :
	    types = "Mono Windows MetaFiles (*.WMF)|*.WMF|All Files (*.*)|*.*||";
	    ext = ".WMF";
	    break;
       case GF_CPWMF  :
       case GF_CXWMF  :
	    types = "Color Windows MetaFiles (*.WMF)|*.WMF|All Files (*.*)|*.*||";
	    ext = ".WMF";
	    break;
       case GF_MBMP :
	    types = "Monochrome Bitmap Files (*.BMP)|*.BMP|All Files (*.*)|*.*||";
	    ext = ".BMP";
	    break;
       case GF_CBMP :
	    types = "Color Bitmap Files (*.BMP)|*.BMP|All Files (*.*)|*.*||";
	    ext = ".BMP";
	    break;
       case GF_CEPS :
	    types = "Color Encapsulated Postcript Files (*.EPS)|*.EPS|All Files (*.*)|*.*||";
	    ext = ".EPS";
	    break;
       case GF_CGIF :
	    types = "Color Graphics Interchange Files (*.GIF)|*.GIF|All Files (*.*)|*.*||";
	    ext = ".GIF";
	    break;
       case GF_MPCX :
	    types = "Monochrome PCX Files (*.PCX)|*.PCX|All Files (*.*)|*.*||";
	    ext = ".PCX";
	    break;
       case GF_CPCX :
	    types = "Color PCX Files (*.PCX)|*.PCX|All Files (*.*)|*.*||";
	    ext = ".PCX";
	    break;
       case GF_MCTIF :
	    types = "Monochrome TIFF Files (*.TIF)|*.TIF|All Files (*.*)|*.*||";
	    ext = ".TIF";
	    break;
       case GF_CCTIF :
	    types = "Color Compressed TIFF Files (*.TIF)|*.TIF|All Files (*.*)|*.*||";
	    ext = ".TIF";
	    break;
       case GF_CUTIF :
	    types = "Color Uncompressed Files (*.TIF)|*.TIF|All Files (*.*)|*.*||";
	    ext = ".TIF";
	    break;
       case GF_PNG :
	    types = "Color Portable Network Graphic File (*.PNG)|*.PNG|All Files (*.*)|*.*||";
	    ext = ".PNG";
	    break;
       case GF_JPG :
	    types = "Color JPEG Files (*.JPG)|*.JPG|All Files (*.*)|*.*||";
	    ext = ".JPG";
	    break;
	   default :
	   break;
       }
    return( 1 );
    }
 else {
    delete gfdd;
    return( 0 );
    }
}


void revMono( unsigned int huge *buf, int bw, int rows )
{
 int l, i;
 unsigned int huge *b = buf, huge *bp;

 bw /= 4;
 for ( i = 0; i < rows; i++, b += bw ) {
     for ( l = 0, bp = b; l < bw; l++, bp++ )
	 *bp = *bp ^ 0xffffffff;
     }
}


int GraphicFileConverter::doConvert()
{
 imgdes image;
 //zBitmap *bmp = 0;
// HPALETTE hPal, hPalOld = 0;
// LOGPALETTE *pallete;
 unsigned char huge *dbadr;
 int bppixel, rcode;

 if ( data.getFormat() <= GF_CXWMF ) {
    switch( data.getFormat() ) {
	  case GF_MPWMF :
	      view->toWMF( (char *)(LPCTSTR)file, 1, 0, data.getReverse() );
	      break;
	  case GF_CPWMF :
	      view->toWMF( (char *)(LPCTSTR)file, 1, 1, data.getReverse() );
	      break;
	  case GF_MXWMF :
	      view->toWMF( (char *)(LPCTSTR)file, 0, 0, data.getReverse() );
	      break;
	  case GF_CXWMF :
	      view->toWMF( (char *)(LPCTSTR)file, 0, 1, data.getReverse() );
	      break;
	  default :
	      break;
	  }
    return( 1 );
    }
 bppixel = data.isFormatColor()?8:1;
 if ( !data.isFormatColor() ) {
    rcode = allocimage( &image, data.getDotWidth(), data.getDotHeight(), 1 );
    if ( rcode == NO_ERROR ) {
       view->toDib( &image, data.isFormatColor(), data.getReverse(), 1 );
       //if ( data.getReverse() )
	   //revMono( (unsigned huge *)image.ibuff, image.buffwidth, data.getDotHeight() );
       }
    }
 else {
    rcode = allocimage( &image, data.getDotWidth(), data.getDotHeight(), data.getFormatBits() );
    if ( rcode == NO_ERROR ) {
       image.bmh->biClrImportant=0;
       int dib;
       if ( data.getFormat()==GF_PNG)
   		  dib = 0;
	   else if ( data.getFormat() == GF_JPG)
	      dib=-1;
	   else  dib = 1;  
   	   view->toDib( &image, 1, data.getReverse(), dib );
       }
    }
 if ( rcode != NO_ERROR ) {
	 alert_box( ERROR1, "Not Enough Memory To Convert File %s", (char *)(LPCTSTR)file  );
    return( 0 );
    }
 switch(data.getFormat()) {
       case GF_MBMP :
       case GF_CBMP :
	   rcode = savebmp((char *)(LPCTSTR)file, &image, 0 );
	   break;
       case GF_CEPS :
	   rcode = saveeps((char *)(LPCTSTR)file, &image );
	   break;
       case GF_CGIF :
	   rcode = savegif((char *)(LPCTSTR)file, &image );
	   break;
       case GF_MPCX :
       case GF_CPCX :
	   rcode = savepcx((char *)(LPCTSTR)file, &image );
	   break;
       case GF_MCTIF :
       case GF_CCTIF :
	   if ( data.getFormat()== GF_CCTIF )
	      image.imgtype=0;
	   rcode = savetif((char *)(LPCTSTR)file, &image, 2 );
	   break;
       case GF_CUTIF :
	   image.imgtype=0;
	   rcode = savetif((char *)(LPCTSTR)file, &image, 0 );
	   break;
       case GF_PNG :
	   rcode = savepng((char *)(LPCTSTR)file, &image, PNGALLFILTERS|PNGINTERLACE );
	   break;
       case GF_JPG :
	   rcode = savejpg((char *)(LPCTSTR)file, &image, 100);
	   break;
       default :
	   break;
       }
 freeimage(&image);
 if ( rcode == NO_ERROR )
    return( 1 );
 else {
    alert_box( ERROR1, "Can't Convert File %s", (char *)(LPCTSTR)file );
    return( 0 );
    }
}




