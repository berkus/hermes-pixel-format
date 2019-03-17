/* Everything in here (C)1998 The Rasterman */

#include "Dither.h"



/* Rasterman's dither matrix */

char8 DitherMatrix_44[4][4] =
{
    {0, 4, 1, 5},
    {6, 2, 7, 3},
    {1, 5, 0, 4},
    {7, 3, 6, 2}
};

short16 DitherTab_r565_44[4][4][256];
short16 DitherTab_g565_44[4][4][256];
short16 DitherTab_b565_44[4][4][256];

char8 DitherTab_r332_44[4][4][256];
char8 DitherTab_g332_44[4][4][256];
char8 DitherTab_b332_44[4][4][256];


void Dither_SetupMatrices()
{ int i, x, y;
  
  for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
	{
	  for (i = 0; i < 256; i++)
	    {
	      if ((DitherMatrix_44[x][y] < (i & 0x7)) && (i < (256 - 8))) {
	        DitherTab_r565_44[x][y][i] = ((i + 8) & 0xf8) << 8;
		DitherTab_r332_44[x][y][i] = ((i + 8) & 0xe0);
	      }
	      else {
		DitherTab_r565_44[x][y][i] = (i & 0xf8) << 8;
		DitherTab_r332_44[x][y][i] = i & 0xe0;
	      }
	      
	      if ((DitherMatrix_44[x][y] < ((i & 0x3)<<1))&&(i < (256 - 4))) {
		DitherTab_g565_44[x][y][i] = (((i + 4) & 0xfc) << 8) >> 5;
	        DitherTab_g332_44[x][y][i] = ((i + 4) & 0xe0) >> 3;
	      }
	      else {
		DitherTab_g565_44[x][y][i] = ((i & 0xfc) << 8) >> 5;
		DitherTab_g332_44[x][y][i] = (i & 0xe0) >> 3;
	      }

	      if ((DitherMatrix_44[x][y] < (i & 0x7)) && (i < (256 - 8))) {
		DitherTab_b565_44[x][y][i] = (((i + 8) & 0xf8) << 16) >> 19;
		DitherTab_b332_44[x][y][i] = ((i+8) >> 6) & 0x3;
	      }
	      else {
		DitherTab_b565_44[x][y][i] = ((i & 0xf8) << 16) >> 19;
		DitherTab_b332_44[x][y][i] = (i >> 6) & 0x3;
	      }
	    }
	}
    }

}


