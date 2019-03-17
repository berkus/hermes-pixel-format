/*
   muhmuh converters for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
 
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/
#include "HermConf.h"
#include "HeadC.h"


/* TO 32 RGB */

void ConvertC_muhmu32_32rgb888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;

  do
  { s_pixel=READ32(source);

    s_pixel=(s_pixel&0xff)|((s_pixel&(0xff<<10))>>2)|((s_pixel&(0xff<<20))>>4);

    WRITE32(dest,s_pixel);
    
    dest+=4;
    source+=4;
  } while(--count);
}


/* TO 32 BGR */

void ConvertC_muhmu32_32bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;

  do
  { s_pixel=READ32(source);

    s_pixel=((s_pixel&0xff)<<16)|((s_pixel&(0xff<<10))>>2)|
            ((s_pixel&(0xff<<20))>>12);

    WRITE32(dest,s_pixel);

    dest+=4;
    source+=4;
  } while(--count);
}




/* TO 32 RGBA */

void ConvertC_muhmu32_32rgba888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;

  do
  { s_pixel=READ32(source);

    s_pixel=(s_pixel&0xff)|((s_pixel&(0xff<<10))>>2)|((s_pixel&(0xff<<20))>>4);

    WRITE32(dest,(s_pixel<<8)|0xff);
    
    dest+=4;
    source+=4;
  } while(--count);
}


/* TO 32 BGRA */

void ConvertC_muhmu32_32bgra888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;

  do
  { s_pixel=READ32(source);

    s_pixel=((s_pixel&0xff)<<16)|((s_pixel&(0xff<<10))>>2)|
            ((s_pixel&(0xff<<20))>>12);

    WRITE32(dest,(s_pixel<<8)|0xff);

    dest+=4;
    source+=4;
  } while(--count);
}



/* TO 24 RGB */

void ConvertC_muhmu32_24rgb888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;
  char8 *s_point=(char8 *)&s_pixel;

  do
  { s_pixel=READ32(source);
    s_pixel=(s_pixel&0xff)|((s_pixel&(0xff<<10))>>2)|((s_pixel&(0xff<<20))>>4);

    *(dest+R_24)=*(s_point+R_32);
    *(dest+G_24)=*(s_point+G_32);
    *(dest+B_24)=*(s_point+B_32);

    source+=4;
    dest+=3;
  } while(--count);
}


/* TO 24 BGR */

void ConvertC_muhmu32_24bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;
  char8 *s_point=(char8 *)&s_pixel;

  do
  { s_pixel=READ32(source);
    s_pixel=(s_pixel&0xff)|((s_pixel&(0xff<<10))>>2)|((s_pixel&(0xff<<20))>>4);
 
    /* Note that R and B are swapped */
    *(dest+B_24)=*(s_point+R_32);
    *(dest+G_24)=*(s_point+G_32);
    *(dest+R_24)=*(s_point+B_32);

    source+=4;
    dest+=3;
  } while(--count);
}


/* TO 16 RGB 565 */

void ConvertC_muhmu32_16rgb565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;
  
  /* If the current pixel isn't dword aligned, try write one pixel first */

  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
  
    r=(s_pixel>>12)&0xf800;
    g=(s_pixel>>7)&0x7e0;
    b=(s_pixel>>3)&0x1f;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);

    source+=4; 
    dest+=2;
    count--;
  }

  /* Write blocks of two pixels */
  
  for(i=0;i<count>>1;i++,source+=8, dest+=4)
  { s_pixel=READ32(source);
     
    d_pixelblock=DWORD_BYTE0(((s_pixel>>12)&0xf800)|
			     ((s_pixel>>7)&0x7e0)|
			     ((s_pixel>>3)&0x1f));

    s_pixel=READ32(source+1);
     
    d_pixelblock|=DWORD_BYTE2(((s_pixel>>12)&0xf800)|
			      ((s_pixel>>7)&0x7e0)|
			      ((s_pixel>>3)&0x1f));
   
    WRITE32(dest,d_pixelblock);
  }


  /* Eventually, write a single odd pixel that might be left */

  if(count&1)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>12)&0xf800;
    g=(s_pixel>>7)&0x7e0;
    b=(s_pixel>>3)&0x1f;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}


/* TO 16 BGR 565 */

