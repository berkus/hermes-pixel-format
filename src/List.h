/*
   Linked list header file for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#ifndef __HERMES_MUTABLE__
#define __HERMES_MUTABLE__


#include "H_Types.h"


typedef struct HermesListElementStruct {
  HermesHandle handle;
  void *data;

  struct HermesListElementStruct *next;
} HermesListElement;


typedef struct {
  HermesListElement *first;
  HermesListElement *last;
} HermesList;



/* Create a new linked list. Returns 0 if failed */
HermesList *Hermes_ListNew();


/* Destroy the list pointed to by list */
void Hermes_ListDestroy(HermesList *list);


/* Create a new list element. Returns 0 if failed */
HermesListElement *Hermes_ListElementNew(HermesHandle handle);


/* Add element to the back of the list (this will overwrite the elements next
   pointer! */
void Hermes_ListAdd(HermesList *list,HermesListElement *element);


/* Add element to the front of the list(this will overwrite the elements next
   pointer */
void Hermes_ListAddFront(HermesList *list,HermesListElement *element);


/* Find element with handle 'handle' and remove it from the list. Returns 0
   if failed */
int Hermes_ListDeleteElement(HermesList *list,HermesHandle handle);


/* Lookup element with handle 'handle', returns 0 if failed */
HermesListElement *Hermes_ListLookup(HermesList *list,HermesHandle handle);


#endif

