#ifndef _GRAFONT__HPP_
#define _GRAFONT__HPP_

class GraphicFonts {
CString glyphfont;
CString datafont;
public:
    GraphicFonts() {}
    ~GraphicFonts() {}
    CString &getGlyphFont() { return glyphfont; }
    CString &getDataFont() { return datafont; }
    int getFromIni(char *sec);
    int saveToIni(char *sec);
    };


/*
class GraphicFontDlgf : public FormDlgf {
GraphicFonts *data;
public:
      GraphicFontDlgf(zWindow *par, GraphicFonts *f);
      ~GraphicFontDlgf() {}
      virtual int command(zCommandEvt *e);
      };
*/
#endif /* _GRAFONT__HPP_  */
