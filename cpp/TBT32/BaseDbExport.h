#pragma once
#include "TBT32.h"
#include <afxcmn.h>
#include "Progress.h"
#include <afxcoll.h>

class CBaseDbExport
{
protected:
    FILE *m_stream;
	CString m_Directory;
	CString m_CurrFile;
	CProgress *m_pProgress;
	CString m_Lang;
	CStringArray *m_pFiles;
public:
	CBaseDbExport(CString &dir, CProgress *prog, int items, CString &lang);
	virtual ~CBaseDbExport(void);
	void SetProgCount(int cnt);
	BOOL OpenFile(CString &fil);
	void CloseFile();
	void WriteHeader(CString &h1, CString &h2, CString &h3);
	void WriteText( CString &txt );
	CString MakeSQL( CString &table, CString &where, CString &order); 
	virtual void Process();
	void SetArray( CStringArray *par ) { m_pFiles = par; }
};
