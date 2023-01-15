#if !defined(AFX_DComboset_H__DBB8DF1D_3C41_416F_AFCE_2B8F0767451A__INCLUDED_)
#define AFX_DComboset_H__DBB8DF1D_3C41_416F_AFCE_2B8F0767451A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DComboset.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDComboset DAO recordset

class CDComboset : public CDaoRecordset
{
public:
	CDComboset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDComboset)

// Field/Param Data
	//{{AFX_FIELD(CDComboset, CDaoRecordset)
   CString m_data;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDComboset)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL
   CString m_field;
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DComboset_H__DBB8DF1D_3C41_416F_AFCE_2B8F0767451A__INCLUDED_)
