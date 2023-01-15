#ifndef CONFIGHELPER_H_INCLUDED
#define CONFIGHELPER_H_INCLUDED

struct entry {
   const char * label;
   unsigned short value;
};


class ConfigHelper {
public:
    ConfigHelper() {}
    ~ConfigHelper() {}
    unsigned short parseFlags(const char *text);
    short findHouses(const char *text);
    short findRect(const char *text);
    short findProgressed(const char *text);
    short findChartCode(const char *text);
protected:
    short findEntry(const char *text, entry *entries, int count, int dflt);
};


#endif // CONFIGHELPER_H_INCLUDED
