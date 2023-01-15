#ifndef _FLISTARC_HPP_
#define  _FLISTARC_HPP_

class FileListArchiver {
char name[250];
FileListArray *pFla;
int type;
ArchiveData *data;
public:
      FileListArchiver(FileListArray *pf, int tp, int arc);
      ~FileListArchiver();
      char *makeArchiveList(int fld);
      int archive(CWnd *pPar, int fld);
      int deArchive(CWnd *pPar, int fld);
      int setup(CWnd *pPar);
      };

#endif /* _FLISTARC_HPP_ */
