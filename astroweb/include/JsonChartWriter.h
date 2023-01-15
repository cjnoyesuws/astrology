#ifndef JSONCHARTWRITER_H
#define JSONCHARTWRITER_H
#include <cstdio>
#include <stdio.h>
#include "BaseChartWriter.h"

class JsonChartWriter : public BaseChartWriter
{
    public:
        JsonChartWriter(FILE *_stream);
        virtual ~JsonChartWriter();
        virtual int writeNatal(int maxp);
        virtual int writeCompat(int maxp);
        virtual int writeProgr(int maxp);
        virtual int writeTrans(int maxp);
    protected:
    char *buffer;
    private:
};

#endif // JSONCHARTWRITER_H
