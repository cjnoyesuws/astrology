#ifndef _PRINTOPT_HPP_
#define _PRINTOPT_HPP_

class PrintData {
int cmt, cpg, cmtb4, hdp1, range, from, to, centerHead;
public:
      PrintData() { cmt = 0; cpg = 0; centerHead = 1;
	    hdp1 = 0; range = 0; cmtb4 = 0; from = 1; to = 1; }
      ~PrintData() {}
      int &getCmt() { return cmt; }
      int &getCpg() { return cpg; }
      int &getHeadP1() { return hdp1; }
      int &getFrom() { return from; }
      int &getTo() { return to; }
      int &getRange() { return range; }
      int &getCenterHead() { return centerHead; }
      int &getCmtBefore() { return cmtb4; }
      int saveToIni();
      int getFromIni();
      };

extern PrintData printData;
/*
class PrintDataDlgf : public FormDlgf {
PrintData *form_data;
public:
      PrintDataDlgf(zWindow *pPar, PrintData *pd);
      ~PrintDataDlgf() {}
      void getData();
      virtual int command(zCommandEvt *e);
      int click(zNotifyEvt *e);
      int enableRange(int en);
      };
*/
#endif /* _PRINTOPT_HPP_  */
                     
