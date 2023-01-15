
typedef struct CODE_WORD {
	TCHAR name[30];
	int  val;
	} CODE_WORD;

typedef struct CWDO {
	TCHAR name[30];
	TCHAR *out;
	int (*df)( Strbuff &in, Strbuff &out, CODE_WORD *cwp, TCHAR *s );
	} CWDO;


#define  REOF   -1
#define  ROBRA  -2
#define  RCBRA  -3
#define  RCODE  -4
#define  REOL   -5

typedef struct STATE {
	int map_caps;
	int map_inv;
	int hi_char;
	int bold;
	int underscore;
	int head;
	int size;
	} STATE;



