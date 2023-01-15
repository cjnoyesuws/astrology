#ifndef _DATABASEODBC_HPP_
#define _DATABASEODBC_HPP_
#pragma warning( disable : 4995 )
#include "DBirthset.h"
#include "DRelocationset.h"
#include "DLocationset.h"
#include "DRectification.h"
#include "DTransitset.h"
#ifndef BIRTH_DB
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#endif

class DaoDatabase {
protected:
	  CDaoRecordset *pSet;
	  int doExecDelete( char *p );
      CString &fmtLongLat( DEG_MIN &rec, CString &str );
      CString &quote( const char *pChar, CString & str );
	  void parseLongLat( CString &str, DEG_MIN &dat );
	  void extractDate( COleDateTime &date, DATES &dt );
public:
	DaoDatabase(CDaoRecordset *p) { pSet=p; }
    virtual ~DaoDatabase() {}
      //void key_error( char *key, char *msg );
      // low level functions
      //long write_rec( short size, long offset, void *data );
      //short read_rec( short size, long offset, void *data );
      //short del_rec( long o, short l );
      //short startup();
      //void shutdown();
      // high level access

	  virtual int transfer( int save=0 ) = 0;
      virtual int checkRec( int wh=0 ) = 0;
	  virtual int dosave();
	  virtual int dodelete() = 0;
	  virtual int find();
      };

class DaoLocDatabase : public DaoDatabase {
protected:
public:
      LOC_DB loc;
	  CDLocationset locset;
	  DaoLocDatabase()  : DaoDatabase(&locset) {}
      virtual ~DaoLocDatabase() { if ( locset.IsOpen() ) locset.Close(); }
      virtual int checkRec( int wh=0 );
	  virtual int dodelete();
	  virtual int transfer( int save=0 );
	  void setLoc( LOC_DB &l ) { loc = l; }
	  LOC_DB &getLoc() { return loc; }
	};

class DaoBirthDatabase : public DaoDatabase {
	  CDBirthset birthset;
	  CDRectification rectset;
	  BIRTH_DB birth;
	  RECT_DATA rect;
	  int isRect;
public:
	DaoBirthDatabase() : DaoDatabase(&birthset) { isRect = 0; }
    virtual ~DaoBirthDatabase() { if (birthset.IsOpen() ) birthset.Close(); if (rectset.IsOpen() ) rectset.Close(); }
      	  void setBirth( BIRTH_DB& b ) { birth = b; }
	  void setRect( RECT_DATA & r ) { rect= r; if ( rect.birth_time_known ) isRect=0; else isRect=1; }
      BIRTH_DB &getBirth() { return birth; }
	  RECT_DATA *getRect() { return &rect; }
	  virtual int transfer( int save=0 );
      virtual int checkRec( int wh=0 );
	  virtual int dodelete();
	  virtual int dosave();
	  virtual int find();
      };

class DaoTransitDatabase : public DaoDatabase {
	  CDTransitset transset;
	  BIRTH_DB birth, trans;
public:
	DaoTransitDatabase()  : DaoDatabase(&transset) { }
      virtual ~DaoTransitDatabase() { if ( transset.IsOpen() ) transset.Close(); }
      void setBirth( BIRTH_DB& b ) { birth = b; }
	  void setTrans( BIRTH_DB & t ) { trans= t; }
      BIRTH_DB &getTrans() { return trans; }
	  virtual int transfer( int save=0 );
	  virtual int checkRec( int wh=0 );
	  virtual int dodelete();
      };

class DaoRelocateDatabase : public DaoDatabase {
	  BIRTH_DB birth;
	  LOC_DB reloc;
	  CDRelocationset relocset;
	  CString personal;
public:
	DaoRelocateDatabase() : DaoDatabase(&relocset) { }
	virtual ~DaoRelocateDatabase() { if ( relocset.IsOpen() ) relocset.Close(); }
      void setBirth( BIRTH_DB& b ) { birth = b; }
	  void setReloc( LOC_DB & l, CString &per ) { reloc=l; personal=per; }
	  LOC_DB &getReloc() { return reloc; }
	  CString &getPersonal() { return personal; }
	  virtual int transfer( int save=0 );
	  virtual int checkRec( int wh=0 );
	  virtual int dodelete();
      };

#endif /* _DATABASE_HPP_ */
