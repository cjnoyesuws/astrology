// AstrowDaoFileListDoc.h : interface of the CAstrowDaoFileListDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASTROWDAOFILELISTDOC_H__34AE9306_C1E9_4460_82AE_B3F10A7EA38A__INCLUDED_)
#define AFX_ASTROWDAOFILELISTDOC_H__34AE9306_C1E9_4460_82AE_B3F10A7EA38A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AstrowDaoFileListSet.h"


class CAstrowDaoFileListDoc : public CDocument
{
protected: // create from serialization only
	CAstrowDaoFileListDoc();
	DECLARE_DYNCREATE(CAstrowDaoFileListDoc)

// Attributes
public:
	CAstrowDaoFileListSet m_astrowDaoFileListSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrowDaoFileListDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstrowDaoFileListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstrowDaoFileListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAstrowDaoFileListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTROWDAOFILELISTDOC_H__34AE9306_C1E9_4460_82AE_B3F10A7EA38A__INCLUDED_)
