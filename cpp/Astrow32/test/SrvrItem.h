// SrvrItem.h : interface of the CTestSrvrItem class
//

class CTestSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CTestSrvrItem)

// Constructors
public:
	CTestSrvrItem(CTestDoc* pContainerDoc);

// Attributes
	CTestDoc* GetDocument() const
		{ return (CTestDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CTestSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