void ConvertC_muhmu32_16bgr565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;

  /* If the current pixel isn't dword aligned, try write one pixel first */

  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>23)&0x1f;
    g=(s_pixel>>7)&0x7e0;
    b=(s_pixel<<8)&0xf800;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);

    source+=4; 
    dest+=2;
    count--;
  }

  /* Write blocks of two pixels */
  
  for(i=0;i<count>>1;i++,source+=8, dest+=4)
  { s_pixel=READ32(source);

    d_pixelblock=DWORD_BYTE0(((s_pixel>>23)&0x1f)|
			     ((s_pixel>>7)&0x7e0)|
			     ((s_pixel<<8)&0xf800));

    s_pixel=READ32(source+1);

    d_pixelblock|=DWORD_BYTE2(((s_pixel>>23)&0x1f)|
			      ((s_pixel>>7)&0x7e0)|
			      ((s_pixel<<8)&0xf800));
   
    WRITE32(dest,d_pixelblock);
  }


  /* Eventually, write a single odd pixel that might be left */

  if(count&1)
  { s_pixel=READ32(source);

    r=(s_pixel>>23)&0x1f;
    g=(s_pixel>>7)&0x7e0;
    b=(s_pixel<<8)&0xf800;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}


/* TO 16 RGB 555 */


void ConvertC_muhmu32_16rgb555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;
  unsigned int i;


  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>13)&0x7c00;
    g=(s_pixel>>8)&0x3e0;
    b=(s_pixel>>3)&0x1f;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);

    source+=4; 
    dest+=2;
    count--;
  }

  for(i=0;i<count>>1;i++,source+=8,dest+=4)
  { s_pixel=READ32(source);

    d_pixelblock=DWORD_BYTE0(((s_pixel>>13)&0x7c00)|
			     ((s_pixel>>8)&0x3e0)|
			     ((s_pixel>>3)&0x1f));

    s_pixel=READ32(source+1);

    d_pixelblock|=DWORD_BYTE2(((s_pixel>>13)&0x7c00)|
			      ((s_pixel>>8)&0x3e0)|
			      ((s_pixel>>3)&0x1f));
   
    WRITE32(dest,d_pixelblock);
  }

  if(count&1)
  { s_pixel=READ32(source);

    r=(s_pixel>>13)&0x7c00;
    g=(s_pixel>>8)&0x3e0;
    b=(s_pixel>>3)&0x1f;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}



/* TO 16 BGR 555 */

void ConvertC_muhmu32_16bgr555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;
  unsigned int i;


  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>23)&0x1f;
    g=(s_pixel>>8)&0x3e0;
    b=(s_pixel<<7)&0x7c00;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);

    source+=4; 
    dest+=2;
    count--;
  }

  for(i=0;i<count>>1;i++,source+=8,dest+=4)
  { s_pixel=READ32(source);

    d_pixelblock=DWORD_BYTE0(((s_pixel>>23)&0x1f)|
			     ((s_pixel>>8)&0x3e0)|
			     ((s_pixel<<7)&0x7c00));

    s_pixel=READ32(source+1);

    d_pixelblock|=DWORD_BYTE2(((s_pixel>>19)&0x1f)|
			      ((s_pixel>>6)&0x3e0)|
			      ((s_pixel<<7)&0x7c00));
   
    WRITE32(dest,d_pixelblock);
  }

  if(count&1)
  { s_pixel=READ32(source);

    r=(s_pixel>>23)&0x1f;
    g=(s_pixel>>8)&0x3e0;
    b=(s_pixel<<7)&0x7c00;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}



/* TO 8 RGB 332 */

void ConvertC_muhmu32_8rgb332(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 s_pixel,d_block;
  char8 d_pixel;

  /* Process single pixels until we are dword aligned */

  while(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);

    d_pixel=(char8)(((s_pixel>>20)&0xe0)|
                    ((s_pixel>>13)&0x1c)|
                    ((s_pixel>>6)&0x3));

    *(dest)=d_pixel;

    count--;
    if (!count) return;
    dest++;
    source+=4;
  }  


  /* Now process blocks of four pixels */

  for(i=0;i<count>>2;i++,source+=16,dest+=4)
  { s_pixel=READ32(source);
    d_block=DWORD_BYTE0(((s_pixel>>20)&0xe0)|((s_pixel>>13)&0x1c)|
			((s_pixel>>6)&0x3));

    s_pixel=READ32(source+1);
    d_block|=DWORD_BYTE1(((s_pixel>>20)&0xe0)|((s_pixel>>13)&0x1c)|
			 ((s_pixel>>6)&0x3));
    
    s_pixel=READ32(source+2);
    d_block|=DWORD_BYTE2(((s_pixel>>20)&0xe0)|((s_pixel>>13)&0x1c)|
			 ((s_pixel>>6)&0x3));
   
    s_pixel=READ32(source+3);
    d_block|=DWORD_BYTE3(((s_pixel>>20)&0xe0)|((s_pixel>>13)&0x1c)|
			 ((s_pixel>>6)&0x3));

    WRITE32(dest,d_block);
  }

  /* Write all possibly remaining pixel */
 
  count&=3;

  while (count--)
  { s_pixel=READ32(source);

    *dest=(char8)(((s_pixel>>20)&0xe0)|
                  ((s_pixel>>13)&0x1c)|
                  ((s_pixel>>6)&0x3));
    dest++;
    source+=4;
  }  
}




