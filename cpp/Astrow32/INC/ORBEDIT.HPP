#ifndef _ORBEDIT__HPP_
#define _ORBEDIT__HPP_

extern int load_orbs(int context);
extern int save_orbs(int context);

class OrbData {
int context;
int orbs[17];
int inc[17];
public:
    OrbData() { context = 0; }
    ~OrbData() {}
    void setupArrays();
    void getData();
    int changeContext(int cnt);
    int getContext();
    int *getOrb(int i) { return( &orbs[i] ); }
    int *getInc(int i) { return( &inc[i] ); }
    int loadData() { return( load_orbs(context) ); }
    int saveData() { return( save_orbs(context) ); }
    };


class AspectOrbDlgf : public FormDlgf {
OrbData *pOrbData;
zAstComboBoxStatic *pCb;
public:
      AspectOrbDlgf(zWindow *pPar, OrbData *pOrb );
      ~AspectOrbDlgf() { }
      void setDefaults();
      int selchg( zEvent *e );
      void getData();
      };


class AspectOrbScreen {
OrbData Orbs;
public:
      AspectOrbScreen(zWindow *pPar);
      ~AspectOrbScreen() {}
      };

#endif /* _ORBEDIT__HPP_  */
