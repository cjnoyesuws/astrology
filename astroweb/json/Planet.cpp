#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <string>
#include "JsonWriter.h"
#include "DataBase.h"
#include "Planet.h"
#include "AspectArray.h"

void Planet::Serialize()
{
    JsonWriter &wr = getWriter();
    fprintf(wr.getStream(),"{\"planet\":%d,\"minutesTotal\":%d,\"sign\":%d,",m_planet,m_inf.minutes_total,m_inf.sign);
    fprintf(wr.getStream(),"\"degreesMinor\":%d,\"minutesMinor\":%d,",m_inf.degree_minor,m_inf.minutes_minor);
    fprintf(wr.getStream(),"\"intercepted\":%d,\"retrograde\":%d,\"house\":%d,\"graph_minutes\":%d,\"formatted\":\"%s\",\"aspects\":",
       m_inf.intercepted,m_inf.retrograde,m_inf.house,m_inf.graph_minutes,m_inf.formatted );
    AspectArray ary(m_planet,(ASPEC *)m_inf.aspectr,m_inf.no_aspects, &wr);
    ary.Serialize();
    fputs("}",wr.getStream());
}
