#ifndef TEXTDEF
#define TEXTDEF

enum file_status { CLOSED = 0, OPEN, MEMORY, DISCARDABLE };

#pragma pack(2)

typedef struct TXTPT {
        long  starts_at;
        short length;
        } TXTPT;

#pragma pack()

typedef struct TFIL {
	int fil;                   /* file handle for index */
	char name[150];            /* file name */
	HANDLE handle;       /* ems handle or xms handle */
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
#endif
#ifndef TCOMPILER
#if (!defined(CHARCONS_SEEN))
  #include "charcons.h"
#endif

#define PLANET_FILE      PLANET_FILE_name
#define HOUSE_FILE       HOUSE_FILE_name
#define ASPECT_FILE      ASPECT_FILE_name
#define SUMMARY_FILE     SUMMARY_FILE_name
#define COMPAT_HOUSES    COMPAT_HOUSES_name
#define COMPAT_SUMMARY   COMPAT_SUMMARY_name
#define TRANSITS_HOUSES  TRANSITS_HOUSES_name
#define TRANSITS_ASPECTS TRANSITS_ASPECTS_name
#define PROGRESS_ASPECTS PROGRESS_ASPECTS_name
#define SIGN_HOUSE_FILE  SIGN_HOUSE_FILE_name
#define COMPAT_ASPECTS   COMPAT_ASPECTS_name
#define MIDPOINT_SIGN    MIDPOINT_SIGN_name
#define ARABIC_SIGN      ARABIC_SIGN_name
#define ARABIC_HOUSE     ARABIC_HOUSE_name
#define ARABIC_ASPECTS   ARABIC_ASPECTS_name
#define FIXEDST_SIGN     FIXEDST_SIGN_name
#define FIXEDST_HOUSE    FIXEDST_HOUSE_name
#define FIXEDST_ASPECTS  FIXEDST_ASPECTS_name
#define SOLAR_PLANET      SOLAR_PLANET_name
#define SOLAR_HOUSE      SOLAR_HOUSE_name
#define SOLAR_ASPECT   SOLAR_ASPECT_name
#define CM_PLANET_FILE      CM_PLANET_FILE_name
#define CM_HOUSE_FILE       CM_HOUSE_FILE_name
#define CM_ASPECT_FILE      CM_ASPECT_FILE_name
#define CM_TRANSITS_HOUSES  CM_TRANSITS_HOUSES_name
#define CM_TRANSITS_ASPECTS CM_TRANSITS_ASPECTS_name

#include "textmanager.h"
#define get_transfer_text(c,r,f,s) (CTextManager::GetManager()->GetRegText((f),(r),(c),(s)))
#define get_transfer_text_asp(c,r,a,f,s) (CTextManager::GetManager()->GetAspText((f),(c),(r),(a),(s)))
#define open_files(f) (CTextManager::GetManager()->OpenText(f))
#define open_asp_files(f) (CTextManager::GetManager()->OpenAspectsText(f))
#define close_files(n) (CTextManager::GetManager()->CloseText(n))
#define close_files_asp(n) (CTextManager::GetManager()->CloseAspText(n))
#define tb_open_file(p) (CTextManager::GetManager()->OpenReportText(p))
#define tb_close_table(n) (CTextManager::GetManager()->CloseReport(n))
#define tb_get_text(r,n,i) (CTextManager::GetManager()->GetReportText((r),(n),(i)))
#define tb_write_text(r,n,i,s) (CTextManager::GetManager()->GetReportText((r),(n),(i), (s)))



#endif
