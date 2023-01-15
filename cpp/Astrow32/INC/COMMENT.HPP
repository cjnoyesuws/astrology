#ifndef _COMMENT__HPP_
#define _COMMENT__HPP_

class CommentEditor : public zMDIChildFrame {
FILE_DB *pDb;
zEditBox *edit;
zString buf;
char name[150];
zMenu *pMenu;
public:
      CommentEditor(zFrameWin *pPar, FILE_DB *db);
      ~CommentEditor() { delete edit; }
      save();
      load();
      virtual int command(zCommandEvt *e);
      virtual int focus(zFocusEvt *ev);
      virtual int MDIActivate(zActivateEvt *ev);
      virtual int kill(zEvent *e);
      };

#endif /* _COMMENT__HPP_ */
