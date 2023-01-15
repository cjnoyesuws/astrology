#include "StdAfx.h"
#include "ado.h"
#include "importerdata.h"
#include "merger.h"
#include "comutil.h"

char *enquote( const char *p, char *buf )
{
 char *sp = (char *)p, *bp = buf;
 while ( *sp ) {
       if ( *sp == '\'' )
          *bp++ = *sp;
	   *bp++ = *sp++;
    }
 *bp++ = '\0';
 *bp++ = '\0';
 return buf;
}

CMerger::CMerger(ImporterData *data)
: m_pData(NULL)
{
 m_pData = data;
}

CMerger::~CMerger(void)
{
}

CString makeSelect( int cnt, char **prim, _variant_t **vars, char *table )
{
 char buf1[100];
 _bstr_t bstr;
 CString str = "Select * from "; 
 str += table;
 str += " where ";
 for ( int i = 0; i < cnt; i++ ) {
     str+= prim[i];
	 str += "=";
	 bstr =*vars[i];
	 if ( !strcmpi(prim[i],"birthdate") )
		 str += "#";
	 else
		 str += "'";
	 str += enquote((const char *)bstr,buf1);
	 if ( !strcmpi(prim[i],"birthdate") )
		 str += "#";
	 else
		 str += "'";
	 if ( i < cnt-1 )
        str += " and ";
 }
 return str;
}

void CMerger::process(void)
{
	char select[200];
	char  *prim[5];
	int prim_count = 1;
    _variant_t *ptrs[5];

	prim[0] =strtok((char *)(LPCSTR)m_pData->m_pkeys,",");
	ptrs[0] = new _variant_t;
	int idx = 1;
	int rec = 1;
	char *tok;
	while ( (tok = strtok(NULL,",") ) != NULL ) {
	   ptrs[idx] = new _variant_t;
	   prim[idx] = tok;
	   idx++;
	   prim_count++;
	}
	CADORecordset m_source(m_pData->m_pSourceDb), m_dest(m_pData->m_pDestDb);
	int status;
	CADOFieldInfo info;
	try {
		sprintf(select,"select * from %s order by %s", m_pData->m_table, m_pData->m_sort);
		m_source.Open(select);
		//m_dest.MoveFirst();	
		m_pData->m_pProgress->SetRange(0,m_source.GetRecordCount());
		m_pData->m_pProgress->SetStep(1);
		m_source.MoveFirst();
        _variant_t srcf;
		//_variant_t dstf;
		//m_source.m_pDAORecordset->GetRows(rw,&rw);
		do {
	        for ( int i = 0; i < prim_count; i++ ) {
			    m_source.GetFieldInfo(prim[i],&info);
			    m_source.GetFieldValue(info.m_strName,*ptrs[i]);
			    }
		    m_dest.Open((char *)(LPCSTR)makeSelect(prim_count,prim,ptrs,(char *)(LPCSTR)m_pData->m_table));
			if ( m_dest.IsBOF() || m_dest.IsEOF() )
				status = 1;
			else
				status = 0;
            if ( status )
				m_dest.AddNew();
			else
				m_dest.Edit();
			setdata(&m_source,&m_dest);
			  //long pos = m_dest.GetAbsolutePosition();
			m_dest.Update();
			m_dest.Close();
			  //m_dest.SetAbsolutePosition(pos);
			m_source.MoveNext();
			rec++;
			m_pData->m_pProgress->StepIt();
			} while (!m_source.IsEOF() && !m_source.IsBOF());
		m_source.Close();

	}
	catch ( CADOException *e ) {
	  char buf[500];
	  e->GetErrorMessage(buf,500);
	  AfxMessageBox(buf);
	}
}

void CMerger::setdata(CADORecordset *pSource, CADORecordset *pDest)
{
 int count = pSource->GetFieldCount();
 CADOFieldInfo info;
 for ( int i = 0; i < count; i++ ) {
     pSource->GetFieldInfo(i,&info);
	 if ( 1 ) {
	    _variant_t data;
	    pSource->GetFieldValue(info.m_strName,data);
	    pDest->SetFieldValue(info.m_strName,data);
	    }
	 } 
 }
