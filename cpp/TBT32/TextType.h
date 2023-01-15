#if !defined(AFX_TEXTTYPE_H__AA4E37FC_E079_4DD9_A558_1A9FF8989474__INCLUDED_)
#define AFX_TEXTTYPE_H__AA4E37FC_E079_4DD9_A558_1A9FF8989474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextType dialog

class CTextType : public CDialog
{
// Construction
public:
	CTextType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextType)
	enum { IDD = IDD_TEXTTYPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextType)
	afx_msg void OnSelchangeTexttype();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTTYPE_H__AA4E37FC_E079_4DD9_A558_1A9FF8989474__INCLUDED_)
