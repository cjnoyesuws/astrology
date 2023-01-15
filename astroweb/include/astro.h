/* Header file for ASTRO Version 2.0 */

#ifndef ASTRO____H__
#define ASTRO____H__

// Edited for Win32
/* MANIFEST CONSTANTS */

/* basic */
#ifndef FALSE
#define   FALSE  0
#define   TRUE   1
#endif
#ifndef NULL
#include <stdlib.h>
#endif
#ifndef ENOMEM
#include <errno.h>
#endif
#ifndef STDIO_DEFINED
#include <stdio.h>
#endif
#if (_MSC_VER >= 600)
#define _CDECL _cdecl
#else
//#define _CDECL cdecl
//#define _cdecl cdecl
#endif

#ifndef WINVER
typedef short BOOL;
#endif

/* system constants */
#define    ASCEND     0
#define    RISING     0
#define    SUN        1
#define    MOON       2
#define    MERCURY    3
#define    VENUS      4
#define    MARS       5
#define    JUPITER    6
#define    SATURN     7
#define    URANUS     8
#define    NEPTUNE    9
#define    PLUTO      10
#define    NORTH_NODE 11
#define    SOUTH_NODE 12
#define    MED_COELI  13
#define    IM_COELI   14
#define    PART_FORTU 15
#define    VERTEX     16
#define    EAST_POINT 17
#define    CUPIDO     18
#define    HADES      19
#define    KRONOS     20
#define    APOLLON    21
#define    ADMETOS    22
#define    VULKANUS   23
#define    POSIDON    24
#define    CERES      25
#define    PALLAS     26
#define    JUNO       27
#define    VESTA      28
#define    CHIRON     29
#define    HOUSE_1    30  /* FOR ASPECT AND MIDPOINT PURPOSES */
#define    HOUSE_12   41

#define    ARIES      0
#define    TAURUS     1
#define    GEMINI     2
#define    CANCER     3
#define    LEO        4
#define    VIRGO      5
#define    LIBRA      6
#define    SCORPIO    7
#define    SAGITARIUS 8
#define    CAPRICORN  9
#define    AQUARIUS   10
#define    PISCES     11

/* a few global types */
#define DEGR short /* degrees */
#define MINU short /* minutes */
#define STAT short /* error no error like BOOL */
#define LMIN long  /* long minutes */
#define NUM short  /* number from 0 to ? like enum */
#define BITS unsigned int /* bitfield type */
#define HRS short  /* number of hours as unit */
#define COUNT short /* counting variable */
#define UDEGR unsigned short /* degrees in unsigned */

#ifndef _MSC_VER
#endif



struct ASPEC {
    short aspect;    /* code for aspect */
    short planet;    /* planet aspect is with */
    short orb;       /* degrees of orb */
    };


struct MIDPT {
	short   total_minutes;
    short   sign;
    short  minor_degrees;
	short   minor_minutes;
	short   cusp;
    short   house;
	short  house_cusp;     /* is planet on house cusp */
	short  intercepted;
    short   second_planet;
    short no_aspect;
    ASPEC *aspectr;
    short no_alt_aspect;
    ASPEC *altaspectr;
    };

struct AS_INF {
	short  minutes_total;  /* total number of minutes */
	short  graph_minutes;
    short   sign;           /* sign the planet is in */
    short   cusp;           /* is planet on cusp if so which one */
    short  degree_minor;   /* degrees minor 0-30 within sign */
	short  minutes_minor;  /* minutes 0-60 */
	short   house;          /* house planet is in */
	short  house_cusp;     /* is planet on house cusp */
	short  intercepted;    /* is the sign interceped */
    short  retrograde;     /* is planet in retrograde motion */
	short  calced;         /* was this calculated */
    unsigned int  misc_code;      /* miscellaneous coded information */
    short no_aspects;     /* count of total aspects */
    ASPEC *aspectr;       /* pointer to block of ASPEC */
    short no_midpt;       /* count of midpoints */
    MIDPT *midptr;        /* pointer to block of MIDPT */
    double longitude;
	double declination;
	short  dec_degrees;
	short  dec_minutes_minor;
	short  dec_minutes_total;
	char formatted[12];
};

struct TIM {
    short hours;   /* basic time structure */
    short minutes;
    short seconds;
    };

struct DATES {  /* basic date structure */
    short month;
    short day;
    short year;
    };

struct DEG_MIN {      /* basic structure for exact degrees/minutes */
    short  degrees;
    short minutes;
	char dir;      /* east or west north or south */
#ifndef _MSC_VER
	char dummy;    /* for Borland Refuses to padd this structure out. */
#endif
        };

struct AS_DATA {
    DEG_MIN latitude;
    DEG_MIN longitude;
    DATES   birth_date;
    TIM     birth_time;
    short local_adjust;
    short local_minutes;
    DATES   noon_date;
    TIM     noon_time;
	TIM     sidereal;
    short hour_adjust;
	short    minutes_adjust;
    };
#ifndef _MSC_VER
#else
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505; disable : 4005; disable : 4995; disable : 4313; disable : 4091; disable : 4101 )
#endif

extern AS_INF birth_inf[], alt_inf[];
extern AS_INF house_inf[], alt_house_inf[];

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
extern short house_cusps[],alt_cusps[];
};

#endif
extern DATES *date_ptr;
extern AS_INF **trans_ptr;
extern AS_INF * moon_series, * prog, * prog_moon_series;
extern short birth_ok, birth_rect_ok, comp_ok, comp_rect_ok,
    trans_ok, trans_data_ok, prog_ok;

#define sign(x) ((x)/1800)                    /* x is total minutes */
#define minor_degrees(x) (((x)/60)%30)        /* x is total minutes */
#define minor_minutes(x) ((x)%60)             /* x is total minutes */
#define decanates(x) ((x)/10)                 /* x is minor degrees */
#endif /* ASTRO____H__ */



