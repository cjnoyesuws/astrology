#ifndef JSONWRITER_H
#define JSONWRITER_H
#include <stdio.h>

class JsonWriter
{
    public:
        JsonWriter( FILE *_stream);
        JsonWriter();
        virtual ~JsonWriter();
        FILE *getStream() { return stream; }
    protected:
        FILE * stream;
    private:

};

#endif // JSONWRITER_H
