#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "resource.h"
#include "acombbox.hpp"
#include "fieldrng.hpp"
#include "asfrmdlg.hpp"
#include "symbol.hpp"
#include "textbloc.hpp"
#include "reprtedt.hpp"
#include "rtextedt.hpp"
#include "atextedt.hpp"
#include "helpid.h"

AspTextEditorDlg::AspTextEditorDlg(zFrameWin *pPar, char *rfile, char *sym, int type, int dlg ) :
     RegTextEditorDlg(pPar, rfile, sym, type, dlg )
{
 pCombo3 = new zComboBoxStatic( this, IDC_COMBO3 );
 pCombo3->setNotifySelChange(this, (NotifyProc)&AspTextEditorDlg::selchg);
 pCombo->setNotifySelChange(this, (NotifyProc)&AspTextEditorDlg::selchg);
 pCombo2->setNotifySelChange(this, (NotifyProc)&AspTextEditorDlg::selchg);
 updateCombos();
 setId(HELPID_DLG_ASPECT);
 run();
}

int AspTextEditorDlg::selchg( zEvent *e )
{
 int sel;
 zString s;

 if ( e->parm1() == IDC_COMBO1 ) {
    sel = pCombo->selection();
    if ( sel < 0 ) {
       pCombo->selection(0);
       sel = 0;
       }
    pCombo->getItem(s,sel);
    symbol = toSymName((char *)s);
    }
 else if ( e->parm1() == IDC_COMBO2 ) {
    sel = pCombo2->selection();
    if ( sel < 0 ) {
       pCombo2->selection(0);
       sel = 0;
       }
    pCombo2->getItem(s,sel);
    symbol2 = toSymName((char *)s);
    }
 else {
    sel = pCombo3->selection();
    if ( sel < 0 ) {
       pCombo3->selection(0);
       sel = 0;
       }
    pCombo3->getItem(s,sel);
    symbol3 = toSymName((char *)s);
    }
 pTextBlock = NULL;
 editText = "";
 setControlsToDefault();
 return( 1 );
}




int AspTextEditorDlg::doFindText()
{
 storeData();
 pTextBlock = pTextAry->Find( (char *)symbol, (char *)symbol2,
      (char *)symbol3 );
 if ( pTextBlock == NULL ) {
    editText = "";
    }
 else {
    editText = pTextBlock->text();
    }
 return(1);
}


int AspTextEditorDlg::doReplaceText()
{
 if ( pTextBlock == NULL )
    pTextBlock = pTextAry->Find( (char *)symbol, (char *)symbol2, (char *)symbol3 );
 if ( pTextBlock == NULL ) {
    pTextBlock = new CTextBlock();
    pTextBlock->SetID( (char *)symbol, (char *)symbol2, (char *)symbol3);
    pTextAry->Add( pTextBlock );
    }
 if ( editText != pTextBlock->text() ) {
    pTextAry->isDirty() = 1;
    pTextBlock->put(editText);
    }
 CSymbol *pSym = pSymAry->Find((char *)symbol, 1);
 if ( pSym != NULL )
    pSym->referenced()=1;
 pSym = pSymAry->Find((char *)symbol2, 2);
 if ( pSym != NULL )
    pSym->referenced()=1;
 pSym = pSymAry->Find((char *)symbol3, 3);
 if ( pSym != NULL )
    pSym->referenced()=1;
 return(1);
}


int AspTextEditorDlg::updateCombos()
{
 pSymAry->toCombo(pCombo, 1, refOnly );
 pSymAry->toCombo(pCombo2, 2, refOnly );
 pSymAry->toCombo(pCombo3, 3, refOnly );
 return( 1 );
}
