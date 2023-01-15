#if !defined(AFX_DLANGUAGES_H__915D7E1B_4661_4174_A99A_7F9CEC915FF8__INCLUDED_)
#define AFX_DLANGUAGES_H__915D7E1B_4661_4174_A99A_7F9CEC915FF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLanguages.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDLanguages DAO recordset

class CDLanguages : public CDaoRecordset
{
public:
	CDLanguages(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDLanguages)

// Field/Param Data
	//{{AFX_FIELD(CDLanguages, CDaoRecordset)
	CString	m_langcode;
	CString	m_Description;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLanguages)
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

#endif // !defined(AFX_DLANGUAGES_H__915D7E1B_4661_4174_A99A_7F9CEC915FF8__INCLUDED_)
