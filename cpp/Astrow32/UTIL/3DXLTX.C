#include <stdio.h>
#include <string.h>
#include <search.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct CTL_LIST {
	char name[20];
	int (*pfn)(FILE *in, FILE *out, char *key, char *data);
	} CTL_LIST;

extern int begin(FILE *in, FILE *out, char *key, char *data);
extern int endx(FILE *in, FILE *out, char *key, char *data);
extern int text(FILE *in, FILE *out, char *key, char *data);
extern int control(FILE *in, FILE *out, char *key, char *data);
extern int group(FILE *in, FILE *out, char *key, char *data);
extern int radio(FILE *in, FILE *out, char *key, char *data);
extern int group(FILE *in, FILE *out, char *key, char *data);
extern int icon(FILE *in, FILE *out, char *key, char *data);
extern int check(FILE *in, FILE *out, char *key, char *data);
extern int static_sub(FILE *in, FILE *out, char *key, char *data);
extern int null_ctl_sub(FILE *in, FILE *out, char *key, char *data);
extern int button_sub(FILE *in, FILE *out, char *key, char *data);
extern int search_list( FILE *in, FILE *out, char *key, CTL_LIST *list, int num, char *data );

#define LIST_CNT 15

CTL_LIST main_list[LIST_CNT] = {
    "LTEXT", text,
    "RTEXT", text,
    "CTEXT", text,
    "CONTROL", control,
    "GROUPBOX", group,
    "RADIOBUTTON", radio,
    "CHECKBOX", check,
    "BEGIN", begin,
    "END",   endx
    };

int list_count = LIST_CNT;

#define SUB_LIST_CNT 6

CTL_LIST sub_list[SUB_LIST_CNT] = {
     "\"BUTTON\"", button_sub,
     "\"COMBOBOX\"", null_ctl_sub,
     "\"EDIT\"", null_ctl_sub,
     "\"LISTBOX\"", null_ctl_sub,
     "\"SCROLLBAR\"", null_ctl_sub,
     "\"STATIC\"", static_sub };

int sub_list_count = SUB_LIST_CNT;

int level;

char *strstri(char *txt, char *fnd )
{
 char buf[400];
 char fndb[50], *p;

 strcpy( fndb, fnd );
 strupr(fndb);
 strcpy(buf,txt);
 strupr(buf);
 p = strstr(buf,fndb);
 if ( p == NULL )
    return( p );
 else
    return( p-buf+txt );
}


int getline( char *buf, int len, FILE *in )
{
 int l = 0;

 do {
    if ( len - l < 10 ) {
       printf( "\a\aERROR--getline Line not long enought len = %d, Balance = %d\n",
	      len, len - l );
       exit( -1 );
       }
    if ( fgets( buf+l, len-l, in ) == NULL )
       return( 0 );
    l = strlen(buf);
    while ( isspace(buf[l-1] ) )
	  l--;
    } while (buf[l-1] == '|' || buf[l-1] == ',');
}


char *ltrim( char *str )
{

 while ( isspace( *str ) )
       str++;
 return( str );
}


char *trim( char *str )
{
 int len = strlen( str );
 while ( isspace( str[len-1] ) )
       len--;
 str[len] = '\0';
 return( str );
}


char *mkoptstr( char *opt, int add )
{
 static char buf[300];

 trim( opt );
 if ( !strlen(opt) && add )
    return( ", WS_VISIBLE | WS_CHILD | " );
 else if ( !strlen(opt) )
    return( ", WS_VISIBLE | WS_CHILD" );
 else
    if ( opt[0] != ',' && opt[1] != ',' )
       strcpy( buf, ", " );
    else
       buf[0] = '\0';
    strcat( buf, opt );
    if ( add )
       strcat( buf, " WS_VISIBLE | WS_CHILD | " );
 return( buf );
}


