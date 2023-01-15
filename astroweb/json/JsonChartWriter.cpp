#include <stdio.h>
#include <string.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <cstdio>
#include <JsonWriter.h>
#include <DataBase.h>
#include <Planet.h>
#include <PlanetArray.h>
#include <HouseCusp.h>
#include <HouseCuspArray.h>
#include <Aspect.h>
#include <AspectArray.h>
#include "BaseChartWriter.h"
#include "JsonChartWriter.h"
#include "useri.h"

JsonChartWriter::JsonChartWriter(FILE *_stream) : BaseChartWriter(_stream)
{
    buffer = new char[4096];
}

JsonChartWriter::~JsonChartWriter()
{
    delete buffer;
}


int JsonChartWriter::writeNatal(int maxpt)
{
   JsonWriter *pWriter = new JsonWriter(stream);
   fprintf(stream, "{\"charts\":[{\"info\":\{\"name\":\"%s\",\"country\":\"%s\",\"state\":\"%s\",\"location\":\"%s\",",birth_rec.name,birth_rec.country,birth_rec.state,birth_rec.location);
   fprintf(stream,"\"birth_date\":\"%02d/%02d/%04d\",\"birth_time\":\"%02d:%02d:%02d\",\"longitude\":\"%3d:%02d %c\",\"latitude\":\"%3d:%02d %c\"},\"planets\":",
        birth_rec.birth_data.birth_date.month,birth_rec.birth_data.birth_date.day,birth_rec.birth_data.birth_date.year,birth_rec.birth_data.birth_time.hours,
        birth_rec.birth_data.birth_time.minutes,birth_rec.birth_data.birth_time.seconds,birth_rec.birth_data.longitude.degrees,birth_rec.birth_data.longitude.minutes,
        birth_rec.birth_data.longitude.dir,birth_rec.birth_data.latitude.degrees,birth_rec.birth_data.latitude.minutes,birth_rec.birth_data.latitude.dir);
   PlanetArray ary((AS_INF *)&birth_inf, maxpt, pWriter);
   ary.Serialize();
   fprintf(stream,",\"houses\":");
   HouseCuspArray hary((AS_INF *)&house_inf,12, pWriter);
   hary.Serialize();
   fprintf(stream,"}],\"signs\":[");
   for (int i = 0; i < 12; i++) {
      if (i < 11) {
         fprintf(stream, "{%d,%d},", signs[i].graph_minutes, signs[i].minutes);
      }
      else {
         fprintf(stream, "{%d,%d}", signs[i].graph_minutes, signs[i].minutes);
      }
   }
   fprintf(stream,"]}\n");
   delete pWriter;
}


int JsonChartWriter::writeCompat(int maxp)
{
}

int JsonChartWriter::writeProgr(int maxp)
{
}

int JsonChartWriter::writeTrans(int maxp)
{
}
