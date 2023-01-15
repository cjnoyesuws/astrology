#ifndef _TFILELST_HPP_
#define _TFILELST_HPP_


class FileListDlgf : public FormDlgf {
zWindow *pw;
zListBox *box;
zString file;
int type;
public:
      FileListDlgf(zWindow *pPar, int t);
      ~FileListDlgf() {}
      CAsFile *toFile();
      };


#endif /* _TFILELST_HPP_  */

