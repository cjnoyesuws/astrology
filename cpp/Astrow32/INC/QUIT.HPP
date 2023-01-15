#ifndef _QUIT_____HPP_
#define _QUIT_____HPP_

class QuitDlgf : public FormDlgf {
      int *_save;
      int ok;
public:
      QuitDlgf(zWindow *par, int *);
      ~QuitDlgf() {}
      virtual int command( zCommandEvt * );
      int is_OK() { return ok; }
      };

#endif /* _QUIT_____HPP_ */
