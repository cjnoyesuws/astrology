// AsxDoc.h : interface of the CAsxDoc class
//


#pragma once

class CAsxDoc : public CDocument
{
protected: // create from serialization only
	CAsxDoc();
	DECLARE_DYNCREATE(CAsxDoc)

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
	virtual ~CAsxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


