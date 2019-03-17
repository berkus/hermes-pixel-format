/*
   16 bit to * converters for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include "HermConf.h"
#include "HeadC.h"


/* TO 32 BIT RGB */

void ConvertC_16rgb565_32rgb888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_pixel;

  do
  { d_pixel=(int32)(READ16(source));

    d_pixel=((d_pixel&0xf800)<<8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<3);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel);

    source+=2;
    dest+=4;
  } while (--count);
}


/* TO 32 BIT BGR */

void ConvertC_16rgb565_32bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_pixel;

  do
  { d_pixel=(int32)(READ16(source));

    d_pixel=((d_pixel&0xf800)>>8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<19);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel);

    source+=2;
    dest+=4;
  } while (--count);
}


/* TO 32 BIT RGBA */

void ConvertC_16rgb565_32rgba888(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ int32 d_pixel;

  do
  { d_pixel=(int32)(READ16(source));

    d_pixel=((d_pixel&0xf800)<<8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<3);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel<<8);

    source+=2;
    dest+=4;
  } while (--count);
}



/* TO 32 BIT BGRA */

void ConvertC_16rgb565_32bgra888(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ int32 d_pixel;

  do
  { d_pixel=(int32)(READ16(source));

    d_pixel=((d_pixel&0xf800)>>8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<19);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel<<8);

    source+=2;
    dest+=4;
  } while (--count);
}



/* TO 24 BIT RGB */

void ConvertC_16rgb565_24rgb888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_pixel;
  char8 *d_ptr=(char8 *)&d_pixel;

  do
  { d_pixel=(int32)(READ16(source));

    d_pixel=((d_pixel&0xf800)<<8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<3);
    d_pixel|=0x030103;

    *(dest+R_24)=*(d_ptr+R_32);
    *(dest+G_24)=*(d_ptr+G_32);
    *(dest+B_24)=*(d_ptr+B_32);
    
    source+=2;
    dest+=3;
  } while (--count);
}


/* TO 24 BIT BGR */

void ConvertC_16rgb565_24bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_pixel;
  char8 *d_ptr=(char8 *)&d_pixel;

  do
  { d_pixel=(int32)(READ16(source));

    d_pixel=((d_pixel&0xf800)<<8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<3);
    d_pixel|=0x030103;

    /* Red and blue are swapped here */
    *(dest+B_24)=*(d_ptr+R_32);
    *(dest+G_24)=*(d_ptr+G_32);
    *(dest+R_24)=*(d_ptr+B_32);

    source+=2;
    dest+=3;
  } while (--count);
}





/* TO 16 BIT BGR 565 */

void ConvertC_16rgb565_16bgr565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 s_pixel;

  /* If we are not aligned to a dword, try and convert a single pixel */
  if(((int)dest&0x3)!=0)
  { s_pixel=(int32)READ16(source);

    /* Swap around R and B, leave G unchanged */
    s_pixel=(s_pixel>>11)|(s_pixel&0x7e0)|((s_pixel<<11)&0xf800);

    WRITE16(dest,(short16)s_pixel);

    count--;
    dest+=2; source+=2;
  }

  /* Now copy blocks of dwords */
  for(i=0;i<count>>1;i++,source+=4,dest+=4)
  { s_pixel=READ32(source);

    /* Leave G unchanged, shift R to the right and B to the left */
    s_pixel=(s_pixel&0x07e007e0)|((s_pixel&0xf800f800)>>11)|
            ((s_pixel&0x001f001f)<<11);
    
    WRITE32(dest,s_pixel);
  }

  if(count&1)
  { s_pixel=(int32)READ16(source);

    /* Swap around R and B, leave G unchanged */
    s_pixel=(s_pixel>>11)|(s_pixel&0x7e0)|((s_pixel<<11)&0xf800);

    WRITE16(dest,(short16)s_pixel);
  }
}



/* TO 16 BIT RGB 555 */

