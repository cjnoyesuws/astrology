#if !defined(AFX_LOCATIONSET_H__BD21C851_A072_4B74_998E_A338135DD690__INCLUDED_)
#define AFX_LOCATIONSET_H__BD21C851_A072_4B74_998E_A338135DD690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocationSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocationSet recordset

class CLocationSet : public CRecordset
{
public:
	CLocationSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLocationSet)

// Field/Param Data
	//{{AFX_FIELD(CLocationSet, CRecordset)
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
	//{{AFX_VIRTUAL(CLocationSet)
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

#endif // !defined(AFX_LOCATIONSET_H__BD21C851_A072_4B74_998E_A338135DD690__INCLUDED_)
