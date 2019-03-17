/*
   C clearing and converter routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#if defined X86_ASSEMBLER && defined __BORLANDC__
//#undef X86_ASSEMBLER
#endif

#ifndef __HERMES_HEAD_C__
#define __HERMES_HEAD_C__


#include "HermConf.h"
#include "H_Types.h"
#include "Clear.h"
#include "Convert.h"


/* Clearer functions */

void STACKCALL ClearC_32(HermesClearInterface *iface);
void STACKCALL ClearC_24(HermesClearInterface *iface);
void STACKCALL ClearC_16(HermesClearInterface *iface);
void STACKCALL ClearC_8(HermesClearInterface *iface);

/* Macros to help with conversion routines */
/* IMPORTANT NOTE: Some of these macros do not bracket "adr" this is intentional */
#define READ8(adr) (*((char *)(adr)))
#define READ16(adr) *((short16 *)adr)
#define READ24(adr) ( \
  (((int32)*( ((unsigned char *)(adr)) + B_24 ))) | \
  (((int32)*( ((unsigned char *)(adr)) + G_24 )) << 8) | \
  (((int32)*( ((unsigned char *)(adr)) + R_24 )) << 16) \
  )
#define READ32(adr) *((int32 *)adr)

#define WRITE8(adr,s) (*((char *)(adr))) = (char) (s)
#define WRITE16(adr,s) *((short16 *)adr)=s
#define WRITE24(adr,s) { \
  *( ((unsigned char *)(adr)) + B_24 ) = (unsigned char) (s);\
  *( ((unsigned char *)(adr)) + G_24 ) = (unsigned char) (s>>8);\
  *( ((unsigned char *)(adr)) + R_24 ) = (unsigned char) (s>>16);\
  }

#define WRITE32(adr,s) *((int32 *)adr)=s


/* This little definition makes everything much nicer below here */

#define CONVERT_PARAMETERS char8 *source,char8 *dest,unsigned int count, \
  unsigned int inc_source


/* See FactConv.c for explanations of the following */

void NotApplicable(CONVERT_PARAMETERS);


/* Converter loop for specific converters */

void STACKCALL ConvertC(HermesConverterInterface *);
void STACKCALL ConvertCStretch(HermesConverterInterface *iface);


/* Generic converters RGB */

