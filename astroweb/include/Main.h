#ifndef MAIN_H
#define MAIN_H

using namespace std;
using std::string;

class Main
{
    public:
        Main(char* exec, char* dir, char* chartConfig, char* input, char* output);
        virtual ~Main();
        int execute();
    protected:
        char *getInput() { return m_input;}
        char *getOutput() { return m_output;}
        char *m_exec;
        char *m_work_dir;
        char *m_chartConfig;
        char *m_input;
        char *m_output;

    private:
};

#endif // MAIN_H
