/*
   Format conversion handle routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H_Conv.h"
#include "H_Format.h"
#include "H_Pal.h"
#include "H_Blit.h"
#include "Palette.h"
#include "Factory.h"
#include "Convert.h"
#include "HermConf.h"
#include "HeadC.h"
#include "HeadX86.h"
#include "HeadMMX.h"
#include "Debug.h"

/* ConverterList is a list of HermesConverter* */

/* This static array is used by programs that require less than (HERMES_INITIAL) number of handles */
/* (Usually programs only require one handle - the static array is used to prevent unnecessary malloc's) */ 
/* If a larger array is required - A new memory block will be allocated */
static HermesConverter *StaticConverterList[HERMES_INITIAL];

static HermesConverter **ConverterList = 0;	// Points to the converter memory (0 = not initialised)
static int LastConverter;	// Array size
static int NextHandle;		// The next handle that is possible free (used to optimise searching)
static int RefCount;		// Contains the number of used handles

HermesJumpTable HJT_NONE[4] = {
	{0, 0, "Not Available" },
	{0, 0, "Not Available" },
	{0, 0, "Not Available" },
	{0, 0, "Not Available" }
	};

static HermesJumpTable Blit_HJT_CC_32[4] = {
	{ConvertC_Generic32_C_Generic8_C_Blit, ConvertC_Generic32_C_Generic8_C_S_Blit, "Generic32_C_Generic8_C" },
	{ConvertC_Generic32_C_Generic16_C_Blit, ConvertC_Generic32_C_Generic16_C_S_Blit, "Generic32_C_Generic16_C" },
	{ConvertC_Generic32_C_Generic24_C_Blit, ConvertC_Generic32_C_Generic24_C_S_Blit, "Generic32_C_Generic24_C" },
	{ConvertC_Generic32_C_Generic32_C_Blit, ConvertC_Generic32_C_Generic32_C_S_Blit, "Generic32_C_Generic32_C" }
	};

static HermesJumpTable Blit_HJT_CC_24[4] = {
	{ConvertC_Generic24_C_Generic8_C_Blit, ConvertC_Generic24_C_Generic8_C_S_Blit, "Generic24_C_Generic8_C" },
	{ConvertC_Generic24_C_Generic16_C_Blit, ConvertC_Generic24_C_Generic16_C_S_Blit, "Generic24_C_Generic16_C" },
	{ConvertC_Generic24_C_Generic24_C_Blit, ConvertC_Generic24_C_Generic24_C_S_Blit, "Generic24_C_Generic24_C" },
	{ConvertC_Generic24_C_Generic32_C_Blit, ConvertC_Generic24_C_Generic32_C_S_Blit, "Generic24_C_Generic32_C" }
	};

static HermesJumpTable Blit_HJT_CC_16[4] = {
	{ConvertC_Generic16_C_Generic8_C_Blit, ConvertC_Generic16_C_Generic8_C_S_Blit, "Generic16_C_Generic8_C" },
	{ConvertC_Generic16_C_Generic16_C_Blit, ConvertC_Generic16_C_Generic16_C_S_Blit, "Generic16_C_Generic16_C" },
	{ConvertC_Generic16_C_Generic24_C_Blit, ConvertC_Generic16_C_Generic24_C_S_Blit, "Generic16_C_Generic24_C" },
	{ConvertC_Generic16_C_Generic32_C_Blit, ConvertC_Generic16_C_Generic32_C_S_Blit, "Generic16_C_Generic32_C" }
	};


static HermesJumpTable Blit_HJT_AO_32[4] = {
	{ConvertC_Generic32_A_Generic8_O_Blit, ConvertC_Generic32_A_Generic8_O_S_Blit, "Generic32_A_Generic8_O" },
	{ConvertC_Generic32_A_Generic16_O_Blit, ConvertC_Generic32_A_Generic16_O_S_Blit, "Generic32_A_Generic16_O" },
	{ConvertC_Generic32_A_Generic24_O_Blit, ConvertC_Generic32_A_Generic24_O_S_Blit, "Generic32_A_Generic24_O" },
	{ConvertC_Generic32_A_Generic32_O_Blit, ConvertC_Generic32_A_Generic32_O_S_Blit, "Generic32_A_Generic32_O" }
	};

