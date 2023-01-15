#ifndef TEXTGETTER_H
#define TEXTGETTER_H 1

#include <bitset>
using namespace std;
class GenericTextGetter {
   protected:
      BOOL bErrorState;
      CDaoRecordset *pSet;
      CDaoQueryDef *pQuery;
      CDaoDatabase *pDatabase;
      CString texttype;
      CString dummyText;
   public:
      void OpenSetAndQuery( char *tt, char *qry );
      GenericTextGetter( char *p, CDaoDatabase *pDb ) { pDatabase=pDb; texttype=p; pQuery=new CDaoQueryDef(pDb); }
      virtual ~GenericTextGetter() { if (pSet->IsOpen()) pSet->Close(); if (pQuery->IsOpen() ) pQuery->Close(); delete pQuery; delete pSet; }
   };


class RegTextGetter : GenericTextGetter {
   public:
      RegTextGetter( char *p, CDaoDatabase *pDb );
      int GetText( int k1, int k2, FILE *stream );
      const char *GetText( int k1, int k2 );
   };



class AspTextGetter : GenericTextGetter {
   public:
      AspTextGetter( char *p, CDaoDatabase *pDb );
      int GetText( int k1, int k2, int k3, FILE *stream );
      const char *GetText( int k1, int k2, int k3 );
   };

enum MapTypesHandled {notset,stringt,array};

class MapHandler {
protected:
	bitset<100> bits;
	MapTypesHandled type;
	const char *pStr;
	int item;
    int len;
	CPtrArray *pStrArray;
public :
	MapHandler(int l) { pStrArray = NULL; pStr=NULL; type=notset; item = 0; len = l; }
	virtual ~MapHandler();
	void SetAt(int i, const char *p);
	bool IsSet(int i);
	const char *GetAt(int i);
};

class ReportTextGetter : GenericTextGetter {
   public:
      CMapWordToPtr cache;
	  short *pLens;
      ReportTextGetter( char *p, CDaoDatabase *pDb );
      const char *GetText( int k, int ind );
      int GetText( int k, int ind, FILE *stream );
      virtual ~ReportTextGetter();
   
   };




#endif