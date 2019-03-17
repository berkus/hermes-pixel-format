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
#include "H_Blit.h"
#include "H_Conv.h"
#include "H_Format.h"
#include "H_Pal.h"
#include "Palette.h"
#include "Factory.h"
#include "Convert.h"
#include "HermConf.h"
#include "HeadC.h"
#include "HeadX86.h"
#include "HeadMMX.h"
#include "Debug.h"

static HermesJumpTable Convert_HJT_CC_32[4] = {
	{ConvertC_Generic32_C_Generic8_C, ConvertC_Generic32_C_Generic8_C_S, "Generic32_C_Generic8_C" },
	{ConvertC_Generic32_C_Generic16_C, ConvertC_Generic32_C_Generic16_C_S, "Generic32_C_Generic16_C" },
	{ConvertC_Generic32_C_Generic24_C, ConvertC_Generic32_C_Generic24_C_S, "Generic32_C_Generic24_C" },
	{ConvertC_Generic32_C_Generic32_C, ConvertC_Generic32_C_Generic32_C_S, "Generic32_C_Generic32_C" }
	};

static HermesJumpTable Convert_HJT_CC_24[4] = {
	{ConvertC_Generic24_C_Generic8_C, ConvertC_Generic24_C_Generic8_C_S, "Generic24_C_Generic8_C" },
	{ConvertC_Generic24_C_Generic16_C, ConvertC_Generic24_C_Generic16_C_S, "Generic24_C_Generic16_C" },
	{ConvertC_Generic24_C_Generic24_C, ConvertC_Generic24_C_Generic24_C_S, "Generic24_C_Generic24_C" },
	{ConvertC_Generic24_C_Generic32_C, ConvertC_Generic24_C_Generic32_C_S, "Generic24_C_Generic32_C" }
	};

static HermesJumpTable Convert_HJT_CC_16[4] = {
	{ConvertC_Generic16_C_Generic8_C, ConvertC_Generic16_C_Generic8_C_S, "Generic16_C_Generic8_C" },
	{ConvertC_Generic16_C_Generic16_C, ConvertC_Generic16_C_Generic16_C_S, "Generic16_C_Generic16_C" },
	{ConvertC_Generic16_C_Generic24_C, ConvertC_Generic16_C_Generic24_C_S, "Generic16_C_Generic24_C" },
	{ConvertC_Generic16_C_Generic32_C, ConvertC_Generic16_C_Generic32_C_S, "Generic16_C_Generic32_C" }
	};