/* -------------------------------------------------------------------------

                              STRETCH CONVERTERS
   
   ------------------------------------------------------------------------- */


void ConvertC_muhmu32_16rgb565_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {
    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>12)&0xf800)|
		  ((*((int32*)source+(x>>16))>>7)&0x7e0)|
		  ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>12)&0xf800)|
		   ((*((int32*)source+(x>>16))>>7)&0x7e0)|
		   ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>12)&0xf800)|
                              ((*((int32*)source+(x>>16))>>7)&0x7e0)|
                              ((*((int32*)source+(x>>16))>>3)&0x1f));

}



void ConvertC_muhmu32_16bgr565_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {

    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>23)&0x1f)|
		  ((*((int32*)source+(x>>16))>>7)&0x7e0)|
		  ((*((int32*)source+(x>>16))<<8)&0xf800));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>23)&0x1f)|
		   ((*((int32*)source+(x>>16))>>7)&0x7e0)|
		   ((*((int32*)source+(x>>16))<<8)&0xf800));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>23)&0x1f)|
                              ((*((int32*)source+(x>>16))>>7)&0x7e0)|
                              ((*((int32*)source+(x>>16))<<8)&0xf800));

}



void ConvertC_muhmu32_16rgb555_S(char8 *source,char8 *dest,unsigned int count,
				  unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {
    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>13)&0x7c00)|
		  ((*((int32*)source+(x>>16))>>8)&0x3e0)|
		  ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>13)&0x7c00)|
		   ((*((int32*)source+(x>>16))>>8)&0x3e0)|
		   ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>13)&0x7c00)|
                              ((*((int32*)source+(x>>16))>>8)&0x3e0)|
                              ((*((int32*)source+(x>>16))>>3)&0x1f));

}


void ConvertC_muhmu32_16bgr555_S(char8 *source,char8 *dest,unsigned int count,
				  unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p; 

  /* Try to write 2 pixel blocks */

  c=count>>1; 

  while (c--) {

    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>23)&0x1f)|
		  ((*((int32*)source+(x>>16))>>8)&0x3e0)|
		  ((*((int32*)source+(x>>16))<<7)&0x7c00));
    x+=inc_source;
 
    p|=DWORD_BYTE2(((*((int32*)source+(x>>16))>>23)&0x1f)|
		   ((*((int32*)source+(x>>16))>>8)&0x3e0)|
		   ((*((int32*)source+(x>>16))<<7)&0x7c00));
    x+=inc_source;
  
    *((int32*)dest)=p;

    dest+=4;
  } 

  /* Write trailing pixel */

  if (count&1)
  *((short16*)dest)=(short16)(((*((int32*)source+(x>>16))>>23)&0x1f)|
                              ((*((int32*)source+(x>>16))>>8)&0x3e0)|
                              ((*((int32*)source+(x>>16))<<7)&0x7c00));

}



void ConvertC_muhmu32_8rgb332_S(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;


  /* Write single pixels until the destination address is aligned mod 4 */

  while (((int)dest&0x3)!=0) {
    *dest=(char8)(((*((int32*)source+(x>>16))>>20)&0xe0)|
                  ((*((int32*)source+(x>>16))>>13)&0x1c)|
                  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;
    dest++;
    count--;
    if (!count) return;
  }


  /* Write blocks of four pixels now */

  c=count>>2;

  while (c--) {
    p=DWORD_BYTE0(((*((int32*)source+(x>>16))>>20)&0xe0)|
                  ((*((int32*)source+(x>>16))>>13)&0x1c)|
                  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE1(((*((int32*)source+(x>>16))>>20)&0xe0)|
		  ((*((int32*)source+(x>>16))>>13)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE2(((*((int32*)source+(x>>16))>>20)&0xe0)|
		  ((*((int32*)source+(x>>16))>>13)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE3(((*((int32*)source+(x>>16))>>20)&0xe0)|
		  ((*((int32*)source+(x>>16))>>13)&0x1c)|
		  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;

    WRITE32(dest,p);

    dest+=4;
  }

  /* Write up to three trailing pixels */

  c=count&0x3;

  while (c--) {
    *dest=(char8)(((*((int32*)source+(x>>16))>>20)&0xe0)|
                  ((*((int32*)source+(x>>16))>>13)&0x1c)|
                  ((*((int32*)source+(x>>16))>>6)&0x3));
    x+=inc_source;
    dest++;
  }
}
