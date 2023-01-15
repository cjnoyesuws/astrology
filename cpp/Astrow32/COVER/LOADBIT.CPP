#include "stdafx.h"
#include "vicdefs.h"
#include "errors.fns"
#include "charcons.h"

#define PCX 0
#define TIF 1
#define BMP 2
#define GIF 3
#define JPG 4
#define PNG 5

#define BADF   1
#define NOMEM  2
#define BADR   3
#define OKF    0

static int fileToType( char *file )
{
 char *p = strrchr( file, '.' );
 if ( p == NULL )
    return( -1 );
 if ( !strcmpi( p, ".TIF" ) )
    return( TIF );
 else if ( !strcmpi( p, ".PCX" ) )
    return( PCX );
 else if ( !strcmpi( p, ".BMP" ) )
    return( BMP );
 else if ( !strcmpi( p, ".GIF" ) )
    return( GIF );
 else if ( !strcmpi( p, ".PNG" ) )
    return( PNG );
 else if ( !strcmpi( p, ".JPG" ) )
    return( JPG );
 else 
	 return( -1 );
}

int loadBmp(char *fname, imgdes *image, int &rcode )
{
   BITMAPINFOHEADER bminfo;
   int bppixel;

   /* Get info on the file we're to load */
   rcode = bmpinfo(fname, &bminfo);
   if(rcode != NO_ERROR) { /* Fill structure */
      return(BADF);
      }
   bppixel = bminfo.biBitCount;
   // If image is 4 bits per pixel, allocate space for 8-bit image
   if(bppixel == 4)
      bppixel = 8;
   /* Allocate space for an image */
   rcode = allocimage(image, (int)bminfo.biWidth,
      (int)bminfo.biHeight, bppixel);
   if(rcode != NO_ERROR) {
     return( NOMEM );
     }   /* Load image */
   rcode = loadbmp(fname, image);
   if(rcode != NO_ERROR) // Free image on error
     return(BADR);
   return( OKF );
}


int loadPcx(char *fname, imgdes *image, int &rcode )
{
   PcxData pdat;

   /* Get info on the file we're to load */
   rcode = pcxinfo(fname, &pdat);
   if(rcode != NO_ERROR) { /* Fill structure */
     return(BADF);
     }
   /* Allocate space for an image */
   rcode = allocimage(image, pdat.width, pdat.length, pdat.vbitcount);
   if(rcode != NO_ERROR) {
     return(NOMEM);
     }
   /* Load image */
   rcode = loadpcx(fname, image);
   if(rcode != NO_ERROR) // Free image on error
     return(BADR);
   return( OKF );
}



int loadGif(char *fname, imgdes *image, int &rcode )
{
   GifData gdat;

   /* Get info on the file we're to load */
   rcode = gifinfo(fname, &gdat);
   if(rcode != NO_ERROR) { /* Fill structure */
     return(BADF);
     }
   /* Allocate space for an image */
   rcode = allocimage(image, gdat.width, gdat.length, gdat.vbitcount);
   if(rcode != NO_ERROR) {
     return(NOMEM);
     }
   /* Load image */
   rcode = loadgif(fname, image);
   if(rcode != NO_ERROR) // Free image on error
     return(BADR);
   return( OKF );
}


int loadJpg(char *fname, imgdes *image, int &rcode )
{
   JpegData pdat;

   /* Get info on the file we're to load */
   rcode = jpeginfo(fname, &pdat);
   if(rcode != NO_ERROR) { /* Fill structure */
     return(BADF);
     }
   /* Allocate space for an image */
   rcode = allocimage(image, pdat.width, pdat.length, pdat.vbitcount);
   if(rcode != NO_ERROR) {
     return(NOMEM);
     }
   /* Load image */
   rcode = loadjpg(fname, image);
   if(rcode != NO_ERROR) // Free image on error
     return(BADR);
   return( OKF );
}


int loadTiff(char *fname, imgdes *image, int &rcode )
{
   TiffData tdat;

   /* Get info on the file we're to load */
   rcode = tiffinfo(fname, &tdat);
   if( rcode != NO_ERROR ) { /* Fill structure */
     return(BADF);
     }
   /* Allocate space for an image */
   rcode = allocimage(image, tdat.width, tdat.length, tdat.vbitcount);
   if( rcode != NO_ERROR ) {
     return(NOMEM);
     }   rcode = loadtif(fname, image);
   if( rcode != NO_ERROR ) // Free image on error
     return(BADR);
   return( OKF );
}


int loadPng(char *fname, imgdes *image, int &rcode )
{
   PngData pdat;

   /* Get info on the file we're to load */
   rcode = pnginfo(fname, &pdat);
   if(rcode != NO_ERROR) { /* Fill structure */
     return(BADF);
     }
   /* Allocate space for an image */
   rcode = allocimage(image, pdat.width, pdat.length, pdat.vbitcount);
   if(rcode != NO_ERROR) {
     return(NOMEM);
     }
   /* Load image */
   rcode = loadpng(fname, image);
   if(rcode != NO_ERROR) // Free image on error
     return(BADR);
   return( OKF );
}

CBitmap *loadBitmap( char *file, CDC *dsp )
{
 static char *tps[] = {"PCX", "TIF", "BMP", "GIF", "JPG", "PNG" };
 int type, rcode, res;
 imgdes img;
 UCHAR huge *dib;
 HDC hdcMem;
 HBITMAP hBitmap, hBitOld;
 BITMAP bmap;
 CBitmap *pBit;

 type = fileToType( file );
 if ( type == -1 )
    return( NULL );
 zeroimgdes( &img );
 switch( type ) {
       case TIF :
	   res = loadTiff( file, &img, rcode );
	   break;
       case PCX :
	   res = loadPcx( file, &img, rcode );
	   break;
       case BMP :
	   res = loadBmp( file, &img, rcode );
	   break;
       case GIF :
	   res = loadGif( file, &img, rcode );
	   break;
       case PNG :
	   res = loadPng( file, &img, rcode );
	   break;
       case JPG :
	   res = loadJpg( file, &img, rcode );
	   break;
       default :
	   return( NULL );
	   break;
       }
 if ( res != OKF ) {
    switch( res ) {
	  case BADF :
	      alert_box( ERROR1, "File %s is not a %s File! Error # %d", file, tps[type], rcode );
	      break;
	  case NOMEM :
	      alert_box( ERROR1, "Not Enough Memory to Read %s!", file );
	      break;
	  case BADR :
	      alert_box( ERROR1, "Error Reading %s! Error # %d", file, rcode );
	      freeimage(&img);
	      break;
	  default:
	      break;
	  }
    return( NULL );
    }
 hdcMem = CreateCompatibleDC( dsp->GetSafeHdc() );
 // Create a bitmap of the entire image
 rcode = dibtobitmap(hdcMem, (unsigned char huge *)img.bmh,
      &hBitmap);
 freeimage(&img);
 DeleteDC(hdcMem);
 if ( rcode == NO_ERROR ) {
    pBit = new CBitmap();
    pBit->FromHandle( hBitmap );
    return( pBit );
    }
 return( NULL );
}





