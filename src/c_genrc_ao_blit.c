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

// *** VERY IMPORTANT NOTE ***
// The generic conversion macros do not perform alpha blending
// The following 2 fuctions
//  ConvertC_Generic32_A_Generic32_O_Blit(HermesConverterInterface *iface)
//  ConvertC_Generic32_A_Generic24_O_Blit(HermesConverterInterface *iface)
// Did contain the correct code - However should all the remaining functions be fixed?
// Also the 2 functions should be optimised

// **************************************************
// ******** The Generic Conversion Functions ********
// **************************************************

void ConvertC_Generic32_A_Generic32_O_Blit(HermesConverterInterface *iface)
{	unsigned long s_pixel, d_pixel, r, g, b, a;
	long sr, sg, sb, dr, dg, db, da;
	char8 *source = iface->s_pixels, *dest = iface->d_pixels;
	unsigned int count;
	float sa;
	DEBUG_PRINT("Func\n","");
	do {
		count = iface->s_width;		
		do {
			// Read source pixel
			s_pixel = READ32(source);
			sr = ((s_pixel >> iface->info.r_right) << iface->info.r_left) & iface->mask_r;
			sg = ((s_pixel >> iface->info.g_right) << iface->info.g_left) & iface->mask_g;
			sb = ((s_pixel >> iface->info.b_right) << iface->info.b_left) & iface->mask_b;
			
			// Compute alpha
			sa = (s_pixel & iface->s_mask_a)/(float)iface->s_mask_a;
			
			// Get destination values
			d_pixel = READ32(dest);
			dr = d_pixel & iface->mask_r;
			dg = d_pixel & iface->mask_g;
			db = d_pixel & iface->mask_b;
			
			
			/* We must downshift because we can't have a negative
			   for red, since the sign bit could already be set!
			   Question: Do I also need to downshift
			   sr?
			   I don't think this is portable, either, especially to big-edian.
			   Someone should really write some assembler to do this...
			   I wish I knew more myself, otherwise I would do it.
			*/ 
			dr >>= 24;
			sr >>= 24;
			dr &= (iface->mask_r >> 24);                        
			r = (int32)(dr + (sr - dr) * sa);
			r <<= 24;
			
			/* Or we could do this... */
			/*Which, unfortunately, does not work
			  if(sr < dr)
			  r = (int32)(dr - (dr-sr)*sa);
			  else
			  r = (int32)(dr + (sr-dr)*sa);
			*/
			// Blend pixels
			g = (int32)(dg + (sg - dg) * sa);
			
			// Blend pixels
			b = (int32)(db + (sb - db) * sa);
			
			// Constrain values
			// Would rounding be better here?
			r &= iface->mask_r;
			g &= iface->mask_g;
			b &= iface->mask_b;
			
			// Hack up alpha, since there is no alpha mask. I suppose this
			// would break anything that put data (perhaps a Zbuffer?) in
			// the alpha slot of a 32-bit RGB pixel. How would I fix this?
			a = ~(iface->mask_r|
			      iface->mask_g|
			      iface->mask_b); // Hack, hope it works.
			
			WRITE32(dest, (r|g|b|a)); // Write destination
			
			source+=4;
			dest+=4;
		} while(--count);
		
		source+=iface->s_add;
		dest+=iface->d_add;
	} while (--iface->s_height);
}

void ConvertC_Generic32_A_Generic24_O_Blit(HermesConverterInterface *iface)
{ unsigned long s_pixel, d_pixel, r, g, b, a;
  long sr, sg, sb, dr, dg, db, da;
  float sa;
  char8 *d_ptr=(char8 *)((int)&s_pixel);
  unsigned int count;
  char8 *source=iface->s_pixels,*dest=iface->d_pixels;    
  DEBUG_PRINT("ConvertC_Generic32_A_Generic24_O_Blit called\n","");
  do {
    count=iface->s_width;
    do
    {         
      /* What the hell? */
      /*
	r=((s_pixel>>iface->info.r_right)<<iface->info.r_left)&
	iface->mask_r;
	g=((s_pixel>>iface->info.g_right)<<iface->info.g_left)&
	iface->mask_g;
	b=((s_pixel>>iface->info.b_right)<<iface->info.b_left)&
	iface->mask_b;
      */
      // Read source pixel            
      s_pixel=READ32(source);
      sr = ((s_pixel >> iface->info.r_right) << iface->info.r_left) & iface->mask_r;
      sg = ((s_pixel >> iface->info.g_right) << iface->info.g_left) & iface->mask_g;
      sb = ((s_pixel >> iface->info.b_right) << iface->info.b_left) & iface->mask_b;
      sa = (s_pixel & iface->s_mask_a)/(float)iface->s_mask_a;
      
      //d_pixel = READ32(dest);
      dr = *(dest+R_24);
      dg = *(dest+G_24);
      db = *(dest+B_24);
      
      DEBUG_PRINT("dr: %X ", dr);
      DEBUG_PRINT("dg: %X ", dg);
      DEBUG_PRINT("db: %X ", db);
      DEBUG_PRINT("sr: %X ", sr);
      DEBUG_PRINT("sg: %X ", sg);
      DEBUG_PRINT("sb: %X ", sb);
      DEBUG_PRINT("sa: %f\n", sa);
      
      r = (int32)(dr + (sr - dr) * sa);
      g = (int32)(dg + (sg - dg) * sa);
      b = (int32)(db + (sb - db) * sa);
      
      *(dest+R_24)=r;
      
      *(dest+G_24)=g;
      
      *(dest+B_24)=b;
      
      source+=4;
      dest+=3;
    } while (--count);
    
    source+=iface->s_add;
    dest+=iface->d_add;
  } while (--iface->s_height);
}


