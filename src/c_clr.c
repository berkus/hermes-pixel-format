/*
   C surface clearing routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/


#include "H_Types.h"
#include "HeadC.h"
#include "HermConf.h"
#include "Clear.h"



void ClearC_32(HermesClearInterface *iface)
{ unsigned int count;
  int32 value=iface->value;
  char8 *dest=(char8 *)iface->dest;

  do
  { 
    count=iface->width;
  
    do
    { *((int32*)dest)=value;
      dest+=4;
    } while(--count);

    dest+=iface->add;
  } while(--iface->height);
}



void ClearC_24(HermesClearInterface *iface)
{ char8 *p_value=(char8 *)&iface->value;
  unsigned int count;
  char8 *dest=iface->dest;
  
  do
  { count=iface->width;

    do
    { *(dest+R_24)=*(p_value+R_32);
      *(dest+G_24)=*(p_value+G_32);
      *(dest+B_24)=*(p_value+B_32);

      dest+=3;
    } while(--count);

    dest+=iface->add;
  } while(--iface->height);
}



void ClearC_16(HermesClearInterface *iface)
{ 
  int32 value32=(iface->value<<16)|(iface->value&0xffff);
  unsigned int countshifted;
  unsigned int count;
  char8 *dest=iface->dest;


  do
  { count=iface->width;
  
    /* Align destination */
    if((int)dest&0x3)
    { *((short16 *)dest)=(short16)iface->value;
      dest+=2;
      count--;
    }

    countshifted=count>>1;

    while(countshifted--)
    { *((int32 *)dest)=value32;
      dest+=4;
    }

    if(count&1)
    { *((short16 *)dest)=(short16)iface->value;
      dest+=2;
    }

    dest+=iface->add;
  } while(--iface->height);
}



void ClearC_8(HermesClearInterface *iface)
{ unsigned int count,shiftcount;
  int32 value32;
  char8 value;
  char8 *dest=iface->dest;

  value=(char8)iface->value&0xff; 
  value32=(value<<24)|(value<<16)|(value<<8)|value;

  do
  { count=iface->width;
   
    while(((int)dest&0x3))         /* Align to dword boundary */
    { *dest++=(char8)value;
      count--;
      if(!count) goto yloop;	   /* GOTO's are nice ;) */
    }
  
    shiftcount=count>>2;

    while(shiftcount--)
    { *((int32 *)dest)=value32;
      dest+=4;
    }

    count&=0x3;
    while(count--)
    *dest++=(char8)value;
    
yloop:    
    dest+=iface->add;
  } while(--iface->height);
}

