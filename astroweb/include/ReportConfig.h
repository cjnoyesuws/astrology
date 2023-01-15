#ifndef REPORTCONFIG_H
#define REPORTCONFIG_H

#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include <string>
#include "utlduad.h"

class ReportConfig
{
    public:
        ReportConfig();
        virtual ~ReportConfig();

        std::string &getExt() { return m_ext; }
        const char *getName() { return m_name.c_str(); }
        const char *getComments() { return m_comments.c_str();}
        std::string &getType() { return m_type; }
        std::string &getReport() { return m_report; }
        std::string &getReportPath() { return m_report_path; }
        AS_INF *getInfPtr() { return inf_ptr; }
        AS_INF *getAltInfPtr() { return alt_inf_ptr; }
        AS_INF_EXT *getInfExtPtr() {return inf_ext_ptr;}
        AS_INF_EXT *getAltInfExtPtr() { return alt_ext_ptr;}
        BIRTH_DB *getBirthData() { return birth_data;}
        DATA_PACKET*getDataPkt() { return data_ptr;}
        void setInfExtPtr( AS_INF_EXT *ptr, AS_INF_EXT *alt_ptr) {inf_ext_ptr = ptr; alt_ext_ptr=alt_ptr;}
        void setInfPtr( AS_INF *ptr, AS_INF *alt) { inf_ptr = ptr; alt_inf_ptr = alt;}
        void setBirthDB( BIRTH_DB* data) { birth_data = data; }
        void setPktPtr(DATA_PACKET *pkt ) { data_ptr = pkt;}
        unsigned &getMode() { return m_mode; }
        int &getHouseMode() { return house_mode;}
    protected:

    private:
        std::string m_ext;
        std::string m_name;
        std::string m_comments;
        std::string m_type;
        std::string m_report;
        std::string m_report_path;
        AS_INF_EXT *inf_ext_ptr;
        AS_INF_EXT *alt_ext_ptr;
        AS_INF *inf_ptr;
        AS_INF *alt_inf_ptr;
        BIRTH_DB *birth_data;
        DATA_PACKET *data_ptr;
        unsigned m_mode;
        int house_mode;
};

#endif // REPORTCONFIG_H
