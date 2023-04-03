#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "Type.h"

#define SYMBOL_MAXLEVELS 128

typedef struct symbol *Symbol;
typedef struct symbolTable *SymbolTable;

struct symbol {
	char	*name;
	int	symbol_type;
	int	level;
	Type	type;
};

struct symbolTable {
	Symbol	s;
	int	size;
	int	allocated;
	int 	current_level;
	int	level_start[SYMBOL_MAXLEVELS];
};

enum symbol_types {SYMBOL_TYPEOTHER=0, SYMBOL_TYPEDEFNAME=1, SYMBOL_VARIABLE=2};

SymbolTable symbolTableNew(int size);

int symbolTableRegister(SymbolTable self, char *name, int symbol_type, int level);
int symbolTableGetSymbolType(SymbolTable self, char *name);
int symbolTablePrint(SymbolTable self, FILE *fp);
int symbolTableLevelUp(SymbolTable self);
int symbolTableLevelDown(SymbolTable self);

#endif
