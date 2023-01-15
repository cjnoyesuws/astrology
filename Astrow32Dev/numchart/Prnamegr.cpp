
#include <stdio.h>
#include <string.h>
#include "chartinf.h"
#include "namegraf.h"
#include "textptr.h"
#include "textsym.h"
#include "output.fns"

extern int do_demo_mode(FILE *stream);

short prev_ess, prev_pinn, prev_life;

char *mark_str( NG_NUM *n )
{
 static char buf[10];
 if ( n->val == -1 )
    return( "{BIRTH}" );
 if ( !n->mark )
    sprintf( buf, "{%d}", n->val );
 else
    sprintf( buf, "{(%d)}", n->val );
 return( buf );
}


short print_name_graf_ele( FILE *stream, NAMEGRF_ELE *e, short text )
{
 char buf[10];

 if ( !e->age )
    strcpy( buf, "BIRTH" );
 else
    sprintf( buf, "%d", e->age );
 fprintf( stream, "\n[THE YEAR %04d - %04d--AGE: %s.]\x80\x80", e->year,
     e->year+1, buf );
 fprintf( stream, "{Current Letters--}\nFirst: %c, Value: %d;|"
    "Middle: %c, Value: %d;|Last: %c, Value: %d.\n\n", e->first.letter,
    e->first.val, e->middle.letter, e->middle.val, e->last.letter,
    e->last.val );
 if ( e->first.letter == '*' )
    fprintf( stream, "Birth Year, No Letters Apply.\n" );
 fprintf( stream, "This Year's Essence is %s\x80", mark_str(&e->essence) );
 if ( text != -1 ) {
    if ( e->essence.val == prev_ess && e->essence.val != -1  ) {
       fprintf( stream, "<See Prev.>\n" );
       }
    else
       get_text( ESSENCE, e->essence.val, text, stream );
    prev_ess = e->essence.val;
    }
 fputc( '\n', stream );

 fprintf( stream, "This Year's Personal Year is %s.\x80",
	mark_str(&e->pers_year) );
 if ( text != -1 )
    get_text( PERS_YEAR, e->pers_year.val, text, stream );
 fputc( '\n', stream );

 fprintf( stream, "This Year's Universal year is %s.\x80",
	mark_str(&e->univ_year) );
 if ( text != -1 )
    get_text( UNIV_YEAR, e->univ_year.val, text, stream );
 fputc( '\n', stream );

 fprintf( stream, "The Pinnacle or Turning Point in Effect is %s.\x80",
	mark_str(&e->pinacle) );
 if ( text != -1 ) {
    if ( e->pinacle.val == prev_pinn ) {
       fprintf( stream, "<See Prev.>\n" );
       }
    else
       get_text( TURN_POINT, e->pinacle.val, text, stream );
    prev_pinn = e->pinacle.val;
    }
 fputc( '\n', stream );
 fprintf( stream, "The Life Cycle in Effect is %s.\x80",
	mark_str(&e->life_cycle) );
 if ( text != -1 ) {
    if ( e->life_cycle.val == prev_life ) {
       fprintf( stream, "<See Prev.>\n" );
       }
    else
       get_text( LIFE_CYCLE_1+e->life_cycle.number,
	     e->life_cycle.val, text, stream );
    prev_life = e->life_cycle.val;
    }
 fputc( '\n', stream );
 fputc( '\n', stream );
 return( ferror( stream ) );
}


void print_name_grafs( FILE *stream, CHART_INFO *cip, NAMEGRF_GRP *g, short head, short start, short end)
{
 short file, i;
 NAMEGRF_ELE *elem;

 file = open_files( TEXT_FILE_NAME );
 fprintf( stream, "\n[NAME TRANSITS ANALYSIS REPORT:]\n\n" );
 settitle( "Name Transits Analysis Report" );
 do_demo_mode(stream);
 if ( head )
    chart_header_print( stream, cip );
 fprintf( stream, "For Years: {%4d - %4d}\n\n", start, end );
 fprintf( stream, "^@|60|2|22|44|" );
 start -= cip->birth_date.year;
 end -= cip->birth_date.year;
 if ( g->at_birth->include ) {
    prev_ess = prev_pinn = prev_life = -1;
    fprintf( stream, "\n[BASED ON NAME AT BIRTH:]\n\n" );
    prev_ess = prev_pinn = prev_life = -1;
    for ( i = start, elem = &g->at_birth[start]; i < end; i++, elem++ )
        print_name_graf_ele( stream, elem, file );
    }    
 if ( g->current->include ) {
    prev_ess = prev_pinn = prev_life = -1;   
    fprintf( stream, "\n[BASED ON CURRENTLY USED NAME:]\n\n" );
    for ( i = start, elem = &g->current[start]; i < end; i++, elem++ )
        print_name_graf_ele( stream, elem, file );
    }
 if ( g->option1->include ) {
    prev_ess = prev_pinn = prev_life = -1;
    fprintf( stream, "\n[BASED ON FIRST OPTIONAL NAME:]\n\n" );
    for ( i = start, elem = &g->option1[start]; i < end; i++, elem++ )
        print_name_graf_ele( stream, elem, file );
    }
 if ( g->option2->include ) {
    prev_ess = prev_pinn = prev_life = -1;   
    fprintf( stream, "\n[BASED ON SECOND OPTIONAL NAME:]\n\n" );
    for ( i = start, elem = &g->option2[start]; i < end; i++, elem++ )
        print_name_graf_ele( stream, elem, file );
    }
 fprintf( stream, "\n\n" );
 close_files( file );
}

