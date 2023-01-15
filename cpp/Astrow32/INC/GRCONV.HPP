#ifndef _GRCONV___HPP_
#define _GRCONV___HPP_

class GraphicFileConverter {
GraphFileData data;
CString file;
CWnd *pPar;
char *ext, *types;
CAstrographView *view;
public:
      GraphicFileConverter(CWnd *pW) {pPar = pW;}
      ~GraphicFileConverter() {}
      int getSetup();
      int getFile();
      int doConvert();
      void setView( CAstrographView *v ) { view = v; }
      };

#endif /* _GRCONV___HPP_ */
