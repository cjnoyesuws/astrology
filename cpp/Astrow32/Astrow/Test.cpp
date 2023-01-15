// Test.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest dialog


CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
	//{{AFX_MSG_MAP(CTest)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_ITALIC, OnItalic)
	ON_UPDATE_COMMAND_UI(ID_ITALIC, OnUpdateItalic)
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, OnUpdateNormal)
	ON_COMMAND(ID_HEADING, OnHeading)
	ON_UPDATE_COMMAND_UI(ID_HEADING, OnUpdateHeading)
	ON_COMMAND(ID_BOLD, OnBold)
	ON_UPDATE_COMMAND_UI(ID_BOLD, OnUpdateBold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest message handlers

void CTest::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnEditDelete() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnEditUndo() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnItalic() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnNormal() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnHeading() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateHeading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CTest::OnBold() 
{
	// TODO: Add your command handler code here
	
}

void CTest::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
