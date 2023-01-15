

typedef struct XZ {
	int x;
	int z;
	int xz;
	} XZ;
	
void test( XZ *pXz, int cnt )
{
 XZ *px;
 
 for ( int j = 0, px = pXz; j < cnt; j++, px++ )
     px->x++;
     px->y--;
     px->xy += (px-py);
     }

}
