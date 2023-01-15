// AstroeditDoc.h : interface of the CAstroeditDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CAstroeditDoc : public CRichEditDoc
{
protected: // create from serialization only
	CAstroeditDoc();
	DECLARE_DYNCREATE(CAstroeditDoc)
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo = NULL) const {return NULL;}
// Attributes
public:
	int SaveFile( CString &act, CString &virt );
	CString ActualFile;
	CString VirtualFile;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstroeditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstroeditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstroeditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
