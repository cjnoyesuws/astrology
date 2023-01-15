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
#include "output.fns"

extern int do_demo_mode(FILE *stream);

extern short get_gnt( short col, short file_num, FILE *stream );

static short check_test( FILE *stream, short test )
{
 if ( !test )
    return( 0 );
 fprintf( stream, "{Warning!} Test Number {%d} Detected,"
	    " May indicate Difficulty.\x80", test );
 return( 1 );
}

short pers_print_name( FILE *stream, char *head, NAME_NUMBER *np, NAME_REC *nmp, int file )
{
 short i;

 if ( !nmp->include )
    return( 0 );
 if ( strlen( nmp->first ) || strlen( nmp->middle ) ||
      strlen( nmp->last ) ) {
    fprintf( stream, head );
    fprintf( stream, "\nExpression Number <(How You Express Yourself)>: "
	 "{%d}.\x80", np->expression.total );
    check_test( stream, np->expression.test);
    get_gnt( EXPRESS, file, stream );
    get_text( EXPRESS, np->expression.total, file, stream );
    fprintf( stream, "\nMotivation Number <(What You are Motivated To)>:"
	 " {%d}.\x80", np->motivation.total );
    check_test( stream, np->motivation.test);
    get_gnt( MOTIV, file, stream );
    get_text( MOTIV, np->motivation.total, file, stream );
    fprintf( stream, "\nInner Self Number, or Soul Urge <(What You Dream of)>: "
	 "{%d}.\x80", np->inner_self.total );
    check_test( stream, np->inner_self.test);
    get_gnt( INNER_SELF, file, stream );
    get_text( INNER_SELF, np->inner_self.total, file, stream );
    fprintf( stream, "\nKarmic Lesson Number <(Experiences You Have Missed)>:"
	 " {%d}.\x80", np->inclusion_tbl.karm_lesn[0] );
    if ( np->inclusion_tbl.karm_count
		&& np->inclusion_tbl.karm_lesn[0] ) {
       get_gnt( KARMIC_LESN, file, stream );
       get_text( KARMIC_LESN, np->inclusion_tbl.karm_lesn[0], file, stream );
       if ( np->inclusion_tbl.karm_count > 1 ) {
	  for ( i = 1; i < np->inclusion_tbl.karm_count; i++ ) {
	      fprintf( stream, "\nKarmic Lesson Number %d: {%d}.\x80",
		   i+1, np->inclusion_tbl.karm_lesn[i] );
	      get_text( KARMIC_LESN, np->inclusion_tbl.karm_lesn[i],
		 file, stream );
	      }
	  }
       }
    
    
    fprintf( stream, "^@|60|4|4|19|34|49|" );
    fprintf( stream, "\n{Your Planes Of Expression--}\x80|Physical: {%d},|Emotional: {%d},|"
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
    fprintf( stream, "\n{Your Traits--}\x80|#1: {%d},|#2: {%d},|#3: {%d},|#4: {%d},|#5:"
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
 else
    return( 0 );
}


static char *signs[] = { "Aries", "Taurus", "Gemini", "Cancer", "Leo",
     "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius",
     "Pisces", "ERROR!" };

short full_personality_report_print( FILE *stream, CHART_INFO *cip,
		    NUMBERS *np, NAME_NUMB_GROUP *nngp, short head )
{
 short file, i;

 file = open_files( TEXT_FILE_NAME );
 fprintf( stream, "[PERSONALITY REPORT:]\n" );
 do_demo_mode(stream);
 if ( head )
    chart_header_print( stream, cip );
 
 if (cip->birth_date.include) {
    fprintf( stream,  "\n[NUMBERS DERIVED FROM YOUR BIRTH DATE:]\x80" );
    fprintf( stream, "\nDestiny Number or Birth Path <(Where You're Headed)>:"
       " {%d}.\x80", np->destiny.red );
    check_test( stream, np->destiny.test);
    get_gnt( DESTINY, file, stream );
    get_text( DESTINY, np->destiny.red, file, stream );
    fprintf( stream, "\nYour Sun Sign is <(Your Outer Personality)>: "
       "{%s}.\x80", signs[ np->sign.raw ] );
    get_gnt( SUN_SIGN, file, stream );
    get_transfer_text( np->sign.raw, SUN_SIGN, file, stream );
    fprintf( stream, "\n{Your Challenges} "
       "<(Areas Where You need to Learn to Grow)>:\x80" );
    get_gnt( CHALLENGE, file, stream );
    fprintf( stream, "\nYour First Minor Challenge is: "
       "{%d}.\x80", np->challenges[CHALMIN1] );
    get_text( CHALLENGE, np->challenges[CHALMIN1], file, stream );
    fprintf( stream, "\nYour Second Minor Challenge is: "
       "{%d}.\x80", np->challenges[CHALMIN2] );
    get_text( CHALLENGE, np->challenges[CHALMIN2], file, stream );
    fprintf( stream, "\nYour Major Challenge is: "
       "{%d}.\x80", np->challenges[CHALMAJR] );
    get_text( CHALLENGE, np->challenges[CHALMAJR], file, stream );

    fprintf( stream, "\n{Your Life Cycles:} <(Critical Periods in"
	  " your Life, which will Effect You)>.\x80" );
    get_gnt( LIFE_CYCLE_1, file, stream );
    fprintf( stream, "\nYour First Life Cycle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80",
      np->life_cycles[0].num, np->life_cycles[0].start, np->life_cycles[0].end );
    get_text( LIFE_CYCLE_1, np->life_cycles[0].num, file, stream );
    fprintf( stream, "\nYour Second Life Cycle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80",
      np->life_cycles[1].num, np->life_cycles[1].start, np->life_cycles[1].end );
    get_text( LIFE_CYCLE_2, np->life_cycles[1].num, file, stream );
    fprintf( stream, "\nYour Third Life Cycle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80",
      np->life_cycles[2].num, np->life_cycles[2].start, np->life_cycles[2].end );
    get_text( LIFE_CYCLE_3, np->life_cycles[2].num, file, stream );

    fprintf( stream, "\n{Your Pinnacles (or Turning Points):} <(Critical Periods in your"
      " Life, which will Effect You. The start of the second Pinnacle"
      " will start at the same time the Second Life Cycle Starts)>.\x80" );
    get_gnt( TURN_POINT, file, stream );
    fprintf( stream, "\nYour First Pinnacle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80",
      np->turn_point[0].num, np->turn_point[0].start, np->turn_point[0].end );
    get_text( TURN_POINT, np->turn_point[0].num, file, stream );
    fprintf( stream, "\nYour Second Pinnacle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80",
      np->turn_point[1].num, np->turn_point[1].start, np->turn_point[1].end );
    get_text( TURN_POINT, np->turn_point[1].num, file, stream );
    fprintf( stream, "\nYour Third Pinnacle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80",
      np->turn_point[2].num, np->turn_point[2].start, np->turn_point[2].end );
    get_text( TURN_POINT, np->turn_point[2].num, file, stream );
    fprintf( stream, "\nYour Fourth Pinnacle Number is {%d} "
      "and it lasts from {%d} to {%d}.\x80", np->turn_point[3].num, np->turn_point[3].start, np->turn_point[3].end );
    get_text( TURN_POINT, np->turn_point[3].num, file, stream );

    fprintf( stream, "\n{Your Personal Year and Month:} <(These"
       " Indicate how these Periods Affect You Personally)>. \x80" );
    fprintf( stream, "\nYour Personal Year Number is {%d}.\x80",
       np->personal.year );
    get_text( PERS_YEAR, np->personal.year, file, stream );

    fprintf( stream, "\nYour Personal Month Number is {%d}.\x80",
      np->personal.month );
    get_text( PERS_MONTH, np->personal.month, file, stream );
    /*
    fprintf( stream, "\nYour Personal Day Number is {%d}.\x80",
      np->personal.day );
    get_text( PERS_DAY, np->personal.day, file, stream );
    */

    fprintf( stream, "\n{Your Universal Year and Month:} <(These"
       " Indicate How these Periods affect The Whole World)>. \x80" );
    fprintf( stream, "\nYour Universal Year Number is {%d}.\x80",
       np->universal.year );
    get_text( UNIV_YEAR, np->universal.year, file, stream );
    fprintf( stream, "\nYour Universal Month Number is {%d}.\x80",
       np->universal.month );
    get_text( UNIV_MONTH, np->universal.month, file, stream );
    /*
    fprintf( stream, "\nYour Universal Day Number is {%d}.\x80",
      np->universal.day );
    get_text( UNIV_DAY, np->universal.day, file, stream );
    */
    }
 pers_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR NAME AT BIRTH:]\x80",
     &nngp->at_birth, &cip->at_birth, file );
 pers_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR CURRENT NAME:]\x80",
     &nngp->current, &cip->current, file );
 pers_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR FIRST OPTIONAL NAME:]\x80",
     &nngp->option1, &cip->opt1, file );
 pers_print_name( stream, "\n[NUMBERS DERIVED FROM YOUR SECOND OPTIONAL NAME:]\x80",
     &nngp->option2, &cip->opt2, file );
 fprintf( stream, "\n" );
 close_files( file );
 return( 1 );
}



