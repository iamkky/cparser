#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "Symbol.h"
#include "Tree.h"
#include "TreeIterator.h"
#include "c_parser.h"
#include "c_parser_tools.h"

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


int iteratorTest(Tree root)
{
TreeIterator it;
Tree i;

	treeFixParents(root, NULL);

	it = treeIteratorNew();
	
	i = treeIteratorBeginPreorder(it, root);
	while(i){
		printNodeValue(i->nodevalue, stdout, it->level);	
		fprintf(stdout, "\n");

		i = treeIteratorNextPreorder(it);
	}	
}

int main(int argc, char **argv)
{
//CxValue  json;
xParser x;
char *buffer;
int bytes, result;
xParserExtraDataType extra;

	//bytes = read(0, buffer, 32767);
	buffer = readToBuffer(0, 32768, 1, &bytes);
	buffer[bytes] = 0;
	
	extra.syms = symbolTableNew(500);
	extra.struct_or_union_name_escope = 0;
	extra.level = 0;
	extra.file = strdup("<stdin>");

	symbolTableRegister(extra.syms, "__builtin_va_list", 1);

	x = xParserNew(buffer, &extra);	

	result = xParserParse(x);

	fprintf(stdout,"Input Size: %d\n", bytes);
	fprintf(stdout,"cursor: %d\n", x->cursor);
	fprintf(stdout,"Last Token: %d\n", x->currToken);
	fprintf(stdout,"\n");
	fprintf(stdout,"Symbol Table:\n");
	symbolTablePrint(extra.syms, stdout);

	if(result>0){
		fprintf(stderr,"Success to parse line\n\n");

		fprintf(stdout,"\nResult:\n");
		treePrintChildreenCount(x->value[0].t, stdout, 2, printNodeValue);
		fprintf(stdout,"\n");

		fprintf(stdout,"\nResult: ========================\n");
		iteratorTest(x->value[0].t);
		fprintf(stdout,"\nEnd:    ========================\n");

		x->value[0].t = treeReduceToMinimal(x->value[0].t, isRemovable);

		fprintf(stdout,"Result (reduced 1):\n");
		treePrintChildreenCount(x->value[0].t, stdout, 2, printNodeValue);
		fprintf(stdout,"\n\n");

		fprintf(stdout,"Result (only tokens):\n");
		treePrint(x->value[0].t, stdout, 2, printNodeValueOnlyToken);
		fprintf(stdout,"\n\n");

		//list = x->value[0].complist;
		//fprintf(stdout,"\nPrint:\n");
		//xComponentListPrint(list, stdout, 0);
		//fprintf(stdout,"\nCode:\n");
		//cxComponentListGenCode(list, stdout, 0);
		//fprintf(stdout,";\n");
	}else{
		fprintf(stderr,"Failed to parse!\n");
	}
	

	xParserFree(x);
	free(buffer);
}

