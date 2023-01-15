#include "stdafx.h"
#include <atlcomtime.h>
#include "date.hpp"

/* Functions for for Perpetual Calendar 1700 - 2108 A.D. */

/* indexes to table below */

enum SEL { A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N };

/* perp_cal[lookup[year-1700]][month] contains .start_day of week, and
   .no_days per month */

CAL_DATA perp_cal[14][12] = {
	  { 3, 31, 6, 28, 6, 31, 2, 30, 4, 31, 0, 30,
	    2, 31, 5, 31, 1, 30, 3, 31, 6, 30, 1, 31 },
	  { 4, 31, 0, 28, 0, 31, 3, 30, 5, 31, 1, 30,
	    3, 31, 6, 31, 2, 30, 4, 31, 0, 30, 2, 31 },
	  { 5, 31, 1, 29, 2, 31, 5, 30, 0, 31, 3, 30,
	    5, 31, 1, 31, 4, 30, 6, 31, 2, 30, 4, 31 },
	  { 0, 31, 4, 28, 3, 31, 6, 30, 1, 31, 4, 30,
	    6, 31, 2, 31, 5, 30, 0, 31, 3, 30, 5, 31 },
	  { 1, 31, 4, 28, 4, 31, 0, 30, 2, 31, 5, 30,
	    0, 31, 3, 31, 6, 30, 1, 31, 4, 30, 6, 31 },
	  { 2, 31, 5, 28, 5, 31, 1, 30, 3, 31, 6, 30,
	    1, 31, 4, 31, 0, 30, 2, 31, 5, 30, 0, 31 },
	  { 3, 31, 6, 29, 0, 31, 3, 30, 5, 31, 1, 30,
	    3, 31, 6, 31, 2, 30, 4, 31, 0, 30, 2, 31 },
	  { 5, 31, 1, 28, 1, 31, 4, 30, 6, 31, 2, 30,
	    4, 31, 0, 31, 3, 30, 5, 31, 1, 30, 3, 31 },
	  { 6, 31, 2, 28, 2, 31, 5, 30, 0, 31, 3, 30,
	    5, 31, 1, 31, 4, 30, 6, 31, 2, 30, 4, 31 },
	  { 1, 31, 4, 29, 5, 31, 1, 30, 3, 31, 6, 30,
	    1, 31, 4, 31, 0, 30, 2, 31, 5, 30, 0, 31 },
	  { 6, 31, 2, 29, 3, 31, 6, 30, 1, 31, 4, 30,
	    6, 31, 2, 31, 5, 30, 0, 31, 3, 30, 5, 31 },
	  { 0, 31, 3, 29, 4, 31, 0, 30, 2, 31, 5, 30,
	    0, 31, 3, 31, 6, 30, 1, 31, 4, 30, 6, 31 },
	  { 2, 31, 5, 29, 6, 31, 2, 30, 4, 31, 0, 30,
	    2, 31, 5, 31, 1, 30, 3, 31, 6, 30, 1, 31 },
	  { 4, 31, 0, 29, 1, 31, 4, 30, 6, 31, 2, 30,
	    4, 31, 1, 31, 3, 30, 5, 31, 1, 30, 3, 31 } };

/* index to table above */

enum SEL lookup[] = {
      H, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, G, H, I, D, J, A, B, H, K, E, F, A,
      N, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, G, H, I, D, J, A, B, H, K, E, F, A,
      N, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, G, H, I, D, J, A, B, H, K, E, F, A,
      N, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, A, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, J, A, B, H, K, E, F, A, N, I,
      D, E, M, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, J, A, B, H, K, E, F, A, N, I,
      D, E, M, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, J, A, B, H, K, E, F, A, N, I,
      D, E, M, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, E, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, H, I, D, E, M, B,
      H, I, L };

/* function to get data from arrays and structures */

void PerpCalendar::getData()
{
 int cal_look;

 cal_look = (int) lookup[day.getYear()-1700];
 cal_data = perp_cal[cal_look][day.getMonth()-1];
}




