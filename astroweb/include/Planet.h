#ifndef PLANET_H
#define PLANET_H
#include "astro.h"
#include <JsonWriter.h>
#include <DataBase.h>


class Planet : public DataBase
{
    public:
        Planet(): DataBase() {}
        Planet(JsonWriter *wr) : DataBase(wr) {}
        Planet(AS_INF &inf, int planet, JsonWriter *wr) : DataBase(wr)  { m_planet = planet; m_inf = inf;}
        virtual ~Planet() {}
        void Set_Planet(AS_INF &p, int planet) {m_inf = p; m_planet = planet;}
        void Serialize();
    protected:
        AS_INF m_inf;
        int m_planet;
    private:
};

#endif // PLANET_H
