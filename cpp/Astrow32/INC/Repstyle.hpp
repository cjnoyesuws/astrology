#ifndef _REPSTYLE_HPP_
#define _REPSTYLE_HPP_

class ReportStyles {
int regpointsize, boldpointsize, headpointsize, italpointsize;
CDC *dc;
LOGFONT *regfont;
LOGFONT *boldfont;
LOGFONT *headfont;
LOGFONT *italfont;
COLORREF regcolor, boldcolor, headcolor, italcolor;
public:
    ReportStyles(CDC *d, int viewer=0, int grid=0);
    ~ReportStyles() { delete regfont;
		      delete boldfont;
		      delete headfont;
		      delete italfont; }
    int &getRegPointSize() { return regpointsize; }
	int &getHeadPointSize() { return headpointsize; }
	int &getBoldPointSize() { return boldpointsize; }
	int &getItalPointSize() { return italpointsize; }
	LOGFONT *getRegFont() { return regfont; }
    COLORREF &getRegColor() { return regcolor; }
    LOGFONT *getBoldFont() { return boldfont; }
    COLORREF &getBoldColor() { return boldcolor; }
    LOGFONT *getHeadFont() { return headfont; }
    COLORREF &getHeadColor() { return headcolor; }
    LOGFONT *getItalFont() { return italfont; }
    COLORREF &getItalColor() { return italcolor; }
    int getFromIni(char *sec);
    int saveToIni(char *sec);
    COLORREF checkColor( COLORREF c );
    void Update(ReportStyles &r);
    CDC *&getDC() {return dc; };
	int adjustSize( int s );
	};
/*
class ReportStylesDlgf : public FormDlgf {
zDisplay *dsp;
ReportStyles *data;
public:
      ReportStylesDlgf(zWindow *par, ReportStyles *f, zDisplay *d);
      ~ReportStylesDlgf() {}
      virtual int command(zCommandEvt *e);
      int doStyle(zColor &c, zFontSpec *pfs );
      };
#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
*/
#endif /* _REPSTYLE_HPP_  */
