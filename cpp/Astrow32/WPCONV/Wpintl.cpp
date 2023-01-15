#include "stdafx.h"
#include <stdlib.h>
#include <winnls.h>

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

typedef struct WPI {
	char index;
	unsigned short wpc;
	} WPI;


static void update_wpcs( unsigned short *wpcs, WPI *wpi, int count )
{
 int i;

 for ( i = 0; i < count; ++i, ++wpi )
     wpcs[wpi->index-128] = wpi->wpc;
}

#define c(s,c) ((s*256)+(c))
#define N850 38
#define N863 16
#define N865 3

void wp5_code_page_update( unsigned short *wpcs )
{
 static WPI w850[N850] = { 155, 0x151, 157, 0x150, 158, c(0,'x'),
    169, 0x416, 181, 0x11a, 182, 0x11c, 183, 0x120, 184, 0x417,
    189, c(0,'c'), 190, c(0,'Y'), 198, 0x14d, 199, 0x14c, 207, 0x418,
    208, 0x157, 209, 0x156, 210, 0x12a, 226, 0x13c, 227, 0x140,
    228, 0x153, 229, 0x152, 230, c(0,'u'), 231, 0x158, 232, 0x159,
    233, 0x142, 234, 0x144, 235, 0x148, 236, 0x155, 237, 0x154,
    244, c(0,'P'), 245, c(0,'S'), 211, 0x12c, 212, 0x2e, 214, 0x130,
    215, 0x132, 216, 0x134, 222, 0x136, 224, 0x13a, 225, 0x117 };
 static WPI w863[N863] = { 132, 0x11c, 134, c(0,'P'), 141, c(0,'='),
   143, c(0,'S'), 153, c(1,61), 162, c(1,49), 142, 0x120, 145, 0x12e,
   146, 0x12a, 148, 0x12c, 149, 0x134, 152, 0x418, 157, 0x148, 158, 0x144,
   163, 0x142, 168, 0x132 };
 static WPI w865[N865] = { 155, c(1,0x51), 151, c(1,0x50), 175, c(4,0x18) };

 switch( GetOEMCP() ) {
       case 850 :
	    update_wpcs( wpcs, w850, N850 );
	    break;
       case 863 :
	    update_wpcs( wpcs, w863, N863 );
	    break;
       case 865 :
	    update_wpcs( wpcs, w865, N865 );
	    break;
       default :
	    return;
	    break;
       }
}
