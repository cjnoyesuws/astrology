extern "C" {
#include "cgic205/cgic.h"
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chartinf.h"
#include "numbr.h"
#include "name.h"
#include "namegraf.h"
#include "numero.h"
#include "numdll.h"
#include "errors.fns"

extern CHART_INFO chart_info_data;

char *makefld( char *nam, char *key)
{
 static char buf[20];
 strcpy(buf,nam);
 strcat(buf,key);
 return( buf); 
}

void parsename(char *nam, NAME_REC *name )
{
 char buf[20];

 char *p, *p2;

 cgiFormString(makefld(nam,"first"),name->first,50);
 cgiFormString(makefld(nam,"middle"),name->middle,50);
 cgiFormString(makefld(nam,"last"),name->last,50);
 name->include = ((strlen(name->first)+strlen(name->middle)+strlen(name->last))?1:0);
}

int readdata( int &chart )
{
 int start=0, end=0, achart=0;
 char got;
 char buf[400];
 int m, d, y, inc;
 
 cgiFormInteger("charttype",&chart,1);

 cgiFormString("birthdate",buf,50);
 sscanf(buf, "%d/%d/%d,%d", &m, &d, &y, &inc );
 chart_info_data.birth_date.month = m;
 chart_info_data.birth_date.day = d;
 chart_info_data.birth_date.year = y;
 chart_info_data.birth_date.include = inc;
 parsename("birth",&chart_info_data.at_birth);
 parsename("current",&chart_info_data.current);
 parsename("opt1",&chart_info_data.opt1);
 parsename("opt2",&chart_info_data.opt2);
 if ( chart==NAMEGRAPH_FILE || chart==NUMGRAPH_FILE ) {
	cgiFormInteger("start", &start, 0);
	cgiFormInteger("End", &end, 0 ); 
	SetGroupStartEnd( start, end );
 }
 return( 1 );
}