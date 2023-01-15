#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "symbol.hpp"
#include "textbloc.hpp"
#include "errors.fns"
#include "tbtutil.h"

#define RBUFSIZ 32000

static int cvtFile;

extern int entab_buf( char *, char *, int );
extern int detab_buf( char *, int, char * );

unsigned char *rbuf;

void setupBuf(int i)
{
 if ( i )
    rbuf = new unsigned char[RBUFSIZ];
 else
    delete rbuf;
}

void setConvertFile( int i )
{
 cvtFile = i;
}

int CTextBlock::ReadText( FILE *stream )
{
 char *buf;            
 int i = 0, c;
 long size;

 if ( feof( stream ) )
    return( 0 );
 do {
    if ( ferror( stream ) )
       return( 1 );
    c = fgetc( stream );
    if ( c == EOF )
       break;
    else if ( c == '#' && rbuf[i-1] == '\n' ) {
       ungetc( c, stream );
       break;
       }
    if ( c == '\n' ) 
       rbuf[i++] = (unsigned char)'\r';
    rbuf[i++] = (unsigned char)c;
    } while ( i < RBUFSIZ );
 rbuf[i++] = '\0';
 size = i * 3L;
 size /= 2L;
 buf = new char[(int)size];
 if ( buf == NULL ) {     
    do_mem_error( 0 );
    return( 1 );
    }
 doConvertText( (char *)rbuf, _EDT_T_, _ANS_T_ );
 size = entab_buf( (char *)rbuf, buf, RBUFSIZ );
 _text_len = size;
 _text = buf;
 delete buf;
 return( 0 );
}

int CTextBlock::SetID( char *id, int n )
{
 char buf[50];

 _type = 1;
 sprintf( buf, "%s\1%d", id, n );
 strcpy( _IDstring, buf );
 return( 1 );
}

int CTextBlock::SetID( char *id1, char *id2 )
{
 char buf[50];

 _type = 2;
 sprintf( buf, "%s\1%s", id1, id2 );
 strcpy( _IDstring, buf );
 return( 1 );
}

int CTextBlock::SetID( char *id1, char *id2, char *id3  )
{
 char buf[50];

 _type = 3;
 sprintf( buf, "%s\1%s\1%s", id1, id2, id3 );
 strcpy( _IDstring, buf );
 return( 1 );
}

int CTextBlock::GetIDParts( char *id, int *n )
{
 char dummy;
 return( sscanf( _IDstring, "%50[^\1]%c%d", id, &dummy, n ) );
}

int CTextBlock::GetIDParts( char *id1, char *id2 )
{
 char dummy;
 return( sscanf( _IDstring, "%40[^\1]%c%s", id1, &dummy, id2 ) );
}

int CTextBlock::GetIDParts( char *id1, char *id2, char *id3 )
{
 char dummy;
 return( sscanf( _IDstring, "%40[^\1]%c%40[^\1]%c%s", id1, &dummy, id2, &dummy, id3 ) );
}


int CTextBlock::ReadHeader( FILE *stream, int *prev, char *prid )
{
 char bufi[50], c;

 c = fgetc( stream );
 if ( c == EOF )
    return( 0 );
 ungetc( c, stream );
 if ( c == '@' ) {
    SetID( "@@COMMENT", 0 );
    strcpy( prid, "@@COMMENT");
    *prev = 0;
    return( ferror( stream ) );
    }
 fscanf( stream, "# %49[^ \n]%c", bufi, &c );
 if ( c == ' ' ) {
    do {
       c = fgetc( stream );
       } while ( c != '\n' );
    }
 if ( !strcmp( bufi, "+" ) ) {
    SetID( prid, *prev+1 );
    *prev+=1;
    }
 else {
    SetID( bufi, 0 );
    strcpy( prid, bufi );
    *prev = 0;
    }
 return( ferror( stream ) );
}

int CTextBlock::ReadHeader2( FILE *stream )
{
 char buf1[40], buf2[40], c;

 c = fgetc( stream );
 if ( c == EOF )
    return( 0 );
 ungetc( c, stream );
 if ( c == '@' ) {
    SetID( "@@COMMENT", "" );
    return( feof( stream ) );
    }
 fscanf( stream, "# %s %39[^ \n]%c", buf1, buf2, &c );
 if ( c == ' ' ) {
    do {
       c = fgetc( stream );
       } while ( c != '\n' );
    }
 SetID( buf1, buf2 );
 return( ferror( stream ) );
}

int CTextBlock::ReadHeader3( FILE *stream )
{
 char buf1[40], buf2[40], buf3[40], c;

 c = fgetc( stream );
 if ( c == EOF )
    return( 0 );
 ungetc( c, stream );
 if ( c == '@' ) {
    SetID( "@@COMMENT", "", "" );
    return( ferror( stream ) );
    }
 fscanf( stream, "# %s %s %39[^ \n]%c", buf1, buf2, buf3, &c );
 if ( c == ' ' ) {
    do {
       c = fgetc( stream );
       } while ( c != '\n' );
    }
 SetID( buf1, buf2, buf3 );
 return( ferror( stream ) );
}

int CTextBlock::WriteHeader( FILE *stream )
{
 char *b;

 if ( _IDstring[0] == '@' )
    return( 0 );
 fputs( "# ", stream );
 for ( b = _IDstring; *b; b++ ) {
     if ( *b == '\1' )
	fputc( ' ', stream );
     else
	fputc( *b, stream );
     }
 return( fputc( '\n', stream ) );
}

int CTextBlock::WriteHeaderR( FILE *stream )
{
 char buf[50];
 int i;
 char *b;

 if ( _IDstring[0] == '@' )
    return( 0 );
 fputs( "# ", stream );
 GetIDParts( buf, &i );
 if ( !i )
    fputs( buf, stream );
 else
    fputs( "+", stream );
 return( fputc( '\n', stream ) );
}


int CTextBlock::WriteText( FILE *stream )
{
 char *buf;
 
 detab_buf( (char *)_text, RBUFSIZ, (char *)rbuf );
 buf = (char *)rbuf;
 if ( cvtFile )
    doConvertText( (char *)rbuf, _ANS_T_, _SRC_T_ );
 else
    doConvertText( (char *)rbuf, _ANS_T_, _EDT_T_ );
 while ( *buf ) {
       if ( *buf == '\r' )
          buf++;
       if ( *buf == '~' ) {
	  fputc( *buf, stream );
	  fputc( *(buf+1), stream );
	  buf++;
	  }
       else if (( *buf < ' ' || *buf >= '~' ) && *buf != '\n' ) {
	  fputc( '~', stream );
	  fputc( *buf, stream );
	  }
       else
	  fputc( *buf, stream );
       buf++;
       }
 return( ferror( stream ) );
}
