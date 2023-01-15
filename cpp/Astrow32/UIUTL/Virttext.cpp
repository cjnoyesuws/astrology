#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "virttext.hpp"
#include "errors.fns"
//#include "msg.hpp"
#include "fptr.h"
#include "paths.hpp"
#include "inifile.hpp"
#include <mbstring.h>

VirtualTextBuffer::~VirtualTextBuffer()
{
 if ( pvBuf != NULL )
    delete pvBuf;
 if ( pvStream != NULL )
    fclose( pvStream );
 if ( pParaOfs != NULL )
    delete pParaOfs;
 unlink(acvFileName);
}

VirtualTextBuffer::VirtualTextBuffer( int size, int vbsize )
{
 char pth[300];
	
 pvStream = NULL;
 _dirty = 0;
 nParaAlloc = size;
 pParaOfs = new uclwlen[size];
 uclVofs.set(0L,0,0);
 if ( pParaOfs == NULL ) {
    do_mem_error(0);
    nParaAlloc = 0;
    return;
    }
 nParas = 0;
 pvBuf = new char[vbsize];
 if ( pvBuf == NULL ) {
    do_mem_error(0);
    return;
    }
 nvbSizeAlloc = vbsize;
 GetTempPath(299,pth);
 GetTempFileName( pth, "AST", 0, (char *)(LPCTSTR)acvFileName.GetBuffer(300) );
 pTabs = new Tabs;
 if ( pTabs == NULL ) {
    do_mem_error(0);
    return;
    }
}

