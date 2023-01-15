// ImportHelp.h: interface for the ImportHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTHELP_H__AF3A2B64_14FC_4119_A251_361C20727D38__INCLUDED_)
#define AFX_IMPORTHELP_H__AF3A2B64_14FC_4119_A251_361C20727D38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dhelptxt1.h"
#include "strtransform.h"
#include "fileary.hpp"
#include "setup.h"

class ImportHelp  
{
public:
   CDHelpTxt set;
   CString dir;
   BOOL m_bExport;
   CProgress *m_pProg;
   ImportHelp(CProgress *p, CString &dr, BOOL bExp=FALSE) {m_pProg=p; dir=dr; m_bExport = bExp; }
   virtual ~ImportHelp() { if ( set.IsOpen() ) set.Close(); }
   int ProcessItem(char *item);
   void Process();
};

#endif // !defined(AFX_IMPORTHELP_H__AF3A2B64_14FC_4119_A251_361C20727D38__INCLUDED_)
