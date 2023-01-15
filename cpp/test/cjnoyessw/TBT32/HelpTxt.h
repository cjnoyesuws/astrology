#if !defined(AFX_HELPTXT_H__174CCA69_ABEA_44F3_989A_3CB066ED8681__INCLUDED_)
#define AFX_HELPTXT_H__174CCA69_ABEA_44F3_989A_3CB066ED8681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpTxt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHelpTxt recordset

class CHelpTxt : public CRecordset
{
public:
	CHelpTxt(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHelpTxt)

// Field/Param Data
	//{{AFX_FIELD(CHelpTxt, CRecordset)
	CString	m_texttype;
	CString	m_Text;
	//}}AFX_FIELD
   CString m_TextTypeParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpTxt)
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

#endif // !defined(AFX_HELPTXT_H__174CCA69_ABEA_44F3_989A_3CB066ED8681__INCLUDED_)
