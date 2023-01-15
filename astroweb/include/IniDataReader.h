#ifndef _DATAREADER_H_
#define _DATAREADER_H_
#include "AbstractReader.h"

#define END_RD      0
#define SECTION_RD  1
#define VARIABLE_RD 2
#define ERROR_RD    3
#define COMMENT_RD  4
#define END_SECTION_RD 5;

using namespace std;

class IniDataReader : public AbstractReader {
protected:
	std::string m_path;
	FILE *stream;
	char section[35];
	char key[25];
	char value[100];
	int parseInt(short &num) { num = atoi(value); return 1; };
	int readBirth(BIRTH_DB &rec);
	int parseDate(DATES &date);
	int parseTime(TIM &time);
	int parseLongLat(DEG_MIN &degs, int lat=1);
	virtual int readRect(RECT_DATA &rect);
	virtual int readTrans(TRANS_DATA &trans);
	int virtual readProg(PROGR_DATA &prog);
	int virtual readReloc(LOC_DB &reloc);
	int readLine();
	std::string &getPath() { return m_path; }
public:
	IniDataReader(const char *path) { m_path = path; }
	virtual ~IniDataReader() {}
	virtual int read();
};




#endif
