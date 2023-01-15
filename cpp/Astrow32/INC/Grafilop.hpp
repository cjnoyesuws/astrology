#ifndef _GRAFILOP_HPP_
#define _GRAFILOP_HPP_

#define GF_DOTS       0
#define GF_INCHES     1
#define GF_MILIM      2

#define GF_SCREENR    0
#define GF_100        1
#define GF_150        2
#define GF_180        3
#define GF_300        4

#define GF_MPWMF      0
#define GF_CPWMF      1
#define GF_MXWMF      2
#define GF_CXWMF      3
#define GF_MBMP       4
#define GF_CBMP       5
#define GF_CEPS       6
#define GF_CGIF       7
#define GF_MPCX       8
#define GF_CPCX       9
#define GF_MCTIF      10
#define GF_CUTIF      11
#define GF_CCTIF      12
#define GF_PNG        13
#define GF_JPG        14


class GraphFileData {
int format;
int units;
int resolution;
float height, width;
int reverse;
public:
      GraphFileData();
      ~GraphFileData() {}
      int &getFormat() { return format; }
      int &getUnits() { return units; }
      int &getResolution() { return resolution; }
      float &getHeight() { return height; }
      float &getWidth() { return width; }
      int getDotWidth();
      int getDotHeight();
      int &getReverse() { return reverse; }
      int isFormatColor();
      int saveToIni();
      int getFromIni();
	  int getFormatBits();
      };

/*
class GraphFileDataDlgf : public FormDlgf {
zAstComboBoxStatic *pCbFmt;
zAstComboBoxStatic *pCbUnt;
zAstComboBoxStatic *pCbRes;
zStaticText *pStW;
zStaticText *pStH;
GraphFileData *dlg_data;
public:
      GraphFileDataDlgf(zWindow *pPar, GraphFileData *pC);
      ~GraphFileDataDlgf() {}
      int selchg( zEvent *e );
      void getData();
      int enableUnitsFields(int en);
      int enableMonoFields(int en);
      };
*/

#endif /* _GRAFILOP_HPP_  */

