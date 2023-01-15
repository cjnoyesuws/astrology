#pragma once

// TabCtrlCtrl.h : Declaration of the CTabCtrlCtrl ActiveX Control class.


// CTabCtrlCtrl : See TabCtrlCtrl.cpp for implementation.

class CTabCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTabCtrlCtrl)

// Constructor
public:
	CTabCtrlCtrl();
	CString m_Tabs;
	int cxChar;

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	afx_msg void OnRButtonDown(UINT nFlags,CPoint point);
	CString MakeTabString(CString &s);
	CString MakeTabs(LPCTSTR s);


// Implementation
protected:
	~CTabCtrlCtrl();

	BEGIN_OLEFACTORY(CTabCtrlCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CTabCtrlCtrl)

	DECLARE_OLETYPELIB(CTabCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTabCtrlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CTabCtrlCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidDoTheClick = 2L,		dispidDoClick = 1L,		dispidTabString = 1,		eventidMouseDown = 1L
	};
protected:

	BSTR GetTabString(void);
	void SetTabString(LPCTSTR newVal);
	void DoClick(OLE_XPOS_PIXELS xpos);
	void DoTheClick(SHORT xpos);
};

