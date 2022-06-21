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

enum types {TYPEOTHER=0, TYPEDEFNAME=1};

SymbolTable symbolTableNew(int size);

int symbolTableRegister(SymbolTable table, char *name, int type);
int symbolTableGetType(SymbolTable table, char *name);
int symbolTablePrint(SymbolTable table, FILE *fp);

#endif
