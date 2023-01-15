#ifndef _FCOVRPRT_HPP_
#define _FCOVRPRT_HPP_

class CoverPagePrinter {
CoverPageData *data;
CFont *pfGlyph;
CBitmap *pBmUser;
public:
      CoverPagePrinter(CoverPageData *d );
      ~CoverPagePrinter();
      int printSetup(CDC *pdc, CPrintInfo *pi);
      int print(CDC *pdc, CPrintInfo *pi);
      };

#endif /*  _FCOVRPRT_HPP_  */
