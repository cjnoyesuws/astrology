// reptransprep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>

char prepbuf[10000];
char textbuf[10000];
int prepptr, textptr;
int repptr, replen;

char *sexcodes[33] = {"He1",
"he1",
"Him1",
"him1",
"His1",
"his1",
"Hiss1",
"hiss1",
"Man1",
"man1",
"boy1",
"Boy1",
"Father1",
"father1",
"Brother1",
"brother1",
"He2",
"he2",
"Him2",
"him2",
"His2",
"his2",
"Hiss2",
"hiss2",
"Man2",
"man2",
"boy2",
"Boy2",
"Father2",
"father2",
"Brother2",
"brother2",
NULL
};

int sexlens[33] = { 3,3,4,4,4,4,5,5,4,4,4,4,7,7,8,8,3,3,4,4,4,4,5,5,4,4,4,4,7,7,8,8};

void reset() {
  prepptr = 0;
  textptr = 0;
  repptr = 0;
}


void prepline(char *buf, FILE *prepf, FILE *txtf) {
  char ch;
  int textstate = -1;
  int textcnt = 0;
  int holdcnt = 0;
  int codeseq = 0;
  char holdbuf[100];
  reset();
  replen = (int)strlen(buf);
  while ( repptr < (replen) ) {
	  switch( buf[repptr] ) {
		 case '@' :
			 codeseq = 0;
			 if ( !strnicmp(buf+repptr,"@TB",3 ) ||
				   !strnicmp(buf+repptr,"@TR",3 ) ) {
			    if ( textstate == 1 ) {
				   textstate = 0;
                   if (holdcnt ) {
				      memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					  prepptr += holdcnt;
					  holdcnt = 0;
				   }
				   if ( textcnt ) {
				     memcpy(prepbuf+prepptr,"`~",2);
				     prepptr += 2;
				   }
				   if ( textcnt )
				      textbuf[textptr++] = '\n';
				 }
			     memcpy(prepbuf+prepptr,buf+repptr,3);
				 prepptr += 3;
				 repptr += 2;
				 textcnt = 0;
				 }
			 else {
				 textstate = 1;
				 textbuf[textptr++] =buf[repptr];
			 }
			 break;
		 case '$' :
             if ( textstate == 1 ) {
			    textstate = 0;
                if ( textcnt ) {
				   memcpy(prepbuf+prepptr,"`~",2);
				   prepptr += 2;
				}
				if (holdcnt ) {
				    memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					prepptr += holdcnt;
				    holdcnt = 0;
				   }
				memcpy(prepbuf+prepptr,buf+repptr,2);
				prepptr += 2;
				if ( textcnt )
				   textbuf[textptr++] = '\n';
			    repptr ++;
				textcnt = 0;
				codeseq = 1;
				}
			 else {
                if (holdcnt ) {
				   memcpy(prepbuf+prepptr,holdbuf,holdcnt);
				   prepptr += holdcnt;
				   holdcnt = 0;
				   }
				memcpy(prepbuf+prepptr,buf+repptr,2);
				prepptr+=2;
				repptr++;
				codeseq = 1;
			 }
			 break;
		 case ' ' :
			 holdbuf[holdcnt++] =buf[repptr];
			 codeseq = 0;
			 break;
		 case '\n' :
			 codeseq = 0;
			 if ( textstate == 1 ) {
			    textstate = 0;
			    if ( textcnt ) {
				   memcpy(prepbuf+prepptr,"`~",2);
				   prepptr += 2;
				}
				if (holdcnt ) {
				    memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					prepptr += holdcnt;
					holdcnt = 0;
				   }
				prepbuf[prepptr++] =buf[repptr];
				if ( textcnt )
				   textbuf[textptr++] = '\n';
				textcnt = 0;
				}
			 else {
			    prepbuf[prepptr++] =buf[repptr];
			 }
			 break;
		 case '[' :
		 case ']' :
		 case '{' :
		 case '}' :
		 case '<' :
		 case '>' :
		 case '|' :
		 case '\'' :
			 codeseq = 0;
			 if ( textstate == 1 ) {
			    textstate = 0;
			    if ( textcnt ) {
				   memcpy(prepbuf+prepptr,"`~",2);
				   prepptr += 2;
				}
				if (holdcnt ) {
				    memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					prepptr += holdcnt;
					holdcnt = 0;
				   }
				prepbuf[prepptr++] =buf[repptr];
				if ( textcnt )
				   textbuf[textptr++] = '\n';
				textcnt = 0;
				}
			 else {
			    prepbuf[prepptr++] =buf[repptr];
			 }
             break;
		 case ':' :
		 case '.' :
		 case ',' :
		 case '#' :
		 case '!' :
		 case '-' :
		 case '?' :
		 case '/' :
			 codeseq = 0;
			 if ( textstate == 1 ) {
				 textbuf[textptr++] =buf[repptr];
			 }
			 else {
			    prepbuf[prepptr++] =buf[repptr];
			 }
			 break;
		 case '^' :
			 if ( buf[repptr+1] == '@' ) {
			    if (holdcnt ) {
				  memcpy(textbuf+textptr,holdbuf,holdcnt);
			      textptr += holdcnt;
				  holdcnt = 0;
				 }
				memcpy(prepbuf+prepptr,buf+repptr,3);
				prepptr+=3;
				repptr += 3;
				while ( buf[repptr] != '|' )
					prepbuf[prepptr++] = buf[repptr++];
				prepbuf[prepptr++] = buf[repptr++];
				int cnt = atoi(buf+repptr);
                while ( buf[repptr] != '|' )
					prepbuf[prepptr++] = buf[repptr++];
				prepbuf[prepptr++] = buf[repptr++];
				for ( int i = 0; i < cnt; i++ ) {
				   while ( buf[repptr] != '|' )
					  prepbuf[prepptr++] = buf[repptr++];
				   prepbuf[prepptr++] = buf[repptr++];
				}
				repptr--;
			 }
			 else {
			   codeseq = 0;
			   if (holdcnt ) {
				  memcpy(textbuf+textptr,holdbuf,holdcnt);
			      textptr += holdcnt;
				  holdcnt = 0;
				 }
			   textstate = 1;
			   textcnt++;
			   textbuf[textptr++] = buf[repptr];
			 }
			 break;
		 case 'D' :
		 case 'd' :
			 if ( !strnicmp(buf+repptr,"DEFTABS",7) ) {
			    codeseq = 0;
			    if ( textstate == 1 ) {
			       textstate = 0;
			       if ( textcnt ) {
				      memcpy(prepbuf+prepptr,"`~",2);
				      prepptr += 2;
				   }
				   if (holdcnt ) {
				       memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					   prepptr += holdcnt;
					   holdcnt = 0;
				      }
				   if ( textcnt )
				      textbuf[textptr++] = '\n';
				   textcnt = 0;
				  }
				memcpy(prepbuf+prepptr,buf+repptr,7);
				prepptr += 7;
				repptr+= 6;
			 }
			 else {
			    codeseq = 0;
			    if (holdcnt ) {
				  memcpy(textbuf+textptr,holdbuf,holdcnt);
			      textptr += holdcnt;
				  holdcnt = 0;
				  }
			 textstate = 1;
			 textcnt++;
			 textbuf[textptr++] = buf[repptr];
			 }
			 break;
		 case 'T' :
		 case 't' :
			 if ( !strnicmp(buf+repptr,"TABS|",5) ) {
			    codeseq = 0;
			    if ( textstate == 1 ) {
			       textstate = 0;
			       if ( textcnt ) {
				      memcpy(prepbuf+prepptr,"`~",2);
				      prepptr += 2;
				   }
				   if (holdcnt ) {
				       memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					   prepptr += holdcnt;
					   holdcnt = 0;
				      }
				   if ( textcnt )
				      textbuf[textptr++] = '\n';
				   textcnt = 0;
				  }
				memcpy(prepbuf+prepptr,buf+repptr,5);
				prepptr += 5;
				repptr+= 5;
				while ( buf[repptr] != '|' )
					prepbuf[prepptr++] = buf[repptr++];
				prepbuf[prepptr++] = buf[repptr++];
				int cnt = atoi(buf+repptr);
                while ( buf[repptr] != '|' )
					prepbuf[prepptr++] = buf[repptr++];
				prepbuf[prepptr++] = buf[repptr++];
				for ( int i = 0; i < cnt; i++ ) {
				   while ( buf[repptr] != '|' )
					  prepbuf[prepptr++] = buf[repptr++];
				   prepbuf[prepptr++] = buf[repptr++];
				}
				repptr--;
			 }
			 else {
			    codeseq = 0;
			    if (holdcnt ) {
				  memcpy(textbuf+textptr,holdbuf,holdcnt);
			      textptr += holdcnt;
				  holdcnt = 0;
				  }
			 textstate = 1;
			 textcnt++;
			 textbuf[textptr++] = buf[repptr];
			 }
			 break;
		 case ';' :
			 {
			   int pos = -1;
			   for ( int i = 0; i < 32; i++ ) {
				   if ( !strncmp(sexcodes[i], buf+repptr+1,sexlens[i]) ) {
				      pos = i;
					  break;
				   }
			   }
			   if ( pos != -1 ) {
				   if ( textstate == 1 ) {
			          textstate = 0;
			          if ( textcnt ) {
				         memcpy(prepbuf+prepptr,"`~",2);
				         prepptr += 2;
				      }
					  if (holdcnt ) {
				          memcpy(prepbuf+prepptr,holdbuf,holdcnt);
					      prepptr += holdcnt;
					      holdcnt = 0;
				         }
				      if ( textcnt )
				         textbuf[textptr++] = '\n';
				      textcnt = 0;
				     }
				   memcpy(prepbuf+prepptr,buf+repptr,sexlens[pos] + 2);
				   prepptr += sexlens[pos] + 2;
				   repptr +=  sexlens[pos] + 1;
			   }
			   else {
			     codeseq = 0;
			     if ( textstate == 1 ) {
				     textbuf[textptr++] =buf[repptr];
			         }
			     else {
			        prepbuf[prepptr++] =buf[repptr];
			     }
			   }
			 }
			 break;
		 default :
			 codeseq = 0;
			 if (holdcnt ) {
				 memcpy(textbuf+textptr,holdbuf,holdcnt);
			     textptr += holdcnt;
				 holdcnt = 0;
				 }
			 textstate = 1;
			 textcnt++;
			 textbuf[textptr++] = buf[repptr];
			 break;
	  }
	  ++repptr;
  }
  prepbuf[prepptr]='\0';
  textbuf[textptr]='\0';
  fputs(prepbuf,prepf);
  fputs(textbuf,txtf);
}




