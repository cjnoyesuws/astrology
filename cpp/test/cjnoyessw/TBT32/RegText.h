#if !defined(AFX_REGTEXT_H__2B49830E_E2A4_438F_ACC6_35D34305CB85__INCLUDED_)
#define AFX_REGTEXT_H__2B49830E_E2A4_438F_ACC6_35D34305CB85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegText recordset

class CRegText : public CRecordset
{
public:
	CRegText(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRegText)

// Field/Param Data
	//{{AFX_FIELD(CRegText, CRecordset)
	CString	m_TextType;
	CString	m_Key1;
	CString	m_key2;
	int		m_Key1num;
	int		m_Key2num;
	CString	m_Text;
	//}}AFX_FIELD
   CString  m_TextTypeParam;
   CString  m_Key1Param;
   CString  m_Key2Param;
   int      m_Key1numParam;
   int      m_Key2numParam;
   BOOL     m_bIntQuery;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegText)
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

#endif // !defined(AFX_REGTEXT_H__2B49830E_E2A4_438F_ACC6_35D34305CB85__INCLUDED_)
