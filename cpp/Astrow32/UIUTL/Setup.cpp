#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "inifile.hpp"
#include "setup.hpp"
#include "flags.h"


ChartSetup setup_dat;

int Options::readFromIni( char *section, char *var )
{
 CString buf, def;

 def.Format( "%hu %d %d %d %d %d", getFlags(),
	 getHouseMode(), getCharts(), getChartCode(), getOpt().datafile, getOpt().def_rectmethod );
 buf = AfxGetApp()->GetProfileString( section, var, def );
 sscanf( buf, "%hu %d %d %d %d %d", &getOpt().flags, &getOpt().house_mode,
	 &getOpt().charts, &getOpt().chart_code, &getOpt().datafile, &getOpt().def_rectmethod );
 return( 1 );
}

int Options::saveToIni( char *section, char *var )
{
 CString buf;

 buf.Format( "%hu %d %d %d %d %d", getFlags(),
	 getHouseMode(), getCharts(), getChartCode(), getOpt().datafile, getOpt().def_rectmethod );
 AfxGetApp()->WriteProfileString( section, var, buf );
 return( 1 );
}


int ChartSetup::readFromIni( char *section )
{
 birth.readFromIni( "Birth", section );
 compat.readFromIni( "Compat", section  );
 trans.readFromIni( "Trans", section  );
 progr.readFromIni( "Progr", section  );
 numer.readFromIni( "Numer", section  );
 reloc.readFromIni( "Reloc", section  );
 compos.readFromIni( "Compos", section  );
 fixstar.readFromIni( "FixStar", section  );
 arabpt.readFromIni( "ArabPt", section  );
 comptr.readFromIni( "CompTr", section  );
 solar.readFromIni( "Solar", section  );
 harmonic.readFromIni( "Harmonic", section  );
 return( 1 );
}

int ChartSetup::saveToIni( char *section )
{
 birth.saveToIni( "Birth", section );
 compat.saveToIni( "Compat", section );
 trans.saveToIni( "Trans", section );
 progr.saveToIni( "Progr", section );
 numer.saveToIni( "Numer", section );
 reloc.saveToIni( "Reloc", section );
 compos.saveToIni( "Compos", section );
 fixstar.saveToIni( "FixStar", section );
 arabpt.saveToIni( "ArabPt", section );
 comptr.saveToIni( "CompTr", section );
 solar.saveToIni( "Solar", section );
 harmonic.saveToIni( "Harmonic", section );
 return( 1 );
}


void ChartSetup::init()
{
 birth.setOpt(HOUSES|ASPECTS|SUMMARY|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH| INTRP | GRIDF, NATAL_CH,0 );
 compat.setOpt(HOUSES|SUMMARY|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH | INTRP | GRIDF, COMPA_CH,0);
 trans.setOpt(HOUSES|ASPECTS|TEXT|VERT_EAST, 34, TEXTF | GRAPH | INTRP| GRIDF, TRANS_CH,0);
 progr.setOpt(HOUSES|ASPECTS|TEXT|VERT_EAST, 34, TEXTF | GRAPH | INTRP | GRIDF, PROGR_CH,0);
 numer.setOpt(HOUSES|ASPECTS|VERT_EAST, 34, TEXTF | GRAPH | GRIDF, NATAL_CH,0);
 reloc.setOpt(HOUSES|ASPECTS|SUMMARY|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH | INTRP | GRIDF, RELOC_CH,0);
 compos.setOpt(HOUSES|ASPECTS|SUMMARY|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH | INTRP | GRIDF, COMPO_CH|RELOC_CH,0);
 fixstar.setOpt(HOUSES|ASPECTS|VERT_EAST|TEXT, 34, TEXTF|GRIDF, FIXED_CH,0);
 arabpt.setOpt(HOUSES|ASPECTS|VERT_EAST|TEXT, 34, TEXTF|GRIDF, ARABP_CH,0);
 comptr.setOpt(HOUSES|ASPECTS|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH|GRIDF|INTRP, COMPO_CH|TRANS_CH|RELOC_CH,0);
 solar.setOpt(HOUSES|ASPECTS|SUMMARY|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH | GRIDF | INTRP, NATAL_CH|SOLAR_CH,0);
 harmonic.setOpt(HOUSES|ASPECTS|SUMMARY|TEXT|VERT_EAST,
	 34, TEXTF | GRAPH | GRIDF | INTRP, NATAL_CH|HARMON_CH,0);
}
