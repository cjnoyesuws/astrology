#ifndef _GRID_____HPP_
#define _GRID_____HPP_

#define GRD_ASP    1
#define GRD_MID    2

#define GRD_SQUARE   16
#define GRD_SLP_LT   1
#define GRD_SLP_LB   2
#define GRD_SLP_RT   3
#define GRD_SLP_RB   4

typedef struct GRD_ASP {
	char first;
	char second;
	char aspect;
	char orb;
	void set( char f, char s, char a, char o) { first=f; second=s;
						    aspect=a; orb=o; }
	void get( char &f, char &s, char &a, char &o) { f=first; s=second;
						    a=aspect; o=orb; }
	} GRD_ASP;

typedef struct GRD_MID {
	char first;
	char second;
	char deg;
	char sign;
	char minor;
	void set( char f, char s, char d, char i, char m) { first=f; second=s;
				       deg=d; sign=i; minor=m; }
	void get( char &f, char &s, char &d, char &i, char &m) { f=first; s=second;
				       d=deg; i=sign; m=minor }
	} GRD_MID;

typedef union GRD_U {
GRD_MID m;
GRD_ASP a;
	GRD_ASP &get() { return a; }
	GRD_MID &get() { return m; }
	void set( char f, char s, char d, char i, char m) { m.set(f,s,d,i,m); }
	void get( char &f, char &s, char &d, char &i, char &m) { m.get(f,s,d,i,m); }
	void set( char f, char s, char a, char o) { a.set( f, s, a, o ); }
	void get( char &f, char &s, char &a, char &o) { a.get( f, s, a, o ); }
	} GRD_U;

typedef struct GRID_STRUCT {
	int type;
	int code;
	int rows, cols;
	int data_points;
	int srows;
	} GRID_STRUCT;

class GridArray {
GRID_STRUCT desc;
GRD_U *data[30];
int count[30];
int alloc[30];
int dcount;
int scount;
int salloc;
GRD_U *sortData;
protected:
      int allocate( int p, int c );
      int add( int p, char f, char s, char a, char o );
      int add(int p, char f, char s, char d, char i, char m );
      void setup();
      readHeader( FILE *stream );
      seekEnd( FILE *stream );
public:
      GridArray() {}
      ~GridArray();
      void mode(int m) { desc.mode = m; }
      int mode() { return desc.mode; }
      void type(int t) { desc.type = t; }
      int type() { return desc.type; }
      int cols() { return desc.cols; }
      void cols(int c) { desc.cols = c; }
      int rows() { return desc.rows; }
      void rows(int r) { desc.rows = r; }
      int sortRows() { return desc.srows; }
      void sortRows(int r) { desc.srows = r; }
      int load( char *name  int which = 0 );
      int save( char *name, int append = 0 );
      void sort();
      int add(int p, MIDPT *m, int count);
      int add(int p, ASPEC *a, int count);
      GRD_U *get(int p, int i);
      GRD_U *getSorted(int i);
      int getCount(int p) { return count[p]; }
      int getDataCount() { return dcount; }
      int doAspects( AS_INF *inf, int count );
      int doMidpoints( AS_INF *inf, int count );
      };

#endif /* _GRID_____HPP_  */
