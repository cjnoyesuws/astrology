#pragma once


// ZipCodeDlg dialog

class ZipCodeDlg : public CDialog
{
	DECLARE_DYNAMIC(ZipCodeDlg)

public:
	ZipCodeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ZipCodeDlg();
	void SetLocDB(LOC_DB *pDb) { m_loc_db_rec = pDb; }

// Dialog Data
	enum { IDD = IDD_ZIPCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_zip_code;
	LOC_DB  *m_loc_db_rec;
protected:
	virtual void OnOK();
	void toDegMin( CString &str, DEG_MIN &deg, BOOL bLat);
};
