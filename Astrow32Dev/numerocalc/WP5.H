#pragma pack( 1 )

typedef struct WPheader {
       char id[4];
       long ptr;
       char product;
       char type;
       char maj_v;
       char min_v;
       int  key;
       int  res;
       } WPheader;
#pragma pack()

#define WPID "\xffWPC"


