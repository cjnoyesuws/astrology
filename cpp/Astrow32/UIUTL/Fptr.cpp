#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "paths.hpp"
#include "errors.fns"
#include "inifile.hpp"
#include <mbstring.h>
#ifdef DEMO
char copyrtmsg[] = { "\n{This Chart Produced by The Shareware Demo Version of "
		     "ASTRO--The Program for Astrological Analysis "
		     "(C) Copyright 1985, 1988-2005 Christopher J. Noyes. "
		     "This Program Licensed For Trial Use Only.}\n\n" };

static char PW1[]= {"1&Natal&9"};
static char PW2[]= {"2!Astrology!8"};
static char PW3[]= {"3@Planets@6"};
static char PW4[]= {"4=Placidus=7"};

#endif

static short ansi_mode = -1;

extern int write_demo_message( FILE *stream, char *file );
unsigned char const * const fpt_ids =(unsigned char const *)ID_STR;
unsigned char const * const fpt_ids2 =(unsigned char const *)ID_STR2;
unsigned char const * const fpt_ids3 =(unsigned char const *)ID_STR3;
unsigned char const * const fpt_idsc =(unsigned char const *)ID_STRC;
unsigned char const * const fpt_ids3w =(unsigned char const *)ID_STR3W;
unsigned char const * const fpt_idscw =(unsigned char const *)ID_STRCW;
unsigned char const * const fpt_ids3wx =(unsigned char const *)ID_STR3WX;
unsigned char const * const fpt_ids3wxg =(unsigned char const *)ID_STR3WXG;
unsigned char const * const fpt_ids3wxu =(unsigned char const *)ID_STR3WXU;
/* Function to write a fptr to a file. */
/*
	O_FILE_DB o;
    W16_FILE_DB w16;
    FILE_DB   n;
*/
short data_type_len( short type )
{
 static short lens[] = {ID_STR_LEN+3, sizeof(O_FPTR),sizeof(W16_FPTR),
	 sizeof(W16_FPTR),sizeof(W16_FPTR),sizeof(FPTR),sizeof(FPTR),
	 sizeof(FPTR),sizeof(FPTR),sizeof(FPTR)};

 return( lens[type] );
}

short file_type( char *ids )
{
if ( isa_ids3wxg( ids ) )
   return( _WINXP_GRID );
else if ( isa_ids3wxg( ids ) )
   return( _WINXP_CHARTUNI );
else if ( isa_ids3wxu( ids ) )
   return( _WINXP_CHART );
else if ( isa_ids3wx( ids ) || isa_ids3w( ids ) )
   return( _WIN95_CHART_ );
else if ( isa_idscw( ids ) )
   return( _WIN95_COMMENT );
else if ( isa_ids3( ids ) )
   return( _WIN16_CHART_ );
else if ( isa_idsc( ids ) )
   return( _COMMENT_FILE );
else if ( isa_ids2( ids ) )
   return(_DOSPRO_CHART);
else if ( isa_ids( ids ) )
   return(_DOSDEX_CHART);
else
   return( 0 );
}


int write_fptr( char *file, NFDB *ptr, int type )
{
 NFP fp;
 int handle;

 if ( ( handle = open( file, O_CREAT|O_WRONLY|O_BINARY) ) == -1 ) {
    do_error( file );
    return( handle );
    }
 if ( type == 8 )
    memcpy( fp.x.ids, fpt_ids3wxg, ID_STR_LEN ); 
  else if ( type == 9 )
    memcpy( fp.x.ids, fpt_ids3wxu, ID_STR_LEN );
 else if ( type == 7 )
    memcpy( fp.x.ids, fpt_ids3wx, ID_STR_LEN );
  else if ( type == 6 )
    memcpy( fp.n.ids, fpt_idscw, ID_STR_LEN );
 else if ( type == 5 )
    memcpy( fp.n.ids, fpt_ids3w, ID_STR_LEN );
 else if ( type == 4 )
    memcpy( fp.n.ids, fpt_idsc, ID_STR_LEN );
 else if ( type == 3 )
    memcpy( fp.n.ids, fpt_ids3, ID_STR_LEN );
 else if ( type == 2 )
    memcpy( fp.n.ids, fpt_ids2, ID_STR_LEN );
 else
    memcpy( fp.n.ids, fpt_ids, ID_STR_LEN );
 memcpy( &fp.x.fpt, ptr, data_type_len(type)-(ID_STR_LEN+1) );
 if ( write( handle, (char *)&fp, data_type_len(type) ) == -1 ) {
       do_error( file );
       close( handle );
       return( -1 );
       }
 return( handle );
}

