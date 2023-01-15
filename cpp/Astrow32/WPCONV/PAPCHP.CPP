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

PAP defPap = { 0, 0, 0, 0, 0, 0, 240, 0, 0, 0L, 0 };

void XPAP::addTab(int i)
{
 thePap.tabs[tabCount++].set(i);
}

int XPAP::getLen()
{
 return( sizeof(PAP)-(14*sizeof(TBD))+
     (tabCount * sizeof(TBD)) );
}

int XPAP::write(FILE *stream)
{
 if ( !fwrite( &count, count, 1, stream ) )
    return( 0 );
 return( count );
}

void XPAP::init()
{
 tabCount = 0;
 ofs = 0;
 count = 0;
 thePap = defPap;
}

void XPAP_GROUP::adjustOfs()
{
 for ( int i = 0; i < nProp; i++ )
     fods[i].chOfsProp(sizeof(FOD)*nProp);
}

int XPAP_GROUP::getPageLen()
{
  int l = 6 + (nProp * sizeof(FOD));

  for ( int i = 0; i < pap_count; i++ )
      l += paps[i].getLen();
  return( l );
}

int XPAP_GROUP::addFod( long o )
{   /* add a new ref to current pap */
 if ( getPageLen()+sizeof(FOD) > 126 )
    return( 0 );
 fods[nProp++].set(o, curr_ofs);
 return( 1 );
}

int XPAP_GROUP::addPap( long o, XPAP &p )
{
 if ( getPageLen()+sizeof(FOD)+p.getCount() > 126 )
    return( 0 );
 if ( pap_count > 0 )
    curr_ofs += paps[pap_count-1].getCount();
 else
    curr_ofs = 0;
 p.setCount();
 p.setOfs(curr_ofs);
 paps[pap_count++] = p;
 return( addFod(o) );
}

int XPAP_GROUP::write( FILE *stream )
{
 int cnt = 0, i;

 adjustOfs();
 if ( !fwrite( &fcFirst, 4, 1, stream ) )
    return( 0 );
 cnt += 4;
 if ( fwrite( fods, sizeof(FOD), nProp, stream ) < nProp )
    return( 0 );
 cnt += (sizeof(FOD) * nProp);
 for ( i = 0; i < pap_count; i++ ) {
     if ( paps[i].write(stream) )
	return( 0 );
     }
 while ( cnt < 126 ) {
       fputc( 0, stream );
       cnt++;
       }
 if ( !fwrite( &nProp, 2, 1, stream ) )
    return( 0 );
 else
    return( 1 );
}



void XPAP_GROUP::init()
{
 fcFirst = 0L;
 nProp = 0;
 curr_ofs = 0;
 pap_count = 0;
}


int CHP_PAGE::addBold( long ofs )
{
 if ( getFodCount() >= MAX_FOD )
    return( 0 );
 fods[nProp++].set(ofs,(unsigned)(OFFBOLD));
 return( 1 );
}

int CHP_PAGE::addReg( long ofs )
{
 if ( getFodCount() >= MAX_FOD )
    return( 0 );
 fods[nProp++].set(ofs,(unsigned)(OFFREG));
 return( 1 );
}

int CHP_PAGE::addHead( long ofs )
{
 if ( getFodCount() >= MAX_FOD )
    return( 0 );
 fods[nProp++].set(ofs,(unsigned)(OFFHEAD));
 return( 1 );
}

int CHP_PAGE::addItal( long ofs )
{
 if ( getFodCount() >= MAX_FOD )
    return( 0 );
 fods[nProp++].set(ofs,(unsigned)(OFFITAL));
 return( 1 );
}

void CHP_PAGE::init(ReportStyles *rs)
{
 int c, f;
 LPLOGFONT fs[4];

 fs[_REG_] = *rs->getRegFont();
 c = 1;
 reg.set(fs[0]->lfHeight, 0, fs[0]->lfUnderline, fs[0]->lfItalic );

 fs[1] = *rs->getHeadFont();
 if ( strcmp( fs[0]->lfFaceName,  fs[1]->lfFaceName ) )
    c++;
 head.set(fs[1]->lfHeight, c-1, fs[1]->lfUnderline, fs[1]->lfItalic );
 fs[2] = *rs->getBoldFont();
 if ( !strcmp( fs[0]->lfFaceName,  fs[2]->lfFaceName ) )
    f = 0;
 else if ( !strcmp( fs[1]->lfFaceName,  fs[2]->lfFaceName ) )
    f = 1;
 else {
    c++;
    f = 2;
    }
 bold.set(fs[2]->lfHeight, f, fs[2]->lfUnderline, fs[2]->lfItalic );
 fs[3] = *rs->getItalFont();
 if ( !strcmp( fs[0]->lfFaceName,  fs[3]->lfFaceName ) )
    f = 0;
 else if ( !strcmp( fs[1]->lfFaceName,  fs[3]->lfFaceName ) )
    f = 1;
 else if ( !strcmp( fs[2]->lfFaceName,  fs[3]->lfFaceName ) )
    f = 2;
 else {
    c++;
    f = 3;
    }
 ital.set(fs[3]->lfHeight, f, fs[3]->lfUnderline, fs[3]->lfItalic );
}
