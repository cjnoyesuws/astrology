#include "stdafx.h"
#include <math.h>


/* fuction that returns a Truncated double argument such that
   trunc_val(-21.7) = -21.0, and trunc_val(21.7) = 21.0 */

double trunc_val( double val )
{
 if ( val < 0.0 )
    return( ceil( val ) );
 else
    return( floor( val ) );
}

/* function that completes fmod in library. If the number involved needs
   to be fmod'ed then fmod is called otherwise it is skipped. If the
   remaining number is negative then divisor is added to that number.
   Returns the corrected number. Used for degrees and radians which need
   to be kept within a circle */

double fmodulus( double num, double divisor )
{
 if ( fabs( num ) >= divisor )
    num = fmod( num, divisor );
 if ( num < 0.0 )
    num += divisor;
 return( num );
}