static HermesJumpTable Blit_HJT_AO_24[4] = {
	{ConvertC_Generic24_A_Generic8_O_Blit, ConvertC_Generic24_A_Generic8_O_S_Blit, "Generic24_A_Generic8_O" },
	{ConvertC_Generic24_A_Generic16_O_Blit, ConvertC_Generic24_A_Generic16_O_S_Blit, "Generic24_A_Generic16_O" },
	{ConvertC_Generic24_A_Generic24_O_Blit, ConvertC_Generic24_A_Generic24_O_S_Blit, "Generic24_A_Generic24_O" },
	{ConvertC_Generic24_A_Generic32_O_Blit, ConvertC_Generic24_A_Generic32_O_S_Blit, "Generic24_A_Generic32_O" }
	};

static HermesJumpTable Blit_HJT_AO_16[4] = {
	{ConvertC_Generic16_A_Generic8_O_Blit, ConvertC_Generic16_A_Generic8_O_S_Blit, "Generic16_A_Generic8_O" },
	{ConvertC_Generic16_A_Generic16_O_Blit, ConvertC_Generic16_A_Generic16_O_S_Blit, "Generic16_A_Generic16_O" },
	{ConvertC_Generic16_A_Generic24_O_Blit, ConvertC_Generic16_A_Generic24_O_S_Blit, "Generic16_A_Generic24_O" },
	{ConvertC_Generic16_A_Generic32_O_Blit, ConvertC_Generic16_A_Generic32_O_S_Blit, "Generic16_A_Generic32_O" }
	};

static HermesJumpTable Blit_HJT_CO_32[4] = {
	{ConvertC_Generic32_C_Generic8_O_Blit, ConvertC_Generic32_C_Generic8_O_S_Blit, "Generic32_C_Generic8_O" },
	{ConvertC_Generic32_C_Generic16_O_Blit, ConvertC_Generic32_C_Generic16_O_S_Blit, "Generic32_C_Generic16_O" },
	{ConvertC_Generic32_C_Generic24_O_Blit, ConvertC_Generic32_C_Generic24_O_S_Blit, "Generic32_C_Generic24_O" },
	{ConvertC_Generic32_C_Generic32_O_Blit, ConvertC_Generic32_C_Generic32_O_S_Blit, "Generic32_C_Generic32_O" }
	};

static HermesJumpTable Blit_HJT_CO_24[4] = {
	{ConvertC_Generic24_C_Generic8_O_Blit, ConvertC_Generic24_C_Generic8_O_S_Blit, "Generic24_C_Generic8_O" },
	{ConvertC_Generic24_C_Generic16_O_Blit, ConvertC_Generic24_C_Generic16_O_S_Blit, "Generic24_C_Generic16_O" },
	{ConvertC_Generic24_C_Generic24_O_Blit, ConvertC_Generic24_C_Generic24_O_S_Blit, "Generic24_C_Generic24_O" },
	{ConvertC_Generic24_C_Generic32_O_Blit, ConvertC_Generic24_C_Generic32_O_S_Blit, "Generic24_C_Generic32_O" }
	};

static HermesJumpTable Blit_HJT_CO_16[4] = {
	{ConvertC_Generic16_C_Generic8_O_Blit, ConvertC_Generic16_C_Generic8_O_S_Blit, "Generic16_C_Generic8_O" },
	{ConvertC_Generic16_C_Generic16_O_Blit, ConvertC_Generic16_C_Generic16_O_S_Blit, "Generic16_C_Generic16_O" },
	{ConvertC_Generic16_C_Generic24_O_Blit, ConvertC_Generic16_C_Generic24_O_S_Blit, "Generic16_C_Generic24_O" },
	{ConvertC_Generic16_C_Generic32_O_Blit, ConvertC_Generic16_C_Generic32_O_S_Blit, "Generic16_C_Generic32_O" }
	};

static HermesJumpTable Blit_HJT_CopyOnly_32[4] = {
	{ConvertC_Generic32_Generic8, ConvertC_Generic32_Generic8_S, "Generic32_Generic8" },
	{ConvertC_Generic32_Generic16, ConvertC_Generic32_Generic16_S, "Generic32_Generic16" },
	{ConvertC_Generic32_Generic24, ConvertC_Generic32_Generic24_S, "Generic32_Generic24" },
	{ConvertC_Generic32_Generic32, ConvertC_Generic32_Generic32_S, "Generic32_Generic32" }
	};

static HermesJumpTable Blit_HJT_CopyOnly_24[4] = {
	{ConvertC_Generic24_Generic8, ConvertC_Generic24_Generic8_S, "Generic24_Generic8" },
	{ConvertC_Generic24_Generic16, ConvertC_Generic24_Generic16_S, "Generic24_Generic16" },
	{ConvertC_Generic24_Generic24, ConvertC_Generic24_Generic24_S, "Generic24_Generic24" },
	{ConvertC_Generic24_Generic32, ConvertC_Generic24_Generic32_S, "Generic24_Generic32" }
	};

