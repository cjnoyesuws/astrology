#ifndef _DATE_____HPP_
#define _DATE_____HPP_

class Date {
private:
int month;
int day;
int year;
public:
      Date() { month = 1, day = 1, year = 1900; }
      ~Date() {}
      Date(int m, int d, int y) { set(m,d,y);}
	  void SetDate(COleDateTime &dt);
      int isLeap();
      int daysToMonth();
      int badDate();
      int dayNumber(int st_month);
      int adjust();
      void set(int m, int d, int y) { month = m; day = d; year = y;}
      int &getMonth() { return month; }
      int &getDay() { return day; }
      int &getYear() { return year; }
      double julian(int epoch=1900);
      double baseJulian();
      char *format();
      Date &operator++();
      Date &operator+(int i);
      };

typedef struct CAL_DATA {
      int start_day;
      short no_days;
      } CAL_DATA;

class PerpCalendar {
private :
      CAL_DATA cal_data;
      Date day;
public :
      PerpCalendar( Date &d ) { day = d; getData();  }
      ~PerpCalendar() {}
      void getData();
      int startDay() { return cal_data.start_day; }
      int no_days() { return cal_data.no_days; }
};




#endif /*  _DATE_____HPP_ */
