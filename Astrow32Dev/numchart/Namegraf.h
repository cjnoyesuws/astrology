#ifndef _NAMEGRAF_H_
#define _NAMEGRAF_H_

typedef struct NG_LTR {
	char letter;
	char val;
	} NG_LTR;

typedef struct NG_NUM {
	short val;
	short mark;
	short number;
	} NG_NUM;


typedef struct NAMEGRF_ELE {
	short include;
	short age;
	short year;
	NG_NUM essence;
	NG_NUM pers_year;
	NG_NUM univ_year;
	NG_NUM pinacle;
	NG_NUM life_cycle;
	NG_LTR first;
	NG_LTR middle;
	NG_LTR last;
	} NAMEGRF_ELE;

typedef struct NAMEGRF_GRP {
	NAMEGRF_ELE at_birth[150];
	NAMEGRF_ELE current[150];
    NAMEGRF_ELE option1[150];
	NAMEGRF_ELE option2[150];
	} NAMEGRF_GRP;

extern NAMEGRF_GRP name_graphs;

#endif /* _NAMEGRAF_H_ */