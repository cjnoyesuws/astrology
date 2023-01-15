#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include <direct.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "astromn.h"
#include "utlduad.h"
#include "msg.hpp"
#include "inifile.hpp"
#include "setup.hpp"
#include "compile.hpp"
#include "astromn.h"
#include "asfrmdlg.hpp"
#include "direc.hpp"
#include "filelst.hpp"
#include "asframe.hpp"
#include "setup.hpp"
#include "title.hpp"
#include "errors.fns"
#include "resstr.hpp"

int read_birth_data(char *file);

Directories theDirectories;
FileListArray AstFileList;


PROGR_DATA progress_data;
TRANS_DATA transit_data;
RECT_DATA birth_rectd, comp_rectd, trans_rectd;
RETURN_DATA return_data;
BIRTH_DB birth_rec, comp_rec, trans_rec;
LOC_DB reloc_data;
int birth_ok, birth_rect_ok = 1, comp_ok, comp_rect_ok = 1,
    trans_ok, trans_data_ok, prog_ok;
AS_INF near birth_inf[18], near alt_inf[18];
AS_INF_EXT near birth_ext[18], near alt_ext[18];
short near house_cusps[13], near alt_cusps[13];
DATA_PACKET birth_dp = { NATAL_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
comp_dp = { COMPA_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
trans_dp = { TRANS_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, NULL },
progr_dp = { PROGR_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
return_dp = { RETUR_CH, &birth_rectd, NULL, &progress_data, &return_data, NULL, &reloc_data, NULL },
reloc_dp = { RELOC_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
compos_dp = { COMPO_CH|RELOC_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
fixed_dp = { FIXED_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
arabp_dp = { ARABP_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
comptr_dp = { COMPO_CH|TRANS_CH|RELOC_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, &comp_rectd };


void zApp::main()
{
 char buf[150];
 int qdt;
 
#ifdef _DEBUG
 debugOn(1);
#endif               
#ifdef NEW
#ifdef PRO
// initIntPack();
#endif
#endif
 _getdcwd(_getdrive(),buf,150);
 if ( buf[strlen(buf)-1] != '\\' )
    strcat( buf, "\\" );
 strcat(buf, ini_file );
 strcpy(ini_file, buf );   
 theDirectories.getFromIni();
 setup_dat.readFromIni();
 birth_rectd.birth_time_known = 1;
 comp_rectd.birth_time_known = 1;
 trans_rectd.birth_time_known = 1;
 zSystemInfo *si = new zSystemInfo();
  AstroAppFrame *apf = new AstroAppFrame(new
    zSizer(0, 0, si->pixWidth(), si->pixHeight()));
 delete si;
 qdt = apf->CheckQdt( cmdLine());
 if ( qdt == -1 ) {                 
    delete apf;          
    return;
    }
 if ( !qdt ) {
   read_birth_data( set_path( "QDTRADAT.HIS", USER_F ) );
   read_birth_data( set_path( "QDTRADAT.DEF", USER_F ) );
   }
 else {
   read_birth_data( set_path( "ASTRODAT.HIS", USER_F ) );
   read_birth_data( set_path( "ASTRODAT.DEF", USER_F ) );
   }
 TitleFrame *tf = new TitleFrame(apf);
 tf->show();
 tf->setFocus();
 apf->processCommandLine( cmdLine() );
 if ( !qdt ) {
    alert_box(_MAN_DAILY/*"","Now Your Daily Chart Will be Compiled!"*/ );
    apf->doQdtComp();
    }
 apf->show(SW_SHOWMAXIMIZED);
 go();
 delete apf;
}   
