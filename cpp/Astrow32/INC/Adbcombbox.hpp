
#ifndef _ADBCOMBBOX_HPP
#define _ADBCOMBBOX_HPP

#include <afxdisp.h>
#include "Dcomboset.h"

/*class CAstComboBox : public CComboBox {
public:
      zAstComboBoxStatic(zDialogFrame *p, int id)
               : zComboBoxStatic(p, id) {}
      ~zAstComboBoxStatic() {}
      int addResStrings(int id);
      int insertResStrings(int id, int nAt);
      };
*/

class CAstComboBox {
     
public:
	  CDComboset set;  
      CComboBox *pCombo;
	  CAstComboBox(CComboBox *pbox) {pCombo=pbox;}
      ~CAstComboBox() { }
	  virtual int loadList() { return 1;}
      virtual int checkData() {return( 1 );}
      virtual int setToDefault() {return( 1 );}
      virtual int storeData() {return( 1 );}
	  CString & quote( const char *pChar, CString &str );
	  void SetWindowText( CString &s ) { ((CWnd *)pCombo)->SetWindowText(s); }
	  int SelectString( int i, CString &s) { return pCombo->SelectString(i,s); }	     
     void doFillCombo(char *sql, char *fld);
};

class CLocationComboBox : public CAstComboBox {
public:
     // CDLocationset set;
	  CLocationComboBox(CComboBox *pbox) : CAstComboBox(pbox) {}
      ~CLocationComboBox() { }
      int loadList( CString &co );
	  int loadList();
	  int loadList( CString &co, CString &st, int cdp=0 );
      virtual int checkData() {return( 1 );}
      virtual int setToDefault() {return( 1 );}
      virtual int storeData() {return( 1 );}
      };

class CBirthComboBox : public CAstComboBox {
public:
	 // CDBirthset set;
	  CBirthComboBox(CComboBox *pbox) : CAstComboBox(pbox) {}
      ~CBirthComboBox() { }
	  int loadList();
      virtual int checkData() {return( 1 );}
      virtual int setToDefault() {return( 1 );}
      virtual int storeData() {return( 1 );}
      };

class CTransitComboBox : public CAstComboBox {
public:
	  //CDTransitset set;
	  CTransitComboBox(CComboBox *pbox) : CAstComboBox(pbox) {}
      ~CTransitComboBox() { }
	   int loadList(CString &n );
      int loadList();
      virtual int checkData() {return( 1 );}
      virtual int setToDefault() {return( 1 );}
      virtual int storeData() {return( 1 );}
      };

class CRelocateComboBox : public CAstComboBox {
public:
     // CDRelocationset set;
	  CRelocateComboBox(CComboBox *pbox) : CAstComboBox(pbox) {}
      ~CRelocateComboBox() { }
	  int loadList( CString &n );
      virtual int checkData() {return( 1 );}
      virtual int setToDefault() {return( 1 );}
      virtual int storeData() {return( 1 );}
      };
/*
class ResStrBlock : public zUserResource {
char *block;
char *ptrs[50];
int next;
int count;
public:
   ResStrBlock( int id );
   ~ResStrBlock() { delete block; }
   char *get();
   char *operator++() {return get();}
   char *operator[](int i);
   };


extern int centerDialog( zFrameWin *fw );

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

*/
#endif /* _ACOMBBOX_HPP */




