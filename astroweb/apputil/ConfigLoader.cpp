#include <string>
#include <stdio.h>
#include "ConfigData.h"
#include "ConfigLoader.h"
#include <cstring>

using namespace std;
using std::string;

extern char *strclip(char *pStr);

int ConfigLoader::load(const char *path)
{
  char buf[100];
  char *p;
  FILE *stream = fopen(path,"r");
  fgets(buf,99,stream);
  buf[strlen(buf)-1]='\0';
  p = strclip(buf);
  getConfigData().getDataDir() = (std::string) p;
  fgets(buf,99,stream);
  buf[strlen(buf)-1]='\0';
  p = strclip(buf);
  getConfigData().getRunDir() = (std::string) p;
  fgets(buf,99,stream);
  buf[strlen(buf)-1]='\0';
  p = strclip(buf);
  getConfigData().getQueueDir() = (std::string) p;
  fgets(buf,99,stream);
  buf[strlen(buf)-1]='\0';
  p = strclip(buf);
  getConfigData().getReportDb() = (std::string) p;
  fclose(stream);
}


ConfigLoader main_config;
