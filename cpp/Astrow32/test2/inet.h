#if !defined(AFX_INET_H__2B5B2937_688D_4787_B54D_A866A2D5BEE7__INCLUDED_)
#define AFX_INET_H__2B5B2937_688D_4787_B54D_A866A2D5BEE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CInet wrapper class

class CInet : public CWnd
{
protected:
	DECLARE_DYNCREATE(CInet)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x48e59293, 0x9880, 0x11cf, { 0x97, 0x54, 0x0, 0xaa, 0x0, 0xc0, 0x9, 0x8 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	long GetProtocol();
	void SetProtocol(long nNewValue);
	CString GetRemoteHost();
	void SetRemoteHost(LPCTSTR lpszNewValue);
	short GetRemotePort();
	void SetRemotePort(short nNewValue);
	CString GetResponseInfo();
	long GetResponseCode();
	long GetHInternet();
	BOOL GetStillExecuting();
	CString GetUrl();
	void SetUrl(LPCTSTR lpszNewValue);
	CString GetProxy();
	void SetProxy(LPCTSTR lpszNewValue);
	CString GetDocument();
	void SetDocument(LPCTSTR lpszNewValue);
	long GetAccessType();
	void SetAccessType(long nNewValue);
	CString GetUserName_();
	void SetUserName(LPCTSTR lpszNewValue);
	CString GetPassword();
	void SetPassword(LPCTSTR lpszNewValue);
	long GetRequestTimeout();
	void SetRequestTimeout(long nNewValue);
	VARIANT OpenURL(const VARIANT& URL, const VARIANT& DataType);
	void Execute(const VARIANT& URL, const VARIANT& Operation, const VARIANT& InputData, const VARIANT& InputHdrs);
	void Cancel();
	VARIANT GetChunk(long* Size, const VARIANT& DataType);
	CString GetHeader(const VARIANT& HdrName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INET_H__2B5B2937_688D_4787_B54D_A866A2D5BEE7__INCLUDED_)
