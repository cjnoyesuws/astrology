#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct WRI_HEADER {
	unsigned  id;
	unsigned dty;
	unsigned wTool;
	unsigned res[4];
	long     fcMac;
	unsigned pageOfs[6];
	char     szSsht[66];
	unsigned pnMac;
	char     blank[30];
	unsigned getPnChar() { return( (fcMac+127)/128 ); }
	unsigned getPageMac() { return pnMac; }
	long     getFcMac()   { return fcMac; }
	void setPageMac(unsigned p) { pnMac = p; }
	void setFcMac(long l)   { fcMac = l; }
	} WRI_HEADER;

WRI_HEADER header;

char ibuf[15000];
char obuf[20000];

void wrap( char *in, char *out )
{
 char *i, *o = out;
 int col = 0;

 for ( i = in; *i; i++ ) {
     if ( *i == ' ' && col > 60 ) {
        *o++ = '\n';
        *o++ = ' ';
        *o++ = ' ';
        *o++ = ' ';
        *o++ = ' ';
        *o++ = ' ';
        col = 0;
        }
     else if ( *i == '\n' ) {
        col = 0;
        *o++ = '\n';
        *o++ = ' ';
        *o++ = ' ';
        *o++ = ' ';
        *o++ = ' ';
        *o++ = ' ';
        }
     else {
	*o++ = *i;
        col++;
        }
     }
 *o++ = '\0';
}

convert( FILE *istream, FILE *ostream )
{
 int col = 0;
 long cnt;

 ibuf[0] ='\0';
 for ( cnt = 0; cnt < header.fcMac; cnt += strlen(ibuf) ) {
     fgets( ibuf, 15000, istream );
     wrap( ibuf, obuf );
     fputs( obuf, ostream );
     }
 return( 1 );
}

void main( void )
{
 char ibuf[150], obuf[150], *p;
 FILE *istream, *ostream;

 printf( "CONVERT MIROSOFT WINDOWS WRITE FILES TO .TXT FILES\n" );
 printf( "Input .WRI File Name: " );
 gets( ibuf );
 strcpy( obuf, ibuf );
 p = strchr( obuf, '.' );
 if ( p != NULL )
    strcpy( p, ".TXT" );
 else
    strcat( obuf, ".TXT" );
 printf( "Output .TXT File Name (Enter for \"%s\"): ", obuf );
 gets( obuf );
 if ( !strlen( obuf ) ) {
    strcpy( obuf, ibuf );
    p = strchr( obuf, '.' );
    if ( p != NULL )
       strcpy( p, ".TXT" );
    else
       strcat( obuf, ".TXT" );
    }
 if ( ( istream = fopen( ibuf, "rb" ) ) == NULL ) {
    printf( "\nCan\'t Open %s to Read!", ibuf );
    exit( -1 );
    }
 if ( ( ostream = fopen( obuf, "wt" ) ) == NULL ) {
    printf( "\nCan\'t Open %s to Write!", obuf );
    fclose( istream );
    exit( -1 );
    }
 fputs( "     ", ostream );
 fread( &header, sizeof(WRI_HEADER), 1, istream );
 header.fcMac -= 128;
 convert( istream, ostream );
 fclose( istream );
 fclose( ostream );
}
