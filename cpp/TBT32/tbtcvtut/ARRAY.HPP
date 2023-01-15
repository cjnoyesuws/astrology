#ifndef ARRAY____HPP_
#define ARRAY____HPP_


class dataArray {
      protected:
      int rows;
      int cols;
      TXTPT **ptr;
      public :
      dataArray() {}
      dataArray( int r, int c );
      virtual ~dataArray();
      int check() { if ( ptr == NULL ) return 1; else return 0; }
      TXTPT *getPtr( int r, int c );
      };

class dataArray3d : public dataArray {
      int depth;
      int element_size;
      public :
      dataArray3d( int r, int c, int dp );
      virtual ~dataArray3d() {}
      TXTPT *getPtr( int r, int c, int d );
      };

#endif /* ARRAY____HPP_ */

