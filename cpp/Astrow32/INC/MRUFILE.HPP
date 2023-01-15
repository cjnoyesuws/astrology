#ifndef _MRUFILE__HPP_
#define _MRUFILE__HPP_

#define _MRUCOUNT_ 6


#define _FLIST_ 0
#define _BDATA_ 1
#define _GRAPH_ 2
#define _TEXT_  3

typedef struct MRUstruct {
zString *name;
DWORD ref;
int id;
char type;
	void set( zString *n, DWORD r, char t = _FLIST_ ) { name = n; ref = r; type = t; }
	zString *getName() { return name; }
	DWORD &getRef() { return ref; }
	int &getId() { return id; }
	char &getType() { return type; }
	int isEqual( char *n ) { return( *name == n ); }
	};

class FileMRUList {
int count, lastid, startPos;
MRUstruct mru[_MRUCOUNT_];
zMenu *pMenu;
HMENU sub;
void *obj;
CommandProc proc;
protected:
      void sort();
public:
      FileMRUList();
      ~FileMRUList();
      void check(char *name, char tp = _FLIST_);
      char *get( int id, char &tp );
      int saveToIni();
      int getFromIni();
      void setupMenu( zMenu *m, void *o, CommandProc p ) { pMenu = m; obj=o; proc = p;  }
      };

extern FileMRUList AstMruList;

#endif /*  _MRUFILE__HPP_ */


