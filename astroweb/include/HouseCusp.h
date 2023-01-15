#ifndef HOUSECUSP_H
#define HOUSECUSP_H
#include "astro.h"
#include <cstring>
#include <JsonWriter.h>
#include <DataBase.h>


class HouseCusp : public DataBase
{
    public:
        HouseCusp() : DataBase() { m_house=0; memset(&m_inf,0,sizeof(AS_INF)); }
        HouseCusp(JsonWriter *wr) : DataBase(wr) {}
        virtual ~HouseCusp() {}
        void Set_House(AS_INF &inf, int house) {m_inf=inf; m_house = house;}
        void Serialize();
    protected:
        AS_INF m_inf;
        int m_house;
    private:
};

#endif // HOUSECUSP_H
