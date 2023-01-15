#ifndef _INIFILE__HPP_
#define _INIFILE__HPP_

#define APPNAME ini_file
extern char ini_file[];

extern char convdatasec[];
#define ConvData_SEC convdatasec

extern char smartasciisec[];
#define SmartAscii_SEC smartasciisec

extern char graphprintoptsec[];
#define GraphPrintOpt_SEC graphprintoptsec

extern char graphicoptionssec[];
#define GraphicsOptions_SEC graphicoptionssec

extern char chartsetupsec[];
#define ChartSetup_SEC chartsetupsec

extern char printdatasec[];
#define PrintData_SEC printdatasec

extern char coversec[];
#define Cover_SEC coversec

extern char pageoptsec[];
#define PageOpt_SEC pageoptsec

extern char viewerdatasec[];
#define ViewerData_SEC viewerdatasec

extern char pageoptgrasec[];
#define PageOptGra_SEC pageoptgrasec

extern char miscsec[];
#define Misc_SEC miscsec

int saveColorToIni(const char *sec, const char *entry, COLORREF &c  );
int readColorFromIni(const char *sec, const char *entry, COLORREF &c  );
int saveFontToIni(const char *sec, const char *entry, LOGFONT *f, int pointsize  );
int readFontFromIni(const char *sec, const char *entry, LOGFONT *f, int &pointsize );
int saveFontColorToIni(const char *sec, char *entry, LOGFONT *f, COLORREF &c, int pointsize  );
int readFontColorFromIni(const char *sec, char *entry, LOGFONT *f, COLORREF &c, int & pointsize  );

#endif /* _INIFILE__HPP_ */
