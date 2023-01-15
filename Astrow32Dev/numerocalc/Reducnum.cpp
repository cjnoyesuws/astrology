#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

short reduce_num( char *num_str, short *test )
{
 short tot = 0, v;

 char buf[10];
 char *s = num_str;
 v = atoi(num_str);
 if ( v == 13 || v == 19 || v == 16 || v == 14 )
    *test = v;
 else
    *test = 0;
 if ( strlen( num_str ) == 1 && isdigit( num_str[0] ) )
    return( num_str[0] - '0' );
 else if ( !strcmp( num_str, "11" ) || !strcmp( num_str, "22" ) )
    return( v );
 while ( *s ) {
       if ( isdigit( *s ) )
	  tot += ( *s - '0' );
       s++;
       }
 if ( tot <= 9 || tot == 11 || tot == 22 )
    return( tot );
 assert( tot > 0 );
 itoa( tot, buf, 10 );
 return( reduce_num( buf, test ) );
}

short reduce_int( short num, short *test )
{
 short n;
 char buf[10];

 if ( !num )
    return( 0 );
 else if ( num <= 9 || num == 11 || num == 22 )
    return( num );
 itoa( num, buf, 10 );
 n = reduce_num( buf, test );
 if ( num == 13 || num == 19 || num == 16 || num == 14 )
    *test = num;
 else
    *test = 0;
 return( n );
}

short add_ints_reduce( short num1, short num2, short num3, short *test  )
{
 short n;

 num1 = reduce_int( num1, &n );
 num2 = reduce_int( num2, &n );
 num3 = reduce_int( num3, &n );
 num1 += num2 + num3;
 return( reduce_int( num1, test ) );
}

short add_digits_reduce( short num1, short num2, short num3, short *test  )
{
 char buf[20];

 sprintf( buf, "%d%d%d", num1, num2, num3 );
 return( reduce_num( buf, test ) );
}

short subtract_ints_reduce( short num1, short num2, short *test )
{
 short x;
 char buf[10];

 num1 = reduce_int( num1,&x );
 num2 = reduce_int( num2, &x );
 if ( num1 < num2 ) {
    x = num1;
    num1 = num2;
    num2 = x;
    }
 num1 -= num2;
 itoa( num1, buf, 10 );
 return( reduce_num( buf, test ) );
}
