#ifndef  _CHARTINF_H_
#define  _CHARTINF_H_                      

#if (WINVER >= 0x400)
#define DllExport __declspec( dllexport ) __cdecl 
#else
#define DllExport _far _pascal _export 
#endif

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

extern CHART_INFO chart_info_data;


typedef struct FILE_ID {
  char id[5];
  char fType[30];
  char comment[80];
  long text, birth, data;
  } FILE_ID;

extern FILE_ID file_info;

extern void chart_header_print( FILE *stream, CHART_INFO *cip );

extern short reduce_num( char *num_str, short *test );
extern short reduce_int( short num, short *test );
extern short add_ints_reduce( short num1, short num2, short num3, short *test  );
extern short add_digits_reduce( short num1, short num2, short num3, short *test  );
extern short subtract_ints_reduce( short num1, short num2, short *test );

#define PERSON_FILE    1
#define NUMERIC_FILE   2
#define NAMEGRAPH_FILE 3
#define NUMGRAPH_FILE  4

#endif /* _CHARTINF_H_ */