#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define IDD_NAME 0
#define IDD_COMMENT 1
#define IDD_TYPE 2

extern char long_types[][35];

// CAstFileOpen form view

class CAstFileOpen : public CFormView
{
	DECLARE_DYNCREATE(CAstFileOpen)

protected:
	CAstFileOpen();           // protected constructor used by dynamic creation
	virtual ~CAstFileOpen();

public:
	enum { IDD = IDD_FORMVIEW_FILES };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void LoadList();
	void LoadFolders();
	CString MakeFilter();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeFolder();
	afx_msg void OnBnClickedGraphs();
	afx_msg void OnBnClickedGrids();
	afx_msg void OnBnClickedReports();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	CComboBox m_folders;
	CListCtrl m_list;
	BOOL m_graphs;
	BOOL m_grids;
	BOOL m_reports;
	int m_folderno;
	CFoldersSet m_foldersset;
	CFileListSet m_filelist;
	CStringArray m_selected;
	CStringArray m_filenames;
	CStringArray &GetSelection() { return m_selected; }
	CString m_caption;
	CString m_sort;
	CImageList m_images;
	CBitmap m_reportbmp;
	CBitmap m_graphbmp;
	CBitmap m_gridbmp;
	void SetCaption(CString &cap) { m_caption = cap; }
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};


