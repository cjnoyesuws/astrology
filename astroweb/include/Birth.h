#ifndef BIRTH_H
#define BIRTH_H
#include <cstring>
#include "astro.h"
#include "useri.h"
#include "DegMin.h"
#include "Location.h"
#include "Writer.h"

using rapidjson, std;

class Birth
{
    public:
        Birth() { memset(&m_birth,0,sizeof(BIRTH_DB));}
        Birth(Birth &b) { m_birth = b.getBirth(); m_location = Location(b.getLocation())};
        virtual ~Birth();
        BIRTH_DB &getBirth() {return m_birth;}
        Location &getLocation() { return m_location;}
        int parseJson(const char *buff);
        int handleKey(const char *key, unsigned int val) {
            return handleKey(key, (int)val);
        }
        int static handleKey(const char *key, double val) {
            if (strcmp(key,"longitude")==0) {
                m_location.handleKey(key,val);
            }
            else if (strcmp(key,"latitude")==0) {
                m_location.handleKey(key,val);
            }
            return 1;
        }
        int static handleKey(const char *key, int val) {
            if (strcmp(key,"sex")==0) {
               m_birth.sex = val;
            }
            if (strcmp(key,"am_pm")==0) {
               m_birth.am_pm=val;
            }
            if (strcmp(key,"time_zone")==0) {
               m_birth.time_zone = val;
            }
            if (strcmp(key,"special_code")) {
               m_birth.special_code = val;
            }
            if (strcmp(key,"adj_hours")==0) {
                m_birth.hrs_offset = val;
            }
            if (strcmp(key,"adj_minutes")==0) {
                m_birth.min_offset = val;
            }
            m_location.handleKey(key,val);

            return 1;
        }
        int static handleKey(const char *key, const char *val) {
            if (strcmp(key,"name")==0) {
               strcpy(&m_birth.name,val);
            }
            else {
                m_location.handleKey(key,val);
            }
            else if (strcmp(key,"birth_date")==0) {
                sscanf(buff,"%d/%d/%d", &m_birth.birth_data.birth_date.year,&m_birth.birth_data.birth_date.month,&m_birth.birth_data.birth_date.day);
            }
            else if (strcmp(key,"birth_time")==0) {
                sscanf(buff,"%d:%d:%d", &m_birth.birth_data.birth_time.hours,&m_birth.birth_data.birth_time.minutes,&m_birth.birth_data.birth_time.seconds);
            }
        }
            return 1;
        }
    protected:
        void Serialize(DataWriter& writer) {
            char buf[20];
            writer.StartObject();
            writer.Key("name");
            writer.String(m_birth.name);
            writer.Key("sex");
            writer.Int(m_birth.sex);
            writer.Key("date");
            sprintf(buf,"%d/%d/%d", m_birth.birth_data.birth_date.year, m_birth.birth_data.birth_date.month, m_birth.birth_data.birth_date.day );
            writer.String(buf);
            writer.Key("time");
            sprintf(buf,"%d:%d:%d", m_birth.birth_data.birth_time.hours, m_birth.birth_data.birth_time.minutes, m_birth.birth_data.birth_time.seconds );
            writer.String(buf);
            writer.Key("country");
            writer.String(m_birth.country);
            writer.Key("state");
            writer.String(m_birth.state);
            writer.Key("location");
            writer.String(m_birth.location);
            writer.Key("longitude");
            writer.Double(toDouble(m_location.longitude));
            writer.Key("latitude");
            writer.Double(toDouble(m_location.latitude));
            writer.Key("timezone");
            writer.Int(m_birth.time_zone);
            writer.Key("special_code");
            writer.Int(m_birth.special_code);
            writer.Key("adj_hours");
            writer.Int(m_birth.birth_data.local_adjust);
            writer.Key("adj_minutes");
            writer.Int(m_birth.birth_data.local_minutes);
            writer.Key("noon_date");
            sprintf(buf,"%d/%d/%d", m_birth.birth_data.noon_date.year, m_birth.birth_data.noon_date.month, m_birth.birth_data.noon_date.day );
            writer.String(buf);
            writer.Key("noon_time");
            sprintf(buf,"%d:%d:%d", m_birth.birth_data.noon_time.hours, m_birth.birth_data.noon_time.minutes, m_birth.birth_data.noon_time.seconds );
            writer.EndObject();
        }
        double toDouble(DEG_MIN &loc);
        void fromDouble(double val, char dirs[2], DEG_MIN &loc);
        struct BirthHandler {
            bool Null() { std::cout << "Null()" << std::endl; return true; }
            bool Bool(bool b) { std::cout << "Bool(" << std::boolalpha << b << ")" << std::endl; return true; }
            bool Int(int i) { std::cout << "Int(" << i << ")" << std::endl; handleKey(currKey,i); return true; }
            bool Uint(unsigned u) { std::cout << "Uint(" << u << ")"; handleKey(currKey,u); std::cout << std::endl; return true; }
            bool Int64(int64_t i) { std::cout << "Int64(" << i << ")" << std::endl; return true; }
            bool Uint64(uint64_t u) { std::cout << "Uint64(" << u << ")" << std::endl; return true; }
            bool Double(double d) { std::cout << "Double(" << d << ")" << std::endl; handleKey(currKey,d); return true; }
            bool RawNumber(const char* str, SizeType length, bool copy) {
                std::cout << "Number(" << str << ", " << length << ", " << std::boolalpha << copy << ")" << std::endl;
                return true;
            }
            bool String(const char* str, SizeType length, bool copy) {
                std::cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << std::endl;
                handleKey(currKey,str);
                return true;
            }
            bool StartObject() { std::cout << "StartObject()" << std::endl; return true; }
            bool Key(const char* str, SizeType length, bool copy) {
                currKey = str;
                std::cout << "Key(" << str << ", " << length << ", " << std::boolalpha << copy << ")" << std::endl;
                return true;
            }
            bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
            bool StartArray() { cout << "StartArray()" << endl; return true; }
            bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
            const char *currKey;
        };

    private:
        BIRTH_DB m_birth;
        Location m_location;
};

#endif // BIRTH_H
