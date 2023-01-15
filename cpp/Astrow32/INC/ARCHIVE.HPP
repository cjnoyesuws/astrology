#ifndef _ARCHIVE__HPP_
#define  _ARCHIVE__HPP_

class ArchiveData {
CString path;
CString command;
int delFile, lha_zip, arc;
public:
      ArchiveData() {}
      ArchiveData(int _arc, int _zip=1);
      ~ArchiveData() {}
      int saveToIni();
      int getFromIni();
      CString &getPath() { return path; }
      CString &getCommand() { return command; }
      int &isDel() { return delFile; }
      int &isZip() { return lha_zip; }
      int &isArc() { return arc; }
      };

/*
class ArchiveDataDlgf : public FormDlgf {
ArchiveData *dlg_data;
public:
      ArchiveDataDlgf(zWindow *par, ArchiveData *d );
      ~ArchiveDataDlgf() {}
      int click(zNotifyEvt *e);
      void getData();
      };
*/
#endif /* _ARCHIVE__HPP_ */

