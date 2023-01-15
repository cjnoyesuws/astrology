#include "stdafx.h"
#include <string.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dbstruct.h"
#include "fptr.h"
#include "paths.hpp"
#include "assert.h"


/* function to take an	LOC_DB structure and turn it into a new disk
   structure type like we are now using. Note data pointed to by dldp,
   must be at least as large as LOC_DB to allow for the strings. */

int cvt_nlocdb_2_dsk( LOC_DB *ldp, D_LOC_DB *dldp )
{
 int cp = 0;
 int size;

 size = sizeof(D_LOC_DB) - L_WIDTH;

 dldp->freer = 0;
 memcpy( &dldp->longitude, &ldp->longitude,
		 (sizeof(DEG_MIN) * 2) + (4 * sizeof( short ) ));
 memset( &dldp->buf, 0, L_WIDTH );
 strcpy( &dldp->buf[cp], ldp->country);
 cp += strlen(ldp->country)+1;
 strcpy( &dldp->buf[cp], ldp->state);
 cp += strlen(ldp->state)+1;
 strcpy( &dldp->buf[cp], ldp->location);
 cp += strlen(ldp->location)+1;
 dldp->buf[cp++] = '\0';
 size += cp;
 if ( size & 1 )
    size++;
 dldp->len = size;
 return( size );
}

/* function to convert an BIRTH_DB like we are using now and converting
   it into its disk representation, which uses variable length strings.
   Note the structure pointed to by dbdp must be as large as bdp to allow
   for the strings */

int cvt_nbirthdb_2_dsk( BIRTH_DB *bdp, DBR *dbdp, RECT_DATA *rdp )
{
 char *buf;
 int cp = 0;
 int size;

 size = sizeof(D_BIRTH_DB) - B_WIDTH;
 dbdp->n.freer = 0;
 dbdp->n.birth_data = bdp->birth_data;
 dbdp->n.sex = bdp->sex;
 dbdp->n.time_zone = bdp->time_zone;
 dbdp->n.special_code = bdp->special_code;
 dbdp->n.am_pm = bdp->am_pm;
 memcpy( dbdp->n.tzcodekey, bdp->tzcodekey, 5 );
 if ( rdp != NULL && !rdp->birth_time_known ) {
    dbdp->r.rect_data = *rdp;
    dbdp->r.with_rect = 1;
    buf = dbdp->r.buf;
    size += sizeof( RECT_DATA );
    }
 else {
    dbdp->n.with_rect = 0;
    buf = dbdp->n.buf;
    }
 strcpy( &buf[cp], bdp->name);
 cp += strlen(bdp->name)+1;
 strcpy( &buf[cp], bdp->country);
 cp += strlen(bdp->country)+1;
 strcpy( &buf[cp], bdp->state);
 cp += strlen(bdp->state)+1;
 strcpy( &buf[cp], bdp->location);
 cp += strlen(bdp->location)+1;
 buf[cp++] = '\0';
 size += cp;
 if ( size & 1 )
    size++;
 dbdp->n.len = size;
 return( size );
}

/* function to take an structure type like we are now using and convert it to
   the in memory structure used. Note data pointed to by dldp,
   must be at least as large as LOC_DB to allow for the strings. */

LOC_DB *cvt_dsk_2_nlocdb( LOC_DB *ldp, D_LOC_DB *dldp )
{
 int cp = 0;

 memcpy( &ldp->longitude, &dldp->longitude,
		 (sizeof(DEG_MIN) * 2) + (4 * sizeof( short )) );
 strcpy( ldp->country, &dldp->buf[cp] );
 assert( sizeof( ldp->country ) > strlen( ldp->country ) );
 cp += strlen(ldp->country)+1;
 strcpy( ldp->state, &dldp->buf[cp] );
 cp += strlen(ldp->state)+1;
 assert( sizeof( ldp->state ) > strlen( ldp->state ) );
 strcpy( ldp->location, &dldp->buf[cp] );
 assert( sizeof( ldp->location ) > strlen( ldp->location ) );
 return( ldp );
}
/* function to convert the disk representation of a BIRTH_DB, which uses
   variable length strings. into an BIRTH_DB like we are using now.
   Note. the structure pointed to by dbdp must be as large as bdp to allow
   for the strings */

