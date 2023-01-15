#include <stdio.h>
/* common c file for buildtxt 3dbldtxt and astro. */

/* this is the array that is used for compression and decompression.
   It is used to do a limited, basic key word replacement. Accessed
   using 31 ascii positions, i.e. chr(0) = NULL, chr(31) = "as",
   etc. Each word or fragment is represented by one character. If a char
   in range ([1-31]|128) then it represents the string indexed by [1-31]
   followed by a space. */

char * word_array[32]  =  {
	"",  "     ",  "   ", "interest",  "companion",
	"Your",  "your",  "will",  "This",  "tion",  "\n",
	"have",  "You",  " ", "the",  "and",  "ing",  "are",
	"for",  "or",  "ti",  "in",  "th",  "or",  "en",
	"el",  "of",  "ea",  "ou",  "es",  "is",  "as"
	};

/* this is the array that is used for compression and decompression.
   It is used to do a limited, basic key word replacement. Accessed
   using 31 ascii positions, i.e. chr(0) = NULL, chr(31) = "as",
   etc. Each word or fragment is represented by one character. If a char
   in range ([1-31]|128) then it represents the string indexed by [1-31]
   followed by a space. */

char word_lens[32] = { 0, 5, 3, 8, 9, 4, 4, 4, 4, 4, 1, 4, 3, 1, 3,
	3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

