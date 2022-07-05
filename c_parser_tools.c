#include <stdio.h>
#include "Symbol.h"
#include "Tree.h"
#include "c_parser.h"
#include "c_parser.tokens.h"
#include "c_parser_tools.h"

#define NO_ANSITERM
#include "ansiterm.h"

int isRemovable(void *nodevalue)
{
struct symbol_info *sinfo;

	sinfo = (struct symbol_info *)nodevalue;

	return !(sinfo->is_token);
}

int printNodeValue(void *nodevalue, FILE *fp, int level)
{
struct symbol_info *sinfo;
int c;

	sinfo = (struct symbol_info *)nodevalue;

	for(c=0; c<level; c++){
		fprintf(fp," ");
	}

	if(sinfo->is_token){
		fprintf(fp, ANSIBOLD ANSIBLUE "%s[%d] value:[[" ANSIRED "%s" ANSIBLUE "]]" ANSIRESET " file:%s, line:%d",
			Rdpp_xParserTerminals_Names[sinfo->id-1000], sinfo->id, sinfo->str, sinfo->file, sinfo->lnumber);
	}else{
		fprintf(fp, ANSIBOLD ANSIGREEN "%s[%d]" ANSIRESET,
			Rdpp_xParserNonterminals_Names[sinfo->id-10000], sinfo->id);
	}
}

int printNodeValueOnlyToken(void *nodevalue, FILE *fp, int level)
{
struct symbol_info *sinfo;
int    c;

	sinfo = (struct symbol_info *)nodevalue;

	if(sinfo->is_token){
		for(c=0; c<level; c++){
			fprintf(fp," ");
		}
		if(sinfo->id == STRING){
			fprintf(fp,"\"%s\"", sinfo->str);
		}else{
			fprintf(fp,"%s", sinfo->str);
		}
		fprintf(fp,"\n");
	}
}

