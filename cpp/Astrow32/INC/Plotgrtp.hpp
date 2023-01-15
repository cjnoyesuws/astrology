#ifndef _PLOTGRTP_HPP_
#define _PLOTGRTP_HPP_

class GraphTextPlotter : public AstDrawBase {
      CFont *pArrow, *pText;
      GR_TEXT **text_array;
      int items;
public:
      GraphTextPlotter(CDC *d, GR_TEXT **ta, int n) : AstDrawBase(d)
		     { text_array = ta; items = n; }
      ~GraphTextPlotter() {}
      void setFonts(CFont *arw, CFont *text) { pArrow = arw; pText = text; }
      void plotItem( GR_TEXT *g );
      void plot();
      };

#endif /* _PLOTGRTP_HPP_ */

