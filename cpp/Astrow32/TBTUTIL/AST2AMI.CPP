#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <ctype.h>

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static char *ami_soft_line = "\n";
static char *ami_hard_line = "\n\n<+@>";

static int write_ami_header(FILE *stream )
{
 static char header1[] = { "[ver]\n\t4\n[sty]\n\t\n[files]\n[charset]\n\t82"
   "\n\tANSI (Windows, IBM CP 1252)\n[revisions]\n\t0\n[toc]\n\tTOC "
   "1\n\tTOC 2\n\tTOC 3\n\t\n\t\n\t\n\t63\n[prn]\n\tHP LaserJet "
   "Series II\n[lang]\n\t1\n[desc]\n\tSource Text File For "
   "ASTRO For Windows\n\t\n\t\n\t\n\t\n\t761096658\n\t1\n\t"
   "761096430\n\t2\n\t2\n\t0\n\t0\n\t0\n\t0\n\tAstrology "
   "Text Source\n\t\n\t\n\t\n\t\n\t\n\t0\n[fopts]\n\t4\n\t"
   "1\n\t2880\n\t0\n[lnopts]\n\t0\n\tBody Text\n\t1\n[docopts]\n\t"
   "5\n\t2\n[tag]\n\tTOC 3\n\t2\n\t[fnt]\n\t\tCourier\n\t\t"
   "240\n\t\t0\n\t\t32768\n\t[algn]\n\t\t0\n\t\t1\n\t\t0\n\t\t"
   "0\n\t\t0\n\t[spc]\n\t\t33\n\t\t273\n\t\t1\n\t\t0\n\t\t"
   "0\n\t\t1\n\t\t100\n\t[brk]\n\t\t4\n\t[line]\n\t\t8\n\t\t"
   "0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t10\n\t\t"
   "1\n\t[spec]\n\t\t0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t1\n\t\t"
   "0\n\t\t2\n\t\t0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t1\n\t\t"
   "2\n\t\t.\n\t\t,\n\t\t$\n\tTOC 3\n\t0\n\t0\n[tag]\n\tBody "
   "Text\n\t3\n\t[fnt]\n\t\tCourier\n\t\t240\n\t\t0\n\t\t"
   "32768\n\t[algn]\n\t\t0\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t"
   "[spc]\n\t\t33\n\t\t273\n\t\t1\n\t\t0\n\t\t0\n\t\t1\n\t\t" };
 static char header2[] = {
   "100\n\t[brk]\n\t\t4\n\t[line]\n\t\t8\n\t\t0\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t10\n\t\t1\n\t[spec]\n\t\t"
   "0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t1\n\t\t0\n\t\t2\n\t\t"
   "0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t1\n\t\t2\n\t\t.\n\t\t"
   ",\n\t\t$\n\tBody Text\n\t0\n\t0\n[tag]\n\tTOC 1\n\t4\n\t"
   "[fnt]\n\t\tCourier\n\t\t240\n\t\t0\n\t\t32768\n\t[algn]\n\t\t"
   "0\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t[spc]\n\t\t33\n\t\t273\n\t\t"
   "1\n\t\t0\n\t\t0\n\t\t1\n\t\t100\n\t[brk]\n\t\t4\n\t[line]\n\t\t"
   "8\n\t\t0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t"
   "10\n\t\t1\n\t[spec]\n\t\t0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t"
   "1\n\t\t0\n\t\t2\n\t\t0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t"
   "1\n\t\t2\n\t\t.\n\t\t,\n\t\t$\n\tTOC 1\n\t0\n\t0\n[tag]\n\t"
   "TOC 2\n\t5\n\t[fnt]\n\t\tCourier\n\t\t240\n\t\t0\n\t\t"
   "32768\n\t[algn]\n\t\t0\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t"
   "[spc]\n\t\t33\n\t\t273\n\t\t1\n\t\t0\n\t\t0\n\t\t1\n\t\t"
   "100\n\t[brk]\n\t\t4\n\t[line]\n\t\t8\n\t\t0\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t10\n\t\t1\n\t[spec]\n\t\t"
   "0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t1\n\t\t0\n\t\t2\n\t\t"
   "0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t1\n\t\t2\n\t\t.\n\t\t"
   ",\n\t\t$\n\tTOC 2\n\t0\n\t0\n[tag]\n\tBody Text\n\t6\n\t"
   "[fnt]\n\t\tTms Rmn\n\t\t240\n\t\t0\n\t\t49152\n\t[algn]\n\t\t"
   "1\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t[spc]\n\t\t17\n\t\t0\n\t\t"
   "1\n\t\t0\n\t\t0\n\t\t1\n\t\t100\n\t[brk]\n\t\t4\n\t[line]\n\t\t"
   "8\n\t\t0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t"
   "10\n\t\t1\n\t[spec]\n\t\t0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t"
   "0\n\t\t0\n\t\t0\n\t\t0\n\t\t0\n\t[nfmt]\n\t\t280\n\t\t"
   "1\n\t\t2\n\t\t.\n\t\t,\n\t\t$\n\tBody Text\n\t0\n\t0\n"
   "[lay]\n\tStandard\n\t513\n\t[rght]\n\t\t15840\n\t\t12240\n\t\t" };
 static char header3[] = {
   "1\n\t\t1440\n\t\t1440\n\t\t1\n\t\t1440\n\t\t2160\n\t\t"
   "2\n\t\t1\n\t\t0\n\t\t1\n\t\t0\n\t\t2\n\t\t1\n\t\t1440\n\t\t"
   "10080\n\t\t10\n\t\t1\n\t\t720\n\t\t1\n\t\t1440\n\t\t1\n\t\t"
   "2160\n\t\t1\n\t\t2880\n\t\t1\n\t\t3600\n\t\t1\n\t\t4320\n\t\t"
   "1\n\t\t5040\n\t\t1\n\t\t5760\n\t\t1\n\t\t6480\n\t\t1\n\t\t"
   "7200\n\t[hrght]\n\t[lyfrm]\n\t\t1\n\t\t11200\n\t\t0\n\t\t"
   "0\n\t\t12240\n\t\t1440\n\t\t0\n\t\t1\n\t\t3\n\t\t1 0 "
   "0 0 0 0 0\n\t\t0\n\t\t0\n\t\t1\n\t[frmlay]\n\t\t1440\n\t\t"
   "12240\n\t\t1\n\t\t1440\n\t\t72\n\t\t1\n\t\t360\n\t\t2160\n\t\t"
   "0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t0\n\t\t1\n\t\t1440\n\t\t"
   "10080\n\t\t0\n\t[txt]\n>\n\t[frght]\n\t[lyfrm]\n\t\t1\n\t\t"
   "13248\n\t\t0\n\t\t14400\n\t\t12240\n\t\t15840\n\t\t0\n\t\t"
   "1\n\t\t3\n\t\t1 0 0 0 0 0 0\n\t\t0\n\t\t0\n\t\t2\n\t[frmlay]\n\t\t"
   "15840\n\t\t12240\n\t\t1\n\t\t1440\n\t\t360\n\t\t1\n\t\t"
   "14472\n\t\t2160\n\t\t0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t1440\n\t\t10080\n\t\t0\n\t[txt]\n>\n[elay]\n"
   "[l1]\n\t0\n[edoc]\n<+@><:#289,8640><:f240,2Times New "
   "Roman,0,0,0>\n\n" };
 fputs( header1, stream );
 fputs( header2, stream );
 fputs( header3, stream );
 return( 0 );
}

