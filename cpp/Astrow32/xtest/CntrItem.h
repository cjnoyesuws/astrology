// CntrItem.h : interface of the CXtestCntrItem class
//

#if !defined(AFX_CNTRITEM_H__55100997_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
#define AFX_CNTRITEM_H__55100997_843B_11D1_9D9B_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXtestDoc;
class CXtestView;

class CXtestCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CXtestCntrItem)

// Constructors
public:
	CXtestCntrItem(CXtestDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CXtestDoc* GetDocument()
		{ return (CXtestDoc*)COleClientItem::GetDocument(); }
	CXtestView* GetActiveView()
		{ return (CXtestView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXtestCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CXtestCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__55100997_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
