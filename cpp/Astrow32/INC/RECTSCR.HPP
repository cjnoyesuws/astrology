#ifndef _RECTSCR__HPP_
#define _RECTSCR__HPP_

class RectDataDlgf : public FormDlgf {
     RECT_DATA *dlg_rect;
     BIRTH_DB *dlg_birth;
     zAstComboBoxStatic *pCbmeth;
     zAstComboBoxStatic *pCbsign;
     zAstComboBoxStatic *pCbangle;
     zAstComboBoxStatic *pCbam;
     zCheckBox *pCbbtk;
public:
      RectDataDlgf(zWindow *pPar, RECT_DATA *pR, BIRTH_DB *pB );
      ~RectDataDlgf() {}
      int btkButtonClick( zEvent *e );
      int selchg( zEvent *e );
      void computeAngle();
      virtual int command( zCommandEvt *e );
      int enableKnownFields(int en);
      };

class CRectDataDlgf : public RectDataDlgf {
public:
      CRectDataDlgf(zWindow *pPar, RECT_DATA *pR, BIRTH_DB *pB )
	  : RectDataDlgf(pPar, pR, pB) {
	     caption( "Compatibility Birth Rectification."); }
      ~CRectDataDlgf() { }
      };
#endif /* _RECTSCR__HPP_  */
