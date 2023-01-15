
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "paths.hpp"
#include "ConfigLoader.h"
#include "ConfigData.h"

static char buffer[120] = {""};
static char home[120] = {""};

void setHomeDir(char *pHome) {
   strcpy(home,pHome);
}


char *getBaseDir() {
  static char buf[75];
  getcwd(home,120);
}

void removeDots( char *buf )
{
}


char *set_path( char const *name, int type )
{

 switch (type) {
   case DATA_F:
	   strcpy(buffer,main_config.getConfigData().getDataDir().c_str());
	   break;
   case USER_F:
	   strcpy(buffer,main_config.getConfigData().getQueueDir().c_str());
	   break;
  }
  if (buffer[strlen(buffer)-1] != '/') {
     strcat(buffer,"/");
  }
  strcat(buffer, name);
  return buffer;
}
