#include <stdio.h>

char array[5][4] = {1,2,3,4,11,12,13,14,21,22,23,24,31,32,33,34,41,42,43,44};
char array2[5][4];
void main()
{
 FILE *stream = fopen("test.dat", "wb" );
 fwrite(array,1,20,stream);
 fclose( stream );
 array2[0][0] = 1;
 array2[1][0] = 1;
 array2[2][0] = 1;
 array2[0][1] = 2;
 array2[0][2] = 2;
 array2[0][3] = 2;
 stream = fopen("test2.dat", "wb" );
 fwrite(array2,1,20,stream);
 fclose( stream );

}

