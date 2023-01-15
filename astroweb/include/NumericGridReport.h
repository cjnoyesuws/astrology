#ifndef NUMERICGRIDREPORT_H
#define NUMERICGRIDREPORT_H
#include "ConfigData.h"
#include "ReportConfig.h"
#include "Report.h"
#include "GridReport.h"


class NumericGridReport : GridReport {
    public:
        NumericGridReport();
        NumericGridReport(ConfigData &configData, ReportConfig &reportConfig, int rows, int cols) : GridReport(configData, reportConfig, rows, cols) : {}
        virtual ~NumericGridReport() {}
        virtual bool generateReport();
    protected:
        const char *rppl, *rphs, *rpah, *rpas;
        const char *reportName="NUMERICGRID";
        const char *summaryName="SUMMARY";
        bool entry( AS_INF  *inf, int planet, unsigned mode, AS_INF_EXT *aie);
    private:
};

#endif // NUMERICGRIDREPORT_H
