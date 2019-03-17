
#ifndef __HERMES_DITHER_H__
#define __HERMES_DITHER_H__


#include "H_Types.h"


/* Rasterman's dither matrix */
extern char8 DitherMatrix_44[4][4];


/* Dithering tables */
extern short16 DitherTab_r565_44[4][4][256];
extern short16 DitherTab_g565_44[4][4][256];
extern short16 DitherTab_b565_44[4][4][256];

extern char8 DitherTab_r332_44[4][4][256];
extern char8 DitherTab_g332_44[4][4][256];
extern char8 DitherTab_b332_44[4][4][256];


void Dither_SetupMatrices();



#endif

