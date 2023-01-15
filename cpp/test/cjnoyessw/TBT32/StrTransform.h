// StrTransform.h: interface for the CStrTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRTRANSFORM_H__46904137_2831_4C20_80C7_971CC9FF6C0B__INCLUDED_)
#define AFX_STRTRANSFORM_H__46904137_2831_4C20_80C7_971CC9FF6C0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStrTransform  
{
CStringArray Symbols;
CStringArray Replacements;
int size;
int count;
public:
   CStrTransform(int sz=62) { size=sz; Symbols.SetSize(size); Replacements.SetSize(size); } 
   CString &ToReplacements(CString &str);
   CString &ToSymbols(CString &str);
   int Load( TCHAR *name=_T("string.Tab") );  
    ~CStrTransform() { Symbols.RemoveAll(); Replacements.RemoveAll(); }
   };

extern CStrTransform *pTransformers;
  
#endif // !defined(AFX_STRTRANSFORM_H__46904137_2831_4C20_80C7_971CC9FF6C0B__INCLUDED_)
