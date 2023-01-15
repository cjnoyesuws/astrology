#include "stdafx.h"
#include "errors.fns"
#include "wmfrec.hpp"
#include "assert.h"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

void WMFPlaceHead::setup( short x, short y, short sc )
{
 botx = x;
 boty = y;
 scale = sc;
}

void WMFPlaceHead::getChecksum()
{
 unsigned cks;

 id = 0x9ac6cdd7L;
 unused = 0;
 topx = 0;
 topy = 0;
 unused2 = 0L;
 cks = HIWORD(id);
 cks ^= LOWORD(id);
 cks ^= topx;
 cks ^= topy;
 cks ^= botx;
 cks ^= boty;
 cks ^= scale;
 checksum = cks;
}


int processRecord( WMFItem *it, char *buf, FILE *istream, FILE *ostream )
{
 static short x, y;

 switch( it->code ) {
       case WMF_REC_TextOut :
	   {
	   fread( buf, (it->size * 2)-6, 1, istream );
	   WMFTxtOutXY *pxy = (WMFTxtOutXY *)((char *)it+(it->size * 2)-4);
	   pxy->y -= y;
	   pxy->x -= x;
	   fwrite( it, it->size * 2, 1, ostream );
	   }
	   break;
       case WMF_REC_PatBlt  :
	   {
	   fread( buf, sizeof(WMFPBlt)-6, 1, istream );
	   WMFPBlt *pb = (WMFPBlt *)it;
	   pb->y -= y;
	   pb->x -= x;
	   fwrite( it, sizeof(WMFPBlt), 1, ostream );
	   }
	   break;
       case WMF_REC_Elipse :
	   {
	   fread( buf, 8, 1, istream );
	   WMFRectParm *rp = (WMFRectParm *)it;
	   rp->y1 -= y;
	   rp->x1 -= x;
	   rp->y2 -= y;
	   rp->x2 -= x;
	   fwrite( it, 14, 1, ostream );
	   }
	   break;
       case WMF_REC_LineTo :
       case WMF_REC_MoveTo :
	   {
	   fread( buf, 4, 1, istream );
	   WMFYXParm *yx = (WMFYXParm *)it;
	   yx->y -= y;
	   yx->x -= x;
	   fwrite( it, 10, 1, ostream );
	   }
	   break;
       case WMF_REC_WinOrg :
	   {
	   fread( buf, 4, 1, istream );
	   WMFYXParm *yx = (WMFYXParm *)it;
	   y = yx->y;
	   x = yx->x;
	   }
	   break;
       case WMF_REC_WinExt :
	   fread( buf, 4, 1, istream );
	   break;
       case WMF_REC_TextColor :
       case WMF_REC_BkColor :
	   fread( buf, 4, 1, istream );
	   fwrite( it, 10, 1, ostream );
	   break;
       case WMF_REC_BkMode :
       case WMF_REC_SelectObj :
       case WMF_REC_Rop2 :
       case WMF_REC_TextAlign :
       case WMF_REC_DeleteObj :
	   fread( buf, 2, 1, istream );
	   fwrite( it, 8, 1, ostream );
	   break;
       case WMF_REC_MapMode :
	   fread( buf, 2, 1, istream );
	   break;
       default :
	   fread( buf, (it->size * 2)-6, 1, istream );
	   fwrite( it, it->size * 2, 1, ostream );
	   break;
       }
 return( 1 );
}

int fixupMetafile( char *temp, char *name )
{
 char *buf;
 WMFPlaceHead place;
 WMFHead head;
 FILE *istream, *ostream;
 WMFItem it;

 if ( ( istream = fopen( temp, "rb" ) ) == NULL ) {
    do_error( temp );
    return( 0 );
    }
 if ( ( ostream = fopen( name, "wb" ) ) == NULL ) {
    do_error( name );
    fclose( istream );
    return( 0 );
    }
 fread( &head, sizeof(WMFHead), 1, istream );
 place.setup(1333,1000,300);
 place.getChecksum();
 fwrite( &place, sizeof(WMFPlaceHead), 1, ostream );
 fwrite( &head, sizeof(WMFHead), 1, ostream );
 buf = new char[(head.largest_rec*2)+3];
 do {
    if ( feof( istream ) || ferror( istream ) || !fread( buf, 6, 1, istream ) )
       break;
    assert(((WMFItem *)buf)->size <= head.largest_rec);
    processRecord( (WMFItem *)buf, buf+6, istream, ostream );
    } while ( !feof( istream ) );
 delete buf;
 fclose( istream );
 fclose( ostream );
 return( 1 );
}

