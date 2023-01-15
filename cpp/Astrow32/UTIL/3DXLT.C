#include <stdio.h>
#include <string.h>
#include <search.h>


typedef struct CTL_LIST {
	char name[20];
	int (*pfn)(FILE *in, FILE *out, char *key, char *data);
	};

#define LIST_CNT 13

CTL_LIST main_list[LIST_CNT] = {
    "LTEXT", text,
    "RTEXT", text,
    "CTEXT", text,
    "COMBOBOX", combo,
    "EDITTEXT", edit,
    "PUSHBUTTON",  push,
    "DEFPUSHBUTTON", push,
    "CONTROL", control,
    "GROUPBOX", group,
    "LISTBOX",  list,
    "RADIOBUTTON", radio,
    "ICON", icon,
    "CHECKBOX", check
    };

int list_count = LIST_CNT;


#define SUB_LIST_CNT 6

CTL_LIST sub_list[SUB_LIST_CNT] = {
     "BUTTON", button_sub,
     "COMBOBOX", combo_sub,
     "EDIT", edit_sub,
     "LISTBOX", listbox_sub,
     "SCROLLBAR", scroll_sub,
     "STATIC", static_sub };

int sub_list_count = SUB_LIST_CNT;



int text(FILE *in, FILE *out, char *key, char *data)
{
}

int combo(FILE *in, FILE *out, char *key, char *data)
{
}

int edit(FILE *in, FILE *out, char *key, char *data)
{
}

int push(FILE *in, FILE *out, char *key, char *data)
{
}

int control(FILE *in, FILE *out, char *key, char *data)
{
 static char buf[120];
 char text[250], class[20];
 int x;

 if ( fgets(buf, 119, in) == NULL )
    return( 0 );
 sscanf( buf, "%249[^,], %d, %19[^,]", text, &x, class );
 if ( ( x = search_list(in, out, class, sub_list,
	   sub_list_count, buf) ) == -1 )
    fprintf( out, "CONTROL %s\n", buf );
 else
    return( x );
}

int group(FILE *in, FILE *out, char *key, char *data)
{
}

int list(FILE *in, FILE *out, char *key, char *data)
{
}

int radio(FILE *in, FILE *out, char *key, char *data)
{
}

int group(FILE *in, FILE *out, char *key, char *data)
{
}

int icon(FILE *in, FILE *out, char *key, char *data)
{
}

int check(FILE *in, FILE *out, char *key, char *data)
{
}


int button_sub(FILE *in, FILE *out, char *key, char *data)
{
}

int combo_sub(FILE *in, FILE *out, char *key, char *data)
{
}

int edit_sub(FILE *in, FILE *out, char *key, char *data)
{
}

int listbox_sub(FILE *in, FILE *out, char *key, char *data)
{
}

int scroll_sub(FILE *in, FILE *out, char *key, char *data)
{
}

int static_sub(FILE *in, FILE *out, char *key, char *data)
{
}


int search_list( FILE *in, FILE *out, char *key, CTL_LIST *list, int num, char *data )
{
 CTL_LIST *fnd;

 fnd = (CTL_LIST *)lfind( key, list, &num, sizeof(CTL_LIST), strcmpi )
 if ( fnd == NULL )
    return( -1 );
 else
    return( fnd->pfn(in, out, key, data ) );
}


void main( int argc, char *argv[] )
{
 char buf[50];
 FILE *in, *out;
 int ic;

 in = fopen( argv[1], "rt" );
 out = foprn( argv[2], "wt" );

 do {
    ic = fgetc( in );
    while ( !feof( in ) && isspace(ic) ) {
	  fputc( ic, out );
	  ic = fgetc( in );
	  }
    ungetc( ic, in );
    fscanf( in, "%49[^\n,\t ]", buf );
    if ( search_list( in, out, buf, main_list, list_count, "" ) == -1 ) {
       fputs( buf, out );
       do {
	  ic = fgetc( in );
	  fputc( ic, out )
	  } while ( !feof( in ) && ic != '\n' );
       }
    } while ( !feof( in ) );
 fclose( in );
 fclose( out );
}


