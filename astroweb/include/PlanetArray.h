#ifndef PLANETARRAY_H
#define PLANETARRAY_H
#include "astro.h"
#include <JsonWriter.h>
#include <DataBase.h>


class PlanetArray : public DataBase
{
    public:
        PlanetArray() : DataBase() {m_infoPtr = 0L; m_count =0;}
        PlanetArray(JsonWriter *wr): DataBase(wr) {}
        PlanetArray(AS_INF *plans, int cnt, JsonWriter *writer) : DataBase(writer) {m_infoPtr = plans; m_count = cnt;}
        virtual ~PlanetArray() {}
        void Serialize();
        void Set_Planets(AS_INF *plans, int cnt) {m_infoPtr = plans; m_count = cnt;}
    protected:
        AS_INF *m_infoPtr;
        int m_count;
    private:
};

#endif // PLANETARRAY_H
