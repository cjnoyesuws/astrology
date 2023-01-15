// ImportThread.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include "ImportThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportThread

IMPLEMENT_DYNCREATE(CImportThread, CWinThread)

CImportThread::CImportThread()
{
}

CImportThread::~CImportThread()
{
}

BOOL CImportThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CImportThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CImportThread, CWinThread)
	//{{AFX_MSG_MAP(CImportThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportThread message handlers
