#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "attrib.h"
#include "errors.fns"
#include <assert.h>
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"


/* default function used for buffer based situations */

char *tab_out_buf( Tabs *t, char *buf, int *col, int *len )
{
 char *bp;
 int c, tb, tc, l;
 tc = t->getCount();
 tb = t->getTab(t->getCurNo());
 if ( !tc || !tb ) {
    *buf++ = ' ';
    *buf = '\0';
    (*col)++;
    (*len)++;
    t->nextTab();
    if ( t->getCurNo() >= t->getCount() )
       t->resetTab();
    return( buf );
    }
 l = tb - *col;
 if ( l )
    *len+= l;
 for ( c = *col, bp = buf; c < tb; ++c )
     *bp++ = ' ';
 *bp = '\0';
 *col = tb;
 t->nextTab();
 if ( t->getCurNo() >= t->getCount() )
    t->resetTab();
 return( bp );
}

/* Spits out a \t where appropriate and adjusts ptrs. */

char *real_tab_out( Tabs *t, char *buf, int *col, int *sz )
{
 int tb, tc, l;

 tc = t->getCount();
 tb = t->getTab(t->getCurNo());
 if ( !tc || !tb ) {
    *buf++ = ' ';
    *buf = '\0';
    (*col)++;
    (*sz)++;
    t->nextTab();
    if ( t->getCurNo() >= t->getCount() )
       t->resetTab();
    return( buf );
    }
 l = tb - *col;
 if ( l )
    (*sz)+=2;
 *buf++ = F_BINARY;
 *buf++ = '\1';
 *buf++ = '\t';
 *buf = '\0';
 *col = tb;

 if ( t->getCurNo() >= t->getCount() )
    t->resetTab();
 return( buf );
}

