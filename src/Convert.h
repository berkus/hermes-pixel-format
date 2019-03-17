/*
   Header definitions for format converters for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/


#ifndef __HERMES_INTERNAL_CONVERT__
#define __HERMES_INTERNAL_CONVERT__

#include "H_Types.h"
#include "H_Format.h"
#include "Utility.h"
#include "HermConf.h"


/* Flag to mark generic converters (as opposed to specialised) */

#define HERMES_CONVERT_GENERIC 65536



/* Pointer to specialised (one-scanline-only) conversion function */

typedef void (*HermesConverterPtr)(char8 *source,char8 *dest,
				   unsigned int count,unsigned int inc_source);



/* Structure for conversion loop routines, don't be scared, size does NOT
   matter in this case :) */

typedef struct {
  char8 *s_pixels;
  int s_width,s_height;
  int s_add;                        /* Offset to next line from end of line */

  char8 *d_pixels;
  int d_width,d_height;
  int d_add;                        

  HermesConverterPtr func;

  int32 *lookup;                    /* Palette lookup table ptr, for 8 bit */

  int s_pitch;                      /* Source and destination pitch, */
  int d_pitch;                      /* only used by C routines */

  HermesGenericInfo info;           /* Only used by generic converters */
  int32 mask_r,mask_g,mask_b,mask_a;       /* Only used by generic converters */
  int32 s_mask_a;

  char s_has_colorkey;
  int32 s_colorkey;

  char d_has_colorkey;
  int32 d_colorkey;
} HermesConverterInterface;

/* Pointer to loop function (C, assembler main loop, generic routines) */
typedef void STACKCALL (*HermesConverterLoopPtr)(HermesConverterInterface*);

/* See blit.c for usage for these Jump Table structures */
typedef struct {
	HermesConverterLoopPtr loopnormal;
	HermesConverterLoopPtr loopstretch;
	char *converter_name;
	} HermesJumpTable;

typedef struct {
	HermesJumpTable **jt_cc;
	HermesJumpTable **jt_ca;
	HermesJumpTable **jt_ac;
	HermesJumpTable **jt_ao;
	HermesJumpTable **jt_aa;
	HermesJumpTable **jt_co;
	HermesJumpTable **jt_copyonly;
	HermesJumpTable **jt_noalpha_alpha;
	} HermesJumpTableList;

typedef struct {

  HermesFormat source,dest;                /* Source and destination format */
  int32* lookup;                           /* Pointer to lookup table (8bit) */

  unsigned long flags;                     /* Defined in H_Conv.h, DITHER,etc*/

  HermesConverterLoopPtr loopnormal;       /* Loop routine for normal conv. */
  HermesConverterLoopPtr loopstretch;
  HermesConverterPtr normal;               /* One-scanline routine */
  HermesConverterPtr stretch;

  HermesConverterLoopPtr dither;           /* Dithering routines always */
  HermesConverterLoopPtr ditherstretch;    /* convert the whole buffer */

} HermesConverter;

// Standard macro to convert the RGB format (only used by generic converters)
// New_RGB = CONVERT_RGB(Original_RGB);
#define CONVERT_RGB(source) ( \
	( ( ( (source) >> iface->info.r_right) << iface->info.r_left ) & iface->mask_r ) | \
        ( ( ( (source) >> iface->info.g_right) << iface->info.g_left ) & iface->mask_g ) | \
        ( ( ( (source) >> iface->info.b_right) << iface->info.b_left ) & iface->mask_b ) \
	)

// Standard macro to convert the RGBA format (only used by generic converters)
// New_RGBA = CONVERT_RGBA(Original_RGBA);
#define CONVERT_RGBA(source) ( \
        ( ( ( (source) >> iface->info.r_right) << iface->info.r_left ) & iface->mask_r ) | \
        ( ( ( (source) >> iface->info.g_right) << iface->info.g_left ) & iface->mask_g ) | \
        ( ( ( (source) >> iface->info.b_right) << iface->info.b_left ) & iface->mask_b ) | \
        ( ( ( (source) >> iface->info.a_right) << iface->info.a_left ) & iface->mask_a ) \
	)

