#include "stdafx.h"
#include "afxcoll.h"
#include "astro.h"
#include "useri.h"
#include "errors.fns"
#include <assert.h>
#include "paths.hpp"
#include "filelst.hpp"


int FileListArray::selCount( int type, int fld )
{
 int i, cnt = 0, max;
 XPFILE_DB *p;
 
 check();
 AryItem &ar = arraygroup.get(type, fldcheck(fld));
 for ( i = 0, max = ar.count; i < max; i++ )	{
 	 p = (XPFILE_DB *)ar.ar->GetAt(i);
	 if ( p != NULL && p->selected && !isDelFile(p) )
		cnt++;
     }
 return( cnt );
}


int FileListArray::getSelection( int type, int nSel, CWordArray &nar, int fld )
{
 
 int i, cnt = 0, max;
 XPFILE_DB *p;
 
 nar.SetSize(nSel,2);

 check();
 AryItem &ar = arraygroup.get(type, fldcheck(fld));
 for ( i = 0, max = ar.count; i < max; i++ )	{
 	 p = (XPFILE_DB *)ar.ar->GetAt(i);
	 if ( p != NULL && p->selected && !isDelFile(p) ) {
		nar[cnt++]=i;
		}
     }
 return( cnt );
}



void FileListArray::clearSel( int type, int fld )
{
int i, max; 
XPFILE_DB *p;

 check();
 AryItem &ar = arraygroup.get(type, fldcheck(fld));
 for ( i = 0, max = ar.count; i < max; i++ )	{
 	 p = (XPFILE_DB *)ar.ar->GetAt(i);
	 if ( p != NULL && p->selected && !isDelFile(p) )
		p->selected = 0;
     }
 
 dirty(1);
 return;
}


int FileListArray::findPtr( int type, XPFILE_DB *ptr )
{
 int i, max; 
 
 check();
 AryItem &ar = arraygroup.get(type,ptr->folder);
 for ( i = 0, max = ar.count; i < max; i++ )	
 	 if ( (XPFILE_DB *)ar.ar->GetAt(i) == ptr )
	    return( i );
return( -1 ); 
}

