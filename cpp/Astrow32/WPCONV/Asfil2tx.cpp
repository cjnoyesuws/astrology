#include "stdafx.h"
#include "astrow.h"
#include <stdio.h>
#include <share.h>
#include <stdlib.h>
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "attrib.h"
#include "errors.fns"
#include "output.fns"
#include "charcons.h"
#include "fptr.h"
#include "inifile.hpp"
#include "convopt.hpp"
#include "paths.hpp"
#include "coverdat.hpp"
#include "repstyle.hpp"
#include "convertdata.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "filelst.hpp"
#include <direct.h>
#include "edit.hpp"

//#include "filelst.hpp"
//#include "edit.hpp"
#include "asfil2tx.hpp"

char conv_file[_MAX_PATH];

static char nb[] = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1 };

char *asc_indent = NULL;


astroFileToText::astroFileToText(int d)
{
 fileList = NULL;
 dir = d;
 prs = 0;
 ansi=1;
 buffer = new char[ 5000 ];
 if ( buffer == NULL ) {
    do_mem_error( 0 );
    exp_buf = NULL;
    return;
    }
 exp_buf = new char[ 10000 ];
 if ( exp_buf == NULL ) {
    do_mem_error( 0 );
    delete buffer;
    buffer = NULL;
    return;
    }
}


astroFileToText::~astroFileToText()
{
 if ( buffer != NULL )
    delete buffer;
 if ( exp_buf != NULL )
    delete exp_buf;
 if ( prs != NULL )
    delete prs;
}

TextConvDriver *astroFileToText::getDriver()
{
 switch( cd.getFmt() ) {
       case PLASCIIDOS :
       case PLASCNBDOS :
	    return( new TextConvDriverPlainAscii(ansi, 1) );
	    break;
       case PLASCIIANS :
       case PLASCNBANS :
	    return( new TextConvDriverPlainAscii(ansi, 0) );
	    break;
       case ASCIITXDOS :
       case ASCIINBDOS :
	    return( (TextConvDriver *) new TextConvDriver(ansi, 1) );
	    break;
       case ASCIITXANS :
       case ASCIINBANS :
	    return( (TextConvDriver *) new TextConvDriver(ansi, 0) );
	    break;
       case WS3 :
	    return((TextConvDriver *) new TextConvDriverWStar3(ansi) );
	    break;
       case WS4 :
	    return((TextConvDriver *) new TextConvDriverWStar4(ansi) );
	    break;
       case WORDPFC4:
	    return((TextConvDriver *) new TextConvDriverWP4(ansi) );
	    break;
       case WORDPFC5:
	    return((TextConvDriver *) new TextConvDriverWP5(ansi) );
	    break;
       case WORDPFC6 :
        return((TextConvDriver*) new TextConvDriverWP6(ansi));
        break;
       case XYWRITE:
       case XYWRINB:
	    return((TextConvDriver *) new TextConvDriverXYW(ansi) );
	    break;
       case MS_RTFDOS:
	    return((TextConvDriver *) new TextConvDriverRTF(ansi, 1));
	    break;
       case MS_RTFANS:
	    return((TextConvDriver *) new TextConvDriverRTF(ansi, 0));
	    break;
       case MS_WRITE:
	    return((TextConvDriver *)new TextConvDriverWriAscii(ansi, 0) );
	    /* return((TextConvDriver *) new TextConvDriverWrite(ansi)); */
            break;
       case AMIPRO:
	    return((TextConvDriver *) new TextConvDriverAmi( ansi ) );
	    break;
      /* case WORDPFCI:
	    return((TextConvDriver *) new TextConvDriverWPi( ansi ) );
	    break; */
       case WWW_HTML:
	    return((TextConvDriver *) new TextConvDriverHTML( ansi ) );
	    break;
       default :
	    return( NULL );
	    break;
       }
 return( NULL );
 }

int astroFileToText::getSetup( ConvData **pCd )
{
 CString types = "Document Files (*.DOC)|*.DOC|"
		          "Text Files (*.TXT)|*.TXT|"
				  "RTF Files (*.RTF)|*.RTF|"
				  "HTML Files (*.HTML)|*.HTML|"
		          "All Files (*.*)|*.*|\0\0" ;

 strcpy( outfile, "TEXT.DOC" );
 CFileDialog cfd( FALSE, ".DOC", outfile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, types );
 if ( cfd.DoModal() != IDOK )
    return( 0 );
 else
    strcpy( outfile, cfd.GetPathName() );
 strcpy( conv_file, cfd.GetPathName() );
 cd.getFromIni();
 CConvertData cdd;
 *pCd = &cd;
 CDC *dc = new CDC;
 dc->CreateIC("DISPLAY",NULL,NULL,0);
 prs = new ReportStyles(dc);
 prs->getFromIni(ConvData_SEC);
 cdd.SetData(cd,*prs);
 delete dc;
 if ( cdd.DoModal() == IDOK ) {
	cdd.GetData(cd);
    cd.saveToIni();
	return( 1 );
    }
 return( 0 );
}

