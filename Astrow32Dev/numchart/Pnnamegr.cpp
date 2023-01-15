#include <stdio.h>
#include <string.h>
#include "chartinf.h"
#include "namegraf.h"
#include "textptr.h"
#include "textsym.h"

extern int do_demo_mode(FILE *stream);

static char *mark_str( NG_NUM *n )
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


short print_name_graf_ele_num( FILE *stream, NAMEGRF_ELE *e )
{
 char buf[10];

 if ( !e->age )
    strcpy( buf, "BIRTH" );
 else
    sprintf( buf, "%d", e->age );
 fprintf( stream, "\n[THE YEAR %04d - %04d--AGE: %s.]\x80\x80", e->year,
     e->year+1, buf );

 fprintf( stream, "{Current Letters--}\nFirst: %c, Value: %d;|"
    "Middle: %c, Value: %d;|Last: %c, Value: %d.\n", e->first.letter,
    e->first.val, e->middle.letter, e->middle.val, e->last.letter,
    e->last.val );
 if ( e->first.letter == '*' )
    fprintf( stream, "Birth Year, No Letters Apply.\n" );
 fprintf( stream, "Essence %s|", mark_str(&e->essence) );
 fprintf( stream, "Personal Year %s|", mark_str(&e->pers_year) );
 fprintf( stream, "Universal Year %s.\n", mark_str(&e->univ_year) );
 fprintf( stream, "Pinnacle %s|", mark_str(&e->pinacle) );
 fprintf( stream, "Life Cycle %s.\n\n", mark_str(&e->life_cycle) );
 return( ferror( stream ) );
}


void print_name_grafs_num( FILE *stream, CHART_INFO *cip, NAMEGRF_GRP *g, short head, short start, short end)
{
 short i;
 NAMEGRF_ELE *elem;

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
    fprintf( stream, "\n[BASED ON NAME AT BIRTH:]\n\n" );
    for ( i = start, elem = &g->at_birth[start]; i < end; i++, elem++ )
        print_name_graf_ele_num( stream, elem );
    }   
 if ( g->current->include ) {
    fprintf( stream, "\n[BASED ON CURRENTLY USED NAME:]\n\n" );
    for ( i = start, elem = &g->current[start]; i < end; i++, elem++ )
        print_name_graf_ele_num( stream, elem );
    }
 if ( g->option1->include ) {
    fprintf( stream, "\n[BASED ON FIRST OPTIONAL NAME:]\n\n" );
    for ( i = start, elem = &g->option1[start]; i < end; i++, elem++ )
        print_name_graf_ele_num( stream, elem );
    }
 if ( g->option2->include ) {
    fprintf( stream, "\n[BASED ON SECOND OPTIONAL NAME:]\n\n" );
    for ( i = start, elem = &g->option2[start]; i < end; i++, elem++ )
        print_name_graf_ele_num( stream, elem );
    }
 fprintf( stream, "\n\n" );
}

