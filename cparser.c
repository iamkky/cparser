#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "Symbol.h"
#include "Tree.h"
#include "c_parser.h"

char *readToBuffer(int fd, int inisize, int extrasize, int *readsize)
{
int bsize, r, rsize;
char *buffer, *tmp;

	bsize=inisize;
	if((buffer = malloc(bsize + extrasize))==NULL) return NULL;

	rsize=0;

	do{
		if(rsize>=bsize){
			bsize += bsize;
			if((tmp = realloc(buffer, bsize + extrasize))==NULL){
				*readsize = 0;
				free(buffer);
				return NULL;
			}
			buffer = tmp;
		} 
		r = read(fd, buffer+rsize, bsize - rsize);
		rsize += r;
	}while(r>0);

	*readsize = rsize;
	return buffer;
}

int main(int argc, char **argv)
{
//CxValue  json;
xParser x;
char *buffer;
int bytes, result;
int lcount;

	//bytes = read(0, buffer, 32767);
	buffer = readToBuffer(0, 32768, 1, &bytes);
	buffer[bytes] = 0;

	x = xParserNew(buffer, &lcount);	

	lcount = 0;
	result = xParserParse(x);

	fprintf(stdout,"Input Size: %d\n", bytes);
	fprintf(stdout,"cursor: %d\n", x->cursor);
	fprintf(stdout,"Last Token: %d\n", x->currToken);

	if(result>0){
		fprintf(stderr,"Success to parse line\n\n");

		fprintf(stdout,"\nResult:\n");
		treePrint(x->value[0].t, stdout, 2);
		fprintf(stdout,"\n");

		fprintf(stdout,"Result (only tokens):\n");
		treePrintToken(x->value[0].t, stdout, 2, RDPP_NONTERMINAL_START);
		fprintf(stdout,"\n\n");
	
		x->value[0].t = treeReduceToMinimal(x->value[0].t, RDPP_NONTERMINAL_START);

		fprintf(stdout,"Result (reduced 1):\n");
		treePrint(x->value[0].t, stdout, 2);
		fprintf(stdout,"\n\n");

		fprintf(stdout,"Result (only tokens):\n");
		treePrintToken(x->value[0].t, stdout, 2, RDPP_NONTERMINAL_START);
		fprintf(stdout,"\n\n");

		//list = x->value[0].complist;
		//fprintf(stdout,"\nPrint:\n");
		//xComponentListPrint(list, stdout, 0);
		//fprintf(stdout,"\nCode:\n");
		//cxComponentListGenCode(list, stdout, 0);
		//fprintf(stdout,";\n");
		/*
		fprintf(stderr,"Value Type %02d\n", jsonValueGetType(json));
		fprintf(stdout,"\n");
		jsonValueFree(json);
		*/
	}else{
		fprintf(stderr,"Failed to parse line %d\n", lcount);
	}
	

	xParserFree(x);
	free(buffer);
}