void astroFileToText::setFiles(CStringArray *ar, int hc)
{
 fileList = ar;
 hasCover = hc;
}

int astroFileToText::convert( char *infile, int code )
{
 FILE *instream;
 char *am;
 unsigned int outsiz = 7000, s;
 int err = 0, lines;
 TextConvDriver *drvr;
 NFP xfpt;

 char *dot = strrchr(infile,'.' );
 if ( dot != NULL ) {
	if ( !strcmpi(dot,".GRA") ) {
	   alert_box("", "Can\'t Export Graphic File %s as Text!", infile );
	   return( 0 );
	   }
	}
 if ( ( instream = freadx_fptr( infile, &xfpt, 0 ) ) == NULL ) {
    do_error( infile );
    return( 0 );
    }
 ansi = (int) AfxGetApp()->GetProfileInt( Misc_SEC, "AnsiText", ansi );
 drvr = getDriver();
 drvr->IsMbString = isafptr3wxu_file( &xfpt );
 drvr->setCenter(cd.getCenter());
 drvr->setJustify(cd.getJust());
 CDC *dc = new CDC;
 dc->CreateIC("DISPLAY",NULL,NULL,0);
 if ( prs != 0 ) {
	prs = new ReportStyles(dc);
    prs->getFromIni(ConvData_SEC);
	}
 delete dc;
 drvr->setStyles(prs);
 if ( !code || code == -1 ) {
    am = drvr->getOpenMode();
    if ( ( outstream = fopen( outfile, am  ) ) == NULL ) {
       delete drvr;
       do_error( outfile );
       fclose( instream );
       return( 0 );
       }
    strcpy( conv_file, outfile );
    }
 drvr->setStreams( instream, outstream );
 drvr->initDriver( &cd.getFileAttribs() );
 drvr->initDecomp( (nb[cd.getFmt()]?32000:cd.getWidth()) );
 drvr->initStringPrint( cd.getLeft(), (nb[cd.getFmt()]?32000:cd.getWidth()), cd.getFmt(), code );
 setvbuf(instream, NULL, _IOFBF, 4096 );
 while( !feof(instream) && !ferror(instream) && err == 0 ) {
    s = drvr->decompress( exp_buf, outsiz, &lines, 0 );
    if ( ( err = drvr->stringPrint( exp_buf ) ) )
	 do_error( outfile );
    fflush( outstream );
    }
 if ( ferror( instream ) )
    do_error( infile );
 if ( code == -1 || code == -2 )
    drvr->finishUpJob();
 else
    drvr->finishUpFile();
 fclose( instream );
 delete drvr;
 return( 1 );
}


int astroFileToText::doConvert(XPFILE_DB *db)
{
 int code = 0, ret, i;
 char buf[350];
#ifdef PRO
 CoverPageData *cpd;
 CString *s = NULL;
#endif
 if ( (*fileList)[1] == "NULL" ) {
    strcpy( buf, set_path( (char *)(LPCTSTR)(*fileList)[0], dir ) );
    ret = convert( buf, -1 );
    fclose( outstream );
    return( ret );
    }
 else {

	for ( i = 0; (*fileList)[i] != "NULL"; code++, i++ ) {
		if ( (*fileList)[i+1] == "NULL")
			code = -2;
		strcpy( buf, set_path( (char *)(LPCTSTR)(*fileList)[i], dir ) );
#ifdef PRO
	    if ( strstr(buf, ".CPG" ) != NULL ) {
			cpd = getCover( buf );
			s = cpd->toAstFile();
			strcpy( buf, (char *)(LPCTSTR)*s );
			}
#endif
		if ( !( ret = convert( buf, code ) ) )
		   break;
#ifdef PRO
		if ( s != NULL ) {
			cpd->deleteTemp();
			delete cpd;
			cpd = NULL;
			s = NULL;
			}
#endif
		}
    }
 fclose( outstream );
 return( ret );
}


CoverPageData *astroFileToText::getCover( char *name )
{
#ifdef PRO
char buf[200];
NFP xfpt;
CoverPageData *cpd;
FILE *stream;

 cpd = new CoverPageData();
 if ( cpd == NULL )
    return( NULL );
 if ( access( name, 6 ) == -1 ) {
    delete cpd;
    return( NULL );
    }
 else {
    if ( !cpd->load(name) ) {
       replace_ext( buf, name, ".OUT" );
	   if ( ( stream = freadx_fptr( buf, &xfpt, 0 ) ) == NULL )
          return( NULL );
	   fclose( stream );
	   cpd->create(&xfpt.x.fpt);
       return( cpd );
       }
    }
 return( cpd );
#else
 return( 0 );
#endif
}



