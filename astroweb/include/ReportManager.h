#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include "astro.h"
#include "dataext.h"
#include "useri.h"
#include "utlduad.h"

#include "ConfigData.h"
#include "TextManager.h"
#include "Report.h"
#include "charcons.h"
#include <sstream>

class ReportManager
{
    public:
        ReportManager(ConfigData &config, std::string &report) { pManager = new TextManager(config);
            m_report = pManager->openReportText(report); m_global = pManager->openReportText( std::string("GLOBAL"));
            m_planets = pManager->openText(ASPECT_FILE_name);
            m_houses = pManager->openText(HOUSE_FILE_name);
        }
      virtual  ~ReportManager() {
           pManager->closeReport(m_report);
           pManager->closeReport(m_global);
           pManager->closeText(m_planets);
           pManager->closeText(m_houses);
           delete pManager;
        }
        TextManager *getTextManager() { return pManager; }
        int getGlobal() { return m_global; }
        int getReport() { return m_report; }
        const char *getKey(int key, int index=0);
        bool title(char *s1, char *s2, char *s3, char *rpt);
        bool houseSign( int house, int minutes, int *pcusp, int *psign, char *s1, char *rpt );
        bool planetSignExt( int planet, AS_INF_EXT *aie, char *s1,  char *rpt, int type );
        bool planetSign( int planet, AS_INF *ptr,void *data, BITS mode, char *s1, char * s2, char *rpt, int type );
        bool planetHouse( int planet, AS_INF *ptr, char *s1, char *s2, char *rpt, int type );
        bool midpointHouse( int planet, MIDPT *ptr, char * s1, char *rpt, int type );
        bool midpointSign(int planet, MIDPT *ptr, char * s1, char *rpt, int type );

        bool switchReport( char *report ) { pManager->closeReport(m_report); m_report =pManager->openReportText( report); return true;}
        bool aspects2( char * s1, char * s2, int pl, ASPEC *as, char *rpt, int type );
        bool aspects( char * s1, int pl, ASPEC *as, char *rpt, int type );

        bool returnTitle(int chart, char * s1, char * s2, char *rpt );
        bool returnHead( char * s1, BIRTH_DB *data,RETURN_DATA *retd, DATA_PACKET *dpk, int house_mode, char *rpt );
        bool returnEntry( int chart, int reno, DATES *d, TIM *t, int ap, char * s1, char *rpt );
        bool birthHeadGroup( BITS mode, BIRTH_DB *data,int house_mode, char *cmt, DATA_PACKET *dpk );
        bool transHeadGroup( BITS mode, BIRTH_DB *data, char *cmt,int house_mode, char *name, DATA_PACKET *dpk );
        bool transitId( int transit, DATES *d, char *s1, char *s2, char *rpt );
        bool tsHouseMode( char * s1, int mode, int house_mode, char *rpt );
        bool relocHeader( char * s1, DATA_PACKET *dpk, char *rpt );
        bool progHeader( char * s1, DATA_PACKET *dpk, char *rpt );
        bool solarHeader( char * s1, DATA_PACKET *dpk, char *rpt );
        bool transHeader(char * s1, DATA_PACKET *dpk, char *rpt );
        bool printCusp( int i, short *house_cusps, char *rpt );
        bool printCusps(short *house_cusps, char *rpt );
        bool scoutPlanet( char * s1, char * s2, int sp, char *rpt );
        bool summGenders( char * s1, char * s2, char *rpt );
        bool summElements( char * s1, char * s2, char *rpt );
        bool summQualities( char * s1, char * s2, char *rpt );
        bool summHemispheres( char * s1, char * s2, char *rpt );
        bool summFunctionals( char * s1, char * s2, char *rpt );
        bool summModals( char * s1, char * s2, char *rpt );
        bool aspectCount( char * s1, char * s2, char *rpt );
        bool signCount( char * s1, char * s2, char *rpt );
        bool houseCount( char * s1, char * s2, char *rpt );
        bool midpointSign(NUM planet, MIDPT *ptr,char * s1, char *rpt, int type );
        bool midpointHouse( NUM planet, MIDPT *ptr, char * s1, char *rpt, int type );
        bool planetHouse( FILE *stream, NUM planet, AS_INF *ptr,char * s1, char *s2, char *rpt, int type );
        bool planetSign( NUM planet, AS_INF *ptr,int type, void *data, BITS mode, char * s1, char * s2, char *rpt );
        bool planetSignExt( NUM planet, AS_INF_EXT *aie,char * s1,  char *rpt, int type );
        bool houseSign( NUM house, DEGR minutes, int *pcusp, int *psign, char * s1, char *rpt );
        std::string getBuffer() { return m_stream.str(); }
        std::stringstream &getStream() { return m_stream; }
    protected:
        friend class TextManager;
        friend class Report;
        TextManager *pManager;
        int m_global;
        int m_report;
        std::stringstream m_stream;

        int m_planets;
        int m_houses;
        int m_aspects;
        void enquoteCaps(char *s, int cap);
        void caps( char *s, int cap );
        void zeroFillNum(int n, int v, int cap);
        char *boolQuery( int var, char *fmt );
        char *mintQuery( short *vars, short *test, int cnt, char *fmt );
        char *nextArg( char *text );
        bool firstName( char *name, int cap );
        bool streamOk() { return m_stream.good(); }
        bool append( char *txt) { m_stream << txt; return streamOk(); }
    private:
};

#endif // REPORTMANAGER_H
