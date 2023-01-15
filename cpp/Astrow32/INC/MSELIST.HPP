#ifndef _MSELIST_HPP_
#define _MSELIST_HPP_

/* Unsorted Multi Selection box */

class zMultiSelListUnsorted : public zListBoxUnsorted {
public:
      zMultiSelListUnsorted(zFrameWin *df, int i) :
	      zListBoxUnsorted(df,i) {}
      ~zMultiSelListUnsorted() {}
      void caret(int i);
      int caret();
      int selection(int f, int l, BOOL s);
      int selCount();
      int selection(int n, int *l);
      };

#endif /* _MSELIST_HPP_ */
