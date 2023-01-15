#ifndef _ASTHLPER_HPP_
#define _ASTHLPER_HPP_

class AstHelperItem {
      CString file;
      CString title;
	  CString textitem;
	  CString text;
public:
      AstHelperItem() {file=""; title=""; }
      ~AstHelperItem() {}
      int read( FILE *stream, CDHelpTxt *pSet );
      CString &getFile()  { return file; }
      CString &getTitle() { return title; }
	  CString &getTextItem() { return textitem; }
	  void doGetText();
      };

class AstHelperArray {
int items;
CDHelpTxt set;
AstHelperItem *data;
protected:

public:
      AstHelperArray() {items = 0; data=NULL; }
      int read(char *name, int dir);
      ~AstHelperArray() { if ( data != NULL ) delete[] data; data=NULL; }
      AstHelperItem *operator[] (int i);
      int count() { return items; }
      };

/*
class AstHelperFormDialog : public zMDIFormDialog {
int caret, *sel;
zMultiSelListUnsorted *pList;
AstHelperArray HelpList;
public:
      AstHelperFormDialog(zFrameWin *pPar);
      ~AstHelperFormDialog();
      virtual int command( zCommandEvt *e);
      int doubleClick(zEvent *e);
      char **makePrintList();
      char **makeTitleList();
      int view();
      int print();
      int convert();
      };
*/
#endif /* _ASTHLPER_HPP_ */
