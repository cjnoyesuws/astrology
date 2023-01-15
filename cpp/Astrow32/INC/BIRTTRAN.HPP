#ifndef _BIRTTRAN_HPP_
#define _BIRTTRAN_HPP_


#define BRTTRNONLY -2  /* this level only */

class BirthTransDataDlgf : public LocationDataDlgf {
      zAstComboBoxStatic *pCbam;
protected:
      BIRTH_DB *dlg_birth;
      RECT_DATA *dlg_rect;
      zAstComboBoxFull *pCbnm;
      BirthDatabase *pBirthDb;
public:
      BirthTransDataDlgf(zWindow *pPar, BIRTH_DB *pB, LOC_DB *pL, RECT_DATA *pR, char *dlg="TRANS_INFO");
      ~BirthTransDataDlgf();
      int selchgStatic( zEvent *e );
      int selchgFull( zEvent *e );
      virtual void updateCombos(int ncode = NOPOSTERR );
      int editUpdate( zEvent *e );
      int killFocus( zEvent *e );
      void mergeLoc2Birth();
      void adjustTime();
      LOC_DB *birth2Loc(BIRTH_DB *pBirth, LOC_DB *pLoc);
      void preAdjustTime();
      int checkDate();
      virtual int doOk(zEvent *e);
      virtual int command( zCommandEvt *e );
      };

class TransitsInfoDlg {
BirthTransDataDlgf *pBtd;
BIRTH_DB save;
LOC_DB loc;
RECT_DATA rect;
public:
      TransitsInfoDlg(zWindow *pWnd, BIRTH_DB *pB);
      ~TransitsInfoDlg() {delete pBtd; free_index_mem();}
      int completed() { return pBtd->completed(); }
      };


#endif /* _BIRTTRAN_HPP_  */
