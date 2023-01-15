// OpenFilesDoc.h : interface of the COpenFilesDoc class
//


#pragma once

class COpenFilesDoc : public CDocument
{
protected: // create from serialization only
	COpenFilesDoc();
	DECLARE_DYNCREATE(COpenFilesDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~COpenFilesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