FILE *fwrite_fptr( char *file, NFDB *ptr, int type )
{
 FILE *stream;
 NFP fp;

 if ( ( stream = fopen( file, "wb" ) ) == NULL ) {
    do_error( file );
    return( stream );
    }
 if ( type == 8 )
    memcpy( fp.x.ids, fpt_ids3wxg, ID_STR_LEN );
  else if ( type == 9 )
    memcpy( fp.x.ids, fpt_ids3wxu, ID_STR_LEN );
 else if ( type == 7 )
    memcpy( fp.x.ids, fpt_ids3wx, ID_STR_LEN );
 else if ( type == 6 )
    memcpy( fp.n.ids, fpt_idscw, ID_STR_LEN );
 else if ( type == 5 )
    memcpy( fp.n.ids, fpt_ids3w, ID_STR_LEN );
 else if ( type == 4 )
    memcpy( fp.n.ids, fpt_idsc, ID_STR_LEN );
 else if ( type == 3 )
    memcpy( fp.n.ids, fpt_ids3, ID_STR_LEN );
 else if ( type == 2 )
    memcpy( fp.n.ids, fpt_ids2, ID_STR_LEN );
 else
    memcpy( fp.n.ids, fpt_ids, ID_STR_LEN );
 memcpy( &fp.x.fpt, ptr, data_type_len(type)-(ID_STR_LEN+1) );
 if ( fwrite( &fp.x, data_type_len(type), 1, stream ) != 1 ) {
    do_error( file );
    fclose( stream );
    return( NULL );
    }
 return( stream );
}


FILE *reread ( char *file, FILE *stream, NFP *ptr) {
NFP fp;
short type, d;

fseek(stream,0,SEEK_SET);
memset( fp.x.ids, 0, ID_STR_LEN+1 );
 if ( fread( &fp, ID_STR_LEN+1, 1, stream ) != 1 ) {
    fseek( stream, 0L, SEEK_SET );
    return( stream );
    }
 type = file_type((char *)fp.x.ids);
 if ( fread( &fp.x.fpt, data_type_len(type)-(ID_STR_LEN+1), 1, stream ) != 1 ) {
    fseek( stream, 0L, SEEK_SET );
    return( stream );
    }
if ( ptr != NULL )
    memcpy( ptr, &fp, data_type_len(type) );
if ( type == _WIN95_CHART_ || type == _WIN16_CHART_ ||
     type == _DOSPRO_CHART || type == _WINXP_CHART || type == _WINXP_GRID || 
	 type==_WIN95_COMMENT || type == _WINXP_CHARTUNI) {
   if ( stream != NULL ) {
      fread( &d, sizeof( short ), 1, stream );
      fread( &d, sizeof( short ), 1, stream );
      if ( fseek( stream, data_type_len(type) + d + 4, SEEK_SET ) == -1L ) {
         do_error( file );
         fclose( stream );
         return( NULL );
         }
      }
   return( stream );
  }
  return stream;
}

int readx_fptr( char *file, NFP *ptr, int do_read )
{
NFP fp;
int handle;
short type, d;

 if ( ( handle = open( file, O_BINARY|O_RDONLY  ) ) == -1 ) {
    return( handle );
    }
 memset( fp.x.ids, 0, ID_STR_LEN+1 );
 if ( read( handle, (char *) &fp.x.ids, ID_STR_LEN+1 ) == -1 ) {
    close( handle );
    return( -1 );
    }
 type = file_type((char *)fp.x.ids);
 if ( read( handle, (char *) &fp.x.fpt, data_type_len(type)-(ID_STR_LEN+1) ) == -1 ) {
    close( handle );
    return( -1 );
    }
if ( ptr != NULL )
   memcpy( ptr, &fp, data_type_len(type) );
if ( type == _WIN95_CHART_ || type == _WIN16_CHART_ ||
     type == _DOSPRO_CHART || type == _WINXP_CHART || type == _WINXP_GRID || 
	 type==_WIN95_COMMENT || type == _WINXP_CHARTUNI ) {
   if ( !do_read ) {
      read( handle, (char *) &d, sizeof( short ) );
      read( handle, (char *) &d, sizeof( short ) );
      if ( lseek( handle, data_type_len(type) + d + 4, SEEK_SET ) == -1L ) {
         do_error( file );
         close( handle );
         return( -1 );
         }
      }
   return( handle );
  }
 else if ( lseek( handle, 0L, SEEK_SET ) == -1L ) {
    do_error( file );
    close( handle );
    return( -1 );
    }
 return( handle );
}
/*
// updated above
int readx_fptr( char *file, NFP *ptr, int do_read )
{
 NFP fp;
 int handle, d;

 if ( ( handle = open( file, O_BINARY|O_RDONLY  ) ) == -1 ) {
    return( handle );
    }
 memset( fp.n.ids, 0, ID_STR_LEN );
 if ( read( handle, (char *) &fp.n, sizeof( FPTR ) ) == -1 ) {
    close( handle );
    return( -1 );
    }
 if ( ptr != NULL )
    memcpy( ptr, &fp, sizeof( NFP ) );
 if ( !memcmp( fp.o.ids, fpt_ids, ID_STR_LEN ) ) {
    if ( lseek( handle, sizeof( O_FPTR ), SEEK_SET ) == -1L ) {
	  do_error( file );
	  close( handle );
	  return( -1 );
	  }
    return( handle );
    }
 else if ( !memcmp( fp.n.ids, fpt_ids2, ID_STR_LEN ) ||
		    !memcmp( fp.n.ids, fpt_ids3, ID_STR_LEN ) ) {
    if ( !do_read ) {
       read( handle, (char *) &d, sizeof( int ) );
       read( handle, (char *) &d, sizeof( int ) );
       if ( lseek( handle, sizeof( FPTR ) + d + 4, SEEK_SET ) == -1L ) {
	  do_error( file );
	  close( handle );
	  return( -1 );
	  }
       }
    return( handle );
    }
 else if ( lseek( handle, 0L, SEEK_SET ) == -1L ) {
    do_error( file );
    close( handle );
    return( -1 );
    }
 return( handle );
}
*/


