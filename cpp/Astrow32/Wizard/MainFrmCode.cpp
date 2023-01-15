// code to implement wizard in astrow
#include "chartwizard.h"


void doWiz()
{
 XPFILE_DB fileinfo;
 DATA_PACKET_EXT chart_data = {0,&birth_rectd,&transit_data,&progress_data,&return_data, 
  &solar_data, &reloc_data,&comp_rectd,&harmonic,NULL,&birth_rec, &comp_rec, &trans_rec,
  &birth_rectd, &comp_rectd, &trans_rectd,&reloc_data, &Personal };

 memset(&fileinfo, 0, sizeof(XPFILE_DB));
 CChartWizard *pWizard = new CChartWizard("Setup Chart Data", this, 0 );
 pWizard->SetChartDataPtrs(chart_data);
 pWizard->SetFileDb(&fileinfo);
 pWizard->DefaultRectMethod()=0;
 pWizard->InitializeSheet();
 if ( pWizard->DoModal() == ID_WIZ_FINISH ) {
      CChartCompiler *pCompiler;
	  switch ( pWizard->GetFileType() ) {
		  case NATAL_FILE:
		  case RELOCATION_FILE:
              pCompiler = (CChartCompiler *)new NatalChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case COMPATIBILITY_FILE:
		  case COMPOSITE_FILE:
			  pCompiler = (CChartCompiler *)new CompChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case TRANSITS_FILE:
			  pCompiler = (CChartCompiler *)new TransChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case PROGRESSED_FILE:
			  pCompiler = (CChartCompiler *)new ProgChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case SOLAR_RETURN_FILE:
			  pCompiler = (CChartCompiler *)new ReturnChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case SOLARARC_FILE:
			  pCompiler = (CChartCompiler *)new SolarChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case HARMONIC_FILE:
			  pCompiler = (CChartCompiler *)new HarmonicChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case COMPOTRAN_FILE:
			  pCompiler = (CChartCompiler *)new ComTrnChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case FIXED_FILE:
		  case ARABIC_FILE:
		  case HELIO_FILE:
		  case PROBLEM_FILE:
			  pCompiler = (CChartCompiler *)new OtherChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  default: 
			  break;
	  }
      pCompiler->SetWizFileInfo(fileinfo);
	  if ( pCompiler->runChart() ) {
		  XPFILE_DB *pFile;
		  char buf[250];

		  pFile = pCompiler->getOutFp();
		  if ( pFile != NULL ) {
		    strpy( buf set_path(pFile->filename,pFile->folder));
			AfxOpenDocumentFile(buf);
		  }
		  pFile = pComiler->getGraphFp();
          if ( pFile != NULL ) {
		    strpy( buf set_path(pFile->filename,pFile->folder));
			AfxOpenDocumentFile(buf);
		  }
		  pFile = pCompiler->getGridFp();
		  if ( pFile != NULL ) {
		    strpy( buf set_path(pFile->filename,pFile->folder));
			AfxOpenDocumentFile(buf);
		  }
	  }
	  delete pCompiler;
    }
 delete pWizard;
}