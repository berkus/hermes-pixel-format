/*
   32 bit to * blitters for the HERMES library
   Copyright (c) 2000 Daniel Vogel (666@grafzahl.de)
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include "HermConf.h"
#include "HeadC.h"


/* -------------------------------------------------------------------------

                              NORMAL BLITTERS
   
   ------------------------------------------------------------------------- */

void ConvertC_32rgba8888_32rgb888_blit(char8 *source, char8 *dest, unsigned int count,
				unsigned int inc_source)
{
  int32 s_pixel,d_pixel,r,g,b,a;
  char8 *s_ptr=(char8 *) &s_pixel, tmp;

  do
  {
    s_pixel=READ32(source);
    d_pixel=READ32(dest);

    a = s_pixel & 0xFF;
    r = ((d_pixel & 0x00FF0000) >> 16) + ((((s_pixel & 0xFF000000) >> 24) - ((d_pixel & 0x00FF0000) >> 16) ) * a ) >> 8;
    g = ((d_pixel & 0x0000FF00) >>  8) + ((((s_pixel & 0x00FF0000) >> 16) - ((d_pixel & 0x0000FF00) >>  8) ) * a ) >> 8;
    b = ((d_pixel & 0x000000FF)) + ((((s_pixel & 0x0000FF00) >>  8) - ((d_pixel & 0x000000FF) >> 0  ) ) * a ) >> 8;
    
    WRITE32(dest, (r << 16) | (g << 8) | b);

    dest+=4;
    source+=4;
  } while(--count);
}

#ifdef C_PLUS_PLUS_COMMENTS_DONT_SUCK_ANYMORE

/* TO 16 RGB 565 */

void ConvertC_32rgb888_16rgb565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 s_pixel;
  int32 *dest_32=(int32 *)dest;
  int32 *source_32=(int32 *)source;

  /* If the current pixel isn't dword aligned, try write one pixel first */
  
  if((int)dest_32&0x3)
  { s_pixel=((*source_32>>8)&0xf800)|
            ((*source_32>>5)&0x7e0)|
            ((*source_32>>3)&0x1f);

    *((short16 *)dest_32)=(short16)s_pixel;
 
    dest_32=(int32 *)(dest+2);
    source_32++;
 
    count--;
  }

  /* Write blocks of two pixels */

  for(i=count>>1;i;i--)
  { /*This horrible construct is actually faster than loading into a variable*/
    #if defined __LITTLE_ENDIAN__
    *dest_32++=((*source_32>>8)&0xf800)|
	       ((*source_32>>5)&0x7e0)|
	       ((*source_32>>3)&0x1f)|
	       ((*(source_32+1)<<8)&0xf8000000)|
	       ((*(source_32+1)<<11)&0x7e00000)|
	       ((*(source_32+1)<<13)&0x1f0000);
    #elif defined __BIG_ENDIAN__
    *dest_32++=((*(source_32+1)>>8)&0xf800)|
	       ((*(source_32+1)>>5)&0x7e0)|
	       ((*(source_32+1)>>3)&0x1f)|
	       ((*source_32<<8)&0xf8000000)|
	       ((*source_32<<11)&0x7e00000)|
	       ((*source_32<<13)&0x1f0000);
    #endif

    source_32+=2; 
  }
  
  /* Eventually, write a single odd pixel that might be left */
  if(count&1)
  { s_pixel=*source_32;

    WRITE16(dest_32,(short16)(((s_pixel>>8)&0xf800)|
	            ((s_pixel>>5)&0x7e0)|
	            ((s_pixel>>3)&0x1f)));
  }
}

/* -------------------------------------------------------------------------

                              STRETCH CONVERTERS
   
   ------------------------------------------------------------------------- */


void ConvertC_32rgb888_32bgr888_S(char8 *source,char8 *dest,unsigned int count,
				  unsigned int inc_source)
{ int32 s_pixel;
  unsigned int x=0;
  char8 *s_ptr=(char8 *)&s_pixel,tmp;

  do
  { s_pixel=*((int32*)source+(x>>16));

    tmp=*(s_ptr+R_32); 
    *(s_ptr+R_32)=*(s_ptr+B_32); 
    *(s_ptr+B_32)=tmp;

    WRITE32(dest,s_pixel);

    dest+=4;
    x+=inc_source;
  } while (--count);
}



void ConvertC_32rgb888_32rgba888_S(char8 *source,char8 *dest,
				   unsigned int count,
				   unsigned int inc_source)
{ unsigned int x=0;

  do
  { *((int32*)dest)=*((int32*)source+(x>>16))<<8;

    dest+=4;
    x+=inc_source;
  } while(--count);
}