static HermesJumpTable Blit_HJT_CopyOnly_16[4] = {
	{ConvertC_Generic16_Generic8, ConvertC_Generic16_Generic8_S, "Generic16_Generic8" },
	{ConvertC_Generic16_Generic16, ConvertC_Generic16_Generic16_S, "Generic16_Generic16" },
	{ConvertC_Generic16_Generic24, ConvertC_Generic16_Generic24_S, "Generic16_Generic24" },
	{ConvertC_Generic16_Generic32, ConvertC_Generic16_Generic32_S, "Generic16_Generic32" }
	};
static HermesJumpTable *Blit_HJT_CC[4] = { HJT_NONE, Blit_HJT_CC_16, Blit_HJT_CC_24, Blit_HJT_CC_32 };
static HermesJumpTable *Blit_HJT_AO[4] = { HJT_NONE, Blit_HJT_AO_16, Blit_HJT_AO_24, Blit_HJT_AO_32 };
static HermesJumpTable *Blit_HJT_CO[4] = { HJT_NONE, Blit_HJT_CO_16, Blit_HJT_CO_24, Blit_HJT_CO_32 };
static HermesJumpTable *Blit_HJT_CopyOnly[4] = { HJT_NONE, Blit_HJT_CopyOnly_16, Blit_HJT_CopyOnly_24, Blit_HJT_CopyOnly_32 };

// *** This table is as of Hermes 1.3.2 - It looks incorrect ***
static HermesJumpTableList Blit_HJT = {
	Blit_HJT_CC,	NULL,	NULL,	Blit_HJT_AO,	Blit_HJT_AO,	Blit_HJT_CO,	Blit_HJT_CopyOnly };

HermesHandle HERMES_API Hermes_BlitterInstance(unsigned long flags)
{
  int i;
  HermesConverter *newinstance;
  HermesConverter **newlist;
  HermesConverter **cptr;
  int cptr_id;
  int new_size;

  DEBUG_PRINT("Hermes_BlitterInstance called\n","");
  /* Initialising, allocate initial size array of converters */

  if (!ConverterList) {		// ConverterList not initialised. (Called on the first call to this function) 
    memset(StaticConverterList, 0, sizeof(StaticConverterList));	// Clear the array
    ConverterList = StaticConverterList;	// Set the ConverterList address to the static array
    LastConverter=HERMES_INITIAL;	// Size of the StaticConvertList array
    NextHandle=1;	// Set the handle will be free
    RefCount=0;		// Number of used handles
  } 

  cptr = 0;	// Flag the converter pointer has not been found
  cptr_id = 0;

  // If the next handle is free use it now (to prevent unnecessary searching)
  if (NextHandle < LastConverter)	// Valid next handle
  {
	if (!ConverterList[NextHandle])	// Found a free handle
	{
		cptr = &(ConverterList[NextHandle]);	// The free handle
		cptr_id = NextHandle;	// The handle id
	}
  } 

  if (!cptr)	// handle not found - do a full search
  {
    // Note, I start searching at one (not zero) this is intentional - since returning zero also denotes an error
    for (i=1; i<LastConverter; i++)	// For all the converters
    {
      if (!ConverterList[i])      // Found an empty slot
      {
        cptr = &(ConverterList[i]);	// The free handle
        cptr_id = i;		// The handle id
        break;
      }
    }
  }

  if (!cptr) // No free slot found
  {

    /* Uh oh, arrary too small, time for growth */
    new_size = LastConverter+HERMES_GROWTH;
    newlist=(HermesConverter **)malloc(sizeof(HermesConverter*) * new_size);
    if (!newlist) return 0;

    /* Copy converter pointers */

    for (i=0;i<LastConverter;i++)	// Copy each existing converters
    {
      newlist[i]=ConverterList[i];
    }
    for ( ; i < new_size; i++ )	// Clear the new elements of the array
    {
      newlist[i]=0;
    }

    if (ConverterList != StaticConverterList)	// Do not deallocate the static array
    {
      free(ConverterList);
    }

    /* Assign new list to old one */
    ConverterList=newlist;

    cptr = &(ConverterList[LastConverter]);	// The free handle
    cptr_id = LastConverter;	// The handle id

    LastConverter = new_size;

    DEBUG_PRINT("Growing dynamic array, new size %d\n",LastConverter)
  }

  /* Create a HermesConverter */

  /* Note: allocates and clears the list */
  newinstance=(HermesConverter *)calloc(1, sizeof(HermesConverter));
  if (!newinstance) return 0;
  newinstance->flags=flags;

  RefCount++;

  *cptr = newinstance;		// Store the new HermesConverter
  NextHandle = cptr_id + 1;	// Set the next possible free handle
  return cptr_id;
}



