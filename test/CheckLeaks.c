#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Hermes.h"

int main()
{ HermesHandle h1,h2,h3;

  printf("Start - Used Memory: %d\n",mallinfo().uordblks);

  Hermes_Init();
  printf("Init - Used Memory: %d\n",mallinfo().uordblks);

  h1=Hermes_ConverterInstance(0);
  printf("Converter - Used Memory: %d\n",mallinfo().uordblks);
        
  h2=Hermes_ClearerInstance();
  printf("Clearer - Used Memory: %d\n",mallinfo().uordblks);

  h3=Hermes_PaletteInstance();
  printf("Palette - Used Memory: %d\n",mallinfo().uordblks);
   
  Hermes_ConverterReturn(h1);
  Hermes_ClearerReturn(h2);
  Hermes_PaletteReturn(h3);
  
  printf("Everything returned - Used Memory: %d\n",mallinfo().uordblks);

  Hermes_Done();
//  malloc_trim(0);
  printf("Deinit - Used Memory: %d\n",mallinfo().uordblks);      

  return 0;
}
