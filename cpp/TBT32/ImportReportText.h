// ImportReportText.h: interface for the ImportReportText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTREPORTTEXT_H__113B7EBB_20D8_45A7_A552_87107F20C2E4__INCLUDED_)
#define AFX_IMPORTREPORTTEXT_H__113B7EBB_20D8_45A7_A552_87107F20C2E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ImportReportText  
{
public:
	CString m_dir;
	CDReportText set;
	char filename[50];
	char textitem[50];
	CProgress *m_pProg;
	ImportReportText(char *fnamestr, char *item, CProgress *prg, CString &dir);
	virtual ~ImportReportText() { if ( set.IsOpen() ) set.Close(); }
    void Process();
	int ProcessItem( CTextBlock *pBlk, char *tt );
	

};

#endif // !defined(AFX_IMPORTREPORTTEXT_H__113B7EBB_20D8_45A7_A552_87107F20C2E4__INCLUDED_)
