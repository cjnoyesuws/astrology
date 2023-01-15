
#ifndef _ACOMBBOX_HPP
#define _ACOMBBOX_HPP

#ifndef IX_OK
#include "asbplus.h"
#endif


/*class CAstComboBox : public CComboBox {
public:
      zAstComboBoxStatic(zDialogFrame *p, int id)
               : zComboBoxStatic(p, id) {}
      ~zAstComboBoxStatic() {}
      int addResStrings(int id);
      int insertResStrings(int id, int nAt);
      };
*/

class CAstComboBox : public CComboBox {
public:
      CAstComboBox() : CComboBox() {}
      ~CAstComboBox() { }
      char *trim(char *);
      int loadList( IX_DESC *index, char *key=NULL );
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




