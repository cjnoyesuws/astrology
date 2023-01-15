#pragma once

// TabCtrlPropPage.h : Declaration of the CTabCtrlPropPage property page class.


// CTabCtrlPropPage : See TabCtrlPropPage.cpp for implementation.

class CTabCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTabCtrlPropPage)
	DECLARE_OLECREATE_EX(CTabCtrlPropPage)

// Constructor
public:
	CTabCtrlPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_TABCTRL };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

