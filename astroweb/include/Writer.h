#ifndef WRITER_H
#define WRITER_H
#include "rapidjson/rapidjson.h"
#include "rapidjson/fwd.h"
#include "rapidjson/prettywriter.h"
#include "Writer.h"
#include <cstdio>
#include <string>

using namespace rapidjson;
using namespace std;

class FileWriter : public PrettyWriter
{
    public:
        DataWriter(const char *file) {filename = file; }
        virtual ~DataWriter();

    protected:
        bool open();
    private:
        const char *filename;
        char *filenameWithExt;
};




#endif // WRITER_H
