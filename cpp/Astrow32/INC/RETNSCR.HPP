#ifndef _RETNSCR__HPP_
#define _RETNSCR__HPP_


class ReturnDataDlgf : public FormDlgf {
      RETURN_DATA *dlg_data;
      int target;
      zAstComboBoxStatic *pCbP;
      zAstComboBoxStatic *pCbB;
      zCheckBox *pCbip;
public:
      ReturnDataDlgf( zWindow *par, RETURN_DATA *pRd);
      ~ReturnDataDlgf() {}
      int selchg( zEvent *e );
      int progButtonClick( zEvent *e );
      void enableProgFlds( int en );
      void getData() { if ( target )
			  dlg_data->prog.progress_system += 100; }
      };


#endif /* _RETNSCR__HPP_  */
