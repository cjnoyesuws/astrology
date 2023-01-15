#include <stdafx.h>
#include <afxcoll.h>
#include "astro.h"
#include "useri.h"
#include "output.fns"
#include "flags.h"
#include "grids.h"
#include "oututil.h"

static char *nbsp = "@NB";

GridRow::GridRow(int c)
{
 cols = c;
 SetSize(cols,5);
 for ( int i = 0; i < cols; i++ )
	 SetAt(i,nbsp);
 mod = 0;
}

void GridRow::SetCol(int col, const char *p )
{
	if ( col >= 0 && col < cols ) {
	   const char * pg =(const char *)GetAt(col);
	   if ( pg != nbsp && p != NULL )
		   delete pg;
	   SetAt(col,_strdup(p));
	   }
 if ( col != 0 )
	 mod = 1;
}

GridRow::~GridRow()
{
 for ( int i = 0; i < GetSize(); i++ ) {
	 void *p = GetAt(i);
	 if ( p != NULL && p != nbsp )
		 delete p;
     }
  RemoveAll();
}

const char *GridRow::GetCol( int col )
{
 if ( col >= 0 && col < cols ) {
	return( (const char *)GetAt(col) );
    }
 else
     return( NULL );
}

CString &GridRow::GetRowText(CString &str)
{
 str = "";
 if ( !mod )
	return str;
 for ( int i = 0; i < cols; i++ ) {
     const char *p;
	 p = (const char *)GetAt(i);
	 if ( p != NULL )
		 str += p;
	 else 
		 str += nbsp;
	 if ( i < cols-1 )
		 str += "|";
	 else
		 str += "@TR\n";
    }
 return str;
 }
     

GridStruct::GridStruct(int c, int r)
{
 rows = r;
 cols = c;
 SetSize(r,1);
 for ( int i = 0; i < rows; i++ ) {
     SetAt(i,new GridRow(c));
     }
}

GridStruct::~GridStruct()
{
  for ( int i = 0; i < rows; i++ ) {
	  GridRow *rw = (GridRow *)GetAt(i);
      if ( rw != NULL )
		  delete rw;
      }
 RemoveAll();
}

void GridStruct::AddRow()
{
 SetAtGrow(rows++,new GridRow(cols));
}


CString &GridStruct::GetRowText(int i)
{
 m_str = "";
 GridRow *pAr;
 if ( i < 0 || i > rows-1 )
	 return m_str;
 else {
     pAr = (GridRow*)GetAt(i);
	 if ( pAr != NULL )
		 return pAr->GetRowText(m_str);
	 else 
		 return m_str;
    }
 }


void GridStruct::SetRowCol(int row, int col, char *p)
{
	if ( row >= 0 && row < rows && col >= 0 && col < cols ) {
	   GridRow *pAr = (GridRow *)GetAt(row);
	   pAr->SetCol(col,p);
	}
}


CString GridStruct::GetRowCol(int row, int col)
{
	if ( row >= 0 && row < rows && col >= 0 && col < cols ) {
	   GridRow *pAr = (GridRow *)GetAt(row);
	   return pAr->GetCol(col);
	}
	else
	   return CString("");
}


void GridStruct::SaveGrid(FILE *stream)
{
 CString s;
 fprintf( stream, "@TB\x80");
 for ( int i = 0; i < rows; i++ ) {
     s = GetRowText(i);
	 if ( !s.GetLength() )
		 continue;
	 fwrite((void *)(LPCTSTR)s,1,s.GetLength(),stream);
     }
 fprintf( stream, "@TB\n");
}


int AspectGridStr::translate(int p)
{
 if ( gtype == FIXED_DI || gtype == ARABP_DI )
	 return p;
 else {
     if ( p < CUPIDO )
		 return p;
	 else if ( gmode & ASTEROID )
		 return p;
	 else
		 return( p - (HOUSE_1-CUPIDO) );
 }
}

AspectGridStr::AspectGridStr(int pl, int pldp, int type, int mode) : GridStruct(pl+1,pldp+1)
{
 gmode = mode;
 gtype = type;
 for ( int i = 1; i < pl+1; i++ ) 
	 SetRowCol(0,i,(char *)planet_str(i-1));
 for ( int j = 1; j < pldp+1; j++ ) {
#ifdef PRO
	 if ( type == ARABP_DI )
        SetRowCol(j,0,(char *)arabic_part_str(j-1));
	 else if ( type == FIXED_DI )
	    SetRowCol(j,0,(char *)fixed_star_str(j-1));
	 else 
#else
	 if ( true )
#endif
	 {
        SetRowCol(j,0,(char *)planet_str(translate(j-1)));
	    }
     }
}

