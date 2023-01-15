// AstrowDaoFileListView.cpp : implementation of the CAstrowDaoFileListView class
//

#include "stdafx.h"
#include "AstrowDaoFileList.h"

#include "AstrowDaoFileListSet.h"
#include "AstrowDaoFileListDoc.h"
#include "AstrowDaoFileListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListView

IMPLEMENT_DYNCREATE(CAstrowDaoFileListView, CDaoRecordView)

BEGIN_MESSAGE_MAP(CAstrowDaoFileListView, CDaoRecordView)
	//{{AFX_MSG_MAP(CAstrowDaoFileListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CDaoRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CDaoRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CDaoRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListView construction/destruction

CAstrowDaoFileListView::CAstrowDaoFileListView()
	: CDaoRecordView(CAstrowDaoFileListView::IDD)
{
	//{{AFX_DATA_INIT(CAstrowDaoFileListView)
	m_pSet = NULL;
	m_cmtpg = _T("");
	m_comment = _T("");
	m_cover = _T("");
	m_filename = _T("");
	m_name = _T("");
	m_type = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CAstrowDaoFileListView::~CAstrowDaoFileListView()
{
}

void CAstrowDaoFileListView::DoDataExchange(CDataExchange* pDX)
{
	CDaoRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAstrowDaoFileListView)
	DDX_Text(pDX, IDC_CMTPG, m_cmtpg);
	DDX_Text(pDX, IDC_COMMENT, m_comment);
	DDX_Text(pDX, IDC_COVER, m_cover);
	DDX_Text(pDX, IDC_FILENAME, m_filename);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TYPE, m_type);
	//}}AFX_DATA_MAP
}

BOOL CAstrowDaoFileListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDaoRecordView::PreCreateWindow(cs);
}

void CAstrowDaoFileListView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_astrowDaoFileListSet;
	CDaoRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListView printing

BOOL CAstrowDaoFileListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAstrowDaoFileListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAstrowDaoFileListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListView diagnostics

#ifdef _DEBUG
void CAstrowDaoFileListView::AssertValid() const
{
	CDaoRecordView::AssertValid();
}

void CAstrowDaoFileListView::Dump(CDumpContext& dc) const
{
	CDaoRecordView::Dump(dc);
}

CAstrowDaoFileListDoc* CAstrowDaoFileListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstrowDaoFileListDoc)));
	return (CAstrowDaoFileListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListView database support
CDaoRecordset* CAstrowDaoFileListView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListView message handlers
