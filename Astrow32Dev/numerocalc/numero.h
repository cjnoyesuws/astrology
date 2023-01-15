

extern void file_info_write( FILE *p );
extern void SetChartInfoData( CHART_INFO *h );
extern void compile_numbers(void);
extern FILE *open_file( char *file );
extern int test_errno(void);
extern int CompileReport( int rep, LPSTR n1_file );
extern short get_transfer_text_asp( short row, short col, short deep,
                                         short file_num, FILE *stream );
extern short num_to_arry_offset( short num );
extern short get_text( short row, short col, short file_num, FILE *stream );;
extern short get_gnt( short col, short file_num, FILE *stream  );;
extern void do_mem_error( int fatal );
extern int alert_box( char *title, char *fmt, ... );
extern int alert_box_ext( char *title, UINT options, char *fmt, ... );
extern void do_error( char *file );
extern int valert_box_ext( char *title, UINT options, char *fmt, va_list marker );
extern double julian_date( DATES *dp, short hours, short minutes, short epoch );
extern void do_all_name_numbers( CHART_INFO *cip, NAME_NUMB_GROUP *n );
extern char *replace_ext( char *buf, char *name, char *ext );
extern short do_all_names(NAMEGRF_GRP *n, CHART_INFO *c, NUMBERS *bn, NAME_NUMB_GROUP *nn );
extern void calc_numbers( NUMBERS *n, DATES *d );
extern short num_print_name( FILE *stream, char *head, NAME_NUMBER *np, NAME *nmp );
extern short num_report_print( FILE *stream, CHART_INFO *cip,
		    NUMBERS *np, NAME_NUMB_GROUP *nngp, short head );
extern short pers_print_name( FILE *stream, char *head, NAME_NUMBER *np, NAME *nmp, short file );
extern short full_personality_report_print( FILE *stream, CHART_INFO *cip,
		    NUMBERS *np, NAME_NUMB_GROUP *nngp, short head );
extern void print_name_grafs_num( FILE *stream, CHART_INFO *cip, NAMEGRF_GRP *g, short head, short start, short end);
extern void chart_header_print( FILE *stream, CHART_INFO *cip );
extern void print_name_grafs( FILE *stream, CHART_INFO *cip, NAMEGRF_GRP *g, short head, short start, short end);
extern short reduce_num( char *num_str, short *test );
extern short reduce_int( short num, short *test );
extern short add_ints_reduce( short num1, short num2, short num3, short *test  );
extern short add_digits_reduce( short num1, short num2, short num3, short *test  );
extern short subtract_ints_reduce( short num1, short num2, short *test );
extern char *strclip( char *pStr );
extern void DllExport SetFileInfo( FILE_ID *p );
extern int fdata_write( FILE *stream, unsigned short type );
extern int file_info_write( FILE *stream );
