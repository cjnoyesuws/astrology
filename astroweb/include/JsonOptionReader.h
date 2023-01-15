#ifndef JSONOPTIONREADER_H
#define JSONOPTIONREADER_H
#include "rapidjson/rapidjson.h"
#include "setup.hpp"
#include <string>
#include "AbstractReader.h"
#include <iostream>
#include <ostream>
using namespace std;
using std::string;
using rapidjson::SizeType;


class JsonOptionReader : public AbstractReader
{
    public:
        JsonOptionReader() {};
        JsonOptionReader(const char *path) {m_path = path;}
        virtual ~JsonOptionReader() {}
        JsonOptionReader(const JsonOptionReader& other);
        virtual int read();
        int handleKey(const char *key, unsigned int val);
        int handleKey(const char *key, const char *val);
        Options &getOptions() { return m_options; }
    protected:
    private:
        std::string m_path;
        Options m_options;

};

static JsonOptionReader static_reader;

struct OptionsHandler {
    bool Null() { return true; }
    bool Bool(bool b) { return true; }
    bool Int(int i) { static_reader.handleKey(currKey, i); return true; }
    bool Uint(unsigned u) { static_reader.handleKey(currKey, (int)u); return true; }
    bool Int64(int64_t i) { return true; }
    bool Uint64(uint64_t u) { return true; }
    bool Double(double d) {return true; }
    bool RawNumber(const char* str, SizeType length, bool copy) {
        return true;
    }
    bool String(const char* str, SizeType length, bool copy) {
        static_reader.handleKey(currKey,str);
        return true;
    }
    bool StartObject() { return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        strcpy(currKey,str);
        return true;
    }
    bool EndObject(SizeType memberCount) { return true; }
    bool StartArray() { return true; }
    bool EndArray(SizeType elementCount) { return true; }
    char currKey[100];
};


#endif // JSONOPTIONREADER_H
