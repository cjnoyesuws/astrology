#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "namegraf.h"
#include "chartinf.h"
#include "name.h"
#include "numbr.h"
#include "lettrtyp.h"

short list[10];
short list_count;
DATES *birth;
TNUM *lif, *pin;

void add_list_item( short i )
{
 list[list_count] = i;
 list_count++;
}

void init_list()
{
 list_count = 0;
}

short universal_year( short year )
{
 short n;

 return( reduce_int( year, &n ) );
}

short personal_year( DATES *d, int year )
{
 short n;
 return( add_ints_reduce( year, d->month, d->day, &n ) );
}

void do_chars( NAMEGRF_ELE *e, char f, char m, char l )
{
 short n;

 f = toupper(f);
 m = toupper(m);
 l = toupper(l);

 if ( f != '*' ) {
    e->first.letter = f;
    e->first.val = letter_val( f ) - '0';
    e->middle.letter = m;
    e->middle.val = letter_val( m ) - '0';
    e->last.letter = l;
    e->last.val = letter_val( l ) - '0';
    e->essence.val = add_ints_reduce(e->first.val, e->middle.val, e->last.val, &n);
    }
 else  {
    e->first.letter = f;
    e->first.val = 0;
    e->middle.letter = m;
    e->middle.val = 0;
    e->last.letter = l;
    e->last.val = 0;
    e->essence.val = -1;
    }
}

void do_years( NAMEGRF_ELE *e, short i )
{
 e->age = i;
 e->year = birth->year + i;
 e->univ_year.val = universal_year( e->year );
 e->pers_year.val = personal_year( birth, e->year );
}

void do_cycles( NAMEGRF_ELE *e )
{
 short i;

 for ( i = 0; i < 3; i++ ) {
     if ( e->year >= lif[i].start && e->year < lif[i].end ) {
	e->life_cycle.val = lif[i].num;
	e->life_cycle.number = i;
	break;
	}
     }
 for ( i = 0; i < 4; i++ ) {
     if ( e->year >= pin[i].start && e->year < pin[i].end ) {
	e->pinacle.val = pin[i].num;
	break;
	}
     }
}

void check_mark(NG_NUM *n, short *list, short l)
{
 short i, *ip;

 n->mark = 0;
 for ( i = 0, ip = list; i < l; i++, ip++ ) {
     if ( n->val == *ip ) {
	n->mark = 1;
	break;
	}
     }
}


void do_check_marks( NAMEGRF_ELE *e )
{
  check_mark(&e->essence, list, list_count);
  check_mark(&e->pers_year, list, list_count);
  check_mark(&e->univ_year, list, list_count);
  check_mark(&e->pinacle, list, list_count);
  check_mark(&e->life_cycle, list, list_count);
}

short do_element( NAMEGRF_ELE *e, short i, char *let )
{
 if ( !i )
    do_chars( e, '*', '*', '*' );
 else
    do_chars( e, let[0], let[1], let[2] );
 do_years( e, i );
 do_cycles( e );
 do_check_marks( e );
 return( 1 );
}

void setup_elements( DATES *pb, TNUM *plif, TNUM *ppin )
{
 birth = pb;
 lif = plif;
 pin = ppin;
}

void do_name( NAMEGRF_ELE *ele, char *first, char *middle, char *last,
				     NUMBERS *bn, NAME_NUMBER *nn )
{
 int i, fc, mc, lc, ft=1, mt=1, lt=1;
 char *f, *m, *l, buf[5];
 static char blk[] = " ";
 NAMEGRF_ELE *e;

 init_list();
 if ( first == NULL || !strlen( first ) )
    first = blk;
 if ( middle == NULL || !strlen( middle ) )
    middle = blk;
 if ( last == NULL || !strlen( last ) )
    last = blk;
 if ( first == middle && first == last )
    return;
 init_list();
 add_list_item( bn->destiny.red );
 add_list_item( nn->motivation.total );
 add_list_item( nn->expression.total );
 add_list_item( nn->inner_self.total );
 f = first, m = middle, l = last;
 fc = mc = lc = 0;
 for ( e = ele, i = 0; i < 120; i++, e++, fc++, mc++, lc++ ) {
     if ( fc >= ft ) {
	fc = 0;
	f++;
	while (*f && !isalpha(*f))
	      f++;
	}
     if ( mc >= mt ) {
	mc = 0;
	m++;
	while (*m && !isalpha(*m))
	      m++;
	}
     if ( lc >= lt ) {
	lc = 0;
	l++;
	while (*l && !isalpha(*l))
	      l++;
	}
     if ( !*f )
	f = first;
     if ( !*l )
	l = last;
     if ( !*m )
	m = middle;
     if ( !fc )
	ft = letter_val(*f) - '0';
     if ( !mc )
	mt = letter_val(*m) - '0';
     if ( !lc )
	lt = letter_val(*l) - '0';
     buf[0] = toupper(*f);
     buf[1] = toupper(*m);
     buf[2] = toupper(*l);
     do_element( e, i, buf );
     if ( !i ) {
	fc--;
	mc--;
	lc--;
	}
     }
}

short do_all_names(NAMEGRF_GRP *n, CHART_INFO *c, NUMBERS *bn, NAME_NUMB_GROUP *nn )
{
 setup_elements( &c->birth_date, bn->life_cycles, bn->turn_point );
 if ( c->at_birth.include ) 
    do_name( n->at_birth, c->at_birth.first, c->at_birth.middle,
	   c->at_birth.last, bn, &nn->at_birth );
	n->at_birth->include = c->at_birth.include;
	   
 if ( c->current.include ) 
    do_name( n->current, c->current.first,
           c->current.middle, c->current.last, bn, &nn->current );
    n->current->include = c->current.include;          
 if ( c->opt1.include ) 
    do_name( n->option1, c->opt1.first, c->opt1.middle,
	   c->opt1.last, bn, &nn->option1 );
	n->option1->include = c->opt1.include;   
 if ( c->opt2.include )   
    do_name( n->option2, c->opt2.first,
  	  c->opt2.middle, c->opt2.last, bn, &nn->option2 );   
  	n->option2->include = c->opt2.include;  
 return( 1 );
}
