#if !defined(AFX_DASPECTTEXT1_H__BC1152C7_B77D_4826_B874_5ECCAD1585F6__INCLUDED_)
#define AFX_DASPECTTEXT1_H__BC1152C7_B77D_4826_B874_5ECCAD1585F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DAspectText1.h : header file
//
#pragma warning( disable : 4995 )
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
	CString m_Lang;
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

#endif // !defined(AFX_DASPECTTEXT1_H__BC1152C7_B77D_4826_B874_5ECCAD1585F6__INCLUDED_)