int doConvText( CWnd *pPar, XPFILE_DB *pFd )
{
 int n=0;
 char buf[250];
 astroFileToText *txt;
 ConvData *pcd;
 CString s;
 static CStringArray sar;

 sar.SetSize(4,0);
 if ( pFd == NULL )
    return( 0 );
 txt = new astroFileToText(pFd->folder);
 if ( !txt->getSetup(&pcd ) ) {
    delete txt;
    return( 0 );
    }
#ifdef PRO
 if ( pcd->getCpg() && pFd->has_cover ) {
    s = replace_ext(buf, pFd->file_name, ".CPG");
	sar[n++] = s;
    }
 if ( pcd->getCmt() && pcd->getCmtFst() && pFd->has_comments ) {
    s = replace_ext(buf, pFd->file_name, ".CMT");
	sar[n++] = s;
	}
#endif
 s = pFd->file_name;
 sar[n++] = s;
 #ifdef PRO
 if ( pcd->getCmt() && !pcd->getCmtFst() && pFd->has_comments ) {
    s = replace_ext(buf, pFd->file_name, ".CMT");
	sar[n++] = s;
    }
#endif
 s = "NULL";
 sar[n++] = s;
 txt->setFiles( &sar, n > 2 );
 txt->doConvert(pFd);
 delete txt;
 return( 1 );
}

#ifndef CHARTVIEW
int doSelConvText(CWnd *pPar, FileListArray *fla, int type )
{
 int n, count, fcount;
 char *fbuf, **flist, nbuf[15];
 XPFILE_DB db;
 int i;
 ConvData *pcd;
 astroFileToText *txt;
 CWordArray war;
 CStringArray sar;

 fla->check();
 count = fla->selCount(type, fla->GetCurFolder());
 if ( !count ) {
	 return( 0 );
	}
 else {
	war.SetSize(count+2,5);
	count = fla->getSelection(NON_GRA, count, war, fla->GetCurFolder());
	}
 CPtrArray &par = fla->fileDBArray(NON_GRA, fla->GetCurFolder());

 txt = new astroFileToText(fla->GetCurFolder());
 if ( !txt->getSetup(&pcd ) ) {
    delete txt;
    return( 0 );
    }
 fcount = getFileCount( war, par, count, pcd->getCmt(), pcd->getCpg() );
 sar.SetSize(fcount+1,2);
 getFileList( sar, war, par, count, fcount, pcd->getCmtFst(), pcd->getCmt(), pcd->getCpg() );
 if ( pcd->getCpg() && strstr((char *)(LPCTSTR)sar[0],".CPG") != NULL )
    txt->setFiles(&sar, 1 );
 else
    txt->setFiles(&sar, 0 );
 txt->doConvert(&db);
 delete txt;
 return( 0 );
}


#ifdef PRO

int doEdit( CWnd *pPar, FileListArray *fla, int type )
{
 EditSetup es;
 char optstr[200];
 char path[300];
 CString pathstr;

 es.getFromIni();
 if ( !doSelConvText(pPar, fla, type ))
    return( 0 );
 if ( !es.UseShell() ) {
    sprintf( optstr, es.getOpt(), conv_file );
    pathstr = es.getPath() + " " + optstr;
    if ( WinExec( (LPCTSTR)pathstr, SW_SHOW ) < 32 ) {
       alert_box_ext(ERROR2, MB_OK|MB_ICONSTOP, "Error Starting %s",
	     (char *)(LPCTSTR)es.getPath());
       return( 0 );
		}
	}
	else {
     _getcwd(path,299);
	 if ( (int)ShellExecute( NULL, "open", conv_file, NULL, path, SW_SHOW) < 32 ) {
	    alert_box_ext(ERROR2, MB_OK|MB_ICONSTOP, "Error Starting %s", conv_file);
        return( 0 );
		}
	}
 return( 1 );
}


int doEdit( CWnd *pPar, XPFILE_DB *pFd )
{
 EditSetup es;
 char optstr[200];
 char path[300];
 CString pathstr;

 if ( pFd == NULL )
    return( 0 );
 es.getFromIni();
 if ( !doConvText( pPar, pFd ) )
    return( 0 );
 if ( !es.UseShell() ) {
    sprintf( optstr, es.getOpt(), conv_file );
    pathstr = es.getPath() + " " + optstr;
    if ( WinExec( (LPCTSTR)pathstr, SW_SHOW ) < 32 ) {
       alert_box_ext(ERROR2, MB_OK|MB_ICONSTOP, "Error Starting %s",
	     (char *)(LPCTSTR)es.getPath());
       return( 0 );
		}
	}
	else {
     _getcwd(path,299);
	 if ( (int)ShellExecute( NULL, "open", conv_file, NULL, path, SW_SHOW) < 32 ) {
	    alert_box_ext(ERROR2, MB_OK|MB_ICONSTOP, "Error Starting %s", conv_file);
        return( 0 );
		}
	}
 return( 1 );
}

#endif
#endif
