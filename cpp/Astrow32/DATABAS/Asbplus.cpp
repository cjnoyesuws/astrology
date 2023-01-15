/*******************************************************************/
/*                                                                  */
/*             BPLUS file indexing program - Version 1.0            */
/*                                                                  */
/*                      A "shareware program"                       */
/*                                                                  */
/*                                                                  */
/*                      Copyright (C) 1987 by                       */
/*                                                                  */
/*                      Hunter and Associates                       */
/*                      7050 NW Zinfandel Lane                      */
/*                      Corvallis, Oregon  97330                    */
/*                      (503) 745 - 7186                            */
/*                                                                  */
/*  Altered by Christopher J. Noyes for Astro to use dynamic allo-  */
/*  cated memory, and case insensitive searches.                    */
/*       Also altered error handler to use popups altered so in     */
/*  in case of error, error handler uses longjmp to return control  */
/*  to top level function that called setjmp last. Date 8/22/88     */
/*  and top level routines return IX_ERROR to calling program       */
/*  8/22/92 adapt to windows c++ design.                            */
/*                                                                  */
/********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <sys\types.h>    /*  delete this line for Turbo C  */
#include <sys\stat.h>
#include <string.h>
#include "asbplus.h"
#include <errno.h>
#include "errors.fns"
#include <setjmp.h>

/*  macros, constants, data types  */

#define  NULLREC      (-1L)
#define  FREE_BLOCK   (-2)

#define  ENT_ADR(pb,off)  ((ENTRY*)((char*)((pb)->entries) + off))
#define  ENT_SIZE(pe)     strlen((pe)->key) + 1 + sizeof(short) + 2 * sizeof(RECPOS)
#define  BUFDIRTY(j)      (mci->cache[j].dirty)
#define  BUFHANDLE(j)     (mci->cache[j].handle)
#define  BUFBLOCK(j)      (mci->cache[j].mb)
#define  BUFCOUNT(j)      (mci->cache[j].count)
#define  CB(j)            (pci->pos[j].cblock)
#define  CO(j)            (pci->pos[j].coffset)


/*  declare some global variables  */

IX_DESC      *pci;
IX_BUFFER    *mci = NULL;
BLOCK        *block_ptr;
BLOCK        *spare_block;
short          cache_ptr = 0;
short          cache_init = 0;
short          split_size = IXB_SPACE;
short          comb_size  = (IXB_SPACE/2);
short          err_flag = 0;
short          keylen;
#if ( defined(_WIN32)  )
jmp_buf      jmp;
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )	
jmp_buf      jmp;
#else
CATCHBUF     catchsp;	
#endif
void error(short, long);
void read_if(long, char *, short);
void write_if(int, long, char *, short);
int  creat_if(char *);
int  open_if(char *);
void close_if(int);
void update_block(void);
void init_cache(void);
short  find_cache(RECPOS);
short  new_cache(void);
void load_cache(RECPOS);
void get_cache(RECPOS);
void retrieve_block(short, RECPOS);
short  prev_entry(short);
short  next_entry(short);
void copy_entry(ENTRY *, ENTRY *);
short  scan_blk(short);
short  last_entry(void);
void write_free( RECPOS, BLOCK *);
RECPOS get_free(void);
short  find_block(ENTRY *, short *);
void movedown(BLOCK *, short, short);
void moveup(BLOCK *, short, short);
void ins_block(BLOCK *, ENTRY *, short);
void del_block(BLOCK *, short);
void split(short, ENTRY *, ENTRY *);
void ins_level(short, ENTRY *);
short  insert_ix(ENTRY *, IX_DESC *);
short  find_ix(ENTRY *, IX_DESC *, short);
short  combineblk(RECPOS, short);
void replace_entry(ENTRY *);
void print_blk(BLOCK *);
void get_mem_if(void);

/*  file I/O for B-PLUS module  */

void error(short j,long l)
{
    if ( j < 3 ) 
       do_error( pci->file_name );
    else {
       do_mem_error( 0 );
       errno = ENOMEM;
       }
#if ( defined(_WIN32) )
	longjmp( jmp, 99 );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlrestoreovl();
    longjmp( jmp, 99 );
#else
    Throw( catchsp, 99 );  Throw
#endif
} /* error */


