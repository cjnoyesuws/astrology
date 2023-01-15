
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chartinf.h"
#include "name.h"
#include "numbr.h"
#include "textptr.h"
#include "textsym.h"


extern int do_demo_mode(FILE *stream);

static int check_test( FILE *stream, short test )
{
 if ( !test )
    return( 0 );
 fprintf( stream, "{Warning!} Test Number {%d} Detected,"
	    " May indicate Difficulty.\n", test );
 return( 1 );
}


short num_print_name( FILE *stream, char *head, NAME_NUMBER *np, NAME_REC *nmp )
{
 if ( !nmp->include )
    return( 0 );
 if ( strlen( nmp->first ) || strlen( nmp->middle ) ||
      strlen( nmp->last ) ) {
    fprintf( stream, head );
    fprintf( stream, "\n^@|60|2|26|29|Expression Number--"
	 "Total: |{%d}|(First: %d + Middle: %d + Last: %d).\n",
	 np->expression.total, np->expression.first,
	 np->expression.middle, np->expression.last);
    check_test( stream, np->expression.test);
    fprintf( stream, "\nMotivation Number--"
	 "Total: |{%d}|(First: %d + Middle: %d + Last: %d).\n",
	 np->motivation.total, np->motivation.first,
	 np->motivation.middle, np->motivation.last);
    check_test( stream, np->motivation.test);
    fprintf( stream, "\nInner Self Number--"
	 "Total: |{%d}|(First: %d + Middle: %d + Last: %d).\n",
	 np->inner_self.total, np->inner_self.first,
	 np->inner_self.middle, np->inner_self.last);
    check_test( stream, np->inner_self.test);
    fprintf( stream, "\n^@|60|1|28|Karmic Lesson Number:"
	 "|{%d}.\n", np->inclusion_tbl.karm_lesn[0] );
    if ( np->inclusion_tbl.karm_lesn[1] != 0 ) {
       fprintf( stream, "Second Karmic Lesson Number:|{%d}.\n",
	  np->inclusion_tbl.karm_lesn[1] );
       }
    
   	fprintf( stream, "^@|60|4|4|19|34|49|" );
    fprintf( stream, "\n{Planes Of Expression--}\x80|Physical: {%d},|Emotional: {%d},|"
	"Mental: {%d},|Intuitive: {%d},\x80|Inspired: {%d},|Dual: {%d},|"
	"Balanced: {%d}.\n",
	   np->expression_planes.physical,
	   np->expression_planes.emotional,
	   np->expression_planes.mental,
	   np->expression_planes.intuitive,
	   np->expression_planes.inspired,
	   np->expression_planes.dual,
	   np->expression_planes.balanced);
    fprintf( stream, "^@|60|6|4|13|22|31|40|49|" );
    fprintf( stream, "\n{Traits--}\x80|#1: {%d},|#2: {%d},|#3: {%d},|#4: {%d},|#5:"
	" {%d},|#6: {%d},\x80|#7: {%d},|#8: {%d},|#9: {%d}.\n",
	   np->traits[0], np->traits[1],
	   np->traits[2], np->traits[3],
	   np->traits[4], np->traits[5],
	   np->traits[6], np->traits[7],
	   np->traits[8] );
    fprintf( stream, "^@|60|4|4|19|34|49|" );
    fprintf( stream, "\n{Elements--}\x80|Fire: {%d},|Earth: {%d},|Water:"
	" {%d},|Air: {%d}.\n", np->elements.fire,
	   np->elements.earth, np->elements.water,
	   np->elements.air );
    return( 1 );
    }
 return( 0 );
}


static char *signs[] = { "Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo",
     "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces", "ERROR!" };


short num_report_print( FILE *stream, CHART_INFO *cip,
		    NUMBERS *np, NAME_NUMB_GROUP *nngp, short head )
{
 fprintf( stream, "[NUMEROLOGY REPORT:]\n" );
 do_demo_mode(stream);
 if ( head )
    chart_header_print( stream, cip );
 if (cip->birth_date.include) {
    if (cip->birth_date.day || cip->birth_date.month || cip->birth_date.year) {
       fprintf( stream,  "\n[NUMBERS DERIVED FROM YOUR BIRTH DATE:]\x80" );
       fprintf( stream, "\nDestiny Number or Birth Path:"
          " {%d}.\x80", np->destiny.red );
       check_test( stream, np->destiny.test);
       fprintf( stream, "\nSun Sign: "
          "{%s}.\x80", signs[ np->sign.raw ] );
       fprintf( stream, "\n^@|60|1|24|{Your Challenges}:\x80" );
       fprintf( stream, "First Minor Challenge: |{%d}.\x80",
	   np->challenges[CHALMIN1] );
       fprintf( stream, "Second Minor Challenge: |{%d}.\x80",
	   np->challenges[CHALMIN2] );
       fprintf( stream, "Major Challenge: |{%d}.\n",
	   np->challenges[CHALMAJR] );
       fprintf( stream, "\n^@|60|2|18|22|{Your Life Cycles:}\x80" );
       fprintf( stream, "First Life Cycle |{%d}|in effect {%d} - {%d}.\x80",
         np->life_cycles[0].num, np->life_cycles[0].start,
         np->life_cycles[0].end );
       fprintf( stream, "Second Life Cycle |{%d}|in effect {%d} - {%d}.\x80",
         np->life_cycles[1].num, np->life_cycles[1].start,
         np->life_cycles[1].end );
       fprintf( stream, "Third Life Cycle |{%d}|in effect {%d} - {%d}.\n",
         np->life_cycles[2].num, np->life_cycles[2].start,
         np->life_cycles[2].end );

       fprintf( stream, "\n^@|60|2|23|29|{Your Pinnacles:}\x80" );
       fprintf( stream, "First Pinnacle Number |{%d}|in effect {%d} - {%d}.\x80",
         np->turn_point[0].num, np->turn_point[0].start, np->turn_point[0].end );
       fprintf( stream, "Second Pinnacle Number |{%d}|in effect {%d} - {%d}.\x80",
         np->turn_point[1].num, np->turn_point[1].start, np->turn_point[1].end );
       fprintf( stream, "Third Pinnacle Number |{%d}|in effect {%d} - {%d}.\x80",
         np->turn_point[2].num, np->turn_point[2].start, np->turn_point[2].end );
       fprintf( stream, "Fourth Pinnacle Number |{%d}|in effect {%d} - {%d}.\n",
         np->turn_point[3].num, np->turn_point[3].start, np->turn_point[3].end );

       fprintf( stream, "\n{Your Personal Year and Month:}\x80" );
       fprintf( stream, "Year Number: {%d}, ", np->personal.year );
       fprintf( stream, "Month Number: {%d}.\n", np->personal.month );

       fprintf( stream, "\n{Universal Year and Month:}\x80" );
       fprintf( stream, "Year Number: {%d}, ", np->universal.year );
       fprintf( stream, "Month Number: {%d}.\n", np->universal.month );
       }
    }
 num_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR NAME AT BIRTH:]\x80",
     &nngp->at_birth, &cip->at_birth );
 num_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR CURRENT NAME:]\x80",
     &nngp->current, &cip->current );
 num_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR FIRST OPTIONAL NAME:]\x80",
     &nngp->option1, &cip->opt1 );
 num_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR SECOND OPTIONAL NAME:]\x80",
     &nngp->option2, &cip->opt2 );
 fprintf( stream, "\n" );
 return( 1 );
}



