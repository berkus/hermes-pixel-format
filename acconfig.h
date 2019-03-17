#undef PACKAGE
#undef VERSION
#undef X86_ASSEMBLER
#undef DEBUG_LEVEL1
#undef DEBUG_LEVEL2

/* Define bit/little endian for Hermes */
#ifdef WORDS_BIGENDIAN
#define __BIG_ENDIAN__ 1
#else
#define __LITTLE_ENDIAN__ 1
#endif
