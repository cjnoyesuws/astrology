#ifndef _ASFIL2TX_HPP_
#define _ASFIL2TX_HPP_

class  astroFileToText {
       ReportStyles *prs;
	   int _break, ansi, n, dir, hasCover, outsiz;
       TextConvDriver *drvr;
       FILE *outstream;
       ConvData cd;
       char outfile[350];
       CStringArray *fileList;
	   char *buffer, *exp_buf;
public:
       astroFileToText( int d );
       ~astroFileToText();
       int getSetup( ConvData **pcd );
       void setFiles( CStringArray *fl, int hc );
       TextConvDriver *getDriver();
       int convert( char *infile, int code );
       int doConvert(XPFILE_DB *ptr);
       CoverPageData *getCover( char *name );
       };


class  astroFileToTextSimple {
       ReportStyles *prs;
	   int _break, ansi, n, dir, hasCover, outsiz;
       TextConvDriver *drvr;
       FILE *outstream;
       ConvData cd;
       char outfile[_MAX_PATH], *thefile; 
       char *buffer, *exp_buf;
	   int rtfdrv;
	   
public:
       astroFileToTextSimple( int d, int drv =0 );
       ~astroFileToTextSimple();
       int getSetup();
       void setFiles( char *file );
	   void setOutFile( char *file ) { strcpy(outfile,file); }
       TextConvDriver *getDriver();
       int convert( const char *infile, int code );
       int doConvert( const char *file );
       char *getOutFile() { return outfile; }
	   NFP fptr;
       };

#endif /* _ASFIL2TX_HPP_  */
