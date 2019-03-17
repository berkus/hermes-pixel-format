/*
   The big fat ifdef-rich configuration header for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/
#if defined X86_ASSEMBLER && defined __BORLANDC__
//#undef X86_ASSEMBLER
#endif

#ifndef __HERMES_CONF_H__
#define __HERMES_CONF_H__


#define HERMES_INITIAL 8             /* Initial size and growth of dynamic */
#define HERMES_GROWTH 4              /* array structures */

#ifdef __unix__
#ifndef __DJGPP__
#include "hrconfig.h"
#endif
#endif 


#ifdef __CYGWIN32__
  #define __CYGNUS__
#endif /* CYGWIN32 */

#if (_MSC_VER>=1000)
  #define __VISUALC__
#endif /* MSC_VER */


#if defined(WIN32) || defined(_WIN32) || defined(WINDOWS) || defined(__NT__)
  #define __WIN32__ 1
  #define __LITTLE_ENDIAN__ 1
  #undef __BIG_ENDIAN__
  #define X86_ASSEMBLER 1
#endif /* WIN32 */

#if defined (__sun)
  #define __BIG_ENDIAN__
  #undef __LITTLE_ENDIAN__ 1
#endif

#if defined(__WATCOMC__) || defined(__DJGPP__) || defined(__CYGNUS__)
  #define __LITTLE_ENDIAN__ 1
  #undef __BIG_ENDIAN__
#endif /* __WATCOMC__ */


#if defined (__WATCOMC__)
  #define STACKCALL cdecl
#else
  #define STACKCALL
#endif /* __WATCOMC__ */


#if defined ( __BEOS__ )
#  if defined ( __INTEL__ )
#    define __LITTLE_ENDIAN__ 1
#    undef __BIG_ENDIAN__
#  else
#    define __BIG_ENDIAN__ 1
#    undef __LITTLE_ENDIAN__ 
#  endif
#endif /* __BEOS__ */




/* Macros to help with big/little endian problems */

#if defined __LITTLE_ENDIAN__
  #define A_32 3		   /* oh yes, hardcode it... tsk tsk tsk */
  #define R_32 2                   /* Position of R,G,B in a 32 bit dword */
  #define G_32 1
  #define B_32 0
  #define R_24 2                   /* Position of R,G,B in a 24 bit pixel */
  #define G_24 1
  #define B_24 0
  #define DWORD_BYTE0(s) s         /* Shift values to get to bytes in dwords */
  #define DWORD_BYTE1(s) ((s)<<8)  /* Check out the bracket paranoia to */   
  #define DWORD_BYTE2(s) ((s)<<16) /* prevent bugs :)) */     
  #define DWORD_BYTE3(s) ((s)<<24)       
  #define DWORD_SHORT0(s) s
  #define DWORD_SHORT1(s) ((s)<<16)
  #define DWORD_SHORT0(s) s
  #define DWORD_SHORT1(s) ((s)<<16)
#elif defined __BIG_ENDIAN__
  #define A_32 0
  #define R_32 1
  #define G_32 2
  #define B_32 3
  #define R_24 0
  #define G_24 1
  #define B_24 2
  #define DWORD_BYTE0(s) ((s)<<24)
  #define DWORD_BYTE1(s) ((s)<<16)
  #define DWORD_SHORT0(s) ((s)<<16)
  #define DWORD_SHORT1(s) s
  #define DWORD_BYTE2(s) ((s)<<8)
  #define DWORD_BYTE3(s) s
  #define DWORD_SHORT0(s) ((s)<<16)
  #define DWORD_SHORT1(s) s
#else
  #error Processor endian-ness not defined!
#endif

#endif


