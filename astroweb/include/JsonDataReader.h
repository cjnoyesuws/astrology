#ifndef JSONDATAREADER_H
#define JSONDATAREADER_H

#include "cJSON.h"

class JsonDataReader : AbstractReader
{
    public:
        JsonDataReader();
        virtual ~JsonDataReader();
        JsonDataReader(const char *path) { m_path = path; }
        virtual int read();
    protected:
        std::string m_path;
        FILE *stream;
        char section[35];
        cJSON *object;
        int parseInt(short &num, cJSON *obj);
        int readBirth(BIRTH_DB &rec, cJSON *object);
        int parseDate(DATES &date, cJSON *obj );
        int parseTime(TIM &time, cJSON *obj );
        int parseLongLat(DEG_MIN &degs, cJSON *obj );
        virtual int readRect(RECT_DATA &rect, cJSON *child );
        virtual int readTrans(TRANS_DATA &trans, cJSON *child );
        int virtual readProg(PROGR_DATA &prog, cJSON *child);
        int virtual readReloc(LOC_DB &reloc, cJSON *child);
        std::string &getPath() { return m_path; }
    private:
};

#endif
