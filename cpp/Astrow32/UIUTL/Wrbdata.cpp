#include "stdafx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include <share.h>
#include "basedcs.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "useri.h"
#include "errors.fns"
#include "charcons.h"

extern CString RelocationPersonal;
BIRTH_DB *BirthCvtToWin( BIRTH_DB *p );
LOC_DB *LocCvtToWin( LOC_DB *p );
                                                           
static char ids[] = { "\xdb\xaa\xae\xff" "ASTRODATA" };
static char idsw[] = { "\xda\xab\xaf\xfd" "ASTRODATA" };

/* function to write the entire set of birth data to a file. This consists
   of all the BIRTH_DB variables, the rectification info, the transits,
   progressions and return data and the flags indicating that the screens
   are or are not complete. The function returns 0 for success, non zero for
   the item that failed */

int write_birth_data( char *file_name )
{
 int handle;
 short flags[10];
 RECT_DATA rc[3];
 BIRTH_DB d[3];

 if ( (handle = open( file_name, O_BINARY | O_CREAT |
		O_WRONLY | O_TRUNC, _S_IREAD | _S_IWRITE ) ) == -1 )
    return( -1 );
 if ( write( handle, idsw, sizeof( idsw )-1 ) != sizeof( ids )-1 ) {
    close( handle );
    unlink( file_name );
    return( 1 );
    }
 d[0] = birth_rec;
 d[1] = comp_rec;
 d[2] = trans_rec;
 if ( write( handle, d, 3 * sizeof( BIRTH_DB ) ) != 3 * sizeof( BIRTH_DB ) ) {
    close( handle );
    unlink( file_name );
    return( 2 );
    }
 if ( write( handle, &progress_data, sizeof( PROGR_DATA ) ) != sizeof( PROGR_DATA ) ) {
    close( handle );
    unlink( file_name );
    return( 3 );
    }
 if ( write( handle, &transit_data, sizeof( TRANS_DATA ) ) != sizeof( TRANS_DATA ) ) {
    close( handle );
    unlink( file_name );
    return( 4 );
    }
 rc[0] = birth_rectd;
 rc[1] = comp_rectd;
 rc[2] = trans_rectd;
 if ( write( handle, rc, 3 * sizeof( RECT_DATA ) ) != 3 * sizeof( RECT_DATA ) ) {
    close( handle );
    unlink( file_name );
    return( 5 );
    }
 if ( write( handle, &return_data, sizeof( RETURN_DATA ) ) != sizeof( RETURN_DATA ) ) {
    close( handle );
    unlink( file_name );
    return( 6 );
    }
 if ( write( handle, &reloc_data, sizeof( LOC_DB ) ) != sizeof( LOC_DB ) ) {
    close( handle );
    unlink( file_name );
    return( 7 );
    }
 flags[0] = birth_ok;
 flags[1] = birth_rect_ok;
 flags[2] = comp_ok;
 flags[3] = comp_rect_ok;
 flags[4] = trans_ok;
 flags[5] = trans_data_ok;
 flags[6] = prog_ok;
 flags[7] = 0;
 flags[8] = 0;
 flags[9] = 0;
 if ( write( handle, flags, 10 * sizeof( short ) ) != 10 * sizeof( short ) ) {
    close( handle );
    unlink( file_name );
    return( 8 );
    }
 if ( write( handle, (const char *)RelocationPersonal, 50) != 50 ) {
    close( handle );
    unlink( file_name );
    return( 9 );
    }
 if ( write( handle, &solar_data, sizeof(DIREC_DATA)) != sizeof(DIREC_DATA) ) {
    close( handle );
    unlink( file_name );
    return( 9 );
    }

 close( handle );
 return( 0 );
}

extern int import_file( char *file );

/* function to read the entire set of birth data from a file. This consists
   of all the BIRTH_DB variables, and the flags indicating that the screens
   are or are not complete. The function returns 0 for failure, 1 for
   success */

