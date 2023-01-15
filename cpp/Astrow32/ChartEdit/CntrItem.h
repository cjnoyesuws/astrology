// CntrItem.h : interface of the CChartEditCntrItem class
//

#if !defined(AFX_CNTRITEM_H__6E38BD84_584C_4850_9E5B_F7440438B4CC__INCLUDED_)
#define AFX_CNTRITEM_H__6E38BD84_584C_4850_9E5B_F7440438B4CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChartEditDoc;
class CChartEditView;

class CChartEditCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CChartEditCntrItem)

// Constructors
public:
	CChartEditCntrItem(REOBJECT* preo = NULL, CChartEditDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CChartEditDoc* GetDocument()
		{ return (CChartEditDoc*)CRichEditCntrItem::GetDocument(); }
	CChartEditView* GetActiveView()
		{ return (CChartEditView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartEditCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CChartEditCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__6E38BD84_584C_4850_9E5B_F7440438B4CC__INCLUDED_)