void read_if(long start,char *buf,short nwrt)
{
    long err;
    err = start - lseek(pci->ixfile, start, SEEK_SET);
    if (err == 0L) err = (long)( nwrt - read(pci->ixfile, buf, nwrt) );
    if (err != 0L) error(1, start);
} /* read_if */


void write_if(int handle, long start, char *buf, short nwrt)
{
    long err;
    err = start - lseek(handle, start, SEEK_SET);
    if (err == 0L) err = (long)(nwrt - write(handle, buf, nwrt) );
    if (err != 0L) error(2, start);
} /* write_if */


int creat_if(char *fn)
{
    int   ret;

    get_mem_if();
    ret = sopen(fn,O_RDWR|O_CREAT|O_TRUNC|O_BINARY,SH_DENYWR,S_IWRITE);
    if (ret  < 0) error(0,0L);
    return (ret);
} /* creat_if */


int open_if(char *fn)
{
    int  ret;

    get_mem_if();
    ret = sopen(fn,O_RDWR|O_BINARY,SH_DENYWR,S_IWRITE);
    if (ret < 1) error(0,0L);
    return (ret);
} /* open_if */


void close_if(int handle)
{
	if (close(handle) < 0)  error(0,0L);
} /*  close_if */


short open_index(char *name, IX_DESC *pix, short dup)
{

    pci = pix;
#if (defined (_WIN32) )
	if ( setjmp(jmp) ) {
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) ) {
#else
    if ( Catch(catchsp) ) {
#endif
       if ( pci->ixfile > 0 )
          close( pci->ixfile );
       return( IX_ERROR );
       }
    strcpy(pci->file_name, name );
    pci->ixfile = open_if(name);
    pci->duplicate = dup;
    read_if(0L,(char *)&(pix->root), (sizeof(BLOCK) + sizeof(IX_DISK)));
	if (!cache_init) {
        init_cache();
        cache_init = 1;
		}
    first_key(pix);
    return ( IX_OK );
} /* open_index */


short close_index(IX_DESC *pix)
{
    short i;
#if ( defined( _WIN32 ) )
	if ( setjmp(jmp) ) {
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) ) {
#else
    if ( Catch(catchsp) ) {
#endif
       if ( pix->ixfile > 0 )
	  close( pix->ixfile );
       return( IX_ERROR );
       }
    pci = pix;
    write_if(pix->ixfile, 0L,(char *)&(pix->root),
               (sizeof(BLOCK) + sizeof(IX_DISK)));
    for (i = 0; i < NUM_BUFS; i++)
	  if (BUFDIRTY(i) && (BUFHANDLE(i) == pix->ixfile)) {
		 write_if(BUFHANDLE(i),
				  BUFBLOCK(i).brec,
				  (char *) &BUFBLOCK(i),
				  sizeof(BLOCK));
		 BUFDIRTY(i) = 0;
		 }
    close_if(pix->ixfile);
    strcpy( pci->file_name, "" );
    return( IX_OK );
} /* close_index */


short make_index(char *name,IX_DESC *pix,short dup)
{
#if ( defined( _WIN32 ) )
	if ( setjmp(jmp) ) {
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) ) {
#else
    if ( Catch(catchsp) ) {
#endif
       if ( pix->ixfile > 0 )
	  close( pix->ixfile );
       return( IX_ERROR );
       }
    pci = pix;
    strcpy( pci->file_name, name );
    pci->ixfile = creat_if(name);
    pci->duplicate = dup;
    pci->dx.nlev = 1;
    pci->dx.ff = NULLREC;
    pci->level = 0;
    CO(0) = -1;
    CB(0) = 0L;
    pci->root.brec = 0L;
    pci->root.bend = 0;
    pci->root.p0 = NULLREC;
    write_if(pci->ixfile, 0L,(char *)&(pix->root),
               (sizeof(BLOCK) + sizeof(IX_DISK)));
	if (!cache_init) {
	   init_cache();
	   cache_init = 1;
	   }
    first_key(pix);
    return ( IX_OK );
} /* make_index */


/*  cache I/O for BPLUS  */

void update_block(void)
{
    if (block_ptr != &(pci->root))
       BUFDIRTY(cache_ptr) = 1;
} /* update_block */

     
void init_cache(void)
{
    register short  j;
	for (j = 0; j < NUM_BUFS; j++) {
		BUFDIRTY(j) = 0;
		BUFCOUNT(j) = 0;
		BUFBLOCK(j).brec = NULLREC;
		}
} /* init_cache */


