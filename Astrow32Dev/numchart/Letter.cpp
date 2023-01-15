#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "chartinf.h"
#include "namegraf.h"
#include "lettrtyp.h"
#include "name.h"
#include "errors.fns"

short wy_vowel;

void SetWYVowel( short s )
{
 wy_vowel = s;
}


short letter_type( char pre, char letter, char post )
{
 if ( !isalnum ( letter ) )
    return( NOTYPE );
 else if ( isdigit( letter ) )
    return( DIGIT );
 if ( strchr( VOWELS, letter ) != NULL )
    return( VOWEL );
 else if ( strchr( CONSONS, letter ) != NULL )
    return( CONSON );
 if ( letter == 'y' || letter == 'Y' ) {
    if ( !pre )
       return( YCONSO );
    if ( !wy_vowel )
       return( YCONSO );
    else if ( strchr( VOWELS, pre ) != NULL )
       return( YVOWEL );
    else if ( strchr( VOWELS, pre ) == NULL &&
	 post && strchr( VOWELS, post ) == NULL )
       return( YVOWEL );
    else if ( strchr( VOWELS, pre ) == NULL && !post )
       return( YVOWEL );
    else
       return( YCONSO );
    }
 else if ( letter == 'w' || letter == 'W' ) {
    if ( !pre )
       return( WCONSO );
    if ( !wy_vowel )
       return( WCONSO );
    else if ( strchr( VOWELS, pre ) != NULL )
       return( WVOWEL );
    else
       return( WCONSO );
    }
 else
    return( LTERR );
}

static char vals[] = { "123456789000000012345678912345678912345678000000123"
   "456789123456789123456780000033511113555999115666663376300000019635516\0\0\0" };

char letter_val( unsigned char c )
{
 if ( c < '1' )
    return( '0' );
 else if ( c > 167 )
    return( '0' );
 else if ( !vals[c-'1'] )
    return( '0' );
 else
    return( vals[c-'1'] );
}

short letter_val_str( char *str, char *buf, int maxlen )
{
 short i = 0;

 while ( *str ) {
       *buf++ = letter_val( *str++ );
       i++;
       if ( i > maxlen ) {
	  assert( i < maxlen );
	  break;
	  }
       }
 *buf = '\0';
 return( i++ );
}

short letter_type_val_str( char *str, char *buf, short type, short maxlen )
{
 short i = 0, ty;
 char *s = str;

 while ( *s ) {
       ty = letter_type( (s==str?0:*(s-1)), *s, (*(s+1)?*(s+1):0) );
       if ( type == ty ) {
	  *buf++ = letter_val( *s );
	  i++;
	  }
       if ( i > maxlen ) {
	  assert( i < maxlen );
	  break;
	  }
       s++;
       }
 *buf++ = '\0';
 return( i++ );
}

short add_buf( char *buf, short val )
{
 short v = val;
 char *b;

 for ( b = buf; *b; b++ )
     v += *b-'0';
 return( v );
}


short string_val( char *str, short red, short start_point, short *test )
{
 short n;
 char buf[125];

 if ( !strlen( str ) )
    return( start_point );
 assert( strlen( str ) < 123 );
 letter_val_str( str, buf, 123 );
 if ( red )
    return( reduce_num( buf, test ) );
 else
    return( add_buf( buf, start_point ) );
}

short string_type_val( char *str, short type, short red, short start_point, short *test )
{
 char buf[125];

 if ( !strlen( str ) )
    return( start_point );
 assert( strlen( str ) < 124 );
 letter_type_val_str( str, buf, type, 123);
 if ( red )
    return( reduce_num( buf, test ) );
 else
    return( add_buf( buf, start_point ) );
}

short str_add_reduc( char *str1, char *str2, char *str3, short *test )
{
 short p1, p2, p3, x;

 p1 = string_val( str1, 1, 0, &x );
 p2 = string_val( str2, 1, 0, &x );
 p3 = string_val( str3, 1, 0, &x );
 return( add_ints_reduce(p1, p2, p3, test) );
}

short str_add_reduc_type( char *str1, char *str2, char *str3, short type, short *test )
{
 short p1, p2, p3, x;

 p1 = string_type_val( str1, type, 1, 0, &x );
 p2 = string_type_val( str2, type, 1, 0, &x );
 p3 = string_type_val( str3, type, 1, 0, &x );
 return( add_ints_reduce(p1, p2, p3, test) );
}

void clear_inclusion_table( INCL_TABLE *t )
{
 memset( t, 0, sizeof( INCL_TABLE ) );
}

