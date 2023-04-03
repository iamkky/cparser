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
        self->current_level;
        self->level_start[0] = 0;

	return self;
}

int symbolTableLevelUp(SymbolTable self)
{
	if(self==NULL){
		fprintf(stderr,"Null Exception at symbolTableLevelUp\n");
		return -1;
	}

	if(self->current_level >= SYMBOL_MAXLEVELS){
		fprintf(stderr,"Symbol Table: Max Levels reached\n");
		return -1;
	}

	self->current_level++;
	self->level_start[self->current_level] = self->size;

	return 0;
}

int symbolTableLevelDown(SymbolTable self)
{
	if(self==NULL){
		fprintf(stderr,"Null Exception at symbolTableLevelUp\n");
		return -1;
	}

	if(self->current_level == 0){
		fprintf(stderr,"Symbol Table: Can not level down from level 0\n");
		return -1;
	}

	self->size = self->level_start[self->current_level];
	self->current_level--;

	return 0;

}


int symbolTableRegister(SymbolTable self, char *name, int symbol_type, int level)
{
	if(self->size>=self->allocated){
		fprintf(stderr,"Symbol table overflow\n");
		exit(-1);
	}
	self->s[self->size].name = strdup(name);
	self->s[self->size].symbol_type = symbol_type;
	self->s[self->size].level = level;
	self->s[self->size].type = NULL;
	
	return self->size++;
	//fprintf(stderr,"Symbol: %s registered as typedef\n", name);
}

int symbolTableGetSymbolType(SymbolTable self, char *name)
{
int c;

	for(c=self->size-1; c>=0; c--){
		if(strcmp(name, self->s[c].name)==0) return self->s[c].symbol_type;
	}
	
	return 0;
}

int symbolTablePrint(SymbolTable self, FILE *fp)
{
int c;

	for(c=0; c<self->size; c++){
		fprintf(fp, "Symbol:%s, type:%d, level: %d\n", self->s[c].name, self->s[c].symbol_type, self->s[c].level);
	}
	
	return 1;
}
