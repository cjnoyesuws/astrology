#ifndef _TABS_____HPP_
#define _TABS_____HPP_

#define TAB_DEF_DEFINED 1

typedef struct TAB_DEF {
	int total_width;   /* Total width of screen or page in units */
	int tab_width;     /* max width of a tabbed out unit in units */
	int left_ofs;      /* left offset in units */
	int tab_count;     /* number of tabs */
	int tabs[20];      /* the actual tabs in units */
	int fill[20];     /* 0 space -- 1 dot */
	int space_add_rem; /* increment to be added to each tab, remainder */
	int space_add_qt;  /* increment to be added to each tab, quotient */
	int unit_mul;      /* mutiplier to convert cols to units */
	int unit_div;      /* divisor if necessary, otherwise 1 */
	int tab_no;
	} TAB_DEF;

class Tabs {
protected:
      TAB_DEF tabs;
      int get_int( FILE *stream, char delim  );
      int to_units( int val );
public:
      Tabs() { memset(&tabs,0,sizeof(TAB_DEF)); init(60); }
      ~Tabs() {}
      void init( int total_width, int mul=1, int div=1, int left=0 );
      char *read( FILE *stream );
      int getCount() { return tabs.tab_count; }
      int getCurNo() { return tabs.tab_no; }
      int getTab( int t ) { return tabs.tabs[t]; }
      int getFill( int t ) { return tabs.fill[t]; }
      void nextTab() {  tabs.tab_no++; }
      void resetTab() {  tabs.tab_no=0; }
      int getTotalWidth() { return tabs.total_width; };
      void setLeft(int l) { tabs.left_ofs = l; }
      int getLeft() { return( tabs.left_ofs );  }
      };

#endif /*  _TABS_____HPP_  */

