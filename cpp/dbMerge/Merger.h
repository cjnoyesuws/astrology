#pragma once

class CMerger
{
public:
	CMerger(ImporterData *data);
	virtual ~CMerger(void);
	void process(void);
	void setdata(CADORecordset *pSource, CADORecordset *pDest);
	ImporterData *m_pData;
};
