/*
   Generic C converter (from 24 bit) for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
 
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include "HeadC.h"
#include "HermConf.h"

/* FROM 24 BIT ROUTINES */


void ConvertC_24rgb888_32rgb888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_block;
 
  do
  {

    d_block=(((int32)*(source+R_24))<<16)|
            (((int32)*(source+G_24))<<8)|
            ((int32)*(source+B_24));
    
    *((int32 *)dest)=d_block;
 
    dest+=4;
    source+=3;
    
  } while(--count);
}



void ConvertC_24rgb888_32bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_block;
 
  do
  {
    d_block=((int32)*(source+R_24))|
            (((int32)*(source+G_24))<<8)|
            (((int32)*(source+B_24))<<16);
    
    *((int32 *)dest)=d_block;
 
    dest+=4;
    source+=3; 
  } while(--count);
}



void ConvertC_24rgb888_32rgba888(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ int32 d_block;
 
  do
  {
    d_block=(((int32)*(source+R_24))<<24)|
            (((int32)*(source+G_24))<<16)|
            (((int32)*(source+B_24))<<8)|0xff;
    
    *((int32 *)dest)=d_block;
 
    dest+=4;
    source+=3;
  } while (--count);
}


void ConvertC_24rgb888_32bgra888(char8 *source,char8 *dest,unsigned int count,
				 unsigned int inc_source)
{ int32 d_block;

  do
  {

    d_block=(((int32)*(source+R_24))<<8)|
            (((int32)*(source+G_24))<<16)|
            (((int32)*(source+B_24))<<24)|0xff;
    
    *((int32 *)dest)=d_block;
 
    dest+=4;
    source+=3;    
  } while(--count);
}


void ConvertC_24rgb888_24bgr888(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_pix1,d_pix2,d_pix3;
  char8 *c_pix1,*c_pix2,*c_pix3,tmp;
  unsigned int i;

  c_pix1=(char8 *)&d_pix1;
  c_pix2=(char8 *)&d_pix2;
  c_pix3=(char8 *)&d_pix3;

  for(i=0;i<count>>2;i++,dest+=12,source+=12)
  { d_pix1=READ32(source);
    d_pix2=READ32((source+4));
    d_pix3=READ32((source+8));

    /* Swap R and B in all three pixels */
    tmp=*(c_pix1+0); *(c_pix1+0)=*(c_pix1+2); *(c_pix1+2)=tmp;
    tmp=*(c_pix1+3); *(c_pix1+3)=*(c_pix2+1); *(c_pix2+1)=tmp;
    tmp=*(c_pix2+2); *(c_pix2+2)=*(c_pix3+0); *(c_pix3+0)=tmp;
    tmp=*(c_pix3+1); *(c_pix3+1)=*(c_pix3+3); *(c_pix3+3)=tmp;

    WRITE32(dest,d_pix1);
    WRITE32((dest+4),d_pix2);
    WRITE32((dest+8),d_pix3);
  }
  
  for(i=0;i<(count&0x3);i++,dest+=3,source+=3)
  { *(dest+0)=*(source+2);
    *(dest+1)=*(source+1);
    *(dest+2)=*(source+0);
  }
}


void ConvertC_24rgb888_16rgb565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_block;
  unsigned int i;

  for(i=0;i<count>>1;i++,source+=6,dest+=4)
  { 
    d_block=DWORD_SHORT0(((((int32)*(source+R_24))<<8)&0xf800)|
			((((int32)*(source+G_24))<<3)&0x7e0)|
			((((int32)*(source+B_24))>>3)&0x1f));

    d_block=d_block|
            DWORD_SHORT1(((((int32)*(source+R_24+3))<<8)&0xf800)|
			((((int32)*(source+G_24+3))<<3)&0x7e0)|
			((((int32)*(source+B_24+3))>>3)&0x1f));

    WRITE32(dest,d_block);
  }

  if(count&1)
  {
    d_block=((((int32)*(source+R_24))<<8)&0xf800)|
            ((((int32)*(source+G_24))<<3)&0x7e0)|
            ((((int32)*(source+B_24))>>3)&0x1f);

    WRITE16(dest,(short16)d_block);
  }
}



