#include "stdafx.h"
//#include "basedcs.h"
#include "polar.hpp"
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
/* int sin Table for integer sin function */ 
/*
static int BCS int_sin_tab[] = { 0, 572, 1143, 1713, 2285, 2855,
	3432, 4002, 4569, 5135, 5699, 6261, 6821, 7380, 7938, 8491,
	9040, 9590, 10135, 10679, 11219, 11755, 12285, 12815, 13339,
	13861, 14377, 14891, 15398, 15901, 16400, 16894, 17383, 17863,
	18338, 18809, 19275, 19737, 20189, 20637, 21079, 21509, 21943,
	22360, 22779, 23187, 23588, 23981, 24368, 24747, 25118, 25479,
	25837, 26187, 26528, 26859, 27184, 27499, 27807, 28106, 28396,
	28677, 28949, 29214, 29469, 29713, 29951, 30179, 30393, 30607,
	30805, 30995, 31176, 31347, 31511, 31665, 31804, 31938, 32056,
	32175, 32282, 32374, 32458, 32531, 32596, 32651, 32696, 32728,
	32751, 32768, 32768 };
*/
/*


static unsigned int BCS int_sin_tab[] = { 0, 1140, 2282, 3420,
	4572, 5712, 6851, 7987, 9121, 10252, 11420, 12549, 13674,
	14806, 15923, 17035, 18155, 19257, 20363, 21454, 22538,
	23639, 24710, 25825, 26883, 27932, 28988, 30021, 31075,
	32090, 33112, 34108, 35093, 36086, 37050, 38003, 38945,
	39874, 40832, 41738, 42631, 43511, 44378, 45232, 46071,
	46897, 47708, 48505, 49287, 50054, 50806, 51491, 52211,
	52915, 53576, 54247, 54875, 55512, 56133, 56681, 57266,
	57835, 58356, 58889, 59286, 59781, 60199, 60658, 61098,
	61489, 61891, 62275, 62640, 62985, 63312, 63619, 63862,
	64130, 64328, 64557, 64766, 64729, 64898, 65047, 65176,
	65286, 65376, 65440, 65490, 65522, 65535 };
*/

static unsigned short int_sin_tab[] = { 0, 1140, 2282, 3430,
	4572, 5712, 6851, 7987, 9121, 10252, 11420, 12549, 13674,
	14806, 15923, 17035, 18155, 19257, 20363, 21454, 22538,
	23639, 24710, 25825, 26883, 27932, 28993, 30026, 31066,
	32081, 33106, 34101, 35086, 36072, 37036, 37988, 38929,
	39859, 40792, 41697, 42589, 43468, 44334, 45187, 46026,
	46850, 47661, 48457, 49238, 50004, 50755, 51471, 52190,
	52894, 53566, 54237, 54858, 55496, 56116, 56692, 57278,
	57846, 58356, 58889, 59286, 59781, 60199, 60658, 61098,
	61489, 61891, 62275, 62640, 62985, 63312, 63619, 63862,
	64130, 64328, 64557, 64766, 64729, 64898, 65047, 65176,
	65286, 65376, 65442, 65492, 65523, 65535 };


int enblScPol = 0;
int polarScaleXm = 1, polarScaleYm = 1;
int polarScaleXd = 1, polarScaleYd = 1;

PolarScaler thePolarScaler;

/* integer sin function. Returns an int value scaled to int max val */

short isin( short degs, short max, short sc )
{
 short d, q;
 int tt;
 long t;

 if ( degs < 0 )
    degs += 360;
 if ( degs == 90 )
    return( max );
 else if ( degs == 270 )
    return( -max );
 else if ( degs == 0 || degs == 180 )
    return( 0 );
 _asm {
    mov ax, degs
    cwd
    mov cx, 90
    idiv cx
    mov d, dx
    mov q, ax
    }
 switch ( q ) {
    case 0 :
	 t = (long)int_sin_tab[d];
	 break;
    case 1 :
	 t = (long)int_sin_tab[89-d];
	 break;
    case 2 :
	 t = -(long)int_sin_tab[d];
	 break;
    case 3 :
	 t = -(long)int_sin_tab[89-d];
	 break;
    default :
	 return( isin( degs % 360, max, sc ) );
	 break;
    }
 t *= (long)max;
 t += 32767L;
 t /= 65535L;
 if ( !sc || ! thePolarScaler.isEnabled() )
    return( (int) t );
 else {
    tt = (int) t;
    tt = thePolarScaler.scaleY( tt );
    return( tt );
    }
}

