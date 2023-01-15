#ifndef JSONCHARTREADER_H_INCLUDED
#define JSONCHARTREADER_H_INCLUDED

class JsonChartReader : public AbstractReader {
public:
    JsonChartReader()  {}
    JsonChartReader(FILE *_stream);
    ~JsonChartReader() {}
    int readData();
protected:
    int loadJson();
    cJSON *getSubObject(const char *key);
    int readLine();
};

#endif // JSONCHARTREADER_H_INCLUDED
