#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "graphdat.hpp"

#define ID_TYPE     0
#define ID_BTK1     1
#define ID_BTK2     2
#define ID_NAME1    3
#define ID_NAME2    4
#define ID_DATE1    5
#define ID_DATE2    6
#define ID_TIME1    7
#define ID_TIME2    8
#define ID_HPRC     9
#define ID_TRSIDE   10
#define ID_NACSP    11
#define ID_OTCSP    12
#define ID_POINTS   13
#define ID_NADEG    14
#define ID_OTMIN    15
#define ID_TEXTCNT  16
#define ID_TEXT     17
#define ID_CHART    18
#define ID_CHARTCNT 19
#define ID_ASPECT   20
#define ID_ASPECTCNT 21
#define ID_MIDPT     22
#define ID_MIDPTCNT  23
#define ID_RELOCCNT  24
#define ID_RELOC     25
#define ID_ASPECT_GLYPH 26
#define ID_OPTIONS      27

#define ID_key_TYPE    "TYPE"
#define ID_key_BTK1    "BTKNOWN1"
#define ID_key_BTK2    "BTKNOWN2"
#define ID_key_NAME1   "NAME1"
#define ID_key_NAME2   "NAME2"
#define ID_key_DATE1   "DATE1"
#define ID_key_DATE2   "DATE2"
#define ID_key_TIME1   "TIME1"
#define ID_key_TIME2   "TIME2"
#define ID_key_HPRC    "HOUSE_PROC"
#define ID_key_TRSIDE  "TROP_SIDE"
#define ID_key_NACSP   "NATAL_CUSP"
#define ID_key_OTCSP   "OTHER_CUSP"
#define ID_key_POINTS  "POINTS"
#define ID_key_NAMIN   "NATAL_MIN"
#define ID_key_OTMIN   "OTHER_MIN"
#define ID_key_TEXTCNT  "TEXT_CNT"
#define ID_key_TEXT     "TEXT"
#define ID_key_CHART    "CHART"
#define ID_key_CHARTCNT "CHART_CNT"
#define ID_key_ASPECT   "ASPECT"
#define ID_key_ASPECTCNT "ASPECTCNT"
#define ID_key_MIDPT     "MIDPT"
#define ID_key_MIDPTCNT "MIDPT_CNT"
#define ID_key_RELOCCNT "RELOC_CNT"
#define ID_key_RELOC    "RELOC"
#define ID_key_ASPECT_GLYPH  "ASPECT_GLYPH"
#define ID_key_OPTIONS       "OPTIONS"

char *keys[] = { ID_key_TYPE,ID_key_BTK1,ID_key_BTK2,ID_key_NAME1,
  ID_key_NAME2, ID_key_DATE1,ID_key_DATE2,ID_key_TIME1,ID_key_TIME2,
  ID_key_HPRC, ID_key_TRSIDE,ID_key_NACSP,ID_key_OTCSP,ID_key_POINTS,
  ID_key_NAMIN, ID_key_OTMIN,ID_key_TEXTCNT,ID_key_TEXT,ID_key_CHART,
  ID_key_CHARTCNT, ID_key_ASPECT,ID_key_ASPECTCNT,ID_key_MIDPT,
  ID_key_MIDPTCNT, ID_key_RELOCCNT,ID_key_RELOC,ID_key_ASPECT_GLYPH,
  ID_key_OPTIONS };


class GraphDataWithImpExp : public GraphData {
FILE *stream;
public:
   GraphDataWithImpExp();
   ~GraphDataWithImpExp() {}
   int readInts( int *array, int count );
   int readEntry( int item );
   void readReloc( GR_RELOC *p );
   void readMidpt( GR_MIDPT *p );
   void readAspt( GR_ASPT *p );
   void readChart( GR_CHART *p );
   void readText( GR_TEXT *p );
   int import( char *name );
   int writeInts( int *array, int count );
   int exportEntry( int item );
   void writeReloc( GR_RELOC *p );
   void writeMidpt( GR_MIDPT *p );
   void writeAspt( GR_ASPT *p );
   void writeChart( GR_CHART *p );
   void writeText( GR_TEXT *p );
   int export( char *name );
   };

int GraphDataWithImpExp::readInts( int *array, int count )
{
 int i, *ip = array;

 for ( i = 0; i < count; i++ ) {
     if ( i < count-1 )
	fscanf(stream, "%d,", ip);
     else
	fscanf(stream, "%d", ip);
     }
 return( i );
}

