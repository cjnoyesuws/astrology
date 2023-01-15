// EZAstrowView.h : interface of the CEZAstrowView class
//


#pragma once


class CEZAstrowView : public CFormView
{
protected: // create from serialization only
	CEZAstrowView();
	DECLARE_DYNCREATE(CEZAstrowView)

public:
	enum{ IDD = IDD_EZASTROW_FORM };

// Attributes
public:
	CEZAstrowDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CEZAstrowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EZAstrowView.cpp
inline CEZAstrowDoc* CEZAstrowView::GetDocument() const
   { return reinterpret_cast<CEZAstrowDoc*>(m_pDocument); }
#endif

