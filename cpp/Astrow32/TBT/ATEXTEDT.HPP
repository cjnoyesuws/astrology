#ifndef _ATEXTEDT_HPP_
#define _ATEXTEDT_HPP_

class AspTextEditorDlg : public RegTextEditorDlg {
      protected:
      zString symbol3;
      zComboBoxStatic *pCombo3;
      CSymbol selSym;
      public :
      AspTextEditorDlg(zFrameWin *pPar, char *rfile, char *sym="TEXT.SYM", int type=3, int dlg =IDD_ASPECT_EDIT );
      ~AspTextEditorDlg() {}
      int selchg( zEvent *e );
      virtual int doFindText();
      virtual int doReplaceText();
      virtual int updateCombos();
      };

#endif /* _ATEXTEDT_HPP_ */

