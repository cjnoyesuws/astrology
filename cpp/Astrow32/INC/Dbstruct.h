#if (!defined(TRUE))
    #include "astro.h"
#endif

#if (!defined(O_NAME_WIDTH))
    #include "useri.h"
#endif

#if (!defined(NATAL_CH))
    #include "dataext.h"
#endif

#define L_WIDTH (COUNTRY_WIDTH+STATE_WIDTH+LOCATION_WIDTH + 4)
#define B_WIDTH (NAME_WIDTH+COUNTRY_WIDTH+STATE_WIDTH+LOCATION_WIDTH + 5)


#pragma pack(2)

typedef struct D_LOC_DB {     /* len is full length of data plus length */
	short len;              /* of buf[] array */
	short freer;
	DEG_MIN longitude;
	DEG_MIN latitude;                /* Binary Disk Representation */
	NUM time_zone;                   /* basic location database structure */
	NUM special_code;                /* Country State & Location */
	HRS hrs_offset;                  /* in buf 0 terminated with 00 */
	MINU min_offset;                 /* at end */
	char tzcodekey[5];
	char buf[L_WIDTH];
	} D_LOC_DB;


typedef struct D_BIRTH_DB {   /* len is full length of data plus length */
	short  len;              /* of buf[] array */
	short freer;
	short with_rect;        /* 0 in this case; */
	short sex;                        /* Binary Disk Representation */
	NUM  time_zone;                  /* birth database structure */
	NUM  special_code;               /* Name, Country State & Location */
	short am_pm;                      /* are in buf 0 terminated with 00 */
	AS_DATA birth_data;              /* at end */
	char tzcodekey[5];
	char buf[B_WIDTH];
	} D_BIRTH_DB;

typedef struct D_RBIRTH_DB {   /* len is full length of data plus length */
	short  len;              /* of buf[] array */
	short  freer;
	short with_rect;                  /* 1 in this case */
	short sex;                        /* Binary Disk Representation */
	NUM  time_zone;                  /* birth database structure */
	NUM  special_code;               /* Name, Country State & Location */
	short am_pm;                      /* are in buf 0 terminated with 00 */
	AS_DATA birth_data;              /* at end */
	char tzcodekey[5];
	RECT_DATA rect_data;
	char buf[B_WIDTH];
	} D_RBIRTH_DB;

typedef union DBR {
	D_RBIRTH_DB r;
	D_BIRTH_DB  n;
	} DBR;

#pragma pack()