/* integer cos function. Returns an int value scaled to int max val */

short icos( short degs, short max, short sc )
{
 int tt;

 tt = isin( degs - 90, max, 0 );
 if ( !sc || !thePolarScaler.isEnabled() )
    return( tt );
 else {
    tt = thePolarScaler.scaleX( tt );
    return( tt );
    }
}


void PolarScaler::enable(int en )
{
 enblScPol = en;
 if ( !en ) {
    polarScaleXm = 1;
    polarScaleYm = 1;
    polarScaleXd = 1;
    polarScaleYd = 1;
    }
}

void PolarScaler::setScale(int xm, int ym, int xd, int yd )
{
  polarScaleXm = xm;
  polarScaleYm = ym;
  polarScaleXd = xd;
  polarScaleYd = yd;
}

int PolarScaler::scaleX( int x )
{
 if ( !enblScPol)
    return( x );
 x *= polarScaleXm;
 x /= polarScaleXd;
 return x;
}

int PolarScaler::scaleY( int y )
{
 if ( !enblScPol)
    return( y );
 y *= polarScaleYm;
 y /= polarScaleYd;
 return y;
}

int PolarScaler::invScaleX( int x )
{
 if ( !enblScPol)
    return( x );
 x *= polarScaleXd;
 x /= polarScaleXm;
 return x;
}

int PolarScaler::invScaleY( int y )
{
 if ( !enblScPol)
    return( y );
 y *= polarScaleYd;
 y /= polarScaleYm;
 return y;
}



void PolarScaler::setupResolutions( int x, int y )
{
 int en = 1;
 int xm=1, ym=1, xd=1, yd=1;
 if ( x == y ) {
    setScale(1, 1, 1, 1);
    enable( 0 );
    return;
    }
 switch( x ) {
    case 72 :
	 if ( y == 120 ) {
	    xm = 3;
	    xd = 5;
	    }
	 else if ( y == 240 ) {
	    xm = 3;
	    xd = 10;
	    }
	 break;
    case 90 :
	 if ( y == 120 ) {
	    xm = 3;
	    xd = 4;
	    }
	 else if ( y == 72 ) {
	    xm = 11;
	    xd = 9;
	    }
	 break;
    case 120 :
	 switch( y ) {
	       case 72 :
		    xm = 5;
		    xd = 3;
		    break;
	       case 144 :
		    xm = 5;
		    xd = 6;
		    break;
	       case 180 :
		    ym = 3;
		    yd = 2;
		    break;
	       case 360 :
		    xd = 3;
		    break;
	       default :
		    break;
	       }
	 break;
    case 144 :
	 if ( y == 120 ) {
	    xm = 6;
	    xd = 5;
	    }
	 else if ( y == 240 ) {
	    xm = 3;
	    xd = 5;
	    }
	 break;
    case 150 :
	 switch( y ) {
	       case 300 :
		    xd = 2;
		    break;
	       case 100 :
		    xm = 2;
		    xd = 3;
		    break;
	       default :
		    break;
	       }
	 break;
    case 180 :
	 switch( y ) {
	       case 120 :
		    xm = 3;
		    xd = 2;
		    break;
	       case 360 :
		    xd = 2;
		    break;
	       default :
		    break;
	       }
	 break;
    case 240 :
	 switch( y ) {
	       case 120 :
		    xm = 2;
		    break;
	       case 72 :
		    xm = 10;
		    xd = 3;
		    break;
	       case 144 :
		    xm = 5;
		    xd = 3;
		    break;
	       default :
		    break;
	       }
	 break;
    case 300 :
	 switch( y ) {
	       case 150 :
		    xm = 2;
		    break;
	       case 600 :
		    xd = 2;
		    break;
	       default :
		    break;
	       }
	 break;
    case 360 :
	 switch( y ) {
	       case 120 :
		    xm = 3;
		    break;
	       case 180 :
		    xm = 2;
		    break;
	       default :
		    break;
	       }
	 break;
    case 400 :
	 switch( y ) {
	       case 300 :
		    xm = 2;
		    break;
	       case 600 :
		    xd = 2;
		    break;
	       default :
		    break;
	       }
	 break;
    case 600 :
	 if ( y == 300 ) {
	    xd = 2;
	    }
	 break;
    default :
	 x /= 10;
	 y /= 10;
	 xm = x;
	 xd = y;
	 break;
    }
 setScale(xm, ym, xd, yd);
 enable( 1 );
}

