
/*  bplus.h - data structures and constants  */

#define NO_DUPS     0
#define OK_DUPS     1 
#define IX_OK       1
#define IX_FAIL     0
#define IX_ERROR    -1
#define EOIX       (-2)
#define MAXKEY      102
#define NUM_BUFS    10
#define MAX_LEVELS  6
#define IXB_SIZE    512
#define IXB_SPACE  (IXB_SIZE - sizeof(short) - sizeof(long) * 2)
#define memcpy(d,s,n) memmove((d),(s),(n))

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

#pragma pack(2)
typedef long RECPOS;
typedef struct ENTRY              /*  entry structure in index         */
  {  RECPOS   idxptr;             /*  points to lower index level      */
     RECPOS   recptr;             /*  points to data record            */
     short      data_len;           /*  length of data record pointed to */
     char     key[MAXKEY];        /*  start of record key              */
  }  ENTRY;

typedef struct BLOCK              /*  index record format             */
  {  RECPOS   brec;               /*  position in index file          */
                                  /*  or location of next free block  */
     short      bend;               /*  first unused block location     */
     RECPOS   p0;                 /*  points to next level            */
     char     entries[IXB_SPACE]; /*  here are the key entries        */
  }  BLOCK;

typedef struct IX_DISK            /*  disk file info                  */
  {  RECPOS   ff;                 /*  location of first free block    */
     short     nlev;               /*  number of index levels          */
  }  IX_DISK;

typedef struct MEMBLOCK           /*  memory buffer pool of indx blks */
  {  short      dirty;              /*  true if changed                 */
     short      handle;             /*  index file handle               */
     short      count;              /*  number of times referenced      */
     BLOCK    mb;
  }  MEMBLOCK;

typedef struct IX_BUFFER
  {  MEMBLOCK     cache [ NUM_BUFS ];
  }  IX_BUFFER;

typedef struct  IX_DESC           /*  in-memory index descriptor      */
  {  short      ixfile;
     short      level;              /*  level in btree                  */
     short      duplicate;          /*  no duplicate keys if 0          */
     struct
       {  RECPOS    cblock;       /*  position in index file          */
          short       coffset;      /*  current offset within block     */
       }  pos [ MAX_LEVELS ];
     BLOCK    root;               /*  root index record               */
     IX_DISK  dx;
     char file_name[150];
  }  IX_DESC;

#pragma pack()
short open_index(char *,IX_DESC *, short);
short close_index(IX_DESC *);
short make_index(char *,IX_DESC *, short);
short first_key(IX_DESC *);
short last_key(IX_DESC *);
short next_key(ENTRY *, IX_DESC *);
short prev_key(ENTRY *, IX_DESC *);
short find_key(ENTRY *, IX_DESC *);
short add_key(ENTRY *, IX_DESC *);
short locate_key(ENTRY *, IX_DESC *);
short delete_key(ENTRY *, IX_DESC *);
short find_exact(ENTRY *, IX_DESC *);
void free_index_mem(void);












