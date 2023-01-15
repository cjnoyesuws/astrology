

class CSymbol {
    protected:
	char _name[40];
	char _descrip[75];
	int _value;
	int _position;
	int _limit;
	int _referenced;
	char _symtype[25];
 public:
	CSymbol() {_position=0; _limit=1; _referenced=0; memset(_name,0,40); memset(_descrip,0,75); memset(_symtype,0,25); }
	~CSymbol() {}
	virtual int Read(FILE *stream);
	int &referenced() { return _referenced; }
	int &value() { return _value; }
	int &limit() { return _limit; }
	int &position() { return _position; }
	char *name() { return _name; }
	char *descrip() { return _descrip; }
	char *symtype() { return _symtype; }
	};

class CRSymbol : public CSymbol {
     public:
	CRSymbol() {}
	~CRSymbol() {}
	virtual int Read(FILE *stream);
	};

class CSymbolAry {
protected:
    int type;
    int _nElements;  /* count in array */
    int _nAlloc;     /* Allocated Space */
    int _iEle;       /* current Element */
    CSymbol *_array;
  public:
	CSymbolAry(int size=500)  { _nElements = 0; _nAlloc = size; _iEle = 0; _array = new CSymbol[size]; }
    ~CSymbolAry() { delete[] _array; _array = NULL; }
    int Load( char *name="TEXT.SYM" );
    CSymbol *Find( const char *sym, int pos=-1, int lin=0 );
	CSymbol *Find( const wchar_t *sym, int pos=-1, int lin=0 );
    int toCombo( CComboBox *cmb, int which, char *typ, int pos2=-1 );
    char *toSymName( CString &s );
	int toArrayCombo( CComboBox *cmb, CString &symtyp );
};

class CRSymbolAry : public CSymbolAry {
  public:
	CRSymbolAry(int size=200)  { _nElements = 0; _nAlloc = size; _iEle = 0; _array = new CRSymbol[size]; }
    CRSymbol *Find( const char *sym, int lin=0 ) { return((CRSymbol *) CSymbolAry::Find(sym, -1, lin ) ); }
        CRSymbol *Find( const wchar_t *sym, int lin=0 ) { return((CRSymbol *) CSymbolAry::Find(sym, -1, lin ) ); }
	int toCombo( CComboBox *cmb, int w, char *tp ) { return( CSymbolAry::toCombo(cmb,w,tp)); }   
    int Load( char *name="REPORT.SYM" ) { return CSymbolAry::Load(name); }
};

extern CSymbolAry *pRegSymbols;
extern CRSymbolAry *pRepSymbols;