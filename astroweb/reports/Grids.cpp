#include "astro.h"
#include "useri.h"
#include "output.fns"
#include "flags.h"
#include <vector>
#include <string>
#include "sqlite3pp.h"
#include "exception"
#include "grids.h"
#include "oututil.h"
#include "sstream"

const char *nbsp = "@NB";

GridRow::GridRow(int c)
{
 m_cols = c;
 m_data.resize(m_cols);
 for ( int i = 0; i < m_cols; i++ ) {
	 m_data[i]=nbsp;
	 }
 m_mod = 0;
}

std::string GridRow::getRowText(std::string &str) {
 str = "";
 if ( !m_mod )
	return str;
 for ( int i = 0; i < m_cols; i++ ) {
	 std::string col = m_data[i];
	 if ( col.size() > 0 )
		 str += col;
	 else
		 str += nbsp;
	 if ( i < m_cols-1 )
		 str += "|";
	 else
		 str += "@TR\n";
    }
 return str;
 }


GridStruct::GridStruct(int cols, int rows) {
 m_rows = rows;
 m_cols = cols;
 m_data.resize(rows);
 for ( int i = 0; i < rows; i++ ) {
     addRow(new GridRow(cols));
     }
}

GridStruct::~GridStruct() {
  for ( int i = 0; i < m_rows; i++ ) {
	  GridRow *rw = m_data[i];
      if ( rw != NULL )
		  delete rw;
      }
 m_data.clear();
}

void GridStruct::addRow(GridRow *pRow)
{
 m_data[m_rows++]=pRow;
}


std::string GridStruct::getRowText(int i)
{
 std::string str = "";
 GridRow *pAr;
 if ( i < 0 || i > m_rows-1 )
	 return str;
 else {
     pAr = m_data[i];
	 if ( pAr != NULL )
		 return pAr->getRowText(str);
	 else
		 return str;
    }
 }


void GridStruct::setRowCol(int row, int col, const char *p)
{
	if ( row >= 0 && row < m_rows && col >= 0 && col < m_cols ) {
	   GridRow *pAr = m_data[row];
	   pAr->setCol(col,p);
	}
}


std::string GridStruct::getRowCol(int row, int col)
{
	if ( row >= 0 && row < m_rows && col >= 0 && col < m_cols ) {
	   GridRow *pAr = (GridRow *)m_data[row];
	   return pAr->getCol(col);
	}
	else
	   return std::string("");
}



std::string GridStruct::getGridText() {
  std::stringstream str = std::stringstream();
  str << "@TB\x80";
  for ( int i = 0; i < m_rows; i++ ) {
     std::string s = getRowText(i);
	 if ( s.length()==0 ) {
		 continue;
		 }
	 str << s << "\n";
     }

  str << "@TB\n";
  return str.str();
}

int AspectGridStr::translate(int p)
{
 if ( m_grid_type == FIXED_DI || m_grid_type == ARABP_DI )
	 return p;
 else {
     if ( p < CUPIDO )
		 return p;
	 else if ( m_grid_mode & ASTEROID )
		 return p;
	 else
		 return( p - (HOUSE_1-CUPIDO) );
 }
}

AspectGridStr::AspectGridStr(int pl, int pldp, int type, int mode) : GridStruct(pl+1,pldp+1)
{
 m_grid_mode = mode;
 m_grid_type = type;
 for ( int i = 1; i < pl+1; i++ )
	 setRowCol(0,i,(char *)planet_str(i-1));
 for ( int j = 1; j < pldp+1; j++ ) {
#ifdef PRO
	 if ( type == ARABP_DI )
        setRowCol(j,0,(char *)arabic_part_str(j-1));
	 else if ( type == FIXED_DI )
	    setRowCol(j,0,(char *)fixed_star_str(j-1));
	 else
#else
	 if ( true )
#endif
	 {
        setRowCol(j,0,(char *)planet_str(translate(j-1)));
	    }
     }
}

