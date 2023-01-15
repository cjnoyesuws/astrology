

#define TYPE_HELP    0
#define TYPE_REPORT  1
#define TYPE_REGULAR 2
#define TYPE_ASPECT  3

class CATextType {
    int _type;
    char _descrip[75];
    char _symtypes[50];
	char _dest[25];
	int _hasarray;
    public:
	CATextType() { memset(_descrip,0,75); memset(_symtypes,0,50); memset(_dest,0,25);}
    ~CATextType() {}
    int &type() { return _type; }
    char *descrip() { return _descrip; }
    char *dest() { return _dest; }
    char *symtypes() { return _symtypes; }
	int &hasArray() { return _hasarray; }
	int Read( FILE *stream ); 
   };

class CATextTypeAry {
    unsigned int _nElements;  /* count in array */
    unsigned int _nAlloc;     /* Allocated Space */
    int _iEle;       /* current Element */
    CATextType *_array;
  public:
    CATextTypeAry(int start_size=220) { _nElements = 0; _nAlloc = start_size; _iEle = 0; _array=new CATextType[start_size]; }
    ~CATextTypeAry() { delete [] _array; _array = NULL; }
    unsigned int &nElements() { return _nElements; }
    unsigned int &nAlloc() { return _nAlloc; }
    int &iEle() { return _iEle; }
    CATextType *array() { return _array; }
    int Load( char *name="TEXTTYPE.LST" );
    int toListBox( CListBox *lb, int which, int ary=0 );
    CATextType *Find( CString &sel, int tp, int lin=0 );
    char *toSymType( CString &name, int tp ) { CATextType *pf=Find(name, tp); if ( pf==NULL) return NULL; else return( pf->symtypes() ); }
    char *toTextType( CString &s ); 
    int toType( CString &name, int tp ) { CATextType *pf=Find(name, tp); if ( pf==NULL) return NULL; else return( pf->type() ); }
    int toTextTypeCombo( CComboBox *pBox, int tp, int ary=0 );
   };

extern int __cdecl CATextTypeCmp( void const * p1, void const *  p2 );

extern CATextTypeAry *pATextTypes;

