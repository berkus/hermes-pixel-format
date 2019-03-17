/*
   32 bit to * converters for the HERMES library
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


/* TO 32 BGR */

void ConvertC_32rgb888_32bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;
  char8 *s_ptr=(char8 *)&s_pixel,tmp;

  do
  { s_pixel=READ32(source);

    tmp=*(s_ptr+R_32); 
    *(s_ptr+R_32)=*(s_ptr+B_32); 
    *(s_ptr+B_32)=tmp;

    WRITE32(dest,s_pixel);

    dest+=4;
    source+=4;
  } while(--count);
}


/* 32 RGBA */

void ConvertC_32rgb888_32rgba888(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{
  do
  { *((int32*)dest)=(*((int32*)source)<<8)|0xff;

    dest+=4;
    source+=4;
  } while (--count);
}



/* 32 BGRA */

void ConvertC_32rgb888_32bgra888(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ int32 s_pixel;
  char8 *s_ptr=(char8 *)&s_pixel,tmp;

  do
  { 
    s_pixel=READ32(source);

    tmp=*(s_ptr+R_32); 
    *(s_ptr+R_32)=*(s_ptr+B_32); 
    *(s_ptr+B_32)=tmp;
    s_pixel|=0xff;

    WRITE32(dest,s_pixel<<8);

    dest+=4;
    source+=4;
  } while(--count);
}



/* TO 24 RGB */

void ConvertC_32rgb888_24rgb888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel,s_pixel2;
  char8 *s_point=(char8 *)&s_pixel;
  unsigned int c;

  /* Align mod 4 (quite important in this case.. ) */

  while (((int)dest&0x3)!=0) 
  { s_pixel=READ32(source);

    *(dest+R_24)=*(s_point+R_32);
    *(dest+G_24)=*(s_point+G_32);
    *(dest+B_24)=*(s_point+B_32);

    source+=4;
    dest+=3;

    count--;
    if (!count) return;
  }

  /* Main loop. TODO: Big endian check! */

  c=count>>2;
  while (c--) {

    #if defined __LITTLE_ENDIAN__     
     
    	s_pixel=READ32(source);
    	s_pixel2=READ32(source+1);
        
    	s_pixel=(s_pixel&0xffffff)|(s_pixel2<<24);
    	WRITE32(dest,s_pixel);
    
    	s_pixel=READ32(source+2);
    	s_pixel2=((s_pixel2>>8)&0xffff)|(s_pixel<<16);
    	WRITE32(dest+1,s_pixel2);
    
    	s_pixel2=READ32(source+3);
    	s_pixel=((s_pixel>>16)&0xff)|(s_pixel2<<8);
    	WRITE32(dest+2,s_pixel);
    	
    #elif defined __BIG_ENDIAN__

	s_pixel=READ32(source);
    	s_pixel2=READ32(source+1);
        
    	s_pixel=(s_pixel<<8)|((s_pixel2>>16)&0xff);
    	WRITE32(dest,s_pixel);
    
    	s_pixel=READ32(source+2);
    	s_pixel2=(s_pixel2<<16)|((s_pixel>>8)&0xffff);
    	WRITE32(dest+1,s_pixel2);
    
    	s_pixel2=READ32(source+3);
    	s_pixel=(s_pixel<<24)|(s_pixel2&0xffffff);
    	WRITE32(dest+2,s_pixel);    

    #endif
    
    source+=16;
    dest+=12;
  }
  
  /* Convert trailing pixels */

  count=count&0x3;
  while (count--) 
  { s_pixel=READ32(source);

    *(dest+R_24)=*(s_point+R_32);
    *(dest+G_24)=*(s_point+G_32);
    *(dest+B_24)=*(s_point+B_32);

    source+=4;
    dest+=3;
  }
}


/* TO 24 BGR */

void ConvertC_32rgb888_24bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 s_pixel;
  char8 *s_point=(char8 *)&s_pixel;

  do
  { s_pixel=READ32(source);

    /* Note that R and B are swapped */
    *(dest+B_24)=*(s_point+R_32);
    *(dest+G_24)=*(s_point+G_32);
    *(dest+R_24)=*(s_point+B_32);

    source+=4;
    dest+=3;
  } while(--count);
}


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


/* TO 16 BGR 565 */

void ConvertC_32rgb888_16bgr565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;

  /* If the current pixel isn't dword aligned, try write one pixel first */

  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>19)&0x1f;
    g=(s_pixel>>5)&0x7e0;
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

    d_pixelblock=DWORD_SHORT0(((s_pixel>>19)&0x1f)|
			     ((s_pixel>>5)&0x7e0)|
                             ((s_pixel<<8)&0xf800));

    s_pixel=READ32(source+1);

    d_pixelblock|=DWORD_SHORT1(((s_pixel>>19)&0x1f)|
			      ((s_pixel>>5)&0x7e0)|
			      ((s_pixel<<8)&0xf800));
   
    WRITE32(dest,d_pixelblock);
  }


  /* Eventually, write a single odd pixel that might be left */
  if(count&1)
  { s_pixel=READ32(source);

    r=(s_pixel>>19)&0x1f;
    g=(s_pixel>>5)&0x7e0;
    b=(s_pixel<<8)&0xf800;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}


/* TO 16 RGB 555 */


