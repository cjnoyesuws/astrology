

typedef struct CSymbol {
	char name[40];
	char descrip[60];
	int position;
	int limit;
	int referenced;
	} CSymbol;

typedef struct CSymbolAry {
    int nElements;  /* count in array */
    int nAlloc;     /* Allocated Space */
    int iEle;       /* current Element */
    CSymbol *array;
    } CSymbolAry;


extern int CSymbolRead( CSymbol *p, FILE *stream );
extern int CRSymbolRead( CSymbol *p, FILE *stream );
extern int CSymbolCmp( void const * const p1, void const * const p2 );
extern int CSymbolAryLoad( CSymbolAry *s, char *name, int start_size );
extern CSymbol *CSymbolAryFind( CSymbolAry *s, char *sym, int lin, int pos );
extern int CSymbolAryKill( CSymbolAry *s );
extern int CSymbolAryMenu( CSymbolAry *s, int which, char *str, int incl );