void HERMES_API Hermes_BlitterReturn(HermesHandle handle)
{
  if (!ConverterList) return;	// Return called before Init
  if (handle<=0 || handle>=LastConverter) return;	// Invalid handle
  if (!ConverterList[handle]) return;   // Already deallocated

  free(ConverterList[handle]);	// Free the handle
  ConverterList[handle]=0;	// Flag handle freed

  NextHandle = handle;		// Flag where the free handle is located

  RefCount--;
  /* No more references, deinitialise */
  if (!RefCount)
  {
    if (ConverterList != StaticConverterList)	// Not using the static array
    {
      free(ConverterList); 		// Free the array
      ConverterList = StaticConverterList;  // Set the ConverterList address to the static array
      LastConverter=HERMES_INITIAL;       // Size of the StaticConvertList array
    }
    NextHandle = 1;	// Where the free handle is located
  }
}

int HERMES_API Hermes_BlitterRequest(HermesHandle handle, HermesFormat *source, HermesFormat *dest)
{
  // Note - Not using specialised converters as we are blitting
  return (Hermes_BlitterRequest_V2(handle, source, dest, 0, &Blit_HJT));
}

// api_flags : 0 = Do not look for the specialised converters
int HERMES_API Hermes_BlitterRequest_V2(HermesHandle handle, HermesFormat *source, HermesFormat *dest, int api_flags, HermesJumpTableList *tptr)
{
  int searchlist;
  int i;
  HermesConverter *cnv;
  int src_bits;
  int dest_bits;
  HermesJumpTable *jptr;
  
  DEBUG_PRINT("Blitter Request\n","");
  /* Check array ranges */

  if (handle<0 || handle>=LastConverter) return 0;
  if (!ConverterList[handle]) return 0;

  cnv=ConverterList[handle];

  /* Cache repeated requests of the same conversion */

  if (Hermes_FormatEquals(source,&ConverterList[handle]->source) &&
      Hermes_FormatEquals(dest,&ConverterList[handle]->dest))
  {
      DEBUG_PRINT("Cached converter, from bpp %d\n", source->bits);
      DEBUG_PRINT("To bpp: %d\n", dest->bits);
      DEBUG_PRINT("\tColorkey source: %d,\n", source->has_colorkey);
      DEBUG_PRINT("\tColorkey dest: %d,\n", dest->has_colorkey);
      return 1;
  }

  DEBUG_PRINT("\tColorkey source: %d,\n", source->has_colorkey);
  DEBUG_PRINT("\tColorkey dest: %d,\n", dest->has_colorkey);

  DEBUG_PRINT("source ->a: %x,\n", (int) source->a);
  DEBUG_PRINT("dest ->a: %x,\n", (int) dest->a);

  /* Clear the generic converter flag */

  cnv->flags&=~HERMES_CONVERT_GENERIC;

  /* If the source and destination are equal and src no alph, use copy routines */
  
  if (Hermes_FormatEquals(source,dest) && !source->a) {
      DEBUG_PRINT("Source, dest equal! bpp %d\n", source->bits);  
      if ((source->bits&0x7)!=0 || source->bits > 32 || !source->bits) return 0;

      i=(source->bits>>3)-1;
      
      if (!equalConverters[i]) return 0;
   
    Hermes_FormatCopy(source,&cnv->source);
    Hermes_FormatCopy(dest,&cnv->dest);

    cnv->loopnormal=equalConverters[i]->loopnormal;
    cnv->loopstretch=equalConverters[i]->loopstretch;
    cnv->normal=equalConverters[i]->normal;
    cnv->stretch=equalConverters[i]->stretch;

    return 1;
  }

  if (api_flags)  /* Start looking for specialised converters */
  {
    searchlist=0xff;

    switch (source->bits) {
      case 32: if (source->r==0xff0000 && source->g==0xff00 && source->b==0xff)
               searchlist=0;
               else
	     if (source->r==0xff<<20 && source->g==0xff<<10 && source->b==0xff)
               searchlist=3;
               break;

      case 24: if (source->r==0xff0000 && source->g==0xff00 && source->b==0xff)
               searchlist=1; break;

      case 16: if (source->r==0xf800 && source->g==0x7e0 && source->b==0x1f)
               searchlist=2; 
               break;

       case 8: if (source->indexed)
               searchlist=4; 
               break;
    }


    /* We can use a quicker loop for 8 bit */

    if (searchlist!=0xff)
    if (source->bits==8) {
      for (i=0;i<numConverters[searchlist];i++) {
        if (standardConverters[searchlist][i])
        if (dest->bits==standardConverters[searchlist][i]->dest.bits)
        {
	Hermes_FormatCopy(source,&cnv->source);
          Hermes_FormatCopy(dest,&cnv->dest);

          cnv->loopnormal=standardConverters[searchlist][i]->loopnormal;
          cnv->loopstretch=standardConverters[searchlist][i]->loopstretch;

          cnv->normal=standardConverters[searchlist][i]->normal;
          cnv->stretch=standardConverters[searchlist][i]->stretch;

	cnv->dither=standardConverters[searchlist][i]->dither;
	cnv->ditherstretch=standardConverters[searchlist][i]->ditherstretch;

          return 1;
        }
      }
    }
    else
    for (i=0;i<numConverters[searchlist];i++) {
      if (standardConverters[searchlist][i])
      if (Hermes_FormatEquals(&standardConverters[searchlist][i]->source,source)&&
	Hermes_FormatEquals(&standardConverters[searchlist][i]->dest,dest))
      { Hermes_FormatCopy(source,&cnv->source);
        Hermes_FormatCopy(dest,&cnv->dest);

        cnv->loopnormal=standardConverters[searchlist][i]->loopnormal;
        cnv->loopstretch=standardConverters[searchlist][i]->loopstretch;

        cnv->normal=standardConverters[searchlist][i]->normal;
        cnv->stretch=standardConverters[searchlist][i]->stretch;

        cnv->dither=standardConverters[searchlist][i]->dither;
        cnv->ditherstretch=standardConverters[searchlist][i]->ditherstretch;

        return 1;
      }
    }
  }

  /* Find a generic converter */

  cnv->loopnormal=0;
  cnv->loopstretch=0;
  cnv->dither=0;
  cnv->ditherstretch=0;
  cnv->flags|=HERMES_CONVERT_GENERIC;


  /* Generic routines implement whole converters not scanline converters, 
     assign placeholders */

  cnv->normal=NotApplicable;
  cnv->stretch=NotApplicable;
 
  // Calculate the jump table offset;
  src_bits = (source->bits >> 3);
  dest_bits = (dest->bits >> 3);
  // Validate the offset
  if ((src_bits <= 0) || (src_bits > 4) || (dest_bits <= 0) || (dest_bits > 4) ) return 0;
  src_bits = src_bits - 1;
  dest_bits = dest_bits - 1;

  jptr = NULL;
  if ((cnv->flags & HERMES_CONVERT_INVERSE_ALPHA) && (dest->a) && (tptr->jt_noalpha_alpha !=NULL))
  {
    jptr = tptr->jt_noalpha_alpha[src_bits] + dest_bits;
  }
  else if ((source->has_colorkey==1) && (dest->has_colorkey==1) && (tptr->jt_cc != NULL))
  {
	 jptr = tptr->jt_cc[src_bits] + dest_bits;
  }
  else if ((source->has_colorkey==1) && dest->a && (tptr->jt_ca != NULL))
  {
	 jptr = tptr->jt_ca[src_bits] + dest_bits;
  }
  else if (source->a && (dest->has_colorkey==1) && (tptr->jt_ac != NULL))
  {
	 jptr = tptr->jt_ac[src_bits] + dest_bits;
  }
  else if (source->a && dest->a && (tptr->jt_ao != NULL))
  {
	 jptr = tptr->jt_ao[src_bits] + dest_bits;
  }
  else if (source->a && (tptr->jt_aa != NULL))
  {
	 jptr = tptr->jt_aa[src_bits] + dest_bits;
  }
  else if (source->has_colorkey==1 && (tptr->jt_co != NULL))
  {
	 jptr = tptr->jt_co[src_bits] + dest_bits;
  }
  else if ( tptr->jt_copyonly != NULL)
  {
	 jptr = tptr->jt_copyonly[src_bits] + dest_bits;
  }

  if (jptr) {
    cnv->loopnormal = jptr->loopnormal;
    cnv->loopstretch = jptr->loopstretch;
    DEBUG_PRINT("Using Converter: %s\n", jptr->converter_name);
    Hermes_FormatCopy(source,&cnv->source);
    Hermes_FormatCopy(dest,&cnv->dest);
    return 1;
  }

  /* No converter found, fail */

  return 0;
}




