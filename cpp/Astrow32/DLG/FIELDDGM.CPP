#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "fielddgm.hpp"
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

int zDegMinField::checkData()
{
 int d, m, v;

 sscanf( (char *)text(), "%d:%d", &d, &m );
 v = (d * 60) + m;
 if ( v < 0 || v > (60 * 360) )
    return( 0 );
 else
    return( 1 );
}


int zDegMinField::storeData()
{
 int d, m, v;

 sscanf( (char *)text(), "%d:%d", &d, &m );
 v = (d * 60) + m;
 *dst = v;
 return( 1 );
 }


int zDegMinField::setToDefault()
{
 char buf[8];
 int v;

 sprintf( buf, "%02d:%02d", *dst/60, *dst%60 );
 text(buf);
 return( 1 );
 }


zDegMinField::zDegMinField(zFrameWin *fw, int id, int *p, DWORD mask ) :
       zIntEdit(fw, id, p, new zPictFormatter( mask, "99':'[012345]9"), mask )
{
 dst = p;
 setToDefault();
}
