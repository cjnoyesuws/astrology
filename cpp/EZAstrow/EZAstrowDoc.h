// EZAstrowDoc.h : interface of the CEZAstrowDoc class
//


#pragma once

class CEZAstrowDoc : public CDocument
{
protected: // create from serialization only
	CEZAstrowDoc();
	DECLARE_DYNCREATE(CEZAstrowDoc)

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
	virtual ~CEZAstrowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


