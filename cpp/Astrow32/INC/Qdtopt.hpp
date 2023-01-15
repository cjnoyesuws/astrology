#ifndef _QDTOPT___HPP_
#define _QDTOPT__HPP_

class QdtData {
int runOnce;
int restrictTime;
int firstHours;
int firstMin;
int lastHours;
int lastMin;
int lastDay;
int lastMonth;
CString name;
CString event;
public:
      QdtData() { runOnce = 0; restrictTime = 0; firstHours = 0; firstMin = 0;
		 lastHours = 24; lastMin = 0; lastDay = 0, lastMonth = 0; }
      ~QdtData() {}
      int &getRunOnce() { return runOnce; }
      int &getRestrictTime() { return restrictTime; }
      int &getFirstHours() { return firstHours; }
      int &getFirstMin() { return firstMin; }
      int &getLastHours() { return lastHours; }
      int &getLastMin() { return lastMin; }
      int &getLastMonth() { return lastMonth; }
      int &getLastDay() { return lastDay; }
      CString &getName() { return name; }
      CString &getEvent() { return event; }
      int saveToIni();
      int getFromIni();
      };

/* class QdtDataDlgf : public FormDlgf {
int fam;
int lam;
QdtData *data;
public:
      QdtDataDlgf(zWindow *pPar, QdtData *data);
      getData();
      };
*/
#endif /* _QDTOPT___HPP_  */
