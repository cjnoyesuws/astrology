#if !defined(AFX_ASPECTTEXT_H__602D2845_FAF4_492E_A89C_EC9B9613C929__INCLUDED_)
#define AFX_ASPECTTEXT_H__602D2845_FAF4_492E_A89C_EC9B9613C929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AspectText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAspectText recordset

class CAspectText : public CRecordset
{
public:
	CAspectText(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAspectText)

// Field/Param Data
	//{{AFX_FIELD(CAspectText, CRecordset)
	CString	m_TextType;
	CString	m_Planet1;
	CString	m_Planet2;
	int		m_Planet1num;
	int		m_Planet2num;
	CString	m_Aspect;
	int		m_Aspectnum;
	CString	m_Text;
	//}}AFX_FIELD
   CString  m_TextTypeParam;
   CString  m_Planet1Param;
   CString  m_Planet2Param;
   CString  m_AspectParam;
   int      m_AspectnumParam;
   int      m_Planet1numParam;
   int      m_Planet2numParam;
   BOOL     m_bIntQuery;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAspectText)
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

#endif // !defined(AFX_ASPECTTEXT_H__602D2845_FAF4_492E_A89C_EC9B9613C929__INCLUDED_)
