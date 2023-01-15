#include "stdafx.h"
#include "astrow.h"
#include "afxcoll.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <share.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "charcons.h"
#include "errors.fns"
#include "paths.hpp"
#include "filelst.hpp"
#include <io.h>
#include "procmsg.h"


#define oldflg 0xfedc;
#define newflg 0xfedf;

/* Buffer to be used for finding files 

struct _finddatai64_t {
    unsigned	attrib;
    time_t	time_create;	// -1 for FAT file systems 
    time_t	time_access;	// -1 for FAT file systems 
    time_t	time_write;
    __int64	size;
    char	name[260];
}; */


struct _finddata_t find_buffer;



int FileListArray::hasFile( char *name, char *ext )
{
 char buf[350], *np;

 strcpy( buf, set_path(name, CURRENT_F) );
 np = strrchr( buf, '.' );
 if ( np != NULL ) {
    strcpy( np, ext );
    if ( !access( buf, 0 ) )
       return( 1 );
    else
       return( 0 );
    }
 else
    return( 0 );
}


long FileListArray::initFileScan(char *buf, char *pat)
{
 long r;

 r = _findfirst( set_path( pat, CURRENT_F ),
      &find_buffer );
 if ( r != -1L )
    strcpy( buf, find_buffer.name );
 else
    *buf = '\0';
 return( r );
}

long FileListArray::fileScanCont( char *buf, long h )
{
 int r;

 r = _findnext( h, &find_buffer );
 if ( !r )
    strcpy( buf, find_buffer.name );
 else
    *buf = '\0';
 return( r );
}

int FileListArray::isFileInQue( char *name, int type )
{
 int i, cnt;
 
 AryItem &ar =arraygroup.get(type,GetCurFolder());
 for ( int j = 0, cnt = ar.fldp->count; j < cnt; j++ ) {
		 if ( ar.fldp->ar[j] != NULL && !strcmpi( name,((XPFILE_DB *)ar.fldp->ar[j])->file_name ) )
	       return( 1 );
        }
 return( 0 );
}

int FileListArray::isAQueFile(char *name)
{
 char *dot;

 dot = strrchr( name, '.' );
 if ( dot == NULL )
    return( 0 );
 if ( !strcmpi(dot, ".GRA" ) || !strcmpi(dot, ".OUT" ) ||
	  !strcmpi(dot, ".ASGRA" ) || !strcmpi(dot, ".ASRPT" ) ||
	  !strcmpi(dot, ".ASGRD" ))
    return( 1 );
 else
    return( 0 );
}

void FileListArray::doFileScan( void )
{
 unsigned short flg = 0xfedf;
 short added = 0;
 int _break = 0;

 ProcMsg pm(" ...REBUILDING FILE LIST...  ", &_break);
 DoFileScanLoop("*.OUT", NON_GRA );
 DoFileScanLoop("*.ASRPT", NON_GRA );
 DoFileScanLoop("*.GRA", GRA_F );
 DoFileScanLoop("*.ASGRA", GRA_F );
 DoFileScanLoop("*.ASGRD", GRIDFX );
}




