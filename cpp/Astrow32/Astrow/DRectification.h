#if !defined(AFX_DRECTIFICATION_H__42880F44_136C_4A4E_9630_4F3D34523973__INCLUDED_)
#define AFX_DRECTIFICATION_H__42880F44_136C_4A4E_9630_4F3D34523973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRectification.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDRectification DAO recordset

class CDRectification : public CDaoRecordset
{
public:
	CDRectification(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDRectification)

// Field/Param Data
	//{{AFX_FIELD(CDRectification, CDaoRecordset)
	CString	m_name;
	COleDateTime	m_birthdate;
	BOOL	m_birth_time_known;
	short	m_rect_system;
	short	m_hours;
	short	m_minutes;
	BOOL	m_am_pm;
	short	m_angle;
	short	m_sign;
	short	m_totalminutes;
	CString	m_degree;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRectification)
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

#endif // !defined(AFX_DRECTIFICATION_H__42880F44_136C_4A4E_9630_4F3D34523973__INCLUDED_)
