// transprep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ctype.h"

FILE *rcfile;
FILE *txtfile;
FILE *prepfile;
char fbuf[200];
char fname[200];
char prepbuf[500];
char txtbuf[500];
char rcbuf[500];

int openf( char *rc, char *spl )
{
 rcfile = fopen(fname,rc);
 strcpy(fbuf,fname);
 char *p = strchr(fbuf,'.');
 strcpy(p,".txt");
 txtfile = fopen(fbuf,spl);
 strcpy(p,".spl");
 prepfile = fopen(fbuf,spl);
 return( 1 );
}

void nextword()
{
  fgets(txtbuf,500,txtfile);
  txtbuf[strlen(txtbuf)-1] = '\0';
  fputs(txtbuf,rcfile);
}

void prepmerge( char *file ) 
{
 char chr, nxt;
 strcpy(fname,file);
 openf("wt","rt");
 if ( rcfile == NULL ) {
   printf("bad file %s\n", fbuf );
   exit( -1 );
 }
 while ( !feof(prepfile) ) {
	chr = fgetc(prepfile);
	if ((char) chr == '`' ) {
	   nxt = fgetc(prepfile);
	   if ((char) nxt == '~' ) 
	      nextword();
	   else {
		  fputc( chr, rcfile );
	      fputc( nxt, rcfile );
	   }
	}
	else
		fputc( chr, rcfile );
 }
 fclose( rcfile );
 fclose( prepfile );
 fclose( txtfile );
}

int main(int argc, char* argv[])
{
  prepmerge(argv[1]);
}

