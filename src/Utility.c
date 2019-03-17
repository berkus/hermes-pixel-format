/*
   Implementation of utility routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/

#include "Utility.h"


void Hermes_Calculate_Generic_Info(int32 s_r,int32 s_g,int32 s_b,int32 s_a,
  int32 d_r,int32 d_g,int32 d_b,int32 d_a,HermesGenericInfo *info)
{ int r_right,g_right,b_right,a_right;
  
  /* Calculate right shift amount for red. If it's <0, then set it to null
     and calculate left shift amount */

  r_right=s_r-d_r;
  if(r_right<0)
  { info->r_left=-r_right;
    info->r_right=0;
  }
  else
  { info->r_left=0;
    info->r_right=r_right;
  }
   
  /* Same for green */

  g_right=s_g-d_g;
  if(g_right<0)
  { info->g_left=-g_right;
    info->g_right=0;
  }
  else
  { info->g_left=0;
    info->g_right=g_right;
  }

  /* Same for blue */

  b_right=s_b-d_b;
  if(b_right<0)
  { info->b_left=-b_right;
    info->b_right=0;
  }
  else
  { info->b_left=0;
    info->b_right=b_right;
  }

  /* Alpha */

  a_right=s_a-d_a;
  if(a_right<0)
  { info->a_left=-a_right;
    info->a_right=0;
  }
  else
  { info->a_left=0;
    info->a_right=a_right;
  }
}



int Hermes_Topbit(int32 mask)
{ int i;

  if(!mask) return 0;

  i=0;

  while(!(mask&1))
  { mask>>=1;
    i++;
  }

  while(mask&1)
  { mask>>=1;
    i++;
  }

  return i;
}


