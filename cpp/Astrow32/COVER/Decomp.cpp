#include "stdafx.h"
#include <errno.h>
#include <assert.h>
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "inifile.hpp"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
extern char *word_array[];

/* decompression for text files using words.c word array */

/* function to decompress string compressed in buildtxt and 3dbldtxt
   using compress function. Uses common word_array in words.c. Each char
   in inbuf between chr(32) - chr(127) is copied to outbuf verbatim. If a
   char (chr(32)|128) - (chr(127)|128) that char has has a word space
   compressed into it. The (char&127) is copied to outbuf, and followed
   by a space. If a char chr(1) - chr(31) is found, word_array[char] is
   copied to the string. If a char (chr(1)|128) - (chr(31)|128) is
   found word_array[char] is copied to the string, followed by a space.
   size represents allocated size of outbuf. Size should be approx
   150% size allocated for inbuf. The number of chars in buffer is
   returned for success. chr(128) is used for embedded (sticky) spaces.
   The sticky spaces allow ASTRO to read an entire block of text including
   groups of lines which need to stay together, and them rewrap them
   after the fact as the chr(128)'s are converted to '\n's and '\n's are
   respected by text_wrap(). Extended characters are not supported at
   this time but could be supported by using the chr(127) as an escape
   character indicating an extended char. ie the chr(127)chr(135) pair
   would indicate the use of the chr(135) char in the text stream */

int decompress( char *inbuf, char **outbuf, int in_size, int *out_size, int notabs )
{
 int ansi=0;
 char buf[5];
 register unsigned char *in = (unsigned char *)inbuf,
       *out = (unsigned char *)*outbuf;
 unsigned char *save;
 unsigned sz = 0, os = *out_size - 10, lenoff=0;

 if ( *outbuf == (char *)0 || *out_size == 0 ) /* no space allocated then return */
    return( 0 );
 else if ( inbuf == (char *)0 )  /* no stuff to copy */
	 return( 0 );
 else if ( *inbuf == '\0' ) /* ditto */
    return( 0 );
 SexCodes *pSxc = new SexCodes;
 Tabs *pTabs = new Tabs();
 pTabs->init(80);
 ansi = (int) AfxGetApp()->GetProfileInt( Misc_SEC, "AnsiText", ansi );
 while ( *in && sz <= os ) {
       if ( (*in == '^' && (!notabs)) || (*in == '^' && *(in+1) != '@' && notabs)) {
	  int len = 0;
	  char *cp = (char *)out;
	  char *rt;
	  save = in;
	  save++;
	  rt = pSxc->doCodes( NULL, &cp, &len, pTabs, (char **)&(++in) );
	  lenoff = in-save;
	  in = save;
	  if ( *in=='1' || *in=='2' )
	     in = (unsigned char *)rt;
	  else
	     in++;
	  if ( len ) {
	     out += len;
	     sz += len + 1;
	     out++;
	     }
	  }
       else if ( *in == 128 ) {
	  *out++ = '\n';
	  ++in;
	  if ( *in == '\r' )
		  in+=2;
	  }
       else if ( *in == '\n' ) {
	  *out++ = '\r';
	  *out++ = '\n';
	  ++sz;
	  in++;
	  }
       else if ( *in & 96 ) {     /* it's a regular char unpack word space */
	  if ( *in & 128 ) {      /* if neccessary */
	     if ( *in == 254 ) {
		*out++ = ' ';
		in++;
		}
	     else {
		*out++ = *in & 127;
		*out++ = ' ';     /* unpack the word space */
		++sz;
		in++;
		}
	     }
	  else {
	     if ( *in == '~' ) {
	        if ( !ansi ) {
	           buf[0] = *(in+1);
	           OemToCharBuff( buf, &buf[3], 1 );
	           *out++=buf[3];
	           }
            else
	           *out++ = *(in+1);
		    in++;
		    }
	     else
		*out++ = *in++;
	     }
	  }

       else {                              /* use the string put in space if nec */
	  save = (unsigned char *)in; /* use save to keep in & out registers */
	  in = (unsigned char *)word_array[*in & 31];
	  while ( *out++ = *in++ )
		++sz;
	  in = save;
	  if ( *in & 128 )
	     *(out-1) = ' ';
	  else {
	     --out;
	     --sz;
	     }
	  ++in;
	  }
       ++sz;
       }
 *out = '\0';
 delete pSxc;
 delete pTabs;
 return( sz+1 );
}
