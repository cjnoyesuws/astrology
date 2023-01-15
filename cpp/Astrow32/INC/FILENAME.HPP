#ifndef _FILENAME_HPP_
#define _FILENAME_HPP_


class FileNameDlgf : public FormDlgf {
      zStaticText *pST;
      zString _name, _comment;
      FILE_DB *pDb;
public:
      FileNameDlgf(zWindow *par, FILE_DB *db, 
                char *type, char *res = "FILE_NAME" );
      ~FileNameDlgf() { }
      void toFileDB();
      };


class FileEditDlgf : public FileNameDlgf {
      zStaticText *pST2;
public:
      FileEditDlgf(zWindow *par, FILE_DB *db, char *type, char *file);
      ~FileEditDlgf() { }
      };

class FileListArray;

class FileKillDlgf : public FormDlgf {
      zStaticText *pSTname;
      zStaticText *pSTcomment;
      zStaticText *pSTfname;
      zStaticText *pSTtype;
      zCheckBox   *pCBask;
      FILE_DB **ppData;
      FileListArray *pFla;
      int nItems;
      int _ask;
public:
      FileKillDlgf(zWindow *par, FILE_DB **ppD, int nIt, FileListArray *pFl);
      ~FileKillDlgf() { }
      int askChecked( zEvent *e );
      int doOkButton( zEvent *e );
      int doNoButton( zEvent *e );
      void setText(FILE_DB *pF );
      };

#endif /* _FILENAME_HPP_ */
