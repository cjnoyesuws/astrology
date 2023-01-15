#ifndef ARRAY____HPP_
#define ARRAY____HPP_


class dataArray {
      protected:
      int rows;
      int cols;
      int data_size;
      HGLOBAL handle;
      LPVOID ptr;
      public :
      dataArray() {}
      dataArray( int r, int c, int ds );
      ~dataArray();
      int check() { if ( handle == 0 || ptr == NULL ) return 1; else return 0; }
      LPVOID getPtr( int r, int c );
      };

class dataArray3d : public dataArray {
      int depth;
      int element_size;
      public :
      dataArray3d( int r, int c, int dp, int ds );
      ~dataArray3d() {}
      LPVOID getPtr( int r, int c, int d );
      };

#endif /* ARRAY____HPP_ */

