#if !defined(AFX_REPORTTEXT_H__523B1E22_EE10_4A0F_8A22_3CF31774ACE3__INCLUDED_)
#define AFX_REPORTTEXT_H__523B1E22_EE10_4A0F_8A22_3CF31774ACE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportText recordset

class CReportText : public CRecordset
{
public:
	CReportText(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CReportText)

// Field/Param Data
	//{{AFX_FIELD(CReportText, CRecordset)
	CString	m_texttype;
	CString	m_textkey;
	int		m_iIndex;
	int		m_iTextKey;
	CString	m_text;
	//}}AFX_FIELD
   CString  m_texttypeParam;
   CString  m_textkeyParam;
   int  m_iIndexParam;
   int  m_iTextKeyParam;
   BOOL m_bIntQuery;
   LPSTR m_pStrTexts;
   long *m_pTextLens;
   int *m_piIndex;
   long *m_piIndexLens;
   int *m_piTextKey;
   long *m_piTextKeyLens;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportText)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
   virtual void DoBulkFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTTEXT_H__523B1E22_EE10_4A0F_8A22_3CF31774ACE3__INCLUDED_)