void ConvertC_32rgb888_16rgb555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;
  unsigned int i;

  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>9)&0x7c00;
    g=(s_pixel>>6)&0x3e0;
    b=(s_pixel>>3)&0x1f;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);

    source+=4; 
    dest+=2;
    count--;
  }

  for(i=0;i<count>>1;i++,source+=8,dest+=4)
  { s_pixel=READ32(source);

    d_pixelblock=DWORD_SHORT0(((s_pixel>>9)&0x7c00)|
			     ((s_pixel>>6)&0x3e0)|
			     ((s_pixel>>3)&0x1f));

    s_pixel=READ32(source+1);

    d_pixelblock|=DWORD_SHORT1(((s_pixel>>9)&0x7c00)|
			      ((s_pixel>>6)&0x3e0)|
			      ((s_pixel>>3)&0x1f));
   
    WRITE32(dest,d_pixelblock);
  }

  if(count&1)
  { s_pixel=READ32(source);

    r=(s_pixel>>9)&0x7c00;
    g=(s_pixel>>6)&0x3e0;
    b=(s_pixel>>3)&0x1f;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}



/* TO 16 BGR 555 */

void ConvertC_32rgb888_16bgr555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 r,g,b;
  int32 s_pixel,d_pixelblock;
  short16 d_pixel;
  unsigned int i;


  if(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);
 
    r=(s_pixel>>19)&0x1f;
    g=(s_pixel>>6)&0x3e0;
    b=(s_pixel<<7)&0x7c00;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);

    source+=4; 
    dest+=2;
    count--;
  }

  for(i=0;i<count>>1;i++,source+=8,dest+=4)
  { s_pixel=READ32(source);

    d_pixelblock=DWORD_SHORT0(((s_pixel>>19)&0x1f)|
			     ((s_pixel>>6)&0x3e0)|
			     ((s_pixel<<7)&0x7c00));

    s_pixel=READ32(source+1);

    d_pixelblock|=DWORD_SHORT1(((s_pixel>>19)&0x1f)|
			      ((s_pixel>>6)&0x3e0)|
			      ((s_pixel<<7)&0x7c00));
   
    WRITE32(dest,d_pixelblock);
  }

  if(count&1)
  { s_pixel=READ32(source);

    r=(s_pixel>>19)&0x1f;
    g=(s_pixel>>6)&0x3e0;
    b=(s_pixel<<7)&0x7c00;

    d_pixel=(short16)(r|g|b);

    WRITE16(dest,d_pixel);
  }
}


/* TO 8 RGB 332 */

void ConvertC_32rgb888_8rgb332(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ unsigned int i;
  int32 s_pixel,d_block;
  char8 d_pixel;

  /* Process single pixels until we are dword aligned */

  while(((int)dest&0x3)!=0)
  { s_pixel=READ32(source);

    d_pixel=(char8)(((s_pixel>>16)&0xe0)|
		    ((s_pixel>>11)&0x1c)|
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
    d_block=DWORD_BYTE0(((s_pixel>>16)&0xe0)|((s_pixel>>11)&0x1c)|
			((s_pixel>>6)&0x3));

    s_pixel=READ32(source+1);
    d_block|=DWORD_BYTE1(((s_pixel>>16)&0xe0)|((s_pixel>>11)&0x1c)|
			 ((s_pixel>>6)&0x3));
    
    s_pixel=READ32(source+2);
    d_block|=DWORD_BYTE2(((s_pixel>>16)&0xe0)|((s_pixel>>11)&0x1c)|
			 ((s_pixel>>6)&0x3));
   
    s_pixel=READ32(source+3);
    d_block|=DWORD_BYTE3(((s_pixel>>16)&0xe0)|((s_pixel>>11)&0x1c)|
			 ((s_pixel>>6)&0x3));

    WRITE32(dest,d_block);
  }

  /* Write all possibly remaining pixel */

  count=count&0x3;
 
  while (count--)
  { s_pixel=READ32(source);

    *dest=(char8)(((s_pixel>>16)&0xe0)|((s_pixel>>11)&0x1c)|((s_pixel>>6)&0x3));

    dest++;
    source+=4;
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
    p=DWORD_SHORT0(((*((int32*)source+(x>>16))>>8)&0xf800)|
		  ((*((int32*)source+(x>>16))>>5)&0x7e0)|
		  ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
 
    p|=DWORD_SHORT1(((*((int32*)source+(x>>16))>>8)&0xf800)|
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

    p=DWORD_SHORT0(((*((int32*)source+(x>>16))>>19)&0x1f)|
		  ((*((int32*)source+(x>>16))>>5)&0x7e0)|
		  ((*((int32*)source+(x>>16))<<8)&0xf800));
    x+=inc_source;
 
    p|=DWORD_SHORT1(((*((int32*)source+(x>>16))>>19)&0x1f)|
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
    p=DWORD_SHORT0(((*((int32*)source+(x>>16))>>9)&0x7c00)|
		  ((*((int32*)source+(x>>16))>>6)&0x3e0)|
		  ((*((int32*)source+(x>>16))>>3)&0x1f));
    x+=inc_source;
 
    p|=DWORD_SHORT1(((*((int32*)source+(x>>16))>>9)&0x7c00)|
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

    p=DWORD_SHORT0(((*((int32*)source+(x>>16))>>19)&0x1f)|
		  ((*((int32*)source+(x>>16))>>6)&0x3e0)|
		  ((*((int32*)source+(x>>16))<<7)&0x7c00));
    x+=inc_source;
 
    p|=DWORD_SHORT1(((*((int32*)source+(x>>16))>>19)&0x1f)|
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
