/*
   C straight copy routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/


#include <string.h>
#include "HermConf.h"
#include "HeadC.h"


void CopyC_4byte(char8 *source,char8 *dest,unsigned int count,
		 unsigned int inc_source)
{ memcpy(dest,source,count<<2);
}


void CopyC_3byte(char8 *source,char8 *dest,unsigned int count,
		 unsigned int inc_source)
{ memcpy(dest,source,count*3);
}



void CopyC_2byte(char8 *source,char8 *dest,unsigned int count,
		 unsigned int inc_source)
{ memcpy(dest,source,count<<1);
}



void CopyC_1byte(char8 *source,char8 *dest,unsigned int count,
		 unsigned int inc_source)
{ memcpy(dest,source,count);
}




void CopyC_4byte_S(char8 *source,char8 *dest,unsigned int count,
		   unsigned int inc_source)
{ unsigned int x=0;

  do {
    *((int32*)dest)=*((int32*)source+(x>>16));

    x+=inc_source;
    dest+=4;
  } while (--count);
}


/* TODO: Optimise */
void CopyC_3byte_S(char8 *source,char8 *dest,unsigned int count,
		   unsigned int inc_source)
{
  unsigned int x=0;
 
  do {
    dest[R_24]=source[(x>>16)+R_24];
    dest[G_24]=source[(x>>16)+G_24];
    dest[B_24]=source[(x>>16)+B_24];
               
    x+=inc_source;
    dest+=3;
  } while (--count);                         
}


void CopyC_2byte_S(char8 *source,char8 *dest,unsigned int count,
		   unsigned int inc_source)
{ unsigned int x=0, c;

  /* Alignment mod 4 */
  if ((int)dest&3) {
    *((short16*)dest)=*((short16*)source+(x>>16)); x+=inc_source; 
    dest+=2;
    count--;
  }
  
  c=(count>>1);

  while (c--) {
    /* TODO: make fast :) */
    int32 p=DWORD_BYTE0((int32)*((short16*)source+(x>>16))); x+=inc_source;
    p|=DWORD_BYTE2((int32)*((short16*)source+(x>>16))); x+=inc_source;

    *((int32*)dest)=p;
    dest+=4;
  } 

  if (count&1) 
    *((short16*)dest)=*((short16*)source+(x>>16));
}


void CopyC_1byte_S(char8 *source,char8 *dest,unsigned int count,
		   unsigned int inc_source)
{ unsigned int x=0, c;

  /* Alignment mod 4 */
  while ((int)dest&3) {
    *dest=*(source+(x>>16));
    x+=inc_source;
    dest++; count--;
    if (!count) return;
  }

  /* Write blocks of four pixels */

  c=count>>2;

  while (c--) {
    int32 p=DWORD_BYTE0((int32)*(source+(x>>16))); x+=inc_source;
    p|=DWORD_BYTE1((int32)*(source+(x>>16))); x+=inc_source;
    p|=DWORD_BYTE2((int32)*(source+(x>>16))); x+=inc_source;
    p|=DWORD_BYTE3((int32)*(source+(x>>16))); x+=inc_source;

    *((int32*)dest)=p;
    dest+=4;
  }


  /* Write up to three trailing pixels */

  c=count&0x3;

  while (c--) {
    *dest=*(source+(x>>16));
    x+=inc_source;
    dest++;
  }
}
