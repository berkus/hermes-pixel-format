/* 

   Generic C converter (from 8 bit indexed) for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/


#include "HermConf.h"
#include "HeadC.h"



/* -------------------------------------------------------------------------

                              NORMAL CONVERTERS
   
   ------------------------------------------------------------------------- */


void ConvertC_index8_32(HermesConverterInterface *iface)
{ int i;
  char8 s_pixel;
  int32 d_pixel;
  char8 *source=(char8 *)iface->s_pixels;
  char8 *dest=(char8 *)iface->d_pixels;

  do {
    
    for(i=0;i<iface->s_width;i++,source++,dest+=4)
    { s_pixel=(char8)*(source);

      d_pixel=iface->lookup[s_pixel];
      WRITE32(dest,d_pixel);
    }
    
    source+=iface->s_add;
    dest+=iface->d_add;
  } while (--iface->s_height);
}


void ConvertC_index8_24(HermesConverterInterface *iface)
{ int count;
  int32 s_pixel,s_pixel2;
  int32 d_pixel;
  char8 *d_ptr=(char8 *)&d_pixel;
  char8 *source=iface->s_pixels;
  char8 *dest=iface->d_pixels;

  do {

    count=iface->d_width>>2;

    while (count--) {

      #if defined __LITTLE_ENDIAN__

        s_pixel=iface->lookup[*source++];
        s_pixel2=iface->lookup[*source++];
      
        s_pixel=(s_pixel&0xffffff)|(s_pixel2<<24);
        WRITE32(dest,s_pixel);
      
        s_pixel=iface->lookup[*source++];
        s_pixel2=((s_pixel2>>8)&0xffff)|(s_pixel<<16);
        WRITE32(dest+1,s_pixel2);
      
        s_pixel2=iface->lookup[*source++];
        s_pixel=((s_pixel>>16)&0xff)|(s_pixel2<<8);
        WRITE32(dest+2,s_pixel);
      
      #elif defined __BIG_ENDIAN__
      
	s_pixel=iface->lookup[*source++];
    	s_pixel2=iface->lookup[*source++];
        
    	s_pixel=(s_pixel<<8)|((s_pixel2>>16)&0xff);
    	WRITE32(dest,s_pixel);
    
    	s_pixel=iface->lookup[*source++];
    	s_pixel2=(s_pixel2<<16)|((s_pixel>>8)&0xffff);
    	WRITE32(dest+1,s_pixel2);
    
    	s_pixel2=iface->lookup[*source++];
    	s_pixel=(s_pixel<<24)|(s_pixel2&0xffffff);
    	WRITE32(dest+2,s_pixel); 

      #endif
      
      dest+=12;
    }
    
    count=iface->d_width&0x3;
    while (count--) {
      d_pixel=iface->lookup[*source++];

      *(dest+R_24)=*(d_ptr+R_32);
      *(dest+G_24)=*(d_ptr+G_32);
      *(dest+B_24)=*(d_ptr+B_32);

      dest+=3;
    }

    source+=iface->s_add;
    dest+=iface->d_add;
    
  } while (--iface->d_height);

}



void ConvertC_index8_16(HermesConverterInterface *iface)
{ char8 *source=iface->s_pixels;
  char8 *dest=iface->d_pixels;
  unsigned int count,c;

  do {

    count=iface->s_width;

    if(((int)dest&0x3)!=0)
    { WRITE16(dest++,(short16)iface->lookup[*source++]);
      dest++;
      count--;
    }


    if ((c=(count>>1)))
    do {
      WRITE32(dest,(DWORD_BYTE0(iface->lookup[(char8)*(source)])|
	            DWORD_BYTE2(iface->lookup[(char8)*(source+1)])));
      dest+=4;
      source+=2;
    } while (--c);


    if(count&1)
    WRITE16(dest,(short16)iface->lookup[*source]);


    source+=iface->s_add;
    dest+=iface->d_add;
  } while (--iface->s_height);
}



/* -------------------------------------------------------------------------

                              STRETCH CONVERTERS
   
   ------------------------------------------------------------------------- */


void ConvertC_index8_32_S(HermesConverterInterface *iface)
{
  unsigned int x,y=0,count;
  unsigned int dy=(iface->s_height<<16)/iface->d_height;
  unsigned int dx=(iface->s_width<<16)/iface->d_width;
  char8 *source =iface->s_pixels;
  
  do {

    count=iface->d_width; 
    x=0;

    do {
      *((int32*)iface->d_pixels)=iface->lookup[*(source+(x>>16))];
      x+=dx;
      iface->d_pixels+=4;
    } while(--count);

    /* Go to next destination row */
    iface->d_pixels+=iface->d_add;
    
    /* Calculate amount of rows to move in source surface */
    y+=dy;
   
    source+=(y>>16)*iface->s_pitch;
    y &= 0xffff;
  } while (--iface->d_height);
}



/* Quick hack of a index 8 to 16 stretch converter */

void ConvertC_index8_16_S(HermesConverterInterface *iface)
{
  unsigned int x,y=0,count;
  unsigned int dy=(iface->s_height<<16)/iface->d_height;
  unsigned int dx=(iface->s_width<<16)/iface->d_width;
  char8 *source=iface->s_pixels;
  char8 *dest=iface->d_pixels;

  do {

    /* Do a two pixel at a time loop */

    count=iface->d_width>>1; 
    x=0;

    while (count--) {
      *((int32*)dest)=DWORD_BYTE0(iface->lookup[*(source+(x>>16))]) |
	              DWORD_BYTE2(iface->lookup[*(source+((x+dx)>>16))]);
      x+=2*dx;
      dest+=4;
    }

    /* Clean up remaining pixel if odd width */

    if (iface->d_width & 1) {
      *((short16*)dest)=(short16)iface->lookup[*(source+(x>>16))];
      dest+=2;
    }


    /* Go to next destination row */
    dest+=iface->d_add;
    
    /* Calculate amount of rows to move in source surface */
    y+=dy;

    source+=(y>>16)*iface->s_pitch;
    y &= 0xffff;
  } while (--iface->d_height);
}
