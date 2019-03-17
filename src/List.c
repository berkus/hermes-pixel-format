/*
   Linked list implementation for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/


#include <stdlib.h>
#include "List.h"



HermesList *Hermes_ListNew()
{ HermesList *tmp;

  tmp=(HermesList *)malloc(sizeof(HermesList));
  if (!tmp) return 0;

  tmp->first=0;
  tmp->last=0;

  return tmp;
}



void Hermes_ListDestroy(HermesList *list)
{ HermesListElement *run,*tmp;

  if (!list) return;

  run=list->first;

  while (run) {
    tmp=run;

    run=run->next;

    if (tmp->data) free(tmp->data);

    free(tmp);
  }

  free(list);
  list=0;
}



HermesListElement *Hermes_ListElementNew(HermesHandle handle)
{ HermesListElement *tmp;

  tmp=(HermesListElement *)malloc(sizeof(HermesListElement));
  if (!tmp) return 0;

  tmp->handle=handle;
  tmp->next=0;
  tmp->data=0;

  return tmp;
}


void Hermes_ListAdd(HermesList *list,HermesListElement *element)
{ if (!list || !element) return;

  if (!list->first) {
    list->first=element;
    list->last=element;

    element->next=0;
    return;
  }

  /* Make the old last point to the new element */
  list->last->next=element;
  /* Make the element the new last */
  list->last=element;

  element->next=0;
}



void Hermes_ListAddFront(HermesList *list,HermesListElement *element)
{
  if (!list || !element) return;

  if (!list->first) {
    list->first=element;
    list->last=element;

    element->next=0;
    return;
  }

  element->next=list->first;
  list->first=element;
}



int Hermes_ListDeleteElement(HermesList *list,HermesHandle handle)
{ HermesListElement *run,*previous;

  if (!list) return 0;
 
  previous=0;
  run=list->first;

  while (run) {

    if (run->handle==handle) {

      if (run==list->first)
      list->first=run->next;
      else
      previous->next=run->next;
      
      if (run==list->last)
      { list->last=previous;
        if(list->last)
        list->last->next=0;
      }

      if (run->data)
      free(run->data);

      free(run);

      return 1;
    }
    
    previous=run;
    run=run->next;
  }

  return 0;
}




HermesListElement *Hermes_ListLookup(HermesList *list,HermesHandle handle)
{ HermesListElement *run;
  
  if (!list) return 0;

  run=list->first;

  while (run) {
    if (run->handle==handle) return run;

    run=run->next;
  }

  return 0;
}