short find_cache(RECPOS r)
{
    register short  j;
	for (j = 0; j < NUM_BUFS; j++) {
		if ((BUFBLOCK(j).brec == r) && (BUFHANDLE(j) == pci->ixfile)) {
		  cache_ptr = j;
		  return (1);
		  }
		}
    return (-1);
} /* find_cache */


short new_cache(void)
{
    register short  i;
    i = (cache_ptr + 1) % NUM_BUFS;
    if (BUFDIRTY(i)) write_if(BUFHANDLE(i),
                              BUFBLOCK(i).brec,
                              (char *) &BUFBLOCK(i),
                              sizeof(BLOCK));
    BUFHANDLE(i) = pci->ixfile;
    BUFDIRTY(i) = 0;
    return (i);
} /* new_cache */


void load_cache(RECPOS r)
{
	cache_ptr = new_cache();
    read_if(r, (char *)&BUFBLOCK(cache_ptr), sizeof(BLOCK));
} /* load_cache */


void get_cache(RECPOS r)
{
    if (find_cache(r) < 0)
       load_cache(r);
    block_ptr = &BUFBLOCK(cache_ptr);
} /* get_cache */


void retrieve_block(short j, RECPOS r )
{
    if (j == 0)
       block_ptr = &(pci->root);
    else  get_cache(r);
    CB(j) = block_ptr->brec;
} /* retrieve_block */


/*  low level functions of BPLUS  */

short prev_entry(short off)
{
	 if (off <= 0) {
		off = -1;
		CO(pci->level) = off;
		}
     else
		off = scan_blk(off);
     return(off);
} /* prev_entry */


short next_entry(short off )
{
     if (off == -1)
       off = 0;
	 else {
	   if (off < block_ptr->bend)
		  off += ENT_SIZE(ENT_ADR(block_ptr,off));
       }
     CO(pci->level) = off;
     return (off);
} /* next_entry */


void copy_entry(ENTRY *to, ENTRY *from)
{
    short me;
    me = ENT_SIZE(from);
    memcpy(to, from, me);
} /* copy_entry */


short scan_blk(short n)
{
     register short off, last;
     off = 0;
     last = -1;
	 while (off < n ) {
		last = off;
		off += ENT_SIZE(ENT_ADR(block_ptr,off));
		}
     CO(pci->level) = last;
     return (last);
} /* scan_blk */


short last_entry(void)
{
     return( scan_blk(block_ptr->bend) );
} /* last_entry *;


/*  maintain list of free index blocks  */

void write_free(RECPOS r, BLOCK *pb)
{
    pb->p0 = FREE_BLOCK;
    pb->brec = pci->dx.ff;
    write_if(pci->ixfile, r, (char *) pb, sizeof(BLOCK));
    pci->dx.ff = r;
} /* write_free */


RECPOS get_free(void)
{
    RECPOS  r, rt;

    r = pci->dx.ff;
	if ( r != NULLREC ) {
	   read_if(r, (char *)&rt, sizeof( RECPOS ));
	   pci->dx.ff = rt;
	   }
    else
	   r = filelength (pci->ixfile);
    return (r);
} /* get_free */


/*  general BPLUS block level functions  */

short find_block(ENTRY *pe, short *poff)
{
    register short pos, nextpos, ret;
    pos = -1;
    nextpos = 0;
    ret = 1;
	while ( nextpos < block_ptr->bend) {
        ret = strnicmp((char *)(pe->key),
                     (char *)(ENT_ADR(block_ptr, nextpos)->key), keylen);
		if (ret <= 0) {
		   if (ret == 0) pos = nextpos;
		   break;
		   }
        pos = nextpos;
        nextpos = next_entry(pos);
		}
    CO(pci->level) = pos;
    *poff = pos;
    return (ret);
} /* find_block */


void movedown(BLOCK *pb,short off,short n)
{
    memcpy(ENT_ADR(pb, off),
           ENT_ADR(pb, off + n),
           pb -> bend - (off + n));
} /* movedown */


