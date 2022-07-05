#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

Tree treeNew(void *nodevalue)
{
Tree self;
int i;

	self = malloc(sizeof(struct tree));
	if(self==NULL){
		fprintf(stderr,"Failed malloc\n");
		exit(-1);
	}

	self->nodevalue = nodevalue;

	self->n_child = 0;
	self->n_child_allocated = 128;

	if((self->child = malloc(sizeof(Tree) * self->n_child_allocated))==NULL){
		free(self);
		return NULL;
	}

	return self;
}

Tree treeGetFirstChild(Tree self)
{
	if(self==NULL) return NULL;

	if(self->n_child>0) return self->child[0];

	return NULL;
}

int treeIsLastChild(Tree self, Tree child)
{
	if(self==NULL) return 0;

	if(self->n_child==0) return 0;
	if(child == self->child[self->n_child-1]) return 1;

	return 0;
}

int treeWhichChild(Tree self, Tree child)
{
int c;

	if(self==NULL) return -2;
	
	for(c=0; c<self->n_child; c++){
		if(child == self->child[c]) return c;
	}

	return -1;
}

Tree treeGetNextChild(Tree self, Tree child)
{
int c;

	if(self==NULL) return NULL;

	if(self->n_child == 0) return NULL;
	if((c = treeWhichChild(self, child)) < self->n_child - 1) return self->child[c+1];

	return NULL;
}

int treeAddChild(Tree self, Tree child)
{
int i;

	if(self==NULL){
		fprintf(stderr,"treeAddChild: Null exception\n");
		return -1;
	}
	if(self->n_child>=self->n_child_allocated){
		if((self->child = realloc(self->child, sizeof(Tree) * 2 * self->n_child_allocated))==NULL){
			return -1;
		}
		self->n_child_allocated = 2 * self->n_child_allocated;
	}
	self->child[self->n_child] = child;
	self->n_child++;
	return 0;
}

int treeFixParents(Tree self, Tree parent)
{
int i;

	if(self==NULL){
		fprintf(stderr,"treeAddChild: Null exception\n");
		return -1;
	}

	self->parent = parent;
	for(i=0; i<self->n_child; i++){
		if(self->child[i]) treeFixParents(self->child[i], self);
	}
	return 0;
}

int treeGetChildCount(Tree self)
{
	if(self==NULL) return -1;
	return self->n_child;	
}

Tree treeGetChild(Tree self, int n)
{
	if(self==NULL) return NULL;
	if(n >= self->n_child) return NULL;
	return self->child[n];	
}

void *treeGetNodeValue(Tree self)
{
	if(self==NULL) return NULL;
	return self->nodevalue;	
}

Tree treeReduceToMinimal(Tree self, int (*isRemovable_fn)(void *))
{
Tree taux;
int i, c;

	if(self==NULL) return NULL;
	for(c=i=0; i<self->n_child; i++){
		if(self->child[i] == NULL) continue;
		taux = treeReduceToMinimal(self->child[i], isRemovable_fn);
		if(taux) self->child[c++] = taux;
	}
	self->n_child = c;
	
	if(isRemovable_fn(self->nodevalue) && self->n_child==0){
		return NULL;
	}

	if(isRemovable_fn(self->nodevalue) && self->n_child==1){
		return self->child[0];
	}
	return self;
}

int treePrintChildreenCount(Tree self, FILE *fp, int level, int (*print_fn)(void *, FILE *, int))
{
int c, i;
	
	if(self==NULL){
		fprintf(stderr,"Tree node null reached\n");
		return -1;
	}

	print_fn(self->nodevalue, fp, level);
	fprintf(fp,", childreen:%d", self->n_child);
	fprintf(fp,"\n");

	for(i=0; i<self->n_child; i++){
		if(self->child[i]) treePrintChildreenCount(self->child[i], fp, level+2, print_fn);
	}

	return 0;
}

int treePrint(Tree self, FILE *fp, int level, int (*print_fn)(void *, FILE *, int))
{
int c, i;
	
	if(self==NULL){
		fprintf(stderr,"Tree node null reached\n");
		return -1;
	}

	print_fn(self->nodevalue, fp, level);

	for(i=0; i<self->n_child; i++){
		if(self->child[i]) treePrint(self->child[i], fp, level+2, print_fn);
	}

	return 0;
}
