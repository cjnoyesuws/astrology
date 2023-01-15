#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <ctype.h>
#include <errno.h>
#include "attrib.h"
#include "errors.fns"
#include "output.fns"
#include <assert.h>
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "asfrmdlg.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "write.hpp"
#include "writecnv.hpp"

static int hf, hs, fs, it;
static PAP reg, head;


void TextConvDriverWrite::initDecomp( int wid )
{
 int x;

 if ( wid < 1800 )
    wid /= 10;
 else
    wid = 222;
 head_mode = 0;
 /*
 getSizes( fs, hs, it );
 if ( strcmp( getFont(x), getHead(x) ) )
    hf = 1;
 else
    hf = 0;
 */
 chps.init(pRs);
 reg = defPap;
 head = defPap;
 head.setJust( JCNTR );
 head.setSpace( (hs+2) * 20 );
 curPap.copyBase(&reg);
 papChange = 1;
 pTabs->init( wid, mul, div, 0 );
}


char *TextConvDriverWrite::tabSet( char *buf, int *sz )
{
 curPap.tabStart();
 for ( int i = 0; i < pTabs->getCount(); ++i ) {
     curPap.addTab(pTabs->getTab(i));
     }
 return( buf );
}


int TextConvDriverWrite::addChps()
{
 CHP_PAGE *cp = new CHP_PAGE;
 if ( cp == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 *cp = chps;
 chpList.append(cp);
 chps.initFodCount();
 chps.setFirst(lastOfsChp);
 return( 1 );
}


int TextConvDriverWrite::addPaps()
{
 XPAP_GROUP *pp = new XPAP_GROUP;
 if ( pp == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 *pp = paps;
 papList.append(pp);
 paps.initFodCount();
 paps.setFirst(lastOfsPap);
 return( 1 );
}




/* decompression for text files using words.c word array */

extern char * word_array[32];


char *TextConvDriverWrite::moveStr( unsigned char *in, unsigned char *out, unsigned int *sz )
{
 register unsigned s = *sz;
 register unsigned char *op = out;

 while ( *op++ = *in++ ) {
       col++;
       s++;
       curOfs++;
       }
 *sz = s-1;
 return((char _far *) op-1 );
}



/* function to decompress string compressed in buildtxt and 3dbldtxt
   using compress function. This version is specific for output to the
   printer and output to a file. Uses common word_array in words.c.
   Each char in inbuf between chr(32) - chr(127) is copied to outbuf
   verbatim. If a char (chr(32)|128) - (chr(127)|128) that char has has a
   word space compressed into it. The (char&127) is copied to outbuf,
   and followed by a space. If a char chr(1) - chr(31) is found,
   word_array[char] is copied to the string. If a char (chr(1)|128) -
   (chr(31)|128) is found word_array[char] is copied to the string,
   followed by a space. size represents allocated size of outbuf. Size
   should be approx 150% size allocated for inbuf. The number of chars
   in buffer is returned for success. chr(128) is used for embedded
   (sticky) spaces. The sticky spaces allow ASTRO to read an entire block
   of text including groups of lines which need to stay together, and them
   rewrap them after the fact as the chr(128)'s are converted to '\n's and
   '\n's are respected by text_wrap(). Extended chars are represented by
   '~' before an extended char. At the end of a word, the extended char
   should be followed by another '~' before the space so the space doesn't
   get lost. '{' indicates the start of bold text. '}' indicates the end of
   bold text. '<' indicates the start of underscored text, and '>' the
   end. When these characters are encountered, the string corresponding
   to these characters are copied to the output buffer. Tab Stops are
   indicated by | in text. */

unsigned int TextConvDriverWrite::decompress( char *outbuf, unsigned out_size, int *lines, int mode )
{
 char bf[10];
 register unsigned char *out = (unsigned char _far *)outbuf;
 unsigned char *cp, c, op;
 unsigned sz = 0, os = out_size - 10;
 int flag = 0, b, row = 0, t;
 XPAP save;
 long xw;

 *lines = 0;
 if ( outbuf == NULL || out_size == 0 ) /* no space allocated then return */
    return( 0 );
 else if ( feof(istream) )
	 return( 0 );

 while ( (b = getc(istream)) != EOF && sz <= os ) {
       c = (unsigned char)b;
       if ( c > (unsigned char) '\x80' ) {
	  c &= 127;
	  flag = 1;
	  }
       if ( isalnum( c ) ) {
	  *out++ = c;
	  col++;
	  curOfs++;
	  }
       else if ( c != ' ' && c != '\n' && c < ' ' )
	  out = (unsigned char _far *) moveStr( (unsigned char _far *)word_array[c], out, &sz );
       else {
	  switch( c ) {
		case (unsigned char) '\x80' :
		case '\n' :
		     pTabs->resetTab();
		     *out++ = '\n';
		     row++;
		     col = 0;
		     if ( papChange ) {
			if (papChange == -1 ) {
			   if ( !paps.addPap(curOfs+1, save ) ) {
			      addPaps();
			      paps.addPap(curOfs+1, save );
			      }
			   save = curPap;
			   }
			else {
			   if ( !paps.addPap(curOfs+1, curPap ) ) {
			      addPaps();
			      paps.addPap(curOfs+1, curPap );
			      }
			   }
			papChange=0;
			}
		     else {
			if ( !paps.addFod(curOfs+1) ) {
			   addPaps();
			   paps.addPap(curOfs+1, curPap );
			   }
			}
		     lastOfsPap = curOfs;
		     curOfs++;
		     if ( (c == '\n' && sz > 3 &&
			op != (unsigned char) '\x80') || c == '\n' && row > 10  ) {
			*lines = row;
			*out++ = '\0';
			*out = '\0';
			return( sz++ );
			}
		     if ( c == (unsigned char) '\x80' &&
			  op == (unsigned char) '\x80' )
			op = 0;
		     break;
		case '~' :
		     *out++ = '~';
		     c = getc(istream);
		     if ( !ansi ) {
			bf[0] = c;
			OemToAnsiBuff(bf, &bf[5], 1 );
			c = bf[5];
			}
		     curOfs++;
		     col++;
		     *out++ = c;
		     break;
		case '^' :
		     if ( out_size - sz < 220 ) {
			ungetc( c, istream );
			*out = '\0';
			*lines = row+1;
			*out++ = '\0';
			*out = '\0';
			return( sz++ );
			}
		     cp = out;
		     if ( pSxc->doCodes( istream, (char **)&cp, (int *)&sz, pTabs ) < (char *)20 )
			out = (unsigned char _far *)tabSet( (char _far *)cp, (int *) &sz );
		     while ( out != cp ) {
			   curOfs++;
			   out++;
			   }
		     break;
		case '{' :
		     bold_mode = 1;
		     if ( !chps.addBold(curOfs+1) ) {
			addChps();
			chps.addBold(curOfs+1);
			}
		     lastOfsChp = curOfs;
		     break;
		case '>' :
		case '}' :
		     if ( !chps.addReg(curOfs+1) ) {
			addChps();
			chps.addReg(curOfs+1);
			}
		     lastOfsChp = curOfs;
		     break;
		case '<' :
		     if ( !chps.addItal(curOfs+1) ) {
			addChps();
			chps.addItal(curOfs+1);
			}
		     lastOfsChp = curOfs;
		     break;
		case '[' :  /* change to the head font */
		     if ( !chps.addHead(curOfs+1) ) {
			addChps();
			chps.addHead(curOfs+1);
			}
		     lastOfsChp = curOfs;
		     curPap.copyBase(&head);
		     papChange = 1;
		     head_mode = 1;
		     break;
		case ']' :  /* change to the text font */
		     if ( !chps.addReg(curOfs+1) ) {
			addChps();
			chps.addReg(curOfs+1);
			}
		     lastOfsChp = curOfs;
		     save = curPap;
		     curPap.copyBase(&reg);
		     papChange = -1;
		     head_mode = 0;
		     break;
		case '|' :
		     if ( out_size - sz < 100 ) {
			ungetc( c, istream );
			*out = '\0';
			*lines = row+1;
			return( sz++ );
			}
		     else {
			cp = (unsigned char _far *)tabOut( (char _far *)out, &col, (int *)&sz );
			while ( out != cp ) {
			      curOfs++;
			      out++;
			      }
			}
		     break;
		default :
		     *out++ = c;
		     col++;
		     curOfs++;
		     break;
		}
	  }
       if ( flag ) {
	  col++;
	  *out++ = ' ';
	  curOfs++;
	  sz++;
	  flag ^= flag;
	  }
       ++sz;
       }
 *out++ = '\0';
 *out = '\0';
 *lines = row+1;
 return( sz );
}