void moveup(BLOCK *pb,short off,short n)
{
    memcpy(ENT_ADR(pb, off + n),
            ENT_ADR(pb, off),
            pb->bend - off);
} /* moveup */


void ins_block(BLOCK *pb,ENTRY *pe,short off)
{
    short size;
    size = ENT_SIZE(pe);
    moveup(pb,off,size);
    copy_entry(ENT_ADR(pb,off),pe);
    pb->bend += size;
} /* ins_block */


void del_block(BLOCK *pb,short off)
{
    short ne;
    ne = ENT_SIZE(ENT_ADR(pb, off));
    movedown(pb, off, ne);
    pb->bend -= ne;
} /* del_block */


/*  position at start/end of index  */

short first_key(IX_DESC *pix)
{
    
#if ( defined( _WIN32 ) ) 
	if ( setjmp(jmp) )
	   return( IX_ERROR );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif
       
    pci = pix;
    block_ptr = &(pci->root);
    CB(0) = 0L;
    CO(0) = -1;
    pci->level = 0;
	while(block_ptr->p0 != NULLREC) {
	   retrieve_block(++(pci->level), block_ptr->p0);
	   CO(pci->level) = -1;
	   }
    return ( IX_OK );
} /* first_key */


short last_key(IX_DESC *pix)
{
    long  ads;
#if ( defined( _WIN32 ) )
    if ( setjmp(jmp) )
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
#else
    if ( Catch(catchsp) ) 
#endif
       return( IX_ERROR );
    pci = pix;
    block_ptr = &(pci->root);
    CB(0) = 0L;
    pci->level = 0;
	if (last_entry() >= 0) {
	  while ((ads = ENT_ADR(block_ptr,last_entry())->idxptr) != NULLREC)
             retrieve_block(++(pci->level), ads);
      }
    CO(pci->level) = block_ptr->bend;
    return ( IX_OK );
} /* last_key */


/*  get next, previous entries  */

short next_key(ENTRY *pe, IX_DESC *pix)
{
    RECPOS  address;
#if ( defined( _WIN32 ) )
	if ( setjmp(jmp) )
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
#else
    if ( Catch(catchsp) ) 
#endif
       return( IX_ERROR );
    pci = pix;
    retrieve_block(pci->level, CB(pci->level));
    address = ENT_ADR(block_ptr, CO(pci->level))->idxptr;
	while (address != NULLREC) {
	  retrieve_block(++(pci->level), address);
	  CO(pci->level) = -1;
	  address = block_ptr->p0;
      }
    next_entry(CO(pci->level));
	if (CO(pci->level) == block_ptr->bend) {
	   do {
		  if (pci->level == 0) {
			last_key(pci);
			return (EOIX);
			}
            --(pci->level);
            retrieve_block(pci->level, CB(pci->level));
            next_entry(CO(pci->level));
		  } while (CO(pci->level) == block_ptr->bend);
	   }
    copy_entry(pe, ENT_ADR(block_ptr, CO(pci->level)));
    return ( IX_OK );
} /* next_key */


short prev_key(ENTRY *pe,IX_DESC *pix)
{
    RECPOS  address;
#if (defined(_WIN32) )  
	if ( setjmp(jmp) )
       return( IX_ERROR );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif
    pci = pix;
    retrieve_block(pci->level, CB(pci->level));
    prev_entry(CO(pci->level));
    if (CO(pci->level) == -1)
      address = block_ptr->p0;
    else
      address = ENT_ADR(block_ptr, CO(pci->level))->idxptr;
	if (address != NULLREC) {
	   do {
            retrieve_block(++(pci->level), address);
            address = ENT_ADR(block_ptr, last_entry())->idxptr;
          } while (address != NULLREC);
      }
	if (CO(pci->level) == -1) {
	   do {
		 if (pci->level == 0) {
		   first_key(pci);
		   return (EOIX);
		   }
            --(pci->level);
          } while (CO(pci->level) == -1);
        retrieve_block(pci->level, CB(pci->level));
      }
    copy_entry(pe, ENT_ADR(block_ptr, CO(pci->level)));
    return ( IX_OK );
} /* prev_key */


/*  insert new entries into tree  */

