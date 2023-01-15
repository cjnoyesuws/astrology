#include "astro.h"
#include "useri.h"
#include <string>
#include <iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "Location.h"
#include "Birth.h"


using namespace rapidjson;
using namespace std;

int Birth::parseJson(const char *buff) {
    if (buff ==0L || strlen(buff)==0) {
        return -1;
    }
    LocationHandler handler;
    Reader reader;
    StringStream ss(buff);
    reader.Parse(ss, handler);
    return 0;
}

