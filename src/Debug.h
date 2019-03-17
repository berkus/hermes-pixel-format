#if defined X86_ASSEMBLER && defined __BORLANDC__
//#undef X86_ASSEMBLER
#endif

#ifndef __HERMES_DEBUG__
#define __HERMES_DEBUG__

#include "HermConf.h"

#if defined(DEBUG_LEVEL1) || defined (DEBUG_LEVEL2)

#include <stdio.h>

#ifndef __FILE__
#error "__FILE__" variable not available for debugging!
#endif
#ifndef __LINE__
#error "__LINE__" variable not available for debugging!
#endif

#define DEBUG_ASSERT(e) if (!(e)) \
    fprintf(stderr,"HERMES Warning: Assertion failed in %s:%d!\n",__FILE__, \
	    __LINE__);
#define DEBUG_PRINT(f,d) printf(f,d);
#define DEBUG_FNAME(n) fprintf(stderr,"%s\n",n);

#if defined (DEBUG_LEVEL2)

#define DEBUG_PRINT2(f,d) printf(f,d);
#define DEBUG_FNAME2(n) fprintf(stderr,"%s\n",n);

#else

#define DEBUG_PRINT2(f,d) { }
#define DEBUG_FNAME2(n) { }
 
#endif /* DEBUG_LEVEL2 */

#else

#define DEBUG_ASSERT(name,e) { }
#define DEBUG_PRINT(f,d) { }
#define DEBUG_FNAME(n) { }

#define DEBUG_PRINT2(f,d) { }
#define DEBUG_FNAME2(n) { }

#endif





#endif