void ConvertC_16rgb565_16rgb555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 s_pixel;

  /* If we are not aligned to a dword, try and convert a single pixel */
  if(((int)dest&0x3)!=0)
  { s_pixel=(int32)READ16(source);

    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    s_pixel=(s_pixel&0x1f)|((s_pixel&0xf800)>>1)|((s_pixel&0x7c0)>>1);

    WRITE16(dest,(short16)s_pixel);

    count--;
    dest+=2; source+=2;
  }

  /* Now copy blocks of dwords */
  for(i=0;i<count>>1;i++,source+=4,dest+=4)
  { s_pixel=READ32(source);

    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    s_pixel=(s_pixel&0x001f001f)|((s_pixel&0xf800f800)>>1)|
            ((s_pixel&0x07c007c0)>>1);
   
    WRITE32(dest,s_pixel);
  }

  if(count&1)
  { s_pixel=(int32)READ16(source);

    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    s_pixel=(s_pixel&0x1f)|((s_pixel&0xf800)>>1)|((s_pixel&0x7c0)>>1);

    WRITE16(dest,(short16)s_pixel);
  }
}



/* TO 16 BIT BGR 555 */

void ConvertC_16rgb565_16bgr555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 s_pixel;

  /* If we are not aligned to a dword, try and convert a single pixel */
  if(((int)dest&0x3)!=0)
  { s_pixel=(int32)READ16(source);

    /* Shift red right by 11, mask green and shift right one, shift blue
       left ten */
    s_pixel=((s_pixel&0xf800)>>11)|((s_pixel&0x7c0)>>1)|((s_pixel&0x1f)<<10);

    WRITE16(dest,(short16)s_pixel);

    count--;
    dest+=2; source+=2;
  }

  /* Now copy blocks of dwords */
  for(i=0;i<count>>1;i++,source+=4,dest+=4)
  { s_pixel=READ32(source);

    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    s_pixel=((s_pixel&0xf800f800)>>11)|((s_pixel&0x07c007c0)>>1)|
            ((s_pixel&0x001f001f)<<10);
   
    WRITE32(dest,s_pixel);
  }

  if(count&1)
  { s_pixel=(int32)READ16(source);

    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    s_pixel=((s_pixel&0xf800)>>11)|((s_pixel&0x7c0)>>1)|((s_pixel&0x1f)<<10);

    WRITE16(dest,(short16)s_pixel);
  }
}


/* TO 8 BIT RGB 332 */

void ConvertC_16rgb565_8rgb332(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_block,d_block;
  unsigned int i;

  /* Align to dword first */
  while(((int)dest&0x3)!=0)
  { s_block=(int32)READ16(source);
  
    s_block=((s_block&0xe000)>>8)|((s_block&0x0700)>>6)|
            ((s_block&0x18)>>3);

    *(dest)=(char8)s_block;

    count--;
    if (!count) return;
    
    source+=2;
    dest++;
  }


  /* Write blocks of four pixels */
  for(i=0;i<count>>2;i++,source+=8,dest+=4)
  { /* Read and process first two pixels */
    s_block=READ32(source);
  
    d_block=((s_block&0xe000e000)>>8)|((s_block&0x07000700)>>6)|
            ((s_block&0x00180018)>>3);
    d_block=(d_block&0xff)|((d_block&0xff0000)>>8);

    /* And the second two */
    s_block=READ32(source+1);

    s_block=((s_block&0xe000e000)>>8)|((s_block&0x07000700)>>6)|
            ((s_block&0x00180018)>>3);
    s_block=(s_block&0xff)|((s_block&0xff0000)>>8);
   
    /* Put it all in one dword and write it */
    #if defined __LITTLE_ENDIAN__
    d_block|=(s_block<<16);
    #elif defined __BIG_ENDIAN__
    d_block<<=16;
    d_block|=s_block;
    #endif

    WRITE32(dest,d_block);
  }

  /* Clean up remaining pixels */
  count&=3;

  while (count--)
  { s_block=(int32)READ16(source);
  
    *dest=(char8)(((s_block&0xe000)>>8)|((s_block&0x0700)>>6)|
		  ((s_block&0x18)>>3));
    dest++;
    source+=2;
  }
}



/* -------------------------------------------------------------------------

                              STRETCH CONVERTERS
   
   ------------------------------------------------------------------------- */


