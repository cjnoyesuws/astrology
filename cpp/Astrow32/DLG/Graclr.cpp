#include "stdafx.h"
#include "asdrawbs.hpp"
#include "gracolor.hpp"
#include "inifile.hpp"
#include "errors.fns"

int GraphicColors::getFromIni( char *sec )
{
 if ( !readColorFromIni(sec, "ClrBack", getColor(0) ) )
    return( 0 );
 if ( !readColorFromIni(sec, "ClrCirc", getColor(CIRC) ) )
    return( 0 );
 if ( !readColorFromIni(sec, "ClrBPlan", getColor(BR+PLAN) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrPlan", getColor(PLAN) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrSign", getColor(SIGN) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrBSign", getColor(BR+SIGN) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrHous", getColor(HOUS) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrBHous", getColor(BR+HOUS) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrRise", getColor(RISE) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrBRise", getColor(BR+RISE) ) )
     return( 0 );
 if ( !readColorFromIni(sec, "ClrBAspec", getColor(ASPECTBR) ) )
     return( 0 );
 RevBack = AfxGetApp()->GetProfileInt( sec, "RevColor", 0 );
 
 return( 1 );
}

int GraphicColors::saveToIni( char *sec )
{
 if ( !saveColorToIni(sec, "ClrBack", getColor(0) ) )
    return( 0 );
 if ( !saveColorToIni(sec, "ClrCirc", getColor(CIRC) ) )
    return( 0 );
 if ( !saveColorToIni(sec, "ClrBPlan", getColor(BR+PLAN) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrPlan", getColor(PLAN) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrSign", getColor(SIGN) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrBSign", getColor(BR+SIGN) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrHous", getColor(HOUS) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrBHous", getColor(BR+HOUS) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrRise", getColor(RISE) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrBRise", getColor(BR+RISE) ) )
     return( 0 );
 if ( !saveColorToIni(sec, "ClrBAspec", getColor(ASPECTBR) ) )
     return( 0 );
 AfxGetApp()->WriteProfileInt( sec, "RevColor", RevBack );
 return( 1 );
}

/*
GraphicColorsDlgf::GraphicColorsDlgf(zWindow *par, GraphicColors *g)
	  : FormDlgf(par,zResId("GRA_COLOR"), HELPID_DLG_GCOLOR )
{
 data = g;
 if (data->getBase()->getColorCount() == 2) {
    alert_box( _GRC_COLORP/* "", "Only On Color Printers" );
    return;
    }
 run();
}

int GraphicColorsDlgf::command(zCommandEvt *e)
{
 int color;
 switch( e->cmd() ) {
      default :
	   color = e->cmd() - GRAPH_COLOR_FIRST;
	   if ( color < 0 || color > 16 )
	      return( 0 );
	   else {
	      zColor c = data->getColor(color);
	      zColorSelForm *csf = new zColorSelForm(this, c);
	      if ( csf->completed() )
		 data->getColor(color) = csf->color();
	      delete csf;
	      }
	   break;
      }
 return( 0 );
}
*/