#ifndef _BUILDER__HPP_
#define _BUILDER__HPP_

typedef struct TXTPT {
	long  starts_at;
	short length;
	} TXTPT;


extern CATCHBUF j;

typedef struct LST {
	char  symbol[18];
	int   value;
	int   col_used;
	} LST;

typedef struct RLST {
	char  symbol[35];
	int   value;
	int   col_used;
	} RLST;

typedef struct VLST {
	char  symbol[35];
	int   value;
	int   type_code;
	} VLST;

extern int compress_string( char *, char *);

#define END_OF_ARRAY 39
#define FAIL    0
#define SUCCEED 1
#define IN_BUF_SIZE 10000

extern LST symbols[];
extern RLST rsymbols[];

extern int num_cols, num_rows, num_symbols;
extern unsigned int bytes_saved;

extern char *buffer;
extern char *comp_buf;
extern char *inbuf;

#endif /* _BUILDER__HPP_ */
