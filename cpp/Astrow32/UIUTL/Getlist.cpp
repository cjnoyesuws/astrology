#include "stdafx.h"
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "paths.hpp"
#include "filelst.hpp"



int getFileCount( CWordArray &war, CPtrArray &par, int n, int cmt, int cvr )
{
 XPFILE_DB *pt;
 int i, c;

 for ( i = 0, c = 0; i < n; i++ ) {
     pt =(XPFILE_DB *) par[war[i]];
	 if ( pt == NULL )
        continue;
	 else
        c++;
	 if ( cmt && pt->has_comments )
     	c++;
     if ( cvr && pt->has_comments )
     	c++;
     
	}
 return( c );
}



int getFileList( CStringArray &sar, CWordArray &war, CPtrArray &par, int n, int sz, int b4, int cmt, int cvr )
{
 CString s;
 char buf[250];
 XPFILE_DB *pt;
 int i, c=0;

 for ( i = 0;  i < n;  i++ ) {
     pt = (XPFILE_DB *)par[war[i]];
	 if ( pt == NULL )
        continue;
	 if ( cvr && pt->has_cover ) {
	    replace_ext(buf, pt->file_name, ".CPG" );
		s = set_path(buf,pt->folder);
		sar[c++] = s;
	    }
     if ( cmt && b4 && pt->has_comments ) {
	    replace_ext(buf, pt->file_name, ".CMT" );
		s = set_path(buf,pt->folder);
		sar[c++] = s;
	    }
     strcpy( buf, pt->file_name );
	 s = set_path(buf,pt->folder);
	 sar[c++] = s;
     if ( cmt && !b4 && pt->has_comments ) {
	    replace_ext(buf, pt->file_name, ".CMT" );
		s = set_path(buf,pt->folder);
		sar[c++] = s;
	    }
     }
 sar[c++] = "NULL";
 return( c );
}

