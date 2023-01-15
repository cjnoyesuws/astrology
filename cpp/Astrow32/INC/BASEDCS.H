#if defined(_MSC_VER) && ( _MSC_VER >= 600 )
#define BCS _based( _segname( "_CODE" ) )
#else
#define BCS _far
#endif

