#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <string>
#include "JsonWriter.h"
#include "DataBase.h"
#include "Aspect.h"
#include "AspectArray.h"

void AspectArray::Serialize() {
    JsonWriter &wr = getWriter();
    fputc('[',wr.getStream());
    Aspect aWriter(&wr);
    ASPEC *el = m_pAspects;
    for (int i = 0; i < m_count; el++, i++) {
        aWriter.Set_Aspect((ASPEC &)*el);
        aWriter.Set_Planet(m_planet);
        aWriter.Serialize();
        if (i < (m_count-1)) {
           fputs(",",wr.getStream());
        }
    }
    fputc(']',wr.getStream());
}
