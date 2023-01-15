#if !defined(AFX_DHELPTXT_H__EF610F21_B219_4969_B520_113AE6F2BF6B__INCLUDED_)
#define AFX_DHELPTXT_H__EF610F21_B219_4969_B520_113AE6F2BF6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DHelpTxt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDHelpTxt DAO recordset

class CDHelpTxt : public CDaoRecordset
{
public:
	CDHelpTxt(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDHelpTxt)

// Field/Param Data
	//{{AFX_FIELD(CDHelpTxt, CDaoRecordset)
	CString	m_texttype;
	CString	m_Text;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHelpTxt)
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

#endif // !defined(AFX_DHELPTXT_H__EF610F21_B219_4969_B520_113AE6F2BF6B__INCLUDED_)
