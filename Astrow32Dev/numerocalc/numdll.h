typedef struct NAME_REC {
  char first  [80];
  char middle [80];
  char last   [80];
  short include;
} NAME_REC;

typedef struct DATES {
  short month, day, year;
  short include;
  } DATES;

typedef struct CHART_INFO {
  char id[5];
  DATES birth_date;
  NAME_REC at_birth, current, opt1, opt2;
  } NUMEROLOGY_DATA;



typedef struct FILE_ID {
  char id[5];
  char fType[30];
  char comment[80];
  long text, birth, data;
  } FILE_ID;



#define PERSON_FILE    1
#define NUMERIC_FILE   2
#define NAMEGRAPH_FILE 3
#define NUMGRAPH_FILE  4


typedef struct FONT {
      char lfFaceName[40];
      int  lfHeight;
      int  lfWeight;
      int  lfItalic;
      int  lfUnderline;
      int  lfPitchAndFamily;
      } FONT;


#define _REG_   0
#define _HEAD_  1
#define _BOLD_  2
#define _UITAL_  3

#define _PITCH_ 0xff
#define _ISBOLD_  0x100
#define _UNDERLINE_  0x200
#define _ITALIC_ 0x400

#define EXP 

void EXP SetGroupStartEnd( short st, short ed );
extern void EXP SetWYVowel( short s );
extern void EXP SetFileInfo( FILE_ID *p );
extern void EXP SetChartInfoData( CHART_INFO *h );
extern int EXP CompileReport( int rep, LPSTR n1_file );
extern int EXP ConvertToRTF( char *in, char *out );
extern void EXP SetupRTFConvert( FONT *pFnt, ULONG *pClr, int lft, int wdt );