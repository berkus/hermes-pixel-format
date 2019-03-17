/*
   Generic format conversion routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include "HermConf.h"
#include "HeadC.h"
#include "Debug.h"

// ***********************************************
// ******** The Generic Conversion Macros ********
// ***********************************************

#define CG_VARS() int32 s_pixel; \
        unsigned int count; \
        char8 *source=iface->s_pixels; \
	char8 *dest=iface->d_pixels; \
	int32 sc = iface->s_colorkey; \
	int32 dc = iface->d_colorkey;

// Define the general macro
// src_read_macro = READxx
// dest_write_macro = WRITEyy
// src_byte_inc = xx/8
// dest_byte_inc = yy/8
// convert_rgb_macro = Macro to convert the RGB eg CONVERT_RGB
// dest_read_macro = 0 (Unused)
#define CG_STANDARD(src_read_macro, dest_write_macro, src_byte_inc, dest_byte_inc, convert_rgb_macro, dest_read_macro) \
	do { \
		count=iface->s_width; \
		do { \
			s_pixel = src_read_macro(source); \
			if (s_pixel == sc) \
			{ \
				dest_write_macro(dest, dc); \
			}else \
			{ \
				dest_write_macro(dest, (convert_rgb_macro(s_pixel))); \
			} \
			source+=src_byte_inc; \
			dest+=dest_byte_inc; \
		} while(--count); \
        	source+=iface->s_add; \
        	dest+=iface->d_add; \
        } while (--iface->s_height);

// ***********************************************
// ******** The Stretch Conversion Macros ********
// ***********************************************

#define CG_S_VARS() int32 s_pixel; \
        unsigned int count; \
        char8 *source=iface->s_pixels; \
	char8 *dest=iface->d_pixels; \
        unsigned int dy=(iface->s_height<<16)/iface->d_height; \
        unsigned int dx=(iface->s_width<<16)/iface->d_width; \
        unsigned int y=0,x; \
	int32 sc = iface->s_colorkey; \
	int32 dc = iface->d_colorkey;

// Define the general macro
// src_read_macro = READxx
// dest_write_macro = WRITEyy
// src_byte_inc = xx/8
// dest_byte_inc = yy/8
// convert_rgb_macro = Macro to convert the RGB eg CONVERT_RGB
// dest_read_macro = 0 (Unused)
#define CG_S_STANDARD(src_read_macro, dest_write_macro, src_byte_inc, dest_byte_inc, convert_rgb_macro, dest_read_macro) \
	do { \
		count=iface->d_width; \
		x = 0; \
		do { \
			s_pixel = src_read_macro(source + (x>>16)); \
			if (s_pixel == sc) \
			{ \
				dest_write_macro(dest, dc); \
			}else \
			{ \
				dest_write_macro(dest, (convert_rgb_macro(s_pixel))); \
			} \
			x+=dx; \
			dest+=dest_byte_inc; \
		} while(--count); \
        	dest+=iface->d_add; \
        	y+=dy; \
        	source+=(y>>16)*iface->s_pitch; \
	        y &= 0xffff; \
        } while (--iface->d_height);

// **************************************************
// ******** The Generic Conversion Functions ********
// **************************************************

void ConvertC_Generic32_C_Generic32_C(HermesConverterInterface *iface)
{
  CG_IDENTICAL( READ32, WRITE32, 4, 0 )
}

void ConvertC_Generic32_C_Generic24_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ32, WRITE24, 4, 3, 0 )
}

void ConvertC_Generic32_C_Generic16_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ32, WRITE16, 4, 2, 0 )
}

void ConvertC_Generic32_C_Generic8_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ32, WRITE8, 4, 1, 0 )
}

void ConvertC_Generic24_C_Generic32_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ24, WRITE32, 3, 4, 0 )
}

void ConvertC_Generic24_C_Generic24_C(HermesConverterInterface *iface)
{
  CG_IDENTICAL( READ24, WRITE24, 3, 0 )
}

void ConvertC_Generic24_C_Generic16_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ24, WRITE16, 3, 2, 0 )
}

void ConvertC_Generic24_C_Generic8_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ24, WRITE8, 3, 1, 0 )
}

void ConvertC_Generic16_C_Generic32_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ16, WRITE32, 2, 4, 0 )
}

void ConvertC_Generic16_C_Generic24_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ16, WRITE24, 2, 3, 0 )
}

void ConvertC_Generic16_C_Generic16_C(HermesConverterInterface *iface)
{
  CG_IDENTICAL( READ16, WRITE16, 2, 0 )
}

void ConvertC_Generic16_C_Generic8_C(HermesConverterInterface *iface)
{
  CG_NORMAL( READ16, WRITE8, 2, 1, 0 )
}

// **************************************************
// ******** The Stretch Conversion Functions ********
// **************************************************

void ConvertC_Generic32_C_Generic32_C_S(HermesConverterInterface *iface)
{
  CG_S_IDENTICAL( READ32, WRITE32, 4, 0 )
}

void ConvertC_Generic32_C_Generic24_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ32, WRITE24, 4, 3, 0 )
}

void ConvertC_Generic32_C_Generic16_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ32, WRITE16, 4, 2, 0 )
}

void ConvertC_Generic32_C_Generic8_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ32, WRITE8, 4, 1, 0 )
}

void ConvertC_Generic24_C_Generic32_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ24, WRITE32, 3, 4, 0 )
}

void ConvertC_Generic24_C_Generic24_C_S(HermesConverterInterface *iface)
{
  CG_S_IDENTICAL( READ24, WRITE24, 3, 0 )
}

void ConvertC_Generic24_C_Generic16_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ24, WRITE16, 3, 2, 0 )
}

void ConvertC_Generic24_C_Generic8_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ24, WRITE8, 3, 1, 0 )
}

void ConvertC_Generic16_C_Generic32_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ16, WRITE32, 2, 4, 0 )
}

void ConvertC_Generic16_C_Generic24_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ16, WRITE24, 2, 3, 0 )
}

void ConvertC_Generic16_C_Generic16_C_S(HermesConverterInterface *iface)
{
  CG_S_IDENTICAL( READ16, WRITE16, 2, 0 )
}

void ConvertC_Generic16_C_Generic8_C_S(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ16, WRITE8, 2, 1, 0 )
}
