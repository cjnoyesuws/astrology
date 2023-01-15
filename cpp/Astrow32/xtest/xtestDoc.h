// xtestDoc.h : interface of the CXtestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTESTDOC_H__5510098E_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
#define AFX_XTESTDOC_H__5510098E_843B_11D1_9D9B_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXtestSrvrItem;

class CXtestDoc : public COleServerDoc
{
protected: // create from serialization only
	CXtestDoc();
	DECLARE_DYNCREATE(CXtestDoc)

// Attributes
public:
	CXtestSrvrItem* GetEmbeddedItem()
		{ return (CXtestSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXtestDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXtestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXtestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CXtestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTESTDOC_H__5510098E_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
