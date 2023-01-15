#ifndef PROGRAMCONFIG_H
#define PROGRAMCONFIG_H
#include "rapidjson/rapidjson.h"
#include "rapidjson/fwd.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "ProgramOptions.h"
#include "setup.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "JsonOptionReader.h"
#include "ConfigData.h"
#include "ProgramConfig.h"

using namespace std;
using std::string;
using rapidjson::Document;
using rapidjson::ParseResult;

class ProgramConfig
{
    public:
        ProgramConfig();
        virtual ~ProgramConfig();
        Document& getInput() {return m_input;}
        Options& getChartConfig() { return m_chart_config;}
        int setup(ProgramOptions &options);
        ConfigData &getMainConfig() { return m_config; }
    protected:
        friend class ProgramOptions;
        Document m_input;
        ConfigData m_config;
        Options m_chart_config;
        ParseResult &getDocument(std::string &str, Document&doc);
        std::string &getFile(std::string &str, std::string &dest);
        std::string &getChartConfigContent(std::string &str);
        bool isJson(std::string &str);
    private:
};

#endif // PROGRAMCONFIG_H
