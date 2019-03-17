/*
   Initialisation functions for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Hermes.h"
#include "Factory.h"
#include "Clear.h"
#include "Convert.h"
#include "Dither.h"
#include "Debug.h"

#if defined X86_ASSEMBLY && defined __BORLANDC__
//#undef X86_ASSEMBLY
#error SHIT
#endif

/* p_converters holds a list of formats, for conversion from 32 bit, 24 bit,
   16 bit, muhmu and 8 bit.
   The destination formats are listed in the order of frequency they might
   occur so common formats can be retriebed faster.

   Format of a row: 
   source bpp, s. indexed, s. r_mask, s. g_mask, s. b_mask, s. alpha ,dest bpp,
   d.indexed, d. r_mask, d. g_mask, d. b_mask, d. alpha
*/

/* I wish I could touch this, but it's used in too many other placed in the code,
   ( at least indirectly), and many of the indicies are hardcoded */

int p_converters[5][12][12]=
{
{/*From 32 bit RGB 888 */
{32,0,0xff0000,0xff00,0xff,0,16,0,0xf800,0x7e0,0x1f,0},         /* 16RGB565 */
{32,0,0xff0000,0xff00,0xff,0, 8,0,0xe0,0x1c,0x3,0},             /* 8RGB332 */
{32,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0},         /* 16RGB555 */
{32,0,0xff0000,0xff00,0xff,0,24,0,0xff0000,0xff00,0xff,0},      /* 24RGB888 */
{32,0,0xff0000,0xff00,0xff,0,32,0,0xff,0xff00,0xff0000,0},      /* 32BGR888 */
{32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x7e0,0xf800,0},         /* 16BGR565 */
{32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0},         /* 16BGR555 */
{32,0,0xff0000,0xff00,0xff,0,32,0,0xff000000,0xff0000,0xff00,0},/* 32RGBA888 */
{32,0,0xff0000,0xff00,0xff,0,32,0,0xff00,0xff0000,0xff000000,0},/* 32BGRA888 */
{32,0,0xff0000,0xff00,0xff,0,24,0,0xff,0xff00,0xff0000,0},      /* 24BGR888 */
}
,
{/* From 24 bit RGB 888 */
{24,0,0xff0000,0xff00,0xff,0,32,0,0xff0000,0xff00,0xff,0},      /* 32RGB888 */
{24,0,0xff0000,0xff00,0xff,0,16,0,0xf800,0x7e0,0x1f,0},         /* 16RGB565 */
{24,0,0xff0000,0xff00,0xff,0, 8,0,0xe0,0x1c,0x3,0},             /* 8RGB332 */
{24,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0},         /* 16RGB555 */
{24,0,0xff0000,0xff00,0xff,0,32,0,0xff,0xff00,0xff0000,0},      /* 32BGR888 */
{24,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x7e0,0xf800,0},         /* 16BGR565 */
{24,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0},         /* 16BGR555 */
{24,0,0xff0000,0xff00,0xff,0,32,0,0xff000000,0xff0000,0xff00,0},/* 32RGBA888 */
{24,0,0xff0000,0xff00,0xff,0,32,0,0xff00,0xff0000,0xff000000,0},/* 32BGRA888 */
{24,0,0xff0000,0xff00,0xff,0,24,0,0xff,0xff00,0xff0000,0},      /* 24BGR888 */
}
,
{/*From 16 bit RGB 565 */
{16,0,0xf800,0x7e0,0x1f,0,32,0,0xff0000,0xff00,0xff,0},         /* 32RGB888 */
{16,0,0xf800,0x7e0,0x1f,0, 8,0,0xe0,0x1c,0x3,0},                /* 8RGB332 */
{16,0,0xf800,0x7e0,0x1f,0,16,0,0x7c00,0x3e0,0x1f,0},            /* 16RGB555 */
{16,0,0xf800,0x7e0,0x1f,0,24,0,0xff0000,0xff00,0xff,0},         /* 24RGB888 */
{16,0,0xf800,0x7e0,0x1f,0,32,0,0xff,0xff00,0xff0000,0},         /* 32BGR888 */
{16,0,0xf800,0x7e0,0x1f,0,16,0,0x1f,0x7e0,0xf800,0},            /* 16BGR565 */
{16,0,0xf800,0x7e0,0x1f,0,16,0,0x1f,0x3e0,0x7c00,0},            /* 16BGR555 */
{16,0,0xf800,0x7e0,0x1f,0,32,0,0xff000000,0xff0000,0xff00,0},   /* 32RGBA888 */
{16,0,0xf800,0x7e0,0x1f,0,32,0,0xff00,0xff0000,0xff000000,0},   /* 32BGRA888 */
{16,0,0xf800,0x7e0,0x1f,0,24,0,0xff,0xff00,0xff0000,0},         /* 24BGR888 */
},
{/* From 32 bit muhmu */
{32,0,0xff00000,0x3fc00,0xff,0,32,0,0xff0000,0xff00,0xff,0},    /* 32RGB888 */
{32,0,0xff00000,0x3fc00,0xff,0,16,0,0xf800,0x7e0,0x1f,0},       /* 16RGB565 */
{32,0,0xff00000,0x3fc00,0xff,0, 8,0,0xe0,0x1c,0x3,0},           /* 8RGB332 */
{32,0,0xff00000,0x3fc00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0},       /* 16RGB555 */
{32,0,0xff00000,0x3fc00,0xff,0,24,0,0xff0000,0xff00,0xff,0},    /* 24RGB888 */
{32,0,0xff00000,0x3fc00,0xff,0,32,0,0xff,0xff00,0xff0000,0},    /* 32BGR888 */
{32,0,0xff00000,0x3fc00,0xff,0,16,0,0x1f,0x7e0,0xf800,0},       /* 16BGR565 */
{32,0,0xff00000,0x3fc00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0},       /* 16BGR555 */
{32,0,0xff00000,0x3fc00,0xff,0,32,0,0xff000000,0xff0000,0xff00,0},/* 32RGBA888 */
{32,0,0xff00000,0x3fc00,0xff,0,32,0,0xff00,0xff0000,0xff000000,0},/* 32BGRA888 */
{32,0,0xff00000,0x3fc00,0xff,0,24,0,0xff,0xff00,0xff0000,0},    /* 24BGR888 */
},
{/* From 8 bit indexed */
{8,1,0,0,0,0,32,0,0,0,0,0},
{8,1,0,0,0,0,24,0,0,0,0,0},
{8,1,0,0,0,0,16,0,0,0,0,0},
}
};