static int rc, mc, ac, tc, cc;

int GraphDataWithImpExp::readEntry( int item )
{
 GR_TEXT *pt;
 GRAPH_DAT *gp = getData();
 char dummy;

 switch( item ) {
       case ID_TYPE :
	    fscanf( stream, " = %d", &gp->type );
	    break;
       case ID_BTK1 :
	    fscanf( stream, " = %d", &gp->birth_time_known1 );
	    break;
       case ID_BTK2 :
	    fscanf( stream, " = %d", &gp->birth_time_known2 );
	    break;
       case ID_NAME1 :
	    fscanf( stream, " = \"%50[^\"]%c", gp->name1, &dummy );
	    break;
       case ID_NAME2 :
	    fscanf( stream, " = \"%50[^\"]%c", gp->name2, &dummy );
	    break;
       case ID_DATE1 :
	    fscanf( stream, " = \"%10[^\"]%c", &gp->date1, &dummy );
	    break;
       case ID_DATE2 :
	    fscanf( stream, " = \"%10[^\"]%c", &gp->date2, &dummy );
	    break;
       case ID_TIME1 :
	    fscanf( stream, " = \"%8[^\"]%c", &gp->time1, &dummy );
	    break;
       case ID_TIME2 :
	    fscanf( stream, " = \"%8[^\"]%c", &gp->time2, &dummy );
	    break;
       case ID_HPRC :
	    fscanf( stream, " = \"%19[^\"]%c", &gp->house_proc, &dummy );
	    break;
       case ID_TRSIDE :
	    fscanf( stream, " = \"%15[^\"]%c", &gp->trop_side, &dummy );
	    break;
       case ID_NACSP :
	    readInts( gp->natal_house_cusps, 12 );
	    break;
       case ID_OTCSP :
	    readInts( gp->other_house_cusps, 12 );
	    break;
       case ID_POINTS :
	    fscanf( stream, " = %d", &gp->maxpt );
	    break;
       case ID_NADEG :
	    readInts( gp->natal_minutes, gp->maxpt );
	    break;
       case ID_OTMIN :
	    readInts( gp->other_minutes, gp->maxpt );
	    break;
       case ID_TEXTCNT :
	    tc = 0;
	    fscanf( stream, " = %d", &gp->num_text );
	    if ( gp->num_text ) {
	       pText = new GR_TEXT *[gp->num_text];
	       text_alloc = gp->num_chart;
	       text_count = 0;
	       if (pText == NULL )
		  do_mem_error(0);
	       }
	    break;
       case ID_TEXT :
	    pt = new char[sizeof(GR_TEXT)+120];
	    if ( pt ) {
	       readText( pt );
	       addTextItem(pt);
	       delete pt;
	       }
	    else
	       do_mem_error( 0 );
	    break;
       case ID_CHART :
	    readChart( pChart+cc );
	    cc++;
	    break;
       case ID_CHARTCNT :
	    cc = 0;
	    fscanf( stream, " = %d", &gp->num_chart );
	    if ( gp->num_chart ) {
	       pChart = new GR_CHART[gp->num_chart];
	       chart_count = gp->num_chart;
	       if ( pChart == NULL )
		  do_mem_error( 0 );
	       }
	    break;
       case ID_ASPECT :
	    readAspect( pAspect+ac );
	    ac++;
	    break;
       case ID_ASPECTCNT :
	    ac = 0;
	    fscanf( stream, " = %d", &gp->num_aspect );
	    if ( gp->num_aspect ) {
	       pAspect = new GR_ASPECT[gp->num_aspect];
	       aspect_count = gp->num_aspect;
	       if ( pAspect == NULL )
		  do_mem_error( 0 );
	       }
	    break;
       case ID_MIDPT :
	    readMidpt( pMidptr+mc );
	    mc++;
	    break;
       case ID_MIDPTCNT :
	    mc = 0;
	    fscanf( stream, " = %d", &gp->num_midpt );
	    if ( gp->num_midpt ) {
	       pMidptr = new GR_MIDPT[gp->num_midpt];
	       mid_count = gp->num_midpt;
	       if ( pMidptr == NULL )
		  do_mem_error( 0 );
	       }
	    break;
       case ID_RELOCCNT :
	    rc = 0;
	    fscanf( stream, " = %d", &gp->num_reloc );
	    if ( gp->num_reloc ) {
	       pRelocs = new GR_RELOC[gp->num_reloc];
	       reloc_count = gp->num_reloc;
	       if ( pRelocs == NULL )
		  do_mem_error( 0 );
	       }
	    break;
       case ID_RELOC :
	    readReloc( pRelocs+rc );
	    rc++;
	    break;
       case ID_ASPECT_GLYPH :
	    fscanf( stream, " = %d", &gp->has_aspect_glyphs );
	    break;
       case ID_OPTIONS :
	    fscanf( stream, " = %d", &gp->layout_options );
	    break;
       default :
	    break;
       }
}


