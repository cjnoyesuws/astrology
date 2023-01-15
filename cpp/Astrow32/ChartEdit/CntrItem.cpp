// CntrItem.cpp : implementation of the CChartEditCntrItem class
//

#include "stdafx.h"
#include "ChartEdit.h"

#include "ChartEditDoc.h"
#include "ChartEditView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartEditCntrItem implementation

IMPLEMENT_SERIAL(CChartEditCntrItem, CRichEditCntrItem, 0)

CChartEditCntrItem::CChartEditCntrItem(REOBJECT* preo, CChartEditDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CChartEditCntrItem::~CChartEditCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CChartEditCntrItem diagnostics

#ifdef _DEBUG
void CChartEditCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CChartEditCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
