/*
   32 bit to * dithered converters for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include "HermConf.h"
#include "Dither.h"
#include "HeadC.h"



void ConvertC_32rgb888_16rgb565_dither(HermesConverterInterface *iface)
{ char8 *source=iface->s_pixels;
  char8 *dest=iface->d_pixels;
  int32 d_pixel;
  int y=0,count;

 
  while (y<iface->d_height) {
   
    /* Get counter for this scanline */
    count=iface->d_width;

    /* Check first pixel alignment, correct if necessary */
    if (((unsigned int)iface->d_pixels)&1) {
      WRITE16(dest,
	    DitherTab_r565_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g565_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b565_44[count&0x3][y&0x3][*((int32*)source)&0xff]);

      source+=4;
      dest+=2;
      count--;
    }

    /* Two pixels at a time loop */
    while (count>1) {

      d_pixel=
DWORD_BYTE0(DitherTab_r565_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g565_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b565_44[count&0x3][y&0x3][*((int32*)source)&0xff]);

      source+=4;

      count--;

      d_pixel|=
DWORD_BYTE2(DitherTab_r565_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g565_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
	    DitherTab_b565_44[count&0x3][y&0x3][*((int32*)source)&0xff]);
	      
	  
      count--;
      source+=4;

      WRITE32(dest,d_pixel);

      dest+=4;      
    }


    /* Convert the odd trailing pixel */

    if (iface->d_width&1) {
      WRITE16(dest,
	    DitherTab_r565_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g565_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b565_44[count&0x3][y&0x3][*((int32*)source)&0xff]);

      source+=4;
      dest+=2;
    }

    
    source+=iface->s_add;
    dest+=iface->d_add;

    y++;
  }

}



void ConvertC_32rgb888_8rgb332_dither(HermesConverterInterface *iface)
{
  char8 *source=iface->s_pixels;
  char8 *dest=iface->d_pixels;
  int32 d_pixel;
  int y=0,count;

 
  while (y<iface->d_height) {
   
    /* Get counter for this scanline */
    count=iface->d_width;


    /* TODO: alignment loop */


    /* Convert 4 pixels at a time */

    while (count>3) {
      d_pixel=DWORD_BYTE0(
	    DitherTab_r332_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g332_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b332_44[count&0x3][y&0x3][*((int32*)source)&0xff]);
      count--;
      source+=4;

      d_pixel|=DWORD_BYTE1(
	    DitherTab_r332_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g332_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b332_44[count&0x3][y&0x3][*((int32*)source)&0xff]);
      count--;
      source+=4;

      d_pixel|=DWORD_BYTE2(
	    DitherTab_r332_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g332_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b332_44[count&0x3][y&0x3][*((int32*)source)&0xff]);
      count--;
      source+=4;

      d_pixel|=DWORD_BYTE3(
	    DitherTab_r332_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g332_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b332_44[count&0x3][y&0x3][*((int32*)source)&0xff]);
      count--;
      source+=4;

      WRITE32(dest,d_pixel);

      dest+=4;
    }


    /* Write trailing pixels */
    while (count--) {
      *dest=DitherTab_r332_44[count&0x3][y&0x3][(*((int32*)source)>>16)&0xff]|
	    DitherTab_g332_44[count&0x3][y&0x3][(*((int32*)source)>>8)&0xff]|
            DitherTab_b332_44[count&0x3][y&0x3][*((int32*)source)&0xff];

      source+=4;
      dest++;
    }

    source+=iface->s_add;
    dest+=iface->d_add;

    y++;
  }

}
