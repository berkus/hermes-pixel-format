/*
   Pixel format structure operations for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include <stdlib.h>
#include <string.h>
#include "H_Format.h"



HermesFormat* HERMES_API Hermes_FormatNewEmpty()
{ HermesFormat *tmp;

  tmp=(HermesFormat *)malloc(sizeof(HermesFormat));
  if (!tmp) return 0;

  tmp->bits=0;
  tmp->indexed=0;
  tmp->r=0;
  tmp->g=0;
  tmp->b=0;
  tmp->a=0;
  tmp->has_colorkey=0;
  tmp->colorkey=0;

  return tmp;
}

HermesFormat* HERMES_API Hermes_FormatNew(int bits,int32 r,int32 g,int32 b,
					  int32 a,char indexed)
{ HermesFormat *tmp;

  /* Indexed has to be 8 bit */
  if (indexed && bits!=8) return 0;
 
  tmp=(HermesFormat *)malloc(sizeof(HermesFormat)); 
  if (!tmp) return 0;

  tmp->bits=bits;
  tmp->r=r;
  tmp->g=g;
  tmp->b=b;
  tmp->a=a;
  tmp->indexed=indexed;
  tmp->has_colorkey=0;
  tmp->colorkey=0;

  return tmp;
}

void HERMES_API Hermes_FormatFree(HermesFormat* fmt)
{
  if (fmt) free(fmt);
}

HermesFormat* HERMES_API Hermes_FormatNewEx(int bits,int32 r,int32 g,int32 b,
					  int32 a,char indexed, char has_colorkey,int32 colorkey)
{ HermesFormat *tmp;

  /* Indexed has to be 8 bit */
  if (indexed && bits!=8) return 0;
 
  tmp=(HermesFormat *)malloc(sizeof(HermesFormat)); 
  if (!tmp) return 0;

  tmp->bits=bits;
  tmp->r=r;
  tmp->g=g;
  tmp->b=b;
  tmp->a=a;
  tmp->indexed=indexed;
  tmp->has_colorkey=has_colorkey;
  tmp->colorkey=colorkey;

  return tmp;
}



/* Compare two formats. Return 1 if they are equal, 0 otherwise */
char HERMES_API Hermes_FormatEquals(HermesFormat *op1,HermesFormat *op2)
{ 
  if (!op1 || !op2) return 0;

  /*  return !memcmp(op1,op2,sizeof(HermesFormat)); */
 
  return (op1->indexed == op2->indexed &&
	  op1->bits == op2->bits &&
	  op1->r == op2->r &&
	  op1->g == op2->g &&
	  op1->b == op2->b &&
	  op1->a == op2->a &&
	  op1->has_colorkey == op2->has_colorkey &&
	  (op1->has_colorkey == 0 || op1->colorkey == op2->colorkey));
}


void HERMES_API Hermes_FormatCopy(HermesFormat *source,HermesFormat *dest)
{
  memcpy(dest,source,sizeof(HermesFormat));
}





