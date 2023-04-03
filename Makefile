
NRLEX=nrlex
RDPPGEN=rdppgen

CFLAGS+=-I. -O2

all: libcl.a cparser cprinttoken

cparser: cparser.o Tree.o TreeIterator.o Symbol.o Type.o libcl.a
	$(CC) $(CFLAGS) -o cparser $^

cprinttoken: cprinttoken.o Tree.o TreeIterator.o Symbol.o Type.o libcl.a
	$(CC) $(CFLAGS) -o cprinttoken $^

libcl.a: c_lex.nrlex c_parser.rdpp common.o c_parser_tools.c
	$(RDPPGEN) c_parser.rdpp
	$(NRLEX) -H c_lex.h < c_lex.nrlex > c_lex.c
	$(CC) $(CFLAGS) -c c_parser_tools.c
	$(CC) $(CFLAGS) -c c_parser.c
	$(CC) $(CFLAGS) -c c_lex.c
	$(AR) rcs libcl.a c_lex.o c_parser.o common.o c_parser_tools.o

clean:
	rm -f *.o c_lex.c c_lex.h c_parser.c c_parser.h c_parser.tokens.h cparser cprinttoken libcl.a 

