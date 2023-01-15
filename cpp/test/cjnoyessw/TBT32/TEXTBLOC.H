

class CTextBlock {
   int type;
   char IDstring[130];
   int text_len;
   TCHAR *text;
   CTextBlock() { type=0; memset(IDString,0,130); text_len=0; text=NULL; }
   ~CTextBlock() { if (text != NULL ) delete text; }
#ifdef _UNICODE
   int ReadTextMbs( FILE *stream, int help );
#endif
   int ReadText( FILE *stream, int help );
   int SetID( char *id, int n );
   int SetID( char *id1, char *id2 );
   int SetID(char *id1, char *id2, char *id3  );
   int GetIDParts( char *id, int *n );
   int GetIDParts( char *id1, char *id2 );
   int GetIDParts( char *id1, char *id2, char *id3 );
   int ReadHeaderR( FILE *stream, int *prev, TCHAR *prid );
   int ReadHeader2( FILE *stream );
   int ReadHeader3( FILE *stream );
   int WriteHeader( FILE *stream );
   int WriteHeaderR( FILE *stream );
   int WriteText( FILE *stream );
   };

class CTextBlockAry {
    int type;
    int bDirty;
    int nElements;  /* count in array */
    int nAlloc;     /* Allocated Space */
    int iEle;       /* current Element */
    CTextBlock *array;
    CTextBlockAry(int tp, int start_size=400) { type=tp, nAlloc=start_size; nElements=0; bDirty=0; iEle=0; array=new CTextBlock[start_size]; }
    ~CTextBlockAry() { delete array; } 
    CTextBlock *Find( CTextBlock *b );
    CTextBlock *Find( char *id, int n );
    CTextBlock *Find( char *id1, char *id2 );
    CTextBlock *Find( char *id1, char *id2, char *id3 );
    int Save( char *name );
    int Load( char *name, int help = 0);
    void reset() { iEle = 0; }
    CTextBlock *next() { if ( iEle >= nElements ) return NULL; else return(&array[iEle++]); }
   };

extern int CTextBlockAryFileType( char *name );
extern CString &CTextBlockAryTexttype( char *name );
extern int CTextBlockCmp( const void * const p1, const void * const p2 );
extern void CTextBlockAryXref( CTextBlockAry *t, struct CSymbolAry *s );