void split(short l,ENTRY *pe,ENTRY *e)
{
    short  half, ins_pos, size;
    ins_pos = CO(pci->level);
    half = scan_blk(block_ptr->bend / 2 + sizeof(RECPOS));
    if (half == ins_pos)
      *e = *pe;
	else {
	  copy_entry(e, ENT_ADR(block_ptr, half));
	  size = ENT_SIZE(e);
	  movedown(block_ptr, half, size);
	  block_ptr->bend -= size;
      }
    spare_block = &BUFBLOCK(new_cache());
    memcpy(spare_block->entries,
           ENT_ADR(block_ptr,half),
           block_ptr->bend - half);
    spare_block->brec = get_free();
    spare_block->bend = block_ptr->bend - half;
    spare_block->p0 = e->idxptr;
    block_ptr->bend = half;
    e->idxptr = spare_block->brec;
    if (ins_pos < half)
      ins_block(block_ptr,pe,ins_pos);
	else if (ins_pos > half) {
	  ins_pos -= ENT_SIZE(e);
	  ins_block(spare_block,pe,ins_pos - half);
	  CB(l) = e->idxptr;
	  CO(l) = CO(l) - half;
      }
    write_if(pci->ixfile, spare_block->brec,
             (char *) spare_block, sizeof(BLOCK));
} /* split */


void ins_level(short l,ENTRY *e)
{
    short  i;
	if ( l < 0) {
	   for (i = 1; i < MAX_LEVELS; i++) {
		   CO(MAX_LEVELS - i) = CO(MAX_LEVELS - i - 1);
		   CB(MAX_LEVELS - i) = CB(MAX_LEVELS - i - 1);
           }
         memcpy(spare_block, &(pci->root), sizeof(BLOCK));
         spare_block->brec = get_free();
         write_if(pci->ixfile, spare_block->brec,
                  (char *) spare_block, sizeof(BLOCK));
         pci->root.p0 = spare_block->brec;
         copy_entry((ENTRY *) (pci->root.entries), e);
         pci->root.bend = ENT_SIZE(e);
         CO(0) = 0;
         pci->level = 0;
	 (pci->dx.nlev)++;
      }
    else ins_block(block_ptr,e,CO(l));
} /* ins_level */


short insert_ix(ENTRY *pe,IX_DESC *pix)
{
    ENTRY    e, ee;
    pci = pix;
    ee = *pe;
    do
      {
		if (CO(pci->level) >= 0)
		  CO(pci->level) +=  ENT_SIZE(ENT_ADR(block_ptr, CO(pci->level)));
		else
           CO(pci->level) = 0;
         update_block();
		 if ( (block_ptr->bend + ENT_SIZE(&ee)) <= split_size) {
		   ins_level(pci->level, &ee);
		   break;
           }
		 else {
		   split(pci->level,&ee, &e);
		   ee = e;
		   pci->level--;
		   if (pci->level < 0) {
			  ins_level(pci->level, &e);
			  break;
			  }
		   retrieve_block(pci->level, CB(pci->level));
           }
      }
    while (1);
    return ( IX_OK );
} /* insert_ix */


/*  BPLUS find and add key functions  */

short find_ix(ENTRY *pe,IX_DESC *pix,short find)
{
    short      level, off, ret;
    RECPOS   ads;

    keylen = strlen( pe->key );
    pci = pix;
    ads = 0L;
    level = ret = 0;
	while (ads != NULLREC) {
	  pci->level = level;
	  retrieve_block(level, ads);
	  if (find_block(pe, &off) == 0) ret = 1;
	  if (ret && find) break;
	  if (off == -1)
		 ads = block_ptr->p0;
	  else
		 ads = ENT_ADR(block_ptr, off)->idxptr;
	  CO(level++) = off;
	  }
     return ( ret );
} /* find_ix */


short find_key(ENTRY *pe,IX_DESC *pix)
{
    short ret;

    keylen = strlen( pe->key );
    pci = pix;
#if ( defined( _WIN32 ) )
	if ( setjmp(jmp) )
       return( IX_ERROR );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif
    ret = find_ix(pe, pix, 1);
    if ( ret ) copy_entry(pe, ENT_ADR(block_ptr, CO(pci->level)));
    return ( ret );
} /* find_key */


