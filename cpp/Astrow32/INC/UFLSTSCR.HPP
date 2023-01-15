#ifndef _UFLSTSCR_HPP_
#define _UFLSTSCR_HPP_

class UserFileListPane : public FileListPane {
char fname[150];
public:
      UserFileListPane(zWindow *w, char *name);
      ~UserFileListPane();
      virtual int doCommand( zCommandEvt *e );
      void setupEditMenu();
      };

class UserFileListFrame : public FileListFrame {
public:
	UserFileListFrame(zFrameWin *pPar, char *name);
	~UserFileListFrame() { }
	virtual int kill( zEvent *e );
	virtual int MDIActivate(zActivateEvt *actEvt);
	};

#endif /* _UFLSTSCR_HPP_ */
