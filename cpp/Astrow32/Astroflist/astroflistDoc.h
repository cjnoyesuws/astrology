// astroflistDoc.h : interface of the CAstroflistDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CAstroflistDoc : public CDocument
{
protected: // create from serialization only
	CAstroflistDoc();
	DECLARE_DYNCREATE(CAstroflistDoc)

// Attributes
public:
	FileListArray *flary;
	int type;
	CPtrArray *ary;
	BOOL newAble;

BOOL &NewAble() { return newAble; }
int &GetType() { return type; }
FileListArray *GetFileList() { return flary; }

// Operations
public:
void Reset() { ary = &(*flary).fileDBArray(type); };
void Update() { UpdateAllViews(NULL); }
void UpdateModified() {SetModifiedFlag(TRUE);UpdateAllViews(NULL);}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstroflistDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstroflistDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstroflistDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
