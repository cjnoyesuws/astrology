#include "stdafx.h"
#include "afxcoll.h"
#include <stdlib.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "astro.h"
#include "useri.h" 
#include "errors.fns"
#include <assert.h>
#include "charcons.h"
#include "paths.hpp"
#include "filelst.hpp"
#include <io.h>
#include "uicvt.fns"
#include "astroflistDoc.h"
#include "fptr.h"
#include "filelistset.h"

#define oldflg 0xfedc
#define newflg 0xfedf


typedef struct fid {
	int type;
	FileListArray *ptr;
	int used;
    int num;
    LPVOID obj;
	} fid;

static int fidscount;
static fid fids[6] = { NON_GRA, &AstFileList, 0, 0, 0, GRA_F, &AstFileList, 0, 1, 0,
                   GRIDFX, &AstFileList, 0, 2, 0, ALL_F, NULL, 0, 3, 0, ALL_F, NULL, 0, 4, 0, ALL_F, NULL, 0, 5, 0};

CPtrArray *AryItem::get(int fld) { 
 if ( fldp != NULL )
	fldp->count = count;
 if ( fld < DEFAULT_FLD )
	 fld = DEFAULT_FLD;
 if ( fld-DEFAULT_FLD >= fldcount  )
	addTo(fld-DEFAULT_FLD+1);
 if ( fldAr.GetSize() > fld-DEFAULT_FLD )
    fldp =(AryFldItem *)fldAr.GetAt(fld-DEFAULT_FLD);
 else 
    return NULL;
 count = fldp->count;
 ar = &fldp->ar;
 return ( ar );
}

void AryItem::free() {
	for ( int i = 0; i < fldAr.GetSize(); i++ ) {
	   fldp =(AryFldItem *)fldAr.GetAt(i); 
	   if ( !fldp )
		   return;
	   fldp->ar.RemoveAll();
	   }
}

void AryItem::add()  {
  if ( fldAr.GetCount()==0)
     fldAr.SetSize(5,5);
  AryFldItem *pf = new AryFldItem;
  pf->ar.SetSize(10,10);
  pf->count = 0;
  fldAr.SetAtGrow(fldcount++,pf);
}

void AryItem::addTo(int n) {
  for ( int i = fldcount; i <= n; i++ )
	  add();
}

void AryItem::SelectAll(BOOL bSelect, int fld) {
	int sel = (bSelect==TRUE?1:0);
    fldp =(AryFldItem *)fldAr.GetAt(fld-DEFAULT_FLD);
	for ( int i =0; i < fldp->ar.GetCount(); i++ ) {
		if ( fldp->ar.GetAt(i) != NULL ) {
			XPFILE_DB *ptr = (XPFILE_DB *)fldp->ar.GetAt(i);
			ptr->selected = sel;
		}
	}
}

AryItem &AryGroup::get(int type, int fld) {
  if ( type == NON_GRA ) {
	 text.get(fld);
     return text;
	 }
  else if ( type == GRA_F ) {
	 graph.get(fld);
	 return graph;
	 }
  else if ( type == GRIDFX ) { 
	 grid.get(fld);
	 return grid;
	 }
  else {
	 all.get(fld);
	 return all;
	 }
}

FileListArray::FileListArray(int doInit, int size)
{
 inMem(0);
 dirty(0);
 keep(0);
 last_no = 0;
 arraygroup.all.fldp=0;
 arraygroup.all.count=0;
 arraygroup.all.fldcount=0;
 arraygroup.text.fldp=0;
 arraygroup.text.count=0;
 arraygroup.text.fldcount=0;
 arraygroup.graph.fldp=0;
 arraygroup.graph.count=0;
 arraygroup.graph.fldcount=0;
 arraygroup.grid.fldp=0;
 arraygroup.grid.count=0;
 arraygroup.grid.fldcount=0;

 strcpy(name, "UNTITLED.AFL" );
 arraygroup.get(ALL_F,DEFAULT_FLD);
 arraygroup.get(GRA_F,DEFAULT_FLD);
 arraygroup.get(NON_GRA,DEFAULT_FLD);
 arraygroup.get(GRIDFX,DEFAULT_FLD);
 arraygroup.all.count = 0;
 arraygroup.text.count = 0;
 arraygroup.graph.count = 0;
 arraygroup.grid.count = 0;
}

