#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Symbol.h"

SymbolTable symbolTableNew(int size)
{
SymbolTable self;

	if((self = malloc(sizeof(*self)))==NULL) return NULL;
	
	self->s = malloc(sizeof(*(self->s)) * size);
	if(self->s == NULL){
		free(self);
		return NULL;
	}

	self->size = 0;
	self->allocated = size;
}

int symbolTableRegister(SymbolTable self, char *name, int type)
{
	if(self->size>=self->allocated){
		fprintf(stderr,"Symbol table overflow\n");
		exit(-1);
	}
	self->s[self->size].name = strdup(name);
	self->s[self->size].type = type;
	self->size++;
	//fprintf(stderr,"Symbol: %s registered as typedef\n", name);
}

int symbolTableGetType(SymbolTable self, char *name)
{
int c;

	for(c=0; c<self->size; c++){
		if(strcmp(name, self->s[c].name)==0) return self->s[c].type;
	}
	
	return 0;
}

int symbolTablePrint(SymbolTable self, FILE *fp)
{
int c;

	for(c=0; c<self->size; c++){
		fprintf(fp, "Symbol: %s type: %d\n", self->s[c].name, self->s[c].type);
	}
	
	return 1;
}
