#ifndef GRIDS_H
#define GRIDS_H 1

class GridRow : public CPtrArray {
   int cols;
   int mod;
public :
	int &GetCols() { return cols; }
	virtual ~GridRow();
	GridRow() { cols=0; SetSize(0,5); }
	GridRow(int c);
    void SetCol(int col, const char *p );
	const char *GetCol( int col );
	CString &GetRowText(CString &s);
	int GetMod() { return mod; }
};

class GridStruct : public CObArray {
   int rows;
   int cols;
   CString m_str;
public :
   virtual ~GridStruct();
   GridStruct() { rows = 0, cols = 0; }
   GridStruct(int r, int c);
protected :
   void AddRow();
   CString &GetRowText(int i);
   void SetRowCol(int row, int col, char *p);
   CString GetRowCol(int row, int col);
   int &GetRows() { return rows; }
   int &GetCols() { return cols; }
public :
   void SaveGrid(FILE *stream);
};

class AspectGridStr : public GridStruct {
protected :
	int gmode;
    int gtype;
	int translate(int p);
public :
	AspectGridStr(int pl, int pldp, int type, int mode);
	void MakeGrid( AS_INF *inf, int cnt, int start=0 );
};

class MidpointGridStr : public AspectGridStr {
public :
	MidpointGridStr(int pl, int pldp, int type, int mode) : AspectGridStr(pl, pldp, type, mode) {}
	void MakeGrid( AS_INF *inf, int cnt, int start=0 );
};

class ProgMoonAspectGridStr : public AspectGridStr {
public :
	ProgMoonAspectGridStr(int pl, int pldp, int type, int mode);
};

class MidAspectGridStr : public GridStruct {
protected :
	int gmode;
    int gtype;
	int currow;
	int curcol;
	int whichcol();
    void AddRow();
public :
	MidAspectGridStr(int pldp, int type, int mode);
	void MakeGrid( AS_INF *inf, int cnt, int start=0, int radix=1 );

};
#endif