HermesClearer *Clearers[4];
int numClearers;

HermesConverter **standardConverters[5];
HermesConverter *equalConverters[4];
int numConverters[]={10,10,10,11,3};

static int refcount=0;



int  HERMES_API Hermes_Init()
{ int i,j;
  HermesFormat source,dest;

  if (refcount) { refcount++; return 1; }
  

  /* Initialise hermes factory */

  Hermes_Factory_Init();


  /* Instruct the factory to return clearing routines */
 
  Clearers[0]=Hermes_Factory_getClearer(32);
  Clearers[1]=Hermes_Factory_getClearer(24);
  Clearers[2]=Hermes_Factory_getClearer(16);
  Clearers[3]=Hermes_Factory_getClearer(8);
  numClearers=4;



  /* Use factory to obtain specialised converters */
  
  for (j=0;j<5;j++)
  {  
    standardConverters[j]=(HermesConverter **)
                          malloc(sizeof(HermesConverter *)*numConverters[j]);
  
    for (i=0;i<numConverters[j];i++)
    {
      // xxx jm color keys not taken into consideration here
      memset( &source, 0, sizeof( source ) );
      memset( &dest, 0, sizeof( dest ) );
      source.bits=p_converters[j][i][0];    dest.bits=p_converters[j][i][6];
      source.indexed=p_converters[j][i][1]; dest.indexed=p_converters[j][i][7];
      source.r=p_converters[j][i][2];       dest.r=p_converters[j][i][8];
      source.g=p_converters[j][i][3];       dest.g=p_converters[j][i][9];
      source.b=p_converters[j][i][4];       dest.b=p_converters[j][i][10];
      source.a=p_converters[j][i][5];       dest.a=p_converters[j][i][11];

      standardConverters[j][i]=Hermes_Factory_getConverter(&source,&dest);
    }
  }


  /* Set up converters for equal colour formats */

  equalConverters[3]=Hermes_Factory_getEqualConverter(32);
  equalConverters[2]=Hermes_Factory_getEqualConverter(24);
  equalConverters[1]=Hermes_Factory_getEqualConverter(16);
  equalConverters[0]=Hermes_Factory_getEqualConverter(8);


  /* Initialise dithering tables */

  Dither_SetupMatrices();


  refcount++;

  return 1;
}




int HERMES_API Hermes_Done()
{ int i,j;

  refcount--;
  
  /* Error, refcount < 0 */
  if (refcount<0) {
    refcount=0;
    return 0;
  }

  if (!refcount) {
    DEBUG_PRINT("Cleaning up, %d\n",refcount)

    for (i=0;i<4;i++) {
      if (Clearers[i]) {
        free(Clearers[i]);
        Clearers[i]=0;
      }
      if (equalConverters[i]) {
        free(equalConverters[i]);
        equalConverters[i]=0;
      }
    }
    
    for (i=0;i<5;i++) {
      if (standardConverters[i]) {
        for (j=0;j<numConverters[i];j++)
        free (standardConverters[i][j]);
        
        free(standardConverters[i]);
      }
      
      standardConverters[i]=0;
    }
  }

  return 1;
}