void GraphDataWithImpExp::readReloc( GR_RELOC *p )
{
 fscanf( stream, "%d, %d, %d, %d, %d", &p->item_type, &p->item_no,
	&p->color, &p->deg, &p->rad );
}


void GraphDataWithImpExp::readMidpt( GR_MIDPT *p )
{
  fscanf( stream, "%d, %d, %d", &p->first, &p->second, &p->deg );
}


void GraphDataWithImpExp::readAspt( GR_ASPT *p )
{
  fscanf( stream, "%d, %d, %d", &p->first, &p->second, &p->aspect );
}

void GraphDataWithImpExp::readChart( GR_CHART *p )
{
 int dummy;

 fscanf( stream, " = \"%10[^\"]%c, %d, ", &p->date, &dummy, &p->maxpt );
 read_ints( p->chart_minutes, p->maxpt );
}


void GraphDataWithImpExp::readText( GR_TEXT *p )
{
 fscanf( stream, "%d, %d, %d, %d, %d, %d, \"%100[^\"]%c",
    &p->x, &p->y, &p->color, &p->len, &p->align, &p->arrow, &p->buf );
}


int GraphDataWithImpExp::find( char *p )
{
 int i;

 for ( i = 0, i < (sizeof(files)/sizeof(char *)); i++ ) {
     if ( !strcmpi(p, files[i] ) )
	return( i );
     }
 return( -1 );
}



int GraphDataWithImpExp::import( char *file )
{
 int item, num = (sizeof(keys)/sizeof(char *));
 char buf[100], *p;

 if ( ( stream = fopen( file, "rt" ) ) == NULL ) {
    do_error( stream );
    return( 0 );
    }
 do {
    fscanf( stream, "%s", buf );
    if ( ( item = find( buf ) ) != -1 )
       readEntry(item);
    else {
       alert_box("Error!", "Can't Find %s!", buf  );
       fgets( buf, 100, stream );
       }
    } while ( !feof( stream ) );
 fclose( stream );
}

int GraphDataWithImpExp::export( char *file )
{
 int i, num = (sizeof(keys)/sizeof(char *));
 char buf[100], *p;

 if ( ( stream = fopen( file, "wt" ) ) == NULL ) {
    do_error( stream );
    return( 0 );
    }
 for ( i = 0; i < ID_OPTIONS; i++ )
     export_entry( i );
 fclose( stream );
}


void GraphDataWithImpExp::writeReloc( GR_RELOC *p )
{
 fprintf( stream, ID_key_RELOC " = %d, %d, %d, %d, %d\n", &p->item_type,
	&p->item_no, &p->color, &p->deg, &p->rad );
}


void GraphDataWithImpExp::writeMidpt( GR_MIDPT *p )
{
  fprintf( stream, ID_key_MIDPT " = %d, %d, %d\n", &p->first, &p->second, &p->deg );
}


void GraphDataWithImpExp::writeAspt( GR_ASPT *p )
{
  fprintf( stream, ID_key_ASPECT " = %d, %d, %d\n", &p->first,
       &p->second, &p->aspect );
}

void GraphDataWithImpExp::writeChart( GR_CHART *p )
{
 int dummy;

 fprintf( stream, ID_key_CHART " = \"%s\", %d, ",
      &p->date, &dummy, &p->maxpt );
 writeInts( p->chart_minutes, p->maxpt );
}


void GraphDataWithImpExp::writeText( GR_TEXT *p )
{
 fprintf( stream, "%d, %d, %d, %d, %d, %d, \"%s\"\n",
    &p->x, &p->y, &p->color, &p->len, &p->align, &p->arrow, &p->buf );
}

int GraphDataWithImpExp::writeInts(char *key, int *array, int count )
{
 int i, *ip = array;

 fprintf( stream, "%s = ", key );
 for ( i = 0; i < count; i++ ) {
     if ( i < count-1 )
	fprintf(stream, "%d,", *ip);
     else
	fprintf(stream, "%d\n", *ip);
     }
 return( i );
}


