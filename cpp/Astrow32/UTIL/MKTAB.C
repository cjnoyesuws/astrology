#include <math.h>
#include <stdio.h>

#define PI        3.14159265358979323846
#define TWO_PI    (PI + PI)
#define d2r(d)    ((d) * (PI/180.0))


double sin_val(int deg)
{
 double x;
 x = sin(d2r((double)deg));
 if ( deg < 10 || deg > 80 )
     return( x );
 else if ( deg < 13 || deg > 77 )
     return( x * 1.0035 );
 else if ( deg < 16 || deg > 75 )
     return( x * 1.0043 );
 else if ( deg < 18 || deg > 68 )
     return( x * 1.005 );
 else if ( deg < 21 || deg > 65 )
     return( x * 1.0055 );
 else if ( deg < 23 || deg > 63 )
     return( x * 1.0065 );
 else if ( deg < 26 || deg > 61 )
     return( x * 1.0085 );
 else if ( deg < 28 || deg > 58 )
     return( x * 1.0092 );
 else if ( deg < 30 || deg > 55 )
     return( x * 1.0097 );
 else if ( deg < 33 || deg > 53 )
     return( x * 1.0103 );
 else if ( deg < 38 || deg > 50 )
     return( x * 1.0106 );
 else
     return( x * 1.011 );
}

void main()
{
 double x, d;
 int i;

 for ( i = 0; i <= 90; i++ ) {
     x = sin_val(i);
     x *= 65535.0;
     x += .5;
     printf( "%1.0lf,\n", x );
     }

}