void ConvertC_32rgb888_32bgra888_S(char8 *source,char8 *dest,
				   unsigned int count,
				   unsigned int inc_source)
{ int32 s_pixel;
  unsigned int x=0; 
  char8 *s_ptr=(char8 *)&s_pixel,tmp;

  do
  { 
    s_pixel=*((int32*)source+(x>>16));

    tmp=*(s_ptr+R_32); 
    *(s_ptr+R_32)=*(s_ptr+B_32); 
    *(s_ptr+B_32)=tmp;

    WRITE32(dest,s_pixel<<8);

    dest+=4;
    x+=inc_source;
  } while (--count);
}




void ConvertC_32rgb888_16rgb565_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Align mod 4 */
  if ((int)dest&3) {
    *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>8)&0xf800)|
				((*((int32*)source+(x>>16))>>5)&0x7e0)|
				((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source; dest+=2;
    count--;
  }
  
  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {
    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>8)&0xf800)|
		  ((*((int32*)source+(x>>16))>>5)&0x7e0)|
		  ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>8)&0xf800)|
		   ((*((int32*)source+(x>>16))>>5)&0x7e0)|
		   ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>8)&0xf800)|
			      ((*((int32*)source+(x>>16))>>5)&0x7e0)|
			      ((*((int32*)source+(x>>16))>>3)&0x1f));

}



void ConvertC_32rgb888_16bgr565_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Align mod 4 */
  if ((int)dest&3) {
    *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>19)&0x1f)|
				((*((int32*)source+(x>>16))>>5)&0x7e0)|
				((*((int32*)source+(x>>16))<<8)&0xf800));
    x+=inc_source; dest+=2;
    count--;
  }

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {

    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>19)&0x1f)|
		  ((*((int32*)source+(x>>16))>>5)&0x7e0)|
		  ((*((int32*)source+(x>>16))<<8)&0xf800));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>19)&0x1f)|
		   ((*((int32*)source+(x>>16))>>5)&0x7e0)|
		   ((*((int32*)source+(x>>16))<<8)&0xf800));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  }

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>19)&0x1f)|
			      ((*((int32*)source+(x>>16))>>5)&0x7e0)|
			      ((*((int32*)source+(x>>16))<<8)&0xf800));

}



void ConvertC_32rgb888_16rgb555_S(char8 *source,char8 *dest,unsigned int count,
				  unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {
    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>9)&0x7c00)|
		  ((*((int32*)source+(x>>16))>>6)&0x3e0)|
		  ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>9)&0x7c00)|
		   ((*((int32*)source+(x>>16))>>6)&0x3e0)|
		   ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>9)&0x7c00)|
			      ((*((int32*)source+(x>>16))>>6)&0x3e0)|
			      ((*((int32*)source+(x>>16))>>3)&0x1f));

}


void ConvertC_32rgb888_16bgr555_S(char8 *source,char8 *dest,unsigned int count,
				  unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {

    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>19)&0x1f)|
		  ((*((int32*)source+(x>>16))>>6)&0x3e0)|
		  ((*((int32*)source+(x>>16))<<7)&0x7c00));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>19)&0x1f)|
		   ((*((int32*)source+(x>>16))>>6)&0x3e0)|
		   ((*((int32*)source+(x>>16))<<7)&0x7c00));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>19)&0x1f)|
			      ((*((int32*)source+(x>>16))>>6)&0x3e0)|
			      ((*((int32*)source+(x>>16))<<7)&0x7c00));

}



void ConvertC_32rgb888_8rgb332_S(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;


  /* Write single pixels until the destination address is aligned mod 4 */

  while (((int)dest&0x3)!=0) {
    *dest=(char8)(((*((int32*)source+(x>>16))>>16)&0xe0)|
		  ((*((int32*)source+(x>>16))>>11)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;
    dest++;
    count--;
    if (!count) return;
  }


  /* Write blocks of four pixels now */

  c=count>>2;

  while (c--) {
    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>16)&0xe0)|
                  ((*((int32*)source+(x>>16))>>11)&0x1c)|
                  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE1(((*((int32*)source+(x>>16))>>16)&0xe0)|
		  ((*((int32*)source+(x>>16))>>11)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE2(((*((int32*)source+(x>>16))>>16)&0xe0)|
		  ((*((int32*)source+(x>>16))>>11)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE3(((*((int32*)source+(x>>16))>>16)&0xe0)|
		  ((*((int32*)source+(x>>16))>>11)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    WRITE32(dest,p);

    dest+=4;
  }

  /* Write up to three trailing pixels */

  c=count&0x3;

  while (c--) {
    *dest=(char8)(((*((int32*)source+(x>>16))>>16)&0xe0)|
		  ((*((int32*)source+(x>>16))>>11)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;
    dest++;
  }
}

#endif
