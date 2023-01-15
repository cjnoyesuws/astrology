#ifndef ASPECTARRAY_H
#define ASPECTARRAY_H
#include "astro.h"

class AspectArray : public DataBase
{
    public:
        AspectArray() : DataBase() {}
        AspectArray(int planet, ASPEC *aspects, int count, JsonWriter *wr) : DataBase(wr) {m_planet = planet; m_pAspects = aspects; m_count = count;}
        virtual ~AspectArray() {}
        void Serialize();
    protected:
        ASPEC *m_pAspects;
        int m_planet;
        int m_count;
    private:
};

#endif // ASPECTARRAY_H
