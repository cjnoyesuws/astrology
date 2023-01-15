#ifndef _DATATYPEHOLDER_H_
#define _DATATYPEHOLDER_H_ 

#define INTTYPE   0
#define STRTYPE   1
#define DBLTYPE   2
#define DATETYPE  3

typedef union DataTypes {
		int int_data;
		CString *str_data;
		COleDateTime *date_data;
		double       dbl_data;
	} DataTypes;

typedef struct DataTypeHolder {
	int data_type;
	char *field_name;
    DataTypes data;
} DataTypeHolder;

#endif /* _DATATYPEHOLDER_H_ */