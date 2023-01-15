#ifndef _BIRTHSCR_HPP_
#define _BIRTHSCR_HPP_

class BirthDataDlgf : public BirthTransDataDlgf {
      zAstComboBoxStatic *pCbsx;
      zPushButton *pBrect;
      zPushButton *pBbdb;
      zPopupMenu *pBDmenu;
public:
      BirthDataDlgf(zWindow *pPar, BIRTH_DB *pB, LOC_DB *pL, RECT_DATA *pR, char *title = NULL );
      ~BirthDataDlgf();
      int selchgStatic( zEvent *e );
      virtual void updateCombos(int ncode = NOPOSTERR );
      int birthMenuBtnClick( zNotifyEvt *e );
      int birthMenuCmd( zEvent *e );
      int rectBtnClick( zNotifyEvt *e );
      };

class BirthDataDialog {
BirthDataDlgf *pBtd;
BIRTH_DB bSave;
LOC_DB loc;
RECT_DATA rSave;
public:
      BirthDataDialog(zWindow *pPar, BIRTH_DB *pB, RECT_DATA *pR, char *title = NULL );
      ~BirthDataDialog() {delete pBtd; free_index_mem();}
      int completed() { return pBtd->completed(); }
      };


#endif /* _BIRTHSCR_HPP_ */
