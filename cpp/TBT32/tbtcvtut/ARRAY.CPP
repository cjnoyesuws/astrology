#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include "array.hpp"

dataArray::dataArray( int r, int c )
{
 rows = r;                
 cols = c;
 ptr = new TXTPT * [r];  
 for ( int i = 0; i < r; i++ )
     ptr[i] = new TXTPT[c];
}

dataArray::~dataArray()
{
 
 for ( int i = 0; i < rows; i++ )
     delete ptr[i];
 delete ptr; 
}

TXTPT *dataArray::getPtr( int r, int c )
{
 long ofs;
 TXTPT *pt = ptr[r];
 return ( &pt[c] );
}


dataArray3d::dataArray3d( int r, int c, int dp ) : dataArray( r, c * dp )
{
 depth = dp;
}

LPVOID dataArray3d::getPtr( int r, int c, int d )
{
 int colpos = (c * depth) + d;
 TXTPT *pt = ptr[r];
 return ( &pt[colpos] );
}

