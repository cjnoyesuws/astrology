#include "stdafx.h"
#include "inifile.hpp"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

#ifndef NUMEROWTBT
char ini_file[150] = "ASTROW.INI";
#else
char ini_file[150] = "NUMERO.INI";
#endif                                     
char convdatasec[]= "ConvData";
char smartasciisec[]= "SmartAscii";
char graphprintoptsec[] = "GraphPrintOpt";
char graphicoptionssec[] = "GraphicsOptions";
char chartsetupsec[] = "ChartSetup";
char printdatasec[] = "PrintData";
char coversec[] = "Cover";
char pageoptsec[] = "PageOpt";
char viewerdatasec[] = "ViewerData";
char pageoptgrasec[] = "PageOptGra";
char miscsec[] = "Misc";
