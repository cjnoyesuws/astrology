#include <stdio.h>
#include "JsonWriter.h"



JsonWriter::JsonWriter()
{
    //ctor
}


JsonWriter::~JsonWriter()
{
}


JsonWriter::JsonWriter(FILE *_stream)
{
   stream = _stream;
}
