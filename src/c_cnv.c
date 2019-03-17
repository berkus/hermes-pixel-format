/*
   C converter main loops for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/


#include "HermConf.h"
#include "Convert.h"
#include "H_Types.h"
#include "HeadC.h"



void ConvertC(HermesConverterInterface *iface)
{
  /* Simply loop through all scanlines */

  do {
    iface->func(iface->s_pixels,iface->d_pixels,iface->d_width,1);

    iface->s_pixels+=iface->s_pitch;
    iface->d_pixels+=iface->d_pitch;
  } while (--iface->d_height);
}



void ConvertCStretch(HermesConverterInterface *iface)
{ unsigned int y=0;
  unsigned int dy=(iface->s_height<<16)/iface->d_height;
  unsigned int dx=(iface->s_width<<16)/iface->d_width;

  /* We have the increment of y and x on the source surface now let's start */

  do {
    iface->func(iface->s_pixels,iface->d_pixels,iface->d_width,dx);

    iface->d_pixels+=iface->d_pitch;

    y+=dy;
    
    /* Check how many lines we need to step forward */

    iface->s_pixels+=(y>>16)*iface->s_pitch;
    y &= 0xffff;    
  } while (--iface->d_height);
}