int HERMES_API Hermes_BlitterPalette(HermesHandle handle,
				       HermesHandle sourcepal,
				       HermesHandle destpal)
{
  if (handle<0 || handle>=LastConverter) return 0;
  if (!ConverterList[handle]) return 0;

  /* Fail silently if not indexed colour format */

  if (!ConverterList[handle]->source.indexed) { 
    ConverterList[handle]->lookup=0;
    return 1;
  }
  
  ConverterList[handle]->lookup=
    Hermes_PaletteGetTable(sourcepal,&ConverterList[handle]->dest);
  
  if (!ConverterList[handle]->lookup) return 0;

  return 1;
}


int HERMES_API Hermes_BlitterBlit(HermesHandle handle,void *s_pixels,int s_x,
				    int s_y,int s_width,int s_height,
				    int s_pitch,void *d_pixels,int d_x,int d_y,
				    int d_width,int d_height,int d_pitch)
{ HermesConverter *cnv;
  HermesConverterInterface iface;

  if (handle<0 || handle>=LastConverter) return 0;
  cnv=ConverterList[handle];
  if (!cnv) return 0;


  /* Returns success if height or width is zero. This is debatable.. ! */

  if (s_width<=0 || s_height<=0 || d_width<=0 || d_height<=0) return 1;
  
  iface.s_pixels=(char8 *)s_pixels;
  iface.s_width=s_width;
  iface.s_height=s_height;
  iface.s_add=s_pitch-s_width*(cnv->source.bits>>3);
  iface.s_pitch=s_pitch;

  iface.d_pixels=(char8 *)d_pixels;
  iface.d_width=d_width;
  iface.d_height=d_height;
  iface.d_add=d_pitch-d_width*(cnv->dest.bits>>3);
  iface.d_pitch=d_pitch;

  iface.s_pixels+=s_y*s_pitch+s_x*(cnv->source.bits>>3);
  iface.d_pixels+=d_y*d_pitch+d_x*(cnv->dest.bits>>3);
  
  iface.s_has_colorkey = cnv->source.has_colorkey;
  iface.d_has_colorkey = cnv->dest.has_colorkey;
  iface.s_colorkey = cnv->source.colorkey;
  iface.d_colorkey = cnv->dest.colorkey;

  iface.lookup=cnv->lookup;


  /* For generic converters, do some extra setup (find shifts, etc.) 
     TODO: Move that out of here and in the request routine ! */

  if (cnv->flags&HERMES_CONVERT_GENERIC) {
    Hermes_Calculate_Generic_Info(Hermes_Topbit(cnv->source.r),
	  			  Hermes_Topbit(cnv->source.g),
		 		  Hermes_Topbit(cnv->source.b),
		 		  Hermes_Topbit(cnv->source.a),
				  Hermes_Topbit(cnv->dest.r),
				  Hermes_Topbit(cnv->dest.g),
				  Hermes_Topbit(cnv->dest.b),
				  Hermes_Topbit(cnv->dest.a),
				  &iface.info);
    iface.mask_r=cnv->dest.r;
    iface.mask_g=cnv->dest.g;
    iface.mask_b=cnv->dest.b;
	iface.mask_a=cnv->dest.a;
    iface.s_mask_a = cnv->source.a;
  }


  /* Check for dithering. This should not be in here but in request as well */

  if (cnv->flags&HERMES_CONVERT_DITHER) {

    /* If there is a ditherer, use it else fall back to normal */

    if (cnv->dither) 
    cnv->loopnormal=cnv->dither;
  }


  /* Normal conversion */

  if (s_width==d_width && s_height==d_height) {
    if (!cnv->normal || !cnv->loopnormal) return 0;

    /* Optimization 
    if (iface.s_add==0 && iface.d_add==0) {
      iface.s_width *= s_height;
      iface.d_width *= d_height;
      iface.s_height = 1;    
      iface.d_height = 1;    
    }*/

    iface.func=cnv->normal;
    cnv->loopnormal(&iface);

    return 1;
  }
  /* Stretch conversion */
  else {
    if (!cnv->stretch || !cnv->loopstretch) return 0;
    
    iface.func=cnv->stretch;
    cnv->loopstretch(&iface);
  }

  return 1;
}








