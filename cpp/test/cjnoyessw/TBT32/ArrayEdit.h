#pragma once


// CArrayEdit dialog

class CArrayEdit : public CDialog
{
	DECLARE_DYNAMIC(CArrayEdit)

public:
	CArrayEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CArrayEdit();
    CString m_item;
	int m_index;
	CString m_orig;
	BOOL m_bModified;
    CString m_texttype;
	CString m_symtypes;
// Dialog Data
	enum { IDD = IDD_ARRAYEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetTextType( char *p) {m_texttype = p;}
	void SetSymTypes( char *p) {m_symtypes=p;}
	CString m_Edit;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	void FillList(CString &s);
	void DoSave();
public:
	afx_msg void OnBnClickedInsert();
};
