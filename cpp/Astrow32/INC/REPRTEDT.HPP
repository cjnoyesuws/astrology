#ifndef _REPRTEDT_HPP_
#define _REPRTEDT_HPP_

class ReportEditorDlg : public FormDlgf {
      protected:
      CSymbolAry *pSymAry;
      CTextBlockAry *pTextAry;
      zString symbol, reportFile, symFile, editFile;
      zString editText;
      zTextBox *editBox;
      zComboBoxStatic *pCombo;
      CSymbol selSym;
      CTextBloc *pTextBlock;
      int index;
      int refOnly;
      public :
      ReportEditorDlg(zFrameWin *pPar, char *rfile, char *sym="REPORT.SYM", int type=1, int dlg =IDD_REPORT_EDIT );
      ~ReportEditorDlg();
      int selchg( zEvent *e );
      int command( zCommandEvt *e );
      int onEditFocus( zEvent *e );
      int onEditLoseFocus( zEvent *e );
      virtual int doFindText();
      virtual int doReplaceText();
      virtual int updateCombos();
      };

#endif /* _REPRTEDT_HPP_ */

