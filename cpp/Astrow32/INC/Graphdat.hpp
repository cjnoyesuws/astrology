/* header file defining structures & constants used
   for graphics data

 date & time constants not in USERI.H */

#define  DATE_WIDTH 10
#define  TIME_WIDTH 8

#define  WIN_GRAPH     0xffff
#define  NEW_WIN_GRAPH 0xfedc
#define  XP_WIN_GRAPH 0xfedf

#pragma pack(2)


typedef struct O_GR_DAT {
  short  type;
  short  birth_time_known_1;
  short  birth_time_known_2;
  char name1[NAME_WIDTH+1];
  char name2[NAME_WIDTH+1];
  char date1[DATE_WIDTH+1];
  char date2[DATE_WIDTH+1];
  char time1[TIME_WIDTH+1];
  char time2[TIME_WIDTH+1];
  short natal_house_cusps[12];
  short other_house_cusps[12];
  short maxpt;
  short natal_minutes[18];
  short other_minutes[18];
  short num_aspects;
  short num_charts;
  } O_GR_DAT;

typedef struct GR_DAT {
  unsigned short version;
  short  type;
  short  birth_time_known_1;
  short  birth_time_known_2;
  char name1[NAME_WIDTH+1];
  char name2[NAME_WIDTH+1];
  char date1[DATE_WIDTH+1];
  char date2[DATE_WIDTH+1];
  char time1[TIME_WIDTH+1];
  char time2[TIME_WIDTH+1];
  char trop_side[15];       /* "Tropical" or "Sidereal" */
  char house_proc[20];      /* "Equal", "Placidus", "Koch" etc. */
  short natal_house_cusps[12];
  short other_house_cusps[12];
  short maxpt;
  short natal_minutes[30];
  short other_minutes[30];
  short num_aspects;
  short num_charts;
  short num_data;
  short num_text;
  short num_other;
  short has_aspect_glyphs;
  unsigned short layout_options;
  short num_grid_aspects;
  short num_other_grid_aspects;
  } GR_DAT;

typedef struct GR_ASPT {
	short first;
	short second;
	short aspect;
	short isHard();
	void set( short f, short s, short a=-1 ) { first = f; second = s; aspect = a;}
	short getAspect() { return( aspect ); }
	short getFirst() { return( first ); }
	short getSecond() { return( second ); }
	} GR_ASPT;

typedef struct O_GR_CHART {
  char date[DATE_WIDTH+2];
  short chart_minutes[18];
  short *getChartMinutes() { return chart_minutes; }
  char *getDate() { return date; }
  } O_GR_CHART;

typedef struct GR_CHART {
  char date[DATE_WIDTH+2];
  short maxpt;
  short chart_minutes[29];
  short aspect_count;
  GR_ASPT *pAspects;
  GR_ASPT *getAspects( short &count ) { count = aspect_count; return pAspects; }
  void setAspects( short n, GR_ASPT *a) { aspect_count = n; pAspects = a; }
  short read( FILE *stream );
  short write( FILE *stream );
  short *getChartMinutes() { return chart_minutes; }
  char *getDate() { return date; }
  } GR_CHART;

typedef struct O_GR_ASPT {
	short first;
	short second;
	} O_GR_ASPT;

typedef struct GR_DATALST {
	short min;
	short house;
	short decan;
	} GR_DATALST;

enum ArrowType { NoArrow, Top, Bottom, Left, Right, URdiag, ULdiag, DLdiag, DRdiag };
enum AlignType { TopLeft, TopRight, BottomLeft, BottomRight, Center };


typedef struct GR_TEXT {
	short x, y, color, len;
	AlignType align;
	ArrowType arrow;
	char buf[1];
	short getArrow() { return arrow; }
	char *getText() { return( buf ); }
	AlignType getAlign() { return( align ); }
	short getColor() { return( color ); }
	void set(short _x, short _y, short co, AlignType al) { x = _x; y = _y; color = co; align = al; }
	void setArrow( ArrowType a ) { arrow = a; }
	void setText( char *text, short l ) { strcpy( buf, text ); len = l; }
	CPoint &at(CPoint &p) { p.x=x; p.y=y;return(p); }
	} GR_TEXT;

	