// This file requires the CONVERT_RGBA macro instead
// The easy way to achieve this is to redefine it
#undef CONVERT_RGB
#define CONVERT_RGB CONVERT_RGBA
#undef COPY_RGB
#define COPY_RGB COPY_RGBA

// ***********************************************
// ******** The Generic Conversion Macros ********
// ***********************************************

#define CG_VARS() int32 s_pixel; \
        unsigned int count; \
        char8 *source=iface->s_pixels; \
	char8 *dest=iface->d_pixels;

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
			dest_write_macro(dest, (convert_rgb_macro(s_pixel))); \
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
        unsigned int y=0,x;

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
			dest_write_macro(dest, (convert_rgb_macro(s_pixel))); \
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
void ConvertC_Generic32_A_Generic16_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ32, WRITE16, 4, 2, 0 )
}

void ConvertC_Generic32_A_Generic8_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ32, WRITE8, 4, 1, 0 )
}

void ConvertC_Generic24_A_Generic32_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ24, WRITE32, 3, 4, 0 )
}

void ConvertC_Generic24_A_Generic24_O_Blit(HermesConverterInterface *iface)
{
  CG_IDENTICAL( READ24, WRITE24, 3, 0 )
}

void ConvertC_Generic24_A_Generic16_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ24, WRITE16, 3, 2, 0 )
}

void ConvertC_Generic24_A_Generic8_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ24, WRITE8, 3, 1, 0 )
}

void ConvertC_Generic16_A_Generic32_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ16, WRITE32, 2, 4, 0 )
}

void ConvertC_Generic16_A_Generic24_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ16, WRITE24, 2, 3, 0 )
}

void ConvertC_Generic16_A_Generic16_O_Blit(HermesConverterInterface *iface)
{
  CG_IDENTICAL( READ16, WRITE16, 2, 0 )
}

void ConvertC_Generic16_A_Generic8_O_Blit(HermesConverterInterface *iface)
{
  CG_NORMAL( READ16, WRITE8, 2, 1, 0 )
}

// **************************************************
// ******** The Stretch Conversion Functions ********
// **************************************************

void ConvertC_Generic32_A_Generic32_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_IDENTICAL( READ32, WRITE32, 4, 0 )
}

void ConvertC_Generic32_A_Generic24_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ32, WRITE24, 4, 3, 0 )
}

void ConvertC_Generic32_A_Generic16_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ32, WRITE16, 4, 2, 0 )
}

void ConvertC_Generic32_A_Generic8_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ32, WRITE8, 4, 1, 0 )
}

void ConvertC_Generic24_A_Generic32_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ24, WRITE32, 3, 4, 0 )
}

void ConvertC_Generic24_A_Generic24_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_IDENTICAL( READ24, WRITE24, 3, 0 )
}

void ConvertC_Generic24_A_Generic16_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ24, WRITE16, 3, 2, 0 )
}

void ConvertC_Generic24_A_Generic8_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ24, WRITE8, 3, 1, 0 )
}

void ConvertC_Generic16_A_Generic32_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ16, WRITE32, 2, 4, 0 )
}

void ConvertC_Generic16_A_Generic24_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ16, WRITE24, 2, 3, 0 )
}

void ConvertC_Generic16_A_Generic16_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_IDENTICAL( READ16, WRITE16, 2, 0 )
}

void ConvertC_Generic16_A_Generic8_O_S_Blit(HermesConverterInterface *iface)
{
  CG_S_NORMAL( READ16, WRITE8, 2, 1, 0 )
}

