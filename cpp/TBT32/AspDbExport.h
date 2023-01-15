#pragma once
#include "basedbexport.h"
#include "DAspecttext1.h"

class CAspDbExport :
	public CBaseDbExport
{
CDAspectText set;
public:
	CAspDbExport(CString &dir, CProgress *prog, int items, CString &lang) : 
	    CBaseDbExport(dir,prog,items,lang) {}
	virtual ~CAspDbExport(void);
	virtual void Process();
};