void calc_express_planes( char *name, NAME_EXPR_PLANES *pl )
{
 char *n;

 for ( n = name; *n; n++ ) {
     switch( toupper(*n) ) {
	   case 'A' :
		++pl->inspired;
		++pl->mental;
		break;
	   case 'B' :
		++pl->dual;
		++pl->emotional;
		break;
	   case 'C' :
		++pl->balanced;
		++pl->intuitive;
		break;
	   case 'D' :
		++pl->balanced;
		++pl->physical;
		break;
	   case 'E' :
		++pl->inspired;
		++pl->physical;
		break;
	   case 'F' :
		++pl->dual;
		++pl->intuitive;
		break;
	   case 'G' :
		++pl->balanced;
		++pl->mental;
		break;
	   case 'H' :
		++pl->dual;
		++pl->mental;
		break;
	   case 'I' :
		++pl->inspired;
		++pl->emotional;
		break;
	   case 'J' :
		++pl->dual;
		++pl->mental;
		break;
	   case 'K' :
		++pl->inspired;
		++pl->intuitive;
		break;
	   case 'L' :
		++pl->balanced;
		++pl->mental;
		break;
	   case 'M' :
		++pl->balanced;
		++pl->physical;
		break;
	   case 'N' :
		++pl->dual;
		++pl->mental;
		break;
	   case 'O' :
		++pl->inspired;
		++pl->emotional;
		break;
	   case 'P' :
		++pl->dual;
		++pl->mental;
		break;
	   case 'Q' :
		++pl->dual;
		++pl->intuitive;
		break;
	   case 'R' :
		++pl->inspired;
		++pl->emotional;
		break;
	   case 'S' :
		++pl->dual;
		++pl->emotional;
		break;
	   case 'T' :
		++pl->dual;
		++pl->emotional;
		break;
	   case 'U' :
		++pl->dual;
		++pl->intuitive;
		break;
	   case 'V' :
		++pl->balanced;
		++pl->intuitive;
		break;
	   case 'W' :
		++pl->dual;
		++pl->physical;
		break;
	   case 'X' :
		++pl->dual;
		++pl->emotional;
		break;
	   case 'Y' :
		++pl->dual;
		++pl->intuitive;
		break;
	   case 'Z' :
		++pl->inspired;
		++pl->emotional;
		break;
	   default:
	       break;

	   }
     }
}

void do_expression_planes( char *first, char *middle, char *last, NAME_EXPR_PLANES *pl )
{
 pl->mental = 0;
 pl->intuitive = 0;
 pl->physical = 0;
 pl->emotional = 0;
 pl->inspired = 0;
 pl->dual = 0;
 pl->balanced = 0;
 calc_express_planes( first, pl );
 calc_express_planes( middle, pl );
 calc_express_planes( last, pl );
}

void calc_traits( char *str, short *aray )
{
 char buf[75];
 char *s;

 letter_val_str( str, buf, 74 );
 for ( s = buf; *s; s++ )
     aray[*s-'1']++;
}

void do_traits( char *first, char *middle, char *last, short *array )
{
 memset( array, 0, 18 );
 calc_traits( first, array );
 calc_traits( middle, array );
 calc_traits( last, array );
}

void calc_element_num( short n, NAME_ELEMENTS *e)
{
 switch( n ) {
       case 1:
       case '1':
       case 3:
       case '3':
       case 9:
       case '9':
	    ++e->fire;
	    break;
       case 2:
       case '2':
       case 7:
       case '7':
       case 22:
	    ++e->water;
	    break;
       case 4:
       case '4':
       case 8:
       case '8':
	    ++e->earth;
	    break;
       case 5:
       case '5':
       case 11:
	    ++e->air;
	    break;
       case 6:
       case '6':
	    ++e->earth;
	    ++e->air;
	    break;
       default :
	    break;
       }
}

void calc_element_string( char *str, NAME_ELEMENTS *e)
{
 char buf[75], *b;

 letter_val_str( str, buf, 74 );
 for ( b = buf; *b; b++ )
     calc_element_num(*b, e);
}


void do_elements( char *first, char *middle, char *last, NAME_ELEMENTS *e, int ex, int is, int mo )
{
 e->earth = 0;
 e->air = 0;
 e->fire = 0;
 e->water = 0;
 calc_element_num( is, e );
 calc_element_num( ex, e );
 calc_element_num( mo, e );
 calc_element_string( first, e);
 calc_element_string( middle, e);
 calc_element_string( last, e);
}


