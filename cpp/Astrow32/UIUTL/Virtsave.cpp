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

#define EDIT   1
#define DELETE 2
#define INSERT 3

#ifdef PRO
extern int compress_string( char *in_str, char *out_str );
extern FILE *re_save_header( char *iname, char *oname );

void strip_binary( char *in, char *out, int mb )
{
 unsigned char l;
 int i;
 while ( *in ) {
    if ( *in == '\1' ) {
       *in++;
       l = *in++;
       for ( i = 0; i < l; i++ )
	   *out++ = *in++;
       }
    else if ( (unsigned char) *in  > (unsigned char) '\x80' && !mb ) {
       *out++ = '~';
       *out++ = *in++;
       if ( *in == ' ' ) {
	  *out++ = '~';
	  *out++ = *in++;
	  }
       }
    else if ( *in == '|' ) {
	  *out++ = *in++;
	  *in++;
	  }
    else
       *out++ = *in++;
    }
 *out++ = '\0';
 *out++ = '\0';
}

#endif

int VirtualTextBuffer::saveFile()
{
#ifdef PRO
 int i, len, svlen;
 unsigned char fl;
 FILE *stream;
 char *ptr, *gt, *cpbuf = new char[15000];
 char buf[150];
 strcpy( buf, set_path( "$$TEMP$$.FIL", USER_F ) );
 if ( (stream = re_save_header((char *)(LPCTSTR)acvSourceName, buf) ) == NULL )
    return( 0 );
 ptr = new char[15000];
 for ( i = 0; i < nParas; i++ ) {
     gt = getText(i, len, fl);
     memcpy( cpbuf, gt, len );
     cpbuf[len] = '\0';
     if ( len && len < 15000 ) {
	strip_binary(cpbuf, ptr, IsMbString );
    svlen = strlen(ptr);
	//svlen = compress_string( ptr, cpbuf );
	fputs( ptr, stream );
	}
     }
 fclose( stream );
 unlink(acvSourceName);
 rename( buf, acvSourceName );
 delete ptr;
 delete cpbuf;
 dirty() = 0;
 #endif
 return( 1 );
}

int VirtualTextBuffer::deletePara(int para)
{
#ifdef PRO
 cmdLast = DELETE;
 cmdUcl = pParaOfs[para];
 cmdPara = para;
 memmove( pParaOfs + para, pParaOfs + para + 1,
	 (nParaAlloc - para) * sizeof(union ucl) );
 nParas--;
 dirty() = 1;
#endif
 return( 1 );

}

int VirtualTextBuffer::insertParaAt(int para)
{
#ifdef PRO
 cmdLast = INSERT;

 cmdPara = para;
 if ( nParas < nParaAlloc ) {
    memmove( pParaOfs + para+1, pParaOfs + para,
	 (nParaAlloc - para-1) * sizeof(union ucl) );
    pParaOfs[para].set(0L,_CHNG_,0);
    }
 else {
    resize( 10 );
    memmove( pParaOfs + para+1, pParaOfs + para,
	 (nParaAlloc - para-1) * sizeof(union ucl) );
    pParaOfs[para].set(0L,_CHNG_,0);
    }
 nParas++;
 replaceParaAt(para,0,"\n");
 dirty() = 1;
#endif
 return( 1 );
}

int VirtualTextBuffer::replaceParaAt(int para, unsigned char fl, char *txt )
{
#ifdef PRO
 long ofs;

 cmdUcl = pParaOfs[para];
 cmdLast = EDIT;
 cmdPara = para;
 fseek( pvStream, 0L, SEEK_END );
 ofs = ftell(pvStream);
 fwrite( txt, 1, strlen(txt)+1, pvStream );
 pParaOfs[para].set(ofs,fl|_CHNG_, strlen(txt) );
 dirty() = 1;
#endif
 return( 1 );
}

int VirtualTextBuffer::undo()
{
#ifdef PRO
 switch( cmdLast ) {
       case EDIT :
	  {
	  uclwlen x = pParaOfs[cmdPara];
	  pParaOfs[cmdPara] = cmdUcl;
	  cmdUcl = x;
	  cmdLast = EDIT;
	  }
	  break;
       case DELETE:
	  insertParaAt(cmdPara);
	  pParaOfs[cmdPara] = cmdUcl;
	  break;
       case INSERT:
	  deletePara(cmdPara);
	  break;
       default :
	  break;
       }
 dirty() = 1;
#endif
 return( 1 );
}

