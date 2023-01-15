#pragma once
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "utlduad.h"
#include "charttypeproppage.h"
#include "databaseodbc.hpp"
#include "birthinfoproppage.h"
#include "transinfoproppage.h"
#include "transdataproppage.h"
#ifdef DELUXE
#include "harmonicxproppage.h"
#include "progrdataproppage.h"
#include "relocscrproppage.h"
#include "returndataproppage.h"
#include "solararcproppage.h"
#endif
#include "inifile.hpp"
#include "options.hpp"
#include "setup.hpp"
#include "procmsg.h"
#include "compile.hpp"
// CChartWizard

class CChartWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CChartWizard)

public:
	CChartWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CChartWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CChartWizard();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_chart_type;
	int m_old_file_type;
	int m_file_type;
	enum ChartType m_chart_type_enum;
	CChartTypePropPage m_chart_typepp;
	CBirthInfoPropPage m_birthinfo_pp;
	CBirthInfoPropPage *m_pcompatinfo_pp;
	CTransInfoPropPage m_transinfo_pp;
	CTransDataPropPage m_transdata_pp;
#ifdef DELUXE
	CHarmonicPropPage m_harmonic_pp;
	CRelocScrPropPage m_reloc_pp;
	CReturnDataPropPage m_return_data_pp;
	CProgrDataPropPage m_progr_pp;
	CSolarArcPropPage m_solar_pp;
#endif
	XPFILE_DB *fileinfo;
	DATA_PACKET_EXT chart_data_ptrs;
	BOOL bNorthLatitude;
	short m_defRectMethod;
	enum ChartType GetChartTypeEnum();
	int &GetChartType() { return m_chart_type; }
	int &GetFileType() { return m_file_type; }
	void SetChartType(int nChartType);
	BOOL &NorthLatitude() { return bNorthLatitude; };
	void InitializeSheet();
	void DoAddPages(void);
	void SetFileDb(XPFILE_DB *p) { fileinfo = p; }
	void SetChartDataPtrs(DATA_PACKET_EXT &cdp) { chart_data_ptrs = cdp; }
	DATA_PACKET_EXT &GetChartDataPtrs() { return chart_data_ptrs; }
	void HandleButtons();
	short &DefaultRectMethod() { return m_defRectMethod; }
};


