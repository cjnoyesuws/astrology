#if !defined(AFX_TRANSITSET_H__801027CD_9A6A_48DA_ACE4_2386FF9329C9__INCLUDED_)
#define AFX_TRANSITSET_H__801027CD_9A6A_48DA_ACE4_2386FF9329C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// transitSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CtransitSet recordset

class CtransitSet : public CRecordset
{
public:
	CtransitSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtransitSet)

// Field/Param Data
	//{{AFX_FIELD(CtransitSet, CRecordset)
	CString	m_name;
	COleDateTime	m_birthdate;
	COleDateTime    m_transdate;
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
	CString	m_Event;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CtransitSet)
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

#endif // !defined(AFX_TRANSITSET_H__801027CD_9A6A_48DA_ACE4_2386FF9329C9__INCLUDED_)
