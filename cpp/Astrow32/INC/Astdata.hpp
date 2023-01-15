#ifndef _ASTDATA__HPP_
#define _ASTDATA__HPP_

#define NATAL_DATA 0
#define TWOWH_ONE  1
#define TWOWH_TWO  2

class AstData {
   int type;
   XPFILE_DB db;
   int count;
   GR_DATALST *data;
   int houses[12];
   CString name;
   CString date;
   CString time;
   CString trop_side;
   CString house_proc;
   CString longitude;
   CString latitude;
   CString location;
public:
   AstData(int wh, GraphData *pData);
   ~AstData() { if ( data != NULL ) delete data;  }
   int type() { return type; }
   XPFILE_DB *FileDB() { return db; }
   GR_DATALST *getData(int &cnt) { cnt = count; return data; }
   int *houses() { return houses; }
   CString &name() { return name; }
   CString &date() { return date; }
   CString &time() { return time; }
   CString &tropSide() { return trop_side; }
   CString &houseProc() { return house_proc; }
   CString &longitude() { return longitude; }
   CString &latitude() { return latitude; }
   CString &location() { return location; }
   };



#endif /* _ASTDATA__HPP_ */
