#ifndef _BIOCHART_HPP_
#define _BIOCHART_HPP_

class BiorythmChartData {
private:
Date birth;
Date start;
char name[100];
public:
      BiorythmChartData();
      ~BiorythmChartData() {}
	  void SetName( char *n ) { strcpy( name, n ); }
	  Date &getBirth() { return birth; }
      Date &getStart() { return start; }
      char *getName() { return name; }
      int save(char *f);
      int load(char *f);
      int export(FILE *stream, int html=0);
      };

#endif /* _BIOCHART_HPP_ */
