#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <string>
#include "JsonWriter.h"
#include "DataBase.h"
#include "Aspect.h"
#include "HouseCusp.h"

 void HouseCusp::Serialize()
 {
    JsonWriter wr = getWriter();
    fprintf(wr.getStream(),"{\"house\":%d,\"minutesTotal\":%d,\"sign\":%d,\"degreesMinor\":%d,\"minutesMinor\":%d,\"graph_minutes\":%d,\"formatted\":\"%s\"}",m_house,
        m_inf.minutes_total,m_inf.sign,m_inf.degree_minor,m_inf.minutes_minor,m_inf.graph_minutes,m_inf.formatted);
}
