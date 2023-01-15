// ChartEditView.h : interface of the CChartEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTEDITVIEW_H__5C69FD81_ED7C_42D3_8BA0_48683457038B__INCLUDED_)
#define AFX_CHARTEDITVIEW_H__5C69FD81_ED7C_42D3_8BA0_48683457038B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChartEditCntrItem;

class CChartEditView : public CRichEditView
{
protected: // create from serialization only
	CChartEditView();
	DECLARE_DYNCREATE(CChartEditView)

// Attributes
public:
	CChartEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartEditView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChartEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChartEditView)
	afx_msg void OnDestroy();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditRepeat();
	afx_msg void OnUpdateEditRepeat(CCmdUI* pCmdUI);
	afx_msg void OnEditReplace();
	afx_msg void OnUpdateEditReplace(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnStylesBold();
	afx_msg void OnUpdateStylesBold(CCmdUI* pCmdUI);
	afx_msg void OnStylesHeading();
	afx_msg void OnUpdateStylesHeading(CCmdUI* pCmdUI);
	afx_msg void OnStylesItalic();
	afx_msg void OnUpdateStylesItalic(CCmdUI* pCmdUI);
	afx_msg void OnStylesNormal();
	afx_msg void OnUpdateStylesNormal(CCmdUI* pCmdUI);
	afx_msg void OnSylesNormal();
	afx_msg void OnUpdateSylesNormal(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ChartEditView.cpp
inline CChartEditDoc* CChartEditView::GetDocument()
   { return (CChartEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTEDITVIEW_H__5C69FD81_ED7C_42D3_8BA0_48683457038B__INCLUDED_)
