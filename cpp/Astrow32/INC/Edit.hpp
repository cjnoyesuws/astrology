#ifndef _EDIT_____HPP_
#define _EDIT_____HPP_

class EditSetup {
CString path;
CString opt;
int _useShell;
public:
      EditSetup() { path = "WordPad.EXE"; opt = "%s"; }
      ~EditSetup() {}
      CString &getPath() {return path;}
      CString &getOpt() {return opt;}
      int saveToIni();
      int getFromIni();
      int &UseShell() { return _useShell; }
		};
/*
class EditSetupDlgf : public FormDlgf {
public:
      EditSetupDlgf(zWindow *pPar, EditSetup *d);
      ~EditSetupDlgf() {}
      };

*/
#endif /*  _EDIT____HPP_  */