static HermesJumpTable Convert_HJT_CA_32[4] = {
	{ConvertC_Generic32_C_Generic8_A, ConvertC_Generic32_C_Generic8_A_S, "Generic32_C_Generic8_A" },
	{ConvertC_Generic32_C_Generic16_A, ConvertC_Generic32_C_Generic16_A_S, "Generic32_C_Generic16_A" },
	{ConvertC_Generic32_C_Generic24_A, ConvertC_Generic32_C_Generic24_A_S, "Generic32_C_Generic24_A" },
	{ConvertC_Generic32_C_Generic32_A, ConvertC_Generic32_C_Generic32_A_S, "Generic32_C_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_CA_24[4] = {
	{ConvertC_Generic24_C_Generic8_A, ConvertC_Generic24_C_Generic8_A_S, "Generic24_C_Generic8_A" },
	{ConvertC_Generic24_C_Generic16_A, ConvertC_Generic24_C_Generic16_A_S, "Generic24_C_Generic16_A" },
	{ConvertC_Generic24_C_Generic24_A, ConvertC_Generic24_C_Generic24_A_S, "Generic24_C_Generic24_A" },
	{ConvertC_Generic24_C_Generic32_A, ConvertC_Generic24_C_Generic32_A_S, "Generic24_C_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_CA_16[4] = {
	{ConvertC_Generic16_C_Generic8_A, ConvertC_Generic16_C_Generic8_A_S, "Generic16_C_Generic8_A" },
	{ConvertC_Generic16_C_Generic16_A, ConvertC_Generic16_C_Generic16_A_S, "Generic16_C_Generic16_A" },
	{ConvertC_Generic16_C_Generic24_A, ConvertC_Generic16_C_Generic24_A_S, "Generic16_C_Generic24_A" },
	{ConvertC_Generic16_C_Generic32_A, ConvertC_Generic16_C_Generic32_A_S, "Generic16_C_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_AA_32[4] = {
	{ConvertC_Generic32_A_Generic8_A, ConvertC_Generic32_A_Generic8_A_S, "Generic32_A_Generic8_A" },
	{ConvertC_Generic32_A_Generic16_A, ConvertC_Generic32_A_Generic16_A_S, "Generic32_A_Generic16_A" },
	{ConvertC_Generic32_A_Generic24_A, ConvertC_Generic32_A_Generic24_A_S, "Generic32_A_Generic24_A" },
	{ConvertC_Generic32_A_Generic32_A, ConvertC_Generic32_A_Generic32_A_S, "Generic32_A_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_AA_24[4] = {
	{ConvertC_Generic24_A_Generic8_A, ConvertC_Generic24_A_Generic8_A_S, "Generic24_A_Generic8_A" },
	{ConvertC_Generic24_A_Generic16_A, ConvertC_Generic24_A_Generic16_A_S, "Generic24_A_Generic16_A" },
	{ConvertC_Generic24_A_Generic24_A, ConvertC_Generic24_A_Generic24_A_S, "Generic24_A_Generic24_A" },
	{ConvertC_Generic24_A_Generic32_A, ConvertC_Generic24_A_Generic32_A_S, "Generic24_A_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_AA_16[4] = {
	{ConvertC_Generic16_A_Generic8_A, ConvertC_Generic16_A_Generic8_A_S, "Generic16_A_Generic8_A" },
	{ConvertC_Generic16_A_Generic16_A, ConvertC_Generic16_A_Generic16_A_S, "Generic16_A_Generic16_A" },
	{ConvertC_Generic16_A_Generic24_A, ConvertC_Generic16_A_Generic24_A_S, "Generic16_A_Generic24_A" },
	{ConvertC_Generic16_A_Generic32_A, ConvertC_Generic16_A_Generic32_A_S, "Generic16_A_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_CopyOnly_32[4] = {
	{ConvertC_Generic32_Generic8, ConvertC_Generic32_Generic8_S, "Generic32_Generic8" },
	{ConvertC_Generic32_Generic16, ConvertC_Generic32_Generic16_S, "Generic32_Generic16" },
	{ConvertC_Generic32_Generic24, ConvertC_Generic32_Generic24_S, "Generic32_Generic24" },
	{ConvertC_Generic32_Generic32, ConvertC_Generic32_Generic32_S, "Generic32_Generic32" }
	};

static HermesJumpTable Convert_HJT_CopyOnly_24[4] = {
	{ConvertC_Generic24_Generic8, ConvertC_Generic24_Generic8_S, "Generic24_Generic8" },
	{ConvertC_Generic24_Generic16, ConvertC_Generic24_Generic16_S, "Generic24_Generic16" },
	{ConvertC_Generic24_Generic24, ConvertC_Generic24_Generic24_S, "Generic24_Generic24" },
	{ConvertC_Generic24_Generic32, ConvertC_Generic24_Generic32_S, "Generic24_Generic32" }
	};

static HermesJumpTable Convert_HJT_CopyOnly_16[4] = {
	{ConvertC_Generic16_Generic8, ConvertC_Generic16_Generic8_S, "Generic16_Generic8" },
	{ConvertC_Generic16_Generic16, ConvertC_Generic16_Generic16_S, "Generic16_Generic16" },
	{ConvertC_Generic16_Generic24, ConvertC_Generic16_Generic24_S, "Generic16_Generic24" },
	{ConvertC_Generic16_Generic32, ConvertC_Generic16_Generic32_S, "Generic16_Generic32" }
	};

static HermesJumpTable Convert_HJT_NoAA_32[4] = {
	{ConvertC_Generic32_NoA_Generic8_A, ConvertC_Generic32_NoA_Generic8_A_S, "Generic32_NoA_Generic8_A" },
	{ConvertC_Generic32_NoA_Generic16_A, ConvertC_Generic32_NoA_Generic16_A_S, "Generic32_NoA_Generic16_A" },
	{ConvertC_Generic32_NoA_Generic24_A, ConvertC_Generic32_NoA_Generic24_A_S, "Generic32_NoA_Generic24_A" },
	{ConvertC_Generic32_NoA_Generic32_A, ConvertC_Generic32_NoA_Generic32_A_S, "Generic32_NoA_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_NoAA_24[4] = {
	{ConvertC_Generic24_NoA_Generic8_A, ConvertC_Generic24_NoA_Generic8_A_S, "Generic24_NoA_Generic8_A" },
	{ConvertC_Generic24_NoA_Generic16_A, ConvertC_Generic24_NoA_Generic16_A_S, "Generic24_NoA_Generic16_A" },
	{ConvertC_Generic24_NoA_Generic24_A, ConvertC_Generic24_NoA_Generic24_A_S, "Generic24_NoA_Generic24_A" },
	{ConvertC_Generic24_NoA_Generic32_A, ConvertC_Generic24_NoA_Generic32_A_S, "Generic24_NoA_Generic32_A" }
	};

static HermesJumpTable Convert_HJT_NoAA_16[4] = {
	{ConvertC_Generic16_NoA_Generic8_A, ConvertC_Generic16_NoA_Generic8_A_S, "Generic16_NoA_Generic8_A" },
	{ConvertC_Generic16_NoA_Generic16_A, ConvertC_Generic16_NoA_Generic16_A_S, "Generic16_NoA_Generic16_A" },
	{ConvertC_Generic16_NoA_Generic24_A, ConvertC_Generic16_NoA_Generic24_A_S, "Generic16_NoA_Generic24_A" },
	{ConvertC_Generic16_NoA_Generic32_A, ConvertC_Generic16_NoA_Generic32_A_S, "Generic16_NoA_Generic32_A" }
	};

static HermesJumpTable *Convert_HJT_CC[4] = { HJT_NONE, Convert_HJT_CC_16, Convert_HJT_CC_24, Convert_HJT_CC_32 };
static HermesJumpTable *Convert_HJT_CA[4] = { HJT_NONE, Convert_HJT_CA_16, Convert_HJT_CA_24, Convert_HJT_CA_32 };
static HermesJumpTable *Convert_HJT_AA[4] = { HJT_NONE, Convert_HJT_AA_16, Convert_HJT_AA_24, Convert_HJT_AA_32 };
static HermesJumpTable *Convert_HJT_CopyOnly[4] = { HJT_NONE, Convert_HJT_CopyOnly_16, Convert_HJT_CopyOnly_24, Convert_HJT_CopyOnly_32 };
static HermesJumpTable *Convert_HJT_NoAA[4] = { HJT_NONE, Convert_HJT_NoAA_16, Convert_HJT_NoAA_24, Convert_HJT_NoAA_32 };

// *** This table is as of Hermes 1.3.2 - It looks incorrect ***
static HermesJumpTableList Convert_HJT = {
	Convert_HJT_CC,	Convert_HJT_CA,	NULL,	Convert_HJT_AA,	NULL,	NULL,	Convert_HJT_CopyOnly, Convert_HJT_NoAA };

HermesHandle HERMES_API Hermes_ConverterInstance(unsigned long flags)
{
  return (Hermes_BlitterInstance(flags));
}

void HERMES_API Hermes_ConverterReturn(HermesHandle handle)
{
  Hermes_BlitterReturn(handle);
}

int HERMES_API Hermes_ConverterRequest(HermesHandle handle, HermesFormat *source, HermesFormat *dest)
{
  return (Hermes_BlitterRequest_V2(handle, source, dest, 1, &Convert_HJT));
}

int HERMES_API Hermes_ConverterPalette(HermesHandle handle, HermesHandle sourcepal, HermesHandle destpal)
{
  return Hermes_BlitterPalette(handle, sourcepal, destpal);
}


int HERMES_API Hermes_ConverterCopy(HermesHandle handle,void *s_pixels,int s_x,
				    int s_y,int s_width,int s_height,
				    int s_pitch,void *d_pixels,int d_x,int d_y,
				    int d_width,int d_height,int d_pitch)
{
	return (Hermes_BlitterBlit(handle, s_pixels, s_x, s_y, s_width, s_height, s_pitch,
		d_pixels, d_x, d_y, d_width, d_height, d_pitch));
}


