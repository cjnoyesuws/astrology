#include <stdio.h>

int compare_house_cusps( int first, int second, unsigned short mins  )
{
 if ( second - first > 0 ) {
    if ( mins < second && mins > first )
       return( 1 );
    else
       return( 0 );
    }
 second += 360*60;
 if ( mins < second && mins > first )
    return( 1 );
 mins += 360*60;
 if ( mins < second && mins > first )
    return( 1 );
 else
    return( 0 );
}


void main()
{
 printf( "%d, %d, %d, %d\n", 100, 500, 200,
       compare_house_cusps( 100, 500, 200 ) );
 printf( "%d, %d, %d, %d\n", 100, 500, 800,
       compare_house_cusps( 100, 500, 800 ) );
 printf( "%d, %d, %d, %d\n", 100, 500, 50,
       compare_house_cusps( 100, 500, 50 ) );
 printf( "%d, %d, %d, %d\n", 300*60, 100, 200,
       compare_house_cusps( 300*60, 100, 200 ) );
 printf( "%d, %d, %d, %d\n", 300*60, 100, 50,
       compare_house_cusps( 300*60, 100, 50 ) );
 printf( "%d, %d, %d, %d\n", 300*60, 100, 320*60,
       compare_house_cusps( 300*60, 100, 320*60 ) );
 printf( "%d, %d, %d, %d\n", 300*60, 100, 320*60,
       compare_house_cusps( 300*60, 100, 320*60 ) );
 printf( "%d, %d, %d, %d\n", 300*60, 100, 180*60,
       compare_house_cusps( 300*60, 100, 180*60 ) );
}
