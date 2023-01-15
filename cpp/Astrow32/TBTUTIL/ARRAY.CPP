#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include "array.hpp"

dataArray::dataArray( int r, int c, int ds )
{
 rows = r;                
 cols = c;
 data_size = ds;
 handle = 0;
 handle = GlobalAlloc( GHND, ((long)(r * c) * ds) );
 ptr = NULL;
 ptr = (LPVOID)GlobalLock(handle);
}

dataArray::~dataArray()
{
 GlobalUnlock( handle );
 GlobalFree(handle);
}

LPVOID dataArray::getPtr( int r, int c )
{
 long ofs;

 ofs = cols * r;
 ofs += c;
 ofs *= data_size;
 return( (LPVOID)((char *)ptr+ofs) );
}


dataArray3d::dataArray3d( int r, int c, int dp, int es ) : dataArray( r, c, dp * es )
{
 element_size = es;
 depth = dp;
}

LPVOID dataArray3d::getPtr( int r, int c, int d )
{
 long ofs;

 ofs = cols * r;
 ofs += c;
 ofs *= data_size;
 ofs += (d * element_size );
 return( LPVOID ((char *)ptr+ofs) );
}

