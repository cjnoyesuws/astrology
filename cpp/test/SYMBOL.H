 

class  CSymbol {

	char _name[40];
	char _descrip[60];
	char _symtype[10];
	int _position;
	int _limit;
	int _referenced;
	int _value;
	virtual int Read( file *stream );
   CSymbol() { position=0; limit=1; referenced=0; memset(name,0,40); memset(descrip,0,60); memset(symtype,0,10); }
   virtual ~CSymbol() {}
   };

class CRSymbol : CSymbol {
   CRSymbol() {}
   virtual ~CRSymbol() {}
   virtual int Read( file *stream );
	};


class CSymbolAry {
    int type;
    int nElements;  /* count in array */
    int nAlloc;     /* Allocated Space */
    int iEle;       /* current Element */
    CSymbol *array;
    CSymbolAry(int start_size=200) { type=1; nElements=0; iEle=0; nAlloc=start_size;
    array=new CSymbol[start_size]; }
    int toComboBox( CComboBox *, int pos=1, char *typ=NULL, int pos2=-1);
    int Read(char *name="Text.sym");   
    ~CSymbolAry() { delete array; }
    CSymbol *Find( char *sym, int lin, int pos );
    
};

class CRSymbolAry {
    CRSymbolAry(int start_size=100) { type=0; nElements=0; iEle=0; nAlloc=start_size;
    array=new CRSymbol[start_size]; }
    int Read(char *name="report.sym") { return CSymbol::Read(name); }   
    ~CRSymbolAry() { delete array; }
    CRSymbol *Find( char *sym, int lin) { return (CRSymbol *)CSymbol::Find(sym,lin,1); }
    
    };

extern CSymbolAry *pRegSymbols;
extern CRSymbolAru *pRepSymbols;