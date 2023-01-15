#ifndef _TBTFRAME_HPP_
#define _TBTFRAME_HPP_

class TbtAppFrame : public zMDIAppFrame {
public:
zClipboard *pClip;
zMenu *pHelpMenu;
zMenu *pSystemMenu;
      TbtAppFrame(zSizer *pSiz);
      ~TbtAppFrame();
      int optionCmd( zCommandEvt *e );
      int utilitiesCmd( zCommandEvt *e );
      int fileCmd( zCommandEvt *e );
      int compile( zCommandEvt *e );
      int convert( zCommandEvt *e );
      int windCmd( zCommandEvt *e );
      int helpCmd( zCommandEvt *e );
      zClipboard *getClipboard() { return pClip; }
      virtual int kill(zEvent *e);
      int processCommandLine( char *cmd );
      int doHelp(zEvent *e);
      int menuSelect(zEvent *e);
      zMenu *getSystemMenu() { return pSystemMenu; }
      void checkConvertSettings();
      };


#endif /* _TBTFRAME_HPP_ */
