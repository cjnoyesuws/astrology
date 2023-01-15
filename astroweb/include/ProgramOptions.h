#ifndef PROGRAMOPTIONS_H_INCLUDED
#define PROGRAMOPTIONS_H_INCLUDED
#include <string>

using namespace std;
using std::string;

class ProgramOptions {
public:
    ProgramOptions() {}
    ProgramOptions(char * exec, char *config, char *dir, char *chartConfig, char *input, char *output) {m_exec = exec;
        m_main_config = config; m_work_dir=dir; m_chart_config = chartConfig; m_input = input; m_output = output; }
    ~ProgramOptions() {}
    int parse();
    std::string &getMainConfig() { return m_main_config;}
    std::string &getChartConfig() { return m_chart_config;}
    std::string &getLog() { return m_log;}
    std::string &getInput() { return m_input; }
    std::string &getOutput() { return m_output; }
    std::string & getRunDir() { return m_run_dir;}
    std::string & getWorkDir() { return m_work_dir;}

protected:
    std::string m_main_config;
    std::string m_chart_config;
    std::string m_log;
    std::string m_input;
    std::string m_output;
    std::string m_run_dir;
    std::string m_data_dir;
    std::string m_work_dir;
    std::string m_exec;
};


#endif // PROGRAMOPTIONS_H_INCLUDED
