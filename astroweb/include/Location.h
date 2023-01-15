#ifndef LOCATION_H
#define LOCATION_H
#include "astro.h"
#include "useri.h"
#include <cstring>
#include "rapidjson/rapidjson.h"
#include "Writer.h"
#include "DegMin.h"

using namespace rapidjson;
using namespace std;

class Location
{
    public:
        Location(BIRTH_DB &b) { strcpy(m_location.country,b.country); strcpy(m_location.state,b.state); strcpy(m_location.location,b.location);
            m_longitude = DegMin(b.birth_data.longitude); m_latitude = DegMin(b.birth_data.latitude);
            m_instance = *this;
            }
        Location(LOC_DB &val) {m_location=val; m_longitude = DegMin(m_location.longitude); m_latitude = DegMin(m_location.latitude);
           m_instance = *this;}
        Location() { memset(&m_location, 0, sizeof(LOC_DB)); m_longitude = DegMin(); m_latitude=DegMin(); m_instance = *this;}
        virtual ~Location();
        LOC_DB &getLocation() { return m_location; }
        void Set( LOC_DB &val ) {m_location=val; m_longitude = DegMin(m_location.longitude); m_latitude = DegMin(m_location.latitude);}
        int parse(const char *buff);
    protected:
        int handleKey(const char *key, unsigned int val) {
            return handleKey(key,(int)val);
        }
        int handleKey(const char *key, double val) {
            if (strcmp(key,"longitude")==0) {
                m_longitude.fromDouble(val,"WE");
            }
            else if (strcmp(key,"latitude")==0) {
                m_latitude.fromDouble(val,"NS");
            }
            return 1;
        }
        int handleKey(const char *key, int val) {
            if (strcmp(key,"timezone")==0) {
                m_location.time_zone = val;
            }
            if (strcmp(key,"special_code")==0) {
                m_location.special_code = val;
            }
            if (strcmp(key,"hours")==0) {
                m_location.hrs_offset = val;
            }
            if (strcmp(key,"minutes")==0) {
                m_location.min_offset = val;
            }
            return 1;
        }
        int handleKey(const char *key, const char * buff) {
            if (strcmp(key,"country")==0) {
                strncpy(m_location.country,buff,sizeof(m_location.country));
            }
            else if (strcmp(key,"state")==0) {
                strncpy(m_location.state,buff,sizeof(m_location.state));
            }
            else if (strcmp(key,"location")==0) {
                strncpy(m_location.location,buff,sizeof(m_location.location));
            }
            return 1;
        }
        void Serialize(Writer& writer) {
            writer.StartObject(0);
            writer.Key("country");
            writer.String(m_location.country);
            writer.Key("state");
            writer.String(m_location.state);
            writer.Key("location");
            writer.String(m_location.location);
            writer.Key("longitude");
            writer.Double(m_longitude.toDouble());
            writer.Key("latitude");
            writer.Double(m_latitude.toDouble());
            writer.Key("timezone");
            writer.Int(m_location.time_zone);
            writer.Key("special_code");
            writer.Int(m_location.special_code);
            writer.Key("hours");
            writer.Int(m_location.hrs_offset);
            writer.Key("minutes");
            writer.Int(m_location.min_offset);
            writer.EndObject();
            }
            struct LocationHandler {
                bool Null() { std::cout << "Null()" << std::endl; return true; }
                bool Bool(bool b) { cout << "Bool(" << std::boolalpha << b << ")" << std::endl; return true; }
                bool Int(int i) { cout << "Int(" << i << ")" << std::endl; m_instance.handleKey(currKey,i); return true; }
                bool Uint(unsigned u) { std::cout << "Uint(" << u << ")"; m_instance.handleKey(currKey,u); << std::endl; return true; }
                bool Int64(int64_t i) { std::cout << "Int64(" << i << ")" << std::endl; return true; }
                bool Uint64(uint64_t u) { std::cout << "Uint64(" << u << ")" << std::endl; return true; }
                bool Double(double d) { std::cout << "Double(" << d << ")" << std::endl; m_instance.handleKey(currKey,d); return true; }
                bool RawNumber(const char* str, SizeType length, bool copy) {
                    std::cout << "Number(" << str << ", " << length << ", " << std::std::boolalpha << copy << ")" << std::endl;
                    return true;
                }
                bool String(const char* str, SizeType length, bool copy) {
                    std::cout << "String(" << str << ", " << length << ", " << std::boolalpha << copy << ")" << std::endl;
                    handleKey(currKey,str);
                    return true;
                }
                bool StartObject() { std::cout << "StartObject()" << std::endl; return true; }
                bool Key(const char* str, SizeType length, bool copy) {
                    currKey = str;
                    std::cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << std::endl;
                    return true;
                }
                bool EndObject(SizeType memberCount) { std::cout << "EndObject(" << memberCount << ")" << std::endl; return true; }
                bool StartArray() { std::cout << "StartArray()" << std::endl; return true; }
                bool EndArray(SizeType elementCount) { std::cout << "EndArray(" << elementCount << ")" << std::endl; return true; }
                const char *currKey;
                };

        private :
            Location &m_instance = Location();
            LOC_DB m_location;
            DegMin m_longitude;
            DegMin m_latitude;
};

#endif // LOCATION_H
