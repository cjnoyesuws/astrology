// ImportRegText.h: interface for the ImportRegText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTREGTEXT_H__F38D1AD0_2525_4EB0_B5EF_1D19142B8E8B__INCLUDED_)
#define AFX_IMPORTREGTEXT_H__F38D1AD0_2525_4EB0_B5EF_1D19142B8E8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ImportRegText  
{
public:
	CString m_dir;
	CDregText set;
	char *filename;
	char *textitem;
	CProgress *m_pProg;
	ImportRegText(char *fname, char *item, CProgress *p, CString &dir) { filename=fname; textitem=item; m_pProg=p; m_dir = dir; }
	virtual ~ImportRegText() { if ( set.IsOpen() ) set.Close(); }
    void Process();
	int ProcessItem( CTextBlock *pBlk );


};

#endif // !defined(AFX_IMPORTREGTEXT_H__F38D1AD0_2525_4EB0_B5EF_1D19142B8E8B__INCLUDED_)