void AspectGridStr::makeGrid( AS_INF *inf, int cnt, int start )
{
 char buf[40];
 AS_INF *infptr;
 ASPEC *asps;
 int i, j;
 for ( i = 0, infptr = inf; i < cnt; i++, infptr++ ) {
	 if ( infptr->no_aspects > 0 ) {
		 for ( j = 0, asps=infptr->aspectr; j < infptr->no_aspects; asps++, j++ ) {
		     sprintf(buf,"%s %d",aspect_str(asps->aspect),asps->orb);
			 setRowCol(translate(asps->planet)+1,i+1+start,buf);
		    }
	     }
    }
}


void MidpointGridStr::makeGrid( AS_INF *inf, int cnt, int start )
{
 char buf[40];
 AS_INF *infptr;
 MIDPT *midps;
 int i, j;
 for ( i = 0, infptr = inf; i < cnt; i++, infptr++ ) {
	 if ( infptr->no_midpt > 0 ) {
		 for ( j = 0, midps=infptr->midptr; j < infptr->no_midpt; midps++, j++ ) {
			 if ( !(m_grid_mode & HALF_MID) && (j % 2)==1 )
                 setRowCol(i+start+1,translate(midps->second_planet)+1,format_degs(midps->total_minutes, buf));
			 else
			     setRowCol(translate(midps->second_planet)+1,i+start+1,format_degs(midps->total_minutes, buf));
			}
	     }
    }
}

ProgMoonAspectGridStr::ProgMoonAspectGridStr(int pl, int pldp, int type, int mode) : AspectGridStr(pl+1,pldp+1, type, mode)
{
 int j;
 char buf[25];
 m_grid_mode = mode;
 m_grid_type = type;
 for ( int i = 1; i < pl+1; i++ )
	 setRowCol(0,i,(char *)planet_str(i-1));
 for ( j = 1; j < pldp+1; j++ ) {
	 sprintf(buf,"Moon Month #%d", j );
	 setRowCol(j,0,buf);
     }
}


MidAspectGridStr::MidAspectGridStr(int pldp, int type, int mode) :
	GridStruct(10,pldp+1) {
  char buf[5];
  m_grid_mode = mode;
  m_grid_type = type;
  m_cur_row = 0;
  m_cur_col = 0;
  setRowCol(0,1,"Planets");
  setRowCol(0,2,"Aspect to");
  setRowCol(0,3,"Aspect");
  setRowCol(0,4,"Planets");
  setRowCol(0,5,"Aspect to");
  setRowCol(0,6,"Aspect");
  setRowCol(0,7,"Planets");
  setRowCol(0,8,"Aspect to");
  setRowCol(0,9,"Aspect");
  for ( int i = 1; i < pldp; ++i ) {
	  sprintf(buf,"%d", i );
	  setRowCol(i,0,buf);
      }
}


int MidAspectGridStr::whichCol()
{
 if ( m_cur_col == 9 )
	 m_cur_col = 0;
 int col = m_cur_col;
 m_cur_col+= 3;
 if ( col == 0 ) {
    m_cur_row++;
	if ( m_cur_row > getRows()-1 )
		addRow();
    }
 return ( col );
}

void MidAspectGridStr::addRow()
{
 GridRow *prow = new GridRow(getCols());
 char buf[10];
 getRows()++;
 sprintf(buf, "%d", m_cur_row );
 prow->setCol(0,buf);
 GridStruct::addRow(prow);
}

void MidAspectGridStr::makeGrid( AS_INF *inf, int cnt, int start, int radix )
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
			    col = whichCol();
                sprintf(buf1,"%s/%s", planet_str(i+start), planet_str(midptr->second_planet) );
				setRowCol(m_cur_row,col+1,buf1);
				setRowCol(m_cur_row,col+2,(char *)planet_str(aspectr->planet));
				sprintf(buf2,"%s: %d",aspect_str(aspectr->aspect), aspectr->orb );
			    setRowCol(m_cur_row,col+3,buf2);
			    }
		     }
	    }
     }
}
