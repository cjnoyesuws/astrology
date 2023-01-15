#include "stdafx.h"
#include <conio.h>
#include <mbctype.h>
// langfixup.cpp : Defines the entry point for the console application.
//
typedef union cpval {
int icpval;
unsigned char ccpval[4];
} cpval;

void Convert( int argc, char *argv[] )
{
 char langdir[255], engdir[255], savedir[255];
 char langfname[255], engfname[255], savefname[255];
 FILE *langinstream, *langoutstream, *engstream;
 unsigned char *langbuf;
 char *engbuf;
 unsigned char *outbuf;
 int len, cpage;
 cpval cpbuf;

 langbuf = new unsigned char[15000];
 engbuf = new char[15000];
 outbuf = new unsigned char[15000];
 strcpy( langdir, argv[1] );
 strcpy( engdir, argv[2] );
 strcpy(savedir, argv[3] );
 if ( langdir[strlen(langdir)-1] != '\\' )
	 strcat( langdir, "\\");
 if ( engdir[strlen(engdir)-1] != '\\' )
	 strcat( engdir, "\\");
 if ( savedir[strlen(savedir)-1] != '\\' )
	 strcat( savedir, "\\");
 
 for ( int i = 4; i < argc; i++ ) {
	 printf("processing: %s\n", argv[i] );
     memset( langbuf,0,15000);
     memset( engbuf,0,15000);
     memset( outbuf,0,15000);
     strcpy(langfname, langdir );
     strcat(langfname, argv[i] );
     strcpy(engfname, engdir );
     strcat(engfname, argv[i] );
     strcpy(savefname, savedir );
     strcat(savefname, argv[i] );
     if ( (langinstream =fopen(langfname,"rt")) == NULL ) 
     {
       printf( "can't open %s for reading", langfname );
       delete langbuf;
       delete engbuf;
       delete outbuf;
       return;
     }
    if ( (langoutstream =fopen(savefname,"wt")) == NULL ) 
     {
       printf( "can't open %s for writing", savefname );
       fclose( langinstream );
       delete langbuf;
       delete outbuf;
       delete engbuf;
       return;
     }
     if ( (engstream =fopen(engfname,"rt")) == NULL ) 
     {
       printf( "can't open %s for reading", engfname );
       fclose( langinstream );
       fclose( langoutstream );
       delete langbuf;
       delete outbuf;
       delete engbuf;
       return;
     }
     char *read;
     int ch;
     ch = fgetc(langinstream);
     if ( ch != '#' ) {
	     cpbuf.ccpval[0] = ch;
	     cpbuf.ccpval[1] = fgetc(langinstream);
	     cpbuf.ccpval[2] = fgetc(langinstream);
	     cpbuf.ccpval[3] = '\0';
     }
     else
        ungetc(ch,langinstream);

     while ( ( fgets((char *)langbuf, 14999, langinstream )) != NULL ) 
     {
       unsigned char *ip, *op;
       fgets(engbuf, 14999, engstream );
       if ( langbuf[0] == '#' ) {
	       fputs( (char *)engbuf, langoutstream );
         }
       else {
	     fputs( (char *)langbuf, langoutstream );
         }
   
      }
     fclose( langinstream );
     fclose( langoutstream );
     fclose( engstream );
     }
}



int main(int argc, char* argv[])
{
	printf("argc=%d",argc); 
	if ( argc < 4 )
	{
		printf("Langfixup: fixup texts\n");
		printf("langfixup languagedirectory inputfile englishdirectory\n");
		printf("ex langfixup C:\\Astrow test.txt D:\\");
		exit(0);
	}
    Convert(argc, argv);	
	getche();
	return 0;
}



