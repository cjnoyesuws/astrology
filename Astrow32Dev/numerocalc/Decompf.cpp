#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "attrib.h"
#include "errors.fns"
#include "output.fns"
#include <assert.h>
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"


void TextConvDriver::initDecomp( int wid )
{
 if ( wid < 1800 )
    wid /= 10;
 col = 0;
 head_mode = 0;
 pTabs->init( wid, mul, div, 0 );
 width = wid;
}

/* decompression for text files using words.c word array */

extern char * word_array[32];

/* Function used to move strings into the out buffer, and update the size
   of the copy as well. Returns a pointer to the end of the copy */

char *TextConvDriver::moveStr( unsigned char *in, unsigned char *out, unsigned int *sz )
{
 register unsigned s = *sz;
 register unsigned char *op = out;

 while ( *op++ = *in++ ) {
       col++;
       s++;
       }
 *sz = s-1;
 return( (LPSTR)op-1 );
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

unsigned int TextConvDriver::decompress( char *outbuf, unsigned out_size, int *lines, int mode )
{
 register unsigned char *out = (unsigned char *)outbuf;
 unsigned char *cp, c, op;
 unsigned char *sp = NULL;
 unsigned sz = 0, os = out_size - 10;
 int flag = 0, b, spcol = 0, row = 0, t;
 long xw;

 *lines = 0;
 if ( outbuf == NULL || out_size == 0 ) /* no space allocated then return */
    return( 0 );
 else if ( feof(istream) )
	 return( 0 );
 sp = NULL;
 spcol = 0;
 while ( (b = getc(istream)) != EOF && sz <= os ) {
       c = (unsigned char)b;
       if ( c > (unsigned char) '\x80' ) {
	  c &= 127;
	  flag = 1;
	  }
       if ( isalnum( c ) ) {
	  *out++ = c;
	  col++;
	  }
       else if ( c != ' ' && c != '\n' && c < ' ' )
	  out = (unsigned char *)moveStr( (unsigned char *)word_array[c], out, &sz );
       else {
	  switch( c ) {
		case ' ' :
		     sp = out;
		     spcol = col;
		     col++;
		     *out++ = ' ';
		     break;
		case (unsigned char) '\x80' :
		case '\n' :
		     sp = NULL;
		     spcol =  0;
		     pTabs->resetTab();
		     *out++ = F_HARDCR;
		     row++;
		     col = 0;
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
			out = (unsigned char *) tabSet( (char *)cp, (int *) &sz );
		     else {
			if ( out != cp ) {
			   if ( *(out + 1) == F_BINARY )
			      out = cp;
			   else {
			      while ( out++ != cp )
				 col++;
			       }
			   }
			}
		     break;
		case '{' :
		     *out++ = F_STARTBD;
		     break;
		case '}' :
		     *out++ = F_ENDBD;
		     break;
		case '<' :
		     *out++ = F_STARTUL;
		     break;
		case '>' :
		     *out++ = F_ENDUL;
		     break;
		case '[' :  /* change to the head font */
		     head_mode = 1;
		     *out++ = F_STARTHD;
		     t = col;
                     break;
		case ']' :  /* change to the text font */
		     head_mode = 0;
		     *out++ = F_ENDHD;
                     *out++ = F_BINARY;
		     *out++ = 2;        /* next two bytes =
				      indent to center text */
		     t = (width - col);
                     t /= 2;
		     memcpy( out, &t, 2 );
		     out+=2;
		     sz+= 4;
		     break;
		case '|' :
		     if ( out_size - sz < 100 ) {
			ungetc( c, istream );
			*out = '\0';
			*lines = row+1;
			return( sz++ );
			}
		     else {
			sp = NULL;
			spcol = 0;
			out = (unsigned char *)tabOut( (char *)out, &col, (int *)&sz );
			}
		     break;
		default :
		     *out++ = c;
		     col++;
		     break;
		}
	  }
       if ( flag ) {
	  sp = out;
	  spcol = col;
	  col++;
	  *out++ = ' ';
	  sz++;
	  flag ^= flag;
	  }
       ++sz;
       if ( col >= width && sp != NULL ) {
	  *sp = F_SOFTCR;
	  if ( head_mode ) {
	     memmove( sp+7, sp+1, out-sp+1 );
	     *sp++ = F_ENDHD;
	     *sp++ = F_BINARY;
	     *sp++ = 2; /* next two bytes =
			   left indent for text */
	     t = (width - spcol);
	     memcpy( sp, &t, 2 );
	     sp+=2;
	     *sp++ = F_SOFTCR;
	     *sp++ = F_STARTHD;
	     sz+= 5;
	     out+=6;
	     }
	  col = col - spcol;
	  sp = NULL;
	  row++;
	  spcol = 0;
	  }
       op = c;
       }
 *out++ = '\0';
 *out = '\0';
 *lines = row+1;
 return( sz );
}
