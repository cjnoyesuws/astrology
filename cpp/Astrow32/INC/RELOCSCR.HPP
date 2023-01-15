#ifndef _RELOCSCR_HPP_
#define _RELOCSCR_HPP_

#define NOPOSTERR 0
#define NOLOOKUP  -1
#define POSTERR   1

class LocationDataDlgf : public FormDlgf {
      zAstComboBoxFull *pCbco;
      zAstComboBoxFull *pCbst;
      zAstComboBoxFull *pCblo;
      zAstComboBoxStatic *pCbew;
      zAstComboBoxStatic *pCbns;
      zAstComboBoxStatic *pCbtz;
      zAstComboBoxStatic *pCbsc;
      zPopupMenu *pMenu;
      zPushButton *pBLoc;
      LocDatabase *pLocDb;
protected:
      LOC_DB *dlg_data;
public:
      LocationDataDlgf(zWindow *pPar, LOC_DB *pL, char *pDlg = "RELOC_DAT");
      ~LocationDataDlgf();
      int selchgStatic( zEvent *e );
      int selchgFull( zEvent *e );
      void setDefaults();
      void updateGMT();
      virtual void updateCombos(int ncode = NOPOSTERR );
      int editUpdate( zEvent *e );
      int killFocus( zEvent *e );
      int locMenuBtnClick( zNotifyEvt *e );
      int locMenuCmd( zEvent *e );
      int doMessage( char *title, char *string );
      virtual int command( zCommandEvt *e );
      int menuSelect(zEvent *e);
      };



class RelocationDataDlg {
LOC_DB save;
LOC_DB *pLoc;
LocationDataDlgf *pLdDf;
public:
      RelocationDataDlg( zWindow *pWnd, LOC_DB *pL );
      ~RelocationDataDlg() { delete pLdDf; free_index_mem(); }
      int completed() { return pLdDf->completed(); }
      };

#endif /* _RELOCSCR_HPP_ */
