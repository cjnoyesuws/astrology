#include "stdafx.h"
#include <stdlib.h>
#include "symbol.hpp"
#include "textbloc.hpp"
#include "errors.fns"
#include <winnls.h>

#define RBUFSIZ 32000

extern int charsize;

#ifdef _UNICODE
void trim( TCHAR *p )
{
 TCHAR *pe = p + _tcslen(p)-1;
 while ( *pe==_T(' ')||*pe==_T('\n')||*pe==_T('\r')) {
	*pe=_T('\0');
	pe--;
	}

}
#endif

void trim( char *p )
{
 char *pe = p + strlen(p)-1;
 while ( *pe==' '||*pe=='\n'||*pe=='\r') {
	*pe='\0';
	pe--;
	}

}

static int cvtFile;

//extern int entab_buf( const TCHAR *, TCHAR *, int );
//extern int detab_buf( const TCHAR *, int, TCHAR * );

unsigned char *rbuf;

void setupBuf(int i)
{
 if ( i )
    rbuf = new unsigned char[RBUFSIZ * charsize];
 else
    delete rbuf;
}

void setConvertFile( int i )
{
 cvtFile = i;
}

#ifdef _UNICODE
int CTextBlock::ReadTextMbs( FILE *stream, int help )
{
 unsigned char *buf;
 wchar_t *widebuf;
 static unsigned char *getbuf=NULL;
 int i = 0, c, endf=0;
 long size;
 static int flag;
 
 if ( getbuf == NULL ) {
	 getbuf = new unsigned char[10000];
     memset( getbuf,0,10000*sizeof(unsigned char));
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
    else
		c = fgetc(stream);
	if ( c=='#' && !help ) {
	   ungetc(c,stream);
	   endf = 1;
	   }
	else
	   ungetc(c,stream);
	if ( !endf && !_mbslen(getbuf) ) {
	   fgets((char *)getbuf,10000,stream);
       if ( getbuf[0] == '#' && help )
          fgets((char *)getbuf,100,stream);
       if ( help && (!strnicmp((char *)getbuf,"deftabs",7) || !strnicmp((char *)getbuf,"tabs",4) || !strnicmp((char *)getbuf,"^@",2)) )
		endf = 1;
	   }
	if ( !endf ) {
	   strcpy((char *)&rbuf[i],(char *)getbuf);
	   i+= strlen((char *)getbuf);
	   getbuf[0]='\0';
	   }
    } while ( i < RBUFSIZ && !endf );
 rbuf[i++] = '\0';
 _text_len = strlen((char *)rbuf);
 widebuf = new wchar_t[_text_len+1];
 _text_len =MultiByteToWideChar(CP_UTF8,0,(LPCSTR)rbuf,_text_len,widebuf,_text_len+1);
 //mbstowcs(widebuf,(const char *)rbuf,_mbslen(rbuf));
 widebuf[_text_len] = L'\0';
 _text = widebuf;
 delete widebuf;
 return( 0 );
}
#endif


