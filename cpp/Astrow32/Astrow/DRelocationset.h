#if !defined(AFX_DRELOCATIONSET_H__8DC37B7C_7887_4AF0_B986_FFE18C8092C6__INCLUDED_)
#define AFX_DRELOCATIONSET_H__8DC37B7C_7887_4AF0_B986_FFE18C8092C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRelocationset.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDRelocationset DAO recordset

class CDRelocationset : public CDaoRecordset
{
public:
	CDRelocationset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDRelocationset)

// Field/Param Data
	//{{AFX_FIELD(CDRelocationset, CDaoRecordset)
	COleDateTime	m_birthdate;
	CString	m_country;
	short	m_houroff;
	CString	m_latitude;
	CString	m_location;
	CString	m_longitude;
	short	m_minoff;
	CString	m_name;
	CString	m_personal;
	short	m_specialcode;
	CString	m_state;
	short	m_timezone;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRelocationset)
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

#endif // !defined(AFX_DRELOCATIONSET_H__8DC37B7C_7887_4AF0_B986_FFE18C8092C6__INCLUDED_)
