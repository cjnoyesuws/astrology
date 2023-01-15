#pragma once
#include "basedbexport.h"
#include "DRegText1.h"

class CRegDbExport :
	public CBaseDbExport
{
CDregText set;
public:
	CRegDbExport(CString &dir, CProgress *prog, int items, CString &lang) : 
	    CBaseDbExport(dir,prog,items,lang) {}
	virtual ~CRegDbExport(void);
    virtual void Process();
};
