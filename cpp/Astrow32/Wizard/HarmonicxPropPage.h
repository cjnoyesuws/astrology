#pragma once


// CHarmonic dialog

class CHarmonicPropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CHarmonicPropPage)

public:
	CHarmonicPropPage();   // standard constructor
	virtual ~CHarmonicPropPage();

// Dialog Data
	enum { IDD = IDD_HARMONIC_PROP_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_harmonic;
	int GetValue(void);
	void SetValue(int m_Value);
    virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
};