short add_key(ENTRY *pe,IX_DESC *pix)
{
    short ret;

    pci = pix;
    keylen = strlen( pe->key );
#if ( defined( _WIN32 ) )
    if ( setjmp(jmp) )
       return( IX_ERROR );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif
       
    ret = find_ix(pe, pix, 0);
    if ( ret && (pci->duplicate == 0)) return ( IX_FAIL );
    pe->idxptr = NULLREC;
    return (insert_ix(pe, pix));
} /* add_key */


short locate_key(ENTRY *pe,IX_DESC *pix)
{
    short ret;

    pci = pix;
    keylen = strlen( pe->key );
#if ( defined( _WIN32 ) )
	if ( setjmp(jmp) )
       return( IX_ERROR );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif
       
    ret = find_ix(pe, pix, 1);
    if (ret) copy_entry(pe, ENT_ADR(block_ptr, CO(pci->level)));
    else next_key(pe,pix);
    return ( ret );
} /* locate_key */


short find_exact(ENTRY *pe,IX_DESC * pix)
{
    short  ret;
    ENTRY e;

    pci = pix;
    keylen = strlen( pe->key );  
#if ( defined( _WIN32 ) )
    if ( setjmp(jmp) )
       return( IX_ERROR );
    
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif

    copy_entry(&e, pe);
    ret = find_key(&e, pix);
	if ( ret && pci->duplicate) {
	   do {
		  ret = (e.recptr == pe->recptr);
		  if ( !ret )  ret = next_key(&e, pci);
		  if (ret) ret = (strnicmp(e.key, pe->key, keylen) == 0);
		  if ( !ret ) return ( 0 );
          } while ( !ret );
      }
    copy_entry(pe, &e);
    return ( ret );
} /* find_exact */


/* BPLUS delete key functions */

short delete_key(ENTRY *pe,IX_DESC *pix)
{
     ENTRY   e;
     RECPOS  ads;
     short     h, leveli, levelf;

    pci = pix;
#if ( defined( _WIN32 ) )
    if ( setjmp(jmp) )
       return( IX_ERROR );
#elif ( !defined(_Windows) && !defined(_WINDOWS)  )
    rtlsaveovl();
    if ( setjmp(jmp) )
       return( IX_ERROR );
#else
    if ( Catch(catchsp) ) 
       return( IX_ERROR );
#endif

     if (!find_exact(pe, pix))  return( IX_FAIL );
     h = 1;
	 if ((ads = pe->idxptr) != NULLREC) {
		leveli = pci->level;
		do {
		   retrieve_block(++(pci->level), ads);
		   CO(pci->level) = -1;
		   } while ((ads = block_ptr->p0) != NULLREC);
		 CO(pci->level) = 0;
		 copy_entry(&e, ENT_ADR(block_ptr, CO(pci->level)));
		 levelf = pci->level;
		 pci->level = leveli;
		 replace_entry(&e);
		 pci->level = levelf;
		 }
	 while ( h ) {
          retrieve_block(pci->level, CB(pci->level));
          del_block(block_ptr, CO(pci->level));
          update_block();
		  if ( (pci->level == 0) && (block_ptr->bend == 0)) {
			 if (pci->root.p0 != NULLREC) {  /* tree was reduced in height */
				 retrieve_block(++pci->level, pci->root.p0);
				 memcpy(&(pci->root), block_ptr, sizeof(BLOCK));
				 (pci->dx.nlev)--;
				 write_free(block_ptr->brec, block_ptr);
				 BUFDIRTY(cache_ptr) = 0;
				 BUFHANDLE(cache_ptr) = 0;
				 }
              break;
            }
          h = (block_ptr->bend < comb_size) && (pci->level > 0);
          if ( h )
              h = combineblk(CB(pci->level), block_ptr->bend);
       }
    return( IX_OK );
} /* delete_key */


