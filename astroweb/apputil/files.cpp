#include <stdafx.h>
#include <stdio.h>
#include <files.h>
#include "errors.fns"
#include <paths.hpp>
#include <stdlib.h>
#include <string.h>

static char *sessionkey = "default";
static FILE *config;
static FILE *input;
static FILE *output;
static char buffer[150];


void closeFiles() {
   if (config != NULL) {
      fclose(config);
	  config = NULL;
   }
   if (input != NULL) {
      fclose(input);
	  input = NULL;
   }
   if (output != NULL) {
      fclose(output);
	  output = NULL;
   }
}

char * formatFile(char *name, char *ext) {
   char temp[72];
   if (strchr(name,'.')!= NULL) {
      sprintf(temp,"%s", name);
   }
   else {
      sprintf(temp,"%s.%s", name, ext);
   }
   strcpy(buffer,set_path(temp,USER_F));
   return buffer;
}

FILE* getConfigFile(char *name, char *ext) {
	if (config != NULL) {
	   return config;
	}
	else {
	   config = fopen(formatFile(name,ext),"r");
	   if (config == NULL) {
	      do_error(buffer);
		  exit(-98);
	   }
	   return config;
	}
}

FILE* getInputFile(char *name, char *ext) {
    if (input != NULL) {
        return input;
    }
    input = fopen(formatFile(name,ext),"r");
    if (input ==NULL) {
        do_error(buffer);
        exit(-98);
    }
    return input;
}

FILE* getOutputFile(char *name, char *ext) {
    if (output != NULL) {
        return output;
    }
    output = fopen(formatFile(name,ext),"w");
    if (output == NULL) {
        do_error(buffer);
        exit(-1);
    }
    return output;
}

FILE* getErrorFile() {
	return stderr;

}