int FileListArray::getCount( int type, int fld )
{
 check();
 return( arraygroup.get(type, fldcheck(fld)).count );
 }

void FileListArray::setName( char *fname, int dir )
{
 if ( dir != -1 )
    strcpy( name, set_path( fname, dir ) );
 else
    strcpy( name, fname );
}

int FileListArray::append( XPFILE_DB *ptr )
{
 unsigned short flg = 0xfedf;
 int num_files;
 char *am;
 FILE *stream;

 alert_box("error", "calling Append file list");
/*
 dirty(1);
 if (  !isDelFile(ptr) ) {
    if ( access( name, 2 ) == -1 )
       am = "wb";
    else
       am = "r+b";
    if ( ( stream = fopen( name, am ) ) == NULL ) {
       do_error( name );
       return( 0 );
       }
    num_files = arraygroup.all.totalcount;
	if ( num_files == 1 ) {
      fwrite( (char *) &flg, 2, 1, stream);
	  if ( fwrite( (char *) &num_files, sizeof( COUNT ), 1, stream) != 1) {
	     do_error( name );
         fclose( stream );
	     return( 0 );
	     }
       }  
    if ( !strcmpi(am, "r+b") ) {
       if ( fseek( stream, 0L, SEEK_END ) == -1L ) {
	      do_error( name );
	      fclose( stream );
	      return( 0 );
	      }
       }
    if ( fwrite( (char *) ptr, sizeof( XPFILE_DB ), 1, stream ) != 1 ) {
       do_error( name );
       fclose( stream );
       return( 0 );
       }  
	if ( fileCount(ALL_F,ptr->folder) == 1 ) {
       fclose( stream );
       return( 0 );
       }
    if ( fseek( stream, 2L, SEEK_SET ) == -1L ) {
       do_error( name );
       fclose( stream );
       return( 0 );
       }  
    if ( fread( (char *) &num_files, sizeof( COUNT ), 1, stream ) != 1 ) {
       do_error( name );
       fclose( stream );
       return( 0 );
       }
    num_files++;
	if ( fseek( stream, 2L, SEEK_SET ) == -1L ) {
       do_error( name );
       fclose( stream );
       return( 0 );
       }  
    if ( fwrite( (char *) &num_files, sizeof( COUNT ), 1, stream ) != 1 ) {
       do_error( name );
       fclose( stream );
       return( 0 );
       }
    fclose( stream );
    }*/
return( 1 );
}

/* function to write out whole que. Only writes non_deleted files in
   que to file */

int FileListArray::write()
{
 /*unsigned short flg = 0xfedf;
 FILE *stream;
 short x, count;
 COUNT written = 0;
 CPtrArray &ar =arraygroup.all.fldAr;


 if ( !inMem() )
    return( 0 );
 keep( 1 );
 check();
 if ( !strlen(name) ) {
    keep( 0 );
    return( 0 );
    }
 if ( ( stream = fopen( name, "wb" ) ) == NULL ) {
    do_error( name );
    keep( 0 );
    return( 0 );
    }
 fwrite( (char *) &flg, 2, 1, stream );
 short num_files = arraygroup.all.totalcount;
 if ( fwrite( (char *) &num_files, sizeof( short ), 1, stream ) != 1 ) {
    do_error( name );
    fclose( stream );
    keep( 0 );
    return( 0 );
    }
 for ( x = 0, count = arraygroup.all.fldcount; x < count; ++x ) {
     AryFldItem *par = (AryFldItem *)ar.GetAt(x);
	 for ( int j = 0; j < par->count; j++ ) {
		 XPFILE_DB *ptr = (XPFILE_DB *)par->ar.GetAt(j);
	     if ( ptr != NULL && !isDelFile(ptr) ) {
	        if ( fwrite( (char *) ptr, sizeof( XPFILE_DB ), 1, stream ) != 1 ) {
	           do_error( name );
	           fclose( stream );
	           return( 0 );
              }  
          else
             ++written;
          }
       }
 }
 if ( fseek( stream, 2L, SEEK_SET ) ) {
    do_error( name );
    fclose( stream );
    keep( 0 );
    return( 0 );
    }
 if ( fwrite( (char *) &written, sizeof( COUNT ), 1, stream ) != 1 ) {
    do_error( name );
    }
 fclose( stream );
 inMem(1);
 dirty(0);
 keep(0);*/
 return(1);
}

