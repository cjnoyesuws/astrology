#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "attrib.h"
#include "errors.fns"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "asfrmdlg.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "write.hpp"
#include "writecnv.hpp"


char *TextConvDriverWrite::tabOut( char *buf, int *col, int *sz )
{
 int tb, tc, l;

 tc = pTabs->getCount();
 tb = pTabs->getTab(pTabs->getCurNo());
 if ( !tc || !tb ) {
    *buf++ = ' ';
    *buf = '\0';
    (*col)++;
    (*sz)++;
    pTabs->nextTab();
    if ( pTabs->getCurNo() >= pTabs->getCount() )
       pTabs->resetTab();
    return( buf );
    }
 else if ( tb <= *col ) {
    pTabs->nextTab();
    if ( pTabs->getCurNo() >= pTabs->getCount() )
       pTabs->resetTab();
       return( buf );
    }
 l = tb - *col;
 if ( l )
    (*sz)++;
 *buf++ = '\t';
 *col = tb;

 if ( pTabs->getCurNo() >= pTabs->getCount() )
    pTabs->resetTab();
 return( buf );
}



int TextConvDriverWrite::writeHeader()
{
 static WRI_HEADER def = {0137061, 0, 0125400,0 };
 WRI_HEADER hd = def;

 hd.setPageMac(pnMac);
 hd.setFcMac(fcMac);
 PAGES &rp = hd.getPages();
 rp = pgOfs;

 fseek(ostream, SEEK_SET, 0L );
 fwrite(&hd, 128, 1, ostream);
 return( 1 );
}


int TextConvDriverWrite::writeFontTable()
{
 FFN f;
 char *fn;
 long of;
 int count = 1, pg;
 ReportStyles *s = getStyles();
 zFontSpec *fs[4];
 int fc[4];

 fc[1] = 1;
 fs[0] = s->getRegFont();
 fs[1] = s->getHeadFont();
 if ( !strcmp( fs[0]->faceName(),  fs[1]->faceName() ) )
    fc[1] = 2;
 else
    fc[1] = 1;
 fs[2] = s->getBoldFont();
 if ( fc[1] == 1 && !strcmp( fs[1]->faceName(),  fs[2]->faceName() ) )
    fc[2] = 1;
 else if ( strcmp( fs[0]->faceName(),  fs[2]->faceName() ) )
    fc[2] = 1;
 else if ( strcmp( fs[1]->faceName(),  fs[2]->faceName() ) )
    fc[1] = 2;
 fs[3] = s->getItalFont();
 if ( strcmp( fs[0]->faceName(),  fs[3]->faceName() ) )
    fc[3] = 1;
 else if ( strcmp( fs[1]->faceName(),  fs[3]->faceName() ) )
    fc[3] = 2;
 else if ( strcmp( fs[2]->faceName(),  fs[3]->faceName() ) )
    fc[3] = 3;
 /*

 getHead(code);
 if ( code ) {
    count = 2;
    fwrite( &count, 2, 1, ostream );
    fn = getFont(code);
    f.set(code,fn);
    fwrite( &f, f.len+2, 1, ostream );
    fn = getHead(code);
    f.set(code,fn);
    count = f.len;
    f.len = 0;
    fwrite( &f, count+2, 1, ostream );
    }
 else {
    count = 1;
    fwrite( &count, 2, 1, ostream );
    fn = getFont(code);
    f.set(code,fn);
    count = f.len;
    f.len = 0;
    fwrite( &f, count+2, 1, ostream );
    }
 */
 fflush(ostream);
 of = ftell(ostream);
 pg = of/128;
 pgOfs.setFontPage(pg);
 of %=128;
 if ( of ) {
    do {
       fputc( 0, ostream );
       of++;
       } while ( of < 128L );
    }
 return( 1 );
}

int TextConvDriverWrite::writePageTable()
{
 char *fn;
 int of;
 int code, count, pg;
 static PGTB tb = {1,0,1,128L};

 fwrite( &tb, sizeof(PGTB), 1, ostream );
 fflush( ostream );
 pg = ftell(ostream)/128;
 pgOfs.setSectpPage(pg);
 pgOfs.setSectdPage(pg);
 pgOfs.setFootnotePage(pg);
 pgOfs.setPagetPage(pg);
 of = sizeof(PGTB);
 do {
    fputc( 0, ostream );
    of++;
    } while ( of < 128 );
 fflush( ostream );
 return( 1 );
}

void TextConvDriverWrite::finishUpFile()
{
}


void TextConvDriverWrite::finishUpJob()
{
 long of;

 if (chps.getFodCount() )
    addChps();
 if (paps.getFodCount() )
    addPaps();
 fflush(ostream);
 of = ftell(ostream);
 fcMac = of;
 of %=128;
 if ( of ) {
    do {
       fputc( 0, ostream );
       of++;
       } while ( of < 128L );
    }
 writeChpPaps();
 writeFontTable();
 writePageTable();
 pnMac = pgOfs.getPagetPage();
 writeHeader();
}

TextConvDriverWrite::writeChpPaps()
{
 long of;
 CHP_PAGE *cp;
 XPAP_GROUP *pp;
 OSLITER(CHP_PAGE) chpitr(&chpList);
 OSLITER(XPAP_GROUP) papitr(&papList);

 while ( ( cp = (CHP_PAGE *) chpitr() ) != NULL )
       cp->write(ostream);
 fflush(ostream);
 of = ftell(ostream);
 pgOfs.setParaPage(of/128);
 while ( ( pp = (XPAP_GROUP *) papitr()) != NULL )
       pp->write(ostream);
 fflush(ostream);
 return( 1 );
}
