/*
   Internal palette structure definitions for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#ifndef __HERMES_INTERNAL_PALETTE__
#define __HERMES_INTERNAL_PALETTE__

#include "List.h"
#include "H_Types.h"
#include "H_Format.h"


typedef struct {
  int32 *data;                     /* Actual lookup table */
  char valid;                      /* Is this table up to date? */
  HermesFormat format;             /* Format of lookup table */
} HermesLookupTable;


typedef struct {
  int32 *data;                     /* Palette data */

  HermesList *tables;              /* Linked list of HermesLookupTables */
} HermesPalette;


int32 *Hermes_PaletteGetTable(HermesHandle palette,HermesFormat *format);


void Hermes_PaletteMakeLookup(int32 *lookup,int32 *palette,
			      HermesFormat *format);


#endif
