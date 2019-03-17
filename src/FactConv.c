#include "HermConf.h"
#include "Factory.h"
#include "HeadMMX.h"
#include "HeadX86.h"
#include "HeadC.h"

/* Placeholder converter. This is for things like 8 bit converters that have
   one main loop and NO scanline conversion function as opposed to most others
   which use the generic loop.
   There needs to be a function assigned to the scanline loop however, 
   otherwise the converter will fail a test in Convert.c. This is the easiest
   way. Do NOT use NotApplicable as NotYetImplemented ! */


void NotApplicable(char8 *source,char8 *dest,unsigned int count, 
  unsigned int inc_source)
{
  if (source);
  if (dest);
  if (count);
  if (inc_source);
}



/* Factory converter array, holds ALL converters available from HERMES. Note
   that converters have to be assigned IN ORDER of priority for processors
   that can run different converters.
   Thus, for an Intel MMX Pentium, the order would be:

      - MMX converters
      - X86 converters
      - C converters

   If someone wrote a P2 or P3 converter, if would be added even further up.
*/


HermesFactoryStruct Factory_Converters[]=
{
#ifdef X86_ASSEMBLER

/* disable visual c++ warning */
#if (_MSC_VER>=1000)
#pragma warning( disable : 4113 )
#endif
#pragma error

  /* ------ From 32 RGB 888 - MMX PENTIUM II ---- */
  {32,0,0xff0000,0xff00,0xff,0,24,0,0xff0000,0xff00,0xff,0,ConvertMMX,0,
   ConvertMMXpII32_24RGB888,0,0,0,PROC_MMX_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0xf800,0x7e0,0x1f,0,ConvertMMX,0,
   ConvertMMXpII32_16RGB565,0,0,0,PROC_MMX_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x7e0,0xf800,0,ConvertMMX,0,
   ConvertMMXpII32_16BGR565,0,0,0,PROC_MMX_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0,ConvertMMX,0,
   ConvertMMXpII32_16RGB555,0,0,0,PROC_MMX_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0,ConvertMMX,0,
   ConvertMMXpII32_16BGR555,0,0,0,PROC_MMX_PENTIUM},

  /* ------ From 32 RGB 888 - MMX PENTIUM ------- */

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0,ConvertMMX,0,
   ConvertMMXp32_16RGB555,0,0,0,PROC_MMX_PENTIUM},
  

  /* ------ From 32 RGB 888 - X86 PENTIUM ------- */

  {32,0,0xff0000,0xff00,0xff,0,32,0,0xff,0xff00,0xff0000,0,ConvertX86,0,
   ConvertX86p32_32BGR888,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,32,0,0xff000000,0xff0000,0xff00,0xff,
   ConvertX86,0,
   ConvertX86p32_32RGBA888,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,32,0,0xff00,0xff0000,0xff000000,0xff,
   ConvertX86,0,
   ConvertX86p32_32BGRA888,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,24,0,0xff0000,0xff00,0xff,0,ConvertX86,0,
   ConvertX86p32_24RGB888,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,24,0,0xff,0xff00,0xff0000,0,ConvertX86,0,
   ConvertX86p32_24BGR888,0,0,0,PROC_X86_PENTIUM},
  
  {32,0,0xff0000,0xff00,0xff,0,16,0,0xf800,0x7e0,0x1f,0,
   ConvertX86,ConvertX86Stretch,
   ConvertX86p32_16RGB565,ConvertX86p32_16RGB565_S,
   0,0,PROC_X86_PENTIUM},
  
  {32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x7e0,0xf800,0,ConvertX86,0,
   ConvertX86p32_16BGR565,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0,ConvertX86,0,
   ConvertX86p32_16RGB555,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0,ConvertX86,0,
   ConvertX86p32_16BGR555,0,0,0,PROC_X86_PENTIUM},

  {32,0,0xff0000,0xff00,0xff,0,8,0,0xe0,0x1c,0x3,0,ConvertX86,0,
   ConvertX86p32_8RGB332,0,0,0,PROC_X86_PENTIUM},



  /* ------ From 16 RGB 565 - X86 PENTIUM ------- */

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff0000,0xff00,0xff,0,ConvertX86,0,
   ConvertX86p16_32RGB888,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff,0xff00,0xff0000,0,ConvertX86,0,
   ConvertX86p16_32BGR888,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff000000,0xff0000,0xff00,0xff,ConvertX86,0,
   ConvertX86p16_32RGBA888,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff00,0xff0000,0xff000000,0xff,ConvertX86,0,
   ConvertX86p16_32BGRA888,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,24,0,0xff0000,0xff00,0xff,0,ConvertX86,0,
   ConvertX86p16_24RGB888,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,24,0,0xff,0xff00,0xff0000,0,ConvertX86,0,
   ConvertX86p16_24BGR888,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,16,0,0x1f,0x7e0,0xf800,0,ConvertX86,0,
   ConvertX86p16_16BGR565,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,16,0,0x7c00,0x3e0,0x1f,0,ConvertX86,0,
   ConvertX86p16_16RGB555,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,16,0,0x1f,0x3e0,0x7c00,0,ConvertX86,0,
   ConvertX86p16_16BGR555,0,0,0,PROC_X86_PENTIUM},

  {16,0,0xf800,0x7e0,0x1f,0,8,0,0xe0,0x1c,0x3,0,ConvertX86,0,
   ConvertX86p16_8RGB332,0,0,0,PROC_X86_PENTIUM},

  {8,1,0,0,0,0,16,0,0,0,0,0,ConvertX86,0,
   ConvertX86pI8_16,0,0,0,PROC_X86_PENTIUM},
     

