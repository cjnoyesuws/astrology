#ifndef CHART_H
#define CHART_H
#include <string>
#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
class Chart
{
    public:
        Chart() {}
        virtual ~Chart() {}
        void Serialize(PrettyWriter<StringBuffer>& writer);
    protected:

    private:
};

#endif // CHART_H
