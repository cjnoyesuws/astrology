// chartengine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "charcons.h"

PROGR_DATA progress_data;
TRANS_DATA transit_data;
RECT_DATA birth_rectd, comp_rectd, trans_rectd;
RETURN_DATA return_data;
BIRTH_DB birth_rec, comp_rec, trans_rec;
LOC_DB reloc_data;
short birth_ok, birth_rect_ok = 1, comp_ok, comp_rect_ok = 1,
    trans_ok, trans_data_ok, prog_ok;
AS_INF near birth_inf[18], near alt_inf[18];
AS_INF_EXT near birth_ext[18], near alt_ext[18];
short near house_cusps[13], near alt_cusps[13];
DATA_PACKET birth_dp = { NATAL_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
comp_dp = { COMPA_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
trans_dp = { TRANS_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, NULL },
progr_dp = { PROGR_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
return_dp = { RETUR_CH, &birth_rectd, NULL, &progress_data, &return_data, NULL, &reloc_data, NULL },
reloc_dp = { RELOC_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
compos_dp = { COMPO_CH|RELOC_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
fixed_dp = { FIXED_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
arabp_dp = { ARABP_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
comptr_dp = { COMPO_CH|TRANS_CH|RELOC_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, &comp_rectd };




int main(int argc, char* argv[])
{
	return 0;
}
