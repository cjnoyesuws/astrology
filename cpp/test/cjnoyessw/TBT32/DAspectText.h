#if !defined(AFX_DASPECTTEXT_H__5947B376_3BE0_41A4_9ABD_D91AF74D8DEF__INCLUDED_)
#define AFX_DASPECTTEXT_H__5947B376_3BE0_41A4_9ABD_D91AF74D8DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DAspectText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAspectText DAO recordset

class CDAspectText : public CDaoRecordset
{
public:
	CDAspectText(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDAspectText)

// Field/Param Data
	//{{AFX_FIELD(CDAspectText, CDaoRecordset)
	CString	m_TextType;
	CString	m_Planet1;
	CString	m_Planet2;
	short	m_Planet1num;
	short	m_Planet2num;
	CString	m_Aspect;
	short	m_Aspectnum;
	CString	m_Text;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAspectText)
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

#endif // !defined(AFX_DASPECTTEXT_H__5947B376_3BE0_41A4_9ABD_D91AF74D8DEF__INCLUDED_)
