#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <string>
#include "ConfigData.h"

using namespace std;
using std::string;

class ConfigLoader
{
    public:
        ConfigLoader() {}
        virtual ~ConfigLoader() {}
        ConfigData &getConfigData() {return m_data;}
        int load(const char *path);
    protected:

    private:
        ConfigData m_data;
};

extern ConfigLoader main_config;

#endif // CONFIGLOADER_H