FILE *freadx_fptr( char *file, NFP *ptr, int do_read )
{
 short d, type;
 NFP fp;
 FILE *stream;

 if ( ( stream = fopen( file, "rb"  ) ) == NULL ) {
    return( NULL );
    }
 if ( strstr( file, ".ASHLP" ) != NULL || strstr( file, ".ashlp" ) != NULL )
	return( stream );
 memset( fp.x.ids, 0, ID_STR_LEN+1 );
 if ( fread( &fp, ID_STR_LEN+1, 1, stream ) != 1 ) {
    fseek( stream, 0L, SEEK_SET );
    return( stream );
    }
 type = file_type((char *)fp.x.ids);
 if ( fread( &fp.x.fpt, data_type_len(type)-(ID_STR_LEN+1), 1, stream ) != 1 ) {
    fseek( stream, 0L, SEEK_SET );
    return( stream );
    }
if ( ptr != NULL )
    memcpy( ptr, &fp, data_type_len(type) );
if ( type == _WIN95_CHART_ || type == _WIN16_CHART_ ||
     type == _DOSPRO_CHART || type == _WINXP_CHART || type == _WINXP_GRID || 
	 type==_WIN95_COMMENT || type == _WINXP_CHARTUNI) {
   if ( !do_read ) {
      fread( &d, sizeof( short ), 1, stream );
      fread( &d, sizeof( short ), 1, stream );
      if ( fseek( stream, data_type_len(type) + d + 4, SEEK_SET ) == -1L ) {
         do_error( file );
         fclose( stream );
         return( NULL );
         }
      }
   return( stream );
  } 
else if ( fseek( stream, 0L, SEEK_SET ) == -1L ) {
    do_error( file );
    fclose( stream );
    return( NULL );
    }
 return( stream );
}

char *enquote_strclip( unsigned char *str, unsigned char *buf )
{
 char buffer[200];
 unsigned char *s = (unsigned char *)buffer, *d = buf;

 if ( ansi_mode == -1 ) {
    ansi_mode = (short) AfxGetApp()->GetProfileInt( Misc_SEC, "AnsiText", 0 );
    }
 if ( !ansi_mode ) {
    AnsiToOem( (const char *)str, (char *)buffer );
    }
 else
    strcpy( (char *)buffer, (const char *)str );
 while ( *s ) {
       if ( *s > '\x7f' || strchr("<>{}[]~ ", *s) != NULL )
	  *d++ = '~';
       *d++ = *s++;
       }
 *d = '\0';
 return( (char *)buf );
}

char *xstrupr( char *src )
{
 
if ( ansi_mode == -1 ) {
    ansi_mode = (short) AfxGetApp()->GetProfileInt( Misc_SEC, "AnsiText", 0 );
    }
 if ( ansi_mode==1 )
    return( AnsiUpper(src) ); // src and dest are ansi
 if ( ansi_mode==2 )
    return( CharUpper(src) ); // src and dest are ansi
 else {
	int len =strlen(src);     // src and dest are oem
    char *buf = new char[len+10];
    OemToAnsi( src, buf );
    AnsiUpper(buf);
    AnsiToOem( buf, src );
    delete buf;
    return( src );
    }
}


int write_demo_message( FILE *stream, char *file )
{
#ifdef DEMO
  CString st;
  st = AfxGetApp()->GetProfileString( "Shareware", "Reg", "" );
  if ( !(!strcmpi(st, PW1) || !strcmpi(st, PW2) ||
       !strcmpi(st, PW3) || !strcmpi(st, PW4) ) ) {
     if ( fputs( (char *)copyrtmsg, stream ) != 0 ) {
	do_error( file );
	return( 0 );
	}
     }
#endif
 return( 1 );
}

XPFILE_DB *FileDb2XPFileDB( FILE_DB *old, XPFILE_DB *newp )
{
 memcpy((void *)newp,(void *)old,sizeof(FILE_DB)-6);
 newp->folder = DEFAULT_FLD;
 newp->arch_dsk = old->arch_dsk;
 newp->has_comments = old->has_comments;
 newp->has_cover = old->has_cover;
 newp->selected = old->selected;
 return newp;
}