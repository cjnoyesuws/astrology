#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <strstream>

extern char *word_array[32];
extern char word_lens[];
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

#define word(n) word_array[n]

/* function to traverse list word_array[] and find word if found */

int find_word( char *word )
{
 int i;

 for ( i = 1; i < 32; ++i ) {
     if ( !strncmp( word, word_array[i], word_lens[i] ) && i!=0x0d )
	return( i );
     }
 return( 0 );
}

/* function to compress a string into a shorter string. Works by folding
   spaces onto char before by oring 128 with char before. If a section
   of string is found in list word_array[] then the offset into that
   array is placed in the string instead of word found. If that word is
   followed by a space, then that index is ored with 128. Returns number
   of characters saved. A chr(128) indicates a "sticky" line_feed that
   will be converted to a new_line char '\n' during decompression. This
   allows whole groups of paragraphs and lines to be treated as logical
   chunks. extended chars could be represented using chr(127) where
   chr(127)chr(135) represents a chr(135) in the text stream. */


int compress_string_out( unsigned char *in_str, unsigned char *out_str )
{
 unsigned char *in = (unsigned char *)in_str, *out = (unsigned char *)out_str, *save;
 int counter = 0, len, found, l;

 while ( *in ) {
       if ( *in == '\t' ) {
	      *in = '|';
	      }
      if ( *in == '\x0d' ) {
	     counter++;
	     *in++;
	     }
      if ( ( found = find_word( (char *)in ) ) == 0 ) {
	     if ( *in == '~' || *in == '^' ) {
	        *out++ = *in++;
	        *out++ = *in++;
	        if ( *in == ' ' )
		       *out++ = *in++;
	        }
	    else if ( *in >= '~' && *in != (unsigned char)'\x80' ) {
	        *out++ = '~';
	        *out++ = *in++;
	        if ( *in == ' ' )
		    *out++ = *in++;
	        }
	   else if ( *in == ' ' && in != (unsigned char *)in_str ) {
	        *(out-1) |= 128;
	        in++;
	        counter++;
	        }
	   else
	       *out++ = *in++;
	  }
       else {
	     *out = (char) found;
	     in += word_lens[found];
	     counter += word_lens[found]-1;
	     if ( *in == ' ' ) {
	        *out |= 128;
	        in++;
	        counter++;
	        }
	     out++;
	     }
       }
 *out = '\0';
 return( counter );
}
		   

int CompressStrstreamFile(istrstream &in, FILE *out )
{
int len, outlen;
	
unsigned char *buf = new unsigned char[20000];
unsigned char *outb = new unsigned char[20000];

while ( !in.eof() && in.good() ) {
      in.getline(buf,19999);
	  len = strlen((const char *)buf);
	  compress_string_out( buf, outb );
	  fwrite(outb,strlen((const char *)outb),1,out);
	  fputc('\n',out);
      }
delete buf;
delete outb;
return(1);
}