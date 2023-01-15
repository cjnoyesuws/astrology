#ifndef _WRITECNV_HPP_
#define _WRITECNV_HPP_


declSlist(CHP_PAGE);
declSlist(XPAP_GROUP);


class TextConvDriverWrite : public TextConvDriverWFnt {
private:
	OSLIST(CHP_PAGE) chpList;
	OSLIST(XPAP_GROUP) papList;
	XPAP curPap;
	XPAP_GROUP paps;
	CHP_PAGE   chps;
	PAGES pgOfs;
	long fcMac;
	unsigned pnMac;
	long curOfs;
	long lastOfsChp;
	long lastOfsPap;
	int  papChange;
public:
      TextConvDriverWrite( int ans ) : TextConvDriverWFnt(ans,0)  {
	 curPap.init(); paps.init();  paps.setFirst(128L);
	 chps.setFirst(128L); curOfs = 128L; lastOfsChp = 128L;
	 lastOfsPap = 128L; papChange = 1; chps.initFodCount(); mul = 144;
      }
      ~TextConvDriverWrite() {}
      virtual void initDriver( FIL_ATTRIB *a ) {}
      virtual char *tabSet( char *buf, int *sz );
      virtual char *tabOut( char *buf, int *col, int *sz );
      virtual void initStringPrint(int left, int width, int version, int code )
		 { writeHeader(); }
      virtual void finishUpFile();
      virtual void finishUpJob();
      virtual void initDecomp( int width );
      virtual unsigned int decompress(char *outbuf,
			  unsigned out_size, int *lines, int mode );
      virtual int stringPrint( char *string )
		 { fwrite(string, 1, strlen(string), ostream); return( ferror(ostream ) ); }
      virtual char *getOpenMode() { return "wb"; }
      virtual char *getAppendMode() { return "ab"; }
      char *moveStr( unsigned char *in, unsigned char *out, unsigned int *sz );
      int writeHeader();
      int writeFontTable();
      int writePageTable();
      int writeChpPaps();
      int addPaps();
      int addChps();
      };

#endif /*  _WRITECNV_HPP_ */
