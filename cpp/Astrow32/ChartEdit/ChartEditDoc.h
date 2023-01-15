// ChartEditDoc.h : interface of the CChartEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTEDITDOC_H__0D89A22F_B756_4D8B_8DDA_D1F5000D5415__INCLUDED_)
#define AFX_CHARTEDITDOC_H__0D89A22F_B756_4D8B_8DDA_D1F5000D5415__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChartEditDoc : public CRichEditDoc
{
protected: // create from serialization only
	CChartEditDoc();
	DECLARE_DYNCREATE(CChartEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CChartEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChartEditDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTEDITDOC_H__0D89A22F_B756_4D8B_8DDA_D1F5000D5415__INCLUDED_)
