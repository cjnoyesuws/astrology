#include <string>
#include "Main.h"
#include "ProgramOptions.h"
#include "ProgramConfig.h"
#include "Compile.hpp"
#include "ConfigData.h"
#include "ConfigLoader.h"

using namespace std;
using std::string;

extern void closeFiles();

Main::Main(char* exec, char* dir, char* chartConfig, char* input, char* output)
{
  m_exec = exec;
  m_work_dir = dir;
  m_chartConfig = chartConfig;
  m_input = input;
  m_output = output;
}

Main::~Main()
{
    //dtor
}


int Main::execute()
{
    char buf[125];
    ProgramOptions opt(m_exec, (char *)"/etc/charts.conf", m_work_dir, m_chartConfig, m_input, m_output);
    opt.parse();
    ProgramConfig config;
    if (config.setup(opt)==-1) {
       return -1;
    }
    strcpy(buf, m_work_dir);
    strcat(buf, "/");
    strcat(buf, m_output);
    Options options = config.getChartConfig();
    ChartType type =(enum ChartType)options.getChartCode();
    ChartCompiler *compiler=NULL;
    if (strlen(options.getFormat())==0) {
       options.setFormat("ini");
    }
    switch( options.getChartCode() ) {
       case SgnHseAsp:
       case Complete:
       case CompleteBMid:
       case Numeric:
       case DefaultChart:
            compiler = new NatalChartCompiler(type, buf, options.getFormat());
            compiler->setOptions(options);
       break;
       case Compos:
       case Compatibility:
            compiler = new CompChartCompiler(type, buf, options.getFormat());
            break;
       case Progress:
            compiler = new ProgChartCompiler(type, buf,  options.getFormat());
            break;
       case Transits:
            compiler = new TransChartCompiler(type, buf, options.getFormat());
    }
    if (compiler != NULL) {
        compiler->runChart();
        delete compiler;
    }
    closeFiles();
    return 0;
}


int main( int argc, char *argv[] ) {
   if (argc < 5) {
       fputs("Chart-Compiler <dir> <chart options> <chart input> <chart output>", stderr);
       return -1;
   }

    try {
        Main runner(argv[0], argv[1], argv[2], argv[3], argv[4]);
        return runner.execute();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }

}
