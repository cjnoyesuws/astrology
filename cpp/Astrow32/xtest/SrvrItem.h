// SrvrItem.h : interface of the CXtestSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__55100993_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
#define AFX_SRVRITEM_H__55100993_843B_11D1_9D9B_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXtestSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CXtestSrvrItem)

// Constructors
public:
	CXtestSrvrItem(CXtestDoc* pContainerDoc);

// Attributes
	CXtestDoc* GetDocument() const
		{ return (CXtestDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXtestSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CXtestSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__55100993_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
