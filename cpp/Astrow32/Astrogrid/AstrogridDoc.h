// AstrogridDoc.h : interface of the CAstrogridDoc class
//


#pragma once

class CAstrogridDoc : public CDocument
{
protected: // create from serialization only
	CAstrogridDoc();
	DECLARE_DYNCREATE(CAstrogridDoc)

// Attributes
public:
    XPFILE_DB db;
	CString m_strName;
	CString m_strTemp;
    CString m_strDoc;
	CString m_strHTML;
	void makeURL(CString &s);
// Operations
public:
    int CanClose;
	int num_files;
	int file_no;
	CStringArray* pStringArray;
// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
    
// Implementation
public:
	virtual ~CAstrogridDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstrogridDoc)
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddtoMru);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void OnCloseDocument(void);
	void SetCanClose(int c) { CanClose = c; }
    void SetMultiFiles( CStringArray *par, int num ) { pStringArray = par; num_files = num; file_no = 1; }
	int HasMoreFiles() { if (file_no < num_files ) return 1; else return 0;}
	void DoNextFile();
	int GetFileNo() { return file_no; }
	int canClose() { return CanClose; }
	void DoPrint();
	CString &Url() { return m_strHTML; }
};


