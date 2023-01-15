#include "rapidjson/rapidjson.h"
#include "rapidjson/fwd.h"
#include "rapidjson/stream.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/encodedstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "Writer.h"
#include "string.h"

using rapidjson, std;

bool DataWriter::open()
{
    if (strstr(filename,".json") ==0) {
       char *buf = new char[strlen(filename+5)];
       strcpy(buf,filename);
       strcat(buf,".json");
       filenameWithExt = buf;
    }
    else {
        filenameWithExt = strdup(filename);
    }
    // Prepare writer and output stream.
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));
    typedef AutoUTFOutputStream<unsigned, FileWriteStream> OutputStream;    // NEW
    OutputStream eos(os, eis.GetType(), eis.HasBOM());                      // NEW
    PrettyWriter<OutputStream, UTF8<>, AutoUTF<unsigned> > writer(eos);
    m_writer = writer;
    return true;
}

DataWriter::~DataWriter()
{
    m_writer.close();
    delete filenameWithExt;
}
