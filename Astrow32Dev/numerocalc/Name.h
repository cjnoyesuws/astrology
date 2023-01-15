#ifndef _NAME_____H_
#define _NAME_____H_

typedef struct NAME_NUM {
	short first;
	short middle;
	short last;
	short total;
	short test;
	} NAME_NUM;

typedef struct INCL_TABLE {
	short table[10];
	short karm_count;
	short karm_lesn[7];
	} INCL_TABLE;

typedef struct NAME_EXPR_PLANES {
	short physical;
	short mental;
	short emotional;
	short intuitive;
	short dual;
	short inspired;
	short balanced;
	} NAME_EXPR_PLANES;

typedef struct NAME_ELEMENTS {
	short fire;
	short water;
	short air;
	short earth;
	} NAME_ELEMENTS;

typedef struct NAME_NUMBER {
	short include;
    NAME_NUM expression;
	NAME_NUM motivation;
	NAME_NUM inner_self;
	INCL_TABLE inclusion_tbl;
	NAME_EXPR_PLANES expression_planes;
	NAME_ELEMENTS elements;
	short traits[9];
	} NAME_NUMBER;


typedef struct LOTT_NAME {
	NAME_NUM at_birth;
	NAME_NUM current;
	} LOTT_NAME;

typedef struct NAME_NUMB_GROUP {
	NAME_NUMBER at_birth;
	NAME_NUMBER current;
	NAME_NUMBER option1;
    NAME_NUMBER option2;
	} NAME_NUMB_GROUP;

extern NAME_NUMB_GROUP name_numbers;

#endif /* _NAME_____H_ */