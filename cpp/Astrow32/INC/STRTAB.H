
#define STRTABSLEN 60

typedef struct STR_TAB {
	char search[STRTABSLEN];
	unsigned char slen;
	char replace[STRTABSLEN];
	unsigned char rlen;
	} STR_TAB;

typedef struct CHREP {
    char ch[10];
    unsigned char len;
    } CHREP;
extern CHREP char_table[];
extern STR_TAB string_table[];
extern string_table_count;