int read_birth_data( char *file_name )
{
 char bf[10];
 char id[20];
 int handle;
 short flags[10];
 RECT_DATA rc[3];
 BIRTH_DB d[3];
 char buffer[50];
#ifdef PRO
 static char recs[] = {"^BD ^BL ^BR ^BX ^CD ^CL ^CR ^CX ^TD ^TL ^TA ^RD ^RL ^RP ^PD"};
#endif

 if ( (handle = open( file_name, O_BINARY | O_RDONLY  ) ) == -1 )
    return( -1 );

 if ( read( handle, id, sizeof( idsw )-1 ) != sizeof( ids )-1 ) {
    close( handle );
    return( 1 );
    }
 id[sizeof(idsw)-1]= '\0';
 if ( strcmp( id, idsw ) && strcmp( id, ids ) ) {
#ifdef PRO
    memcpy( bf, id, 4 );
    bf[3] = '\0';
    if ( strstr( recs, bf ) != NULL ) {
       close(handle);
       return( import_file( file_name ) );
       }
#endif
    alert_box( ERROR2, "%s is not a Birth Data File!", file_name );
    close( handle );
    return( 99 );
    }
 if ( read( handle, d, 3 * sizeof( BIRTH_DB ) ) != 3 * sizeof( BIRTH_DB ) ) {
    close( handle );
    return( 2 );
    }
 if ( strlen( d[0].name ) > NAME_WIDTH )
    return( 2 );
 birth_rec = d[0];
 comp_rec = d[1];
 trans_rec = d[2];
 if ( read( handle, &progress_data, sizeof( PROGR_DATA ) ) != sizeof( PROGR_DATA ) ) {
    close( handle );
    return( 3 );
    }
 if ( read( handle, &transit_data, sizeof( TRANS_DATA ) ) != sizeof( TRANS_DATA ) ) {
    close( handle );
    return( 4 );
    }
 if ( read( handle, rc, 3 * sizeof( RECT_DATA ) ) != 3 * sizeof( RECT_DATA ) ) {
    close( handle );
    return( 5 );
    }
 if ( read( handle, &return_data, sizeof( RETURN_DATA ) ) != sizeof( RETURN_DATA ) ) {
    close( handle );
    return( 6 );
    }
 if ( read( handle, &reloc_data, sizeof( LOC_DB ) ) != sizeof( LOC_DB ) ) {
    close( handle );
    return( 7 );
    }
 birth_rectd = rc[0];
 comp_rectd = rc[1];
 trans_rectd = rc[2];
 if ( read( handle, flags, 10 * sizeof( short ) ) != 10 * sizeof( short ) ) {
    close( handle );
    return( 8 );
    }
 if ( read( handle, buffer, 50 ) == 50 ) {
    RelocationPersonal = buffer;
    }
 read( handle, &solar_data, sizeof(DIREC_DATA) );
 if ( strcmp( id, idsw ) ) {
    BirthCvtToWin( &birth_rec );
    BirthCvtToWin( &comp_rec );
    BirthCvtToWin( &trans_rec );
    LocCvtToWin( &reloc_data );
    }
 birth_ok = flags[0];
 birth_rect_ok = flags[1];
 comp_ok = flags[2];
 comp_rect_ok = flags[3];
 trans_ok = flags[4];
 trans_data_ok = flags[5];
 prog_ok = flags[6];
 close( handle );
 return( 0 );
}
/* Function to handle saving birth data. Prompts user for a file name.
   If the name has a drive or directory information, it is considered
   to be either fully qualified, off the current directory of this
   drive or the drive specified, otherwise the file is saved to the
   user directory. Returns 0 for error, otherwise 1 for success */

int do_save_birth_data( CWnd *pPar )
{
 char wr_name[250];
 static char types[] = { "Data Files (*.DAT)|*.DAT|All Files (*.*)|*.*||" };
 memset( wr_name, 0, 250 );
 strcpy( wr_name, "*.DAT" );
 CFileDialog cfd(FALSE,".DAT","ASTRO.DAT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, types, pPar );
 cfd.m_ofn.lpstrTitle = "Enter Name of File To Save Data To:";
 if ( cfd.DoModal() != IDOK ) 
    return( 0 );
 strcpy( wr_name, cfd.GetPathName() );
 if ( write_birth_data( wr_name ) ) {
    do_error( wr_name );
    return( 0 );
    }
 else
    return( 1 );
}

/* Function to handle loading birth data. Prompts user for a file name.
   If the name has a drive or directory information, it is considered
   to be either fully qualified, off the current directory of this
   drive or the drive specified, otherwise the file is loaded from the
   user directory. Returns 0 for error, otherwise 1 for success */

int do_load_birth_data( CWnd *pPar )
{
 char rd_name[250];
 static char types[] = { "Data Files (*.DAT)|*.DAT|All Files (*.*)|*.*||" };
 memset( rd_name, 0, 250 );
 CFileDialog cfd(TRUE,".DAT","ASTRO.DAT", OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, types, pPar );
 cfd.m_ofn.lpstrTitle = "Enter Name of File To Read Data From:";
 if ( cfd.DoModal() != IDOK ) 
    return( 0 );
 strcpy( rd_name, cfd.GetPathName() );
 if ( read_birth_data( rd_name ) ) {
    do_error( rd_name );
    return( 0 );
    }
 else
    return( 1 );
}
