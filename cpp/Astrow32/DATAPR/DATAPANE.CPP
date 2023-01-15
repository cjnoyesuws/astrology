#include "graphdat.hpp"
#include "astdata.hpp"
#include "datapane.hpp"

extern void zYield(int i);

class DataTextStream : zTextStream {
zString buf;
public:
     DataTextStream() {}
     ~DataTextStream() {}
     virtual void put(char *p) { buf &= p; }
     char *get() { return( (char *)buf );
     };



int AstDataFrame::MDIActivate(zActivateEvt *actEvt)
{
 if ( (actEvt->active()) && (pane!=0) ) {
    pane->setFocus();
    }
 return 0;
}

AstDataFrame::focus(zFocusEvt *focEvt)
{
 char buf[150];

 if ( (focEvt->gainFocus()) && pane != 0 ) {
    pane->setFocus();
    pane->setDirty();
    strcpy( buf, "View Data: " );
    strcat( buf, pane->data->FileDb()->name );
    strcat( buf, ", " );
    strcat( buf, pane->data->FileDb()->comment );
    caption( zString( buf ) );
    }
 return 0;
}

int AstDataPane::size( zSizeEvt *e)
{
 canvas()->setDirty();
 cxClient=e->width();
 cyClient=e->height();
 setMetrics();
 return(1);
}

int AstDataPane::morePages()
{
 return( 0 );
}

int AstDataPane::doPrint(zEvent *)
{
 float fs;
 char buf[150];

 strcpy( buf, "Printing: " );
 strcat( buf, data->FileDb()->name );
 PrinterSetup psg;
 psg.getFromIni(GraphPrintOpt_SEC);
 zPrinterDisplay *pr=new zPrinterDisplay(psg.getSpec(), psg.toDevMode(0, 0));
 AstPrJobDlg *prDlg=new AstPrJobDlg(app->rootWindow());
 prDlg->setName(buf);
 zPrintJob *pj = new zPrintJob(this, pr, prDlg);
 pj->setJobName(buf);
 pj->go();
 while ( app->tasks()->busy() ) {
       zYield(0);
       zYield(1);
       }
 return 1;
}

int AstDataPane::print(zPrinterDisplay *pd, zRect *)
{
 GraphOptions ogd;

 int dmode = mode;
 ogd.getFromIni(GraphPrintOpt_SEC);
 mode = ogd.getDrawMode();
 pushDisplay(pd);
 draw(0);
 popDisplay();
 draw(0);
 return 0;
}

AstDataPane::AstDataPane(zWindow *w, int wh, GraphData *pData )
		      : zPane(w,new zSizeWithParent,zSCROLLV|zSCROLLH)
{
 data = new AstData(int wh, GraphData *pData);
}

AstGraphicsFrame::AstGraphicsFrame(zFrameWin *pPar, int wh, GraphData *pData )
		    : zMDIChildFrame(pPar,new zSizer,zSTDFRAME,"Data Viewer")
{
 pane=new AstDataPane(this, wh, pData );
 setIcon(new zIcon(zResId("DataIcon")));
 pane->addVertScrollBar();
 pane->addHorzScrollBar();
 pane->show();
 pane->setFocus();
 deleteOnClose(TRUE);
}

int AstDataPane::drawKey( zDisplay *zd )
{
 int y;
 char buf[150];

 sprintf( buf, "Name: %s", (char *)data->name() );
 zd->text( 0, 0, buf );
 y += cyHt;
 if ( data->time().length() )
    sprintf( buf, "Date: %s, Time: %s", (char *)data->date(), (char *)data->name() )
 else
    sprintf( buf, "Date: %s", (char *)data->date() );
 zd->text( 0, y, buf );
 y += cyHt;
 if ( data->type() == NATAL_DATA ) {
    sprintf( buf, "Long: %s, Lat: %s, Location: %s", (char *)data->longitude(),
       (char *)data->latitude(), (char *)data->location() );
    zd->text( 0, y, buf );
    y += cyHt;
    }
 sprintf( buf, "Tropical or Sidereal: %s, House Procedure: %s",
     (char *)data->tropSide(), (char *)data->houseProc() );
 zd->text( 0, y, buf );
 y += cyHt;
 y += cyHt;
 return( y );
}

int AstDataPane::putKey( DataTextStream *s )
{
 int y;
 char buf[150];

 s->printf( "Name: %s\n", (char *)data->name() );
 if ( data->time().length() )
    s->printf( "Date: %s\tTime: %s\n", (char *)data->date(), (char *)data->name() );
 else
    s->printf( "Date: %s\n", (char *)data->date() );
 if ( data->type() == NATAL_DATA ) {
    s->printf( "Long: %s\tLat: %s\tLocation: %s\n", (char *)data->longitude(),
       (char *)data->latitude(), (char *)data->location() );
    }
 s->printf( "Tropical or Sidereal: %s\tHouse Procedure: %s\n\n",
     (char *)data->tropSide(), (char *)data->houseProc() );
 return( 1 );
}

int AstDataPane::putPlanets( DataTextStream *s  )
{
 char buf[15];
 Grfa grx;
 GR_DATALST *d, *dd;
 int i, n, xm, xd, xh;

 d = data->getData( n );
 s->put("PLANET:")
 if (d->house != -1) {
    s->put( "\tHOUSE:" );
 if (d->decan != -1)
    s->put( "\tDECAN:" );
 s->put( "\n" );
 for ( i = 0, dd = d; i < n; i++, dd++ ) {
     grx.format( dd->min, mode );
     s->put( planet_str(i) );
     s->put('\t');
     s->put( grx.get() );
     if (dd->house != -1) {
	s->printf( "\t%d", dd->house );
	}
     if (dd->decan != -1) {
	s->printf( "\t%d", dd->decan );
	}
     s->put('\n');
     }
 s->put('\n');
 return( 1 );
}


int AstDataPane::drawPlanets( zDisplay *zd, int y )
{
 char buf[15];
 Grfa grx;
 GR_DATALST *d, *dd;
 int i, n, xm, xd, xh;

 d = data->getData( n );
 zd->PushFont(pDataFnt);
 xm = zd->dimension("Part of Fortune   ").width();
 zd->popFont();
 zd->PushFont(pBoldFnt);
 xh = xm + zd->dimension("DEGREE:    ").width();
 xd = xh + zd->dimension("HOUSE:     ").width();
 zd->text(0, y, "PLANET:" );
 zd->text(xm, y, "DEGREE:" );
 if (d->house != -1) {
    zd->text(xh, y, "HOUSE:" );
 if (d->decan != -1)
    zd->text(xd, y, "DECAN:" );
 zd->popFont();
 y+= cyHt;
 for ( i = 0, dd = d; i < n; i++, dd++ ) {
     grx.format( dd->min, mode );
     zd->PushFont(pDataFnt);
     zd->text( 0, y, planet_str(i) )
     zd->popFont();
     zd->PushFont(pDegFnt);
     zd->text( xm, y, grx.get() );
     if (dd->house != -1) {
	sprintf( buf, "%d", dd->house );
	zd->text( xh, y, buf );
	}
     if (dd->decan != -1) {
	sprintf( buf, "%d", dd->decan );
	zd->text( xd, y, buf );
	}
     y+= cyHt;
     zd->popFont();
     }
 y+= cyHt;
 return( y );
}

int AstDataPane::drawHousesH( zDisplay *zd, int y, int x )
{
 int i, *h;
 Grfa grxa;
 char buf[15];

 zd->PushFont(pBoldFnt);
 SetTextAlign(*zd,TA_RIGHT|TA_TOP);
 zd->text(0, 0, "HOUSES:" );
 zd->popFont();
 zd->PushFont(pDegFnt);
 y = cyHt;
 h = data->houses();
 int x2 = x - zd->dimension(" 29SCO39 ").width();
 for ( i = 0; i < 12; i++ ) {
     grxa.format( h[i], mode );
     zd->text( x, y, grxa.get() );
     sprintf( buf, "# %d : ", i+1 );
     zd->text( x2, y, buf );
     y+= cyHt;
     }
 SetTextAlign(*zd,TA_LEFT|TA_TOP);
 return( 1 );
}


int AstDataPane::putHouses( DataTextStream *s  )
{
 int i, *h;
 Grfa grxa, grxb;
 char bufa[15], bufb[15];


 s->put( "HOUSES:\n" );
 h = data->houses();
 for ( i = 0; i < 12; i+=2 ) {
     grxa.format( h[i], mode );
     s->printf( "%d\t%s\t", i+1, grxa.get() );
     zd->text( 0, y, bufa );
     grxb.format( h[i+1], mode );
     sprintf( "%d\t%s\n", i+3, grxb.get() );
     zd->text( x, y, bufb );
     }
 return( 1 );
}



int AstDataPane::drawHousesV( zDisplay *zd, int y )
{
 int i, *h;
 Grfa grxa, grxb;
 char bufa[15], bufb[15];

 zd->PushFont(pBoldFnt);
 zd->text(0, y, "HOUSES:" );
 zd->popFont();
 zd->PushFont(pDegFnt);
 y+= cyHt;

 h = data->houses();
 int x = zd->dimension("# 12 :  29SCO39       ").width();
 for ( i = 0; i < 12; i += 2 ) {
     grxa.format( h[i], mode );
     sprintf( buf, "# %d :  %s ", i+1, grxa.get() );
     zd->text( 0, y, bufa );
     grxb.format( h[i+1], mode );
     sprintf( buf, "# %d :  %s ", i+3, grxb.get() );
     zd->text( x, y, bufb );
     }
}


int AstDataPane::drawHouses( zDisplay *zd, int y )
{
 if ( data->houses()[0] == -1 )
    return( 0 );
 if ( zd->type() == PrinterDisp && cxClient > cyClient  )
    drawHousesH( zd, y, cxClient );
 else if ( zd->type() == PrinterDisp )
    drawHousesV( zd, y );
 else if ( cxClient > 500 )
    drawHousesH( zd, y, cxClient );
 else
    drawHousesV( zd, y );
}

AstDataPane::draw( zDrawEvt *e )
{
 char buf[150];
 int x = 0, y = 0;
 zDisplay *zd = canvas();
 zd->lock();
 SetBkMode( *zd, TRANSPARENT );
 zd->getDirty(r);
 zd->fill(r,pbBack);
 zBrush *pB = new zBrush(NullBrush);
 zd->pushBrush(pB);
 zdPushFont(pDataFnt);
 y = drawKey(zd);
 zd->popFont();
 zdPushFont(pDegreeFnt);
 y = drawPlanets( zd, y );
 drawHouses( zd, y );
 zd->popFont();
 zd->unlock();
}

AstDataPane::copyToClipboard()
{
 DataTextStream stream;
 int dmode = mode;
 mode = 0;
 putKey(&stream);
 putPlanets(&stream);
 putHouses(&stream);
 pClip->clear();
 pClip->add(stream.get());
 mode = dmode;
}

