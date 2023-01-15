#ifndef _CHARTWRITER_H_
#define _CHARTWRITER_H_


class IniChartWriter : public BaseChartWriter {
protected:
	int writeLine(const char *key, const char *buff);
	int writeSection(const char *key);
	int writeHouses(const char *key, short *houses);
	int writeAspect(const char *key, int planet, ASPEC &aspect );
	int writeAspects(const char *sec, AS_INF *data, int count);
	int writeAspects(const char *key, int index, int planet, AS_INF &data);
	int writePlanet(const char *key, int index, AS_INF &data);
	int writePlanets(const char *, AS_INF *data, int count, int start=0);
	int writeTransitDates();
	int writeTransitChart(int index);
public:
	IniChartWriter( FILE *_stream ) : BaseChartWriter(_stream) {}
	virtual ~IniChartWriter() {}
	virtual int writeNatal(int maxp);
	virtual int writeCompat(int maxp);
	virtual int writeProgr(int maxp);
	virtual int writeTrans(int maxp);
};

#endif



