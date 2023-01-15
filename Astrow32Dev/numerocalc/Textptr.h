#pragma pack(2)

enum file_status { CLOSED = 0, OPEN, MEMORY, DISCARDABLE };

typedef struct TXTPT {
        long  starts_at;
        short length;
        } TXTPT;

typedef struct TFIL {
	int fil;                   /* file handle for index */
	char name[150];            /* file name */
#if (WINVER >= 0x400)
	void * handle;
#else
	unsigned int handle;       /* ems handle or xms handle */
#endif	
	enum file_status is_open;  /* 1 open, 0 closed, 3 discardable */
	} TFIL;

typedef struct TXTFIL {
	char base[9];    /* Base Name For file */
	TFIL txptp;      /* info for the index */
	TFIL textp;	 /* info for the text file */
	short rows;	 /* number of rows for index */
    short cols;        /* number of cols for index */
    short deep;        /* used only for aspects number of above deep */
	short mode;	 /* 2 for reg 3 for aspect */
	TXTPT *ptr;  /* NULL for on disk, base ptr for in memory index */
	char  *text; /* NULL for on disk  base ptr for in memory text */
	TXTPT txtpt;	 /* local txtpt to use for reference. */
        } TXTFIL;

#pragma pack()

#ifndef TCOMPILER
#if (!defined(CHARCONS_SEEN))
  #include "charcons.h"
#endif

#define get_transfer_text(c,r,f,s) get_transfer_text_asp((c),(r),0,(f),(s))
#define open_files(f) x_open_files((f),2)
#define open_asp_files(f) x_open_files((f),3)

#define TEXT_FILE_NAME "N1TEXT"

extern short num_to_arry_offset( short num );
extern short get_text( short row, short col, short file_num, FILE *stream );
extern short get_gnt( short col, short file_num, FILE *stream  );




#endif
