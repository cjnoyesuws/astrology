#ifndef DATABASE_H
#define DATABASE_H

#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "JsonWriter.h"

class DataBase
{
    public:
        DataBase();
        DataBase(JsonWriter *wr) {curWriter = wr;}
        virtual ~DataBase();
        JsonWriter &getWriter() { return *curWriter;}
    protected:
        void setWriter(JsonWriter *writer) {curWriter = writer;}
        JsonWriter *curWriter;
    private:
};

#endif // DATABASE_H
