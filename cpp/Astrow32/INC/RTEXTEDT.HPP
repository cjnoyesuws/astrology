#ifndef _RTEXTEDT_HPP_
#define _RTEXTEDT_HPP_

class RegTextEditorDlg : public ReportEditorDlg {
      protected:
      zString symbol2;
      zComboBoxStatic *pCombo2;
      CSymbol selSym;
      public :
      RegTextEditorDlg(zFrameWin *pPar, char *rfile, char *sym="TEXT.SYM", int type=2, int dlg =IDD_TEXT_EDIT );
      ~RegTextEditorDlg() {}
      int selchg( zEvent *e );
      virtual int doFindText();
      virtual int doReplaceText();
      virtual int updateCombos();
      };

#endif /* _RTEXTEDT_HPP_ */

