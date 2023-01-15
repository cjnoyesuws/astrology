#ifndef PROGRSCR_HPP
#define PROGRSCR_HPP

#include "astro.h"
#include "dataext.h"

class ProgressDlgf : public FormDlgf {
      int target;
      PROGR_DATA *dlg_data;
      zAstComboBoxStatic *pCb;
public:
      ProgressDlgf(PROGR_DATA *pPd, zWindow *par);
      ~ProgressDlgf() { delete pCb; }
      int selchg( zEvent *e );
      void getData() { if ( target )
			  dlg_data->progress_system += 100; }
      };


#endif /* PROGRSCR_HPP */
