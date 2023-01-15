
typedef struct CODE_WORD {
	char name[30];
	int  val;
	} CODE_WORD;

typedef struct CWDO {
	char name[30];
	char *out;
	int (*df)( FILE *in, FILE *out, CODE_WORD *cwp, char *s );
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



