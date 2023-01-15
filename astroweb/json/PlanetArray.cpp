#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <string>
#include <stdio.h>
#include "JsonWriter.h"
#include "DataBase.h"
#include "PlanetArray.h"
#include "Planet.h"

void PlanetArray::Serialize()
{
    JsonWriter wr = getWriter();
    fputc('[',wr.getStream());
    Planet pWriter(&wr);
    AS_INF *el = m_infoPtr;
    for (int i = 0; i < m_count; el++, i++) {
        pWriter.Set_Planet(*el,i);
        pWriter.Serialize();
        if (i < (m_count-1)) {
           fputs(",",wr.getStream());
        }
    }
    fputc(']',wr.getStream());
}
