// TabCtrlPropPage.cpp : Implementation of the CTabCtrlPropPage property page class.

#include "stdafx.h"
#include "TabCtrl.h"
#include "TabCtrlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CTabCtrlPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CTabCtrlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTabCtrlPropPage, "TABCTRL.TabCtrlPropPage.1",
	0xea8c936, 0x72e1, 0x466b, 0x9f, 0xb9, 0x4d, 0xca, 0x65, 0x56, 0x5c, 0xf5)



// CTabCtrlPropPage::CTabCtrlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CTabCtrlPropPage

BOOL CTabCtrlPropPage::CTabCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_TABCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CTabCtrlPropPage::CTabCtrlPropPage - Constructor

CTabCtrlPropPage::CTabCtrlPropPage() :
	COlePropertyPage(IDD, IDS_TABCTRL_PPG_CAPTION)
{
}



// CTabCtrlPropPage::DoDataExchange - Moves data between page and properties

void CTabCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CTabCtrlPropPage message handlers