/* function to read que list from disk. If list does not exist, it is 
   assumed it was killed and que is set to 0 files, otherwise que is
   read and number of files in que is set  */

int FileListArray::read()
{
 //unsigned short flg;
 short num_files;	
 //FILE *stream;
 XPFILE_DB db, *ptr;
 FILE_DB w32;
 W16_FILE_DB w16;
 COUNT x, i, allpt = 0, textpt = 0, graphpt = 0, gridpt=0;

 /*if ( !strlen(name) )
    return( 0 );
 if ( !strcmpi(name,"UNTITLED.AFL") )
    return( 0 );
 if ( inMem() )
    return( 1 );
 keep(1);
 if ( ( stream = fopen( name, "rb" ) ) == NULL ) {
    doFileScan();
    if ( ( stream = fopen( name, "rb" ) ) == NULL )
       return( 0 );
    }
 if ( !_filelength( fileno(stream ) ) ) {
	fclose(stream);
	_unlink(name);
	doFileScan();
    if ( ( stream = fopen( name, "rb" ) ) == NULL )
       return( 0 );
	}
 if ( fread( (char *) &flg, 2, 1, stream ) != 1 ) {
    fileCount( 0 );
    do_error( name );
    fclose( stream );
    keep( 0 );
    return( 0 );
    }
 if ( flg == oldflg || flg==newflg ) {
    if ( fread( (char *) &num_files, sizeof( COUNT ), 1, stream ) != 1 ) {
       fileCount( 0 );
       do_error( name );
       fclose( stream );
       keep( 0 );
       return( 0 );
       }
    }
 else
	num_files = flg;
 if ( num_files == 0 ) {
    fclose( stream );
    keep( 0 );
    inMem(1);
    return( 0 );
    }*/
 CFileListSet fls;
 try {
	 fls.m_strSort = "folder, counter";
	 fls.Open();
	 if ( !fls.IsBOF() && !fls.IsEOF() ) {
		 while ( !fls.IsEOF() ) {
			ptr = new XPFILE_DB;
			strcpy(ptr->comment,(LPCTSTR)fls.m_comments);
			strcpy(ptr->name,(LPCTSTR)fls.m_name);
			strcpy(ptr->file_name,fls.m_filename);
			ptr->folder = fls.m_Folder;
			ptr->type = fls.m_FileType;
			ptr->has_comments = fls.m_has_comments;
			ptr->has_cover = fls.m_has_cover;
			ptr->file_num = fls.m_filenum;
			ptr->selected = 0;
			addEntry( ptr, 0, FALSE);
			fls.MoveNext();
		 }
	 }
 }
 catch ( CDaoException *e) {
   char buf[500];
   e->GetErrorMessage(buf,500);
   alert_box("Database Error", buf );
 }
 /*for ( i = 0; i < num_files; i++ ) {
	 ptr = new XPFILE_DB;
	 if ( flg == oldflg ) {
	    if ( fread( &w32, sizeof(FILE_DB), 1, stream) != 1 ) {
           do_error( name );
           fclose( stream );
           return( 0 );
           }
		FileDb2XPFileDB( &w32, ptr );
        if ( ptr->type >= LAST_NON_GRAPH_OLD )
           ptr->type += NEW_GRA_DIFF;
	 }
	 else if ( flg == newflg ) {
		 if ( fread( &db, sizeof(FILE_DB), 1, stream) != 1 ) {
           do_error( name );
           fclose( stream );
           return( 0 );
           }
		 *ptr = db;
	 }
	 else {
	    if ( fread( &w16, sizeof(W16_FILE_DB), 1, stream) != 1 ) {
           do_error( name );
           fclose( stream );
           return( 0 );
           }				 
		cvt_w16filedb_2_filedb( &w16, ptr );
		if ( ptr->type > LAST_NON_GRAPH_OLD )
			ptr->type += NEW_GRA_DIFF;
	 }
   addEntry( ptr, 0);
 } */  
 CPtrArray &ar = arraygroup.all.fldAr;
 for ( i = 1, x = arraygroup.all.fldcount; i < x; i++ ) {
     AryFldItem *par =(AryFldItem *) ar.GetAt(i);
	 for ( int j = 0; j < par->count; j++ ) {
		 ptr = (XPFILE_DB *)par->ar[i];
	     if ( ptr != NULL ) {
	        int fn = ptr->file_num;
	        if ( fn >= last_no )
   	           last_no = fn +1;
	      }
	    }
 }
 /*if ( flg == oldflg )
	write(); */
 inMem(1);
 dirty(0);
 keep(0);
 return(1);
}

