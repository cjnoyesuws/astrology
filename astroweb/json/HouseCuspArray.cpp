#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <string>
#include "JsonWriter.h"
#include "DataBase.h"
#include "Planet.h"
#include "HouseCusp.h"
#include "HouseCuspArray.h"

void HouseCuspArray::Serialize()
{
    JsonWriter &wr=getWriter();
    fputc('[',wr.getStream());
    HouseCusp pWriter(&wr);
    AS_INF *el = m_infoPtr;
    for (int i = 0; i < 12; el++, i++) {
        pWriter.Set_House(*el, i);
        pWriter.Serialize();
         if (i < 11) {
           fputs(",",wr.getStream());
        }
    }
    fputc(']',wr.getStream());
}
