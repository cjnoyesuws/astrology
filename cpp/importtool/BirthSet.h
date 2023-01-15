#if !defined(AFX_BIRTHSET_H__6E4C2619_D6C4_41C8_915E_11E81BDD4721__INCLUDED_)
#define AFX_BIRTHSET_H__6E4C2619_D6C4_41C8_915E_11E81BDD4721__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BirthSet.h : header file
//
#include <afxdisp.h>
/////////////////////////////////////////////////////////////////////////////
// CBirthSet recordset

class CBirthSet : public CRecordset
{
public:
	CBirthSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBirthSet)

// Field/Param Data
	//{{AFX_FIELD(CBirthSet, CRecordset)
	CString	m_name;
	COleDateTime	m_birthdate;
	int		m_hours;
	int		m_minutes;
	BOOL	m_AMPM;
	CString	m_country;
	CString	m_state;
	CString	m_location;
	CString	m_longitude;
	CString	m_latitude;
	int		m_timezone;
	int		m_specialcode;
	int		m_houroff;
	int		m_minoff;
	BOOL	m_rect;
	int		m_sex;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirthSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIRTHSET_H__6E4C2619_D6C4_41C8_915E_11E81BDD4721__INCLUDED_)
