// RTFFuncs.h: interface for the RTFFuncs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTFFUNCS_H__04F524C2_380E_430B_A190_FE6BAE92A3D6__INCLUDED_)
#define AFX_RTFFUNCS_H__04F524C2_380E_430B_A190_FE6BAE92A3D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxcmn.h>

class RTFFuncs  
{
private:
   CRichEditCtrl *GetCtrl(int id) { return ((CRichEditCtrl *)pDialog->GetDlgItem(id));}
public:
   CString tabstring;
   CString BasicString;
   CDialog *pDialog;
   RTFFuncs(CDialog *pDlg) { pDialog=pDlg; }
   CString GetRTF( int id );
   void SetRTF( int id, CString &str );
   void NewRTF( int id );
   void DoBold( int id );
   void DoItalic( int id );
   void DoHeading( int id );
   void DoUnBold( int id );
   void DoUnItalic( int id );
   void DoUnHeading( int id );
   void Cut( int id ) { GetCtrl(id)->Cut(); }
   void Paste( int id ) { GetCtrl(id)->Paste(); }
   void Copy( int id ) { GetCtrl(id)->Copy(); }
   void Undo( int id ) { GetCtrl(id)->Undo(); }
   void Clear( int id ) { GetCtrl(id)->Clear(); }
   BOOL Modified(int id) { return (GetCtrl(id)->GetModify() ); }
   void SetTabString(CString &s) { tabstring = s; }
   CString &GetTabString() { return tabstring; }
   virtual ~RTFFuncs() {}
   void splitTabs(CString &s);
   CString &getBasicString() { return BasicString; }
};

#endif // !defined(AFX_RTFFUNCS_H__04F524C2_380E_430B_A190_FE6BAE92A3D6__INCLUDED_)
