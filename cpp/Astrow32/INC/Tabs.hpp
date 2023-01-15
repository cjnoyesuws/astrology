#ifndef _TABS_____HPP_
#define _TABS_____HPP_

#define TAB_DEF_DEFINED 1

typedef struct TAB_DEF {
	short total_width;   /* Total width of screen or page in units */
	short tab_width;     /* max width of a tabbed out unit in units */
	short left_ofs;      /* left offset in units */
	short tab_count;     /* number of tabs */
	short tabs[20];      /* the actual tabs in units */
	short fill[20];     /* 0 space -- 1 dot */
	short space_add_rem; /* increment to be added to each tab, remainder */
	short space_add_qt;  /* increment to be added to each tab, quotient */
	short unit_mul;      /* mutiplier to convert cols to units */
	short unit_div;      /* divisor if necessary, otherwise 1 */
	short tab_no;
	} TAB_DEF;

class Tabs {
protected:
	  int stroff;
      TAB_DEF tabs;
      short get_short( FILE *stream, char delim  );
	  short get_short( char **p, char delim  );
      short to_units( short val );
public:
      Tabs() { memset(&tabs,0,sizeof(TAB_DEF));}
      ~Tabs() {}
      void init( short total_width, short mul=1, short div=1, short left=0 );
      char *read( FILE *stream );
	  char *read( char **p );
      short getCount() { return tabs.tab_count; }
      short getCurNo() { return tabs.tab_no; }
      short getTab( short t ) { return tabs.tabs[t]; }
      short getFill( short t ) { return tabs.fill[t]; }
      void nextTab() {  tabs.tab_no++; }
      void resetTab() {  tabs.tab_no=0; }
      short getTotalWidth() { return tabs.total_width; };
      void setLeft(short l) { tabs.left_ofs = l; }
      short getLeft() { return( tabs.left_ofs );  }
      };

#endif /*  _TABS_____HPP_  */

