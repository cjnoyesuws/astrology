#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "julian.h"
#include "utl.h"
#include "compute.fns"
#include "basedcs.h"

#define STALL  1.48
#define RETRO  1.32

static char BCS pluto_correx[] = { 76, 84,
	92, 101, 81, 91, 101, 82, 63,
	74, 86, 98, 80, 92, 75, 58, 71,
	84, 97, 80, 63, 77, 90, 74, 88,
	71, 85, 70, 85, 69, 85, 71, 86,
	73, 60, 77, 64, 82, 71, 60, 79,
	69, 60, 81, 71, 93, 55, 77, 69,
	92, 55, 78, 71, 94, 58, 82, 75,
	69, 63, 57, 80, 44, 67, 60, 84,
	47, 70, 63, 85, 48, 71, 63, 86,
	49, 72, 64, 87, 51, 44, 67, 61,
	55, 49, 73, 68, 63, 58, 53, 78,
	43, 69, 64, 30, 56, 52, 77, 43,
	39, 64, 60, 55, 50, 45, 70, 34,
	58, 52, 75, 39, 61, 53, 75, 37,
	59, 50, 71, 31, 52, 42, 62, 52,
	42, 62, 22, 42, 62, 51, 42, 31,
	51, 41, 31, 50, 40, 60, 19, 39,
	58, 47, 36, 55, 43, 61, 20, 37,
	54, 41, 28, 43, 59, 14, 28, 42,
	55, 38, 50, 31, 42, 22, 32, 41,
	50, 29, 37, 45, 23, 30, 36, 43,
	19, 25, 30, 36, 11, 46, 50, 54,
	28, 32, 35, 8, 40, 42, 43, 14,
	15, 44, 43, 12, 40, 37, 4, 29,
	24, 48, 11, 33, 25, 45, 4, 23,
	40, 27, 13, 28, 42, 25, 38, 19,
	0, 11, 20, 29, 7, 15, 21, -1,
	3, 38, 42, 16, 19, 21, -7, 23,
	23, 21, 20, 17, 13, 9, 4, 27,
	19, 11, 31, 20, 8, 24, 9, 23,
	6, 17, 27, 6, 13, 18, -6, 26,
	28, 28, -1, 26, 23, 19, 14, 37,
	0, 20, 10, 0, 17, 4, -9, 4,
	17, 29, 10, 20, 28, 5, 11, 15,
	-11, 20, 20, -10, 16, 11, 5, -2,
	17, 6, -7, 7, -9, 0, 9, -13,
	-8, 23, -5, -6, 20, -14, 8, 0,
	-11, 5, 20, 4, 15, 25, 3, 9,
	13, -14, 15, -15, 10, 5, -1, -11,
	7, -5, 8, 20, 1, 8, -14, -11,
	19, -11, -15, 7, -1, 17, -27, -14,
	-4, -27, 6, 7, 6, 1, -5, -16,
	0, -16, -5, -27, 6, 8, -22, 3,
	-3, -13, 4, -11, 0, -20, -15, -12,
	-12, 14, -21, 0, -12, 2, -15, -6,
	-1, 1, 0, -3, -11, -21, -6, -24,
	-15, -11, -10, -13, -20, -1, -15, -4,
	-27, 5, -24, 0, -39, -22, -39, -1,
	-26, -26, -30, -8, -20, -6, -25, -19,
	-17, -19, -25, -5, -19, -7, -29, -25,
	-25, 0, -38, -20, -36, 2, -21, 8,
	-24, -31, -13, -29, -20, -15, -15, -19,
	0, -12, -31, -25, -23, -26, -34, -17,
	-34, -26, -24, -25, -2, -13, -29, -20,
	-15, -15, -18, -27, -10, -27, -48, -14,
	-43, -17, -25, -36, -22, -12, -35, -32,
	-33, -37, -16, -28, -14, -33, -25, -22,
	-21, -25, -2, -12, -26, -14, -35, -29,
	-27, -28, -33, -41, -22, -36, -53, -14,
	-37, -32, -31, -32, -36, -12, -20, -30,
	-41, -26, -41, -28, -17, -37, -28, -20,
	-13, -37, -32, -27, -23, -49, -15, -41,
	-38, -34, -30, -26, -52, -17, -42, -36,
	-30, -24, -47, -39, -31, -22, -42, -32,
	-20, -37, -53, -9, -23, -35, -17, -27,
	-35, -11, -16, -49, -49, -18, -45, -39,
	-31, -20, -36, -21, -32, -40, -15, -17,
	-46, -12, -34, -53, -38, -21, -29, -34,
	-35, -32, -26, -16, -32, -15, -24, -29,
	-32, -30, -54, -16, -33, -47, -28, -35,
	-9, -39, -35, -28, -47, -33, -15, -54,
	-29, -30, -57, -21, -41, -28, -40, -48,
	-24, -54, -21, -44, -63, -18, -58, -35,
	-37, -65, -29, -49, -35, -46, -24, -27,
	-27, -52, -43, -30, -44, -24, -59, -32,
	-30, -26, -47, -35, -49, -60, -38, -42,
	-44, -41, -36, -57, -45, -59, -41, -49,
	-24, -56, -24, -49, -42, -60, -46, -58,
	-37, -42, -44, -42, -38, -59, -48, -63,
	-44, -52, -27, -58, -56, -50, -42, -60,
	-45, -27, -36, -42, -45, -45, -43, -37,
	-59, -48, -65, -49, -30, -39, -45, -49,
	-51, -50, -46, -70, -63, -52, -69, -54,
	-66, -46, -54, -59, -32, -62, -30, -55,
	-48, -68, -56, -41, -54, -34, -71, -46,
	-49, -48, -46, -71, -64, -54, -72, -58,
	-71, -53, -33, -70, -45, -78, -50, -50,
	-77, -44, -68, -60, -51, -70, -58, -44,
	-58, -40, -81, -60, -38, -74, -48, -51,
	-52, -51, -79, -74, -39, -60, -51, -39,
	-56, -70, -83, -64, -43, -80, -55, -58,
	-58, -58 };
	
#define FVAL 2396758.5
#define LVAL 2469608.5


double correct_pluto( JULIAN *j, double lpd, double earth )
{
 int index;
 double x, t, v;


 t = j->jd_base;
 if ( t < FVAL || t > LVAL )
    return( lpd );
 t -= FVAL;

 index = (int) trunc_val(t/100.0);
 t = fmodulus( t, 100.0 );
 v  = (double) pluto_correx[index];
 x = (double) pluto_correx[index+1];
 v += 30.0;
 v /= 30.0;
 x += 30.0;
 x /= 30.0;
 v *= t;
 v /= 100;
 x *= (100.0 - t);
 x /= 100;
 v += x;
 lpd -= d2r( v );
 x = lpd - earth;
 if ( x < RETRO ) {
    v /= 4.0;
    lpd += d2r( v );
    }
 else if ( x < STALL ) {
    v /= 7.0;
    lpd += d2r( v );
    }
 return( lpd );
}
