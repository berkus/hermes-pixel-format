/*
   Type definitions for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#if defined X86_ASSEMBLER && defined __BORLANDC__
//#undef X86_ASSEMBLER
#endif

#ifndef __HERMES_TYPES__
#define __HERMES_TYPES__

typedef int HermesHandle;

#if (_MSC_VER>=1000) || defined(__VISUALC__)

typedef unsigned __int32 int32;
typedef unsigned __int16 short16;
typedef unsigned __int8 char8;

#else

#if !defined (__BEOS__) || !defined(_SUPPORT_DEFS_H)
typedef unsigned int int32;
#endif /* BEOS */

typedef unsigned short short16;
typedef unsigned char char8;

#endif /* VISUALC */

#endif
