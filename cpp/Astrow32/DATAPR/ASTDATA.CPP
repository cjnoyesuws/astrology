#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "graphdat.hpp"
#include "astdata.hpp"


AstData::AstData(int wh, GraphData *pData)
{
 type = wh;
 db = pData->getFileDB();
 GR_DAT *pd = pData->getData();
 trop_side = pd->trop_side;
 house_proc = pd->house_proc;
 if (wh == NATAL_DATA) {
    longitude = pd->date2;
    latitude = pd->time2;
    location = pd->name2;
    }
 GR_DATALST *gd;
 int c;
 if ( wh == NATAL_DATA || wh == TWOWH_ONE ) {
    name = pd->name1;
    date = pd->date1;
    time = pd->time1;
    memcpy( houses, pd->natal_house_cusps, 24 );
    gd = pData->getDataLst(c);
    }
 else {
    if ( strlen( pd->name2 )
       name = pd->name2;
    else
       name = pd->name1;
    date = pd->date2;
    time = pd->time2;
    memcpy( houses, pd->other_house_cusps, 24 );
    gd = pData->getOtherDataLst(c);
    }
 data = new GR_DATALST[c];
 if ( data != NULL ) {
    count = c;
    memcpy( data, gd, sizeof(GR_DATALST)*c );
    }
 else
    count = 0;
}

