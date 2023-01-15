#include "ReportManager.h"
#include <cassert>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include "charcons.h"
#include "utlduad.h"
#include <exception>


 const char *ReportManager::getKey(int key, int index) {
 static char erf[] = { "Error in Report--Key %d Not Found see REPORT.SYM" };
 char buf[120];
 static char missing[] = {""};
 const char *text = pManager->getReportText(m_report, key, index);
 const char *alt = pManager->getReportText(m_global, key, index);
   if ( text == NULL && alt == NULL) {
       sprintf(buf, erf, key);
      throw std::logic_error(buf);
   }
   if (text != NULL) {
      return text;
   }
   if (alt != NULL) {
      return alt;
   }
}


char *ReportManager::boolQuery( int var, char *fmt )
{
 char *pt, dlm;

 pt = fmt;
 dlm = *pt;
 pt++;
 if ( var ) {
    while ( *pt && *pt != dlm )
	  m_stream.put( *pt++ );
    pt++;
    while ( *pt && *pt++ != dlm );
    }
 else {
    while ( *pt && *pt != dlm )
		pt++;
	pt++;
	while ( *pt && *pt != dlm )
	    m_stream.put( *pt++);
    pt++;
    }
 return( pt );
}

char *ReportManager::mintQuery( short *vars, short *test, int cnt, char *fmt )
{
 char *pt, dlm;
 int i;

 pt = fmt;
 dlm = *pt;
 pt++;

 for ( i = 0; i < cnt; ++i ) {
     if ( vars[i] == test[i] ) {
	while ( *pt && *pt != dlm )
	      m_stream.put( *pt++ );
	pt++;
	}
     else {
	while ( *pt && *pt != dlm )
		pt++;
	pt++;
	}
     }
 return( pt );
}

char *ReportManager::nextArg( char *text )
{
 char *pt = text;

 while ( *pt && *pt != '$' )
       m_stream.put( *pt++);
 if ( *pt )
    pt++;
 return( pt );
}


bool ReportManager::firstName(char *name, int cap )
{
 char buf[75], buf2[75], *p;


 assert( strlen(name) < sizeof( buf ) );
 if ( cap )
    strcpy( buf2, xstrupr(enquote_strclip(name,(unsigned char *)buf)) );
 else
    strcpy( buf2, enquote_strclip(name,(unsigned char *)buf) );
 assert( strlen(name) < sizeof( buf2 ) );
 if ( !strnicmp( name, "Mr. ", 4 ) || !strnicmp( name, "Ms. ", 4 ) || !strnicmp( name, "Dr. ", 4 ) )
    p = &buf2[4];
 else if ( !strnicmp( name, "Mrs. ", 5 ) || !strnicmp( name, "Mme. ", 5 ) )
    p = &buf2[5];
 else if ( !strnicmp( name, "Sr. ", 4 ) )
    p = &buf2[4];
 else if ( !strnicmp( name, "Sra. ", 5 ) )
    p = &buf2[5];
 else if ( !strnicmp( name, "Srta. ", 6 ) )
    p = &buf2[6];
 else if ( !strnicmp( name+1, ". ", 2 ) )
    p = &buf2[3];
 else
    p = buf2;
 while ( *p && *p != ' ' )
       m_stream.put( *p++ );
 return( m_stream.good() );
}

