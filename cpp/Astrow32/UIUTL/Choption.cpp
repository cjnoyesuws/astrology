#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "inifile.hpp"
#include "setup.hpp"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "options.hpp"
#include "asframe.hpp"
#include "astromn.h"
#include "direc.hpp"
#include "ATTRIB.H"
#include "convopt.hpp"
#include "asgflags.h"
#include "graopt.hpp"
#include "orbedit.hpp"
#include "inifile.hpp"
#include "repstyle.hpp"
#include "edit.hpp"
#include "grafilop.hpp"
#include "qdtopt.hpp"
#include "resstr.hpp"

int AstroAppFrame::chOptCmd( zCommandEvt *e )
{
 int r, id;
 Options *op;
 char *prompt;

 setup_dat.readFromIni();
 switch( e->cmd() ) {

       case  IDM_ONATAL :
	     id = _OPT_NATAL; /*prompt="Natal/Birth Options";*/
	     op = &setup_dat.getBirthOpt();
	     break;
       case  IDM_OCOMPAT :
	     id = _OPT_COMPAT;/*prompt="Compatibility Options";*/
	     op = &setup_dat.getCompatOpt();
	     break;
       case  IDM_OTRANS :
	     id = _OPT_TRANS;/*prompt="Transits Options";*/
	     op = &setup_dat.getTransOpt();
	     break;
       case  IDM_OPROGR :
	     id = _OPT_PROGR;/*prompt="Progressions Options";*/
	     op = &setup_dat.getProgrOpt();
	     break;
       case  IDM_OCOMPOS :
	     id = _OPT_COMPOS;/*prompt="Composite Options";*/
	     op = &setup_dat.getComposOpt();
	     break;
#ifdef PRO
       case  IDM_OCMTR :
	     id = _OPT_CMTR;/*prompt="Compos. Transits Options";*/
	     op = &setup_dat.getComptrOpt();
	     break;
#endif
      case  IDM_ORELOC :
	     id = _OPT_RELOC;/*prompt="Relocation Options";*/
	     op = &setup_dat.getRelocOpt();
	     break;
#ifdef PRO
       case  IDM_OFIXED :
	     id = _OPT_FIXED;/*prompt="Fixed Star Options";*/
	     op = &setup_dat.getFixstarOpt();
	     break;
       case  IDM_OARABIC :
	     id = _OPT_ARABIC;/*prompt="Arabic Parts Options";*/
	     op = &setup_dat.getArabptOpt();
	     break;
#endif
       case  IDM_ONUMER :
	     id = _OPT_NUMER;/*prompt="Natal Numeric Options";*/
	     op = &setup_dat.getNumerOpt();
	     break;
      default :
	     return( 0 );
	     break;
      }
#ifdef PRO
 
 CustomDlgf *cf = new CustomDlgf(this, CResStr(id), op, 1 );
 if ( cf->completed() ) {
    cf->buildFlags();
    setup_dat.saveToIni();
    }
 delete cf;
#else
 OptionsDlgf *of = new OptionsDlgf(this, CResStr(id), &op->getHouseMode(), (unsigned int *)&op->getFlags() );
 if ( of->completed() ) {
    of->buildFlags();
    setup_dat.saveToIni();
    }
 delete of;
#endif
 return( 1 );
}

int AstroAppFrame::OptionCmd( zCommandEvt *e )
{
 switch( e->cmd() ) {
       case IDM_OSETUP :
	    {
	    Directories *dp = new Directories();
	    *dp = theDirectories;
	    DirectDlgf *dd = new DirectDlgf( (zWindow *)this, dp );
	    if (dd->completed() ) {
	       theDirectories = *dp;
	       theDirectories.saveToIni();
	       }
	    delete dd;
	    delete dp;
	    }
	    break;
       case IDM_OTEXT :
	    {
	    ConvData *pcd = new ConvData();
	    pcd->getFromIni();
	    ConvDataDlgf *cd = new ConvDataDlgf( (zWindow *)this,pcd);
	    if ( cd->completed() ) {
	       cd->getData();
	       pcd->saveToIni();
	       }
	    delete cd;
	    delete pcd;
	    }
	    break;
       case IDM_OGRAPHICS :
	    {
	    GraphOptions ogd;
	    ogd.getFromIni(GraphicsOptions_SEC);
	    GraphOptionsScreen *gos = new
		  GraphOptionsScreen((zWindow *)this, &ogd);
	    delete gos;
	    ogd.saveToIni(GraphicsOptions_SEC);
	    }
	    break;
#ifdef PRO
	case IDM_OEDIT :
	    {
	    EditSetup es;
	    es.getFromIni();
	    EditSetupDlgf *esd = new EditSetupDlgf(this, &es);
	    if ( esd->completed() )
	       es.saveToIni();
	    delete esd;
	    }
	    break;
#endif
	case IDM_OVIEW :
	    {
	    zWinDisplay *d = new zWinDisplay(this);
	    ReportStyles rs(d, 1);
	    rs.getFromIni(ViewerData_SEC);
	    ReportStylesDlgf *rsd = new ReportStylesDlgf(this, &rs, d);
	    if ( rsd->completed() )
	       rs.saveToIni(ViewerData_SEC);
	    delete rsd;
	    delete d;
	    return( 1 );
	    }
	    break;
#ifdef PRO
	 case IDM_OGRPHFIL :
	    {
	    GraphFileData data;
	    data.getFromIni();
	    GraphFileDataDlgf *gfdd = new GraphFileDataDlgf((zWindow *)this,
		   &data );
	    if ( gfdd->completed() )
	       data.saveToIni();
	    delete gfdd;
	    return( 1 );
	    }
	    break;
       case IDM_OEORBS :
	    {
	    AspectOrbScreen *gos = new AspectOrbScreen((zWindow *)this);
	    delete gos;
	    }
	    break;
#endif

	case IDM_OALLCK :
	     fAllChecked ^= 1;
	     menu()->checkItem(IDM_OALLCK, fAllChecked &1 );
	     break;
	case IDM_OQDT :
	    {
	    QdtData qdt;
	    qdt.getFromIni();
	    QdtDataDlgf *qdtd = new QdtDataDlgf(this, &qdt);
	    if ( qdtd->completed() ) {
	       qdtd->getData();
	       qdt.saveToIni();
	       }
	    delete qdtd;
	    }
	    break;
        default :
	     return( 0 );
	     break;
	}
 return( 1 );
}
