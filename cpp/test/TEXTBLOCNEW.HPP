
class CTextBlock {
   int _type;
   CString _IDstring;
   int _text_len;
   CString _text;
 public:
   CTextBlock() {}
   ~CTextBlock() {}
   int &type() { return _type; }
   CString &IDstring() { return _IDstring; }
   int &text_len() { return _text_len; }
   CString &text() { return _text;  }
   int WriteText( FILE *stream );
   int ReadText( FILE *stream, int help );
   int put( TCHAR *p ) { _text = p; _text_len = tcslen(p); return 1; }
   int put( TCHAR *p, int l ) { _text = p; _text_len = l; return 1; }
   int put( CString &s ) { _text = s; _text_len = s.GetLength(); return 1; }
   int SetID( CString &id, int n );
   int SetID( CString &id1, CString &id2 );
   int SetID( CString &id1, CString &id2, CString &id3  );
   int GetIDParts( CString &id, int *n );
   int GetIDParts( CString &id1, CString &id2 );
   int GetIDParts( CString &id1, CString &id2, CString &id3 );
   int ReadHeader( FILE *stream, int *prev, CString &prid );
   int ReadHeader2( FILE *stream );
   int ReadHeader3( FILE *stream );
   int WriteHeader( FILE *stream );
   int WriteHeaderR( FILE *stream );
   };

class CTextBlockAry {
    int _type;
    int _bDirty;
    int _nElements;  /* count in array */
    int _nAlloc;     /* Allocated Space */
    int _iEle;       /* current Element */
    CTextBlock *_array;
 public:
	CTextBlockAry(int tp, int size) { _type = tp; _bDirty = 0; _nElements = 0; _nAlloc = size; _iEle = 0; _array = new CTextBlock[size]; }
    ~CTextBlockAry() { delete[] _array; _array = NULL;}
    CTextBlock *Find( CTextBlock *b );
    CTextBlock *Find( CString &id, int n );
    CTextBlock *Find( CString &id1, CString &id2 );
    CTextBlock *Find( CString &id1, CString &id2, CString &id3 );
    int Save( char *name );
    int Add( CTextBlock *b );
    int Load( char *name, int help=0 );
    //void Xref( CSymbolAry *p );
    int &isDirty() { return _bDirty; }
	CTextBlock *next() { if ( _iEle >= _nElements ) return NULL; else return _array+_iEle++; }
    int &nElements() { return _nElements; }
	};

extern int __cdecl CTextBlockCmp( const void * p1, const void * p2 );
extern void setupBuf(int i);