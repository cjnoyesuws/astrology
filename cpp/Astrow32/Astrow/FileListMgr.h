// FileListMgr.h: interface for the CFileListMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILELISTMGR_H__83820682_456A_44D2_BDF5_255304EFC4ED__INCLUDED_)
#define AFX_FILELISTMGR_H__83820682_456A_44D2_BDF5_255304EFC4ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxcoll.h>
#include "filelistset.h"
#include "fileListcounterset.h"


class CStack : CWordArray {
int m_stackPtr;
public:
	CStack( int sz=20 ) : CWordArray() { SetSize(sz); m_stackPtr=0; }
    void Push( int val ) { SetAtGrow(m_stackPtr++, val );  }
	int Peek() { return GetAt(m_stackPtr-1); }
    int Pop() { if (!m_stackPtr) return( -1 ); else return(GetAt(--m_stackPtr) ); }
};


class CFileListMgr  
{
private:
	BOOL m_bIsTextReport;
	BOOL m_bAll;
	CFileListSet theSet;
	CFileListCounterSet theCounterSet;
	CDWordArray CounterArray;
	CByteArray SelectedArray;
	CStack RecNumStack;
	int m_nRecords;
	CString m_strSort;
	BOOL m_bErrorState;
	int m_iRecNum;
	FILE_DB filedb;
protected:
	void FillArrays();
	void RefillArrays();
	void DoOpen();
    int  IndexOfCounter(long ctr);
public:
	CFileListMgr( short type=ALL_F );
	virtual ~CFileListMgr();
    void ChangeSort( CString &srt );
	CFileListSet *GetRowPtr() { return &theSet; }
	BOOL MoveFirst();
	BOOL MoveLast();
	BOOL MoveNext();
	BOOL MovePrior();
	BOOL MoveRelative(int rows);
	BOOL Add( FILE_DB &db );
	BOOL DeleteItem( int it );
	BOOL DeleteSelection( CWnd *pPar );
	BOOL IsEOF() { return theSet.IsEOF(); }
	BOOL IsBOF() { return theSet.IsBOF(); }
	BOOL SetAbsolutePosition( int r );
    GetSelected(CDWordArray &ar);
    void setSelected(char sel) { SelectedArray[m_iRecNum]=sel; }
    FILE_DB &ToFDB();
	PushPosition(int pos);
	BOOL PopPosition();
	int SelCount();
    int getFileList( CStringArray &sar, CDWordArray &war, int n, int sz, int b4, int cmt, int cvr );
};

class CFileListMgrGraphics : CFileListMgr {
public:
	CFileListMgrGraphics() : CFileListMgr(GRA_F) {}

};


class CFileListMgrReports : CFileListMgr {
public:
	CFileListMgrReports() : CFileListMgr(NON_GRA) {}

};

#endif // !defined(AFX_FILELISTMGR_H__83820682_456A_44D2_BDF5_255304EFC4ED__INCLUDED_)
