#include <stdio.h>

/*
120 ST_BLK DISCARDABLE
BEGIN
    0x6f44, 0x7374, 0x4901, 0x636e, 0x6568, 0x0173, 0x694d, 0x6c6c, 0x6d69,
    0x7469, 0x7265, 0x0073, 0x0000, 0x0000, 0x0000, 0x0000
END
*/

FILE *istream;
buf[1000];
int index;
int code;

int readnum()
{
 unsigned int x;
 char c;

 c = fgetc(istream);
 if ( c == ' ' ) {
    while ( fgetc(istream) == ' ' );
    }
 c = fgetc(istream);
 if ( c == '0' )
    c = fgetc(istream);
 fscanf( istream, "%x", &x );
 buf[index++] = x & 0xff;
 buf[index++] = (x & 0xff00)/0xff;
 c = fgetc(istream);
 if ( c == '\n' )
    return( 0 );
 else if ( c == ',' ) {
    c = fgetc(istream);
    return( 1 );
    }
}

void xread()
{
 char bff[100];

 if ( feof( istream ) )
    exit( 1 );
 index = 0;
 fscanf( istream, "%d", &code );
 fgets( bff, 99, istream );
 fgets( bff, 99, istream );
 while ( readnum() );
 fgets( bff, 99, istream );
 fgets( bff, 99, istream );
 index++;
}


void xwrite()
{
 int i, c = 0;

 if ( !code )
    exit( 1 );
 printf( "%d ST_BLK DISCARDABLE\nBEGIN\n    \"", code );
 for ( i = 0; buf[i]; i++ ) {
     if ( buf[i]  == '\1' ) {
	if ( c > 50 ) {
	   printf( "\\1\"\n    \"" );
	   c = 0;
	   }
	else {
	   printf( "\\1" );
	   c+=2;
	   }
	}
     else if ( buf[i]  == ' ' ) {
	if ( c > 50 ) {
	   printf( " \"\n    \"" );
	   c = 0;
	   }
	else {
	   printf( " " );
	   c++;
	   }
	}
     else {
	c++;
	putchar( buf[i] );
	}
     }
 printf( "\\0\"\n" );
 printf( "END\n\n" );
}


void main(int argc, char *argv[] )
{
 istream = fopen( argv[1], "rt" );
 do {
   code = 0;
   xread();
   xwrite();
   } while ( !feof( istream ) );
}

