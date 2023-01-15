#if !defined(AFX_REPORTTEXTS_H__551543BB_BA55_4FAE_B564_811484102B43__INCLUDED_)
#define AFX_REPORTTEXTS_H__551543BB_BA55_4FAE_B564_811484102B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportTexts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportTexts recordset

class CReportTexts : public CRecordset
{
public:
	CReportTexts(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CReportTexts)

// Field/Param Data
	//{{AFX_FIELD(CReportTexts, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportTexts)
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

#endif // !defined(AFX_REPORTTEXTS_H__551543BB_BA55_4FAE_B564_811484102B43__INCLUDED_)
