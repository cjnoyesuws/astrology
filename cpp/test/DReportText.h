#if !defined(AFX_DREPORTTEXT_H__E26CDE22_6587_442F_972D_C5A7AFF0E854__INCLUDED_)
#define AFX_DREPORTTEXT_H__E26CDE22_6587_442F_972D_C5A7AFF0E854__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DReportText.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDReportText DAO recordset

class CDReportText : public CDaoRecordset
{
public:
	CDReportText(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDReportText)

// Field/Param Data
	//{{AFX_FIELD(CDReportText, CDaoRecordset)
	CString	m_texttype;
	CString	m_textkey;
	short	m_iIndex;
	short	m_iTextKey;
	CString	m_text;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDReportText)
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

#endif // !defined(AFX_DREPORTTEXT_H__E26CDE22_6587_442F_972D_C5A7AFF0E854__INCLUDED_)