void STACKCALL ConvertC_Generic32_Generic32(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_Generic24(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_Generic16(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_Generic8(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_Generic32(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_Generic24(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_Generic16(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_Generic8(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_Generic32(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_Generic24(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_Generic16(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_Generic8(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_Generic32_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_Generic24_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_Generic16_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_Generic8_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_Generic32_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_Generic24_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_Generic16_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_Generic8_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_Generic32_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_Generic24_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_Generic16_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_Generic8_S(HermesConverterInterface *);

/* Generic converters RGBA */

void STACKCALL ConvertC_Generic32_A_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_A_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_A_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_A_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic8_A_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_A_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic8_A_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_A_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic8_A_S(HermesConverterInterface *);


/* Generic converters colorkey->colorkey */

void STACKCALL ConvertC_Generic32_C_Generic32_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_C(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_C(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_C(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_C_Generic32_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_C_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_C_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_C_S(HermesConverterInterface *);

/* Generic converters colorkey->alpha */

void STACKCALL ConvertC_Generic32_C_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_C_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_A_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_A_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_A_S(HermesConverterInterface *);


/* Generic converters RGBA->colorkey */

void STACKCALL ConvertC_Generic32_A_Generic32_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic24_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic16_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic8_C(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_A_Generic32_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic24_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic16_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic8_C(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_A_Generic32_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic24_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic16_C(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic8_C(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_A_Generic32_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic24_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic16_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic8_C_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_A_Generic32_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic24_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic16_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic8_C_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_A_Generic32_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic24_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic16_C_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic8_C_S(HermesConverterInterface *);


/* Generic blitters C->O */

void STACKCALL ConvertC_Generic32_C_Generic32_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_O_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_O_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_O_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_C_Generic32_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_O_S_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_O_S_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_O_S_Blit(HermesConverterInterface *);


/* Generic blitters C->C */

void STACKCALL ConvertC_Generic32_C_Generic32_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_C_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_C_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_C_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_C_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_C_Generic32_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic24_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic16_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_C_Generic8_C_S_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_C_Generic32_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic24_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic16_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_C_Generic8_C_S_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_C_Generic32_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic24_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic16_C_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_C_Generic8_C_S_Blit(HermesConverterInterface *);


/* Generic blitters A->O */

void STACKCALL ConvertC_Generic32_A_Generic32_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic24_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic16_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic8_O_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_A_Generic32_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic24_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic16_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic8_O_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_A_Generic32_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic24_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic16_O_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic8_O_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_A_Generic32_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic24_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic16_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_A_Generic8_O_S_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_A_Generic32_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic24_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic16_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_A_Generic8_O_S_Blit(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_A_Generic32_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic24_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic16_O_S_Blit(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_A_Generic8_O_S_Blit(HermesConverterInterface *);

/* Generic converters RGBA (noAlpha) */

void STACKCALL ConvertC_Generic32_NoA_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_NoA_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_NoA_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_NoA_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_NoA_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_NoA_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_NoA_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_NoA_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_NoA_Generic32_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_NoA_Generic24_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_NoA_Generic16_A(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_NoA_Generic8_A(HermesConverterInterface *);

void STACKCALL ConvertC_Generic32_NoA_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_NoA_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_NoA_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic32_NoA_Generic8_A_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic24_NoA_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_NoA_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_NoA_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic24_NoA_Generic8_A_S(HermesConverterInterface *);

void STACKCALL ConvertC_Generic16_NoA_Generic32_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_NoA_Generic24_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_NoA_Generic16_A_S(HermesConverterInterface *);
void STACKCALL ConvertC_Generic16_NoA_Generic8_A_S(HermesConverterInterface *);


/* From muhmu */

void ConvertC_muhmu32_32rgb888(CONVERT_PARAMETERS);
void ConvertC_muhmu32_32bgr888(CONVERT_PARAMETERS);
void ConvertC_muhmu32_32rgba888(CONVERT_PARAMETERS);
void ConvertC_muhmu32_32bgra888(CONVERT_PARAMETERS);
void ConvertC_muhmu32_24rgb888(CONVERT_PARAMETERS);
void ConvertC_muhmu32_24bgr888(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16rgb565(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16bgr565(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16rgb555(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16bgr555(CONVERT_PARAMETERS);
void ConvertC_muhmu32_8rgb332(CONVERT_PARAMETERS);

void ConvertC_muhmu32_16rgb565_S(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16bgr565_S(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16rgb555_S(CONVERT_PARAMETERS);
void ConvertC_muhmu32_16bgr555_S(CONVERT_PARAMETERS);
void ConvertC_muhmu32_8rgb332_S(CONVERT_PARAMETERS);

/* From 32 bit RGBA */
void ConvertC_32rgba8888_32rgb888_blit(CONVERT_PARAMETERS);



/* From 32 bit RGB */

void ConvertC_32rgb888_32bgr888(CONVERT_PARAMETERS);
void ConvertC_32rgb888_32rgba888(CONVERT_PARAMETERS);
void ConvertC_32rgb888_32bgra888(CONVERT_PARAMETERS);
void ConvertC_32rgb888_24rgb888(CONVERT_PARAMETERS);
void ConvertC_32rgb888_24bgr888(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16rgb565(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16bgr565(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16rgb555(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16bgr555(CONVERT_PARAMETERS);
void ConvertC_32rgb888_8rgb332(CONVERT_PARAMETERS);

void ConvertC_32rgb888_32bgr888_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_32rgba888_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_32bgra888_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16rgb565_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16bgr565_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16rgb555_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_16bgr555_S(CONVERT_PARAMETERS);
void ConvertC_32rgb888_8rgb332_S(CONVERT_PARAMETERS);

void STACKCALL ConvertC_32rgb888_16rgb565_dither(HermesConverterInterface*);
void STACKCALL ConvertC_32rgb888_8rgb332_dither(HermesConverterInterface*);


/* From 24 bit RGB */

void ConvertC_24rgb888_32rgb888(CONVERT_PARAMETERS);
void ConvertC_24rgb888_32bgr888(CONVERT_PARAMETERS);
void ConvertC_24rgb888_32rgba888(CONVERT_PARAMETERS);
void ConvertC_24rgb888_32bgra888(CONVERT_PARAMETERS);
void ConvertC_24rgb888_24bgr888(CONVERT_PARAMETERS);
void ConvertC_24rgb888_16rgb565(CONVERT_PARAMETERS);
void ConvertC_24rgb888_16bgr565(CONVERT_PARAMETERS);
void ConvertC_24rgb888_16rgb555(CONVERT_PARAMETERS);
void ConvertC_24rgb888_16bgr555(CONVERT_PARAMETERS);
void ConvertC_24rgb888_8rgb332(CONVERT_PARAMETERS);


/* From 16 bit RGB */

void ConvertC_16rgb565_32rgb888(CONVERT_PARAMETERS);
void ConvertC_16rgb565_32bgr888(CONVERT_PARAMETERS);
void ConvertC_16rgb565_32rgba888(CONVERT_PARAMETERS);
void ConvertC_16rgb565_32bgra888(CONVERT_PARAMETERS);
void ConvertC_16rgb565_24rgb888(CONVERT_PARAMETERS);
void ConvertC_16rgb565_24bgr888(CONVERT_PARAMETERS);
void ConvertC_16rgb565_16bgr565(CONVERT_PARAMETERS);
void ConvertC_16rgb565_16rgb555(CONVERT_PARAMETERS);
void ConvertC_16rgb565_16bgr555(CONVERT_PARAMETERS);
void ConvertC_16rgb565_8rgb332(CONVERT_PARAMETERS);

void ConvertC_16rgb565_32rgb888_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_32bgr888_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_32rgba888_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_32bgra888_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_16bgr565_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_16rgb555_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_16bgr555_S(CONVERT_PARAMETERS);
void ConvertC_16rgb565_8rgb332_S(CONVERT_PARAMETERS);

/* From 8 bit indexed */
void STACKCALL ConvertC_index8_32(HermesConverterInterface *);
void STACKCALL ConvertC_index8_24(HermesConverterInterface *);
void STACKCALL ConvertC_index8_16(HermesConverterInterface *);

void STACKCALL ConvertC_index8_32_S(HermesConverterInterface *);
void STACKCALL ConvertC_index8_16_S(HermesConverterInterface *);


void CopyC_4byte(CONVERT_PARAMETERS);
void CopyC_3byte(CONVERT_PARAMETERS);
void CopyC_2byte(CONVERT_PARAMETERS);
void CopyC_1byte(CONVERT_PARAMETERS);
void CopyC_4byte_S(CONVERT_PARAMETERS);
void CopyC_3byte_S(CONVERT_PARAMETERS);
void CopyC_2byte_S(CONVERT_PARAMETERS);
void CopyC_1byte_S(CONVERT_PARAMETERS);

#endif


