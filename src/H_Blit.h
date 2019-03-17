/*
   Pixel format conversion interface for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/
//#if defined X86_ASSEMBLER && defined __BORLANDC__
//#undef X86_ASSEMBLER
//#endif

#ifndef __HERMES_BLITTER_H__
#define __HERMES_BLITTER_H__

#include "H_Conv.h"

/*
   Get a blitter to work with, specifying a combination of the flags
   in H_Conv. Returns 0 if unsuccessful.
*/
HERMES_C HermesHandle HERMES_API Hermes_BlitterInstance(unsigned long flags);


/*
   Return a blitter if it is not needed anymore, thus releasing some 
   memory.
*/
HERMES_C void HERMES_API Hermes_BlitterReturn(HermesHandle handle);


/*
   Request a format blitting between two formats. This function returns 0
   if the blitting cannot be provided (which should not occur too often :)
   Repeated calls to this function will be cached an terminate almost 
   immediately, so don't be ashamed of calling it often.
*/
HERMES_C int HERMES_API Hermes_BlitterRequest(HermesHandle handle,
						HermesFormat *source,
						HermesFormat *dest);


/*
   Set the palette of the source surface / destination surface for a 
   subsequent blitting. At the moment, only sourcepal is used.
   Returns 0 if unsuccessful (invalid handle!).
*/
HERMES_C int HERMES_API Hermes_BlitterPalette(HermesHandle handle,
						HermesHandle sourcepal,
						HermesHandle destpal);


/*
   Do a format blitting after calling the setup routines above. This will
   blit the pixel data from s_pixels to the data in d_pixels.  Both source
   and destination areas/origins can be specified as well as the scanline
   width in bytes of the source/destination.  Returns 0 if unsuccessful
   (invalid handle or request not called before).
*/
HERMES_C int HERMES_API Hermes_BlitterBlit(HermesHandle handle,
			 void *s_pixels,int s_x,int s_y,int s_width,
			 int s_height,int s_pitch,void *d_pixels,int d_x,
			 int d_y,int d_width,int d_height,int d_pitch);

#endif
