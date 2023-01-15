#ifndef REPORT_H
#define REPORT_H

#include "Report.h"
#include "ReportManager.h"
#include "TextManager.h"
#include "ReportConfig.h"
#include "ConfigData.h"
#include "stdio.h"
#include "cJSON.h"


class Report
{
    public:
        Report(ConfigData &configData, ReportConfig &reportConfig);
        Report();
        virtual ~Report();
        bool open();
        bool close() { fclose(m_pStream); m_pStream = NULL; return true; }
        virtual bool generateReport();
    protected:
        friend class ReportManager;
        friend class TextManaqer;
        FILE *getStream() {return m_pStream;}
        cJSON *getMetadata();
        bool writeDocument();
        cJSON *getDocument() { return m_pDocument; }
        bool addBodyItem(cJSON *item, char *key);
        bool addText( char *text, char *key);
        ReportManager *getReportManager() { return m_pReportManager;}
        TextManager *getTextManager() { return m_pTextManager; }
        cJSON *getBody() { return m_pBody; }
        ConfigData& getConfig() { return m_rConfig; }
        ReportConfig& getReportConfig() { return m_rReportConfig; }
        bool title(char *s1, char *s2, char *s3, char *rpt);
        bool commit(char *key);
        virtual bool printSummary();
        virtual bool updateBody() { return true; }
        std::string getName() { return m_name; }
        std::string getComments() { return m_comments; }
    private:
        std::string m_ext;
        std::string m_name;
        std::string m_comments;
        std::string m_type;
        std::string m_path;
        ReportManager * m_pReportManager;
        TextManager *m_pTextManager;
        int m_planets;
        int m_houses;
        int m_aspects;
        int m_summary;
        FILE *m_pStream;
        cJSON *m_pDocument;
        cJSON *m_pReport;
        cJSON *m_pBody;
        ReportConfig m_rReportConfig;
        ConfigData m_rConfig;
};

#endif // REPORT_H