int CTextBlock::ReadText( FILE *stream, int help )
{
 TCHAR *buf;
 static TCHAR *getbuf=NULL;
 int i = 0, c, endf=0;
 long size;
 static int flag;
 
 if ( getbuf == NULL ) {
	 getbuf = new TCHAR[10000];
     memset( getbuf,0,10000*sizeof(TCHAR));
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
    else
		c = _fgettc(stream);
	if ( c==_T('#') && !help ) {
	   _ungettc(c,stream);
	   endf = 1;
	   }
	else
	   _ungettc(c,stream);
	if ( !endf && !_tcslen(getbuf) ) {
	   _fgetts(getbuf,10000,stream);
       if ( getbuf[0] == _T('#') && help )
          _fgetts(getbuf,100,stream);
       if ( help && (!_tcsnicmp(getbuf,_T("deftabs"),7) || !_tcsnicmp(getbuf,_T("tabs"),4) || !_tcsnicmp(getbuf,_T("^@"),2)) )
		endf = 1;
	   }
	if ( !endf ) {
	   _tcscpy((TCHAR *)&rbuf[i],getbuf);
	   i+= _tcslen(getbuf);
	   getbuf[0]=_T('\0');
	   }
    } while ( i < RBUFSIZ && !endf );
 rbuf[i++] = _T('\0');
 _text_len = _tcslen((const TCHAR *)rbuf);
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

#ifdef _UNICODE
int CTextBlock::ReadHeader( FILE *stream, int *prev, char *prid )
{
 char bufi[50];
 TCHAR tbufi[50], c, cmt[300];
 memset(bufi,0,50);
 c = _fgettc( stream );
 if ( c == _TEOF )
    return( 0 );
 
 if ( c == _T('@') ) {
	 while ( c == _T('@') ) {
	    _fgetts(cmt,299,stream);
		c = _fgettc(stream);
	    }
	 _ungettc(c,stream);
    }
 else 
    _ungettc( c, stream );
 _ftscanf( stream, _T("# %49l[^\n]%lc"), tbufi, &c );
 if ( c == _T(' ') ) {
    do {
       c = _fgettc( stream );
       } while ( c != _T('\n') );
    }
 trim(tbufi);
 if ( !_tcscmp( tbufi, _T("+") ) ) {
    SetID( prid, *prev+1 );
    *prev+=1;
    }
 else {
    wcstombs(bufi,tbufi,_tcslen(tbufi));
	bufi[_tcslen(tbufi)]='\0';
    SetID( _strupr(bufi), 0 );
    strcpy( prid, _strupr(bufi) );
    *prev = 0;
    }
 return( ferror( stream ) );
}

int CTextBlock::ReadHeader2( FILE *stream )
{
 TCHAR tbuf1[40], tbuf2[40], c, cmt[300];
 char buf1[40], buf2[40];

 c = _fgettc( stream );
 if ( c == _TEOF )
    return( 0 );
  if ( c == _T('@') ) {
	 while ( c == _T('@') ) {
	    _fgetts(cmt,299,stream);
		c = _fgettc(stream);
	    }
	 _ungettc(c,stream);
    }
 else 
    _ungettc( c, stream );
 _ftscanf( stream, _T("# %ls %39l[^\n]%lc"), tbuf1, tbuf2, &c );
 trim(tbuf2);
 wcstombs(buf1,tbuf1,_tcslen(tbuf1));
 buf1[_tcslen(tbuf1)] = '\0';
 wcstombs(buf2,tbuf2,_tcslen(tbuf2));
 buf2[_tcslen(tbuf2)] = '\0';
 SetID( _strupr(buf1), _strupr(buf2) );
 return( ferror( stream ) );
}

int CTextBlock::ReadHeader3( FILE *stream )
{
 char buf1[40], buf2[40], buf3[40];
 TCHAR tbuf1[40], tbuf2[40], tbuf3[40], c, cmt[300];
 c = _fgettc( stream );
 if ( c == _TEOF )
    return( 0 );
 if ( c == _T('@') ) {
	 while ( c == _T('@') ) {
	    _fgetts(cmt,299,stream);
		c = _fgettc(stream);
	    }
	_ungettc(c,stream);
    }
 else 
   _ungettc( c, stream );
 _ftscanf( stream, _T("# %ls %ls %39l[^\n]%lc"), tbuf1, tbuf2, tbuf3, &c );
 trim(tbuf3);
 wcstombs(buf1,tbuf1,_tcslen(tbuf1));
 buf1[_tcslen(tbuf1)] = '\0';
 wcstombs(buf2,tbuf2,_tcslen(tbuf2));
 buf2[_tcslen(tbuf2)] = '\0';
 wcstombs(buf3,tbuf3,_tcslen(tbuf3));
 buf3[_tcslen(tbuf3)] = '\0';
 SetID( _strupr(buf1), _strupr(buf2), _strupr(buf3) );
 return( ferror( stream ) );
}

#else

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
 AfxMessageBox(CString(buf1));
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

#endif

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
 TCHAR *buf;
 
// detab_buf( (const TCHAR *)_text, RBUFSIZ, (TCHAR *)rbuf );
 buf = (TCHAR *)rbuf;
// if ( cvtFile )
//    doConvertText( (TCHAR *)rbuf, _ANS_T_, _SRC_T_ );
// else
//    doConvertText( (TCHAR *)rbuf, _ANS_T_, _EDT_T_ );
 while ( *buf ) {
       if ( *buf == _T('\r') )
          buf++;
#ifndef _UNICODE
	   if ( *buf == '~' ) {
	  fputc( *buf, stream );
	  fputc( *(buf+1), stream );
	  buf++;
	  }
       else 

	if (( *buf < ' ' || *buf >= '~' ) && *buf != _T('\n') ) {
	  _fputtc( _T('~'), stream );
	  _fputtc( *buf, stream );
	  }
       else
	  _fputtc( *buf, stream );
       buf++;
       }
#else
   _fputtc( *buf, stream );
       buf++;
 }
#endif
 return( ferror( stream ) );
}
