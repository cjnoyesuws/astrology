#pragma once
#include "afxwin.h"


// CTransWiz dialog

class CTransWiz : public CDialog
{
	DECLARE_DYNAMIC(CTransWiz)

public:
	CTransWiz(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransWiz();

// Dialog Data
	enum { IDD = IDD_TRANSTASKS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void ExportAspectText();
    void ExportHelpText();
    void ExportRegularText();
    void ExportReportText();
    void ImportAspectFiles();
    void ImportHelpFiles();
    void ImportPlanetFiles();
    void ImportReportFiles();
	void WriteABatch(LPCTSTR name, CString &prog, CString &args, LPCTSTR bid );
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedImport();
	afx_msg void OnBnClickedMerge();
	afx_msg void OnBnClickedPrepare();
	afx_msg void OnBnClickedSetbasedir();
	afx_msg void OnBnClickedSetcurrlang();
	afx_msg void OnBnClickedSettransdir();
	afx_msg void OnBnClickedAddnewlang();
	afx_msg void OnBnClickedCheck();
	BOOL m_aspexp;
	BOOL m_aspimp;
	BOOL m_hlpexp;
	BOOL m_hlpimp;
	BOOL m_regexp;
	BOOL m_regimp;
	BOOL m_reptexp;
	BOOL m_reptimp;
};