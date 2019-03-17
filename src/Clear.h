/*
   Header definitions surface clearing routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#ifndef __HERMES_INTERNAL_CLEAR__
#define __HERMES_INTERNAL_CLEAR__

#include "HermConf.h"
#include "H_Types.h"


typedef struct {
  char8 *dest;
  int32 value;
  unsigned int width;
  unsigned int height;
  int add;
} HermesClearInterface;


typedef void STACKCALL (*HermesClearPtr)(HermesClearInterface *);


typedef struct {
  int bits;
  HermesClearPtr func;                     /* Clearer function */
} HermesClearer;

extern HermesClearer *Clearers[4];
extern int numClearers;




#endif