typedef struct GR_RELOC {
	short item_type;
	short item_no;
	short color;
	short deg;
	short rad;
	} GR_RELOC;


#pragma pack(2)



class GraphData {
protected:
	  short fudge;
      NFP nfp;
      GR_DAT *data;
      short other_data_count;
      GR_DATALST *pOtherLst;
      short data_count;
      GR_DATALST *pDataLst;
      short aspect_count;
      GR_ASPT  *pAspect;
      short chart_count;
      short cur_chart;
      GR_CHART *pChart;
      short text_count, text_alloc;
      GR_TEXT **pText;
      short grid_aspect_count;
      GR_ASPT  *pGridAspect;
      short other_grid_aspect_count;
      GR_ASPT  *pOtherGridAspect;
      short has_aspect_glyphs;
      short writeTextItem( GR_TEXT **pT, FILE *stream );
      short readTextItem( GR_TEXT **pT, FILE *stream );
      short readOld1( O_GR_DAT *pOld, FILE *stream );
      short readOld2( O_GR_DAT *pOld, FILE *stream );
      short cvtTo( O_GR_DAT *pOld );
public:
      GraphData();
      ~GraphData();
      short ncharts();
      short read(char *file_name, short dir);
      short save(char *file_name, short dir);
      XPFILE_DB *getFileDb() { return &nfp.x.fpt; }
      GR_DAT *getData() { return data; }
      GR_DATALST *getOtherDataLst(short &n) { n = other_data_count; return pOtherLst; }
      GR_DATALST *getDataLst(short &n) { n = data_count; return pDataLst; }
      GR_ASPT *getAspects(short &n) { n = aspect_count; return pAspect; }
      GR_TEXT **getText(short &n) { n = text_count; return pText; }
      GR_CHART *getCharts(short n) { n = chart_count;  return pChart; }
      GR_CHART *getFirstChart() { cur_chart = 0; return pChart; }
      GR_CHART *getNextChart() { cur_chart++;
				 if ( cur_chart >= chart_count ) {
				    cur_chart = 0;
				    return( pChart );
				    }
				 else
				    return( pChart+cur_chart );
				 }
      GR_CHART *getPrevChart() { cur_chart--;
				 if ( cur_chart < 0 ) {
				    cur_chart = chart_count-1;
				    return( pChart+cur_chart );
				    }
				 else
				    return( pChart+cur_chart );
				 }
      GR_TEXT *addTextItem( GR_TEXT *p );
      GR_TEXT *replaceTextItem( GR_TEXT *p );
      unsigned short getLayoutOptions() { return data->layout_options;}
      void setLayoutOptions(unsigned short o) { data->layout_options = o;}
      short hasAspGlyphs() { return has_aspect_glyphs; }
      GR_ASPT *getGridAspects(short &n) { n = grid_aspect_count; return pGridAspect; }
      GR_ASPT *getOtherGridAspects(short &n) { n = other_grid_aspect_count; return pOtherGridAspect; }
      void setCharts(short n,GR_CHART *c) { pChart = c; data->num_charts = n; chart_count = n; }
      void setAspects(short n,GR_ASPT *p) { pAspect = p; data->num_aspects = n; aspect_count = n; }
      void setOtherGridAspects(short n,GR_ASPT *p) { pOtherGridAspect = p; data->num_other_grid_aspects = n; other_grid_aspect_count = n; }
      void setGridAspects(short n,GR_ASPT *p) { pGridAspect = p; grid_aspect_count = n; data->num_grid_aspects = n;  }
      void setDataLst(short n,GR_DATALST *p ) { data_count = n; pDataLst = p; data->num_data = n;  }
      void setOtherDataLst(short n,GR_DATALST *p ) { other_data_count = n; data->num_other = n; pOtherLst = p; }
      void setNfp(NFP n) { nfp = n; }
      unsigned short getVersion( FILE *stream, char *name );
      };

#pragma pack()