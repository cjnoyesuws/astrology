#ifndef _NUMBR____H_
#define _NUMBR____H_
#ifndef _CHARTINF_H_
#include "chartinf.h"
#endif

#define CHALMIN1 0
#define CHALMIN2 1
#define CHALMAJR 2
#define MAXCAL   36

typedef struct DTN {
	short date;
	short time;
	short dow_doy;
	} DTN;

typedef struct TNUM {
	short num;
	short test;
	short start;
	short end;
	} TNUM;

typedef struct NUM {
	short raw;
	short red;
	short test;
	} NUM;

typedef struct CALDATE {
	DATES d;
	short  calendar[32];
	} CALDATE;

typedef struct NUMBERS {
	NUM destiny;
	NUM sign;
	NUM degrees;
	NUM minor;
	short dest_direct;
	TNUM life_cycles[3];
	TNUM turn_point[4];
	short  challenges[3];
	DATES personal;
	DATES universal;
	} NUMBERS;

typedef struct CALENDARS {
	short cal_cnt;
	DATES start;
	DATES end;
	CALDATE cal[MAXCAL];
	} CALENDARS;

extern NUMBERS date_numbers;

#endif /* _NUMBR____H_ */