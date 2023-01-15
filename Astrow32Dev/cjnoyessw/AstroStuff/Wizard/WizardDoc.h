// WizardDoc.h : interface of the CWizardDoc class
//


#pragma once

class CWizardDoc : public CDocument
{
protected: // create from serialization only
	CWizardDoc();
	DECLARE_DYNCREATE(CWizardDoc)

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
	virtual ~CWizardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


