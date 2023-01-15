#include "stdafx.h"
#include <stdlib.h>
#include "pageopt.hpp"
#include "inifile.hpp"

// Classes to manage Page dimension data and margins
// Useage:
//
//  PageDataDlgf *pd = new PageDataDlgf(out,
//     &printPageData );
//  if ( pd->completed() ) {
//     pd->getData();
//     zRect &s = printPageData.getPageSize();
//     out->printf("High = %d\n", s.height() );
//     zRect &r = printPageData.getMargins();
//     out->printf("Top = %d\n", r.top() );
//     out->printf("Left = %d\n", r.left() );
//     out->printf("Bottom = %d\n", r.bottom() );
//     out->printf("Right = %d\n", r.right() );
//     }
//  delete pd;
//


int PageData::saveToIni( char *sec )
{
 CString b;

 b.Format("%d %d %d %d", (int)margins.left, (int)margins.top,
     (int)margins.right, (int)margins.bottom );
 AfxGetApp()->WriteProfileString( sec, "Margins", (char *)(LPCTSTR)b );
 return( 1 );
}


int PageData::getFromIni( char *sec )
{
 int l, t, r, b;
 CString bf;

 bf = AfxGetApp()->GetProfileString( sec, "Margins", "75 75 75 75" );
 sscanf( (char *)(LPCTSTR)bf, "%d %d %d %d", &l, &t, &r, &b );
 margins = CRect( l, t, r, b );
 return( 1 );
}


/*PageDataDlgf::PageDataDlgf( zWindow *pPar, PageData *pP )
		   : FormDlgf( pPar, zResId("PAGE_OPT"), HELPID_DLG_PAGEOPT )
{
 char buf[10];
 form_data = pP;

 zRect &r = form_data->getMargins();
 sprintf( buf, "%01d.%02d", r.top()/100,
   r.top()%100 );
 top = buf;
 new zStringEdit(this, IDC_PGTOP, &top, "9'.'99" );

 sprintf( buf, "%01d.%02d", r.left()/100,
   r.left()%100 );
 left = buf;
 new zStringEdit(this, IDC_PGLT, &left, "9'.'99");

 sprintf( buf, "%01d.%02d", r.bottom()/100,
   r.bottom()%100 );
 bottom = buf;
 new zStringEdit(this, IDC_PGBTM, &bottom, "9'.'99");

 sprintf( buf, "%01d.%02d", r.right()/100,
   r.right()%100 );
 right = buf;
 new zStringEdit(this, IDC_PGRT, &right, "9'.'99");
 run();
}

void PageDataDlgf::getData()
{
 form_data->getPageSize() =
   zRect( 0, 0, (int)(atof(width)*100.0),
            (int)(atof(high)*100.0) );
  form_data->getMargins() =
    zRect( (int)(atof(left)*100.0),(int)(atof(top)*100.0),
    (int)(atof(right)*100.0),(int)(atof(bottom)*100.0));
}
*/