// Standard macro to convert the RGBA format with inverse alpha format (only used by generic converters)
#define CONVERT_RGBA_NOALPHA(source) ( \
        ( ( ( (source) >> iface->info.r_right) << iface->info.r_left ) & iface->mask_r ) | \
        ( ( ( (source) >> iface->info.g_right) << iface->info.g_left ) & iface->mask_g ) | \
        ( ( ( (source) >> iface->info.b_right) << iface->info.b_left ) & iface->mask_b ) | \
        ( ( ( (~source) >> iface->info.a_right) << iface->info.a_left ) & iface->mask_a ) \
	)
	

// Macro to get a RGB. This may look like a useless macro, however it is required for the generic converter macros
#define COPY_RGB(source) source
#define COPY_RGBA(source) source

// **********************************************
// * The General Pixel Conversion Macros        *
// * The CG_VARS() and CG_STANDARD() Macros are *
// * defined inside the c_genrc*.c source code  *
// **********************************************

// Define the macro to convert a pixel type
// src_read_macro = READxx
// dest_write_macro = WRITEyy
// src_byte_inc = xx/8
// dest_byte_inc = yy/8
// dest_read_macro = READyy (0 if unused)
#define CG_NORMAL(src_read_macro, dest_write_macro, src_byte_inc, dest_byte_inc, dest_read_macro) \
 	CG_VARS() \
	CG_STANDARD(src_read_macro, dest_write_macro, src_byte_inc, dest_byte_inc, CONVERT_RGB, dest_read_macro)

// Define the macro to copy an identical pixel type - checking that the pixel colours are in the same position
// src_read_macro = READxx
// dest_write_macro = WRITExx
// byte_inc = xx/8
// dest_read_macro = READyy (0 if unused)
#define CG_IDENTICAL(src_read_macro, dest_write_macro, byte_inc, dest_read_macro) \
 	CG_VARS() \
	/* Are the pixel colours in the same position */ \
	if (  (iface->info.r_right == iface->info.r_left) \
	   && (iface->info.g_right == iface->info.g_left) \
	   && (iface->info.b_right == iface->info.b_left) ) \
	{ \
		CG_STANDARD(src_read_macro, dest_write_macro, byte_inc, byte_inc, COPY_RGB, dest_read_macro) \
	}else \
	{ \
		CG_STANDARD(src_read_macro, dest_write_macro, byte_inc, byte_inc, CONVERT_RGB, dest_read_macro) \
	}

// Define the stretch macro to convert a pixel type
// src_read_macro = READxx
// dest_write_macro = WRITEyy
// src_byte_inc = xx/8
// dest_byte_inc = yy/8
// dest_read_macro = READyy (0 if unused)
#define CG_S_NORMAL(src_read_macro, dest_write_macro, src_byte_inc, dest_byte_inc, dest_read_macro) \
 	CG_S_VARS() \
	CG_S_STANDARD(src_read_macro, dest_write_macro, src_byte_inc, dest_byte_inc, CONVERT_RGB, dest_read_macro)

// Define the stretch macro to copy an identical pixel type - checking that the pixel colours are in the same position
// src_read_macro = READxx
// dest_write_macro = WRITExx
// byte_inc = xx/8
// dest_read_macro = READyy (0 if unused)
#define CG_S_IDENTICAL(src_read_macro, dest_write_macro, byte_inc, dest_read_macro) \
 	CG_S_VARS() \
	/* Are the pixel colours in the same position */ \
	if (  (iface->info.r_right == iface->info.r_left) \
	   && (iface->info.g_right == iface->info.g_left) \
	   && (iface->info.b_right == iface->info.b_left) ) \
	{ \
		CG_S_STANDARD(src_read_macro, dest_write_macro, byte_inc, byte_inc, COPY_RGB, dest_read_macro) \
	}else \
	{ \
		CG_S_STANDARD(src_read_macro, dest_write_macro, byte_inc, byte_inc, CONVERT_RGB, dest_read_macro) \
	}

extern HermesConverter **standardConverters[];
extern HermesConverter *equalConverters[];

extern int numConverters[];

extern HermesJumpTable HJT_NONE[4];
extern int HERMES_API Hermes_BlitterRequest_V2(HermesHandle handle, HermesFormat *source, HermesFormat *dest, int api_flags, HermesJumpTableList *tptr);

#endif