/* function to make a temporary file name. file name is unique for up
   to a total of 999 files, which is pretty unrealistic to need.
   Creates a file with the type of the file as the first 5 characters
   and number of the file, and then a type ext. .OUT means a text out
   file for printing, conversion or display. .GRA means a graphics
   data file. Function puts file name and associated file_num into
   ptr structure once it is created. */ 

void FileListArray::makeFileName( NUM type, XPFILE_DB *ptr )
{
 char buf[200];
 char buf2[200];
 char buf3[250];
 char nbuf[10];
 int num;

 if ( strlen(ptr->file_name) )
	return;
 strcpy( buf, ptr->name );
 strcat( buf, "; " );
 strcat( buf, ptr->comment );
 strcpy( buf2, buf );
 if ( ptr->type > LAST_NON_GRAPH && ptr->type < NATAL_GRID_FILE )
    strcat( buf2, ".ASGRA" );
 else if ( ptr->type > LAST_GRAPH )
    strcat( buf2, ".ASGRD" );
 else
	strcat( buf2, ".ASRPT" );
 strcpy( buf3, set_path(buf2, ptr->folder ) );
 if ( access( buf3, 00 ) == -1 ) {
	strcpy( ptr->file_name, buf2 );
 	return;
 	}
 num=0;
 do {
	sprintf(nbuf,"-%d", num );
	strcpy( buf2, buf );
	strcat( buf2, nbuf );
	num++;
	if ( ptr->type > LAST_NON_GRAPH && ptr->type < NATAL_GRID_FILE )
       strcat( buf2, ".ASGRA" );
	else if ( ptr->type > LAST_GRAPH )
	   strcat( buf2, ".ASGRD" );
    else
	   strcat( buf2, ".ASRPT" );
	strcpy( buf3, set_path(buf2, ptr->folder ) );
    } while ( access( buf3, 00 ) == 0 && num < 300 );
 strcpy( ptr->file_name, buf2 );
}

/* Function to add a file to a que. This function first looks for a 
   slot held by a deleted file, then if that is not possible, creates
   space for a new one by a call to realloc. Must check for errno ==
   ENOMEM after this call. If errno is ENOMEM no filename exists, the
   que has probably been lost, and user should exit immediately. 
       If space exists, new filename is created, and structure is filled
   and num_files variable is increased, and que file is appended.
       Function returns a pointer to the structure */

XPFILE_DB *FileListArray::addFile( XPFILE_DB *optr, NUM type)
{
 XPFILE_DB *ptr;
 
 keep(1);
 check();
 if ( arraygroup.all.totalcount == 0 )
    last_no = 0;
 ptr = new XPFILE_DB;
 *ptr = *optr;
 addEntry( ptr, 1, TRUE);
 /*if ( type > LAST_NON_GRAPH && ptr->type < NATAL_GRID_FILE ) {
	//Add(GRA_F,ptr);
	//FlistDoUpdate(GRA_F);
    addEntry( XPFILE_DB *ptr, 1, TRUE);
	}
 else if ( type > LAST_GRAPH ) {
    Add(GRIDFX,ptr);
	FlistDoUpdate(GRIDFX);
    }
 else {
	FlistDoUpdate(NON_GRA);
	Add(NON_GRA,ptr);
	}*/
 /*FlistDoUpdate(ALL_F);
 Add(ALL_F,ptr);
 append( (XPFILE_DB *)ptr );*/
 dirty(1);
 return( (XPFILE_DB *)ptr );
}

