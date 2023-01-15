#pragma once
#include "afxcoll.h"

class CFolders :
	public CStringArray
{
protected :
	int FldCount;
	int CurFolder;
	CString CurFolderName;
public:
	int &GetCurFolder() { return CurFolder; }
	CString &GetCurFolderName() { return CurFolderName; }
	CFolders();
	virtual ~CFolders();
	void ChangeFolder(int fld);
	void AddFolder(CString &fn);
	void RenameFolder(CString &newn);
	void getFromIni();
	void SaveToIni();
	void toCombo(CComboBox *p);
	CString GetFolder(int i);
};

extern CFolders theFolders;