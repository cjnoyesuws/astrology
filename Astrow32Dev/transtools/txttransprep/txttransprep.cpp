// transprep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ctype.h"

FILE *rcfile;
FILE *txtfile;
FILE *prepfile;
char srcbuf[10000];
char fbuftxt[200];
char fbufspl[200];
char fname[200];
char *lastbuf;

char *setup_file( char *name, char *ext, char *dir, char *buf )
{
  strcpy(buf,dir);
  strcat(buf,"\\");
  strcat(buf,name);
  char *p = strchr(buf,'.');
  strcpy(p,ext);
  lastbuf = buf;
  return buf;
}

int openf( char *name, char *rc, char *spl, char *rcdir, char *spldir, char *txtdir )
{
 rcfile = fopen(setup_file(name,".AST",rcdir,fname),rc);
 if ( rcfile == NULL ) {
   printf("bad file %s\n", lastbuf );
   exit( -1 );
 }
 txtfile = fopen(setup_file(name,".TXT",txtdir,fbuftxt),spl);
 if ( txtfile == NULL ) {
   printf("bad file %s\n", lastbuf );
   exit( -1 );
 }
 prepfile = fopen(setup_file(name,".SPL",spldir,fbufspl),spl);
 if ( txtfile == NULL ) {
   printf("bad file %s\n", lastbuf );
   exit( -1 );
 }
 return( 1 );
}


void prepline(char *buf, FILE *prep, FILE *txt)
{
 char tbuf[50];
	if ( !strnicmp(buf,"DEFTABS",7) ) {
	   fputs("DEFTABS`~", prep );
	   fputs(buf+7,txt);
	}
	else if ( !strnicmp(buf,"TABS|",5) ) {
	   int i = 4;
	   while (buf[i] == '|' || isdigit(buf[i]))
		   i++;
       memcpy(tbuf,buf,i);
	   tbuf[i] = '\n';
	   tbuf[i+1] = '\0';
	   fputs(tbuf,prep);
	   fputs(buf+i,txt);
	}
	else {
	   fputs(buf,txt);
	   fputs("`~\n",prep);
	}
}


void prepmerge( char *file, char *rcdir, char *spldir, char *txtdir  ) 
{
 char chr, nxt;
 openf(file,"rt","wt", rcdir, spldir, txtdir);
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
  if ( argc < 5 )
	 printf("needs four args, file srcdir splitdir txtdir\n");
  else
     prepmerge(argv[1],argv[2],argv[3],argv[4]);
}

