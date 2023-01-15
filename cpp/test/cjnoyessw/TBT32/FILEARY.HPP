#ifndef TYPE_HELP

#define TYPE_HELP    0
#define TYPE_REPORT  1
#define TYPE_REGULAR 2
#define TYPE_ASPECT  3

class CAsFile {
    int _type;
    char _descrip[75];
    char _name[25];
    char _symbols[9];
	char _dest[40];
    public:
		CAsFile() { memset(_descrip,0,75); memset(_name,0,25); memset(_symbols,0,9); memset(_dest,0,25);}
    ~CAsFile() {}
    int type() { return _type; }
    char *descrip() { return _descrip; }
    char *name() { return _name; }
    char *symbols() { return _symbols; }
    char *dest() { return _dest; }
	int Read( FILE *stream ); 
   };

class CAsFileAry {
    unsigned int _nElements;  /* count in array */
    unsigned int _nAlloc;     /* Allocated Space */
    int _iEle;       /* current Element */
    CAsFile *_array;
  public:
    CAsFileAry(int start_size=170) { _nElements = 0; _nAlloc = start_size; _iEle = 0; _array=new CAsFile[start_size]; }
    ~CAsFileAry() { delete [] _array; _array = NULL; }
    unsigned int &nElements() { return _nElements; }
    unsigned int &nAlloc() { return _nAlloc; }
    int &iEle() { return _iEle; }
    CAsFile *array() { return _array; }
    int Load( char *name="TFILE.LST" );
    int toListBox( CListBox *lb, int which );
    CAsFile *Find( const char *name, int lin=0 );
    char *toTextType( const char *name ) { CAsFile *pf=Find(name); if ( pf==NULL) return NULL; else return( pf->dest() ); }
    TCHAR *toFileName( const TCHAR *sel ); 
	char *toFileName( CString &sel ); 
    int toType( const char *name ) { CAsFile *pf=Find(name); if ( pf==NULL) return NULL; else return( pf->type() ); }
    int toTextTypeCombo( CComboBox *pBox );
    int getCount( int t );   
};

extern int __cdecl CAsFileCmp( void const * p1, void const * p2 );

extern CAsFileAry *pFileList;

#endif