void ConvertC_24rgb888_16bgr565(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_block;
  unsigned int i;

  for(i=0;i<count>>1;i++,source+=6,dest+=4)
  { 
    d_block=DWORD_SHORT0(((((int32)*(source+R_24))>>3)&0x1f)|
			((((int32)*(source+G_24))<<3)&0x7e0)|
			((((int32)*(source+B_24))<<8)&0xf800));

    d_block=d_block|
            DWORD_SHORT1(((((int32)*(source+R_24+3))>>3)&0x1f)|
			((((int32)*(source+G_24+3))<<3)&0x7e0)|
			((((int32)*(source+B_24+3))<<8)&0xf800));

    WRITE32(dest,d_block);
  }

  if(count&1)
  {
    d_block=((((int32)*(source+R_24))>>3)&0x1f)|
            ((((int32)*(source+G_24))<<3)&0x7e0)|
            ((((int32)*(source+B_24))<<8)&0xf800);

    WRITE16(dest,(short16)d_block);
  }
}




void ConvertC_24rgb888_16rgb555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_block;
  unsigned int i;

  for(i=0;i<count>>1;i++,source+=6,dest+=4)
  { 

    d_block=DWORD_SHORT0(((((int32)*(source+R_24))<<7)&0x7c00)|
                        ((((int32)*(source+G_24))<<2)&0x3e0)|
                        ((((int32)*(source+B_24))>>3)&0x1f));

    d_block=d_block|
             DWORD_SHORT1(((((int32)*(source+R_24+3))<<7)&0x7c00)|
			 ((((int32)*(source+G_24+3))<<2)&0x3e0)|
			 ((((int32)*(source+B_24+3))>>3)&0x1f));

    WRITE32(dest,d_block);
  }

  if(count&1)
  {
    d_block=((((int32)*(source+R_24))<<7)&0x7c00)|
            ((((int32)*(source+G_24))<<2)&0x3e0)|
            ((((int32)*(source+B_24))>>3)&0x1f);


    WRITE16(dest,(short16)d_block);
  }
}




void ConvertC_24rgb888_16bgr555(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 d_block;
  unsigned int i;

  for(i=0;i<count>>1;i++,source+=6,dest+=4)
  { 

    d_block=DWORD_SHORT0(((((int32)*(source+R_24))>>3)&0x1f)|
                        ((((int32)*(source+G_24))<<2)&0x3e0)|
                        ((((int32)*(source+B_24))<<7)&0x7c00));

    d_block=d_block|
             DWORD_SHORT1(((((int32)*(source+R_24+3))>>3)&0x1f)|
			 ((((int32)*(source+G_24+3))<<2)&0x3e0)|
			 ((((int32)*(source+B_24+3))<<7)&0x7c00));

    WRITE32(dest,d_block);
  }

  if(count&1)
  {
    d_block=((((int32)*(source+R_24))>>3)&0x1f)|
            ((((int32)*(source+G_24))<<2)&0x3e0)|
            ((((int32)*(source+B_24))<<7)&0x7c00);


    WRITE16(dest,(short16)d_block);
  }
}



/* optimise me !! */

void ConvertC_24rgb888_8rgb332(char8 *source,char8 *dest,unsigned int count,
				unsigned int inc_source)
{ int32 r,g,b;
  unsigned int i;

  for(i=0;i<count;i++,source+=3,dest++)
  { 
    r=((int32)*(source+R_24))&0xe0;
    g=(((int32)*(source+G_24))>>3)&0x1c;
    b=(((int32)*(source+B_24))>>6)&0x3;

    *(dest)=(char8)(r|g|b);
  }
}

