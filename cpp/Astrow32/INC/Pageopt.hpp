#ifndef _PAGEOPT__HPP_
#define _PAGEOPT__HPP_

class PageData {
CRect pageSize;
CRect margins;
public:
      PageData() {}
      ~PageData() {}
      CRect &getPageSize() { return pageSize; }
      CRect &getMargins() { return margins; }
      void setPageSize(CRect &p) { pageSize =p; }
      void setMargins(CRect &m) { margins = m; };
      int saveToIni( char *sect );
      int getFromIni( char *sect );
      };

/*class PageDataDlgf : public FormDlgf {
zString left, width, bottom, right, high, top;
PageData *form_data;
public:
      PageDataDlgf(zWindow *pPar, PageData *pd);
	  ~PageDataDlgf() {}
      void getData();
      };

*/
#endif /* _PAGEOPT__HPP_ */
