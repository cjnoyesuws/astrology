#ifndef _LETTRTYP_H_
#define _LETTRTYP_H_

#define VOWELS    "AaEeOoIiUu"
#define CONSONS   "rtpscdfmnghjklbvxqzRTPSCDFNGHMJKLBVXQZ"


#define NOTYPE    0
#define VOWEL     1
#define CONSON    2
#define YVOWEL    1
#define YCONSO    2
#define WVOWEL    1
#define WCONSO    2
#define DIGIT     3
#define LTERR     -1


extern short letter_type( char pre, char letter, char post );
extern char letter_val( unsigned char c );
extern short letter_val_str( char *str, char *buf, int maxlen );
extern short letter_type_val_str( char *str, char *buf, short type, short maxlen );
extern short add_buf( char *buf, short val );
extern short string_val( char *str, short red, short start_point, short *test );
extern short string_type_val( char *str, short type, short red, short start_point, short *test );
extern short str_add_reduc( char *str1, char *str2, char *str3, short *test );
extern short str_add_reduc_type( char *str1, char *str2, char *str3, short type, short *test );



#endif /* _LETTRTYP_H_ */