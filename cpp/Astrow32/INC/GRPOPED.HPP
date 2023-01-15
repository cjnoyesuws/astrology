#ifndef _GRPOPED__HPP_
#define _GRPOPED__HPP_

class GrPopView : public zPopupFrame {
zEditBox *edit;
zString buf;
char name[150];
public:
      GrPopView(zFrameWin *pPar, char *name);
      ~GrPopView() { delete edit; }
      load();
      };

#endif /* _GRPOPED__HPP_ */

