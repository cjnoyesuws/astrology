#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chartinf.h"
#include "name.h"
#include "numbr.h"

extern char *make_date(DATES *);

void chart_header_print( FILE *stream, CHART_INFO *cip )
{
 fprintf( stream, "^@|60|2|5|40|" );
 fprintf( stream, "\n{Data Based On:}\n" );
 if ( cip->at_birth.include && (strlen(cip->at_birth.first) || 
      	strlen(cip->at_birth.middle) || strlen(cip->at_birth.last)) ) {
    if ( strlen(cip->at_birth.middle) )
       fprintf( stream, " |Name at Birth:   |{%s %s %s}.\n",
	  cip->at_birth.first, cip->at_birth.middle, cip->at_birth.last );
    else
       fprintf( stream, " |Name at Birth:   |{%s %s}.\n",
	  cip->at_birth.first, cip->at_birth.last );
    }
 if ( cip->current.include && (strlen(cip->current.first) || 
      	strlen(cip->current.middle) || strlen(cip->current.last)) ) {
    if ( strlen(cip->current.middle) )
       fprintf( stream, " |Currently Used Name: |{%s %s %s}.\n",
	  cip->current.first, cip->current.middle, cip->current.last );
    else
       fprintf( stream, " |Currently Used Name: |{%s %s}.\n",
	  cip->current.first, cip->current.last );
    }
 if ( cip->opt1.include && (strlen(cip->opt1.first) || 
      	strlen(cip->opt1.middle) || strlen(cip->opt1.last)) ) {
    if ( strlen(cip->opt1.middle) )
       fprintf( stream, " |Optional Name 1: |{%s %s %s}.\n",
	  cip->opt1.first, cip->opt1.middle, cip->opt1.last );
    else
       fprintf( stream, " |Optional Name 1: |{%s %s}.\n",
	  cip->opt1.first, cip->opt1.last );
    }
 if ( cip->opt2.include && (strlen(cip->opt2.first) || 
      	strlen(cip->opt2.middle) || strlen(cip->opt2.last)) ) {
    if ( strlen(cip->opt2.middle) )
       fprintf( stream, " |Optional Name 2: |{%s %s %s}.\n",
	  cip->opt2.first, cip->opt2.middle, cip->opt2.last );
    else
       fprintf( stream, " |Optional Name 2: |{%s %s}.\n",
	  cip->opt2.first, cip->opt2.last );
    }
 if ( cip->birth_date.include && cip->birth_date.day && 
       	cip->birth_date.month && cip->birth_date.year )
    fprintf( stream, "|Birth Date: |{%s}.\n", make_date(&cip->birth_date) );

 fprintf( stream, "\n\n" );
}


