#include "stdafx.h"
#include "paths.hpp"
#include "errors.fns"
#include "DHelpTxt.h"
#include "asthlper.hpp"
#include "Astro.h"
#include "inifile.hpp"
#include "direc.hpp"


int AstHelperItem::read( FILE *stream, CDHelpTxt *pSet )
{
 char nbuf[35], tibuf[50];
 char sqlbuf[100], errbuf[500];
 fgets(nbuf,34,stream);
 nbuf[strlen(nbuf)-1] = '\0';
 fgets(tibuf,49,stream);
 tibuf[strlen(tibuf)-1] = '\0';
 file = nbuf;
 title = tibuf;
 char *p = strchr(nbuf,'.');
 if ( p != NULL )
	 *p = '\0';
 textitem = nbuf;
 
 if ( theDirectories.getDatabaseText() != FALSE ) {
    sprintf( sqlbuf, "texttype=\'%s\'", nbuf );
    try {
       if ( pSet->FindFirst(sqlbuf) )
          text =((CDHelpTxt *)pSet)->m_Text;
       else
          text = "";
	   do {
          if ( text == "" ) 
			  break;
          ((CDHelpTxt *)pSet)->MoveNext();
		  if ( ((CDHelpTxt *)pSet)->m_texttype==nbuf )
			  text += ((CDHelpTxt *)pSet)->m_Text;
	      } while ( text != "" && ((CDHelpTxt *)pSet)->m_texttype==nbuf 
			  && !((CDHelpTxt *)pSet)->IsEOF());
       }
    catch ( CDaoException *e ) {
       e->GetErrorMessage( errbuf, 500 );
       alert_box("Database Error",errbuf );
       }
 }
 return( !ferror(stream) );
}


AstHelperItem *AstHelperArray::operator[] (int i)
{
 AstHelperItem *pItem;
 if ( i >= items || i < 0 )
    return( NULL );
 pItem = &data[i];
 return( pItem );
}

int AstHelperArray::read( char *name, int dir )
{
 char buf[100], errbuf[500];
 int count, i;
 FILE *stream;

 strcpy( buf, set_path( name, dir ) );
 if ( ( stream = fopen( buf, "rt" ) ) == NULL ) {
    do_error( buf );
    items = 0;
    return( 0 );
    }
 if ( theDirectories.getDatabaseText() == TRUE ) {
     try {
	   set.m_strSort="texttype, iChunk";
       set.Open(); 
      }
    catch ( CDaoException *e ) {
       e->GetErrorMessage( errbuf, 500 );
       alert_box("Database Error",errbuf );
       }
    }
 fscanf( stream, "%d ", &count );
 data = new AstHelperItem[count+1];
 if ( data == NULL ) {
    items = 0;
    fclose( stream );
    do_mem_error(0);
    return( 0 );
    }
 items = count;
 for ( i = 0; i < count; i++ ) {
     if ( !data[i].read(stream, &set) )
	break;
     }
 if ( theDirectories.getDatabaseText() != FALSE ) {
    try {
       set.Close(); 
      }
    catch ( CDaoException *e ) {
       e->GetErrorMessage( errbuf, 500 );
       alert_box("Database Error",errbuf );
       }
    }
 if ( ferror( stream ) ) {
    delete data;
    fclose( stream );
    items = 0;
    do_error( buf );
    return( 0 );
    }
 fclose( stream );
 return( 1 );
}

void AstHelperItem::doGetText()
{
FILE *stream;
char path[250];
if (theDirectories.getDatabaseText()==FALSE)
   return;
strcpy(path,set_path( (char *)(LPCSTR) file, HELP_F ));
stream = fopen(path,"wb");
if ( stream != NULL ) {
   fwrite((void *)(LPCSTR) text,text.GetLength(),1,stream);
   fclose( stream );
   }
}

