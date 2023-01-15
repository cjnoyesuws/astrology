#ifdef VIRTUAL
#include <vmemory.h>
#endif


typedef struct CTextBlock {
   int type;
   char IDstring[130];
   int text_len;
   char *text;
#ifdef VIRTUAL
   _vmhnd_t handle;
#endif
   } CTextBlock;

typedef struct CTextBlockAry {
    int type;
    int bDirty;
    int nElements;  /* count in array */
    int nAlloc;     /* Allocated Space */
    int iEle;       /* current Element */
    CTextBlock **array;
    } CTextBlockAry;

extern int CTextlockAryFileType( char *name );
extern int CTextBlockReadText( CTextBlock *ptb, FILE *stream );
extern int CTextBlockSetIDR( CTextBlock *ptb, char *id, int n );
extern int CTextBlockSetID2( CTextBlock *ptb, char *id1, char *id2 );
extern int CTextBlockSetID3( CTextBlock *ptb, char *id1, char *id2, char *id3  );
extern int CTextBlockGetIDPartsR( CTextBlock *ptb, char *id, int *n );
extern int CTextBlockGetIDParts2( CTextBlock *ptb, char *id1, char *id2 );
extern int CTextBlockGetIDParts3( CTextBlock *ptb, char *id1, char *id2, char *id3 );
extern int CTextBlockReadHeaderR( CTextBlock *ptb, FILE *stream, int *prev, char *prid );
extern int CTextBlockReadHeader2( CTextBlock *ptb, FILE *stream );
extern int CTextBlockReadHeader3( CTextBlock *ptb, FILE *stream );
extern int CTextBlockWriteHeader( CTextBlock *ptb, FILE *stream );
extern int CTextBlockWriteHeaderR( CTextBlock *ptb, FILE *stream );
extern int CTextBlockWriteText( CTextBlock *ptb, FILE *stream );
extern int CTextBlockCmp( const void * const p1, const void * const p2 );
extern CTextBlock *CTextBlockAryFind( CTextBlockAry *t, CTextBlock *b );
extern CTextBlock *CTextBlockAryFindR( CTextBlockAry *t, char *id, int n );
extern CTextBlock *CTextBlockAryFind2( CTextBlockAry *t, char *id1, char *id2 );
extern CTextBlock *CTextBlockAryFind3( CTextBlockAry *t, char *id1, char *id2, char *id3 );
extern int CTextBlockAryKill( CTextBlockAry *t );
extern int CTextBlockArySave( CTextBlockAry *t, char *name );
extern int CTextBlockAryAdd( CTextBlockAry *t, CTextBlock *b );
extern int CTextBlockAryLoad( CTextBlockAry *t, char *name, int start_size, int tp );
extern void CTextBlockAryXref( CTextBlockAry *t, struct CSymbolAry *s );
#ifdef VIRTUAL
extern int CTextBlockGet( CTextBlock *ptb );
extern int CTextBlockRelease( CTextBlock *ptb );
extern int CTextBlockPut( CTextBlock *ptb );

#endif
