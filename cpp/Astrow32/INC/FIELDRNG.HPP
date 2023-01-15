#ifndef _FIELDRNG_HPP_
#define _FIELDRNG_HPP_

#include <limits.h>

class zNumFieldRng : public zIntEdit {
      int _hi, _low;
public:
      zNumFieldRng(zFrameWin *fw, int id, int *p, int hi=INT_MAX, int low = 0)
	     : zIntEdit(fw, id, p) {_hi = hi, _low = low; }
      ~zNumFieldRng() {}
      void SetLimits( int hi, int low=1) { _hi = hi, _low = low; }
      virtual int checkData();
      };

extern int centerDialog( zFrameWin *fw );

#endif /* _FIELDRNG_HPP_ */

