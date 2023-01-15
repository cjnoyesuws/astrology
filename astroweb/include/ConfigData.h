#ifndef CONFIGDATA_H
#define CONFIGDATA_H
#include <string>

using namespace std;
using std::string;

class ConfigData
{
    public:
        ConfigData();
        virtual ~ConfigData();
        std::string &getDataDir() { return m_data_dir; }
        std::string &getRunDir() { return m_run_dir;}
        std::string &getQueueDir() { return m_queue_dir; }
        std::string &getReportDb() { return m_report_db; }
    protected:

    private:
        std::string m_queue_dir;
        std::string m_data_dir;
        std::string m_run_dir;
        std::string m_report_db;
};

#endif // CONFIGDATA_H
