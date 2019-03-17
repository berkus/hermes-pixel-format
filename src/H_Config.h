/*
   API definitions for the HERMES library
   Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
   This source code is licensed under the GNU LGPL
  
   Please refer to the file COPYING contained in the distribution for
   licensing conditions
*/

#if defined X86_ASSEMBLY && defined __BORLANDC__
//#undef X86_ASSEMBLER
#endif

#ifndef __HERMES_APIDEF__
#define __HERMES_APIDEF__

#if defined(WIN32) || defined(_WIN32) || defined(WINDOWS) || defined(__NT__)

#define HERMES_API __stdcall

#else
#define HERMES_API

#endif /* _WIN32 */


#ifdef __cplusplus

#define HERMES_C extern "C"

#else

#define HERMES_C

#endif /* __cplusplus */


#endif




