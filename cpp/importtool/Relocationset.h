#if !defined(AFX_RELOCATIONSET_H__8D7F4019_BABB_44C1_ADF4_49298F692BC0__INCLUDED_)
#define AFX_RELOCATIONSET_H__8D7F4019_BABB_44C1_ADF4_49298F692BC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Relocationset.h : header file
//
#include <afxdisp.h>
/////////////////////////////////////////////////////////////////////////////
// CRelocationset recordset

class CRelocationset : public CRecordset
{
public:
	CRelocationset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRelocationset)

// Field/Param Data
	//{{AFX_FIELD(CRelocationset, CRecordset)
	CString m_personal;
	CString	m_name;
	COleDateTime	m_birthdate;
	CString	m_country;
	CString	m_state;
	CString	m_location;
	CString	m_longitude;
	CString	m_latitude;
	int		m_timezone;
	int		m_specialcode;
	int		m_houroff;
	int		m_minoff;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelocationset)
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

#endif // !defined(AFX_RELOCATIONSET_H__8D7F4019_BABB_44C1_ADF4_49298F692BC0__INCLUDED_)
