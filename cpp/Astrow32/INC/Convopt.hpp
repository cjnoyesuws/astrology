#ifndef _CONVOPT__HPP_
#define _CONVOPT__HPP_

class ConvData {
int left, width;
int fmt, cmt, cpg, cmtf;
int ctr, just;
int doGlyph, glyphFont;
FIL_ATTRIB fa;
public:
      ConvData() { left = 100; width = 600; fmt = 0; cmt = 0;
	       cpg = 0; cmtf = 1; ctr = 1; just=0; doGlyph=0;glyphFont=0;}
      ~ConvData() {}
      int &getLeft() { return left; }
      int &getWidth() { return width; }
      int &getFmt() { return fmt; }
      int &getCmt() { return cmt; }
      int &getCpg() { return cpg; }
      int &getCmtFst() { return cmtf; }
      int &getCenter() { return ctr; }
      int &getJust() { return just; }
      void setLeft(int v) { left = v; }
      void setWidth(int v) { width = v; }
      void setFmt(int v) { fmt = v; }
      void setCmt(int v) { cmt = v; }
      void setCpg(int v) { cpg = v; }
      void setCenter(int v) { ctr = v; }
      void setJust(int v) { just = v; }
      void setCmtFst(int v) { cmtf = v; }
	  void setGlyph(int v) { doGlyph = v; }
	  int &getGlyph() { return doGlyph; }
	  void setGlyphFont(int f) { glyphFont = f; }
	  int &getGlyphFont() { return glyphFont; }
      FIL_ATTRIB &getFileAttribs() { return fa; }
      int saveToIni();
      int getFromIni();
      };

extern ConvData conversionData;
/*
class ConvDataDlgf : public FormDlgf {
zAstComboBoxStatic *pCb;
ConvData *dlg_data;
zString lft, wid;
public:
      ConvDataDlgf(zWindow *pPar, ConvData *pC);
      ~ConvDataDlgf() {}
      int selchg( zEvent *e );
      void getData();
      virtual int command(zCommandEvt *e);
      };

class PseudoAsciiDlgf : public FormDlgf {
FIL_ATTRIB *data;
zString sh, eh, sb, eb, su, eu;
public:
      PseudoAsciiDlgf(zWindow *pPar, FIL_ATTRIB *d);
      ~PseudoAsciiDlgf() {}
      void getData();
      };

*/
#endif /* _CONVOPT__HPP_  */
