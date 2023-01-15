
class CTextBlock {
   int _type;
   char _IDstring[130];
   int _text_len;
   zString _text;
 public:
   CTextBlock() {}
   ~CTextBlock() {}
   int &type() { return _type; }
   char *IDstring() { return _IDstring; }
   int &text_len() { return _text_len; }
   zString &text() { return _text;  }
   int WriteText( FILE *stream );
   int ReadText( FILE *stream );
   int put( char *p ) { _text = p; _text_len = strlen(p); return 1; }
   int put( char *p, int l ) { _text = p; _text_len = l; return 1; }
   int put( zString &s ) { _text = s; _text_len = s.length(); return 1; }
   int SetID( char *id, int n );
   int SetID( char *id1, char *id2 );
   int SetID( char *id1, char *id2, char *id3  );
   int GetIDParts( char *id, int *n );
   int GetIDParts( char *id1, char *id2 );
   int GetIDParts( char *id1, char *id2, char *id3 );
   int ReadHeader( FILE *stream, int *prev, char *prid );
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
    CTextBlock **_array;
 public:
    CTextBlockAry() { _type = 0; _bDirty = 0; _nElements = 0; _nAlloc = 0; _iEle = 0; }
    ~CTextBlockAry() { delete[] _array; _array = NULL;}
    CTextBlock *Find( CTextBlock *b );
    CTextBlock *Find( char *id, int n );
    CTextBlock *Find( char *id1, char *id2 );
    CTextBlock *Find( char *id1, char *id2, char *id3 );
    int Save( char *name );
    int Add( CTextBlock *b );
    Load( char *name, int start_size, int tp );
    void Xref( CSymbolAry *p );
    int &isDirty() { return _bDirty; }
    };

extern int CTextBlockCmp( const void * const p1, const void * const p2 );
