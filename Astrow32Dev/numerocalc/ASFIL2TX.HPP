#ifndef _ASFIL2TX_HPP_
#define _ASFIL2TX_HPP_

class  astroFileToText {
       int ansi, n, outsiz;
       TextConvDriver *drvr;
       FILE *outstream;
       char *buffer, *exp_buf;
public:
       astroFileToText();
       TextConvDriver *getDriver() { return drvr; }
       ~astroFileToText();
       int convert( char *infile, char *outfile );
       };

#endif /* _ASFIL2TX_HPP_  */
