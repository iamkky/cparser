
NRLEX=nrlex
RDPPGEN=rdppgen

CFLAGS+=-I. -gstabs 

all: libcl.a cparser cprinttoken

cparser: cparser.o libcl.a Tree.o Symbol.o
	$(CC) $(CFLAGS) -o cparser cparser.o libcl.a Tree.o Symbol.o

cprinttoken: cprinttoken.o libcl.a Tree.o Symbol.o
	$(CC) $(CFLAGS) -o cprinttoken cprinttoken.o libcl.a Tree.o Symbol.o

libcl.a: c_lex.nrlex c_parser.rdpp Tree.c
	$(RDPPGEN) c_parser.rdpp
	$(NRLEX) -H c_lex.h < c_lex.nrlex > c_lex.c
	$(CC) $(CFLAGS) -c c_parser.c
	$(CC) $(CFLAGS) -c c_lex.c
	$(CC) $(CFLAGS) -c Tree.c
	$(AR) rcs libcl.a c_lex.o c_parser.o

clean:
	rm -f *.o c_lex.c c_lex.h c_parser.c c_parser.h c_parser.tokens.h cparser cprinttoken libcl.a 

