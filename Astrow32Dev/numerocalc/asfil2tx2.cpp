#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
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
#include "acombbox.hpp"
#include "inifile.hpp"
#include "asfrmdlg.hpp"
#include "convopt.hpp"
#include "coverdat.hpp"
#include "msg.hpp"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "write.hpp"
#include "writecnv.hpp"
#include "basedcs.h"
#include "asfrmdlg.hpp"
#include "edit.hpp"
#include "asfil2tx.hpp"

char _far conv_file[150];

static char BCS nb[] = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 };

char *asc_indent = NULL;


astroFileToText::astroFileToText(int d)
{
 dir = d;
 pm = new ProcMessage( " Converting File ", &_break );
 buffer = new char[ 5000 ];
 if ( buffer == NULL ) {
    do_mem_error( 0 );
    delete pm;
    pm = NULL;
    exp_buf = NULL;
    return;
    }
 exp_buf = new char[ 10000 ];
 if ( exp_buf == NULL ) {
    do_mem_error( 0 );
    delete pm;
    pm = NULL;
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
 delete pm;
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
       default :
	   return( NULL );
	   break;
       }
 return( NULL );
 }

int astroFileToText::getSetup( zWindow *pPar, ConvData **pCd )
{
 static char *types[] = { "Document Files (*.DOC)","*.DOC",
		       "Text Files (*.TXT)","*.TXT",
		       "All Files (*.*)", "*.*", 0, 0 };

 strcpy( outfile, "TEXT.DOC" );
 pm->releaseMouse();
 zFileSaveAsForm *fsaf = new zFileSaveAsForm( pPar,
		"Save Astro File As.", outfile, types );
 if ( !fsaf->completed() ) {
    delete fsaf;
    return( 0 );
    }
 strcpy( outfile, fsaf->name() );
 delete fsaf;
 cd.getFromIni();
 ConvDataDlgf *cdf = new ConvDataDlgf(pPar, &cd );
 *pCd = &cd;
 pm->setCursor( zCursor(Hourglass) );
 pm->captureMouse();
 if ( cdf->completed() ) {
    cdf->getData();
    cd.saveToIni();
    pm->update();
    delete cdf;
    return( 1 );
    }
 delete cdf;
 return( 0 );
}

