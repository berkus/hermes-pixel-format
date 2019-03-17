## Process this file with automake to create Makefile.in

publicheaders = Hermes.h Types.h H_Conv.h H_Clear.h H_Pal.h H_Format.h H_Config.h H_Types.h H_Blit.h

lib_LTLIBRARIES = libHermes.la

if BUILDASM
ASMSOURCES = mmx_main.S mmx_clr.S mmxp_32.S x86_clr.S x86_main.S \
  x86p_16.S x86p_32.S x86p_s32.S x86p_cpy.S x86p_i8.S mmxp2_32.S
else
ASMSOURCES = 
endif

libHermes_la_SOURCES = Clear.c Convert.c Blit.c Dither.c FactConv.c Factory.c \
  Format.c Hermes.c List.c Palette.c Utility.c c_16.c c_24.c c_32.c \
  c_clr.c c_cnv.c c_cpy.c c_genrc.c c_genrc_ac.c c_genrc_ca.c c_genrc_a.c c_genrc_cc.c c_genrc_cc_blit.c \
  c_genrc_co_blit.c c_i8.c c_muhmu.c d_32.c c_genrc_ao_blit.c c_genrc_noalpha_alpha.c \
  $(ASMSOURCES) 

libHermes_la_LDFLAGS = -no-undefined -version-info $(HERMES_CURRENT):$(HERMES_REVISION):$(HERMES_AGE)
libHermes_la_LIBADD = $(HERMES_LIBS)

##SUFFIXES = .asm
##.asm.lo:
##	nasm -o $@ -f elf $<
##	cp $@ `echo $@ | sed -e 's/\.lo$$/.o/'`

SUFFIXES = .S

.S.o:
	gcc -c -o $@ $<
	cp $@ `echo $@ | sed -e 's/\.lo$$/.o/'`

install-data-local:
	$(INSTALL) -m 0755 -d $(includedir)/Hermes
	for incfile in $(publicheaders); do \
	  $(INSTALL) -m 0644 $$incfile $(includedir)/Hermes; \
	done

uninstall-local:
	for incfile in $(publicheaders); do \
	  rm -f $(includedir)/Hermes/$$incfile; \
	done
	rmdir $(includedir)/Hermes

libHermes.la: $(libHermes_la_OBJECTS) $(libHermes_la_DEPENDENCIES)
	$(LINK) -rpath $(libdir) $(libHermes_la_LDFLAGS) \
	$(libHermes_la_OBJECTS) $(libHermes_la_LIBADD) $(LIBS)
