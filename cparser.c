#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "Symbol.h"
#include "Tree.h"
#include "TreeIterator.h"
#include "c_parser.h"
#include "c_parser_tools.h"

struct options {
	char *gencode_filename;
	char *tree_filename;
	char *reduced_tree_filename;
	char *symbols_filename;
} options = {
	NULL,
	NULL,
	NULL,
	NULL,
};

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

static void missingParameter(char *option)
{
	fprintf(stderr,"Missing parameter for options %s\n", option);
	exit(-1);
}

int get_options(int argc, char **argv, struct options *options)
{
int argcount = 1;

	while(argcount<argc){
		if(!strcmp(argv[argcount], "-c")){
			if(++argcount==argc) missingParameter("-c");
			options->gencode_filename = argv[argcount++];
			continue;
		}
		if(!strcmp(argv[argcount], "-t")){
			if(++argcount==argc) missingParameter("-t");
			options->tree_filename = argv[argcount++];
			continue;
		}
		if(!strcmp(argv[argcount], "-r")){
			if(++argcount==argc) missingParameter("-r");
			options->reduced_tree_filename = argv[argcount++];
			continue;
		}
		if(!strcmp(argv[argcount], "-s")){
			if(++argcount==argc) missingParameter("-s");
			options->symbols_filename = argv[argcount++];
			continue;
		}
		fprintf(stderr,"know command line parameter: %s\n", argv[argcount]);
		exit(-1);
	}

	return argcount;
}

FILE *openOutputFile(char *filename)
{
FILE *fp;

	if((fp = fopen(filename,"w"))==NULL){
		fprintf(stderr,"Could not open output file %s\n", options.tree_filename);
		exit(-1);
	}

	return fp;
}

// Worst possible implementation :-)
int printCodeSnippet(xParser self)
{
int c, cln = 0, ch, flag = 0;

	c = self->cursor < 128 ? 0 : self->cursor - 128;

	cln = 0;
	for(cln=0; c < self->cursor+128; c++){

		ch = self->buffer[c];
		if(ch==0) break;

		fputc(ch, stdout);

		if(self->buffer[c] == '\n') {
			if(c<self->cursor){
				cln = 0;
			}else{
				if(flag==0){
					while(cln-->0){
						fputc(' ', stdout);
					}
					fprintf(stdout,"^   just here\n");
					flag = 1;
				}
			}
		}else if(self->buffer[c] == '\t') {
			fputs("        ", stdout);
		}else{
			cln++;
		}
		
	}

}

int unexpected_handler(xParser self, int token, int nonterminal)
{
int size;

	fprintf(stderr,"HHH: Expected: token: %d\n", token);
	printCodeSnippet(self);
}

int backtrackFail_handler(xParser self, int nonterminal)
{
int size;

	fprintf(stderr,"HHH: Backtracking failed:  %d\n", nonterminal);
	printCodeSnippet(self);
}

int main(int argc, char **argv)
{
xParserExtraDataType	extra;
xParser			x;
FILE	*fp_code, *fp_tree, *fp_reduced_tree, *fp_symbols;
char	*buffer;
int	bytes, result;

	get_options(argc, argv, &options);

	buffer = readToBuffer(0, 32768, 1, &bytes);
	buffer[bytes] = 0;
	
	extra.syms = symbolTableNew(2000);
	extra.struct_or_union_name_escope = 0;
	extra.level = 0;
	extra.file = strdup("<stdin>");

	symbolTableRegister(extra.syms, "__builtin_va_list", 1);

	x = xParserNew(buffer, &extra);	

	xParserSetUnexpected(x, unexpected_handler);
	xParserSetBacktrackFail(x, backtrackFail_handler);

	result = xParserParse(x);

	fprintf(stdout,"Input Size: %d\n", bytes);
	fprintf(stdout,"cursor: %d\n", x->cursor);
	fprintf(stdout,"Last Token: %d\n", x->currToken);
	fprintf(stdout,"\n");
	
	if(options.symbols_filename && (fp_symbols = openOutputFile(options.symbols_filename))){
		symbolTablePrint(extra.syms, fp_symbols);
	}

	if(result>0){
		if(options.tree_filename && (fp_tree = openOutputFile(options.tree_filename))){
			//iteratorTest(x->value[0].t);
			treePrintChildreenCount(x->value[0].t, fp_tree, 2, printNodeValue);
			fclose(fp_tree);
		}

		x->value[0].t = treeReduceToMinimal(x->value[0].t, isRemovable);

		if(options.reduced_tree_filename && (fp_reduced_tree = openOutputFile(options.reduced_tree_filename))){
			treePrintChildreenCount(x->value[0].t, fp_reduced_tree, 2, printNodeValue);
			fclose(fp_reduced_tree);
		}

		if(options.gencode_filename && (fp_code = openOutputFile(options.gencode_filename))){
			treePrint(x->value[0].t, fp_code, 2, printNodeValueOnlyToken);
			fclose(fp_code);
		}
	}else{
		fprintf(stderr,"Failed to parse!\n");
		exit(-1);
	}
	

	xParserFree(x);
	free(buffer);
}

