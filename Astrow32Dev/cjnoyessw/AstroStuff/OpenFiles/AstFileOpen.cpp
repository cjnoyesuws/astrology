// AstFileOpen.cpp : implementation file
//

#include "stdafx.h"
#include "OpenFiles.h"
#include "direc.hpp"
#include "FileListSet.h"
#include "foldersset.h"
#include "AstFileOpen.h"
#include ".\astfileopen.h"


// CAstFileOpen



IMPLEMENT_DYNCREATE(CAstFileOpen, CFormView)

CAstFileOpen::CAstFileOpen()
	: CFormView(CAstFileOpen::IDD)
	, m_graphs(TRUE)
	, m_grids(TRUE)
	, m_reports(TRUE)
	, m_folderno(10)
	, m_sort(_T("name"))
	, m_caption(_T("Open Files"))
{
}

CAstFileOpen::~CAstFileOpen()
{
}

void CAstFileOpen::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOLDER, m_folders);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Check(pDX, IDC_GRAPHS, m_graphs);
	DDX_Check(pDX, IDC_GRIDS, m_grids);
	DDX_Check(pDX, IDC_REPORTS, m_reports);
}

BEGIN_MESSAGE_MAP(CAstFileOpen, CFormView)
	ON_CBN_SELCHANGE(IDC_FOLDER, OnCbnSelchangeFolder)
	ON_BN_CLICKED(IDC_GRAPHS, OnBnClickedGraphs)
	ON_BN_CLICKED(IDC_GRIDS, OnBnClickedGrids)
	ON_BN_CLICKED(IDC_REPORTS, OnBnClickedReports)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList1)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, OnHdnItemdblclickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnLvnColumnclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CAstFileOpen diagnostics

#ifdef _DEBUG
void CAstFileOpen::AssertValid() const
{
	CFormView::AssertValid();
}

void CAstFileOpen::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CAstFileOpen message handlers

void CAstFileOpen::OnCbnSelchangeFolder()
{
	// TODO: Add your control notification handler code here
	int sel = m_folders.GetCurSel();
	m_folderno = (int) m_folders.GetItemData(sel);
	LoadList();
}

void CAstFileOpen::OnBnClickedGraphs()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	LoadList();
}

void CAstFileOpen::OnBnClickedGrids()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	LoadList();
}

void CAstFileOpen::OnBnClickedReports()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	LoadList();
}

void CAstFileOpen::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	delete this;
}

void CAstFileOpen::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
}

void CAstFileOpen::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	switch( phdr->iItem ) {
	  case 0:
		  m_sort = "name";
		  break;
	  case 1:
		  m_sort = "comments";
		  break;
	  case 2:
		  m_sort = "FileType";
		  break;
	  default:
		  break;
	}
	LoadList();
	*pResult = 0;
}

void CAstFileOpen::OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CAstFileOpen::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CAstFileOpen::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	UpdateData(FALSE);

	m_list.InsertColumn(0,"Name", LVCFMT_LEFT,320,-1);
	m_list.InsertColumn(1,"Comments", LVCFMT_LEFT,300,1);
	m_list.InsertColumn(3,"File Type", LVCFMT_LEFT,300,3);
	m_reportbmp.LoadBitmap(IDB_REPORT);
	m_graphbmp.LoadBitmap(IDB_GRAPH);
	m_gridbmp.LoadBitmap(IDB_GRID);
	m_images.Create(24,24,ILC_COLOR4,3,1);
	m_images.Add(&m_reportbmp,&m_reportbmp);
    m_images.Add(&m_graphbmp,&m_graphbmp);
	m_images.Add(&m_gridbmp,&m_gridbmp);
	m_list.SetImageList(&m_images,LVSIL_SMALL);
	LoadList();
    LoadFolders();


	// TODO: Add your specialized code here and/or call the base class
}

void CAstFileOpen::LoadList()
{
  m_list.DeleteAllItems();
  m_filenames.RemoveAll();
  m_filelist.m_strSort = m_sort;
  m_filelist.m_strFilter = MakeFilter();
  m_filelist.Open();
  int nItem=0, nImage = 0;
  if ( !m_filelist.IsEOF() ) {
	  while ( !m_filelist.IsEOF() ) {
		  if ( m_filelist.m_ListType == "GRA")
			  nImage = 1;
		  else if ( m_filelist.m_ListType == "GRD")
			  nImage = 2;
		  else
			  nImage = 0;
		  m_list.InsertItem(nItem,m_filelist.m_name,nImage);
		  m_list.SetItemText(nItem,1,m_filelist.m_comments);
		  m_list.SetItemText(nItem,2,long_types[m_filelist.m_FileType]);
		  m_filenames.SetAtGrow(nItem,m_filelist.m_filename);
		  m_filelist.MoveNext();
	      nItem++;
	  }
  }
  m_filelist.Close();
}

void CAstFileOpen::LoadFolders()
{
  m_folders.ResetContent();
  int item =m_folders.AddString("Default Folder");
  m_folders.SetItemData(item, 10);
  m_foldersset.Open();
  if ( !m_foldersset.IsBOF() && !m_foldersset.IsEOF() ) {
	  while ( !m_foldersset.IsEOF() ) {
		  item =m_folders.AddString(m_foldersset.m_folder_name);
		  m_folders.SetItemData(item, m_foldersset.m_folder_num);
		  m_foldersset.MoveNext();
	  }
  }
  m_folders.SetCurSel(0);
}

CString CAstFileOpen::MakeFilter()
{
    char *inlist = NULL, buf[300];
	if (m_graphs && m_grids && m_reports)
       inlist = "in ('GRD','OUT','GRA')";
	else if (!m_graphs && m_grids && m_reports)
       inlist = "in ('GRD','OUT')";
    else if (m_graphs && !m_grids && m_reports)
	   inlist = "in ('GRA','OUT')";
	else if (m_graphs && m_grids && !m_reports)
	   inlist = "in ('GRA','GRD')";
	else if ( m_graphs )
	   inlist = "='GRA'";
	else if ( m_grids )
	   inlist = "='GRD'";
	else
	   inlist = "='OUT'";
    sprintf( buf, "ListType %s and Folder=%d", inlist, m_folderno );
	return ( CString(buf));
}
void CAstFileOpen::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
