
CPARSER=cparser

.c.o:
	$(CC) -D__extension__= -D'__attribute__(...)'= -E $(CFLAGS) $(CPPFLAGS) $< | $(CPARSER) -c $<.cparsed.c -t $<.cparsed.tree -r $<.cparsed.rtree -s $<.cparsed.syms
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<.cparsed.c
