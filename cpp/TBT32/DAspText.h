#if !defined(AFX_DASPTEXT_H__7D619CE7_20A1_4D3D_80D3_0805967B9028__INCLUDED_)
#define AFX_DASPTEXT_H__7D619CE7_20A1_4D3D_80D3_0805967B9028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DAspText.h : header file
//
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDAspText DAO recordset

class CDAspText : public CDaoRecordset
{
public:
	CDAspText(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDAspText)

// Field/Param Data
	//{{AFX_FIELD(CDAspText, CDaoRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAspText)
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

#endif // !defined(AFX_DASPTEXT_H__7D619CE7_20A1_4D3D_80D3_0805967B9028__INCLUDED_)
