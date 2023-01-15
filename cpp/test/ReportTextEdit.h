#if !defined(AFX_REPORTTEXTEDIT_H__D8D34128_F924_4192_9B80_5785D27811B2__INCLUDED_)
#define AFX_REPORTTEXTEDIT_H__D8D34128_F924_4192_9B80_5785D27811B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportTextEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportTextEdit dialog

class CReportTextEdit : public CDialog
{
// Construction
public:
	CReportTextEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportTextEdit)
	enum { IDD = IDD_REPORTTEXT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportTextEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportTextEdit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTTEXTEDIT_H__D8D34128_F924_4192_9B80_5785D27811B2__INCLUDED_)
