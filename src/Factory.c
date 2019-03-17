/*
   Factory methods implementation for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include <stdio.h>
#include <stdlib.h>
#include "Factory.h"
#include "HermConf.h"
#include "Clear.h"
#include "Convert.h"
#include "HeadC.h"
#include "HeadX86.h"
#include "HeadMMX.h"
#include "Debug.h"



/* disable visual c++ warning */
#if (_MSC_VER>=1000)
#pragma warning( disable : 4113 )
#endif



int processor;



void Hermes_Factory_Init()
{ int res=0;

  processor=PROC_GENERIC;

#ifdef X86_ASSEMBLER
  processor|=PROC_X86_PENTIUM;      /* There are no others at the moment */

  res=Hermes_X86_CPU();

  DEBUG_PRINT("CPUID: %x\n",res)
  
  if (res&0x800000) { 
    processor|=PROC_MMX_PENTIUM;
    DEBUG_PRINT("MMX enabled!\n%s","");
  }
#endif
}




HermesClearer *Hermes_Factory_getClearer(int32 bits)
{ HermesClearer *tmp;

  /* Try different processors in order of priority..
     Note that for this to work, an MMX processor has to have both MMX and
     X86 flags */

  tmp=(HermesClearer *)malloc(sizeof(HermesClearer));
  if (!tmp) return 0;

  tmp->bits=bits;


#ifdef X86_ASSEMBLER

  if (processor & PROC_MMX_PENTIUM) {
    switch(bits) {
      case 32: tmp->func=ClearMMX_32; return tmp;
      case 24: break;
      case 16: tmp->func=ClearMMX_16; return tmp;
       case 8: tmp->func=ClearMMX_8; return tmp;
    }

  }

  if (processor & PROC_X86_PENTIUM) {
    switch(bits) {
      case 32: tmp->func=ClearX86_32; return tmp;
      case 24: break;
      case 16: tmp->func=ClearX86_16; return tmp;
       case 8: tmp->func=ClearX86_8; return tmp;
    }
  }

#endif /* X86_ASSEMBLER */


  /* C routines here */  

  switch (bits) {
    case 32: tmp->func=ClearC_32; return tmp;
    case 24: tmp->func=ClearC_24; return tmp;
    case 16: tmp->func=ClearC_16; return tmp;
     case 8: tmp->func=ClearC_8; return tmp;
    default: { free(tmp); return 0; }
  }
}


HermesConverter *Hermes_Factory_getConverter(HermesFormat *source,
  HermesFormat *dest)
{ HermesConverter *tmp;
  char found=0;
  int i=0;
  
  tmp=(HermesConverter *)malloc(sizeof(HermesConverter));
  if (!tmp) return 0;

  /* Set all conversion routines to null */

  tmp->loopnormal=0;
  tmp->loopstretch=0;
  tmp->normal=0;
  tmp->stretch=0;
  tmp->dither=0;
  tmp->ditherstretch=0;
  tmp->flags=0;


  if (source->indexed) {

    /* For 8 bit indexed, just look at the destination bit depth and check
       if the converter's processor is a subset of our processor */
    
    for (i=0;i<Factory_NumConverters;i++)
    if (Factory_Converters[i].d_bits==dest->bits &&
	Factory_Converters[i].s_idx &&
	(processor & Factory_Converters[i].processor)) {


      /* If any routines are unassigned, assign them now */

      if (!tmp->loopnormal)
      { tmp->loopnormal=Factory_Converters[i].loopnormal; found=1; }

      if (!tmp->normal)
      { tmp->normal=Factory_Converters[i].normal; found=1; }

      if (!tmp->loopstretch)
      { tmp->loopstretch=Factory_Converters[i].loopstretch; found=1; }

      if (!tmp->stretch)
      { tmp->stretch=Factory_Converters[i].stretch; found=1; }

    }
      
  } else {
    
    /* Otherwise we need to compare everything, including bitmasks */

    for (i=0;i<Factory_NumConverters;i++)
    if (Factory_Converters[i].d_bits==dest->bits &&
	Factory_Converters[i].d_r==dest->r &&
	Factory_Converters[i].d_g==dest->g &&
	Factory_Converters[i].d_b==dest->b &&
	Factory_Converters[i].d_a==dest->a &&
	Factory_Converters[i].d_idx==dest->indexed &&
	Factory_Converters[i].s_bits==source->bits &&
	Factory_Converters[i].s_r==source->r &&
	Factory_Converters[i].s_g==source->g &&
	Factory_Converters[i].s_b==source->b &&
	Factory_Converters[i].s_a==source->a &&
	Factory_Converters[i].s_idx==source->indexed &&
	(processor & Factory_Converters[i].processor)) {

      /* If any routines are unassigned, assign them now */

      if (!tmp->loopnormal && Factory_Converters[i].loopnormal)
      { tmp->loopnormal=Factory_Converters[i].loopnormal; found=1; }

      if (!tmp->normal && Factory_Converters[i].normal)
      { tmp->normal=Factory_Converters[i].normal; found=1; }

      if (!tmp->loopstretch && Factory_Converters[i].loopstretch)
      { tmp->loopstretch=Factory_Converters[i].loopstretch; found=1; }

      if (!tmp->stretch && Factory_Converters[i].stretch)
      { tmp->stretch=Factory_Converters[i].stretch; found=1; }

      if (!tmp->dither && Factory_Converters[i].dither)
      { tmp->dither=Factory_Converters[i].dither; }

      if (!tmp->ditherstretch && Factory_Converters[i].ditherstretch)
      { tmp->ditherstretch=Factory_Converters[i].ditherstretch; found=1; }


      /* In the rare event of having everything assigned, pull the emergency
	 break. Otherwise we need to continue looking (might be stretching
         routines somewhere :) 
         Do I sound like a stewardess? */

      if (tmp->loopnormal && tmp->normal && tmp->loopstretch && tmp->stretch)
      break;

    }
  }


  if (found) {
    Hermes_FormatCopy(source,&tmp->source);
    Hermes_FormatCopy(dest,&tmp->dest);
    
    return tmp;
  }

  free(tmp);

  return 0;
}