short combineblk(RECPOS ads, short size)
{
    ENTRY  e;
    RECPOS address;
    short    esize, off, ret, saveoff, ibuff;
    ret = 0;
    saveoff = CO(--(pci->level));
    retrieve_block(pci->level, CB(pci->level));
	if ((off = next_entry( saveoff )) < block_ptr->bend) {
      /* combine with page on right */
	   if ( (ENT_SIZE(ENT_ADR(block_ptr, off)) + size) < (unsigned short) split_size) {
		  copy_entry(&e, ENT_ADR(block_ptr, off));
		  address = ENT_ADR(block_ptr, CO(pci->level))->idxptr;
		  retrieve_block(++pci->level, address);
		  ibuff = cache_ptr;
		  spare_block = block_ptr;
		  retrieve_block(pci->level, ads);
		  esize = ENT_SIZE(&e);
		  if (((block_ptr->bend + spare_block->bend + esize) >= split_size)
                 && (spare_block->bend <= block_ptr->bend + esize))
               return( ret );
		  e.idxptr = spare_block->p0;
		  ins_block(block_ptr, &e, block_ptr->bend);
		  update_block();
		  if ((block_ptr->bend + spare_block->bend) < split_size) {
		   /* combine the blocks */
			 memcpy(ENT_ADR(block_ptr, block_ptr->bend),
					ENT_ADR(spare_block, 0),
					spare_block->bend);
			 block_ptr->bend += spare_block->bend;
			 write_free(spare_block->brec, spare_block);
			 BUFDIRTY(ibuff) = 0;
			 BUFHANDLE(ibuff) = 0;
			 --pci->level;
			 ret = 1;
			 }
			else {
            /* move an entry up to replace the one moved */
			  copy_entry(&e, ENT_ADR(spare_block, 0));
			  esize = ENT_SIZE(&e);
			  movedown(spare_block, 0, esize);
			  spare_block->bend -= esize;
			  spare_block->p0 = e.idxptr;
			  BUFDIRTY(ibuff) = 1;
			  --(pci->level);
			  replace_entry(&e);
              }
          }
      }
    else
      /* move from page on left */
      {
		if ( (ENT_SIZE(ENT_ADR(block_ptr, CO(pci->level))) + size)
			< (unsigned short) split_size) {
            copy_entry(&e, ENT_ADR(block_ptr, saveoff));
            off = prev_entry(saveoff);
            if (CO(pci->level) == -1) address = block_ptr->p0;
            else address = ENT_ADR(block_ptr, CO(pci->level))->idxptr;
            retrieve_block(++pci->level, address);
            off = last_entry();
            ibuff = cache_ptr;
            spare_block = block_ptr;
            retrieve_block(pci->level, ads);
            esize = ENT_SIZE(&e);
			if (((block_ptr->bend + spare_block->bend + esize) >= split_size)
                 && (spare_block->bend <= block_ptr->bend + esize))
               return( ret );
            BUFDIRTY(ibuff) = 1;
            CO(pci->level) = 0;
            e.idxptr = block_ptr->p0;
            ins_block(block_ptr, &e, 0);
			if ((block_ptr->bend + spare_block->bend) < split_size) {
            /* combine the blocks */
			   memcpy(ENT_ADR(spare_block, spare_block->bend),
					ENT_ADR(block_ptr, 0),
					block_ptr->bend);
			   spare_block->bend += block_ptr->bend;
			   write_free(block_ptr->brec, block_ptr);
			   BUFDIRTY(cache_ptr) = 0;
			   BUFHANDLE(cache_ptr) = 0;
			   CO(--(pci->level)) = saveoff;
			   ret = 1;
			   }
			else {
            /* move an entry up to replace the one moved */
			  block_ptr->p0 = ENT_ADR(spare_block,off)->idxptr;
			  copy_entry(&e, ENT_ADR(spare_block, off));
			  spare_block->bend = off;
			  update_block();
			  CO(--(pci->level)) = saveoff;
			  replace_entry(&e);
              }
          }
      }
    return ( ret );
} /* combineblk */


void replace_entry(ENTRY *pe)
{
    retrieve_block(pci->level, CB(pci->level));
    pe->idxptr = ENT_ADR(block_ptr, CO(pci->level))->idxptr;
    del_block(block_ptr, CO(pci->level));
    prev_entry(CO(pci->level));
    insert_ix(pe, pci);
} /* replace_entry */

void free_index_mem(void)
{
 delete mci;
 mci = NULL;
#if ( !defined(_Windows) && !defined(_WINDOWS)  )
 free_ovl_status();
#endif
}

void get_mem_if()
{
 if ( mci != NULL )
    return;
 if (( mci = (IX_BUFFER *) new IX_BUFFER ) == NULL )
    error(3,0L);
 memset( mci, 0, sizeof( IX_BUFFER ) );

}

void clear_err()
{
 err_flag = 0;
}
