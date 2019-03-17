/*
   Surface clearing handler routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include <stdlib.h>
#include "H_Clear.h"
#include "List.h"
#include "Factory.h"
#include "Utility.h"


typedef struct {
  HermesFormat *format;
  HermesClearPtr func;
} ClearerInstance;


/* ClearerList is a list of ClearerInstance */
static HermesList *ClearerList=0;

static int refcount=0;
static HermesHandle currenthandle=0;



HermesHandle HERMES_API Hermes_ClearerInstance()
{ HermesListElement *element;
  ClearerInstance *newinstance;

   if (!refcount) {
    /* Create a clearer list */
    ClearerList=Hermes_ListNew();
    if (!ClearerList) return 0;
  }

  element=Hermes_ListElementNew(currenthandle+1);
  if (!element) return 0;
 
  newinstance=(ClearerInstance *)malloc(sizeof(ClearerInstance));
  if (!newinstance) return 0;
  

  newinstance->func=0;
  newinstance->format=Hermes_FormatNewEmpty();
  if (!newinstance->format) return 0;
  
  element->data=newinstance;

  Hermes_ListAdd(ClearerList,element);

  refcount++;

  return ++currenthandle;
}



void HERMES_API Hermes_ClearerReturn(HermesHandle handle)
{
  HermesListElement *element;
  ClearerInstance *clr; 

  refcount--;

  /* Look up this clearer in the list */
  element=Hermes_ListLookup(ClearerList,handle);
  if (!element) return;
  
  clr=(ClearerInstance *)element->data;

  Hermes_FormatFree(clr->format);

  if (!Hermes_ListDeleteElement(ClearerList,handle)) return;

  if (!refcount) {
    /* Dirty fix: Free the format pointers in all the clearer instances */
    /* The list functions need updating to allow member deletion! */
    
    HermesListElement *element;
    element=ClearerList->first;
    while (element) {
      ClearerInstance *instance=(ClearerInstance *)element->data;
      Hermes_FormatFree(instance->format);
    }
    
    /* Delete clearer list */
    Hermes_ListDestroy(ClearerList);
  }
}



int HERMES_API Hermes_ClearerRequest(HermesHandle handle,HermesFormat *format)
{ HermesListElement *element;
  ClearerInstance *clr; 
  int i;
  
  /* Look up this clearer in the list */
  element=Hermes_ListLookup(ClearerList,handle);
  if (!element) return 0;
  
  clr=(ClearerInstance *)element->data;

  /* If the clearer is the same, return 1 */
  if (Hermes_FormatEquals(clr->format,format))
  return 1;

  /* Otherwise look for a new clearer */
  clr->func=0;

  for (i=0;i<numClearers;i++) {
    if (Clearers[i]->bits==format->bits)
    { clr->func=Clearers[i]->func;
      Hermes_FormatCopy(format,clr->format);
      return 1;
    }
  }

  return 0; 
}


int HERMES_API Hermes_ClearerClear(HermesHandle handle,void *pixels,int x1,
			int y1,int width,int height,int pitch,int32 r,int32 g,
			int32 b,char8 index)
{ HermesListElement *element;
  HermesGenericInfo info; 
  ClearerInstance *clr;
  int32 pixelval,d_r,d_g,d_b,d_a;
  HermesClearInterface iface;

  if (height<=0 || width<=0) return 1;

  /* Look up this clearer in the list */
  element=Hermes_ListLookup(ClearerList,handle);
  if (!element || !element->data) return 0;
 
  /* Get clearer instance from list element data */
  clr=(ClearerInstance *)element->data;

  /* No conversion function assigned */
  if (!clr->func) return 0;

  if (clr->format->indexed) {
    pixelval=index;
  }
  else {
    /* Calculate pixel value for direct colour formats */

    Hermes_Calculate_Generic_Info(24,16,8,32,
				  Hermes_Topbit(clr->format->r),
				  Hermes_Topbit(clr->format->g),
				  Hermes_Topbit(clr->format->b),
				  Hermes_Topbit(clr->format->a),&info);

    pixelval=(((int32)index)<<24)|(r<<16)|(g<<8)|b;

    d_r=((pixelval>>info.r_right)<<info.r_left)&
        clr->format->r;
    d_g=((pixelval>>info.g_right)<<info.g_left)&
        clr->format->g;
    d_b=((pixelval>>info.b_right)<<info.b_left)&
        clr->format->b;
    d_a=((pixelval>>info.a_right)<<info.a_left)&
        clr->format->a;
         
    pixelval=d_r|d_g|d_b|d_a;
  }

  iface.dest=(char8 *)pixels;
  iface.dest+=y1*pitch+x1*(clr->format->bits>>3);

  iface.width=width;
  iface.height=height;
  iface.add=pitch-width*(clr->format->bits>>3);

  iface.value=pixelval;

  /* Optimization */
  if (iface.add==0) {
    iface.width *= height;
    iface.height = 1;
  }

  clr->func(&iface);

  return 1;
}



