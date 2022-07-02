#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "c_parser.tokens.h"

int main(int argc, char **argv)
{
int token;

	token = atoi(argv[1]);
	fprintf(stdout, "Token: %s (%d)\n", Rdpp_xParserTerminals_Names[token-1000], token);
}
