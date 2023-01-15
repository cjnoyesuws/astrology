

class CSymbol {
    protected:
	char _name[40];
	char _descrip[60];
	int _value;
	int _position;
	int _limit;
	int _referenced;
     public:
	CSymbol() {}
	~CSymbol() {}
	virtual int Read(FILE *stream);
	virtual int Write(FILE *stream);
	int &referenced() { return _referenced; }
	int &value() { return _value; }
	int &limit() { return _limit; }
	int &position() { return _position; }
	char *name() { return _name; }
	char *descrip() { return _descrip; }
	};

class CRSymbol : public CSymbol {
     public:
	CRSymbol() {}
	~CRSymbol() {}
	virtual int Read(FILE *stream);
	virtual int Write(FILE *stream);
	};

class CSymbolAry {
    int type;
    int _nElements;  /* count in array */
    int _nAlloc;     /* Allocated Space */
    int _iEle;       /* current Element */
    CSymbol *_array;
  public:
    CSymbolAry() { _nElements = 0; _nAlloc = 0; _iEle = 0; _array = NULL; }
    ~CSymbolAry() { delete[] _array; _array = NULL; }
    int Load( char *name, int start_size );
    int Save( char *name );
    CSymbol *Find( char *sym, int pos=-1, int lin=0 );
    int toCombo( zComboBoxBase *cmb, int which, int incl );
    };

extern char *toSymName( char *sel );
