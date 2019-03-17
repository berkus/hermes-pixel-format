/*
   Header for utility functions for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#ifndef __HERMES_UTILITIES__
#define __HERMES_UTILITIES__


#include "H_Types.h"


/* Structure to hold shift amounts for the generic routines */

typedef struct {
  int r_right,g_right,b_right,a_right;     /* Shift amount to the right */
  int r_left,g_left,b_left,a_left;         /* Shift amount to the left */
} HermesGenericInfo;



/* Calculate the left and right shifts required for conversion */

void Hermes_Calculate_Generic_Info(int32 s_r,int32 s_g,int32 s_b,int32 s_a,
  int32 d_r,int32 d_g,int32 d_b,int32 d_a,HermesGenericInfo *info);


/* Find the highest bit set to one in the bitmask */

int Hermes_Topbit(int32 mask);


#endif
