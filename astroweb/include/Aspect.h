#ifndef ASPECT_H
#define ASPECT_H
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <JsonWriter.h>
#include <DataBase.h>


class Aspect : public DataBase
{
    public:
        virtual ~Aspect() {}
        Aspect() : DataBase() {}
        Aspect(JsonWriter *wr) : DataBase(wr) {}
        Aspect(int planet, ASPEC &aspect, JsonWriter *wr) : DataBase(wr) { m_planet = planet; m_aspect = aspect; }
        int Get_planet() { return m_planet; }
        void Set_Planet(int val) { m_planet = val; }
        ASPEC Get_aspect() { return m_aspect; }
        void Set_Aspect(ASPEC &val) { m_aspect = val; }
        void Serialize();
    protected:
        int m_planet;
        ASPEC m_aspect;
    private:
};

#endif // ASPECT_H
