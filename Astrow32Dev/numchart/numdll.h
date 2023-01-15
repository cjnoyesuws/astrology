
#define PERSON_FILE    1
#define NUMERIC_FILE   2
#define NAMEGRAPH_FILE 3
#define NUMGRAPH_FILE  4


#define _REG_   0
#define _HEAD_  1
#define _BOLD_  2
#define _UITAL_  3

extern char data_path[];

void  SetGroupStartEnd( short st, short ed );
extern void SetWYVowel( short s );
extern void SetFileInfo( FILE_ID *p );
extern void SetChartInfoData( CHART_INFO *h );
extern int CompileReport( int rep, char * n1_file );
extern int convert( char *in, FILE *out );
