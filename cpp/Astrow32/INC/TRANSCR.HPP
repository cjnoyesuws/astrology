#ifndef _TRANSCR__HPP_
#define _TRANSCR__HPP_

class TransDataDlgf : public FormDlgf {
     TRANS_DATA *dlg_data;
     zAstComboBoxStatic *pCbsp;
     zAstComboBoxStatic *pCbep;
public:
      TransDataDlgf(zWindow *pPar, TRANS_DATA *pT );
      ~TransDataDlgf() { delete pCbsp; delete pCbep; }
      int selchg( zEvent *e );
      };

#endif /* _TRANSCR__HPP_ */
