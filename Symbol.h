#ifndef _SYMBOL_H_
#define _SYMBOL_H_

typedef struct symbol *Symbol;
typedef struct symbolTable *SymbolTable;

struct symbol {
	char	*name;
	int	type;
};

struct symbolTable {
	Symbol	s;
	int	size;
	int	allocated;
};

enum types {TYPEDEFNAME=1, TYPEOTHER};

SymbolTable symbolTableNew(int size);

int symbolTableRegister(SymbolTable table, char *name, int type);
int symbolTableGet(SymbolTable table, char *name);
int symbolTablePrint(SymbolTable table);

#endif
