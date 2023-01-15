#ifndef _ASFRAME__HPP_
#define _ASFRAME__HPP_

class AstroAppFrame : public zMDIAppFrame {
int fAllChecked;
public:
zMenu *pHelpMenu;
zMenu *pSystemMenu;
#ifdef NEW
zStatusLineEZ *pStatusLine;
#endif
int qdtMode;
zMDIChildFrame *pTextFrame;
zMDIChildFrame *pGraphFrame;
      zClipboard *pClip;
      AstroAppFrame(zSizer *pSiz);
      ~AstroAppFrame();
      int chOptCmd( zCommandEvt *e );
      int setupCompMenu( int *enbl );
      int getDataCmd( zCommandEvt *e );
      int utilCmd( zCommandEvt *e );
      int fileCmd( zCommandEvt *e );
      int doCompileCmd( zCommandEvt *e );
      int windCmd( zCommandEvt *e );
      int OptionCmd( zCommandEvt *e );
      int helpCmd( zCommandEvt *e );
      int mruCmd(zCommandEvt *e);
      zClipboard *getClipboard() { return pClip; }
      virtual int kill(zEvent *e);
      int processCommandLine( char *cmd );
      int doHelp(zEvent *e);
      int menuSelect(zEvent *e);
      zMenu *getSystemMenu() { return pSystemMenu; }
      int &getAllCheck() { return fAllChecked; }
      int &getQdtMode() { return qdtMode; }
      int CheckQdt( char *);
      void doQdtComp();
      void doQdtView(struct FILE_DB *out_fp, struct FILE_DB *gra_fp);
      };


#endif /* _ASFRAME__HPP_ */
