// numchart.cpp : Defines the entry point for the console application.
//
extern "C" {
#include "cgic205/cgic.h"
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <ctype.h>
#include "chartinf.h"
#include "numbr.h"
#include "name.h"
#include "namegraf.h"
#include "numero.h"
#include "numdll.h"


char data_path[100];
char chart_temp[100];

void getconf()
{
 FILE * stream;

 stream = fopen("numero.conf", "r");
 fgets(data_path,100, stream);
 fgets(chart_temp, 100, stream);
 data_path[strlen(data_path)-1] = '\0';
 chart_temp[strlen(chart_temp)-1] = '\0';
 fclose(stream);
}


int cgiMain()
{
 char buf2[500];
 char buf[500];
 int chart, drive;
 FILE *stream=NULL;

 getconf();
 //CookieSet();
/* Send the content type, letting the browser know this is HTML */
 cgiHeaderContentType("text/html");
 strcpy( buf, chart_temp );
#ifdef _DEBUG
 cgiReadEnvironment("./capcgi.dat");
#else
 cgiWriteEnvironment("./capcgitest.dat");
#endif
 readdata( chart );
 do {
   if ( stream != NULL )
	   fclose(stream);
   strcpy( buf2, chart_temp );
   sprintf(buf,"num%-d",rand());
   strcat(buf2,buf);
   strcat(buf2, ".out" );
 } while ((stream =fopen(buf2,"r")) != NULL );
 CompileReport( chart, buf2 );
 convert( buf2, cgiOut );
 unlink(buf2);
 return(0);
}
