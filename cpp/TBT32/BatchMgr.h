#pragma once
#include "afxcoll.h"

class CBatchMgr :
	public CStringArray
{
public:
	CString m_id;
	CString m_dir;
	CBatchMgr(CString &id, CString &dir);
	virtual ~CBatchMgr(void) { RemoveAll(); }
	void Read();
	void Write();
};
