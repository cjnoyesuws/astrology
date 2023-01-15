#if !defined(AFX_DREGTEXT_H__DF478C87_6379_4A73_8482_5BD205D1A9BE__INCLUDED_)
#define AFX_DREGTEXT_H__DF478C87_6379_4A73_8482_5BD205D1A9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRegText.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDRegText DAO recordset

class CDRegText : public CDaoRecordset
{
public:
	CDRegText(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDRegText)

// Field/Param Data
	//{{AFX_FIELD(CDRegText, CDaoRecordset)
	CString	m_TextType;
	CString	m_Key1;
	CString	m_key2;
	short	m_Key1num;
	short	m_Key2num;
	CString	m_Text;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRegText)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DREGTEXT_H__DF478C87_6379_4A73_8482_5BD205D1A9BE__INCLUDED_)
