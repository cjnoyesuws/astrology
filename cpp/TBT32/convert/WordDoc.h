#if !defined(AFX_WORDDOC_H__E7C0D84F_2676_4BA2_B8FB_93EB7094725E__INCLUDED_)
#define AFX_WORDDOC_H__E7C0D84F_2676_4BA2_B8FB_93EB7094725E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWordDoc document

class CWordDoc : public COleDocument
{
protected:
	CWordDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWordDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordDoc)
	public:
	virtual void OnFinalRelease();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWordDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWordDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CWordDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDDOC_H__E7C0D84F_2676_4BA2_B8FB_93EB7094725E__INCLUDED_)
