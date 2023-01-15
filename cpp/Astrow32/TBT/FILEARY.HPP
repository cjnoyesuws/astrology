

class CAsFile {
    int _type;
    char _descrip[75];
    char _name[9];
    char _symbols[13];
    public:
    CAsFile() {}
    ~CAsFile() {}
    int &type() { return _type; }
    char *descrip() { return _descrip; }
    char *name() { return _name; }
    char *symbols() { return _symbols; }
    int Read( FILE *stream );
    };

class CAsFileAry {
    unsigned int _nElements;  /* count in array */
    unsigned int _nAlloc;     /* Allocated Space */
    int _iEle;       /* current Element */
    CAsFile *_array;
  public:
    CAsFileAry() { _nElements = 0; _nAlloc = 0; _iEle = 0; }
    ~CAsFileAry() { delete []_array; _array = NULL; }
    unsigned int &nElements() { return _nElements; }
    unsigned int &nAlloc() { return _nAlloc; }
    int &iEle() { return _iEle; }
    CAsFile *array() { return _array; }
    int Load( char *name, int start_size );
    int toListBox( zListBoxBase *lb, int which );
    CAsFile *Find( char *name, int lin = 1 );
    };

extern int CAsFileCmp( void const * const p1, void const * const p2 );

extern CAsFileAry tbtEditFiles;

