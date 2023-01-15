#include "ConfigData.h"
#include "ReportConfig.h"
#include "Report.h"
#include "GridReport.h"
#include "NumericGridReport.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "sqlite3pp.h"
#include <string>
#include "charcons.h"
#include "dataext.h"
#include "utlduad.h"
#include "report_def.h"
#include "oututil.h"
#include "aspect.h"
#include <vector>
#include "grids.h"


bool NumericGridReport::entry( AS_INF  *inf, int planet, unsigned mode, AS_INF_EXT *aie)
{
 int i;
 MIDPT *mid;
 ASPEC *as;
 const char *rps;
 char *name = (char *)getName().c_str();
 char *comments = (char *) getComments().c_str();

 if ( getReportManager()->planetSign( planet, inf, NULL, mode, name, comments, (char *)rppl, 0 ))
    return( true );
 if ( mode & EXT_CALCS ) {
    rps = getReportManager()->getKey( CH__PLAN_EXT, 0 );
    if ( rps == NULL )
       return( true );
    if ( getReportManager()->planetSignExt( planet, aie, name, (char *)rps, 0 ) )
       return( true );
    }
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI &&
	  planet != IM_COELI ) {
    if ( getReportManager()->planetHouse( planet, inf, name, comments, (char *)rphs, 0 ) )
       return( 1 );
    }
 else if ( mode & HOUSES )
    getReportManager()->getStream() << "@NB|@NB";
 return( 1 );
}


NumericGridReport::NumericGridReport()
{
    //ctor
}

bool NumericGridReport::generateReport() {
 int house_mode;
 AS_INF *inf;
 AS_INF_EXT *aiep;
 int maxp, grddp;
 std::string str="";
 char *report;
 const char *name = getName().c_str();
 const char *comments = getComments().c_str();


 unsigned mode = getReportConfig().getMode();
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST  )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;
 if ( mode & ASTEROID )
	 grddp = HOUSE_12;
 else
	 grddp = HOUSE_12 - (HOUSE_1-CUPIDO);
 DATA_PACKET* dpk = getReportConfig().getDataPkt();
 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 if ( ( report = getReportManager()->getKey( CHH_TITLE, 0 ) ) == NULL ) {
    return false;
    }
 else
    title( (char *)name, (char *)comments, "", (char *)report );
 if ( getReportManager()->birthHeadGroup( mode, getReportConfig().getBirthData(), getReportConfig().getHouseMode(), (char *)comments, dpk ) ) {
    return false;
    }
 rppl = getReportManager()->getKey( CH__PLANET, 0 );
 rphs = getReportManager()->getKey( CH__PLAN_HOUSE, 0 );
 rpah = getReportManager()->getKey( CH__ASPECT_HD, 0 );
 rpas = getReportManager()->getKey( CH__MID_ASPT, 0 );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL ) {
    return false;
    }
 getReportManager()->getStream() << "@TB\x80";
 int i = 0;
 for ( i = 0, inf = getReportConfig().getInfPtr(), aiep = getReportConfig().getAltInfExtPtr(); i <= maxp; ++i, ++inf, aiep++ ) {
     entry( inf, i, mode, aiep, data->name, (char *)comments );
	 getReportManager()->getStream() << "@TR\n";
     }
getReportManager()->getStream() << "@tb\n\n";
commit("planets");
const char *chh = getReportManager()->getKey(CH__HOUSE_HEAD,0);
getReportManager()->printCusps( house_cusps, (char *)chh );
getReportManager()->getStream() << "@TB\n";
commit("houses");


if ( mode & ASPECTS ) {
	getReportManager()->title( (char *)name, (char *)comments, "", (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->makeGrid(inf,maxp);
    str = pGrid->getGridText();
    getReportManager()->getStream() << str;
	delete pGrid;
	commit("aspects");
   }
if ( mode & (BASE_MID|HALF_MID|FULL_MID)) {
	getReportManager()->title( (char *)name, (char *)comments, "", (char *)rpas );
	MidpointGridStr *pmGrid = new MidpointGridStr(maxp,grddp, type,mode);
    pmGrid->makeGrid(inf_ptr,maxp+1);
	str = pmGrid->getGridText();
    getReportManager()->getStream() << str;
	delete pmGrid;
	if ( mode & MID_ASPECT ) {
	   MidAspectGridStr *pmpas = new MidAspectGridStr(grddp,type,mode);
	   pmpas->makeGrid(inf_ptr,maxp+1);
	   str = pmpas->getGridText();
       getReportManager()->getStream() << str;
	   delete pmpas;
	   }
    commit("midpoints");
   }
 getReportManager()->switchReport(summaryName);

 unsigned short msk = 0xffff ^ TEXT;
 unsigned short xmd = getReportConfig().getMode() & msk;
 if ( getReportConfig->getMode() & SUMMARY )
    printSummary();
 return true;
}

