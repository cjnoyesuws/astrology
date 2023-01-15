#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "fdecomp.hpp"
#include "errors.fns"
#include "msg.hpp"
#include "fptr.h"
#include "inifile.hpp"

int TextDecompressor::nextTab()
{
 int t;
 if ( pTabs->getCount() == 0 )
    return( -1 );
 t = pTabs->getTab(pTabs->getCurNo());
 pTabs->nextTab();
 if ( pTabs->getCurNo() > pTabs->getCount()+1 )
    pTabs->resetTab();
 return( t );
}

TextDecompressor::~TextDecompressor()
{
 if ( pBuf != NULL )
    delete pBuf;
 if ( pStream != NULL )
    fclose( pStream );
 delete pSexCodes;
 delete pTabs;
}

void TextDecompressor::closeFile()
{
 fclose( pStream );
 pStream = NULL;
}

int TextDecompressor::openFile( char *name )
{
 NFP xfpt;
 CWinApp *app;

 app = AfxGetApp();
 strcpy( acvFileName, name );
 if ( ( pStream = freadx_fptr( name, &xfpt, 0 ) ) == NULL ) {
    do_error( acvFileName );
    fclose( pStream );
    pStream = NULL;
    return( 0 );
    }
 ansi = (int) app->GetProfileInt( Misc_SEC, "AnsiText", ansi );
 if ( isafptr3w_file( &xfpt ) ) {
    fpt = xfpt.n.fpt;
    }
 if ( isafptr3_file( &xfpt ) ) {
    cvt_w16filedb_2_filedb( &xfpt.w16.fpt, &fpt );
	}
 else if ( isafptr2_file( &xfpt ) ) {
    cvt_filedb_2_win( &xfpt.w16.fpt );
    cvt_w16filedb_2_filedb( &xfpt.w16.fpt, &fpt );
    }
 else  {
    cvt_ofiledb_2_nfiledb( &xfdb.w16, &xfpt.o.fpt );
    cvt_w16filedb_2_filedb( &xfdb.w16, &fpt );
    }
 
 
 
 
 
 if ( isafptr3_file( &xfpt ) ) {
    fpt = xfpt.n.fpt;
    }
 else if ( isafptr2_file( &xfpt ) ) {
    fpt = xfpt.n.fpt;
    cvt_filedb_2_win( &fpt );
    }
 else  {
    cvt_ofiledb_2_nfiledb( &fpt, &xfpt.o.fpt );
    }
 if ( feof(pStream) ) {
    fclose( pStream );
    pStream = NULL;
    return( 0 );
    }
 if  ( strstr(name, ".ASHLP" ) != NULL || strstr(name, ".ashlp" ) != NULL ) {
     strcpy( fpt.name, titleName );
     strcpy( fpt.comment, "ASTRO-Helper File" );
     fpt.type = -1;
     }
 if  ( strstr(name, ".CMT" ) != NULL || strstr(name, ".cmt" ) != NULL ) {
     strcpy( fpt.name, "" );
     strcpy( fpt.comment, "ASTRO Comment File" );
     fpt.type = -2;
     }
 finished(1);
 return( 1 );
}


TextDecompressor::TextDecompressor( int size )
{
 atrib = 0;
 nSize = size;
 pBuf = new char[size];
 if ( pBuf == NULL ) {
    do_mem_error(0);
    return;
    }
 pTabs = new Tabs;
 if ( pTabs == NULL ) {
    do_mem_error(0);
    return;
    }
 pSexCodes = new SexCodes;
 if ( pSexCodes == NULL ) {
    do_mem_error(0);
    return;
    }
}


char *TextDecompressor::decompressPar( int &len, int &startAtr, int &endAtr )
{
 char buf2[100];
 int col = 0, sz = 0, ssz;
 char *cp, *buf = pBuf;
 int flag = 0, b, l = len;
 unsigned char c;
 extern char near word_lens[];
 extern char *word_array[];

 startAtr = atrib;
 while ( (b = getc(pStream) )  != EOF ) {
       c = (unsigned char)b;
       if ( c > (unsigned char) '\x80' ) {
    	  c &= 127;
	      flag = 1;
	      }
       if ( isalnum( c ) ) {
	      col++;
	      *buf++ = c;
	      }
       else if ( c != '\n' && c != ' ' && iscntrl( c ) ) {
	      l = word_lens[c];
	      memcpy( buf,  word_array[c], l );
	      buf+= l;
	      col += l;
	      sz+=l-1;
	      }
       else {
	  switch((unsigned char) c ) {
		case '\n':
		case (unsigned char)'\x80' :
		     *buf++ = '\n';
		     pTabs->resetTab();
		     if ( c != (unsigned char)'\x80' && col > 2 || sz+1 > 10 ) {
			    *buf++= '\0';
			    col = 0;
			    len = sz+1;
			    endAtr = atrib;
			    return( pBuf );
			    }
		     col = 0;
		     break;
		case '^' :
		     cp = buf;
		     ssz = 0;
		     pSexCodes->doCodes( pStream, &cp, &ssz, pTabs );
		     if ( ssz ) {
			    sz += ssz;
			    col += ssz + 1;
			    buf = ++cp;
			    }
		     else
                sz--;
		     break;
		case '|' :
		     *buf++ = c;
		     break;
		case '<' :
		     *buf++ = c;
		     atrib |= _ITAL_;
		     break;
		case '>' :
		     *buf++ = c;
		     atrib ^= _ITAL_;
		     break;
		case '{' :
		     *buf++ = c;
		     atrib |= _BOLD_;
		     break;
		case '}' :
		     *buf++ = c;
		     atrib ^= _BOLD_;
		     break;
		case '[' :
		     *buf++ = c;
		     atrib |= _HEAD_;
		     break;
		case ']' :
		     *buf++ = c;
		     atrib ^= _HEAD_;
		     break;
		case '~' :
		     col++;
		     buf2[0] = getc(pStream);
		     if ( strchr( "<>{}|^", buf2[0] ) != NULL ) {
			    *buf++ = '~';
			    sz++;
			    }
		     if ( !ansi ) {
			    OemToCharBuff( buf2, &buf2[50], 1 );
			    *buf++ = buf2[50];
			    }
		     else
			    *buf++ = buf2[50];
		     break;
		default :
		     *buf++ = c;
		     col++;
		     break;
		}
	  }
       if ( flag ) {
	      *buf++ = ' ';
	      col++;
	      sz++;
	      flag ^= flag;
	      }
       sz++;
       }
 if ( ferror( pStream ) )
    do_error( acvFileName );
 len = sz;
 endAtr = atrib;
 *buf++= '\0';
 return( pBuf );
}

char *TextDecompressor::tab_out( int *col, int *sz, char *buf )
{
 int tb, tc, l;

 tc = pTabs->getCount();
 tb = pTabs->getTab(pTabs->getCurNo());
 if ( !tc || !tb ) {
    *buf++ = ' ';
    (*col)++;
    (*sz)++;
    pTabs->nextTab();
    if ( pTabs->getCurNo() > pTabs->getCount() )
       pTabs->resetTab();
    return(buf);
    }
 else {
    pTabs->nextTab();
    if ( pTabs->getCurNo() > pTabs->getCount() )
       pTabs->resetTab();
    }
 (*sz)+=2;
 *buf++ = '|';
 *buf++ = (unsigned char )tb;
 *col = tb;
 return( buf );
}
