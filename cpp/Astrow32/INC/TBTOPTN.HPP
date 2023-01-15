#ifndef _TBTOPTN__HPP_
#define _TBTOPTN__HPP_

class TbtOptions {
int enableExtText;
int textFormat;
zString txtFmtKey;
zString txtSrcExt;
public:
      TbtOptions();
      ~TbtOptions() {}
      int &getEnableExtText() { return enableExtText; }
      int &getTextFormat() { return textFormat; }
      zString &getTextFormatKey() { return txtFmtKey; }
      zString &getTextSourceExt() { return txtSrcExt; }
      int saveToIni();
      int getFromIni();
      };


class TbtOptionsDlgf : public FormDlgf {
zAstComboBoxStatic *pCbFmt;
TbtOptions *dlg_data;
public:
      TbtOptionsDlgf(zWindow *pPar, TbtOptions *pO);
      ~TbtOptionsDlgf() {}
      int selchg( zEvent *e );
      };

extern TbtOptions theTbtOptions;

#endif /* _TBTOPTN__HPP_  */

