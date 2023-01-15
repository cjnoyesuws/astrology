#include "stdafx.h"
#include "inifile.hpp"
#include "grafont.hpp"


int GraphicFonts::getFromIni( char *sec )
{
 CWinApp *app = AfxGetApp();

 glyphfont = app->GetProfileString( sec, "GlyphFont", "AstGlyphs" );
 datafont = app->GetProfileString( sec, "DegFont", "Arial" );
 return( 1 );
}

int GraphicFonts::saveToIni( char *sec )
{
CWinApp *app = AfxGetApp();
 
app->WriteProfileString( sec, "GlyphFont", glyphfont );
app->WriteProfileString( sec, "DegFont", datafont );
return(1);
}
/*
GraphicFontDlgf::GraphicFontDlgf(zWindow *par, GraphicFonts *f) :
		FormDlgf(par,zResId("GRA_FONT"), HELPID_DLG_GRAFONT )
{
 data = f;
 run();
}

int GraphicFontDlgf::command(zCommandEvt *e)
{
 switch( e->cmd() ) {
      case IDC_GLYPHFONT:
	   {
	   zFontSpec *pfs = new zFontSpec(data->getGlyphFont(),zDimension(0,14),FW_NORMAL,
	      ffDontCare, VariablePitch, 0, 0, 0, SymbolCharSet,
	      CharOutPrec, StrokeClipPrec, DefaultQual );
	   zFontSelForm *fsf = new zFontSelForm(this, zColor(), pfs );
	   if ( fsf->completed() )
	      data->getGlyphFont() = fsf->fontSpec()->faceName();
	   delete pfs;
	   delete fsf;
	   return( 1 );
	   }
	   break;
      case IDC_DEGFONT:
	   {
	   zFontSpec *pfsx = new zFontSpec(data->getDataFont(),zDimension(0,14),FW_NORMAL,
	      ffDontCare, VariablePitch, 0, 0, 0, SymbolCharSet,
	      CharOutPrec, StrokeClipPrec, DefaultQual );
	   zFontSelForm *fsd = new zFontSelForm(this, zColor(), pfsx );
	   if ( fsd->completed() )
	      data->getDataFont() = fsd->fontSpec()->faceName();
	   delete fsd;
	   delete pfsx;
	   return( 1 );
	   }
	   break;
      default :
	   return( 0 );
	   break;
      }
 return( 0 );
}
*/