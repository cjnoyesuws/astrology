#if !defined(AFX_DBIRTHSET_H__E3971771_C838_4F28_B9CB_BAE1AA5058A1__INCLUDED_)
#define AFX_DBIRTHSET_H__E3971771_C838_4F28_B9CB_BAE1AA5058A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBirthset.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDBirthset DAO recordset

class CDBirthset : public CDaoRecordset
{
public:
	CDBirthset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDBirthset)

// Field/Param Data
	//{{AFX_FIELD(CDBirthset, CDaoRecordset)
	CString	m_name;
	COleDateTime	m_birthdate;
	short	m_hours;
	short	m_minutes;
	BOOL	m_AMPM;
	CString	m_country;
	CString	m_state;
	CString	m_location;
	CString	m_longitude;
	CString	m_latitude;
	short	m_timezone;
	short	m_specialcode;
	short	m_houroff;
	short	m_minoff;
	BOOL	m_rect;
	short	m_sex;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBirthset)
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

#endif // !defined(AFX_DBIRTHSET_H__E3971771_C838_4F28_B9CB_BAE1AA5058A1__INCLUDED_)
