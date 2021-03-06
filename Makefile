
NRLEX=nrlex
RDPPGEN=rdppgen

CFLAGS+=-I. -gstabs 

all: libcl.a cparser cprinttoken common.o

cparser: cparser.o Tree.o TreeIterator.o Symbol.o libcl.a
	$(CC) $(CFLAGS) -o cparser cparser.o Tree.o TreeIterator.o Symbol.o libcl.a

cprinttoken: cprinttoken.o Tree.o TreeIterator.o Symbol.o libcl.a
	$(CC) $(CFLAGS) -o cprinttoken cprinttoken.o Tree.o TreeIterator.o Symbol.o libcl.a

libcl.a: c_lex.nrlex c_parser.rdpp Tree.c common.o c_parser_tools.c
	$(RDPPGEN) c_parser.rdpp
	$(NRLEX) -H c_lex.h < c_lex.nrlex > c_lex.c
	$(CC) $(CFLAGS) -c c_parser_tools.c
	$(CC) $(CFLAGS) -c c_parser.c
	$(CC) $(CFLAGS) -c c_lex.c
	$(CC) $(CFLAGS) -c Tree.c
	$(AR) rcs libcl.a c_lex.o c_parser.o common.o c_parser_tools.o

clean:
	rm -f *.o c_lex.c c_lex.h c_parser.c c_parser.h c_parser.tokens.h cparser cprinttoken libcl.a 

