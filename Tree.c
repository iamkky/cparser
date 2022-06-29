#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "c_parser.tokens.h"

//#define NO_ANSITERM
#include "ansiterm.h" 

Tree treeNew(int type, char *value)
{
Tree self;
int i;

	self = malloc(sizeof(struct tree));
	if(self==NULL){
		fprintf(stderr,"Failed malloc\n");
		exit(-1);
	}

	self->type = type ;
	self->value = value ? strdup(value) : NULL;
	self->n_child = 0;
	self->n_child_allocated = 128;

	if((self->child = malloc(sizeof(Tree) * self->n_child_allocated))==NULL){
		free(self);
		return NULL;
	}

	return self;
}

int treeAddChild(Tree self, Tree child)
{
int i;

	if(self==NULL){
		fprintf(stderr,"treeAddChild: Null exception\n");
		return -1;
	}
	if(self->n_child>=self->n_child_allocated){
		if((self->child = malloc(sizeof(Tree) * 2 * self->n_child_allocated))==NULL){
			return -1;
		}
		self->n_child_allocated = 2 * self->n_child_allocated;
	}
	self->child[self->n_child] = child;
	self->n_child++;
	return 0;
}

Tree treeReduceToMinimal(Tree self, int nt_start)
{
Tree taux;
int i, c;

	if(self==NULL) return NULL;
	for(c=i=0; i<self->n_child; i++){
		if(self->child[i] == NULL) continue;
		taux = treeReduceToMinimal(self->child[i], nt_start);
		if(taux) self->child[c++] = taux;
	}
	self->n_child = c;
	
	if(self->type>= nt_start && self->n_child==0){
		return NULL;
	}
	if(self->type>= nt_start && self->n_child==1){
		return self->child[0];
	}
	return self;
}

int treePrint(Tree self, FILE *fp, int level)
{
int c, i;
	
	if(self==NULL){
		fprintf(stderr,"Tree node null reached\n");
		return -1;
	}
	for(c=0; c<level; c++){
		fprintf(fp," ");
	}
	if(self->type>=10000){
		fprintf(fp, ANSIBOLD ANSIGREEN "%s[%d]" ANSIRESET,
			Rdpp_xParserNonterminals_Names[self->type-10000], self->type);
	}else{
		fprintf(fp, ANSIBOLD ANSIBLUE "%s[%d] value:[[" ANSIRED "%s" ANSIBLUE "]]" ANSIRESET,
			Rdpp_xParserTerminals_Names[self->type-1000], self->type, self->value);
	}
	fprintf(fp,", p:%p", self);
	fprintf(fp,", childreen:%d", self->n_child);
	fprintf(fp,"\n");
	for(i=0; i<self->n_child; i++){
		if(self->child[i]) treePrint(self->child[i], fp, level+2);
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
