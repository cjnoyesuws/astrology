// TabCtrlCtrl.cpp : Implementation of the CTabCtrlCtrl ActiveX Control class.

#include "stdafx.h"
#include "TabCtrl.h"
#include "TabCtrlCtrl.h"
#include "TabCtrlPropPage.h"
#include ".\tabctrlctrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CTabCtrlCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CTabCtrlCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CTabCtrlCtrl, COleControl)
	DISP_PROPERTY_EX_ID(CTabCtrlCtrl, "TabString", dispidTabString, GetTabString, SetTabString, VT_BSTR)
	DISP_DEFVALUE(CTabCtrlCtrl, "TabString")
	DISP_FUNCTION_ID(CTabCtrlCtrl, "DoClick", dispidDoClick, DoClick, VT_EMPTY, VTS_XPOS_PIXELS)
	DISP_FUNCTION_ID(CTabCtrlCtrl, "DoTheClick", dispidDoTheClick, DoTheClick, VT_EMPTY, VTS_I2)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CTabCtrlCtrl, COleControl)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CTabCtrlCtrl, 1)
	PROPPAGEID(CTabCtrlPropPage::guid)
END_PROPPAGEIDS(CTabCtrlCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTabCtrlCtrl, "TABCTRL.TabCtrlCtrl.1",
	0x5230206e, 0x3e6a, 0x454c, 0x99, 0x99, 0xea, 0xda, 0x11, 0xae, 0x4f, 0x32)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CTabCtrlCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DTabCtrl =
		{ 0xD1F60DF7, 0x733E, 0x4C91, { 0x86, 0x43, 0x7A, 0xC, 0x49, 0xB3, 0xAB, 0xE6 } };
const IID BASED_CODE IID_DTabCtrlEvents =
		{ 0x11CFF31B, 0x719B, 0x440F, { 0x93, 0x63, 0x7D, 0xFD, 0x7C, 0xD8, 0x22, 0xBD } };




// Control type information

static const DWORD BASED_CODE _dwTabCtrlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTabCtrlCtrl, IDS_TABCTRL, _dwTabCtrlOleMisc)



// CTabCtrlCtrl::CTabCtrlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CTabCtrlCtrl

BOOL CTabCtrlCtrl::CTabCtrlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_TABCTRL,
			IDB_TABCTRL,
			afxRegApartmentThreading,
			_dwTabCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("TabCtrl.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 2004 ";



// CTabCtrlCtrl::CTabCtrlCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CTabCtrlCtrl::CTabCtrlCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}



// CTabCtrlCtrl::CTabCtrlCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CTabCtrlCtrl::CTabCtrlCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}



// CTabCtrlCtrl::CTabCtrlCtrl - Constructor

CTabCtrlCtrl::CTabCtrlCtrl()
{
	InitializeIIDs(&IID_DTabCtrl, &IID_DTabCtrlEvents);
	// TODO: Initialize your control's instance data here.
   char buf[100];
   memset(buf,' ',80);
   buf[80] = '\0';
   m_Tabs = buf;
}



// CTabCtrlCtrl::~CTabCtrlCtrl - Destructor

CTabCtrlCtrl::~CTabCtrlCtrl()
{
	// TODO: Cleanup your control's instance data here.

}



// CTabCtrlCtrl::OnDraw - Drawing function

void CTabCtrlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CFont *pFnt=NULL, *pFold = NULL;
	CPen  *pPen=NULL, *pPold = NULL;
	CBrush *pBr=NULL, *pBold = NULL;
	CRect border, clip;
	if (!pdc)
		return;
	border = rcBounds;
	border.bottom--;
	border.top++;
	border.left++;
	border.right--;
	clip = border;
	clip.top+=2;
	clip.bottom--;
	clip.right-=3;
	clip.left++;
	pFnt = new CFont();
	pFnt->CreatePointFont(120,"Courier New",pdc);
	pFold = pdc->SelectObject(pFnt);
	cxChar = pdc->GetTextExtent(" ").cx;
	int nChar = rcBounds.Width()/cxChar;
    pPen = new CPen(PS_SOLID,1,RGB(0,0,0));
    pBr = new CBrush(RGB(0xff,0xff,0xff));
	pPold =pdc->SelectObject(pPen);
    pdc->FillRect(&rcBounds,pBr);
	pdc->Rectangle(&border);
	pdc->SetTextAlign(TA_TOP|TA_LEFT);
	pdc->SetTextColor(RGB(0,0,0));
	pdc->SetBkColor(RGB(0xff,0xff,0xff));
	pdc->ExtTextOut(3,2,ETO_CLIPPED|ETO_OPAQUE,&clip,m_Tabs,nChar,NULL);
    delete pdc->SelectObject(pPold);
    delete pdc->SelectObject(pFold);
	delete pBr;
}