void ConvertC_16rgb565_32rgb888_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0;
  int32 p; 

  do {
    p=((*((short16*)source+(x>>16))&0xf800)<<8)|
      ((*((short16*)source+(x>>16))&0x7e0)<<5)|
      ((*((short16*)source+(x>>16))&0x1f)<<3)|
      0x030103;

    x+=inc_source;
 
    WRITE32(dest,p);

    dest+=4;
  } while (--count);
}




void ConvertC_16rgb565_32bgr888_S(char8 *source,char8 *dest,unsigned int count,
				  unsigned int inc_source)
{ int32 d_pixel;
  unsigned int x=0;

  do
  { d_pixel=(int32)*((short16*)source+(x>>16));

    d_pixel=((d_pixel&0xf800)>>8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<19);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel);
    
    dest+=4;
    x+=inc_source;
  } while (--count);
}



void ConvertC_16rgb565_32rgba888_S(char8 *source,char8 *dest,
				   unsigned int count,
				   unsigned int inc_source)
{ int32 d_pixel;
  unsigned int x=0;

  do
  { d_pixel=(int32)*((short16*)source+(x>>16));

    d_pixel=((d_pixel&0xf800)<<8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<3);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel<<8);
    
    dest+=4;
    x+=inc_source;
  } while (--count);
}



void ConvertC_16rgb565_32bgra888_S(char8 *source,char8 *dest,
				   unsigned int count,
				   unsigned int inc_source)
{ int32 d_pixel;
  unsigned int i,x=0;

  for(i=0;i<count;i++,dest+=4,x+=inc_source)
  { d_pixel=(int32)*((short16*)source+(x>>16));

    d_pixel=((d_pixel&0xf800)>>8)|((d_pixel&0x7e0)<<5)|((d_pixel&0x1f)<<19);
    d_pixel|=0x030103;

    WRITE32(dest,d_pixel<<8);
    
    dest+=4;
    x+=inc_source;
  } while (--count);
}



void ConvertC_16rgb565_16bgr565_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;

  /* If we are not aligned to a dword, try and convert a single pixel */
  if(((int)dest&0x3)!=0) {

    /* Swap r and b, leave g untouched */
  *((short16*)dest)=(short16)(*((short16*)source+(x>>16))>>11)|
                             (*((short16*)source+(x>>16))&0x7e0)|
                             ((*((short16*)source+(x>>16))<<11)&0xf800);
     x+=inc_source;
     count--;
  }

  c=count>>1;

  while (c--) {

    /* Swap r and b, leave g untouched */

    p=DWORD_BYTE0((*((short16*)source+(x>>16))>>11)|
		  (*((short16*)source+(x>>16))&0x7e0)|
		  ((*((short16*)source+(x>>16))<<11)&0xf800));

    x+=inc_source;

    p=DWORD_BYTE2((*((short16*)source+(x>>16))>>11)|
		  (*((short16*)source+(x>>16))&0x7e0)|
		  ((*((short16*)source+(x>>16))<<11)&0xf800));

    x+=inc_source;

    *((int32*)dest)=p;

    dest += 4;
  }

  if(count&1)
  *((short16*)dest)=(short16)(*((short16*)source+(x>>16))>>11)|
                             (*((short16*)source+(x>>16))&0x7e0)|
                             ((*((short16*)source+(x>>16))<<11)&0xf800);
}



void ConvertC_16rgb565_16rgb555_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;

  /* If we are not aligned to a dword, try and convert a single pixel */
  if(((int)dest&0x3)!=0) {
  *((short16*)dest)=(short16)((*((short16*)source+(x>>16))&0xf800)>>1)|
                             ((*((short16*)source+(x>>16))&0x7c0)>>1)|
                             (*((short16*)source+(x>>16))&0x1f);
     x+=inc_source;
     count--;
  }

  c=count>>1;

  while (c--) {
    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    p=DWORD_BYTE0(((*((short16*)source+(x>>16))&0xf800)>>1)|
		  ((*((short16*)source+(x>>16))&0x7c0)>>1)|
		  (*((short16*)source+(x>>16))&0x1f));

    x+=inc_source;

    p|=DWORD_BYTE2(((*((short16*)source+(x>>16))&0xf800)>>1)|
		   ((*((short16*)source+(x>>16))&0x7c0)>>1)|
		   (*((short16*)source+(x>>16))&0x1f));

    x+=inc_source;

    *((int32*)dest)=p;

    dest += 4;
  }

  if(count&1)
  *((short16*)dest)=(short16)((*((short16*)source+(x>>16))&0xf800)>>1)|
                             ((*((short16*)source+(x>>16))&0x7c0)>>1)|
                             (*((short16*)source+(x>>16))&0x1f);
}