BIRTH_DB *cvt_dsk_2_nbirthdb( BIRTH_DB *bdp, DBR *dbdp, RECT_DATA *rdp )
{
 char *buf;
 int cp = 0;

 bdp->birth_data = dbdp->n.birth_data;
 bdp->sex = dbdp->n.sex;
 bdp->time_zone = dbdp->n.time_zone;
 bdp->special_code = dbdp->n.special_code;
 bdp->am_pm = dbdp->n.am_pm;
 memcpy( bdp->tzcodekey, dbdp->n.tzcodekey, 5 );
 if ( dbdp->n.with_rect && rdp != NULL ) {
    *rdp = dbdp->r.rect_data;
    buf = dbdp->r.buf;
    }
 else if ( !dbdp->n.with_rect && rdp != NULL ) {
    rdp->birth_time_known = 1;
    buf = dbdp->n.buf;
    }
 else if ( dbdp->n.with_rect && rdp == NULL )
    buf = dbdp->r.buf;
 else
    buf = dbdp->n.buf;
 strcpy( bdp->name, &buf[cp]);
 cp += strlen(bdp->name)+1;
 assert( sizeof( bdp->name ) > strlen( bdp->name ) );
 strcpy( bdp->country, &buf[cp] );
 cp += strlen(bdp->country)+1;
 assert( sizeof( bdp->country ) > strlen( bdp->country ) );
 strcpy( bdp->state, &buf[cp]);
 cp += strlen(bdp->state)+1;
 assert( sizeof( bdp->state ) > strlen( bdp->state ) );
 strcpy( bdp->location, &buf[cp] );
 assert( sizeof( bdp->location ) > strlen( bdp->location ) );
 return( bdp  );
}


O_FILE_DB *cvt_filedb_2_ofiledb( W16_FILE_DB *fdp, O_FILE_DB *ofdp )
{
 cvt_win_2_filedb( fdp );
 strncpy( ofdp->name, fdp->name, O_NAME_WIDTH+2 );
 ofdp->name[O_NAME_WIDTH+2] = '\0';
 strncpy( ofdp->comment, fdp->comment, O_COMMENT_WIDTH );
 ofdp->comment[O_COMMENT_WIDTH] = '\0';
 strcpy( ofdp->file_name, fdp->file_name );
 ofdp->type = fdp->type;
 ofdp->file_num = fdp->file_num;
 return( ofdp );
}

W16_FILE_DB *cvt_ofiledb_2_nfiledb( W16_FILE_DB *nfdp, O_FILE_DB *fdp )
{
 fdp->name[O_NAME_WIDTH]= '\0';
 strcpy( nfdp->name, fdp->name );
 fdp->comment[O_COMMENT_WIDTH]= '\0';
 strcpy( nfdp->comment, fdp->comment );
 fdp->file_name[12]= '\0';
 strcpy( nfdp->file_name, fdp->file_name );
 nfdp->type = fdp->type;
 nfdp->file_num = fdp->file_num;
 if ( nfdp->type > 12 )
    nfdp->type += 3;
 nfdp->has_comments = 0;
 nfdp->has_cover = 0;
 nfdp->arch_dsk = 0;
 nfdp->selected = 0;
 return( cvt_filedb_2_win( nfdp ) );
}


W16_FILE_DB *cvt_filedb_2_win( W16_FILE_DB *fdp )
{
 char buf[NAME_WIDTH+3];

 OemToAnsi(fdp->name, buf );
 strcpy(fdp->name, buf );
 OemToAnsi(fdp->comment, buf );
 strcpy(fdp->comment, buf );

 OemToAnsi(fdp->file_name, buf );
 strcpy(fdp->file_name, buf );
 fdp->arch_dsk = 0;
 fdp->selected = 0;
 return( fdp );
}

