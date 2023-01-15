#include <string>
#include "ProgramOptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using std::string;

int ProgramOptions::parse()
{
   char buf[100];
   std::string log = (std::string) m_exec;
   log = log + ".log";
   m_log = log;
   FILE * logStream = fopen(m_log.c_str(),"wt");
   return 0;
}

