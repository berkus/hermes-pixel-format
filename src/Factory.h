/*
   Factory methods header for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#ifndef __HERMES_FACTORY__
#define __HERMES_FACTORY__

#include "H_Types.h"
#include "H_Format.h"
#include "Clear.h"
#include "Convert.h"


/* Initialise factory */
void Hermes_Factory_Init();


/* Get a clearer function for bits / pixel */
HermesClearer *Hermes_Factory_getClearer(int32 bits);


/* Get a converter for conversion from source to dest */
HermesConverter *Hermes_Factory_getConverter(HermesFormat *source, 
					     HermesFormat *dest);

/* Get a converter for equal formats with source format bits / dest format
   bits */
HermesConverter *Hermes_Factory_getEqualConverter(int bits);


typedef struct {
  int s_bits,s_idx;
  int32 s_r,s_g,s_b,s_a;
  int d_bits,d_idx;
  int32 d_r,d_g,d_b,d_a;

  HermesConverterLoopPtr loopnormal,loopstretch;
  HermesConverterPtr normal,stretch;
  HermesConverterLoopPtr dither,ditherstretch;

  int processor;
} HermesFactoryStruct;


#define PROC_GENERIC 1
#define PROC_X86_PENTIUM 2
#define PROC_MMX_PENTIUM 4

extern HermesFactoryStruct Factory_Converters[];
extern int Factory_NumConverters;

#endif




