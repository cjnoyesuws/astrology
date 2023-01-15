// AstrowDaoFileListView.h : interface of the CAstrowDaoFileListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASTROWDAOFILELISTVIEW_H__5950F417_9A40_4F0E_80B4_DD2423CCF0A1__INCLUDED_)
#define AFX_ASTROWDAOFILELISTVIEW_H__5950F417_9A40_4F0E_80B4_DD2423CCF0A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAstrowDaoFileListSet;

class CAstrowDaoFileListView : public CDaoRecordView
{
protected: // create from serialization only
	CAstrowDaoFileListView();
	DECLARE_DYNCREATE(CAstrowDaoFileListView)

public:
	//{{AFX_DATA(CAstrowDaoFileListView)
	enum { IDD = IDD_ASTROWDAOFILELIST_FORM };
	CAstrowDaoFileListSet* m_pSet;
	CString	m_cmtpg;
	CString	m_comment;
	CString	m_cover;
	CString	m_filename;
	CString	m_name;
	CString	m_type;
	//}}AFX_DATA

// Attributes
public:
	CAstrowDaoFileListDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrowDaoFileListView)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstrowDaoFileListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstrowDaoFileListView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AstrowDaoFileListView.cpp
inline CAstrowDaoFileListDoc* CAstrowDaoFileListView::GetDocument()
   { return (CAstrowDaoFileListDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTROWDAOFILELISTVIEW_H__5950F417_9A40_4F0E_80B4_DD2423CCF0A1__INCLUDED_)
