#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "mselist.hpp"

// Set the Caret
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
void zMultiSelListUnsorted::caret(int i)
{
 SendMessage(hWnd,LB_SETCARETINDEX,i,0L);
}

// Get the Caret

int zMultiSelListUnsorted::caret()
{
 return( (int)SendMessage(hWnd,LB_GETCARETINDEX,0,0L) );
}

// get the selection count

int zMultiSelListUnsorted::selCount()
{
 return( (int)SendMessage(hWnd,LB_GETSELCOUNT,0,0L) );
}

// get a list of each item that is selected.

int zMultiSelListUnsorted::selection(int n, int *l)
{
 return( (int)SendMessage(hWnd,LB_GETSELITEMS,n, (DWORD)l) );
}

// select a range of items from f to l if s is TRUE they are selected, etc.

int zMultiSelListUnsorted::selection(int f, int l, BOOL s)
{
 return( (int)SendMessage(hWnd,LB_SELITEMRANGE,s,MAKELPARAM(f,l) ) );
}
