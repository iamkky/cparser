
CPARSER=cparser

.c.o:
	$(CC) -D__extension__= -D'__attribute__(...)'= -E $(CFLAGS) $(CPPFLAGS) $< | $(CPARSER) &> $<.cparsed
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