void astroFileToText::setFiles(char **files, int hc)
{
 fileList = files;
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

 if ( ( instream = freadx_fptr( infile, &xfpt, 0 ) ) == NULL ) {
    do_error( infile );
    return( 0 );
    }
 ansi = (int) GetPrivateProfileInt( Misc_SEC, "AnsiText", ansi, APPNAME );
 drvr = getDriver();
 drvr->setCenter(cd.getCenter());
 drvr->setJustify(cd.getJust());
 zWinDisplay *z = new zWinDisplay((zWindow *)pm);
 ReportStyles rs(z);
 rs.getFromIni(ConvData_SEC);
 delete z;
 drvr->setStyles(&rs);
 if ( !code || code == -1 ) {
    am = drvr->getOpenMode();
    if ( ( outstream = _fsopen( outfile, am, SH_DENYWR  ) ) == NULL ) {
       delete drvr;
       do_error( outfile );
       fclose( instream );
       return( 0 );
       }
    strcpy( conv_file, outfile );
    }
 drvr->setStreams( instream, outstream );
 drvr->initDriver( cd.getFileAttribs() );
 drvr->initDecomp( (nb[cd.getFmt()]?32000:cd.getWidth()) );
 drvr->initStringPrint( cd.getLeft(), (nb[cd.getFmt()]?32000:cd.getWidth()), cd.getFmt(), code );
 setvbuf(instream, buffer, _IOFBF, 4096 );
 while( !feof(instream) && !ferror(instream) && err == 0 ) {
    zYield();
    s = drvr->decompress( exp_buf, outsiz, &lines, 0 );
    if ( ( err = drvr->stringPrint( exp_buf ) ) )
	 do_error( outfile );
    fflush( outstream );
    if ( _break ) {
       fclose( instream );
       delete drvr;
       return( 0 );
       }
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


int astroFileToText::doConvert(FILE_DB *db)
{
 int code = 0, ret;
 char buf[100], **p;
#ifdef PRO
 CoverPageData *cpd;
 zString *s = NULL;
#endif
 if ( *(fileList+1) == NULL ) {
    strcpy( buf, set_path( *fileList, dir ) );
    ret = convert( buf, -1 );
    fclose( outstream );
    return( ret );
    }
 else {
    for ( p = fileList; *p != NULL; p++, code++ ) {
	if ( *(p+1) == NULL )
	   code = -2;
	if ( p == fileList && !hasCover || p != fileList )
	   strcpy( buf, set_path( *p, dir ) );
#ifdef PRO
	else {
	   cpd = getCover( *p, db );
	   s = cpd->toAstFile();
	   strcpy( buf, (char *)*s );
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


CoverPageData *astroFileToText::getCover( char *name, FILE_DB *db )
{
#ifdef PRO
 char buf[150], *dot;
 CoverPageData *cpd;

 cpd = new CoverPageData();
 if ( cpd == NULL )
    return( NULL );
 strcpy( buf, set_path( name, USER_F ) );
 if ( access( buf, 6 ) == -1 ) {
    delete cpd;
    return( NULL );
    }
 else {
    if ( !cpd->load(buf) ) {
       cpd->create(db);
       return( cpd );
       }
    }
 return( cpd );
#else
 return( 0 );
#endif
}


int doConvText( zWindow *pPar, FILE_DB *pFd )
{
 int n=0;
 char nbuf[15], *ar[4], nbuf2[15];
 astroFileToText *txt;
 ConvData *pcd;

 if ( pFd == NULL )
    return( 0 );
 txt = new astroFileToText(USER_F);
 if ( !txt->getSetup(pPar, &pcd ) ) {
    delete txt;
    return( 0 );
    }
#ifdef PRO
 if ( pcd->getCpg() && pFd->has_cover ) {
    ar[0] = replace_ext(nbuf, pFd->file_name, ".CPG");
    n++;
    }
 if ( pcd->getCmt() && pcd->getCmtFst() && pFd->has_comments ) {
    ar[n] = replace_ext(nbuf2, pFd->file_name, ".CMT");
    n++;
    }
#endif
 ar[n] = pFd->file_name;
 n++;
#ifdef PRO
 if ( pcd->getCmt() && !pcd->getCmtFst() && pFd->has_comments ) {
    ar[n] = replace_ext(nbuf2, pFd->file_name, ".CMT");
    n++;
    }
#endif
 ar[n] = NULL;
 txt->setFiles( ar, n > 1 );
 txt->doConvert(pFd);
 delete txt;
 return( 1 );
}


int doSelConvText(zWindow *pPar, FileListArray *fla )
{
#ifndef _QDTRAN_
 int n, count, fcount;
 char *fbuf, **flist, nbuf[15];
 FILE_DB **ptr, **pt;
 int i;
 ConvData *pcd;
 astroFileToText *txt;
 
 fla->check();
 count = fla->selCount(NON_GRA);
 if ( !count )
    return(0);
 ptr = new FILE_DB *[count+2];
 if ( ptr == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 count = fla->getSelection(NON_GRA, count, ptr);
 txt = new astroFileToText(USER_F);
 if ( !txt->getSetup(pPar, &pcd ) ) {
    delete txt;
    return( 0 );
    }
 fcount = getFileCount( ptr, count, pcd->getCmt() );
 flist = new char *[fcount+2];
 fbuf = new char[(fcount+2)*15];
 if ( flist == NULL || fbuf == NULL ) {
    do_mem_error(0);
    if ( flist != NULL )
       delete flist;
    if ( fbuf != NULL )
       delete fbuf;
    delete ptr;
    delete txt;
    return( 0 );
    }
 getFileList( ptr, flist, fbuf, count, fcount, pcd->getCmtFst(), pcd->getCmt() );
 if ( pcd->getCpg() && (*ptr)->has_cover )
    txt->setFiles(flist, 1 );
 else
    txt->setFiles(flist, 0 );
 txt->doConvert(*ptr);
 delete txt;
#endif
 return( 0 );
}
#ifdef PRO
int doEdit( zWindow *pPar, FILE_DB *pFd )
{
 EditSetup es;

 if ( pFd == NULL )
    return( 0 );
 es.getFromIni();
 if ( !doConvText( pPar, pFd ) )
    return( 0 );
 zString optstr((unsigned int)100), pathstr((unsigned int)200);
 sprintf( (char *)optstr, es.getOpt(), conv_file );
 pathstr = es.getPath() & " " & optstr;
 if ( WinExec( (char *)pathstr, SW_SHOW ) < 32 ) {
    alert_box_ext(ERROR2, MB_OK|MB_ICONSTOP, "Error Starting %s",
	  (char _far *)es.getPath());
    return( 0 );
    }
 return( 1 );

}

#endif

/*

class TestApp : public zAppFrame {
	zTextPane* out;
public:
       	TestApp(char * title);
	virtual int command(zCommandEvt *);
	~TestApp() { delete out; }
	};

TestApp::TestApp(char * title):zAppFrame(0,new zSizer,zSTDFRAME,title) {
	out = new zTextPane(this,new zSizeWithParent);
	out->show();
	menu(new zMenu(this));
	menu()->addStr(101, "&Do It");
	menu()->update();
}

TestApp::command(zCommandEvt *e)
{
 static char *types[] = { "ASTRO Reports (*.OUT)", "*.OUT", 0, 0 };
 FILE_DB file;

 if (e->cmd() == 101 ) {
    zFileOpenForm *fof = new zFileOpenForm(this, "File to View", "*.out", types );
      if ( fof->completed() ) {
         strcpy( file.file_name, strrchr( fof->name(), '\\' )+1 );
	 doConvText( this, &file );
         }
    delete fof;
    }
 return 1;
}

void zApp::main() {
	theDirectories.getFromIni("test.ini");
        TestApp *p=new TestApp("Test Tester");
	p->show();
	go();
	delete p;
}
*/