// CTabCtrlCtrl::DoPropExchange - Persistence support

void CTabCtrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CTabCtrlCtrl::OnResetState - Reset control to default state

void CTabCtrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CTabCtrlCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CTabCtrlCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("EDIT");
	return COleControl::PreCreateWindow(cs);
}



// CTabCtrlCtrl::IsSubclassedControl - This is a subclassed control

BOOL CTabCtrlCtrl::IsSubclassedControl()
{
	return TRUE;
}



// CTabCtrlCtrl::OnOcmCommand - Handle command messages

LRESULT CTabCtrlCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}



// CTabCtrlCtrl message handlers

BSTR CTabCtrlCtrl::GetTabString(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult = MakeTabString(m_Tabs);

	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}

void CTabCtrlCtrl::SetTabString(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    m_Tabs = MakeTabs(newVal);
	// TODO: Add your property handler code here
    Invalidate();
	SetModifiedFlag();
}

void CTabCtrlCtrl::OnRButtonDown(UINT nFlags,CPoint point)
{
	int col = (point.x-3) / cxChar;
	if ( m_Tabs.GetAt(col) == 'X' )
		m_Tabs.SetAt(col, ' ');
	else
		m_Tabs.SetAt(col, 'X');
	Invalidate();
}

CString CTabCtrlCtrl::MakeTabString(CString &s)
{
 int iTabs[80];
 char nbf[5];
 CString buf;
 buf = "^@|80|";
 int cnt = 0;
 for ( int i = 0; i < m_Tabs.GetLength(); i++ ) {
	 if ( m_Tabs.GetAt(i) == 'X' )
	    iTabs[cnt++]=i;
     }
 itoa(cnt,nbf,10);
 buf += nbf;
 buf += "|";
 for ( int j = 0; j < cnt; j++ ) {
     itoa(iTabs[j],nbf,10);
	 buf += nbf;
	 buf += "|";
     }
 return ( buf );
}

CString CTabCtrlCtrl::MakeTabs(LPCTSTR s)
{
 CString str;
 int cnt;
 int n;
 char *p, buf[81];

 memset(buf,' ',80);
 buf[80]='\0';
 str = buf;
 p = strchr(s,'|');
 if ( p != NULL )
	 p = strchr(p+1,'|');
 if ( p != NULL ) {
    p++;
    cnt=(*p-'0');
	p++;
	if ( *p != '|' ) {
       cnt *= 10;
	   cnt += (*p-'0');
	   p++;
	   p++;
	   }
	else
       p++;
	for ( int i = 0; i < cnt; i++ ) {
	    n=(*p-'0');
	    p++;
		if ( *p != '|' ) {
            n *= 10;
	        n += (*p-'0');
	        p++;
	        p++;
	        }
		else
            p++;
		str.SetAt(n,'X');
	    }
    }
  return( str );
 }

void CTabCtrlCtrl::DoClick(OLE_XPOS_PIXELS xpos)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    OnRButtonDown(0,CPoint(xpos,0));
	// TODO: Add your dispatch handler code here
}

void CTabCtrlCtrl::DoTheClick(SHORT xpos)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    OnRButtonDown(0,CPoint(xpos,0));
	// TODO: Add your dispatch handler code here
}
