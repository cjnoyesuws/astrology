#pragma once
#include "basedbexport.h"
#include "DReportText1.h"

class CReptDbExport :
	public CBaseDbExport
{
CDReportText set;
public:
	CReptDbExport(CString &dir, CProgress *prog, int items, CString &lang) : 
	    CBaseDbExport(dir,prog,items,lang) {}
	virtual ~CReptDbExport(void);
    virtual void Process();
};
