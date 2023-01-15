#if !defined(AFX_FILELISTCOUNTERSET_H__311536A3_C9AF_48C9_AFDD_AECFE3DD1FEF__INCLUDED_)
#define AFX_FILELISTCOUNTERSET_H__311536A3_C9AF_48C9_AFDD_AECFE3DD1FEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileListCounterSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileListCounterSet recordset

class CFileListCounterSet : public CRecordset
{
public:
	CFileListCounterSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFileListCounterSet)

// Field/Param Data
	//{{AFX_FIELD(CFileListCounterSet, CRecordset)
	long	m_counter;
	//}}AFX_FIELD
    long    *m_pCounters;
	long    *m_pCounterLengths;
	BOOL    m_IsTextReportParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileListCounterSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual void DoBulkFieldExchange(CFieldExchange* pFX); 
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILELISTCOUNTERSET_H__311536A3_C9AF_48C9_AFDD_AECFE3DD1FEF__INCLUDED_)