int GraphDataWithImpExp::exportEntry( int item )
{
 GR_TEXT *pt;
 GRAPH_DAT *gp = getData();
 char dummy;

 switch( item ) {
       case ID_TYPE :
	    fprintf( stream, ID_key_TYPE " = %d\n", gp->type );
	    break;
       case ID_BTK1 :
	    fprintf( stream, ID_key_BTK1 " = %d\n", gp->birth_time_known1 );
	    break;
       case ID_BTK2 :
	    fprintf( stream, ID_key_BTK2 " = %d\n", gp->birth_time_known2 );
	    break;
       case ID_NAME1 :
	    fprintf( stream, ID_key_NAME1 " = \"%s\"\n", gp->name1 );
	    break;
       case ID_NAME2 :
	    fprintf( stream, ID_key_NAME2 " = \"%s\"\n", gp->name2 );
	    break;
       case ID_DATE1 :
	    fprintf( stream, ID_key_DATE1 " = \"%s\"\n", gp->date1 );
	    break;
       case ID_DATE2 :
	    fprintf( stream, ID_key_DATE2 " = \"%s\"\n", gp->date2 );
	    break;
       case ID_TIME1 :
	    fprintf( stream, ID_key_TIME1 " = \"%s\"\n", gp->time1 );
	    break;
       case ID_TIME2 :
	    fprintf( stream, ID_key_TIME2 " = \"%s\"\n", gp->time2 );
	    break;
       case ID_HPRC :
	    fprintf( stream, ID_key_HPRC " = \"%s\"\n", gp->house_proc );
	    break;
       case ID_TRSIDE :
	    fprintf( stream, ID_key_TRSIDE " = \"%s\"\n", gp->trop_side );
	    break;
       case ID_NACSP :
	    writeInts( ID_key_NACSP,  gp->natal_house_cusps, 12 );
	    break;
       case ID_OTCSP :
	    writeInts( ID_key_OTCSP, gp->other_house_cusps, 12 );
	    break;
       case ID_POINTS :
	    fscanf( stream, ID_key_POINTS " = %d\n", &gp->maxpt );
	    break;
       case ID_NADEG :
	    writeInts( ID_key_NADEG, gp->natal_minutes, gp->maxpt );
	    break;
       case ID_OTMIN :
	    writeInts( ID_key_OTMIN, gp->other_minutes, gp->maxpt );
	    break;
       case ID_TEXTCNT :
	    fwriteIf( stream, ID_key_TEXTCNT " = %d\n", gp->num_text );
	    break;
       case ID_TEXT :
	    for ( int tc = 0, GR_TEXT **pt = pText; tc < gp->num_text; tc++, pt++ )
		writeText( *pt );
	    break;
       case ID_CHART :
	    for ( int cc = 0; cc < gp->num_chart; cc++ )
		writeChart( pChart+cc );
	    break;
       case ID_CHARTCNT :
	    fprintf( stream, ID_key_CHARTCNT " = %d\n", gp->num_chart );
	    break;
       case ID_ASPECT :
	    for ( int ac = 0; ac < gp->num_aspect; ac++ )
		writeAspect( pAspect+ac );
	    break;
       case ID_ASPECTCNT :
	    fprintf( stream, ID_key_ASPECTCNT " = %d\n", gp->num_aspect );
	    break;
       case ID_MIDPT :
	    for ( int mc = 0; mc < gp->num_midpt; mc++ )
		writeMidpt( pMidptr+mc );
	    break;
       case ID_MIDPTCNT :
	    fprintf( stream, ID_key_MIDPTCNT " = %d\n", gp->num_midpt );
	    break;
       case ID_RELOCCNT :
	    fprintf( stream, ID_key_RELOCCNT " = %d\n", gp->num_reloc );
	    break;
       case ID_RELOC :
	    for ( int rc = 0; rc < gp->num_reloc; rc++ )
		writeReloc( pRelocs+rc );
	    break;
       case ID_ASPECT_GLYPH :
	    fprintf( stream, ID_key_ASPECT_GLYPH " = %d\n", gp->has_aspect_glyphs );
	    break;
       case ID_OPTIONS :
	    fprintf( stream, ID_key_OPTIONS " = %d\n", gp->layout_options );
	    break;
       default :
	    break;
       }
}
