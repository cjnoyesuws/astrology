#include "stdafx.h"
#include "astrow.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "coverdat.hpp"


//   Classes to contain cover page information and get info from user
//   Useage:
//
//   CoverPageDataDlgf *cd = new CoverPageDataDlgf( out, &cover );
//   if ( cd->completed() ) {
//      out->printf( "Image = %d\n", cover.getImage() );
//      out->printf( "Font = %d\n", cover.getFont() );
//      out->printf( "Image file = %s\n", cover.getFile() );
//      out->printf( "Title = %s\n", cover.getTitle() );
//      out->printf( "Name = %s\n", cover.getName() );
//      out->printf( "Comments = %s\n", cover.getComments() );
//      }
//   delete cd;
//
/*
char *images[] = { "Sun Planet Glyph", "Moon Planet Glyph",
    "Mercury Planet Glyph", "Venus Planet Glyph",
    "Mars Planet Glyph", "Jupiter Planet Glyph",
    "Saturn Planet Glyph", "Uranus Planet Glyph",
    "Neptune Planet Glyph", "Pluto Planet Glyph",
    "Aries Sign Glyph", "Taurus Sign Glyph",
    "Gemini Sign Glyph", "Cancer Sign Glyph", "Leo Sign Glyph",
    "Virgo Sign Glyph", "Libra Sign Glyph", "Scorpio Sign Glyph",
    "Sagittarius Sign Glyph", "Capricorn Sign Glyph" };

char *fonts[] = { "ASTRO Glyphs Font", "ASTRO Pi #1", "ASTRO Pi #2", "WingDings", "User Font", "User Graphic" };
*/
/*CoverPageDataDlgf::CoverPageDataDlgf(zWindow *pPar, CoverPageData *pC)
		     :  FormDlgf(pPar,zResId("COVER_DAT"), HELPID_DLG_CPAGE )
{

 dlg_data = pC;
 pCbFnt = new zAstComboBoxStatic(this, IDC_CPFONT );
// for ( int j = 0; j < 4; j++ )
//     pCbFnt->add( zString(fonts[j]) );
 pCbFnt->setNotifySelChange(this,(NotifyProc)&CoverPageDataDlgf::selchg);
 pCbFnt->addResStrings(SB_FONT);
 pCbFnt->selection(dlg_data->getFont() );
 pCb = new zAstComboBoxStatic(this, IDC_CPIMAGE );
 pCb->setNotifySelChange(this,(NotifyProc)&CoverPageDataDlgf::selchg);
// for ( int i = 0; i < 33; i++ )
//     pCb->add( zString(images[i]) );
 if ( dlg_data->getFont() == 3 )
    pCb->addResStrings( SB_IMAGE2 );
 else
    pCb->addResStrings( SB_IMAGE1 );
 pCb->selection(dlg_data->getImage() );
 new zStringEdit( this, IDC_CPFILE, &dlg_data->getFile(), FLD_NOTREQUIRED );
 new zStringEdit( this, IDC_CPTITLE, &dlg_data->getTitle() );
 new zStringEdit( this, IDC_CPNAME, &dlg_data->getName() );
 new zStringEdit( this, IDC_CPASTR, &dlg_data->getAstName() );
 if ( dlg_data->getComments()[dlg_data->getComments().length()-1] == '\n' )
    dlg_data->getComments()[dlg_data->getComments().length()-1] = '\0';
 new zEditBox( this, IDC_CPCOMMENTS, &dlg_data->getComments(), FLD_NOTREQUIRED );
 run();
}



int CoverPageDataDlgf::selchg( zEvent *e )
{
 switch( e->parm1() ) {
    case IDC_CPIMAGE :
	 if ( pCb->selection() != LB_ERR )
	    dlg_data->setImage( pCb->selection());
	 else
	    dlg_data->setImage( 0 );
	 break;
    case IDC_CPFONT :
	 int f = dlg_data->getFont();
	 if ( pCbFnt->selection() != LB_ERR )
	    dlg_data->setFont( pCbFnt->selection());
	 else
	    dlg_data->setFont( 0 );
	 if (f != dlg_data->getFont() ) {
	    pCb->reset();
	    if ( dlg_data->getFont() == 3 )
	       pCb->addResStrings( SB_IMAGE2 );
	    else
	       pCb->addResStrings( SB_IMAGE1 );
	    }
	 break;
    }

 return( 1 );
}


CoverPageEditor::CoverPageEditor( zWindow *pWnd, FILE_DB *ptr )
{
 CoverPageData *cpd;
 char buf[150], *dot;
 char name[20];
 zString astName;

 cpd = new CoverPageData();
 if ( cpd == NULL )
    return;
 strcpy( name, ptr->file_name );
 dot = strrchr( name, '.' );
 if ( dot == NULL )
    strcat( name, ".CPG" );
 else
    strcpy( dot, ".CPG" );
 strcpy( buf,  set_path( name, USER_F ) );   
 if ( access( buf, 6 ) == -1 )
    cpd->create(ptr);
 else {
    if ( !cpd->load(name) )
       cpd->create(ptr);
    }
 CoverPageDataDlgf *cd = new CoverPageDataDlgf( pWnd, cpd );
 if ( cd->completed() ) {
    ptr->has_cover = 1;
    cpd->save(name);
    }
 delete cd;
 delete cpd;
}
*/