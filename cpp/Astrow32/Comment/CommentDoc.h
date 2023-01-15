// CommentDoc.h : interface of the CCommentDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMENTDOC_H__AC727BB6_DA55_11D1_9DB4_0000C00DEE96__INCLUDED_)
#define AFX_COMMENTDOC_H__AC727BB6_DA55_11D1_9DB4_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommentDoc : public CDocument
{
protected: // create from serialization only
	CCommentDoc();
	DECLARE_DYNCREATE(CCommentDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommentDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommentDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommentDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMENTDOC_H__AC727BB6_DA55_11D1_9DB4_0000C00DEE96__INCLUDED_)
