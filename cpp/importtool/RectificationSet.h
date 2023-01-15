#if !defined(AFX_RECTIFICATIONSET_H__F0EB17C3_F15E_4026_95E9_AEF9A0C8908E__INCLUDED_)
#define AFX_RECTIFICATIONSET_H__F0EB17C3_F15E_4026_95E9_AEF9A0C8908E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RectificationSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRectificationSet recordset

class CRectificationSet : public CRecordset
{
public:
	CRectificationSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRectificationSet)

// Field/Param Data
	//{{AFX_FIELD(CRectificationSet, CRecordset)
	CString	m_name;
	COleDateTime	m_birthdate;
	BOOL	m_birth_time_known;
	int		m_rect_system;
	int		m_hours;
	int		m_minutes;
	BOOL	m_am_pm;
	int		m_angle;
	int		m_sign;
	int		m_totalminutes;
	CString m_degree;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectificationSet)
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

#endif // !defined(AFX_RECTIFICATIONSET_H__F0EB17C3_F15E_4026_95E9_AEF9A0C8908E__INCLUDED_)
