#include <string>
#include "ProgramOptions.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/fwd.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/pointer.h"
#include "setup.hpp"
#include "IniOptionsReader.h"
#include "JsonOptionReader.h"
#include "stdio.h"
#include "ConfigData.h"
#include "ConfigLoader.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "IniDataReader.h"
#include "ProgramConfig.h"
#include "cstring"
#include "JsonDataReader.h"

using namespace std;
using std::string;
using rapidjson::FileReadStream;
using rapidjson::Document;
using rapidjson::AutoUTF;
using rapidjson::ParseResult;
using rapidjson::ParseFlag;

ProgramConfig::ProgramConfig()
{
    //ctor
}

ProgramConfig::~ProgramConfig()
{
    //dtor
}

int ProgramConfig::setup(ProgramOptions &options)
{

    main_config.load(options.getMainConfig().c_str());
    m_config = main_config.getConfigData();
    std::string dir = m_config.getRunDir();
    options.getRunDir() = dir;
    std::string work = dir + "/" + options.getWorkDir();
    options.getWorkDir() = work;
    options.getInput() = work + "/" + options.getInput();
    options.getOutput() = work + "/" + options.getOutput();
    options.getChartConfig() = work + "/" + options.getChartConfig();

    if (isJson(options.getChartConfig())) {
        JsonOptionReader reader(options.getChartConfig().c_str());
        if (reader.read()==-1) {
           return -1;
        }
        m_chart_config = reader.getOptions();
    }
    else {
        IniOptionsReader reader(options.getChartConfig());
        if (reader.read()==-1) {
           return -1;
           }
        m_chart_config = reader.getOptions();
    }
    if (isJson(options.getInput())) {
        JsonDataReader data(options.getInput().c_str());
        if (data.read() == -1) {
           return -1;
        }
    }
    else {
        IniDataReader reader(options.getInput().c_str());
        if (reader.read()==-1) {
           return -1;
        };
    }

    return 1;
}




std::string &ProgramConfig::getFile( std::string &path, std::string &dest) {
    FILE *file = fopen(path.c_str(),"rt");
    std::string str;
    char *buf = new char[4096];
    while (!feof(file)) {
       char *p = fgets(buf,4096,file);
       str += *p;
    }
    fclose(file);
    dest = str;
    return dest;
}

std::string &ProgramConfig::getChartConfigContent(std::string &path) {
   std::string str = "";
   str = getFile(path, str);

   return str;
}

ParseResult &ProgramConfig::getDocument(std::string &str, Document &doc)
{
    ParseResult res = doc.Parse(str.c_str());
    rapidjson::Value *itr = rapidjson::GetValueByPointer(doc,"/Birth/date");


    return res;
}

bool ProgramConfig::isJson(string &str)
{
    int pos = (str.find(".json"));
    if (pos == std::string::npos) {
        return false;
    }
    else {
        return true;
    }

   }