void FileListArray::remFile( char *name )
{
 XPFILE_DB *ptr;
 char *p;
 COUNT x, count;
 int type=0;

 check();
 p = strrchr( name, '\\' );
 if ( p == NULL ) {
    p = strrchr( name, ':' );
    }
 p++;

 CPtrArray &ar = arraygroup.all.fldAr;
 for ( x = 0, count = ar.GetSize(); x < count; ++x ) {
     AryFldItem *par = (AryFldItem *)ar.GetAt(x);
	 for ( int y = 0; y < par->count; y++ ) {
	     ptr = (XPFILE_DB *)par->ar[y];
	     if ( ptr != NULL ) {
	        if ( strstr( ptr->file_name, p )!= NULL ) {
				deleteEntry( ptr );
				//par->ar.RemoveAt(x);
		        killFile( ptr );
	            //type = ptr->type;
		        dirty(1);
	            return;
	         }
	       }
	   }
	 }
 /*if (type < LAST_NON_GRAPH )
 	type = NON_GRA;
 else if ( type > LAST_GRAPH )
    type = GRIDFX;
 else
	type = GRA_F;
 CPtrArray &ar2 = arraygroup.get(type,DEFAULT_FLD).fldAr;
 for ( x = 0, count = ar2.GetSize(); x < count; ++x ) {
     AryFldItem *par = (AryFldItem *)ar2.GetAt(x);
	 for ( int y = 0; y < par->count; y++ ) {
	     ptr = (XPFILE_DB *)par->ar.GetAt(y);
	     if ( ptr != NULL ) {
	        if ( strstr( ptr->file_name, p )!= NULL ) {
	           par->ar.RemoveAt(x);
		       delete ptr;
	           return;
	           }
	       }
	    }
	 }*/
 return;
}


void GetFileListPtrAndType( FileListArray **ptr, int &type, void *p )
{
 if ( fidscount == 0 || fidscount == 1 || fidscount==2 ) {
	type = fids[fidscount].type;
 	*ptr = fids[fidscount].ptr;
	fids[fidscount].used = 1;
    fids[fidscount].obj = p;
	fidscount++;
    return;
    }
 else {
	 int n;
	 if ( !fids[0].used )
		n = 0;
	 else if ( !fids[1].used )
		n = 1;
	 else
		n = fidscount++;
	type = fids[n].type;
 	if ( n == 0 || n == 1 )
	   *ptr = fids[n].ptr;
	else {	
	   *ptr = fids[n].ptr = new FileListArray( 1, 20 ) ;
	   ((FileListArray *)*ptr)->inMem(1);
		}
	fids[n].used = 1;
    fids[n].obj = p;
    }

}


void PutBackFileListPtrAndType( FileListArray *ptr, int type )
{
 int n;

 if ( type == GRA_F )
	n = 1;
 else if ( type == NON_GRA )
	n = 0;
 else {
	for ( int x = 1; x < 7; x++ ) {
		if ( fids[x].ptr == ptr )
 		   n = x;
	   }
	}
 if ( n == 0 || n == 1 || n == 2)
	fids[n].used = 0;
 else {
	delete ptr;
 	fids[n].ptr = NULL;
	fids[n].used = 0;
    fids[n].obj = NULL;
    }
}

// notify document related to type to file list

void FlistDoUpdate(int type)
{
 int i;
 if ( type == GRA_F && fids[1].obj != NULL ) {
	((CAstroflistDoc *)fids[1].obj)->Update();
	return;
	}
 if ( type == NON_GRA && fids[0].obj != NULL ) {
	((CAstroflistDoc *)fids[0].obj)->Update();
	return;
    }
 if ( type == GRIDFX && fids[2].obj != NULL ) {
	((CAstroflistDoc *)fids[2].obj)->Update();
	return;
    }
 for ( i = 3; i < 6; i++ ) {
	 if ( fids[i].used && fids[i].ptr != NULL && fids[i].obj != NULL )
 	    ((CAstroflistDoc *)fids[i].obj)->Update();
     }
}