int FileListArray::DoFileScanLoop( char *pat, int type )
{
 unsigned short flg = 0xfedf;
 NFP nfpt, nfp2;
 char name_buf[250];
 FILE *stream;
 long handle;
 int fh;
 short added = 0, cng = 0;
 int _break = 0;
 XPFILE_DB db;
 XPFILE_DB *xdb = &db;
 int new_file = 0;

 db.folder=GetCurFolder();
 if ( (handle = initFileScan( name_buf, pat )) == -1L )
    return 0;
 do {
    cng = 0;
    if ( find_buffer.attrib != _A_ARCH && find_buffer.attrib != _A_NORMAL )
	   continue;
	if ( !isAQueFile(name_buf) )
	   continue;
	if ( isFileInQue(name_buf, type) )
       continue;
    ((CAstrowApp *)AfxGetApp())->_Yield();
	if ( ( fh = readx_fptr( set_path(name_buf, xdb->folder), &nfpt, 0 ) ) != -1 ) {
       if ( isafptr_file( &nfpt ) ) {
	      if ( strcmpi( name_buf, nfpt.o.fpt.file_name ) ) {
	         if (isFileInQue(nfpt.o.fpt.file_name, type))
		        cng = 1;
	         else
		        cng = 0;
	         strcpy( nfpt.o.fpt.file_name, name_buf );
	         nfpt.o.fpt.comment[O_COMMENT_WIDTH]='\0';
	         lseek( fh, 0L, SEEK_SET );
	         ::write( fh, &nfpt.o, sizeof( O_FPTR ) );
	         }
	  nfpt.o.fpt.comment[O_COMMENT_WIDTH]='\0';
	  cvt_ofiledb_2_nfiledb( &nfp2.w16.fpt, &nfpt.o.fpt );
	  cvt_w16filedb_2_filedb( &nfp2.w16.fpt, &nfpt.x.fpt );
	  if ( hasFile( name_buf, ".CMT" ) )
	     nfpt.x.fpt.has_comments = 1;
	  else
	     nfpt.x.fpt.has_comments = 0;
	  if ( hasFile( name_buf, ".CPG" ) )
	     nfpt.x.fpt.has_cover = 1;
	  else
	     nfpt.x.fpt.has_cover = 0;
	  addEntry(&nfpt.x.fpt,0,(isFileInQue(name_buf,type)?FALSE:TRUE));
	  ++added;
	  }
    else if ( isafptr2_file( &nfpt ) || isafptr3_file( &nfpt ) ) {
	  if ( strcmpi( name_buf, nfpt.w16.fpt.file_name ) ) {
	     if (isFileInQue(nfpt.w16.fpt.file_name, type))
		    cng = 1;
	     else
		    cng = 0;
	     strcpy( nfpt.w16.fpt.file_name, name_buf );
	     nfpt.w16.fpt.comment[COMMENT_WIDTH]='\0';
	     lseek( fh, 0L, SEEK_SET );
	     ::write( fh, &nfpt.w16, sizeof( FPTR ) );
	     }
	  nfpt.w16.fpt.comment[COMMENT_WIDTH]='\0';
	  if ( hasFile( name_buf, ".CMT" ) )
	     nfpt.w16.fpt.has_comments = 1;
	  else
	     nfpt.w16.fpt.has_comments = 0;
	  if ( hasFile( name_buf, ".CPG" ) )
	     nfpt.w16.fpt.has_cover = 1;
	  else
	     nfpt.w16.fpt.has_cover = 0;
	  nfpt.w16.fpt.selected = 0;
	  nfpt.w16.fpt.arch_dsk = 0;
	  if ( isafptr2_file( &nfpt ) )	
	     cvt_filedb_2_win(&nfpt.w16.fpt);
	  cvt_w16filedb_2_filedb( &nfpt.w16.fpt, &nfp2.x.fpt );
	  addEntry(&nfpt.x.fpt,0,(isFileInQue(name_buf,type)?FALSE:TRUE));
	  ++added;
	  }
	else if ( isafptr3w_file( &nfpt ) ) {
	  if ( strcmpi( name_buf, nfpt.n.fpt.file_name ) ) {
	     if (isFileInQue(nfpt.n.fpt.file_name, type))
		    cng = 1;
	     else
		    cng = 0;
		 FileDb2XPFileDB(&nfpt.n.fpt,xdb);
		 nfpt.x.fpt = *xdb;
		 strcpy( nfpt.x.fpt.file_name, name_buf );
	     nfpt.n.fpt.comment[COMMENT_WIDTH]='\0';
	     lseek( fh, 0L, SEEK_SET );
		 ::write( fh, &nfpt.x, sizeof( XFPTR ) );
	     }
	  nfpt.x.fpt.comment[COMMENT_WIDTH]='\0';
	  if ( hasFile( name_buf, ".CMT" ) )
	     nfpt.x.fpt.has_comments = 1;
	  else
	     nfpt.x.fpt.has_comments = 0;
	  if ( hasFile( name_buf, ".CPG" ) )
	     nfpt.x.fpt.has_cover = 1;
	  else
	     nfpt.x.fpt.has_cover = 0;
	  nfpt.x.fpt.selected = 0;
	  nfpt.x.fpt.arch_dsk = 0;
	  if ( !cng ) {
	     addEntry(&nfpt.x.fpt,0,(isFileInQue(name_buf,type)?FALSE:TRUE));
	     ++added;
	     }
	  }
   else {
	    addEntry(&nfpt.x.fpt,0,(isFileInQue(name_buf,type)?FALSE:TRUE));
	    ++added;    
	    }
	  close( fh );
    }
  ((CAstrowApp *)AfxGetApp())->_Yield();
 if ( _break )
	break; 
 } while( fileScanCont( name_buf, handle ) != -1L );
 _findclose(handle);
 arraygroup.all.totalcount += added;
 added = arraygroup.all.totalcount;
 return added; 
}

