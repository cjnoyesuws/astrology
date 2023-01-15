#include "stdafx.h"
#include <atlcomtime.h>
#include "date.hpp"
#include "biochart.hpp"
#include "biodata.hpp"
#include "biochdta.hpp"
#include "errors.fns"

DayData *BiorythmData::operator[](int i)
{
 if ( i < 0 || i > cnt )
    return( NULL );
 else
    return( &data[i] );
}


void BiorythmData::calculate()
{
 double j;
 int i;
 Date d;

 setCnt(chart.getStart().daysToMonth());
 j = chart.getBirth().julian();
 for ( i = 0, d = chart.getStart(); i < cnt; i++ ) {
     data[i].setup(d);
     data[i].calculate(j);
     physpt[i] = data[i].getPhysical().get();
     emotpt[i] = data[i].getEmotional().get();
     intelpt[i] = data[i].getIntellectual().get();
     critpt[i] = data[i].getCritical().get();
     d++;
     }
}

int BiorythmData::export( char *name, char *css )
{
 int i;
 int html = 0;
 FILE *stream;

 if ( strstr(name,".htm") != NULL )
	 html = 1;
 stream = fopen( name, "wt" );
 if ( stream == NULL ) {
    do_error( name );
    return( 0 );
    }
 if (html) {
   fprintf(stream,"<HTML>\n<HEAD><TITLE>Biorythm Report</TITLE>");
   if (css != NULL && strlen(css)>0)
      fprintf(stream,"<LINK REL=STYLESHEET TYPE=\"text/css\" HREF=\"%s\">\n", css);
   fprintf(stream,"</HEAD>\n<BODY><DIV>" );
   fprintf(stream,"<h2><center>Biorythm Report</center></h2></div><div>\n" );
 }
 chart.export(stream, true);
 if (html) {
   fputs("<table width=\"100%%\" border=\"0\">\n", stream);
   fputs("<th><td><b>PHYSICAL</b></td><td><b>EMOTIONAL</b></td><td><b>INTELLECTUAL</b></td><td><b>CRITICAL</b></td><td><b>WARNING</b></td></th>\n",stream);
 }
 else {
   fprintf( stream, "\"DATE\",\"PHYSICAL\",\"EMOTIONAL\",\"INTELLECTUAL\",\"CRITICAL\"\n" );
   fprintf( stream, "\"====\",\"========\",\"=========\",\"============\",\"========\"\n" );
 }
 for ( i = 0; i < cnt; i++ )
     data[i].export(stream, true);
 if (html) {
   fputs("<div></table></body></html>",stream);
 }
 fclose ( stream );
 return( 1 );
}

void BiorythmData::nextMonth()
{
 getChart().getStart().getMonth()++;
 if (getChart().getStart().getMonth() > 12) {
    getChart().getStart().getMonth() = 1;
    getChart().getStart().getYear()++;
    }
 calculate();
}

void BiorythmData::prevMonth()
{
 getChart().getStart().getMonth()--;
 if ( getChart().getStart().getMonth() < 1 ) {
    getChart().getStart().getMonth() = 12;
    getChart().getStart().getYear()--;
    }
 calculate();
}

void BiorythmData::nextYear()
{
 getChart().getStart().getYear()++;
 calculate();
}

void BiorythmData::prevYear()
{
 getChart().getStart().getYear()--;
 calculate();
}

