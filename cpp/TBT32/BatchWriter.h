#pragma once
#include <afxcoll.h>

class CBatchWriter
{
FILE *stream;
CString m_file;
CString m_path;
CString m_prog;
CString m_args;
CStringArray *m_pFiles;
public:
	CBatchWriter(CString &fil, CString &pth, CString &prg, CString &args, CStringArray *pArr);
	void WriteOne(CString str);
	void WriteBatch();
	virtual ~CBatchWriter(void);
};
