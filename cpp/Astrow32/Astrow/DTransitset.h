#if !defined(AFX_DTRANSITSET_H__DC91A38F_5B39_4611_845D_F683F31361E8__INCLUDED_)
#define AFX_DTRANSITSET_H__DC91A38F_5B39_4611_845D_F683F31361E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DTransitset.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDTransitset DAO recordset

class CDTransitset : public CDaoRecordset
{
public:
	CDTransitset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDTransitset)

// Field/Param Data
	//{{AFX_FIELD(CDTransitset, CDaoRecordset)
	BOOL	m_AMPM;
	COleDateTime	m_birthdate;
	CString	m_country;
	CString	m_event;
	short	m_houroff;
	short	m_hours;
	CString	m_latitude;
	CString	m_location;
	CString	m_longitude;
	short	m_minoff;
	short	m_minutes;
	CString	m_name;
	short	m_specialcode;
	CString	m_state;
	short	m_timezone;
	COleDateTime	m_transdate;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTransitset)
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

#endif // !defined(AFX_DTRANSITSET_H__DC91A38F_5B39_4611_845D_F683F31361E8__INCLUDED_)
