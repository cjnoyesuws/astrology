#ifndef _ABUTTON__HPP_
#define _ABUTTON__HPP_


class YNButton : public zButton {
     int val;
     zString yes;
     zString no;
public:
     YNButton(zDialogFrame *pDf, int id, char *pY, char *pN);
     ~YNButton() {}
     buttonVal() {return val;}
     buttonVal(int v);
     zString &buttonTxt() { if ( val )  return( yes );
                            else return( no );
			  }
     int notifyClick(zEvent *e);
     };


#endif /* _ABUTTON__HPP_ */