int text(FILE *in, FILE *out, char *key, char *data)
{
 char text[250], id[50], options[150];
 int x, y, width, height, dummy;

 if ( !level )
    return( -1 );
 options[0] = '\0';
 text[0] = '\0';
 fscanf( in, " \"%249[^\"]\",%49[^,],%d,%d,%d,%d%149[^\n]", text, id, &x, &y, &width, &height, options );
 fprintf( out, "CONTROL \"%s\", %s, \"zStatTxt3dClass\"%s", text, id, mkoptstr(options,1) );
 if ( !strcmpi( key, "RTEXT" ) ) {
    fprintf( out, "SS_RIGHT" );
    }
 else if (!strcmpi( key, "LTEXT" ) ) {
    fprintf( out, "SS_LEFT");
    }
 else if (!strcmpi( key, "CTEXT" ) ) {
    fprintf( out, "SS_CENTER");
    }
 fprintf( out, " | ZTXT3D_INSET, %d, %d, %d, %d", x, y, width, height );
 return( 1 );
}

int control(FILE *in, FILE *out, char *key, char *data)
{
 static char buf[300];
 char text[250], class[20], id[50];
 int x;

 if ( !level )
    return( -1 );
 if ( getline(buf, 299, in) == 0 )
    return( 0 );
 sscanf( buf, " \"%249[^\"]\",%49[^,],%19[^,]", text, id, class );
 if ( ( x = search_list(in, out, class, sub_list,
	   sub_list_count, buf) ) == -1 )
    fprintf( out, "CONTROL %s", buf );
 else
    return( x );
}

int group(FILE *in, FILE *out, char *key, char *data)
{
 char text[250], id[50], options[150];
 int x, y, width, height, dummy;

 if ( !level )
    return( -1 );
 options[0] = '\0';
 fscanf( in, " \"%249[^\"]\",%49[^,],%d,%d,%d,%d%149[^\n]", text, id, &x, &y, &width, &height, options );
 fprintf( out, "CONTROL \"%s\", %s, \"zGroupBox3dClass\"", text, id );
 fprintf( out, "%s ZTXT3D_INSET | ZTXT3D_LEFT | ZGRP3D_BLACK, %d, %d, %d, %d", mkoptstr(options,1), x, y, width, height );
 return( 1 );
}

int radio(FILE *in, FILE *out, char *key, char *data)
{
 char text[250], id[50], options[150];
 int x, y, width, height, dummy;

 if ( !level )
    return( -1 );
 options[0] = '\0';
 fscanf( in, " \"%249[^\"]\",%49[^,],%d,%d,%d,%d%149[^\n]", text, id, &x, &y, &width, &height, options );
 fprintf( out, "CONTROL \"%s\", %s, \"zRadioBtn3dClass\"", text, id );
 fprintf( out, "%s ZRDO3D_INSET, %d, %d, %d, %d", mkoptstr(options,1), x, y, width, height );
 return( 1 );
}

int check(FILE *in, FILE *out, char *key, char *data)
{
 char text[250], id[50], options[150];
 int x, y, width, height, dummy;

 if ( !level )
    return( -1 );
 options[0] = '\0';
 fscanf( in, " \"%249[^\"]\",%49[^,],%d,%d,%d,%d%149[^\n]", text, id, &x, &y, &width, &height, options );
 fprintf( out, "CONTROL \"%s\", %s, \"zCheckBox3dClass\"", text, id );
 fprintf( out, "%s ZCHECK3D_CROSS, %d, %d, %d, %d", mkoptstr(options,1), x, y, width, height );
 return( 1 );
}

int begin(FILE *in, FILE *out, char *key, char *data)
{
 level++;
 fprintf( out, "BEGIN", data );
 return( 1 );
}

int endx(FILE *in, FILE *out, char *key, char *data)
{
 level--;
 fprintf( out, "END", data );
 return( 1 );
}


int null_ctl_sub(FILE *in, FILE *out, char *key, char *data)
{
 if ( !level )
    return( -1 );
 fprintf( out, "CONTROL %s\n", data );
 return( 1 );
}


