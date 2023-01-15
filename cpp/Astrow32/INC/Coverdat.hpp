#ifndef _COVERDAT_HPP_
#define _COVERDAT_HPP_

#define USER_BMP 5
#define USER_FNT 4


class CoverPageData {
      int ok;
      int image;
      int font;
      CString file;
      CString title;
      CString name;
      CString comments;
      CString tempName;
      CString astName;
public:
      CoverPageData() { image = 0; }
      ~CoverPageData() {}
      int &getImage() { return image; }
      int &getFont() { return font; }
      void setImage(int i) {image = i;}
      void setFont( int f) { font = f; }
      CString &getFile() { return file; }
      CString &getTitle() {return title;}
      CString &getName()  {return name; }
      CString &getAstName()  {return astName; }
      CString &getComments() { return comments; }
      int save( char *name, int fld=CURRENT_F );
      int load( char *name, int fld=CURRENT_F );
      int create( XPFILE_DB *ptr );
      CString *toAstFile();
      int deleteTemp();
      int isOk() { return ok; }
      };
/*
class CoverPageDataDlgf : public FormDlgf {
CoverPageData *dlg_data;
zAstComboBoxStatic *pCbFnt;
zAstComboBoxStatic *pCb;
public:
      CoverPageDataDlgf(zWindow *pPar, CoverPageData *pC);
      ~CoverPageDataDlgf() { delete pCb; delete pCbFnt;  }
      int selchg( zEvent *e );
      };

class CoverPageEditor {
public:
      CoverPageEditor(zWindow *pPar, FILE_DB *ptr );
      ~CoverPageEditor() {}
      };

*/

#endif /* _COVERDAT_HPP_ */
