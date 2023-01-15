#ifndef _TDIREC___HPP_
#define _TDIREC___HPP_



class TbtDirectories {
zString main;
zString source;
zString text;
zString data;
zString edit;
zString help;
public:
      TbtDirectories() {}
      ~TbtDirectories() {}
      zString &getMain() {return main;}
      zString &getSource() {return source;}
      zString &getHelp() {return help;}
      zString &getData() {return data;}
      zString &getEdit() {return edit;}
      zString &getText() {return text;}
      void setMain(char *s) {main = s;}
      void setSource(char *s) {source = s;}
      void setHelp(char *s) {help = s;}
      void setData(char *s) {data = s;}
      void setEdit(char *s) {edit = s;}
      void settext(char *s) {text = s;}
      int saveToIni();
      int getFromIni();
      };

extern TbtDirectories theTbtDirectories;

class TbtDirectDlgf : public FormDlgf {
public:
      TbtDirectDlgf(zWindow *pPar, TbtDirectories *d);
      ~TbtDirectDlgf() { }
      };

#endif /*  _TDIREC___HPP_  */
