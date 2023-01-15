// ImportAspText.h: interface for the ImportAspText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTASPTEXT_H__B515CCB6_3BE5_40BF_A481_5B8D156D56A1__INCLUDED_)
#define AFX_IMPORTASPTEXT_H__B515CCB6_3BE5_40BF_A481_5B8D156D56A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ImportAspText  
{
public:
	CString m_dir;
	CDAspectText set;
	CProgress *m_pProg;
	char *filename;
	char *textitem; 
    void Process();
	int ProcessItem( CTextBlock *pBlk );
	ImportAspText(char *fname, char *item, CProgress *p, CString &dir) { filename=fname; textitem=item; m_pProg=p; m_dir = dir; }
	virtual ~ImportAspText() { if ( set.IsOpen() ) set.Close(); }

};

#endif // !defined(AFX_IMPORTASPTEXT_H__B515CCB6_3BE5_40BF_A481_5B8D156D56A1__INCLUDED_)