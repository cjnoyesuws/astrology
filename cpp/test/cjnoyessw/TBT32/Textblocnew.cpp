#include "stdafx.h"
#include <stdlib.h>
#include "symbol.hpp"
#include "textbloc.hpp"
#include "errors.fns"


#define RBUFSIZ 32000
/*

void trim( char *p )
{
 char *pe = p + strlen(p)-1;
 while ( *pe==' ') {
	*pe='\0';
	pe--;
	}

}


static int cvtFile;

extern int entab_buf( const char *, char *, int );
extern int detab_buf( const char *, int, char * );
*/
TCHAR *rbuf;

void setupBuf(int i)
{
 if ( i )
    rbuf = new TCHAR[RBUFSIZ];
 else
    delete rbuf;
}
/*
void setConvertFile( int i )
{
 cvtFile = i;
}
*/
int CTextBlock::ReadText( FILE *stream, int help )
{
 char *buf;
 static TCHAR *getbuf=NULL;
 int i = 0, endf=0;
 long size;
 static int flag;
 TCHAR c;

 if ( getbuf == NULL ) {
	 getbuf = TCHAR[10000];
     memset( getbuf,sizeof(TCHAR),10000);
     }
 if ( feof( stream ) ) {
    delete getbuf;
	getbuf = NULL;
	return( 0 );
    }
 do {
    if ( ferror( stream ) )
       return( 1 );
	if ( feof( stream )) { 
       endf = 1;
	   break;
	}
    c = fgettc(stream);
	if ( c=='#' && !help ) {
	   ungettc(c,stream);
	   endf = 1;
	   break;
	   }
	else
	   ungettc(c,stream);
	if ( !strlen(getbuf) ) {
	   fgetts(getbuf,10000,stream);
       if ( getbuf[0] == '#' && help )
          fgetts(getbuf,100,stream);
       if ( help && (!_tcsnicmp(getbuf,"deftabs",7) || !_tcsnicmp(getbuf,"tabs",4) || !strnicmp(getbuf,"^@",2)) )
		endf = 1;
	   }
	if ( !endf ) {
	   strcpy((char *)&rbuf[i],getbuf);
	   i+= tcslen(getbuf);
	   getbuf[0]='\0';
	   }
    } while ( i < RBUFSIZ && !endf );
 rbuf[i++] = '\0';
 _text_len = tcslen((TCHAR *)rbuf);
 _text = rbuf;
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
 char bufi[50], c, cmt[300];
 memset(bufi,0,50);
 c = fgetc( stream );
 if ( c == EOF )
    return( 0 );
 
 if ( c == '@' ) {
	 while ( c == '@' ) {
	    fgets(cmt,299,stream);
		c = fgetc(stream);
	    }
	 ungetc(c,stream);
    }
 else 
    ungetc( c, stream );
 fscanf( stream, "# %49[^\n]%c", bufi, &c );
 if ( c == ' ' ) {
    do {
       c = fgetc( stream );
       } while ( c != '\n' );
    }
 trim(bufi);
 if ( !strcmp( bufi, "+" ) ) {
    SetID( prid, *prev+1 );
    *prev+=1;
    }
 else {
    SetID( _strupr(bufi), 0 );
    strcpy( prid, _strupr(bufi) );
    *prev = 0;
    }
 return( ferror( stream ) );
}

int CTextBlock::ReadHeader2( FILE *stream )
{
 char buf1[40], buf2[40], c, cmt[300];

 c = fgetc( stream );
 if ( c == EOF )
    return( 0 );
  if ( c == '@' ) {
	 while ( c == '@' ) {
	    fgets(cmt,299,stream);
		c = fgetc(stream);
	    }
	 ungetc(c,stream);
    }
 else 
    ungetc( c, stream );
 fscanf( stream, "# %s %39[^\n]%c", buf1, buf2, &c );
 trim(buf2);
 SetID( _strupr(buf1), _strupr(buf2) );
 return( ferror( stream ) );
}

int CTextBlock::ReadHeader3( FILE *stream )
{
 char buf1[40], buf2[40], buf3[40], c, cmt[300];

 c = fgetc( stream );
 if ( c == EOF )
    return( 0 );
 if ( c == '@' ) {
	 while ( c == '@' ) {
	    fgets(cmt,299,stream);
		c = fgetc(stream);
	    }
	 ungetc(c,stream);
    }
 else 
    ungetc( c, stream );
 fscanf( stream, "# %s %s %39[^\n]%c", buf1, buf2, buf3, &c );
 trim(buf3);
 SetID( _strupr(buf1), _strupr(buf2), _strupr(buf3) );
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
 
 detab_buf( (const char *)_text, RBUFSIZ, (char *)rbuf );
 buf = (char *)rbuf;
// if ( cvtFile )
//    doConvertText( (char *)rbuf, _ANS_T_, _SRC_T_ );
// else
//    doConvertText( (char *)rbuf, _ANS_T_, _EDT_T_ );
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
