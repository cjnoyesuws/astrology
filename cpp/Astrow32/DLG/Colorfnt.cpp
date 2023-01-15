#include "stdafx.h"
#include "inifile.hpp"
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

int saveColorToIni(const char *sec, const char *entry, COLORREF &c  )
{
 CString a; 

 a.Format("%lx", (DWORD)c );
 AfxGetApp()->WriteProfileString( sec, entry, a );
 return(1);
}

int readColorFromIni(const char *sec, const char *entry, COLORREF &c  )
{
 unsigned long lx;
 CString a;
 
 a.Format( "%lx", (DWORD)c );
 a = AfxGetApp()->GetProfileString( sec, entry, a );
 sscanf( a, "%lx", &lx );
 c = (DWORD)lx;
 return( 1 );
}

int saveFontToIni(const char *sec, const char *entry, LOGFONT *f, int pointsize  )
{
 CString a;

 a.GetBuffer(150);
 a.Format( "%s,%d,%d,%d,%d,%d,%d", f->lfFaceName,
   (int)f->lfPitchAndFamily, f->lfHeight, f->lfWeight, (int)f->lfItalic,
   (int)f->lfUnderline, pointsize );
 AfxGetApp()->WriteProfileString( sec, entry, a );

return( 1 );
}

int readFontFromIni(const char *sec, const char *entry, LOGFONT *f, int &pointsize )
{
 int u, i, fm;
 CString a;

 a.GetBuffer(150);
 a.Format( "%s,%d,%d,%d,%d,%d,%d", f->lfFaceName,
   (int)f->lfPitchAndFamily, (int)f->lfHeight, (int)f->lfWeight, (int)f->lfItalic,
   (int)f->lfUnderline, (int)pointsize );
 a = AfxGetApp()->GetProfileString( sec, entry, a );
 sscanf( a, "%[^,],%d,%d,%d,%d,%d,%d", f->lfFaceName,
   &fm, &f->lfHeight, &f->lfWeight, &i, &u, &pointsize );
 f->lfUnderline = u;
 f->lfItalic= i;
 f->lfPitchAndFamily = fm;
 return( 1 );
}


int saveFontColorToIni(const char *sec, char *entry, LOGFONT *f, COLORREF &c, int pointsize  )
{
 int r;
 CString a, a2;
 
 a = entry;
 a += "Color";
 a2 = entry;
 a2 += "Font";
 r = saveColorToIni(sec, (LPCTSTR)a, c );
 saveFontToIni(sec, (LPCTSTR)a2, f, pointsize );
 return( 1 );
}

int readFontColorFromIni(const char *sec, char *entry, LOGFONT *f, COLORREF &c, int &pointsize  )
{
 CString a, a2;
 
 a = entry;
 a += "Color";
 a2 = entry;
 a2+= "Font";
 readColorFromIni(sec, (LPCTSTR)a, c );
 readFontFromIni(sec, (LPCTSTR)a2, f, pointsize );
 return(1);
}