#endif
  
  /* ------ From 32 RGBA 8888 ----*/
  /*
  {32,0,0xff000000,0xff0000,0xff00,0xff,32,0,0xff000000,0xff0000,0xff00,0xff,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_32bgr888,ConvertC_32rgb888_32bgr888_S,
   0,0,PROC_GENERIC},
  */
  
  /* ------ From 32 RGB 888 ------- */

  {32,0,0xff0000,0xff00,0xff,0,32,0,0xff,0xff00,0xff0000,0,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_32bgr888,ConvertC_32rgb888_32bgr888_S,
   0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,32,0,0xff000000,0xff0000,0xff00,0xff,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_32rgba888,ConvertC_32rgb888_32rgba888_S,
   0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,32,0,0xff00,0xff0000,0xff000000,0xff,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_32bgra888,ConvertC_32rgb888_32bgra888_S,
   0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,24,0,0xff0000,0xff00,0xff,0,ConvertC,0,
   ConvertC_32rgb888_24rgb888,0,0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,24,0,0xff,0xff00,0xff0000,0,ConvertC,0,
   ConvertC_32rgb888_24bgr888,0,0,0,PROC_GENERIC},

  
  {32,0,0xff0000,0xff00,0xff,0,16,0,0xf800,0x7e0,0x1f,0,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_16rgb565,ConvertC_32rgb888_16rgb565_S,
   ConvertC_32rgb888_16rgb565_dither,0,PROC_GENERIC},
  
  {32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x7e0,0xf800,0,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_16bgr565,ConvertC_32rgb888_16bgr565_S,0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_16rgb555,ConvertC_32rgb888_16rgb555_S,0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_16bgr555,ConvertC_32rgb888_16bgr555_S,0,0,PROC_GENERIC},

  {32,0,0xff0000,0xff00,0xff,0,8,0,0xe0,0x1c,0x3,0,
   ConvertC,ConvertCStretch,
   ConvertC_32rgb888_8rgb332,ConvertC_32rgb888_8rgb332_S,
   ConvertC_32rgb888_8rgb332_dither,0,PROC_GENERIC},



 /* ------ From 32 RGB MUHMU ------- */

  {32,0,0xff<<20,0xff<<10,0xff,0,32,0,0xff0000,0xff00,0xff,0,ConvertC,0,
   ConvertC_muhmu32_32rgb888,0,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,32,0,0xff,0xff00,0xff0000,0,ConvertC,0,
   ConvertC_muhmu32_32bgr888,0,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,32,0,0xff000000,0xff0000,0xff00,0xff,
   ConvertC,0,
   ConvertC_muhmu32_32rgba888,0,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,32,0,0xff00,0xff0000,0xff000000,0xff,
   ConvertC,0,
   ConvertC_muhmu32_32bgra888,0,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,24,0,0xff0000,0xff00,0xff,0,
   ConvertC,0,
   ConvertC_muhmu32_24rgb888,0,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,24,0,0xff,0xff00,0xff0000,0,
   ConvertC,0,
   ConvertC_muhmu32_24bgr888,0,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,16,0,0xf800,0x7e0,0x1f,0,
   ConvertC,ConvertCStretch,
   ConvertC_muhmu32_16rgb565,ConvertC_muhmu32_16rgb565_S,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,16,0,0x1f,0x7e0,0xf800,0,
   ConvertC,ConvertCStretch,
   ConvertC_muhmu32_16bgr565,ConvertC_muhmu32_16bgr565_S,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,16,0,0x7c00,0x3e0,0x1f,0,
   ConvertC,ConvertCStretch,
   ConvertC_muhmu32_16rgb555,ConvertC_muhmu32_16rgb555_S,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,16,0,0x1f,0x3e0,0x7c00,0,
   ConvertC,ConvertCStretch,
   ConvertC_muhmu32_16bgr555,ConvertC_muhmu32_16bgr555_S,0,0,PROC_GENERIC},

  {32,0,0xff<<20,0xff<<10,0xff,0,8,0,0xe0,0x1c,0x3,0,
   ConvertC,ConvertCStretch,
   ConvertC_muhmu32_8rgb332,ConvertC_muhmu32_8rgb332_S,0,0,PROC_GENERIC},


  /* ------ From 24 RGB 888 ------- */

  {24,0,0xff0000,0xff00,0xff,0,32,0,0xff0000,0xff00,0xff,0,ConvertC,0,
   ConvertC_24rgb888_32rgb888,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,32,0,0xff,0xff00,0xff0000,0,ConvertC,0,
   ConvertC_24rgb888_32bgr888,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,32,0,0xff000000,0xff0000,0xff00,0xff,ConvertC,0,
   ConvertC_24rgb888_32rgba888,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,32,0,0xff00,0xff0000,0xff000000,0xff,ConvertC,0,
   ConvertC_24rgb888_32bgra888,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,24,0,0xff,0xff00,0xff0000,0,ConvertC,0,
   ConvertC_24rgb888_24bgr888,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,16,0,0xf800,0x7e0,0x1f,0,ConvertC,0,
   ConvertC_24rgb888_16rgb565,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x7e0,0xf800,0,ConvertC,0,
   ConvertC_24rgb888_16bgr565,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,16,0,0x7c00,0x3e0,0x1f,0,ConvertC,0,
   ConvertC_24rgb888_16rgb555,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,16,0,0x1f,0x3e0,0x7c00,0,ConvertC,0,
   ConvertC_24rgb888_16bgr555,0,0,0,PROC_GENERIC},

  {24,0,0xff0000,0xff00,0xff,0,8,0,0xe0,0x1c,0x3,0,ConvertC,0,
   ConvertC_24rgb888_8rgb332,0,0,0,PROC_GENERIC},



  /* ------ From 16 RGB 565 ------- */

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff0000,0xff00,0xff,0,
   ConvertC,ConvertCStretch,
   ConvertC_16rgb565_32rgb888,ConvertC_16rgb565_32rgb888_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff,0xff00,0xff0000,0,
   ConvertC,ConvertCStretch,
   ConvertC_16rgb565_32bgr888,ConvertC_16rgb565_32bgr888_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff000000,0xff0000,0xff00,0xff,
   ConvertC,ConvertCStretch,
   ConvertC_16rgb565_32rgba888,ConvertC_16rgb565_32rgba888_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,32,0,0xff00,0xff0000,0xff000000,0xff,
   ConvertC,ConvertCStretch,
   ConvertC_16rgb565_32bgra888,ConvertC_16rgb565_32bgra888_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,24,0,0xff0000,0xff00,0xff,0,ConvertC,0,
   ConvertC_16rgb565_24rgb888,0,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,24,0,0xff,0xff00,0xff0000,0,ConvertC,0,
   ConvertC_16rgb565_24bgr888,0,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,16,0,0x1f,0x7e0,0xf800,0,ConvertC,ConvertCStretch,
   ConvertC_16rgb565_16bgr565,ConvertC_16rgb565_16bgr565_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,16,0,0x7c00,0x3e0,0x1f,0,ConvertC,ConvertCStretch,
   ConvertC_16rgb565_16rgb555,ConvertC_16rgb565_16rgb555_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,16,0,0x1f,0x3e0,0x7c00,0,ConvertC,ConvertCStretch,
   ConvertC_16rgb565_16bgr555,ConvertC_16rgb565_16bgr555_S,0,0,PROC_GENERIC},

  {16,0,0xf800,0x7e0,0x1f,0,8,0,0xe0,0x1c,0x3,0,ConvertC,ConvertCStretch,
   ConvertC_16rgb565_8rgb332,ConvertC_16rgb565_8rgb332_S,0,0,PROC_GENERIC},

 

  /* ------ From 8 bit INDEXED ------- */   

  {8,1,0,0,0,0,32,0,0,0,0,0,ConvertC_index8_32,ConvertC_index8_32_S,
   NotApplicable,NotApplicable,0,0,PROC_GENERIC},

  {8,1,0,0,0,0,24,0,0,0,0,0,ConvertC_index8_24,0,NotApplicable,0,0,0,
   PROC_GENERIC},

  {8,1,0,0,0,0,16,0,0,0,0,0,ConvertC_index8_16,ConvertC_index8_16_S,
   NotApplicable,NotApplicable,0,0,PROC_GENERIC},

};


int Factory_NumConverters=sizeof(Factory_Converters)/sizeof(HermesFactoryStruct);



