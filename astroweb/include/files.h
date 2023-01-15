extern void setSession(char *);
extern char *getSession();
extern FILE *getConfigFile();
extern FILE *getInputFile();
extern FILE *getOutputFile(char *basename, char *format);
extern FILE *getErrorFile();
extern void closeFiles();