void AspectGridStr::MakeGrid( AS_INF *inf, int cnt, int start )
{
 char buf[40];
 AS_INF *infptr;
 ASPEC *asps;
 int i, j;
 for ( i = 0, infptr = inf; i < cnt; i++, infptr++ ) {
	 if ( infptr->no_aspects > 0 ) {
		 for ( j = 0, asps=infptr->aspectr; j < infptr->no_aspects; asps++, j++ ) {
		     sprintf(buf,"%s %d",aspect_str(asps->aspect),asps->orb);
			 SetRowCol(translate(asps->planet)+1,i+1+start,buf);
		    }
	     }
    }
}


void MidpointGridStr::MakeGrid( AS_INF *inf, int cnt, int start )
{
 char buf[40];
 AS_INF *infptr;
 MIDPT *midps;
 int i, j;
 for ( i = 0, infptr = inf; i < cnt; i++, infptr++ ) {
	 if ( infptr->no_midpt > 0 ) {
		 for ( j = 0, midps=infptr->midptr; j < infptr->no_midpt; midps++, j++ ) {
			 if ( !(gmode & HALF_MID) && (j % 2)==1 )
                 SetRowCol(i+start+1,translate(midps->second_planet)+1,format_degs(midps->total_minutes, buf));
			 else
			     SetRowCol(translate(midps->second_planet)+1,i+start+1,format_degs(midps->total_minutes, buf));
			}
	     }
    }
}

ProgMoonAspectGridStr::ProgMoonAspectGridStr(int pl, int pldp, int type, int mode) : AspectGridStr(pl+1,pldp+1, type, mode)
{
 int j;
 char buf[25];
 gmode = mode;
 gtype = type;
 for ( int i = 1; i < pl+1; i++ ) 
	 SetRowCol(0,i,(char *)planet_str(i-1));
 for ( j = 1; j < pldp+1; j++ ) {
	 sprintf(buf,"Moon Month #%d", j );
	 SetRowCol(j,0,buf);
     }
}


MidAspectGridStr::MidAspectGridStr(int pldp, int type, int mode) :
	GridStruct(10,pldp+1) {
  char buf[5];
  gmode = mode;
  gtype = type;
  currow = 0;
  curcol = 0;
  SetRowCol(0,1,"Planets");
  SetRowCol(0,2,"Aspect to");
  SetRowCol(0,3,"Aspect");
  SetRowCol(0,4,"Planets");
  SetRowCol(0,5,"Aspect to");
  SetRowCol(0,6,"Aspect");
  SetRowCol(0,7,"Planets");
  SetRowCol(0,8,"Aspect to");
  SetRowCol(0,9,"Aspect");
  for ( int i = 1; i < pldp; ++i ) {
	  sprintf(buf,"%d", i );
	  SetRowCol(i,0,buf);
      }
}


int MidAspectGridStr::whichcol() 
{
 if ( curcol == 9 )
	 curcol = 0;
 int col = curcol;
 curcol+= 3;
 if ( col == 0 ) {
    currow++;
	if ( currow > GetRows()-1 )
		AddRow();
    }
 return ( col );
}

void MidAspectGridStr::AddRow()
{
 GridRow *prow = new GridRow(GetCols());
 char buf[10];
 GetRows()++;
 sprintf(buf, "%d", currow );
 prow->SetCol(0,buf);
 SetAtGrow(currow,prow);
}

void MidAspectGridStr::MakeGrid( AS_INF *inf, int cnt, int start, int radix )
{
 AS_INF *infptr;
 ASPEC *aspectr;
 MIDPT *midptr;
 int i, j, k, col, apcnt;
 char buf1[75], buf2[75];

 for ( infptr = inf, i = 0; i < cnt; infptr++, i++ ) {
	 if ( infptr->no_midpt > 0 ) {
		 for ( midptr = infptr->midptr, j = 0; j < infptr->no_midpt; j++, midptr++ ) {
			 if ( radix && midptr->no_aspect > 0 ) {
			    apcnt = midptr->no_aspect;
				aspectr = midptr->aspectr;
			    }
			 else if ( !radix && midptr->no_alt_aspect > 0 ) {
			    apcnt = midptr->no_alt_aspect;
				aspectr = midptr->altaspectr;			 
			    }
			 else {
			    apcnt = 0;
				aspectr = NULL;
				}
			 for ( k = 0; k < apcnt; k++, aspectr++ ) {
			    col = whichcol();
                sprintf(buf1,"%s/%s", planet_str(i+start), planet_str(midptr->second_planet) );
				SetRowCol(currow,col+1,buf1);
				SetRowCol(currow,col+2,(char *)planet_str(aspectr->planet));
				sprintf(buf2,"%s: %d",aspect_str(aspectr->aspect), aspectr->orb );
			    SetRowCol(currow,col+3,buf2); 
			    }		 		 
		     }	 
	    } 
     }
}