#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <stdio.h>
#include <string>
#include "JsonWriter.h"
#include "DataBase.h"
#include "Aspect.h"

void Aspect::Serialize()
{
    JsonWriter wr = getWriter();
    fprintf(wr.getStream(),"{\"planet\":%d,\"other\":%d,\"aspect\":%d,\"orb\":%d}",m_planet,m_aspect.planet,m_aspect.aspect,m_aspect.orb);
}
