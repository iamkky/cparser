#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "c_parser.tokens.h"

//#define NO_ANSITERM

#include "ansiterm.h" 

Tree treeNew(int type, char *value)
{
Tree t;
int i;

	t = malloc(sizeof(struct tree));
	if(t==NULL){
		fprintf(stderr,"Failed malloc\n");
		exit(-1);
	}

	t->type = type ;
	t->value = value ? strdup(value) : NULL;
	t->n_child = 0;

	for(i=0; i<256; i++){
		t->child[i] = NULL;
	}

	return t;
}

int treeAddChild(Tree t, Tree child)
{
int i;

	if(t==NULL){
		fprintf(stderr,"treeAddChild: Null exception\n");
		return -1;
	}
	if(t->n_child>=256){
		fprintf(stderr,"Tree child vector overflow\n");
		return -1;
	}
	t->child[t->n_child] = child;
	t->n_child++;
	return 0;
}

Tree treeReduceToMinimal(Tree t, int nt_start)
{
Tree taux;
int i, c;

	if(t==NULL) return t;
	for(c=i=0; i<t->n_child; i++){
		if(t->child[i] == NULL) continue;
		taux = treeReduceToMinimal(t->child[i], nt_start);
		if(taux) t->child[c++] = taux;
	}
	t->n_child = c;
	
	if(t->type>= nt_start && t->n_child==0){
		return NULL;
	}
	if(t->type>= nt_start && t->n_child==1){
		return t->child[0];
	}
	return t;
}

int treePrint(Tree t, FILE *fp, int level)
{
int c, i;
	
	if(t==NULL){
		fprintf(stderr,"Tree node null reached\n");
		return -1;
	}
	for(c=0; c<level; c++){
		fprintf(fp," ");
	}
	if(t->type>=10000){
		fprintf(fp, ANSIBOLD ANSIGREEN "%s[%d]" ANSIRESET,
			Rdpp_xParserNonterminals_Names[t->type-10000], t->type);
	}else{
		fprintf(fp, ANSIBOLD ANSIBLUE "%s[%d] value:[[" ANSIRED "%s" ANSIBLUE "]]" ANSIRESET,
			Rdpp_xParserTerminals_Names[t->type-1000], t->type, t->value);
	}
	fprintf(fp,", p:%p", t);
	fprintf(fp,", childreen:%d", t->n_child);
	fprintf(fp,"\n");
	for(i=0; i<t->n_child; i++){
		if(t->child[i]) treePrint(t->child[i], fp, level+2);
	}

	return 0;
}

int treePrintToken(Tree t, FILE *fp, int level, int non_terminal_start)
{
int c, i;
	
	if(t==NULL){
		fprintf(stderr,"Tree node null reached\n");
		return -1;
	}
	if(t->type<non_terminal_start){
		for(c=0; c<level; c++){
			fprintf(fp," ");
		}
		fprintf(fp,"%s", t->value);
		fprintf(fp,"\n");
	}
	for(i=0; i<t->n_child; i++){
		if(t->child[i]) treePrintToken(t->child[i], fp, level+2, non_terminal_start);
	}

	return 0;
}