/* AstHelperFormDialog::~AstHelperFormDialog()
{
 if ( sel != NULL ) {
    delete sel;
    sel = NULL;
    }
}
        
AstHelperFormDialog::AstHelperFormDialog(zFrameWin *pPar)
			    : zMDIFormDialog(pPar, zResId("AST_HELP"))
{
  int i;
  AstHelperItem *item;

  HelpList.read("ASTHLPER.DAT", HELP_F);
  if ( !HelpList.count() )
     return;
  sel = new int[HelpList.count()+1];
  if ( sel == NULL ) {
     do_mem_error( 0 );
     return;
     }
  memset( sel, 0, (HelpList.count()+1) * 2 );
  pList = new zMultiSelListUnsorted(this, IDC_HFILES);
  for ( i = 0; item != NULL; i++ ) {
      item = HelpList[i];
      if ( item != NULL )
	 pList->add(item->getTitle());
      }
  pList->setNotifyDoubleClick(this,
	(NotifyProc)&AstHelperFormDialog::doubleClick);
  caret = 0;
  pList->caret(caret);
  pList->selection(0,HelpList.count()-1,0);
  deleteOnClose(1);
  show();
}


char **AstHelperFormDialog::makePrintList()
{
 int i, cnt, *sp;
 char **printList;

 if ( !pList->selCount() ) {
    alert_box(_NOFILESELEC/*"", "No Files Selected!"*//*);
    return( NULL );
    }
 printList = new char *[pList->selCount()+2];
 pList->selection(pList->selCount(), sel);
 for ( i = 0, cnt = pList->selCount(), sp = sel; i < cnt; i++, sp++ )
     printList[i] = (char *) HelpList[*sp]->getFile();
 printList[cnt] = NULL;
 return( printList  );
}


char **AstHelperFormDialog::makeTitleList()
{
 int i, cnt, *sp;
 char **titleList;

 if ( !pList->selCount() ) {
    alert_box(_NOFILESELEC/*"", "No Files Selected!"*//*);
    return( NULL );
    }
 titleList = new char *[pList->selCount()+2];
 pList->selection(pList->selCount(), sel);
 for ( i = 0, cnt = pList->selCount(), sp = sel; i < cnt; i++, sp++ )
     titleList[i] = (char *) HelpList[*sp]->getTitle();
 titleList[cnt] = NULL;
 return( titleList  );
}

int AstHelperFormDialog::view()
{
 int i;
 FILE_DB fd;
 
 i = pList->caret();
 strcpy( fd.name, (char *) HelpList[i]->getTitle() );
 strcpy( fd.comment, CResStr(_ASTROHELPFI)/*"ASTRO-Helper File"*//* );
 FileViewFrame *fvfp = new FileViewFrame((zFrameWin *)parent(), (char *) HelpList[i]->getFile(), HELP_F );
 fvfp->setFileDb( &fd );
 fvfp->show();
 fvfp->setFocus();
 return( 1 );
}

int AstHelperFormDialog::print()
{
 char **list, **tlist;
 PrintData data;

 data.getFromIni();
 PrintDataDlgf *pdf = new PrintDataDlgf(this, &data );
 if ( !pdf->completed() ) {
    delete pdf;
    return( 0 );
    }
 else {
    pdf->getData();
    delete pdf;
    }
 data.saveToIni();
 list = makePrintList();
 if (list == NULL )
    return( 0 );
 tlist = makeTitleList();
 if (tlist == NULL )
    return( 0 );
 FilePrinter *fp = new FilePrinter(list, HELP_F, tlist);
 fp->doPrint();
 while ( app->tasks()->busy() )
       zYield();
 delete fp;
 delete list;
 return( 1 );
}

int AstHelperFormDialog::convert()
{
 int n, cnt = pList->selCount()-1;
 char **list, **p;
 char outfile[100];
 astroFileToText *txt;
 ConvData *pcd;
 
 strcpy( outfile, "TEXT.TXT" );
 list = makePrintList();
 if (list == NULL )
    return( 0 );
 txt = new astroFileToText(HELP_F);
 if ( !txt->getSetup(this, &pcd ) ) {
    delete txt;
    return( 0 );
    }
 txt->setFiles( list, 0 );
 txt->doConvert(0);
 delete txt;
 return( 0 );
}


int AstHelperFormDialog::doubleClick(zEvent *e)
{
 if (pList->caret() < pList->count())
    view();
 return( 1 );
}

int AstHelperFormDialog::command( zCommandEvt *e )
{
 char file[150];

 switch( e->cmd() ) {
      case IDCANCEL:
	   shutdown();
	   break;
      case IDC_HVIEW:
	   view();
	   break;
      case IDC_HCONV:
	   convert();
	   break;
      case IDC_HPRINT:
	   print();
	   break;
      case IDC_HELP:
	   strcpy( file, set_path("ASTROW.HLP", HELP_F ) );
	   WinHelp(*app->rootWindow(), file, HELP_CONTEXT, HELPID_DLG_ASTHELP );
	   break;
      default :
	   return( 0 );
	   break;
      }
 return( 1 );
}
*/