#if defined X86_ASSEMBLER && defined __BORLANDC__
//#undef X86_ASSEMBLER
#endif

#ifndef __HERMES_FORMAT__
#define __HERMES_FORMAT__


#include "H_Types.h"
#include "H_Config.h"

typedef struct {
  int32 r,g,b,a;                   /* Bitmasks for red, green, blue, alpha */
  int bits;                        /* Bits per pixel */
  char indexed;                    /* 1 if indexed colour format */
  char has_colorkey;               /* 1 if colorkey transparency is used */
  int32 colorkey;                  /* colorkey, if has_colorkey is 1 */
} HermesFormat;

HERMES_C HermesFormat* HERMES_API Hermes_FormatNewEmpty();

/* Create a new format structure, returns 0 if failed.
*/
HERMES_C HermesFormat* HERMES_API Hermes_FormatNew(int bits,int32 r,int32 g,
					  int32 b,int32 a,char indexed);
/* Free a format structure
*/
HERMES_C void HERMES_API Hermes_FormatFree(HermesFormat* fmt);

/* Create a new format structure with colorkey info, returns 0 if failed.
*/
HERMES_C HermesFormat* HERMES_API Hermes_FormatNewEx(int bits,int32 r,int32 g,
					  int32 b,int32 a,char indexed,char has_colorkey,
					  int32 colorkey);

/* Compare two formats. Return 1 if they are equal, 0 otherwise */
HERMES_C char HERMES_API Hermes_FormatEquals(HermesFormat *op1,
					     HermesFormat *op2);

/* Copy the contents of format 'source' to format 'destination' */
HERMES_C void HERMES_API Hermes_FormatCopy(HermesFormat *source,
					   HermesFormat *dest);

#endif

