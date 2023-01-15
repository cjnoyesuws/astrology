#ifndef GRIDREPORT_H
#define GRIDREPORT_H

#include "Report.h"
#include "ReportConfig.h"
#include "ConfigData.h"
#include "grids.h"

class GridReport : public Report
{
    public:
        GridReport();
        GridReport(ConfigData &configData, ReportConfig &reportConfig, int rows, int cols) : Report(configData,reportConfig) { m_rows = rows; m_cols = cols; }
        virtual ~GridReport();

    protected:
        int &getCols() { return m_cols;}
        int &getRows() { return m_rows; }
    private:
        int m_rows;
        int m_cols;
};

#endif // GRIDREPORT_H
