#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H
#include <string>

using namespace std;
using std::string;

class AbstractReader
{
    public:
        AbstractReader(const char *path) { m_path = path; }
        AbstractReader() {}
        virtual ~AbstractReader();
        virtual int read() = 0;
    protected:
        std::string &getPath() { return m_path; }
    private:
        std::string m_path;
};

#endif // ABSTRACTREADER_H
