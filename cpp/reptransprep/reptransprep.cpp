// transprep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ctype.h"

FILE *rcfile;
FILE *txtfile;
FILE *prepfile;
char fbuf[200];
char fname[200];
char srcbuf[10000];

extern void prepline(char *buf, FILE *prep, FILE *txt);

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


void prepmerge( char *file ) 
{
 char chr, nxt;
 strcpy(fname,file);
 openf("rt","wt");
 if ( rcfile == NULL ) {
   printf("bad file %s\n", fbuf );
   exit( -1 );
 }
 while ( !feof(rcfile) ) {
	fgets(srcbuf,10000,rcfile);
	if ( srcbuf[0] == '@' || srcbuf[0] == '#')
		fputs(srcbuf,prepfile);
	else 
		prepline( srcbuf, prepfile, txtfile );
 }
 fclose( rcfile );
 fclose( prepfile );
 fclose( txtfile );
}

int main(int argc, char* argv[])
{
  prepmerge(argv[1]);
}