int static_sub(FILE *in, FILE *out, char *key, char *data)
{
 char text[250], class[20], id[50];
 char options[200];
 int x, y, width, height;

 if ( !level )
    return( -1 );
 options[0] = '\0';
 if ( strstri( data, "SS_LEFT" ) != NULL ||
      strstri( data, "SS_RIGHT" ) != NULL ||
      strstri( data, "SS_CENTER" ) != NULL ) {
    sscanf( data, " \"%249[^\"]\",%49[^,],\"%19[^\"]\",%199[^,],%d,%d,%d,%d",
	   text, id, class, options, &x, &y, &width, &height );
    fprintf( out, "CONTROL \"%s\", %s, \"zStatTxt3dClass\"%s ZTXT3D_INSET, %d, %d, %d, %d\n",
      text, id, mkoptstr(options,1), x, y, width, height );
    }
 else
    fprintf( out, "CONTROL %s\n", data );
 return( 1 );
}


int button_sub(FILE *in, FILE *out, char *key, char *data)
{
 char text[250], class[20], id[50];
 char options[200];
 int x, y, width, height;

 if ( !level )
    return( -1 );
 options[0] = '\0';
 if ( strstri( data, "BS_GROUPBOX" ) != NULL ) {
    sscanf( data, " \"%249[^\"]\",%49[^,],\"%19[^\"]\",%199[^,],%d,%d,%d,%d",
	   text, id, class, options, &x, &y, &width, &height );
    fprintf( out, "CONTROL \"%s\", %s, \"zGroupBox3dClass\"%s ZTXT3D_INSET | ZTXT3D_LEFT | ZGRP3D_BLACK, %d, %d, %d, %d\n",
      text, id, mkoptstr(options,1), x, y, width, height );
    }
 else if ( strstri( data, "BS_CHECKBOX" ) != NULL ||
      strstri( data, "BS_AUTOCHECKBOX" ) != NULL ||
      strstri( data, "BS_3STATE" ) != NULL ||
      strstri( data, "BS_AUTO3STATE" ) != NULL ) {
    sscanf( data, " \"%249[^\"]\",%49s,\"%19[^\"]\",%199[^,],%d,%d,%d,%d",
	   text, id, class, options, &x, &y, &width, &height );
    fprintf( out, "CONTROL \"%s\", %s, \"zCheckBox3dClass\"%s ZCHECK3D_CROSS, %d, %d, %d, %d\n",
      text, id, mkoptstr(options,1), x, y, width, height );
    }
 else if ( strstri( data, "BS_AUTORADIOBUTTON" ) != NULL ) {
    sscanf( data, " \"%249[^\"]\",%49[^,],\"%19[^\"]\",%199[^,],%d,%d,%d,%d",
	   text, id, class, options, &x, &y, &width, &height );
    fprintf( out, "CONTROL \"%s\", %s, \"zRadioBtn3dClass\"%s ZRDO3D_INSET, %d, %d, %d, %d\n",
      text, id, mkoptstr(options,1), x, y, width, height );
    }
 else
    fprintf( out, "CONTROL %s\n", data );
 return( 1 );
}



int search_list( FILE *in, FILE *out, char *key, CTL_LIST *list, int num, char *data )
{
 CTL_LIST *fnd;

 fnd = (CTL_LIST *)lfind( key, list, &num, sizeof(CTL_LIST), strcmpi );
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
 out = fopen( argv[2], "wt" );

 do {
    ic = fgetc( in );
    if ( ic == EOF )
       break;
    while ( !feof( in ) && isspace(ic) ) {
	  fputc( ic, out );
	  ic = fgetc( in );
	  if ( ic == EOF )
	     break;
	  }
    if ( ic == EOF )
       break;
    ungetc( ic, in );
    fscanf( in, "%49[^\n,\t ]", buf );
    if ( search_list( in, out, buf, main_list, list_count, "" ) == -1 ) {
       fputs( buf, out );
       do {
	  ic = fgetc( in );
	  if ( ic == EOF )
	     break;
	  fputc( ic, out );
	  } while ( !feof( in ) && ic != '\n' );
       }
    } while ( !feof( in ) );
 fclose( in );
 fclose( out );
}


