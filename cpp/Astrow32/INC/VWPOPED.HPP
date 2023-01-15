#ifndef _VWPOPED__HPP_
#define _VWPOPED__HPP_

class EditTextBlock {
zString buf;
int nsr;
int stickRet[5];
int nTabs;
unsigned char tabs[15];
char tabbuf[60];
public:
     EditTextBlock() { nsr=0; nTabs = 0; tabbuf[0] = '\0';}
     ~EditTextBlock() {}
     void preProcess();
     void postProcess();
     zString &get() { return buf; }
     void set( char *, int l );
    };

class ViewPopEdit : public zMDIChildFrame {
zEditBox *edit;
EditTextBlock buf;
unsigned char flags;
VirtualTextBuffer *pVirt;
int para;
public:
      ViewPopEdit(zFrameWin *pPar, VirtualTextBuffer *pv, int pa );
      ~ViewPopEdit() { delete edit; }
      int save();
      int load();
      int kill( zEvent *e );
      virtual int command( zCommandEvt *e );
      virtual int MDIActivate(zActivateEvt *e);
      };

#endif /* _VWPOPED__HPP_ */

