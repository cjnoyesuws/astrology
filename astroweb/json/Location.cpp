#include "astro.h"
#include "useri.h"
#include <iostream>
#include <string>
#include <rapidjson/rapidjson.h>
#include <rapidjson/fwd.h>
#include <rapidjson/reader.h>
#include "Location.h"
using namespace rapidjson;
using namespace std;


int Location::parse(const char *buff) {
    if (buff ==0L || strlen(buff)==0) {
        return -1;
    }
    instance.m_location = m_location;
    instance.m_latitude = m_latitude;
    instance.m_longitude = m_longitude;
    Reader reader;
    StringStream ss(buff);
    reader.Parse(ss, handler);
    m_location = instance.m_location;
    m_latitude = instance.m_latitude;
    m_longitude = instance.m_longitude;
    return 0;
}




