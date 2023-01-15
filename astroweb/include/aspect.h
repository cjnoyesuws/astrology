
struct ASP_DEF {
    short aspect;
    short degrees;
    short orb;
};


#define CONJUNCT    0
#define SEXTILE     1
#define TRINE       2
#define OPPOSITION  3
#define SQUARED     4
/* full text not produced on these */
#define SEMISEXT    5
#define SEMISQUARE  6
#define SEMISESQUAD 7
#define QUINCUNX    8
#define BIQUINTILE  9
#define QUINTILE    10
#define TREDECILE   11
#define DECILE      12
#define SEPTILE     13
/* basic aspect structure */

extern char asp_map[];
extern int high_asp;
extern ASP_DEF aspect_def[];
extern short inc_hscsp, other_orb, hscsp_orb;
extern int max_asp;
#define NO_ASPECT -999




