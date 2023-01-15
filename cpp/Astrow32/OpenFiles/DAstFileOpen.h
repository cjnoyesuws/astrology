#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "charcons.h"
#include "foldersset.h"
#include "filelistset.h"
// CDAstFileOpen dialog

class CDAstFileOpen : public CDialog
{
	DECLARE_DYNAMIC(CDAstFileOpen)

public:
	CDAstFileOpen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDAstFileOpen();

// Dialog Data
	enum { IDD = IDD_FILEOPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CComboBox m_folders;
	CListCtrl m_list;
	BOOL m_graphs;
	BOOL m_grids;
	BOOL m_reports;
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeFolder();
	afx_msg void OnBnClickedGraphs();
	afx_msg void OnBnClickedGrids();
	afx_msg void OnBnClickedReports();
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
    void LoadList();
	void LoadFolders();
	CString MakeFilter();
};