W16_FILE_DB *cvt_win_2_filedb( W16_FILE_DB *fdp )
{
 char buf[NAME_WIDTH+3];

 AnsiToOem(fdp->name, buf );
 strcpy(fdp->name, buf );
 AnsiToOem(fdp->comment, buf );
 strcpy(fdp->comment, buf );
 AnsiToOem(fdp->file_name, buf );
 strcpy(fdp->file_name, buf );
 fdp->arch_dsk = 0;
 fdp->selected = 0;
 return( fdp );
}

BIRTH_DB *BirthCvtToWin( BIRTH_DB *p )
{
 char buf[NAME_WIDTH+1];

 if ( !strlen( p->name ) || strlen( p->name ) > NAME_WIDTH ) {
    memset( p, 0, sizeof( BIRTH_DB ) );
    return( p );
    }
 OemToAnsi(p->name, buf);
 strcpy(p->name, buf );
 OemToAnsi(p->country, buf);
 strcpy(p->country, buf );
 OemToAnsi(p->state, buf);
 strcpy(p->state, buf );
 OemToAnsi(p->location, buf);
 strcpy(p->location, buf );
 return( p );
}

LOC_DB *LocCvtToWin( LOC_DB *p )
{
 char buf[NAME_WIDTH+1];

 if ( !strlen( p->country ) || strlen( p->country ) > NAME_WIDTH ) {
    memset( p, 0, sizeof( LOC_DB ) );
    return( p );
    }
 OemToAnsi(p->country, buf);
 strcpy(p->country, buf );
 OemToAnsi(p->state, buf);
 strcpy(p->state, buf );
 OemToAnsi(p->location, buf);
 strcpy(p->location, buf );
 return( p );
}


W16_FILE_DB *cvt_filedb_2_w16filedb( W16_FILE_DB *ofdp, FILE_DB *fdp )
{
strcpy( ofdp->name, fdp->name );
strcpy( ofdp->comment, fdp->comment );
ofdp->type = fdp->type;
ofdp->file_num = fdp->file_num;
ofdp->has_comments = fdp->has_comments;
ofdp->has_cover = fdp->has_cover;
ofdp->arch_dsk = fdp->arch_dsk;
ofdp->selected = fdp->selected;
return( ofdp );
}

XPFILE_DB *cvt_w16filedb_2_filedb( W16_FILE_DB *ofdp, XPFILE_DB *fdp )
{
strcpy( fdp->name, ofdp->name );
strcpy( fdp->comment, ofdp->comment );
strcpy( fdp->file_name, ofdp->file_name );
fdp->type = ofdp->type;
fdp->file_num = ofdp->file_num;
fdp->has_comments = ofdp->has_comments;
fdp->has_cover = ofdp->has_cover;
fdp->arch_dsk = ofdp->arch_dsk;
fdp->selected = ofdp->selected;
fdp->folder = DEFAULT_FLD;
return( fdp );
}

CString &fmtLongLat( DEG_MIN &rec, CString &str )
{
 char buf[15];
 sprintf( buf, "%02d%c%02d", rec.degrees, rec.dir, rec.minutes );
 str = buf;
 return ( str );

}

 CString &quote( char *pChar, CString & str )
{
 char buf[100], *p, *d;
 buf[0] = '\'';
 for ( p=pChar, d=buf+1; *p!='\0'; p++ ) {
     if ( *p == '\'' ) {
	    *d++= '\'';
		*d++=*p;
		}
     else 
		 *d++=*p;
	}
  *d++='\'';
  *d++='\0';
  str=buf;
  return( str );
 }

void parseLongLat( CString &str, DEG_MIN &dat )
{
 sscanf((const char *)str,"%d%c%d", &dat.degrees, &dat.dir, &dat.minutes );
}