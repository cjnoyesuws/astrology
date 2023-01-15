#ifndef HOUSECUSPARRAY_H
#define HOUSECUSPARRAY_H
#include "astro.h"
#include <JsonWriter.h>
#include <DataBase.h>

class HouseCuspArray : public DataBase
{
    public:
       HouseCuspArray() : DataBase() {m_infoPtr = 0L; m_count =0;}
       HouseCuspArray(AS_INF *plans, int cnt, JsonWriter *wr) : DataBase(wr) {m_infoPtr = plans; m_count = cnt;}
       virtual ~HouseCuspArray() {}
       void Serialize();
       void Set_Houses(AS_INF *house) {m_infoPtr = house;}
    protected:
        AS_INF *m_infoPtr;
        int m_count;
    private:
};

#endif // HOUSECUSPARRAY_H