bool ReportManager::aspects2( char *s1, char *s2, int pl, ASPEC *as, char *rpt, int type )
{
 short ar[3], ar2[3], flag = 0;
 char buf[80];
 char *p = rpt;
 int cap = 0;

 if ( pl < 0 ) {
    flag = 1;
    pl = abs( pl );
    if ( pl >= 100 )
       pl %= 100;
    }
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$');
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n');
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '0' :
	       caps(planet_str( pl ), cap);
	       break;
	  case '1' :
           caps(aspect_str( as->aspect ), cap);
	       break;
	  case '2' :
	       caps(planet_str( as->planet ), cap);
	       break;
	  case '3' :
	       number(2, as->orb );
	       break;
          case '4' :
	       enquoteCaps(s1,cap);
	       break;
	  case '5' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case '6' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if (as->orb < 1) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( as->orb > 8 ) {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       else  {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       p = mintQuery( ar, ar2, 3, p );
	       cap = 0;
	       break;
	  case '7' :
	       p = boolQuery( flag, p );
	       cap = 0;
	       break;
          case '8' :
	  case 'b' : /* Compromise to fix a bug in table */
	       enquoteCaps(s2,buf);
	       break;
	  case '9' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	  	   switch( type ) {
	  #ifdef PRO
	  		  case ARABP_DI :
	  			caps( arabic_part_str( pl ), cap );
	  			break;
	  		  case FIXED_DI :
	  			caps( fixed_star_str( pl ), cap );
	  			break;
	  		  case HELIO_DI :
	  			caps( nh_pla_str( pl ), cap );
	  			break;
	  #endif
	  		 default :
	  			cap = 0;
	  			break;
		     }
          default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::aspects( char *s1, int pl, ASPEC *as, char *rpt, int type )
{
 return( aspects2( s1, "", pl, as, rpt, type ) );
}

void ReportManager::enquoteCaps(char * s, int &cap)
{
 char buf[256];
 if ( s == NULL )
	 return;
 if ( cap ) {
    m_stream << xstrupr(s,buf));
    cap = 0;
    }
 else
    m_stream << s;
}

void ReportManager::caps(char *s, int cap)
{
 char buf[200];
 char buf2[200];
 if ( s == NULL )
	 return;
 if ( cap ) {
    strcpy(buf, s);
    m_stream << xstrupr(buf, buf2));
    cap = 0;
    }
 else
    m_stream << s;
}

void ReportManager::number(int n, int v, int cap)
{
 char buf[100];
 if (cap ) {
    sprintf( buf, "%*d", n, v )
    }
 else {
    sprintf( buf, "%d", v );
    }
  m_stream << buf;
}

void ReportManager::zeroFillNum(int n, int v, int cap)
{
  char buf[100];
  if ( cap ) {
    sprintf( buf, "%0*d", n, v );
    }
 else {
    sprintf( buf, "%d", v );
    }
  m_stream << buf;
}


bool ReportManager::returnTitle(int chart, std::string s1, std::string s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$');
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream(put( '\x80' ) );
	       cap = 0;
		   if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       p = boolQuery(!chart, p );
	       break;
	  case '3' :
	       enquoteCaps(s2, buf );
	       break;
	  case '4' :
	       firstName(s1, cap);
	       cap = 0;
	       break;
	  case '5' :
	       firstName(s2, cap);
	       cap = 0;
	       break;
	  default :
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::returnHead( char * s1, BIRTH_DB *data,
    RETURN_DATA *retd, DATA_PACKET *dpk, int house_mode, char *rpt )
{
 short ar[4], ar2[4];
 char buf[80];
 char *p = rpt;
 int cap = 0;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
		   if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '\n' :
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '2' :
	       m_stream << make_date( &retd->start, buf );
	       cap = 0;
	       break;
	  case '3' :
	       m_stream <<  make_date( &retd->end, buf );
	       cap = 0;
	       break;
	  case '5' :
	       if ( retd->is_prog ) {
		      number(2, retd->prog.offset.year );
		  }
          break;
	  case '4' :
	  case '6' :
	  case '8' :
	  case 'A' :
	  case 'a' :
	  case 'F' :
	  case 'f' :
	       p = boolQuery(retd->is_prog, p );
	       cap = 0;
	       break;
	  case '7' :
	       if ( retd->is_prog ) {
		     number( 2, retd->prog.offset.month );
		     }
	       break;
	  case '9' :
	       if ( retd->is_prog ) {
		     number( 2, retd->prog.offset.day );
		  }
	       break;
	  case 'B' :
	  case 'b' :
	       memset( ar, 0, 8 );
	       memset( ar2, 0xff, 8 );
	       ar[retd->prog.progress_system] = 1;
	       ar2[retd->prog.progress_system] = 1;
	       if ( !retd->is_prog ) {
                ar[3] = 1;
                ar2[3] = 1;
                ar[retd->prog.progress_system] = 0;
                ar2[retd->prog.progress_system] = 0xff;
		  }
	       p = mintQuery( ar, ar2, 4, p );
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       if ( retd->is_prog ) {
                zeroFillNum(2, retd->prog.offset.year );
		   }
	       break;
	  case 'D' :
	  case 'd' :
	       if ( retd->is_prog ) {
                zeroFillNum( 2, retd->prog.offset.month );
		  }
	       break;
	  case 'E' :
	  case 'e' :
	       if ( retd->is_prog ) {
		  zeroFillNum( 2, retd->prog.offset.day );
		  }
	       break;
	  case 'G' :
	  case 'g' :
	       firstName(s1, cap);
	       cap = 0;
	       break;
	  case 'H' :
	  case 'h' :
	       p = boolQuery(!retd->planet, p );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::returnEntry( int chart, int reno, DATES *d, TIM *t, int ap, char *s1, char *rpt )
{
 int cap = 0;
 char buf[100];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$');
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n');
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80');
	       cap = 0;
		   if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( s1, buf );
	       break;
	  case '2' :
	       m_stream << make_date( d, buf );
	       cap = 0;
	       break;
	  case '3' :
	       m_stream << make_time( t, ap, buf );
	       cap = 0;
	       break;
	  case '4' :
	       p = boolQuery(chart, p );
	       break;
	  case '5' :
	       cap = 1;
	       number( 2, reno );
	       break;
	  case '6' :
	       firstName(s1, cap);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::birthHeadGroup( unsigned mode, BIRTH_DB *data,int house_mode, char *cmt, DATA_PACKET *dpk)
{
 const char *report;
 sexCodes(data->sex, 1);
 if ( dpk->chart_code & TRANS_CH ) {
    report = getKey(CHT_TRANS_YB, 0 );
    if ( report == NULL )
       return( -1 );
    title( data->name, data->name, cmt, (char *)report );
    }
 report = getKey( CHH_BIRTH, 0);
 if ( report == NULL )
    return( -1 );
 birthHeader( mode, data,
	      data->name, house_mode, dpk, (char *)report  );

 if ( mode & NOBIRTHTIM ) {
    report = getKey( CHH_RECT, 0 );
    if ( report == NULL )
       return( -1 );
    rectHeader( dpk->rdp, data->name, (char *)report );
    }
 if ( house_mode != -1 ) {
    report = getKey( CHH_TS_HOUSE, 0 );
    if ( report == NULL )
       return( -1 );
    tsHouseMode( data->name, mode, house_mode, (char *)report );
    }
 if ( dpk->chart_code & RELOC_CH ) {
    report = getKey( CHH_RELOC_DAT, 0 );
    if ( report == NULL )
       return( -1 );
    relocHeader( data->name, dpk, (char *)report );
    }

 if ( dpk->chart_code & PROGR_CH ) {
    if ( ( report = getKey( CHH_PROG, 0 ) ) == NULL )
       return( -1 );
    progHeader( data->name, dpk, (char *)report );
    }
 if ( dpk->chart_code & SOLAR_CH ) {
    if ( ( report = get_report( CHSO_DATA, 0 ) ) == NULL )
       return( -1 );
    m_stream << "\x80\x80";
	solarHeader( data->name, dpk, (char *)report );
    }

 return( m_stream.good() );
}

bool ReportManager::compHeadGroup( BITS mode, BIRTH_DB *data,
    BIRTH_DB *padata, int house_mode, char *cmt,
					   DATA_PACKET *dpk )
{
 const char *report;

 report = getKey( table, CHH_MALE, 0 );
 sexCodes(data->sex, 1);
 sexCodes(padata->sex, 2);
 report = getKey(CHH_COMPAT_YB);
 if ( report == NULL )
    return( -1 );
 title( data->name, padata->name, cmt, (char *)report );

 if ( ( report = getKey(CHH_BIRTH, 0)) == NULL )
    return( -1 );
 birthHeader( mode, data,
	      data->name, house_mode, dpk, (char *)report  );

 if ( mode & NOBIRTHTIM ) {
    if ( ( report = get_key(CHH_RECT ) ) == NULL )
       return( -1 );
    rectHeader( dpk->rdp, data->name, (char *)report );
    }

 if ( ( report = getKey( CHH_COMPAT_YB, 0 ) ) == NULL )
    return( -1 );
 title( padata->name, data->name, cmt, (char *)report );

 if ( ( report = getKey CHH_BIRTH, 0 ) ) == NULL )
    return( -1 );
 birthHeader( mode, padata,
	      padata->name, house_mode, dpk, (char *)report  );

 if ( mode & NOBIRTHTIM ) {
    if ( ( report = getKey( CHH_RECT, 0 ) ) == NULL )
       return( -1 );
    rectHeader( dpk->crdp, padata->name, (char *)report );
    }

 if ( ( report = getKey( CHH_TS_HOUSE, 0 ) ) == NULL )
    return( -1 );
 tsHouseMode( data->name, mode, house_mode, (char *)report );

 if ( dpk->chart_code & RELOC_CH ) {
    if ( ( report = getKey( CHH_RELOC_DAT, 0 ) ) == NULL )
       return( -1 );
    relocHeader( data->name, dpk, (char *)report );
    }

 if ( dpk->chart_code & PROGR_CH ) {
    if ( ( report = getKey( CHH_PROG, 0 ) ) == NULL )
       return( -1 );
    progHeader( data->name, dpk, (char *)report );
    }
 return( m_stream.good() );
}


bool ReportManager::transHeadGroup( BITS mode, BIRTH_DB *data, char *cmt,int house_mode, char *name, DATA_PACKET *dpk )
{
 const char *report;

 if ( ( report = getKey(CHT_TRANS_TD, 0 ) ) == NULL )
    return( -1 );
 title( name, data->name, cmt, (char *)report );

 if ( ( report = getKey( CHH_BIRTH, 0 ) ) == NULL )
    return( -1 );
 birthHeader( mode, data,
	      data->name, house_mode, dpk, (char *)report  );
 if ( mode & NOBIRTHTIM ) {
    if ( ( report = getKey( CHH_RECT ) ) == NULL )
       return( -1 );
    rectHeader( dpk->rdp, data->name, (char *)report );
    }
 if ( house_mode != -1 ) {
    if ( ( report = getKey(CHH_TS_HOUSE ) ) == NULL )
       return( -1 );
    tsHouseMode(data->name, mode, house_mode, (char *)report );
    }
 if ( dpk->chart_code & RELOC_CH ) {
    if ( ( report = getKey( CHH_RELOC_DAT, 0 ) ) == NULL )
       return( -1 );
    relocHeader( data->name, dpk, (char *)report );
    }
 if ( dpk->chart_code & PROGR_CH ) {
    if ( ( report = getKey( CHH_PROG, 0 ) ) == NULL )
       return( -1 );
    progHeader( data->name, dpk, (char *)report );
    }
 if ( ( report = getKey( CHT_TRANS_PARAM, 0 ) ) == NULL )
    return( -1 );
 transHeader(name, dpk, (char *)report );
 return( 0 );
}


extern void do_house_sign( DEGR minutes, int *minor, int *sign, int *cusp );
extern const char *nh_pla_str( int planet );
bool ReportManager::midpointSign( NUM planet, MIDPT *ptr, char *s1, char *rpt, int type )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       caps( planet_str( ptr->second_planet ), buf );
	       break;
	  case '3' :
	       number( 2, ptr->minor_degrees );
	       break;
	  case '4' :
	       zeroFillNumber( 0, ptr->minor_minutes );
	       break;
	  case '5' :
	       caps( sign_str( ptr->sign ), buf );
	       break;
	  case '6' :
	  case '7' :
	  case '8' :
	       p = boolQuery( ptr->cusp!=-1, p );
	       cap = 0;
	       break;
	  case '9' :
	       if ( ptr->cusp != -1 )
		  caps( sign_str( ptr->cusp ), buf );
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       m_stream << format_degs( ptr->total_minutes, buf ) ;
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'C' :
	  case 'c' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'D' :
	  	  case 'd' :
	  	       switch( type ) {


	  		     case ARABP_DI :
	  			  caps( arabic_part_str( planet ), buf );
	  			  break;
	  		     case FIXED_DI :
	  			  caps( fixed_star_str( planet ), buf );
	  			  break;
	  		     case HELIO_DI :
	  			  caps( nh_pla_str( planet ), buf );
	  			  break;

	  		     default :
	  			  cap = 0;
	  			  break;
		     }
		  case 'E' :
		  case 'e' :
		  	switch( type ) {


		  	  	  case ARABP_DI :
		  	  	    caps( arabic_part_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case FIXED_DI :
		  	  	    caps( fixed_star_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case HELIO_DI :
		  	  	    caps( nh_pla_str( ptr->second_planet ), buf );
		  	  	    break;

		  	  	  default :
		  	  		 cap = 0;
		  	  	     break;
		  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::midpointHouse( NUM planet, MIDPT *ptr, char *s1, char *rpt, int type )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       caps( planet_str( ptr->second_planet ), buf );
	       break;
	  case '3' :
	       number( 2, ptr->house );
	       break;
	  case '4' :
           caps( number_str( ptr->house ), buf );
	       break;
	  case '5' :
	  case '6' :
	       p = boolQuery( ptr->house_cusp, p );
	       break;
	  case '7' :
	  case '8' :
	       p = boolQuery( ptr->intercepted, p );
	       break;
	  case '9' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(m_stream,cap,s1);
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	  	       switch( type ) {

	  		     case ARABP_DI :
                  caps( arabic_part_str( planet ), buf );
	  			  break;
	  		     case FIXED_DI :
	  			  caps( fixed_star_str( planet ), buf );
	  			  break;
	  		     case HELIO_DI :
	  			  caps( nh_pla_str( planet ), buf );
	  			  break;

	  		     default :
	  			  cap = 0;
	  			  break;
		     }
		case 'C' :
		case 'c' :
		  	switch( type ) {


		  	  	  case ARABP_DI :
		  	  	    caps( arabic_part_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case FIXED_DI :
		  	  	    caps( fixed_star_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case HELIO_DI :
		  	  	    caps( nh_pla_str( ptr->second_planet ), buf );
		  	  	    break;

		  	  	  default :
		  	  		 cap = 0;
		  	  	     break;
		  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::planetHouse( NUM planet, AS_INF *ptr, char *s1, char *s2, char *rpt, int type )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       number( 2, ptr->house );
	       break;
	  case '3' :
	       caps( number_str( ptr->house ), buf );
	       break;
	  case '4' :
	  case '5' :
	       p = boolQuery( ptr->house_cusp, p );
	       break;
	  case '6' :
	  case '7' :
	       p = boolQuery( ptr->intercepted, p );
	       break;
	  case '8' :
	       enquoteCaps( s1, buf );
	       break;
	  case '9' :
	       enquoteCaps( s2, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	  	  switch( type ) {

	  	  		     case ARABP_DI :
	  	  			  caps( arabic_part_str( planet ), buf );
	  	  			  break;
	  	  		     case FIXED_DI :
	  	  			  caps( fixed_star_str( planet ), buf );
	  	  			  break;
	  	  		     case HELIO_DI :
	  	  			  caps( nh_pla_str( planet ), buf );
	  	  			  break;
	  	  		     default :
	  	  			  cap = 0;
	  	  			  break;
	  		     }
	      case 'C' :
	  	  case 'c' :
	  	       firstName(cap,s2);
	  	       cap = 0;
	       break;

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::planetSign( NUM planet, AS_INF *ptr, int type, void *data, BITS mode, char *s1, char *s2, char *rpt )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int cap = 0;
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n',m_stream);
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       number( 2, ptr->degree_minor );
	       break;
	  case '3' :
	       zeroFillNumber( 0, ptr->minutes_minor );
	       break;
	  case '4' :
	       caps( sign_str( ptr->sign ), buf );
	       break;
	  case '5' :
	  case '6' :
	  case '7' :
	       p = boolQuery( ptr->cusp!=-1, p );
	       break;
	  case '8' :
	       if ( ptr->cusp != -1 )
		  caps( sign_str( ptr->cusp ), buf );
	       break;
	  case '9' :
	       m_stream << format_degs( ptr->minutes_total, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       caps( motion_str( ptr->retrograde ), buf );
	       break;
	  case 'B' :
	  case 'b' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       ar[ptr->retrograde] = 1;
	       ar2[ptr->retrograde] = 1;
	       p = mintQuery( ar, ar2, 3, p );
	       break;
	  case 'C' :
	  case 'c' :
	  case 'D' :
	  case 'd' :
	       p = boolQuery( mode & MISCELL, p );
	       break;
	  case 'E' :
	  case 'e' :
	       if ( mode & MISCELL )
		  caps( number_str( ptr->misc_code & 3 ), buf );
	       break;
	  case 'F' :
	  case 'f' :
	  case 'G' :
	  case 'g' :
	       p = boolQuery( mode & MISCELL &&
					     ptr->misc_code & CRITICAL, p );
	       break;
	  case 'H' :
	  case 'h' :
	  case 'I' :
	  case 'i' :
	       p = boolQuery( mode & MISCELL &&
					     ptr->misc_code & ANARET_DEG, p );
	       break;
	  case 'J' :
	  case 'j' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'K' :
	  case 'k' :
	       switch( type ) {
		     case MONTH_DI :
			  caps( month_str( (int)data ), buf );
			  break;
		     case DATES_DP :
			  m_stream << make_date((struct DATES *)data, buf) ;
			  cap = 0;
			  break;
		     case ARABP_DI :
			  caps( arabic_part_str( (int)data ), buf );
			  break;
		     case FIXED_DI :
			  caps( fixed_star_str( (int)data ), buf );
			  break;
		     case HELIO_DI :
			  caps( nh_pla_str( (int)data ), buf );
			  break;
		     default :
			  cap = 0;
			  break;
		     }
	       break;
	  case 'L' :
	  case 'l' :
	       if ( type == DATES_DP ) {
		  number( 2, ((struct DATES *)data)->month );
		  }
	       else
		  cap = 0;
	       break;
	  case 'M' :
	  case 'm' :
	       if ( type == DATES_DP ) {
		  zeroFillNumber( 2, ((struct DATES *)data)->day );
		  }
	       else
		  cap = 0;
	       break;
	  case 'N' :
	  case 'n' :
	       if ( type == DATES_DP ) {
		  zeroFillNumber( 4, ((struct DATES *)data)->year );
		  }
	       else
		  cap = 0;
	       break;
	  case 'O' :
	  case 'o' :
	       if ( type == DATES_DP ) {
		  caps(
			 month_str( ((struct DATES *)data)->month ), buf );
		  }
	       else
		  cap = 0;
	       break;
	  case 'P' :
	  case 'p' :
	       caps( s2, buf );
	       break;
          case 'Q' :
	  case 'q' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'R' :
	  case 'r' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
/*

	  case 'S' :
	  case 's' :
	       p = boolQuery( mode & MISCELL &&
			   ptr->misc_code & VOID_CRSE, p );
	       cap = 0;
	       break;

*/
	  case 'T' :
	  case 't' :
		  zeroFillNumber( 2, planet );
		  break;
	  case 'U' :
	  case 'u' :
		  zeroFillNumber( 2, ptr->sign );
		  break;
	  case 'V' :
	  case 'v' :
		  number( 2, (short)ptr->longitude );
		  break;
	  case 'W' :
	  case 'w' :
		  zeroFillNumber( 3, ptr->dec_degrees );
		  break;
	  case 'X' :
	  case 'x' :
		  number( 3, ptr->dec_degrees );
		  break;
	  case 'Y' :
	  case 'y' :
		  number( 2, ptr->dec_minutes_minor );
		  break;
	  case 'Z' :
	  case 'z' :
		  zeroFillNumber( 2, ptr->dec_minutes_minor );
		  break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}



bool ReportManager::planetSignExt( NUM planet, AS_INF_EXT *aie, char *s1,  char *rpt, int type )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int cap = 0;
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       number( 1, aie->decan );
	       break;
	  case '2' :
	       caps( number_str( aie->decan ), buf );
	       break;
	  case '3' :
	       caps( planet_str( aie->decan_ruler ), buf );
	       break;
	  case '4' :
	  case '5' :
	       p = boolQuery( aie->decan_ruler2 != -1, p );
	       break;
	  case '6' :
	       if ( aie->decan_ruler2 != -1 )
		  caps( planet_str( aie->decan_ruler2 ), buf );
	       break;
	  case '7' :
	       number( 2, aie->navasma );
	       break;
	  case '8' :
	       caps( number_str( aie->navasma ), buf );
	       break;
	  case '9' :
           caps( sign_str( aie->navasma_sign ), buf );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, aie->duad );
	       break;
	  case 'B' :
	  case 'b' :
	       caps( number_str( aie->duad ), buf );
	       break;
	  case 'C' :
	  case 'c' :
	       caps( planet_str( aie->duad_ruler ), buf );
	       break;
	  case 'D' :
	  case 'd' :
	  case 'E' :
	  case 'e' :
	       p = boolQuery( aie->duad_ruler2 != -1, p );
	       break;
	  case 'F' :
	  case 'f' :
	       if ( aie->duad_ruler2 != -1 )
		  caps( planet_str( aie->duad_ruler2 ), buf );
	       break;
	  case 'G' :
	  case 'g' :
	  case 'H' :
	  case 'h' :
	       p = boolQuery( aie->flags & IS_COMBUST, p );
	       break;
	  case 'I' :
	  case 'i' :
	  case 'J' :
	  case 'j' :
	       p = boolQuery( aie->flags & IS_HOME, p );
	       break;
	  case 'K' :
	  case 'k' :
	  case 'L' :
	  case 'l' :
	       p = boolQuery( aie->flags & IS_DETRIMENT, p );
	       break;
	  case 'M' :
	  case 'm' :
	  case 'N' :
	  case 'n' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if ( aie->flags & IS_EXACT && aie->flags & IS_EXALTED ) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( aie->flags & IS_EXALTED ) {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       else {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       p = mintQuery( ar, ar2, 3, p );
	       break;
	  case 'O' :
	  case 'o' :
	  case 'P' :
	  case 'p' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if ( aie->flags & IS_EXACT && aie->flags & IS_FALL ) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( aie->flags & IS_FALL ) {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       else {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       p = mintQuery( ar, ar2, 3, p );
	       break;
	  case 'Q' :
	  case 'q' :
	  case 'R' :
	  case 'r' :
	       p = boolQuery( aie->flags & IS_RULER, p );
	       break;
	  case 'S' :
	  case 's' :
	       if ( aie->flags & IS_RULER )
            caps( planet_str( planet ), buf );
	       break;
	  case 'T' :
	  case 't' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'U' :
	  case 'u' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'V' :
	  case 'v' :
	  	   switch( type ) {


	  	  		     case ARABP_DI :
	  	  			  caps( arabic_part_str( planet ), buf );
	  	  			  break;
	  	  		     case FIXED_DI :
	  	  			  caps( fixed_star_str( planet ), buf );
	  	  			  break;
	  	  		     case HELIO_DI :
	  	  			  caps( nh_pla_str( planet ), buf );
	  	  			  break;

	  	  		     default :
	  	  			  cap = 0;
	  	  			  break;
	  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::houseSign( NUM house, DEGR minutes, int *pcusp, int *psign, char *s1, char *rpt )
{
 int cap = 0, sign, cusp, minor;
 char buf[80];
 char *p = rpt;

 house_sign( minutes, &minor, &sign, &cusp );
 *pcusp = cusp;
 *psign = sign;
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       number( 2, house );
	       break;
	  case '2' :
	       number( 2, minor );
	       break;
	  case '3' :
	       caps( sign_str( sign ), buf );
	       break;
	  case '4' :
	  case '5' :
	  case '6' :
	       p = boolQuery( cusp!=-1, p );
	       break;
	  case '7' :
	       if ( cusp != -1 )
		   caps( sign_str( cusp ), buf );
	       break;
	  case '8' :
	       caps( number_str( house ), buf );
	       break;
	  case '9' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'A' :
	  case 'a' :
           firstName(cap,s1);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool  ReportManager::transitId( int transit, DATES *d, char *s1, char *s2, char *rpt )
{
 int cap = 0, ar[3], ar2[3];
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       number( 2, transit );
	       break;
	  case '2' :
	       caps( make_date( d, buf ) );
	       break;
	  case '3' :
	       number( 2, d->month );
	       break;
	  case '4' :
	       zeroFillNumber( 2, d->day );
	       break;
	  case '5' :
	       zeroFillNumber( 4, d->year );
	       break;
	  case '6' :
	       caps( month_str( d->month ), buf );
	       break;
	  case '7' :
           enquoteCaps( s1, buf );
	       break;
	  case '8' :
	       enquoteCaps( s2, buf );
	       break;
	  case '9' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::tsHouseMode( char *s1, int mode, int house_mode, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps(s1, buf);
	       break;
	  case '2' :
	       p = boolQuery( ( mode & SIDEREAL ), p );
	       cap = 0;
	       break;
	  case '3' :
	       {
	       //ResStrBlock hm(SB_HOUSE);
	       caps(housmod[house_mode]/*hm[house_mode]*/, buf );
	       }
	       break;
	  case '4' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::relocHeader( char *s1, DATA_PACKET *dpk, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
           if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps(s1,buf);
	       break;
	  case '2' :
	       enquoteCaps(dpk->relocp->country, buf);
	       break;
	  case '3' :
	       enquoteCaps(dpk->relocp->state, buf);
	       break;
	  case '4' :
	       enquoteCaps(dpk->relocp->location,buf);
	       break;
	  case '5' :
	       number( 2, dpk->relocp->latitude.degrees );
	       break;
	  case '6' :
	       cap = 1;
	       number( 2, dpk->relocp->latitude.minutes );
	       break;
	  case '7' :
	       m_stream.put( dpk->relocp->latitude.dir );
	       cap = 0;
	       break;
	  case '8' :
	       p = boolQuery( dpk->relocp->latitude.dir=='N', p );
	       cap = 0;
	       break;
	  case '9' :
	       number( 2, dpk->relocp->longitude.degrees );
	       break;
	  case 'A' :
	  case 'a' :
	       cap = 1;
	       number( 2, dpk->relocp->longitude.minutes );
	       break;
	  case 'B' :
	  case 'b' :
	       m_stream.put( dpk->relocp->longitude.dir );
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       p = boolQuery( dpk->relocp->longitude.dir=='W', p );
	       cap = 0;
	       break;
	  case 'D' :
	  case 'd' :
	       {
	       //ResStrBlock tz(SB_TZONE);
	       caps( timezones[dpk->relocp->time_zone]/*tz[dpk->relocp->time_zone]*/, buf );
	       }
	       break;
	  case 'E' :
	  case 'e' :
	       {
	      // ResStrBlock sc(SB_SPECC);
	       caps( speccodes[dpk->relocp->special_code]/*sc[dpk->relocp->special_code]*/, buf );
	       }
	       break;
	       case 'F' :
	  case 'f' :
	       number( 2, dpk->relocp->hrs_offset);
	       break;
	  case 'G' :
	  case 'g' :
	       number( 2, dpk->relocp->min_offset);
	       break;
	  case 'H' :
	  case 'h' :
	       cap = 1;
	       number( 2, dpk->relocp->hrs_offset);
	       break;
	  case 'I' :
	  case 'i' :
	       cap = 1;
	       number( 2, dpk->relocp->min_offset);
	       break;
	  case 'J' :
	  case 'j' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}



bool ReportManager::progHeader( char *s1, DATA_PACKET *dpk, char *rpt )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int psys;
 int cap = 0;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
           if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps(s1,buf);
	       break;
	  case '2' :
	       number(2, dpk->pdp->offset.year );
	       break;
	  case '3' :
	       number( 2, dpk->pdp->offset.month );
	       break;
	  case '4' :
	       number( 2, dpk->pdp->offset.day );
	       break;
	  case '5' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       psys = dpk->pdp->progress_system;
	       if ( psys >= 100 )
		  psys -= 100;
	       ar[psys] = 1;
	       ar2[psys] = 1;
	       p = mintQuery( ar, ar2, 3, p );
	       cap = 0;
	       break;
	  case '6' :
	       zeroFillNumber(2, dpk->pdp->offset.year );
	       break;
	  case '7' :
	       zeroFillNumber( 2, dpk->pdp->offset.month );
	       break;
	  case '8' :
	       zeroFillNumber(2, dpk->pdp->offset.day );
	       break;
	  case '9' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       p = boolQuery( dpk->pdp->progress_system>=100, p );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::solarHeader( char *s1, DATA_PACKET *dpk, char *rpt )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int psys;
 int cap = 0;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps(s1,buf);
	       break;
	  case '2' :
	       number(2, dpk->ddp->direction.year );
	       break;
	  case '3' :
	       number( 2, dpk->ddp->direction.month );
	       break;
	  case '4' :
	       number( 2, dpk->ddp->direction.day );
	       break;
	  case '5' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       psys = dpk->ddp->direct_system;
	       if ( psys >= 100 )
		      psys -= 100;
	       ar[psys] = 1;
	       ar2[psys] = 1;
	       p = mintQuery( ar, ar2, 3, p );
	       cap = 0;
	       break;
	  case '6' :
	       zeroFillNumber(4, dpk->ddp->direction.year );
	       break;
	  case '7' :
	       zeroFillNumber( 2, dpk->ddp->direction.month );
	       break;
	  case '8' :
	       zeroFillNumber( 2, dpk->ddp->direction.day );
	       break;
	  case '9' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       p = boolQuery( dpk->ddp->direct_system>=100, p );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::transHeader(char *s1, DATA_PACKET *dpk, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       number( 2, dpk->tdp->num_transits );
	       break;
	  case '2' :
	       caps( planet_str( dpk->tdp->start_planet ), buf );
	       break;
	  case '3' :
	       caps( planet_str( dpk->tdp->end_planet ), buf );
	       break;
	  case '4' :
	       number( 2, dpk->tdp->interval_date.month );
	       break;
	  case '5' :
	       number( 2, dpk->tdp->interval_date.day );
	       break;
	  case '6' :
	       enquoteCaps( s1, buf );
	       break;
	  case '7' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::printCusp( int i, short *house_cusps, char *rpt )
{
 int cap = 0;
 char b[12];
 char buf[25];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       putc( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
	  case '\0' :
	       return( 1 );
	       break;
	  case '_' :
	       putc( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       zeroFillNumber( 2, i );
	       break;
	  case '2' :
	       sprintf( buf, "%-7.7s", format_degs(house_cusps[i], b) );
	       m_stream << buf;
	       cap = 0;
	       break;
	  case '3' :
	       zeroFillNumber(2, i+1 );
	       break;
	  case '4' :
	       sprintf( buf, "%-7.7s", format_degs(house_cusps[i+1], b) );
	       m_stream << buf;
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( 1 );
}

bool ReportManager::printCusps(short *house_cusps, char *rpt )
{
 int x;

 for ( x = 1; x <= 12; x += 2 )
     printCusp( x, house_cusps, rpt );
 return( m_stream.good() );
}

bool ReportManager::scoutPlanet( char *s1, char *s2, int sp, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       caps( planet_str(sp), buf );
	       break;
	  case '4' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::summGenders( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, genders.masculine );
	       break;
	  case '4' :
	       number( 2, genders.feminine );
	       break;
	  case '5' :
	       number( 2, comp_genders.masculine );
	       break;
	  case '6' :
	       number( 2, comp_genders.feminine );
	       break;
	  case '7' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case '8' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::summElements(char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, elements.fire );
	       break;
	  case '4' :
	       number( 2, elements.earth );
	       break;
	  case '5' :
	       number( 2, elements.air  );
	       break;
	  case '6' :
	       number( 2, elements.water  );
	       break;
	  case '7' :
	       number( 2, comp_elements.fire  );
	       break;
	  case '8' :
	       number( 2, comp_elements.earth  );
	       break;
	  case '9' :
	       number( 2, comp_elements.air  );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, comp_elements.water  );
	       break;
	  case 'B' :
	  case 'b' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::summQualities( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, qualities.cardinal );
	       break;
	  case '4' :
	       number( 2, qualities.fixed );
	       break;
	  case '5' :
	       number( 2, qualities._mutable );
	       break;
	  case '6' :
	       number( 2, comp_qualities.cardinal );
	       break;
	  case '7' :
	       number( 2, comp_qualities.fixed );
	       break;
	  case '8' :
	       number( 2, comp_qualities._mutable );
	       break;
	  case '9' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::summHemispheres( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, hemispheres.north );
	       break;
	  case '4' :
	       number( 2, hemispheres.south );
	       break;
	  case '5' :
	       number( 2, hemispheres.east );
	       break;
	  case '6' :
	       number( 2, hemispheres.west );
	       break;
	  case '7' :
	       number( 2, comp_hemispheres.north );
	       break;
	  case '8' :
	       number( 2, comp_hemispheres.south );
	       break;
	  case '9' :
	       number( 2, comp_hemispheres.east );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, comp_hemispheres.west );
	       break;
	  case 'B' :
	  case 'b' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::summFunctionals( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, functionals.individual );
	       break;
	  case '4' :
	       number( 2, functionals.relative );
	       break;
	  case '5' :
	       number( 2, functionals.temporal );
	       break;
	  case '6' :
	       number( 2, functionals.terminal );
	       break;
	  case '7' :
	       number( 2, comp_functionals.individual );
	       break;
	  case '8' :
	       number( 2, comp_functionals.relative );
	       break;
	  case '9' :
	       number( 2, comp_functionals.temporal );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, comp_functionals.terminal );
	       break;
	  case 'B' :
	  case 'b' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::summModals( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, modals.cadent );
	       break;
	  case '4' :
	       number( 2, modals.angular );
	       break;
	  case '5' :
	       number( 2, modals.succedent );
	       break;
	  case '6' :
	       number( 2, comp_modals.cadent );
	       break;
	  case '7' :
	       number( 2, comp_modals.angular );
	       break;
	  case '8' :
	       number( 2, comp_modals.succedent );
	       break;
	  case '9' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::aspectCount( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, aspect_count[CONJUNCT] );
	       break;
	  case '4' :
	       number( 2, aspect_count[SEXTILE] );
	       break;
	  case '5' :
	       number( 2, aspect_count[TRINE] );
	       break;
	  case '6' :
	       number( 2, aspect_count[OPPOSITION] );
	       break;
	  case '7' :
	       number( 2, aspect_count[SQUARED] );
	       break;
	  case '8' :
	       number( 2, aspect_count[SEMISEXT] );
	       break;
	  case '9' :
	       number( 2, aspect_count[SEMISESQUAD] );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, aspect_count[SEMISQUARE] );
	       break;
	  case 'B' :
	  case 'b' :
	       number( 2, aspect_count[QUINCUNX] );
	       break;
	  case 'C' :
	  case 'c' :
	       number( 2, aspect_count[BIQUINTILE] );
	       break;
	  case 'D' :
	  case 'd' :
	       number( 2, aspect_count[QUINTILE] );
	       break;
	  case 'E' :
	  case 'e' :
	       number( 2, aspect_count[TREDECILE] );
	       break;
	  case 'F' :
	  case 'f' :
	       number( 2, aspect_count[DECILE] );
	       break;
	  case 'G' :
	  case 'g' :
	       number( 2, aspect_count[SEPTILE] );
	       break;
	  case 'H' :
	  case 'h' :
	       number( 2, comp_aspect_count[CONJUNCT] );
	       break;
	  case 'I' :
	  case 'i' :
	       number( 2, comp_aspect_count[SEXTILE] );
	       break;
	  case 'J' :
	  case 'j' :
	       number( 2, comp_aspect_count[TRINE] );
	       break;
	  case 'K' :
	  case 'k' :
	       number( 2, comp_aspect_count[OPPOSITION] );
	       break;
	  case 'L' :
	  case 'l' :
	       number( 2, comp_aspect_count[SQUARED] );
	       break;
	  case 'M' :
	  case 'm' :
	       number( 2, comp_aspect_count[SEMISEXT] );
	       break;
	  case 'N' :
	  case 'n' :
	       number( 2, comp_aspect_count[SEMISESQUAD] );
	       break;
	  case 'O' :
	  case 'o' :
	       number( 2, comp_aspect_count[SEMISQUARE] );
	       break;
	  case 'P' :
	  case 'p' :
	       number( 2, comp_aspect_count[QUINCUNX] );
	       break;
	  case 'Q' :
	  case 'q' :
	       number( 2, comp_aspect_count[BIQUINTILE] );
	       break;
	  case 'R' :
	  case 'r' :
	       number( 2, comp_aspect_count[QUINTILE] );
	       break;
	  case 'S' :
	  case 's' :
	       number( 2, comp_aspect_count[TREDECILE] );
	       break;
	  case 'T' :
	  case 't' :
	       number( 2, comp_aspect_count[DECILE] );
	       break;
	  case 'U' :
	  case 'u' :
	       number( 2, comp_aspect_count[SEPTILE] );
	       break;
	  case 'V' :
	  case 'v' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'W' :
	  case 'w' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::signCount( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, sign_count[ARIES] );
	       break;
	  case '4' :
	       number( 2, sign_count[TAURUS] );
	       break;
	  case '5' :
	       number( 2, sign_count[GEMINI] );
	       break;
	  case '6' :
	       number( 2, sign_count[CANCER] );
	       break;
	  case '7' :
	       number( 2, sign_count[LEO] );
	       break;
	  case '8' :
	       number( 2, sign_count[VIRGO] );
	       break;
	  case '9' :
	       number( 2, sign_count[LIBRA] );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, sign_count[SCORPIO] );
	       break;
	  case 'B' :
	  case 'b' :
	       number( 2, sign_count[SAGITARIUS] );
	       break;
	  case 'C' :
	  case 'c' :
	       number( 2, sign_count[CAPRICORN] );
	       break;
	  case 'D' :
	  case 'd' :
	       number( 2, sign_count[AQUARIUS] );
	       break;
	  case 'E' :
	  case 'e' :
	       number( 2, sign_count[PISCES] );
	       break;
	  case 'F' :
	  case 'f' :
	       number( 2, comp_sign_count[ARIES] );
	       break;
	  case 'G' :
	  case 'g' :
	       number( 2, comp_sign_count[TAURUS] );
	       break;
	  case 'H' :
	  case 'h' :
	       number( 2, comp_sign_count[GEMINI] );
	       break;
	  case 'I' :
	  case 'i' :
	       number( 2, comp_sign_count[CANCER] );
	       break;
	  case 'J' :
	  case 'j' :
	       number( 2, comp_sign_count[LEO] );
	       break;
	  case 'K' :
	  case 'k' :
	       number( 2, comp_sign_count[VIRGO] );
	       break;
	  case 'L' :
	  case 'l' :
	       number( 2, comp_sign_count[LIBRA] );
	       break;
	  case 'M' :
	  case 'm' :
	       number( 2, comp_sign_count[SCORPIO] );
	       break;
	  case 'N' :
	  case 'n' :
	       number( 2, comp_sign_count[SAGITARIUS] );
	       break;
	  case 'O' :
	  case 'o' :
	       number( 2, comp_sign_count[CAPRICORN] );
	       break;
	  case 'P' :
	  case 'p' :
	       number( 2, comp_sign_count[AQUARIUS] );
	       break;
	  case 'Q' :
	  case 'q' :
	       number( 2, comp_sign_count[PISCES] );
	       break;
	  case 'R' :
	  case 'r' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'S' :
	  case 's' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::houseCount( char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       enquoteCaps( s1, buf );
	       break;
	  case '2' :
	       enquoteCaps( s2, buf );
	       break;
	  case '3' :
	       number( 2, house_count[1] );
	       break;
	  case '4' :
	       number( 2, house_count[2] );
	       break;
	  case '5' :
	       number( 2, house_count[3] );
	       break;
	  case '6' :
	       number( 2, house_count[4] );
	       break;
	  case '7' :
	       number( 2, house_count[5] );
	       break;
	  case '8' :
	       number( 2, house_count[6] );
	       break;
	  case '9' :
	       number( 2, house_count[7] );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, house_count[8] );
	       break;
	  case 'B' :
	  case 'b' :
	       number( 2, house_count[9] );
	       break;
	  case 'C' :
	  case 'c' :
	       number( 2, house_count[10] );
	       break;
	  case 'D' :
	  case 'd' :
	       number( 2, house_count[11] );
	       break;
	  case 'E' :
	  case 'e' :
	       number( 2, house_count[12] );
	       break;
	  case 'F' :
	  case 'f' :
	       number( 2, comp_house_count[1] );
	       break;
	  case 'G' :
	  case 'g' :
	       number( 2, comp_house_count[2] );
	       break;
	  case 'H' :
	  case 'h' :
	       number( 2, comp_house_count[3] );
	       break;
	  case 'I' :
	  case 'i' :
	       number( 2, comp_house_count[4] );
	       break;
	  case 'J' :
	  case 'j' :
	       number( 2, comp_house_count[5] );
	       break;
	  case 'K' :
	  case 'k' :
	       number( 2, comp_house_count[6] );
	       break;
	  case 'L' :
	  case 'l' :
	       number( 2, comp_house_count[7] );
	       break;
	  case 'M' :
	  case 'm' :
	       number( 2, comp_house_count[8] );
	       break;
	  case 'N' :
	  case 'n' :
	       number( 2, comp_house_count[9] );
	       break;
	  case 'O' :
	  case 'o' :
	       number( 2, comp_house_count[10] );
	       break;
	  case 'P' :
	  case 'p' :
	       number( 2, comp_house_count[11] );
	       break;
	  case 'Q' :
	  case 'q' :
	       number( 2, comp_house_count[12] );
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::sexCodes( int sex, int sexno )
{
 char buf[10];
 sprintf( buf, "^%d", sexno );
 m_stream << buf;
 if ( sex )
    sex = CHH_FEMALE;
 else
    sex = CHH_MALE;
 char *str = getKey(sex, 0);
 if (str != NULL) {
   m_stream << str;
 }
}

bool ReportManager::midpointSign(NUM planet, MIDPT *ptr,
						     char *s1, char *rpt, int type )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       caps( planet_str( ptr->second_planet ), buf );
	       break;
	  case '3' :
	       number( 2, ptr->minor_degrees );
	       break;
	  case '4' :
	       zeroFillNumber( 0, ptr->minor_minutes );
	       break;
	  case '5' :
	       caps( sign_str( ptr->sign ), buf );
	       break;
	  case '6' :
	  case '7' :
	  case '8' :
	       p = boolQuery( ptr->cusp!=-1, p );
	       cap = 0;
	       break;
	  case '9' :
	       if ( ptr->cusp != -1 )
            caps( sign_str( ptr->cusp ), buf );
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       m_stream << format_degs( ptr->total_minutes, buf );
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'C' :
	  case 'c' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'D' :
	  	  case 'd' :
	  	       switch( type ) {


	  		     case ARABP_DI :
	  			  caps( arabic_part_str( planet ), buf );
	  			  break;
	  		     case FIXED_DI :
	  			  caps( fixed_star_str( planet ), buf );
	  			  break;
	  		     case HELIO_DI :
	  			  caps( nh_pla_str( planet ), buf );
	  			  break;

	  		     default :
	  			  cap = 0;
	  			  break;
		     }
		  case 'E' :
		  case 'e' :
                switch( type ) {


		  	  	  case ARABP_DI :
		  	  	    caps( arabic_part_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case FIXED_DI :
		  	  	    caps( fixed_star_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case HELIO_DI :
		  	  	    caps( nh_pla_str( ptr->second_planet ), buf );
		  	  	    break;

		  	  	  default :
		  	  		 cap = 0;
		  	  	     break;
		  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::midpointHouse( NUM planet, MIDPT *ptr,
						    char *s1, char *rpt, int type )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       caps( planet_str( ptr->second_planet ), buf );
	       break;
	  case '3' :
	       number( 2, ptr->house );
	       break;
	  case '4' :
	       caps( number_str( ptr->house ), buf );
	       break;
	  case '5' :
	  case '6' :
	       p = boolQuery( ptr->house_cusp, p );
	       break;
	  case '7' :
	  case '8' :
	       p = boolQuery( ptr->intercepted, p );
	       break;
	  case '9' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	  	       switch( type ) {


	  		     case ARABP_DI :
	  			  caps( arabic_part_str( planet ), buf );
	  			  break;
	  		     case FIXED_DI :
	  			  caps( fixed_star_str( planet ), buf );
	  			  break;
	  		     case HELIO_DI :
	  			  caps( nh_pla_str( planet ), buf );
	  			  break;


	  		     default :
	  			  cap = 0;
	  			  break;
		     }
		case 'C' :
		case 'c' :
		  	switch( type ) {


		  	  	  case ARABP_DI :
		  	  	    caps( arabic_part_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case FIXED_DI :
		  	  	    caps( fixed_star_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case HELIO_DI :
		  	  	    caps( nh_pla_str( ptr->second_planet ), buf );
		  	  	    break;

		  	  	  default :
		  	  		 cap = 0;
		  	  	     break;
		  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}


bool ReportManager::planetHouse( FILE *stream, NUM planet, AS_INF *ptr,
					    char *s1, char *s2, char *rpt, int type )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$' );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  m_stream.put('\n' );
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       number( 2, ptr->house );
	       break;
	  case '3' :
	       caps( number_str( ptr->house ), buf );
	       break;
	  case '4' :
	  case '5' :
	       p = boolQuery( ptr->house_cusp, p );
	       break;
	  case '6' :
	  case '7' :
	       p = boolQuery( ptr->intercepted, p );
	       break;
	  case '8' :
	       enquoteCaps( s1, buf );
	       break;
	  case '9' :
	       enquoteCaps( s2, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	  	  switch( type ) {


	  	  		     case ARABP_DI :
	  	  			  caps( arabic_part_str( planet ), buf );
	  	  			  break;
	  	  		     case FIXED_DI :
	  	  			  caps( fixed_star_str( planet ), buf );
	  	  			  break;
	  	  		     case HELIO_DI :
	  	  			  caps( nh_pla_str( planet ), buf );
	  	  			  break;

	  	  		     default :
	  	  			  cap = 0;
	  	  			  break;
	  		     }
	      case 'C' :
	  	  case 'c' :
	  	       firstName(cap,s2);
	  	       cap = 0;
	       break;

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::planetSign( NUM planet, AS_INF *ptr,
	    void *data, BITS mode, char *s1, char *s2, char *rpt, int type )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int cap = 0;
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$', m_stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n',stream);
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( planet_str( planet ), buf );
	       break;
	  case '2' :
	       number( 2, ptr->degree_minor );
	       break;
	  case '3' :
	       zeroFillNumber( 0, ptr->minutes_minor );
	       break;
	  case '4' :
	       caps( sign_str( ptr->sign ), buf );
	       break;
	  case '5' :
	  case '6' :
	  case '7' :
	       p = boolQuery( ptr->cusp!=-1, p );
	       break;
	  case '8' :
	       if ( ptr->cusp != -1 )
		  caps( sign_str( ptr->cusp ), buf );
	       break;
	  case '9' :
	       m_stream << format_degs( ptr->minutes_total, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       caps( motion_str( ptr->retrograde ), buf );
	       break;
	  case 'B' :
	  case 'b' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       ar[ptr->retrograde] = 1;
	       ar2[ptr->retrograde] = 1;
	       p = mintQuery( ar, ar2, 3, p );
	       break;
	  case 'C' :
	  case 'c' :
	  case 'D' :
	  case 'd' :
	       p = boolQuery( mode & MISCELL, p );
	       break;
	  case 'E' :
	  case 'e' :
	       if ( mode & MISCELL )
		  caps( number_str( ptr->misc_code & 3 ), buf );
	       break;
	  case 'F' :
	  case 'f' :
	  case 'G' :
	  case 'g' :
	       p = boolQuery( mode & MISCELL &&
					     ptr->misc_code & CRITICAL, p );
	       break;
	  case 'H' :
	  case 'h' :
	  case 'I' :
	  case 'i' :
	       p = boolQuery( mode & MISCELL &&
					     ptr->misc_code & ANARET_DEG, p );
	       break;
	  case 'J' :
	  case 'j' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'K' :
	  case 'k' :
	       switch( type ) {
		     case MONTH_DI :
			  caps( month_str( (int)data ), buf );
			  break;
		     case DATES_DP :
			  m_stream << make_date((struct DATES *)data, buf);
			  cap = 0;
			  break;

		     case ARABP_DI :
			  caps( arabic_part_str( (int)data ), buf );
			  break;
		     case FIXED_DI :
			  caps( fixed_star_str( (int)data ), buf );
			  break;
		     case HELIO_DI :
			  caps( nh_pla_str( (int)data ), buf );
			  break;
		     default :
			  cap = 0;
			  break;
		     }
	       break;
	  case 'L' :
	  case 'l' :
	       if ( type == DATES_DP ) {
		  number( 2, ((struct DATES *)data)->month );
		  }
	       else
		  cap = 0;
	       break;
	  case 'M' :
	  case 'm' :
	       if ( type == DATES_DP ) {
		  zeroFillNumber( 2, ((struct DATES *)data)->day );
		  }
	       else
		  cap = 0;
	       break;
	  case 'N' :
	  case 'n' :
	       if ( type == DATES_DP ) {
		  zeroFillNumber( 4, ((struct DATES *)data)->year );
		  }
	       else
		  cap = 0;
	       break;
	  case 'O' :
	  case 'o' :
	       if ( type == DATES_DP ) {
		  caps(
			 month_str( ((struct DATES *)data)->month ), buf );
		  }
	       else
		  cap = 0;
	       break;
	  case 'P' :
	  case 'p' :
	       enquoteCaps( s2, buf );
	       break;
          case 'Q' :
	  case 'q' :
	       firstName(cap,s1);
	       cap = 0;
	       break;
	  case 'R' :
	  case 'r' :
	       firstName(cap,s2);
	       cap = 0;
	       break;
/*

	  case 'S' :
	  case 's' :
	       p = boolQuery( mode & MISCELL &&
			   ptr->misc_code & VOID_CRSE, p );
	       cap = 0;
	       break;

*/
	  case 'T' :
	  case 't' :
		  zeroFillNumber( 2, planet );
		  break;
	  case 'U' :
	  case 'u' :
		  zeroFillNumber( 2, ptr->sign );
		  break;
	  case 'V' :
	  case 'v' :
		  number( 2, (short)ptr->longitude );
		  break;
	  case 'W' :
	  case 'w' :
		  zeroFillNumber( 3, ptr->dec_degrees );
		  break;
	  case 'X' :
	  case 'x' :
		  number( 3, ptr->dec_degrees );
		  break;
	  case 'Y' :
	  case 'y' :
		  number( 2, ptr->dec_minutes_minor );
		  break;
	  case 'Z' :
	  case 'z' :
		  zeroFillNumber( 2, ptr->dec_minutes_minor );
		  break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}



bool ReportManager::planetSignExt( NUM planet, AS_INF_EXT *aie, char *s1, char *rpt, int type )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int cap = 0;
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$');
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n');
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80');
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       number( 1, aie->decan );
	       break;
	  case '2' :
	       caps( number_str( aie->decan ), buf );
	       break;
	  case '3' :
	       caps( planet_str( aie->decan_ruler ), buf );
	       break;
	  case '4' :
	  case '5' :
	       p = boolQuery( aie->decan_ruler2 != -1, p );
	       break;
	  case '6' :
	       if ( aie->decan_ruler2 != -1 )
		  caps( planet_str( aie->decan_ruler2 ), buf );
	       break;
	  case '7' :
	       number( 2, aie->navasma );
	       break;
	  case '8' :
	       caps( number_str( aie->navasma ), buf );
	       break;
	  case '9' :
	       caps( sign_str( aie->navasma_sign ), buf );
	       break;
	  case 'A' :
	  case 'a' :
	       number( 2, aie->duad );
	       break;
	  case 'B' :
	  case 'b' :
	       caps( number_str( aie->duad ), buf );
	       break;
	  case 'C' :
	  case 'c' :
	       caps( planet_str( aie->duad_ruler ), buf );
	       break;
	  case 'D' :
	  case 'd' :
	  case 'E' :
	  case 'e' :
	       p = boolQuery( aie->duad_ruler2 != -1, p );
	       break;
	  case 'F' :
	  case 'f' :
	       if ( aie->duad_ruler2 != -1 )
		  caps( planet_str( aie->duad_ruler2 ), buf );
	       break;
	  case 'G' :
	  case 'g' :
	  case 'H' :
	  case 'h' :
	       p = boolQuery( aie->flags & IS_COMBUST, p );
	       break;
	  case 'I' :
	  case 'i' :
	  case 'J' :
	  case 'j' :
	       p = boolQuery( aie->flags & IS_HOME, p );
	       break;
	  case 'K' :
	  case 'k' :
	  case 'L' :
	  case 'l' :
	       p = boolQuery( aie->flags & IS_DETRIMENT, p );
	       break;
	  case 'M' :
	  case 'm' :
	  case 'N' :
	  case 'n' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if ( aie->flags & IS_EXACT && aie->flags & IS_EXALTED ) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( aie->flags & IS_EXALTED ) {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       else {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       p = mintQuery( ar, ar2, 3, p );
	       break;
	  case 'O' :
	  case 'o' :
	  case 'P' :
	  case 'p' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if ( aie->flags & IS_EXACT && aie->flags & IS_FALL ) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( aie->flags & IS_FALL ) {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       else {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       p = mintQuery( ar, ar2, 3, p );
	       break;
	  case 'Q' :
	  case 'q' :
	  case 'R' :
	  case 'r' :
	       p = boolQuery( aie->flags & IS_RULER, p );
	       break;
	  case 'S' :
	  case 's' :
	       if ( aie->flags & IS_RULER )
		  caps( planet_str( planet ), buf );
	       break;
	  case 'T' :
	  case 't' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'U' :
	  case 'u' :
	       firstName(s1, cap);
	       cap = 0;
	       break;
	  case 'V' :
	  case 'v' :
	  	   switch( type ) {

	  	  		     case ARABP_DI :
	  	  			  caps( arabic_part_str( planet ), buf );
	  	  			  break;
	  	  		     case FIXED_DI :
	  	  			  caps( fixed_star_str( planet ), buf );
	  	  			  break;
	  	  		     case HELIO_DI :
	  	  			  caps( nh_pla_str( planet ), buf );
	  	  			  break;

	  	  		     default :
	  	  			  cap = 0;
	  	  			  break;
	  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}



bool ReportManager::houseSign( NUM house, DEGR minutes, int *pcusp, int *psign, char *s1, char *rpt )
{
 int cap = 0, sign, cusp, minor;
 char buf[80];
 char *p = rpt;

 doHouseSign( minutes, &minor, &sign, &cusp );
 *pcusp = cusp;
 *psign = sign;
 do {
    p = nextArg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$');
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n');
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80');
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       number( 2, house );
	       break;
	  case '2' :
	       number( 2, minor );
	       break;
	  case '3' :
	       caps( sign_str( sign ), buf );
	       break;
	  case '4' :
	  case '5' :
	  case '6' :
	       p = boolQuery( cusp!=-1, p );
	       break;
	  case '7' :
	       if ( cusp != -1 ) {
                caps( sign_str( cusp ), buf );
		   }
	       break;
	  case '8' :
	       caps( number_str( house ), buf );
	       break;
	  case '9' :
	       enquoteCaps( s1, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       firstName(s1, cap);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );
}

bool ReportManager::title( char *s1, char *s2, char *s3, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( p );
    switch( *p++ ) {
	  case '$' :
	       m_stream.put( '$');
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		   m_stream.put('\n');
		   break;
	  case '\0' :
	       return( m_stream.good() );
	       break;
	  case '_' :
	       m_stream.put( '\x80' );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       caps( s1, buf );
	       break;
	  case '2' :
	       caps( s2, buf );
	       break;
	  case '3' :
	       caps( s3, buf );
	       break;
	  case '4' :
	       firstName(s1,cap);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( m_stream.good() );