extern "C" {

int __far __pascal __export _AST2AMI( int argc, char *argv[] )
{
 char buf[100], *p;
 char gbuf[200], *gpt;
 FILE *in, *out;
 int c=0, l=0, bok = 0, hichar=0, nxt;

 if ( argc < 2 ) {
    alert_box( "AST2AMI", "AST2AMI INFILE OUTFILE\nConvert ASTRO Text Source file Format to AMIPRO" );
    return( -1 );
    }
 if ( argc < 3 ) {
    strcpy( buf, argv[1] );
    p = strchr( buf, '.' );
    if ( p == NULL )
       strcat( buf, ".DOC" );
    else
       strcpy( p, ".DOC" );
    }
 else
    strcpy( buf, argv[2] );
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "AST2AMI", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wt" ) ) == NULL ) {
    alert_box( "AST2AMI", "Can't Open %s for Writing!", buf );
    fclose( out );
    return( -1 );
    }
 if ( setvbuf( in, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( in, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( in, NULL, _IOFBF, 1024 ) )
	  setvbuf( in, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( out, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( out, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( out, NULL, _IOFBF, 1024 ) )
	  setvbuf( out, NULL, _IOFBF, 256 );
       }
    }
 dllYield();
 write_ami_header( out );
 l = 0;
 while ( fgets( gbuf, 199, in ) != NULL ) {
       gpt = gbuf;
       doConvertText( gbuf, _SRC_T_, _ANS_T_ );
       while ( c = *gpt++ ) {
	     switch( c ) {
		   case '\n' :
			dllYield();
			hichar = 0;
			nxt = fgetc(in);
			if ( nxt != '[' )
			   fputs( ami_hard_line, out );
			else
			   fputs( "\n\n", out );
			ungetc( nxt, in );
			l = 0;
			break;
		   case '<' :
			hichar = 0;
			fputs( "<+\">", out );
			break;
		   case '>' :
			hichar = 0;
			fputs( "<-\">", out );
			break;
		   case '{' :
			hichar = 0;
			fputs( "<+!>", out );
			break;
		   case '}' :
			hichar = 0;
			fputs( "<-!>", out );
			break;
		   case '[' :
			hichar = 0;
			fputs( "<+B>", out );
			break;
		   case ']' :
			hichar = 0;
			fputs( "<+@>", out );
			break;
		   case ' ' :
			bok = 1;
			if (hichar) {
			   fputc( '~', out );
			   fputc( ' ', out );
			   hichar = 0;
			   }
			else
			   fputc( ' ', out );
			break;
		   case '~' :
			c = getc( in );
			l++;
			if ( c == '<' ) {
			   fputs( "<<", out );
			   break;
			   }
			else if ( c == '>' ) {
			   fputs( "<;>", out );
			   break;
			   }
			else if ( c == '|' ) {
			   fputs( "\t", out );
			   break;
			   }
			if ( l > 60 && bok ) {
			   fputc( '\n', out );
			   l = 0;
			   }
			putc( c, out );
			hichar = 0;
			bok = 0;
			break;
		   default :
			l++;
			if ( l > 60 && bok ) {
			   fputc( '\n', out );
			   l = 0;
			   }
			bok = 0;
			if ( c > '~' ) {
			   hichar = 1;
			   fputc( '~', out );
			   }
			else
			   hichar = 0;
			fputc( c, out );
			break;
		   }
	     }
	}
 fputs( "\n\n>\n\n", out );
 fclose( in );
 fclose( out );
 return( 0 );
}


}