HermesConverter *Hermes_Factory_getEqualConverter(int bits)
{ HermesConverter *tmp;
  char found=0;
 
  tmp=(HermesConverter *)malloc(sizeof(HermesConverter));
  if (!tmp) return 0;

  /* Set all conversion routines to null */

  tmp->loopnormal=0;
  tmp->loopstretch=0;
  tmp->normal=0;
  tmp->stretch=0;
  tmp->dither=0;
  tmp->ditherstretch=0;


#ifdef X86_ASSEMBLER

  /* Try MMX routines */
  if (!tmp->loopnormal || !tmp->normal || !tmp->loopstretch || !tmp->stretch)
  if (processor & PROC_MMX_PENTIUM) {
    switch (bits) {


    }
  }


  /* Try X86 routines */
  if (!tmp->loopnormal || !tmp->normal || !tmp->loopstretch || !tmp->stretch)
  if (processor & PROC_X86_PENTIUM) {
    int asm_found=0;
    
    switch (bits) {
      case 32: { tmp->normal=CopyX86p_4byte; asm_found=1; } break;
      case 24: break;
      case 16: { tmp->normal=CopyX86p_2byte; asm_found=1; } break;
       case 8: { tmp->normal=CopyX86p_1byte; asm_found=1; } break;
    }

    if (asm_found&1) { tmp->loopnormal=ConvertX86; found=1; }
  }

#endif /* X86_ASSEMBLER */


  if (!tmp->loopnormal || !tmp->normal || !tmp->loopstretch || !tmp->stretch)
  { int c_found=0;

    switch (bits) {
      case 32: { if (!tmp->normal) { tmp->normal=CopyC_4byte; c_found|=1; } 
                 if (!tmp->stretch) { tmp->stretch=CopyC_4byte_S; c_found|=2; }
		 break;
               }

      case 24: { if (!tmp->normal) { tmp->normal=CopyC_3byte; c_found=1; }
		 if (!tmp->stretch) { tmp->stretch=CopyC_3byte_S; c_found|=2; }
		 break;
	       }
	       
      case 16: { if (!tmp->normal) { tmp->normal=CopyC_2byte; c_found|=1; } 
                 if (!tmp->stretch) { tmp->stretch=CopyC_2byte_S; c_found|=2; }
		 break; 
               }

       case 8: { if (!tmp->normal) { tmp->normal=CopyC_1byte; c_found|=1; }
                 if (!tmp->stretch) { tmp->stretch=CopyC_1byte_S; c_found|=2; }
		 break; 
               }
    }

    if (c_found&1) { tmp->loopnormal=ConvertC; found=1; }
    if (c_found&2) { tmp->loopstretch=ConvertCStretch; found=1; }
  }

  if (found) return tmp;

  free(tmp);

  return 0;
}




