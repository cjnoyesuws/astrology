#if !defined(AFX_DLOCATIONSET_H__DBB8DF1D_3C41_416F_AFCE_2B8F0767451A__INCLUDED_)
#define AFX_DLOCATIONSET_H__DBB8DF1D_3C41_416F_AFCE_2B8F0767451A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLocationset.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDLocationset DAO recordset

class CDLocationset : public CDaoRecordset
{
public:
	CDLocationset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDLocationset)

// Field/Param Data
	//{{AFX_FIELD(CDLocationset, CDaoRecordset)
	CString	m_country;
	CString	m_state;
	CString	m_location;
	CString	m_longitude;
	CString	m_latitude;
	short	m_timezone;
	short	m_specialcode;
	short	m_houroff;
	short	m_minoff;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLocationset)
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

#endif // !defined(AFX_DLOCATIONSET_H__DBB8DF1D_3C41_416F_AFCE_2B8F0767451A__INCLUDED_)
