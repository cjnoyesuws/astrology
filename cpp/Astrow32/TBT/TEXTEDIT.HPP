#ifndef _TEXTEDIT_HPP_
#define _TEXTEDIT_HPP_

class TextEditor : public zMDIChildFrame {
zEditBox *edit;
zString buf;
char name[150];
char ename[150];
zMenu *pMenu;
int doCvt;
zClipboard *pClip;
public:
      TextEditor(zFrameWin *pPar, char *file = NULL, int dCvt=0 );
      ~TextEditor();
      int save();
      int backup();
      int load();
      int onUpdate( zEvent *e );
      int updateEditMenu();
      virtual int command(zCommandEvt *e);
      virtual int focus(zFocusEvt *ev);
      virtual int MDIActivate(zActivateEvt *ev);
      virtual int kill(zEvent *e);
      };

#endif /* _TEXTEDIT_HPP_ */
