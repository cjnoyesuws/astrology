// AstrowDaoFileListSet.h : interface of the CAstrowDaoFileListSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASTROWDAOFILELISTSET_H__81A4DA3C_930A_4805_96FA_1915B323160E__INCLUDED_)
#define AFX_ASTROWDAOFILELISTSET_H__81A4DA3C_930A_4805_96FA_1915B323160E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAstrowDaoFileListSet : public CDaoRecordset
{
public:
	CAstrowDaoFileListSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAstrowDaoFileListSet)

// Field/Param Data
	//{{AFX_FIELD(CAstrowDaoFileListSet, CDaoRecordset)
	CString	m_name;
	CString	m_comments;
	CString	m_filename;
	short	m_filenum;
	BOOL	m_IsTextReport;
	BYTE	m_FileType;
	long	m_counter;
	BOOL	m_has_cover;
	BOOL	m_has_comments;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrowDaoFileListSet)
	public:
	virtual CString GetDefaultDBName();		// REVIEW:  Get a comment here
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTROWDAOFILELISTSET_H__81A4DA3C_930A_4805_96FA_1915B323160E__INCLUDED_)

