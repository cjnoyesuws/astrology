/* general header file for database */
/* user must include astro.h and useri.h first */
#include "asbplus.h"
//#include "setup.h"
#include "charcons.h"

#define FAIL     -1
#define SUCCEED  0

extern IX_DESC *loc_index_file, *birth_i, *pop_list;
extern long loc_r, birth_r;
extern short loc_l, birth_l;
extern char db_key[];
extern char db_name[];
#define LOCATION_INDEX   (char *) set_path( LOCATION_INDEX_name, DATABASE_F )
#define LOCATION_DATA    (char *) set_path( LOCATION_DATA_name, DATABASE_F )
#define BIRTHBAS_INDEX   (char *) set_path( BIRTHBAS_INDEX_name, DATABASE_F )
#define BIRTHBAS_DATA    (char *) set_path( BIRTHBAS_DATA_name, DATABASE_F )
#define LOCATION_POPUP   (char *) set_path( LOCATION_POPUP_name, DATABASE_F )
#define BIRTHBAS_POPUP   (char *) set_path( BIRTHBAS_POPUP_name, DATABASE_F )
#define LOC_POPUP_INDEX  (char *) set_path( LOC_POPUP_INDEX_name, DATABASE_F )







