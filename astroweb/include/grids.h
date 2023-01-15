#ifndef GRIDS_H
#define GRIDS_H 1

#include <string>
#include <sstream>
#include <vector>

class GridRow {
   std::vector<std::string> m_data;
   int m_cols;
   int m_mod;
public :

	int &getCols() { return m_cols; }
	virtual ~GridRow() {}
	GridRow() { m_cols=0; m_data.resize(5); }
	GridRow(int c);
    void setCol(int col, std::string val ) { m_data[col] = val;}
    std::string getCol( int col ) { return m_data[col]; }
	std::string getRowText(std::string &str);
	int getMod() { return m_mod; }
};

class GridStruct {
   int m_rows;
   int m_cols;
   std::string m_str;
   std::vector <GridRow*> m_data;
public :
   virtual ~GridStruct();
   GridStruct() { m_rows = 0, m_cols = 0; }
   GridStruct(int r, int c);
protected :
   void addRow(GridRow *pRow);
   std::string getRowText(int i);
   void setRowCol(int row, int col, const char *p);
   std::string getRowCol(int row, int col);
   int &getRows() { return m_rows; }
   int &getCols() { return m_cols; }
public :
   std::string getGridText();
};

class AspectGridStr : public GridStruct {
protected :
	int m_grid_mode;
    int m_grid_type;
	int translate(int p);
public :
	AspectGridStr(int pl, int pldp, int type, int mode);
	void makeGrid( AS_INF *inf, int cnt, int start=0 );
};

class MidpointGridStr : public AspectGridStr {
public :
	MidpointGridStr(int pl, int pldp, int type, int mode) : AspectGridStr(pl, pldp, type, mode) {}
	void makeGrid( AS_INF *inf, int cnt, int start=0 );
};

class ProgMoonAspectGridStr : public AspectGridStr {
public :
	ProgMoonAspectGridStr(int pl, int pldp, int type, int mode);
};

class MidAspectGridStr : public GridStruct {
protected :
	int m_grid_mode;
    int m_grid_type;
	int m_cur_row;
	int m_cur_col;
	int whichCol();
    void addRow();
public :
	MidAspectGridStr(int pldp, int type, int mode);
	void makeGrid( AS_INF *inf, int cnt, int start=0, int radix=1 );

};
#endif
