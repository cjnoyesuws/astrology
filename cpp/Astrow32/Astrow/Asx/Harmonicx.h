#pragma once


// CHarmonic dialog

class CHarmonic : public CDialog
{
	DECLARE_DYNAMIC(CHarmonic)

public:
	CHarmonic(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHarmonic();

// Dialog Data
	enum { IDD = IDD_HARMONIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_harmonic;
	int GetValue(void);
	void SetValue(int m_Value);
};
