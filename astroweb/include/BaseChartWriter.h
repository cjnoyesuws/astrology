#ifndef BASECHARTWRITER_H
#define BASECHARTWRITER_H


class BaseChartWriter
{
    public:
        virtual ~BaseChartWriter() {}
        BaseChartWriter( FILE *_stream ) { stream = _stream; }
        virtual int writeNatal(int maxp) { return 0; }
        virtual int writeCompat(int maxp) { return 0; }
        virtual int writeProgr(int maxp) { return 0; }
        virtual int writeTrans(int maxp) { return 0; }
    protected:
        FILE *stream;

    private:
};

#endif // BASECHARTWRITER_H
