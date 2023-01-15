#ifndef _TABLEPTR_H__
#define _TABLEPTR_H__

/* 09/10/92  Modified for C++ Windows */

enum tb_file_status {  CLOSED = 0, MEM };

typedef struct TBLFIL {
	int fil;                      /* file handle for index */
	char name[9];                 /* file name */
	short end;                      /* last element */
	short start;                    /* first element */
	short *index;                   /* the index itself */
	char  *text;                  /* The data itself */
	enum tb_file_status nd_open;  /* mem, ems, xms, closed */
	enum tb_file_status tb_open;  /* mem, ems, emsst closed */
	} TBLFIL;

#if (!defined(CHARCONS_SEEN))
  #include "charcons.h"
#endif

#endif /* _TABLEPTR_H__  */
