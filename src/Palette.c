/*
   Palette handling routines for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING.LIB contained in the distribution for
   licensing conditions
*/


#include <stdlib.h>
#include <string.h>
#include "H_Format.h"
#include "H_Pal.h"
#include "Palette.h"
#include "List.h"
#include "Utility.h"




static HermesList *PaletteList=0;
static int refcount=0;
static HermesHandle currenthandle=0;



HermesHandle HERMES_API Hermes_PaletteInstance()
{ HermesPalette *newinstance;
  HermesListElement *newelement;

 
  if (!PaletteList) {
    PaletteList=Hermes_ListNew();

    /* Could not create a new list */
    if (!PaletteList) return 0;
  }


  /* Create a new palette structure */

  newinstance=(HermesPalette *)malloc(sizeof(HermesPalette));
  if (!newinstance) return 0;
  

  /* Create palette data */
  newinstance->data=(int32 *)malloc(256*sizeof(int32));
  if (!newinstance->data) {
    free(newinstance);
    return 0;
  }


  /* Create lookup table list */

  newinstance->tables=Hermes_ListNew();
  if (!newinstance->tables) {
    free(newinstance->data);
    free(newinstance);
    return 0;
  }


  /* Everything fine so far, create a new list element */
  newelement=Hermes_ListElementNew(currenthandle+1);
  if (!newelement) {
    Hermes_ListDestroy(newinstance->tables);
    free(newinstance->data);
    free(newinstance);
    return 0;
  }


  /* No errors, put current palette structure into the list element and add 
     that to the list */
  newelement->data=newinstance;

  Hermes_ListAdd(PaletteList,newelement);

  refcount++;
  return ++currenthandle;
}



void HERMES_API Hermes_PaletteReturn(HermesHandle handle)
{ HermesListElement *element=Hermes_ListLookup(PaletteList,handle);
  HermesPalette *pal;
 
  if (!element) return;

  pal=(HermesPalette *)element->data;


  /* Free palette data and lookup tables */
  free(pal->data);

  element=pal->tables->first;
  while (element) {
    HermesLookupTable *table=(HermesLookupTable *)element->data;
    if (table && table->data) {
      free(table->data);
      table->data=0;
    }
    element=element->next;
  }
  Hermes_ListDestroy(pal->tables);


  /* Delete list element that holds this palette */
  Hermes_ListDeleteElement(PaletteList,handle);


  /* Decrease reference count. If down to zero, delete palette list */
  refcount--;
  if (!refcount) {
    Hermes_ListDestroy(PaletteList);
    PaletteList=0;
  }
}



void HERMES_API Hermes_PaletteSet(HermesHandle handle,int32 *palette)
{ HermesListElement *element=Hermes_ListLookup(PaletteList,handle);
  HermesPalette *pal;

  if (!element) return;

  pal=(HermesPalette *)element->data;
  
  element=pal->tables->first;

  /* Invalidate all lookup tables */
 
  while (element) {
    ((HermesLookupTable *)element->data)->valid=0;

    element=element->next;
  }

  memcpy(pal->data,palette,256*4);
}



int32* HERMES_API Hermes_PaletteGet(HermesHandle handle)
{ HermesListElement *element=Hermes_ListLookup(PaletteList,handle);
  HermesPalette *pal;

  if (!element) return 0;

  pal=(HermesPalette *)element->data;

  return pal->data;
}



int32* Hermes_PaletteGetTable(HermesHandle palette,HermesFormat *format)
{ HermesListElement *element=Hermes_ListLookup(PaletteList,palette);
  HermesPalette *pal;
  HermesLookupTable *table;

  if (!element) return 0;

  pal=(HermesPalette *)element->data;


  /* Go to the first table in the list */

  element=pal->tables->first;


  /* Search for correct table using format */

  while (element) {
    table=(HermesLookupTable *)element->data;

    if (Hermes_FormatEquals(&table->format,format)) {
      if (table->valid) return table->data;
      
      /* Have to recreate the lookup table */
      Hermes_PaletteMakeLookup(table->data,pal->data,format);
      table->valid=1;

      return table->data;
    }

    element=element->next;
  }


  /* Format not found, have to create a new table (need no handle) */

  table=(HermesLookupTable *)malloc(sizeof(HermesLookupTable));
  if (!table) return 0;

  table->data=(int32 *)malloc(1024);
  if (!table->data) return 0;

  /* Create lookup table */

  Hermes_PaletteMakeLookup(table->data,pal->data,format);
  Hermes_FormatCopy(format,&table->format);

  table->valid=1;

  /* Create a new list element */

  element=Hermes_ListElementNew(0);
  if (!element) return 0;
  element->data=table;

  /* Add to the front of the list */

  Hermes_ListAddFront(pal->tables,element);

  /* Return lookup data */
  return table->data;
}



void HERMES_API Hermes_PaletteInvalidateCache(HermesHandle handle)
{ HermesListElement *element=Hermes_ListLookup(PaletteList,handle);
  HermesPalette *pal;
  
  if (!element) return;
  	  
  pal=(HermesPalette *)element->data;
      
  element=pal->tables->first;
        
  /* Invalidate all lookup tables */
          
  while (element) {
    ((HermesLookupTable *)element->data)->valid=0;
                
    element=element->next;
  }
}
                      
                      
void Hermes_PaletteMakeLookup(int32 *lookup,int32 *palette,
			      HermesFormat *format)
{ HermesGenericInfo info;
  int i;
  int32 r=0,g=0,b=0;

  if (format->indexed) return;
  
  Hermes_Calculate_Generic_Info(24,16,8,32,
				Hermes_Topbit(format->r),
				Hermes_Topbit(format->g),
				Hermes_Topbit(format->b),
				Hermes_Topbit(format->a),
				&info);

  /* Optimised loop if there are no left shifts */
 
  if(!info.r_left && !info.g_left && !info.b_left)
  for(i=0;i<256;i++)
  { r=(palette[i]>>info.r_right)&format->r;
    g=(palette[i]>>info.g_right)&format->g;
    b=(palette[i]>>info.b_right)&format->b;
    
    lookup[i]=r|g|b;
  }   
  else
  for(i=0;i<256;i++)
  { r=((palette[i]>>info.r_right)<<info.r_left)&format->r;
    g=((palette[i]>>info.g_right)<<info.g_left)&format->g;
    b=((palette[i]>>info.b_right)<<info.b_left)&format->b;
   
    lookup[i]=r|g|b;
  }  
}

