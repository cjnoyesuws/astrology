
struct ARAB_PART {
       int base;
       int plus;
       int minus;
       };

#define N_ARAB_PART 25

extern AS_INF *arabic_parts;
extern int arabic_count;

extern AS_INF *getArabicParts(void);
extern int getArabicCount(void);
