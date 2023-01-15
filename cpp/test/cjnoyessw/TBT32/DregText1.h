#if !defined(AFX_DREGTEXT1_H__B12D5764_3AF6_4DCF_B480_B9ACB29F5272__INCLUDED_)
#define AFX_DREGTEXT1_H__B12D5764_3AF6_4DCF_B480_B9ACB29F5272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DregText1.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDregText DAO recordset

class CDregText : public CDaoRecordset
{
public:
	CDregText(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDregText)

// Field/Param Data
	//{{AFX_FIELD(CDregText, CDaoRecordset)
	CString	m_TextType;
	CString	m_Key1;
	CString	m_key2;
	short	m_Key1num;
	short	m_Key2num;
	CString	m_Text;
	CString m_Lang;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDregText)
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

#endif // !defined(AFX_DREGTEXT1_H__B12D5764_3AF6_4DCF_B480_B9ACB29F5272__INCLUDED_)
