#include "stdafx.h"
#include "afxcoll.h"
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "FILELST.HPP"

int FileListArray::iBottom( int type, int fld )
{
return( arraygroup.get(type,fldcheck(fld)).count-1 );
}

int FileListArray::iTop( int type, int fld )
{
 return( 0 );
}


XPFILE_DB *FileListArray::bottom( int type, int fld )
{
 AryItem &ar = arraygroup.get(type,fldcheck(fld));
 return (XPFILE_DB *)ar.ar->GetAt(ar.count-1);	
}


XPFILE_DB *FileListArray::top( int type, int fld )
{
 return( (XPFILE_DB *)arraygroup.get(type,fldcheck(fld)).ar->GetAt(0) );
}


XPFILE_DB *FileListArray::bottomMinus( int val, int type, int fld )
{
 AryItem &ar = arraygroup.get(type,fldcheck(fld));
 if ( ar.count < val )
	return( NULL );
 val++;
 return (XPFILE_DB *) ar.ar->GetAt(ar.count-val);	 
}

XPFILE_DB *FileListArray::topPlus( int val, int type, int fld )
{
 AryItem &ar = arraygroup.get(type,fldcheck(fld));
 if ( ar.count <= val )
	return( NULL );
 return (XPFILE_DB *) ar.ar->GetAt(val+1);	 
}



int FileListArray::iTopPlus( int val, int type, int fld )
{
 AryItem &ar = arraygroup.get(type,fldcheck(fld));
 if ( ar.count <= val )
	return( -1 );
 return( val+1 );
}


int FileListArray::iCursor( int val, int type, int fld )
{
 AryItem &ar = arraygroup.get(type,fldcheck(fld));
 if ( ar.count <= val )
	return( -1 );
 return( val );
}

