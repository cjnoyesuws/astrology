#ifndef TEXTDEF
#define TEXTDEF
#endif
#ifndef TCOMPILER
#if (!defined(CHARCONS_SEEN))
  #include "charcons.h"
#endif

#define PLANET_FILE      PLANET_FILE_name
#define HOUSE_FILE       HOUSE_FILE_name
#define ASPECT_FILE      ASPECT_FILE_name
#define SUMMARY_FILE     SUMMARY_FILE_name
#define COMPAT_HOUSES    COMPAT_HOUSES_name
#define COMPAT_SUMMARY   COMPAT_SUMMARY_name
#define TRANSITS_HOUSES  TRANSITS_HOUSES_name
#define TRANSITS_ASPECTS TRANSITS_ASPECTS_name
#define PROGRESS_ASPECTS PROGRESS_ASPECTS_name
#define SIGN_HOUSE_FILE  SIGN_HOUSE_FILE_name
#define COMPAT_ASPECTS   COMPAT_ASPECTS_name
#define MIDPOINT_SIGN    MIDPOINT_SIGN_name
#define ARABIC_SIGN      ARABIC_SIGN_name
#define ARABIC_HOUSE     ARABIC_HOUSE_name
#define ARABIC_ASPECTS   ARABIC_ASPECTS_name
#define FIXEDST_SIGN     FIXEDST_SIGN_name
#define FIXEDST_HOUSE    FIXEDST_HOUSE_name
#define FIXEDST_ASPECTS  FIXEDST_ASPECTS_name
#define SOLAR_PLANET      SOLAR_PLANET_name
#define SOLAR_HOUSE      SOLAR_HOUSE_name
#define SOLAR_ASPECT   SOLAR_ASPECT_name
#define CM_PLANET_FILE      CM_PLANET_FILE_name
#define CM_HOUSE_FILE       CM_HOUSE_FILE_name
#define CM_ASPECT_FILE      CM_ASPECT_FILE_name
#define CM_TRANSITS_HOUSES  CM_TRANSITS_HOUSES_name
#define CM_TRANSITS_ASPECTS CM_TRANSITS_ASPECTS_name

#ifdef TEXTMANAGER
#include "TextManager.h"
#define get_transfer_text(c,r,f,s) (TextManager::GetManager()->GetRegText((f),(r),(c),(s)))
#define get_transfer_text_asp(c,r,a,f,s) (TextManager::GetManager()->GetAspText((f),(c),(r),(a),(s)))
#define open_files(f) (TextManager::GetManager()->OpenText(f))
#define open_asp_files(f) (TextManager::GetManager()->OpenAspectsText(f))
#define close_files(n) (TextManager::GetManager()->CloseText(n))
#define close_files_asp(n) (TextManager::GetManager()->CloseAspText(n))
#define tb_open_file(p) (TextManager::GetManager()->OpenReportText(p))
#define tb_close_table(n) (TextManager::GetManager()->CloseReport(n))
#define tb_get_text(r,n,i) (TextManager::GetManager()->GetReportText((r),(n),(i)).c_str()
#define tb_write_text(r,n,i,s) (TextManager::GetManager()->GetReportText((r),(n),(i), (s)))
#else
#include "tableptr.h"
#endif


#endif
