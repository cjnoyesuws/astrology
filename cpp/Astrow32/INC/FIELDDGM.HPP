#ifndef _FIELDDGM_HPP_
#define _FIELDDGM_HPP_

class zDegMinField : public zIntEdit {
int *dst;
public:
      zDegMinField(zFrameWin *fw, int id, int *p, DWORD msk =0);
      ~zDegMinField() {}
      virtual int checkData();
      virtual int storeData();
      virtual int setToDefault();
      };

#endif /* _FIELDDGM_HPP_ */