void make_inclusion_table( char *str, INCL_TABLE *t )
{
 short *tbl = t->table;
 char buf[125];
 char *s;

 assert( strlen( str ) < 123 );
 letter_val_str( str, buf, 123 );
 s = buf;
 while ( *s ) {
       tbl[*s-'0']++;
       s++;
       }
}

void make_type_inclusion_table( char *str, INCL_TABLE *t, short type )
{
 short *tbl = t->table;
 char buf[125];
 char *s;

 assert( strlen( str ) < 123 );
 letter_type_val_str( str, buf, 123, type );
 s = buf;
 while ( *s ) {
       tbl[*s-'0']++;
       s++;
       }
}

void process_inclusion_table( INCL_TABLE *t )
{
 short *ip = &t->table[1], num = 0, count = 999, i, nx, k;

 for ( i = 1, k = 0; i < 10; i++ ) {
     if ( !t->table[i] ) {
	t->karm_lesn[k] = i;
	k++;
	}
     }
 t->karm_count = k;
}

void do_name_number( char *first, char *middle, char *last, NAME_NUMBER *n )
{
 short t;
 if ( !strcmpi( first, "" ) && !strcmpi( middle, "" ) &&
	!strcmpi( last, "" ) ) {
    return;
    }
 do_traits( first, middle, last, n->traits );
 n->expression.total = str_add_reduc( first, middle, last,
     &n->expression.test );
 n->expression.first = str_add_reduc( first, "", "", &t );
 n->expression.middle = str_add_reduc( "", middle, "", &t );
 n->expression.last = str_add_reduc( "", "", last, &t );
 clear_inclusion_table( &n->inclusion_tbl );
 make_inclusion_table( first, &n->inclusion_tbl );
 make_inclusion_table( middle, &n->inclusion_tbl );
 make_inclusion_table( last, &n->inclusion_tbl );
 process_inclusion_table( &n->inclusion_tbl );
 n->inner_self.total = str_add_reduc_type( first, middle, last,
     VOWEL, &n->inner_self.test  );
 n->inner_self.first = str_add_reduc_type( first, "", "", VOWEL, &t );
 n->inner_self.middle = str_add_reduc_type( "", middle, "", VOWEL, &t );
 n->inner_self.last = str_add_reduc_type( "", "", last, VOWEL, &t );
 n->motivation.total = str_add_reduc_type( first, middle, last,
     CONSON, &n->motivation.test );
 n->motivation.first = str_add_reduc_type( first, "", "", CONSON, &t );
 n->motivation.middle = str_add_reduc_type( "", middle, "", CONSON, &t );
 n->motivation.last = str_add_reduc_type( "", "", last, CONSON, &t );
 do_expression_planes( first, middle, last, &n->expression_planes );
 do_elements( first, middle, last, &n->elements, n->expression.total,
      n->inner_self.total, n->motivation.total );
}


short street_val( char *stradr )
{
 short flag = 0, test;
 char buf[25], *s = stradr, *bp = buf;

 if ( !strcmpi( stradr, "" ) )
    return( 0 );
 while ( *s ) {
       if ( !isdigit( *s ) )
	  s++;
       else
	  flag = 1;
       if ( flag && isdigit( *s ) )
	  *bp++ = *s;
       if ( flag && !isdigit( *s ) )
	  break;
       s++;
       }
 *bp++ = '\0';
 return( reduce_num( buf, &test ) );
}

void do_all_name_numbers( CHART_INFO *cip, NAME_NUMB_GROUP *n )
{
 
 if ( cip->at_birth.include ) {
    do_name_number( cip->at_birth.first, cip->at_birth.middle, 
	cip->at_birth.last, &n->at_birth );
    n->at_birth.include = 1;
    }	
 else
    n->at_birth.include = 0;
 if ( cip->current.include ) {
    do_name_number( cip->current.first, cip->current.middle, 
	cip->current.last, &n->current );
    n->current.include = 1;
    }
 else
    n->current.include = 0;
 if ( cip->opt1.include ) {
    do_name_number( cip->opt1.first, cip->opt1.middle, 
	cip->opt1.last, &n->option1 );
    n->option1.include = 1;
    }
 else
    n->option1.include = 0;
 if ( cip->opt2.include ) {
    do_name_number( cip->opt2.first, cip->opt2.middle, 
	cip->opt2.last, &n->option2 );
    n->option2.include = 1;
    }
 else
    n->option2.include = 0;

}

