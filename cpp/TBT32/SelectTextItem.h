#if !defined(AFX_SELECTTEXTITEM_H__04A5EFA5_5A71_4534_85F6_F3CA0918B4A7__INCLUDED_)
#define AFX_SELECTTEXTITEM_H__04A5EFA5_5A71_4534_85F6_F3CA0918B4A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectTextItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectTextItem dialog

class CSelectTextItem : public CDialog
{
// Construction
public:
	CSelectTextItem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectTextItem)
	enum { IDD = IDD_SELTEXTITEM };
	int		m_Item;
	//}}AFX_DATA
   CString m_strItem;
   int m_type;
   int m_ary;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectTextItem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectTextItem)
	afx_msg void OnSelchangeTextitem();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTTEXTITEM_H__04A5EFA5_5A71_4534_85F6_F3CA0918B4A7__INCLUDED_)
