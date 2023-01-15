#ifndef _OPTIONSREADER_H_
#define _OPTIONSREADER_H_
#include <string>
#include "AbstractReader.h"
#include "setup.hpp"

using namespace std;

class IniOptionsReader : public  AbstractReader {
protected:
    std::string m_path;
public:
	IniOptionsReader(std::string &str) { m_path = str; }
	virtual ~IniOptionsReader() {}
	virtual int read();
	Options & getOptions() {return m_options;}
	std::string &getPath() { return m_path; }
private:
    Options m_options;
};


#endif
