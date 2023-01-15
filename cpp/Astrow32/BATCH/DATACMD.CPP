
int trans_count( ArgType *pArg, CMD *cm )
{
 int i;

 parseInt( (char *)pArg->get(), "%d", ".", &i );
 if ( i )
    transit_data.num_transits = i;
 return( 0 );
}

int trans_ofs( ArgType *pArg, CMD *cm )
{
 int i, j;

 parsef( (char *)pArg->get(), "%d, %d", ".", &i, &j );
 if ( j ) {
    transit_data.interval_date.month = i;
    transit_data.interval_date.day = j;
    }
 return( 0 );
}

int trans_date( ArgType *pArg, CMD *cm )
{
 int m, d, y;

 parsef( (char *)pArg->get(), "%d/%d/%d", ".", &m, &d, &y );
 trans_rec.birth_data.birth_date.month = m;
 trans_rec.birth_data.birth_date.day = d;
 trans_rec.birth_data.birth_date.year = y;
 return( 0 );
}

int progr_ofs( ArgType *pArg, CMD *cm )
{
 int m, d, y;

 parsef( (char *)pArg->get(), "%d/%d/%d", ".", &y, &m, &d );
 progress_data.offset.month = m;
 progress_data.offset.day = d;
 progress_data.offset.year = y;
 return( 0 );
}

int trans_today( ArgType *pArg, CMD *cm )
{
 struct dosdate_t d;

 _dos_getdate( &d );
 trans_rec.birth_data.birth_date.month = d.month;
 trans_rec.birth_data.birth_date.day = d.day;
 trans_rec.birth_data.birth_date.year = d.year;
 return( 0 );
}


