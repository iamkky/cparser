#
# Cparser Compilation System - cpcs
#
# Changes in Makefile to support a cparser passing-through processing using gcc pre-processor and gcc-compilation
#

CPARSER=cparser

.c.o:
	$(CC) -D__extension__= -D'__attribute__(...)'= -E $(CFLAGS) $(CPPFLAGS) $< | $(CPARSER) -c $<.cparsed.c -t $<.cparsed.tree -r $<.cparsed.rtree -s $<.cparsed.syms
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -fgnu89-inline -o $@ $<.cparsed.c

#	$(CC) -E $(CFLAGS) $(CPPFLAGS) $< > $<.cparsed.c
#	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<.cparsed.c