void ConvertC_16rgb565_16bgr555_S(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;

  /* If we are not aligned to a dword, try and convert a single pixel */
  if(((int)dest&0x3)!=0) {

  *((short16*)dest)=(short16)((*((short16*)source+(x>>16))&0xf800)>>11)|
                             ((*((short16*)source+(x>>16))&0x7c0)>>1)|
                             ((*((short16*)source+(x>>16))&0x1f)<<10);
     x+=inc_source;
     count--;
  }

  c=count>>1;

  while (c--) {
    /* Leave blue untouched, mask red and shift by one, mask green and shift
       by one */
    p=DWORD_BYTE0(((*((short16*)source+(x>>16))&0xf800)>>11)|
		  ((*((short16*)source+(x>>16))&0x7c0)>>1)|
		  ((*((short16*)source+(x>>16))&0x1f)<<10));

    x+=inc_source;

    p|=DWORD_BYTE2(((*((short16*)source+(x>>16))&0xf800)>>11)|
		   ((*((short16*)source+(x>>16))&0x7c0)>>1)|
		   ((*((short16*)source+(x>>16))&0x1f)<<10));

    x+=inc_source;

    *((int32*)dest)=p;

    dest += 4;
  }

  if(count&1)
  *((short16*)dest)=(short16)((*((short16*)source+(x>>16))&0xf800)>>11)|
                             ((*((short16*)source+(x>>16))&0x7c0)>>1)|
                             ((*((short16*)source+(x>>16))&0x1f)<<10);
}



void ConvertC_16rgb565_8rgb332_S(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ unsigned int x=0,c;
  int32 p;

  /* Write single pixels until the destination address is aligned mod 4 */

  while (((int)dest&0x3)!=0) {
    *dest=((*((short16*)source+(x>>16))>>8)&0xe0)|
          ((*((short16*)source+(x>>16))>>6)&0x1c)|
          ((*((short16*)source+(x>>16))>>3)&0x3);
    x+=inc_source;
    dest++;
    count--;
    if (!count) return;
  }


  /* Write blocks of four pixels now */

  c=count>>2;

  while (c--) {
    p=DWORD_BYTE0(((*((short16*)source+(x>>16))>>8)&0xe0)|
                  ((*((short16*)source+(x>>16))>>6)&0x1c)|
                  ((*((short16*)source+(x>>16))>>3)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE1(((*((short16*)source+(x>>16))>>8)&0xe0)|
                  ((*((short16*)source+(x>>16))>>6)&0x1c)|
                  ((*((short16*)source+(x>>16))>>3)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE2(((*((short16*)source+(x>>16))>>8)&0xe0)|
                  ((*((short16*)source+(x>>16))>>6)&0x1c)|
                  ((*((short16*)source+(x>>16))>>3)&0x3));
    x+=inc_source;

    p|=
      DWORD_BYTE3(((*((short16*)source+(x>>16))>>8)&0xe0)|
                  ((*((short16*)source+(x>>16))>>6)&0x1c)|
                  ((*((short16*)source+(x>>16))>>3)&0x3));
    x+=inc_source;

    WRITE32(dest,p);

    dest+=4;
  }

  /* Write up to three trailing pixels */

  c=count&0x3;

  while (c--) {
    *dest=((*((short16*)source+(x>>16))>>8)&0xe0)|
          ((*((short16*)source+(x>>16))>>6)&0x1c)|
          ((*((short16*)source+(x>>16))>>3)&0x3);
    x+=inc_source;
    dest++;
  }
}




