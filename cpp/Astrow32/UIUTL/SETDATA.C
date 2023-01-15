#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "astro.h"
#include "useri.h"
#include "dbstruct.h"
#include "DBDLL.h"


int SetDBName(int file, LPSTR name, int sex)
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );
 strcpy( dbdlldata[file].birth.name, name );
 dbdlldata[file].birth.sex = sex;
 return( 1 );
}

int SetDBBirthDate(int file, int m, int d, int y )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );
 dbdlldata[file].birth.birth_date.months = m;
 dbdlldata[file].birth.birth_date.days = d;
 dbdlldata[file].birth.birth_date.years = y;
 return( 1 );
}

int SetDBBirthTime(int file, int h, int m, int pm )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );
 dbdlldata[file].birth.birth_time.hours = m;
 dbdlldata[file].birth.birth_time.minutes = d;
 dbdlldata[file].birth.birth_time.am_pm = pm;
 return( 1 );
}


int SetDBName(int file, LPSTR name, int sex)
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );
 strcpy( dbdlldata[file].birth.name, name );
 dbdlldata[file].birth.sex = sex;
 return( 1 );
}

typedef struct LOC_DB {                /* basic location database structure */
	char country[COUNTRY_WIDTH+1];
	char state[STATE_WIDTH+1];
	char location[LOCATION_WIDTH+1];
	DEG_MIN longitude;
	DEG_MIN latitude;
	NUM time_zone;
	NUM special_code;
	HRS hrs_offset;
	MINU min_offset;
	char tzcodekey[5];
	} LOC_DB;

int SetDBLoc(int file, LPSTR country, LPSTR state LPSTR loc )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );
 strcpy( dbdlldata[file].birth.name, name );
 return( 1 );
}


int SetDB(int file, )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );

 return( 1 );
}

int SetDB(int file, )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );

 return( 1 );
}

int SetDB(int file, )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );

 return( 1 );
}

int SetDB(int file, )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );

 return( 1 );
}

int SetDB(int file, )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );

 return( 1 );
}

int SetDB(int file, )
{
 if ( file >= dbdllfilecount || dbdlldata[file].stream == NULL )
    return( 0 );

 return( 1 );
}

