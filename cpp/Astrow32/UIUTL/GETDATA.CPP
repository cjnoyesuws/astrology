#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "astromn.h"
#include "dialogs.h"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "retnscr.hpp"
#include "fieldrng.hpp"
#include "charcons.h"
#include "database.hpp"
#include "rectscr.hpp"
#include "relocscr.hpp"
#include "birttran.hpp"
#include "birthscr.hpp"
#include "transcr.hpp"
#include "progrscr.hpp"
#include "utils.hpp"
#include "asframe.hpp"
#include "resstr.hpp"

static int enbl[10];

int AstroAppFrame::setupCompMenu( int *enbl )
{
 /*
 int list[20], i = 0, j;

 disableMenuItems( menu(), IDM_CDEF, IDM_CPROB );
 if ( enbl[0] && enbl[5] ) {
    for ( j = IDM_CDEF; j < IDM_CNUMERIC; j++ )
	list[i++] = j;
    list[i++] = IDM_CFIXED;
    list[i++] = IDM_CHELIO;
    list[i++] = IDM_CARABIC;
    list[i++] = IDM_CPROB;
    if ( enbl[6] && enbl[1] ) {
       list[i++] = IDM_CCOMPAT;
       list[i++] = IDM_CCOMPOS;
       if ( enbl[2] && enbl[3] )
	  list[i++] = IDM_CCMTR;
       }
    if ( enbl[2] && enbl[3] )
       list[i++] = IDM_CTRANS;
    if ( enbl[4] )
       list[i++] = IDM_CPROGR;
    if ( enbl[8] )
       list[i++] = IDM_CRELOC;
    if ( enbl[7] )
       list[i++] = IDM_CRETURN;
    }
 list[i++] = 0;
 enableMenuItems( menu(), list );
 */
 return( 1 );
}

int AstroAppFrame::getDataCmd( zCommandEvt *e )
{
 switch( e->cmd() ) {
       case IDM_DBIRTHI :
	    {
	    BirthDataDialog *bdd = new BirthDataDialog(this,
		 &birth_rec, &birth_rectd, CResStr(_GDT_BIRTHINF)/*"Birth Information."*/ );
	    if ( bdd->completed() ) {
	       enbl[0] = 1;
	       enbl[5] = 1;
	       }
	    delete bdd;
	    }
	    break;
#ifndef _QDTRAN_
       case IDM_DCOMPATI :
	    {
	    BirthDataDialog *cdd = new BirthDataDialog(this,
		 &comp_rec, &comp_rectd, CResStr(_GDT_COMPATINF)/*"Compatibility Birth Information."*/ );
	    if ( cdd->completed() ) {
	       enbl[1] = 1;
	       enbl[6] = 1;
	       }
	    delete cdd;
	    }
	    break;
#endif
       case IDM_DTRANSI :
	    {
	    TransitsInfoDlg *tid =
		  new TransitsInfoDlg(this, &trans_rec );
	    if ( tid->completed() ) {
	       enbl[2] = 1;
	       }
	    delete tid;
	    }
	    break;
#ifndef _QDTRAN_
       case IDM_DTRANSD :
	    {
	    TRANS_DATA tds = transit_data;
	    TransDataDlgf *td = new TransDataDlgf( this, &tds );
	    if ( td->completed() ) {
	       transit_data = tds;
	       enbl[3] = 1;
	       }
	    delete td;
	    }
	    break;
#ifdef DELUXE
       case IDM_DPROGD :
	    {
	    PROGR_DATA pds = progress_data;
	    ProgressDlgf* pf = new ProgressDlgf( &pds, this );
	    if ( pf->completed() ) {
	       pf->getData();
	       progress_data = pds;
	       enbl[4] = 1;
	       }
	    delete pf;
	    }
	    break;
#endif
       case IDM_DBIRTHR :
	    {
	    RECT_DATA brds = birth_rectd;
	    RectDataDlgf *brd = new RectDataDlgf(
		      this, &brds, &birth_rec );
	    if ( brd->completed() ) {
	       brd->computeAngle();
	       birth_rectd = brds;
	       enbl[5] = 1;
	       }
	    delete brd;
	    }
	    break;
       case IDM_DCOMPATR :
	    {
	    RECT_DATA crds = comp_rectd;
	    RectDataDlgf *crd = new RectDataDlgf( this, &crds, &comp_rec);
	    if ( crd->completed() ) {
	       crd->computeAngle();
	       comp_rectd = crds;
	       enbl[6] = 1;
	       }
	    delete crd;
	    }
	    break;
#ifdef DELUXE
       case IDM_DRETURND :
	    {
	    RETURN_DATA rds = return_data;
	    ReturnDataDlgf *rd = new ReturnDataDlgf( this, &rds );
	    if ( rd->completed() ) {
	       rd->getData();
	       return_data = rds;
	       enbl[7] = 1;
	       }
	    delete rd;
	    }
	    break;
       case IDM_DRELOCD :
	    {
	    LOC_DB rds = reloc_data;
	    RelocationDataDlg *ld =
		     new RelocationDataDlg(this, &rds );
	    if ( ld->completed() ) {
	       reloc_data = rds;
	       enbl[8] = 1;
	       }
	    delete ld;
	    }
	    break;
#endif
#endif
       default:
	    return( 0 );
	    break;
       }
 setupCompMenu(enbl);
 return( 1 );
}
