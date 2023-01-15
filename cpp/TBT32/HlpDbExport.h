#pragma once
#include "basedbexport.h"
#include "DHelptxt1.h"

class CHlpDbExport :
	public CBaseDbExport
{
CDHelpTxt set;
public:
	CHlpDbExport(CString &dir, CProgress *prog, int items, CString &lang) : 
	    CBaseDbExport(dir,prog,items,lang) {}
	virtual ~CHlpDbExport(void);
	virtual void Process();
};