int VirtualTextBuffer::resize( int size )
{
 uclwlen *plTmp;

 plTmp = new uclwlen[size+nParaAlloc];
 if ( plTmp == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 memcpy( plTmp, pParaOfs, sizeof(uclwlen) * nParas );
 delete pParaOfs;
 pParaOfs = plTmp;
 nParaAlloc += size;
 return( 1 );
}

int VirtualTextBuffer::virtualizeFile( char *name, int dir)
{
 long bw = 0L, obw = 0L, ofi;
 char buf[100];
 int col = 0, sz;
 int ansi = 0;
 char *cp, *rt;
 NFP xfpt;
 NFDB xfdb;
 FILE *prStream;
 SexCodes *pSxc;
 int _break = 0, flag = 0, b, l;
 unsigned char atrib = 0, c;
 uclwlen ofs;
 extern char near word_lens[];
 extern char *word_array[];

 ansi = (int) GetPrivateProfileInt( Misc_SEC, "AnsiText", ansi, APPNAME );
 acvSourceName = set_path(name, dir);
 if ( ( pvStream = fopen( acvFileName, "wb" ) ) == NULL ) {
    do_error( (char *)(LPCTSTR)acvFileName );
    return( 0 );
    }
 if ( ( prStream = freadx_fptr((char *)(LPCTSTR) acvSourceName, &xfpt, 0 ) ) == NULL ) {
    do_error( name );
    fclose( pvStream );
    return( 0 );
    }
 if ( isafptr3w_file( &xfpt ) || isafptrcw_file( &xfpt ) || isafptr3wx_file( &xfpt ) || isafptr3wxu_file( &xfpt )) {
    fpt = xfpt.x.fpt;
    }
 else if ( isafptr3_file( &xfpt ) ) {
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
 IsMbString = isafptr3wxu_file( &xfpt );
 if ( feof(prStream) ) {
    fclose( prStream );
    fclose( pvStream );
    return( 0 );
    }
 pSxc = new SexCodes;
 if ( pSxc == NULL || pTabs == NULL ) {
    do_mem_error(0);
    fclose( prStream );
    fclose( pvStream );
    return( 0 );
    }
 //ProcMessage *pm = new ProcMessage(CResStr(_VTX_DECOMP)/*"Decompressing File..."*/, &_break);
 ofs.set(0L,0,0);
 pParaOfs[nParas++] = ofs;
 while ( (b = getc(prStream) )  != EOF ) {
       c = (unsigned char)b;
       if ( c > (unsigned char) '\x80' ) {
	      if ( !IsMbString ) {
		     c &= 127;
	         flag = 1;
	         }
	   }
      if ( isalnum( c ) ) {
	  col++;
	  bw++;
	  fputc( c, pvStream );
	  }
       else if ( c != '\n' && c != ' ' && iscntrl( c ) ) {
	  l = word_lens[c];
	  fwrite( word_array[c], 1, l, pvStream );
	  col += l;
	  bw += l;
	  }
       else {
	  switch((unsigned char) c ) {
		case '\n':
		case (unsigned char)'\x80' :
		     fputc( '\n', pvStream );
		     bw++;
		     if ( col < 2 ) {
			    col = 0;
			 pTabs->resetTab();
			 if ( c == (unsigned char)'\x80' ) {
			    b = getc(prStream);
                if ( b == '\r' )
                   b = getc(prStream);
				else
				   ungetc(b,prStream);
			    }
			 break;
			 }
		     col = 0;
		     pTabs->resetTab();
		     if ( nParas == nParaAlloc-1 ) {
			    if ( !resize( 100 ) ) {
 			       fclose( prStream );
			       fclose( pvStream );
			       pvStream = NULL;
			       delete pTabs;
			    pTabs = NULL;
			    delete pSxc;
			    pSxc = NULL;
			   //delete pm;
			   //pm = NULL;
			   return( 0 );
			   }
			}
		     ofs.set(obw,atrib,bw-obw);
		     obw = bw;
		     pParaOfs[nParas++] = ofs;
		     if ( _break ) {
			fclose( prStream );
			fclose( pvStream );
			pvStream = NULL;
			delete pTabs;
			pTabs = NULL;
			delete pSxc;
			pSxc = NULL;
			//delete pm;
			//pm = NULL;
			return( 0 );
			}
		     break;
		case '^' :
		     cp = buf;
		     sz = 0;
		     ofi = ftell( prStream );
		     rt = pSxc->doCodes( prStream, &cp, &sz, pTabs );
#ifdef NEW
#ifdef PRO
		     if ( (int)rt == pTabs->getCount() ) {
			int t, ct, ict;
			char xbuf[100], fmt[20], del;
			fseek(prStream, ofi+1, SEEK_SET );
			del = fgetc( prStream );
			strcpy( fmt, "%99[" );
			fmt[4]= del;
			strcpy( &fmt[5], "1234567890]" );
			fscanf(prStream, fmt, xbuf );
			fputc( '\1', pvStream );
			l = strlen(xbuf)+3;
			fputc( (unsigned char)l, pvStream );
			fputc( '^', pvStream );
			fputc( '@', pvStream );
			fputc( del, pvStream );
			fwrite( xbuf, 1, l-3, pvStream );
			bw+=l+2;
			}
#endif
#endif
		     if ( cp != buf ) {
			col++;
			}
		     if ( sz ) {
			fwrite( buf, 1, sz+1, pvStream );
			bw += sz + 1;
			}
		     break;
		case '|' :
		     sz = 0;
		     tab_out( &col, &sz );
		     bw += sz;
		     break;
		case '<' :
		     bw++;
		     fputc( c, pvStream );
		     atrib |= _ITAL_;
		     break;
		case '>' :
		     bw++;
		     fputc( c, pvStream );
		     atrib ^= _ITAL_;
		     break;
		case '{' :
		     bw++;
		     fputc( c, pvStream );
		     atrib |= _BOLD_;
		     break;
		case '}' :
		     bw++;
		     fputc( c, pvStream );
		     atrib ^= _BOLD_;
		     break;
		case '[' :
		     bw++;
		     fputc( c, pvStream );
		     atrib |= _HEAD_;
		     break;
		case ']' :
		     bw++;
		     fputc( c, pvStream );
		     atrib ^= _HEAD_;
		     break;
		case '@' :
			{
			 char cht = getc(prStream);
			 if ( cht == 'T' || cht == 't' ) {
				 int c =getc(prStream);
				 if ( c=='p' || c=='P' ) {
				   getc(prStream);
				   getc(prStream);
				 }
				 getc(prStream);
			     putc('\n',pvStream);
				 bw++;
				 pTabs->resetTab();
			 }
			 else {
			    ungetc(cht,prStream);
				col++;
		        bw++;
				fputc( '@', pvStream );
				bw++;
				col++;
			   }
			 }
			break;
		case '~' :
		     col++;
		     bw++;
		     buf[0] = getc(prStream);
		     if ( strchr( "<>{}|^", buf[0] ) != NULL ) {
			fputc( '~', pvStream );
			bw++;
			}
		     if ( !ansi ) {
			OemToCharBuff( buf, &buf[50], 1 );
			fputc( buf[50], pvStream );
			}
		     else
			fputc( buf[0], pvStream );
		     break;
		default :
		     fputc( c, pvStream );
		     bw++;
		     col++;
		     break;
		}
	  }
       if ( flag ) {
	  fputc( ' ', pvStream );
	  bw++;
	  col++;
	  flag ^= flag;
	  }
       if ( _break )
	  break;
       }
 if ( nParas == nParaAlloc-1 )
    flag = resize( 3 );
 if ( flag || (bw-obw)) {
    ofs.set(obw,atrib,bw-obw);
    obw = bw;
    pParaOfs[nParas++] = ofs;
    }
 for ( int i = nParas+1; i < nParaAlloc; i++ ) {
     ofs.set(0xffffff,0,0);
     pParaOfs[i++] = ofs;
     }
 fclose( prStream );
 fclose( pvStream );
 pvStream = NULL;
 delete pSxc;
 pSxc = NULL;
 delete pTabs;
 pTabs = NULL;
 //if ( pm != NULL )
 //   delete pm;
 return( 0 );
}

/* Get the size in bytes of a paragraph */

int VirtualTextBuffer::getSize( int nPar )
{
 if ( nPar < nParas-1 )
    return( pParaOfs[nPar].getLen() );
 else
    return( 0 );
}

/* Open the virtual buffer. Opens the precreated virtual file to read
   and reads the first chunk */

int VirtualTextBuffer::openVbuf()
{
 if ( pvBuf != NULL && pvStream != NULL )
    return(1);
 if ( pvBuf == NULL ) {
    pvBuf = new char[nvbSizeAlloc];
    if ( pvBuf == NULL ) {
       do_mem_error(0);
       return(0);
       }
    }
 if ( ( pvStream = fopen( acvFileName, "r+b" ) ) == NULL ) {
    do_error( (char *)(LPCTSTR)acvFileName );
    return( 0 );
    }
 fseek( pvStream, uclVofs.getOfs(), SEEK_SET );
 nvbLen = fread( pvBuf, 1, nvbSizeAlloc, pvStream );
 return( ferror( pvStream ) );
}

/* close the virtual buffer. Closes the file and deletes the in memory
   buffer */

void VirtualTextBuffer::closeVbuf()
{
 if ( pvBuf == NULL && pvStream == NULL )
    return;
 if ( pvBuf != NULL ) {
    delete pvBuf;
    pvBuf = NULL;
    }
 if ( pvStream != NULL ) {
    fclose( pvStream );
    pvStream = NULL;
    }
}

/* Find a paragraph, starting at paragraph, nPar and further back,
   where the offset it less than lOfs into the file */

int VirtualTextBuffer::findPar( int nPar, long lOfs )
{
 int i;
 uclwlen lo;

 if ( nPar >= nParas )
    return( -1 );
 if ( lOfs <= 0L )
    return( 0 );
 lo = pParaOfs[nPar];
 if ( lo.getOfs() == 0xffffff )
    return( -1 );
 if ( lo.getFlags() & _CHNG_ )
    return( nPar );
 for ( i = nPar; lo.getOfs() > lOfs && i >= 0; i-- )
     lo = pParaOfs[i];
 return( i );
}

/* get the text at nPar, returning the length as well. If that text is
   not currently in memory read the chunk with that paragraph approximately
   in the middle or 2nd quarter of the buf, to allow for scrolling */


char *VirtualTextBuffer::getText( int nPar, int &len, unsigned char &flags )
{
 uclwlen lo;
 long wh, whe;
 int np;

 if ( nPar >= nParas )
    return( NULL );
 lo = pParaOfs[nPar];
 if (lo.getOfs() == 0xffffff)
    return( NULL );
 len = getSize(nPar);
 wh = (long)(lo.getOfs() - uclVofs.getOfs());
 whe = wh + len;
 if ( lo.getOfs() >= uclVofs.getOfs()
      && wh >= 0 && whe >= 0 && whe <= (long) nvbLen ) {
    flags = pParaOfs[nPar].getFlags();
    return( pvBuf + (int)wh );
    }
 np = findPar( nPar, lo.getOfs() - 1200 );
 if ( np < 0 )
    return( NULL );
 assert( np >= 0 );
 uclVofs = pParaOfs[np];
 assert(uclVofs.getOfs() != 0xffffff );
 fseek( pvStream, uclVofs.getOfs(), SEEK_SET );
 nvbLen = fread( pvBuf, 1, nvbSizeAlloc, pvStream );
 flags = pParaOfs[nPar].getFlags();
 return( pvBuf + (int)(lo.getOfs() - uclVofs.getOfs()) );
}


void VirtualTextBuffer::tab_out( int *col, int *sz )
{
 int tb, tc;

 tc = pTabs->getCount();
 tb = pTabs->getTab(pTabs->getCurNo());
 if ( !tc || !tb ) {
    fputc( ' ', pvStream );
    (*col)++;
    (*sz)++;
    pTabs->nextTab();
    if ( pTabs->getCurNo() > pTabs->getCount() )
       pTabs->resetTab();
    return;
    }
 else {
    pTabs->nextTab();
    if ( pTabs->getCurNo() > pTabs->getCount() )
       pTabs->resetTab();
    }
 (*sz)+=2;
 fputc( '|', pvStream );
 fputc( (unsigned char ) tb, pvStream );
 *col = tb;
}

long VirtualTextBuffer::getOfsAt(int i)
{
 if ( i < nParas )
    return( pParaOfs[i].getOfs() );
 else
    return( -1L );
}

unsigned char VirtualTextBuffer::getFlagsAt(int i)
{
 if ( i < nParas )
    return( pParaOfs[i].getFlags() );
 else
    return( 0 );
}
